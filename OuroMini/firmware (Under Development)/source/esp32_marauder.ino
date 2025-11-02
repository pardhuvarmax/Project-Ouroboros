/* FLASH SETTINGS

Board: LOLIN D32
Flash Frequency: 80MHz
Partition Scheme: Minimal SPIFFS
Upload Speed: 115200
PSRAM: Enabled
*/

/* 
 ESP32 OuroMini Firmware
 Team Ouroboros 2025
 Version 1.0
 Inspired By ESP32 Marauder by JustCallMeRick.
*/

#include "configs.h"

#ifndef HAS_SCREEN
  #define MenuFunctions_h
  #define Display_h
#endif

#include <WiFi.h>
#include "EvilPortal.h"
#include "WebInterface.h"
#include <Wire.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_netif.h"
#include "esp_event.h"
#include <Arduino.h>

#ifdef HAS_GPS
  #include "GpsInterface.h"
#endif

#include "Assets.h"
#include "WiFiScan.h"
#ifdef HAS_SD
  #include "SDInterface.h"
#endif
#include "Buffer.h"

#ifdef HAS_FLIPPER_LED
  #include "flipperLED.h"
#elif defined(XIAO_ESP32_S3)
  #include "xiaoLED.h"
#elif defined(MARAUDER_M5STICKC) || defined(MARAUDER_M5STICKCP2)
  #include "stickcLED.h"
#elif defined(HAS_NEOPIXEL_LED)
  #include "LedInterface.h"
#endif

#include "settings.h"
#include "CommandLine.h"
#include "lang_var.h"

#ifdef HAS_BATTERY
  #include "BatteryInterface.h"
#endif

#ifdef HAS_SCREEN
  #include "Display.h"
  #include "MenuFunctions.h"
#endif

#ifdef HAS_BUTTONS
  #include "Switches.h"
  #if (U_BTN >= 0)
    Switches u_btn = Switches(U_BTN, 1000, U_PULL);
  #endif
  #if (D_BTN >= 0)
    Switches d_btn = Switches(D_BTN, 1000, D_PULL);
  #endif
  #if (L_BTN >= 0)
    Switches l_btn = Switches(L_BTN, 1000, L_PULL);
  #endif
  #if (R_BTN >= 0)
    Switches r_btn = Switches(R_BTN, 1000, R_PULL);
  #endif
  #if (C_BTN >= 0)
    Switches c_btn = Switches(C_BTN, 1000, C_PULL);
  #endif
#endif

// ----- Objects -----
WiFiScan wifi_scan_obj;
EvilPortal evil_portal_obj;
Buffer buffer_obj;
Settings settings_obj;
CommandLine cli_obj;

#ifdef HAS_GPS
  GpsInterface gps_obj;
#endif

#ifdef HAS_BATTERY
  BatteryInterface battery_obj;
#endif

#ifdef HAS_SCREEN
  Display display_obj;
  MenuFunctions menu_function_obj;
#endif

#if defined(HAS_SD) && !defined(HAS_C5_SD)
  SDInterface sd_obj;
#endif

#ifdef MARAUDER_M5STICKC
  AXP192 axp192_obj;
#endif

#ifdef HAS_FLIPPER_LED
  flipperLED flipper_led;
#elif defined(XIAO_ESP32_S3)
  xiaoLED xiao_led;
#elif defined(MARAUDER_M5STICKC) || defined(MARAUDER_M5STICKCP2)
  stickcLED stickc_led;
#else
  LedInterface led_obj;
#endif

#ifdef HAS_NEOPIXEL_LED
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);
#endif

uint32_t currentTime = 0;

// ----- Web / Scan LinkedLists -----
#include "Globals.h"   // assumes Globals.h declares/defines accessPoints, probes, webStations etc.

// Timing
unsigned long lastScan = 0;
const unsigned long scanIntervalMs = 5000; // 5s

// --------------------
// Forward declarations
// --------------------
void startAsyncScan();
void onScanDone(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void backlightOn();
void backlightOff();

// --------------------
// Idempotent setup guard + debug
// --------------------
static bool setupCompleted = false; // prevents double init within same boot
static esp_event_handler_instance_t scan_done_handler_instance = NULL;

// Helper: readable reset reason
const char* resetReasonToStr(esp_reset_reason_t r) {
  switch(r) {
    case ESP_RST_POWERON: return "POWERON";
    case ESP_RST_EXT: return "EXTERNAL";
    case ESP_RST_SW: return "SOFTWARE";
    case ESP_RST_PANIC: return "PANIC";
    case ESP_RST_INT_WDT: return "INTERNAL WATCHDOG";
    case ESP_RST_TASK_WDT: return "TASK WATCHDOG";
    case ESP_RST_WDT: return "OTHER WATCHDOG";
    case ESP_RST_DEEPSLEEP: return "DEEPSLEEP WAKE";
    case ESP_RST_BROWNOUT: return "BROWNOUT";
    case ESP_RST_SDIO: return "SDIO";
    default: return "UNKNOWN";
  }
}

// Prevent repeated Wi-Fi / scan handler init
static bool wifiInitialized = false;
static bool scanHandlerRegistered = false;

// Background scan control
static bool backgroundScanEnabled = true;   // master switch for background scanning
static bool backgroundScanPaused = false;   // true while sniff/other radio mode is active
static bool pendingBackgroundScan = false;  // set when a scan was requested but couldn't run

// --------------------
// Helper globals & functions (must be defined before loop() so they're visible)
// --------------------

// set to true to see background-scan debug messages in Serial
bool showScanLogs = false; // set to true only when debugging

// Check if promiscuous mode is active
bool isPromiscuousEnabled() {
    bool enabled = false;
    // esp_wifi_get_promiscuous returns esp_err_t, but fills a bool via pointer on Arduino/IDF
    // If the SDK differs, you can replace this with whatever function is provided by your SDK.
    esp_err_t rc = esp_wifi_get_promiscuous(&enabled);
    (void)rc; // ignore return code here
    return enabled;
}

// --------------------
// Setup
// --------------------
void setup() {
    // Print reset reason early for debugging reboots
    esp_reset_reason_t rr = esp_reset_reason();
    Serial.begin(115200);
    delay(10); // small delay so serial is ready (non-blocking)
    Serial.printf("=== Boot (reset reason=%s) ===\n", resetReasonToStr(rr));

    // Prevent double initialization if setup() is somehow re-entered
    if (setupCompleted) {
        Serial.println("Setup already completed — skipping re-init.");
        return;
    }
    setupCompleted = true; // mark early

    delay(500);

    Serial.println("ESP-IDF version: " + String(esp_get_idf_version()));

    #ifndef HAS_DUAL_BAND
      esp_spiram_init();
    #endif

    #if defined(MARAUDER_M5STICKC) && !defined(MARAUDER_M5STICKCP2)
      axp192_obj.begin();
    #endif

    #ifdef HAS_SCREEN
      pinMode(TFT_BL, OUTPUT);
      backlightOff();
    #endif

    settings_obj.begin();
    buffer_obj = Buffer();

    wifi_scan_obj.RunSetup();
    evil_portal_obj.setup();

    #ifdef HAS_BATTERY
      battery_obj.RunSetup();
    #endif

    #ifdef HAS_SCREEN
      display_obj.RunSetup();
      menu_function_obj.RunSetup();
      display_obj.tft.setTextColor(TFT_WHITE, TFT_BLACK);
      display_obj.tft.drawCentreString("ESP32 OuroMini", TFT_WIDTH/2, TFT_HEIGHT * 0.33, 1);
      display_obj.tft.drawCentreString("Team Ouroboros", TFT_WIDTH/2, TFT_HEIGHT * 0.5, 1);
      display_obj.tft.drawCentreString(display_obj.version_number, TFT_WIDTH/2, TFT_HEIGHT * 0.66, 1);
      backlightOn();
    #endif

    cli_obj.RunSetup();
    Serial.println(F("CLI Ready"));

    // ----------- Proper ESP-IDF network init -------------
    esp_err_t r;

    r = esp_netif_init();
    if (r != ESP_OK) Serial.printf("⚠️ esp_netif_init failed: %d\n", r);

    r = esp_event_loop_create_default();
    if (r != ESP_OK && r != ESP_ERR_INVALID_STATE) // invalid state means already created - ignore
        Serial.printf("⚠️ esp_event_loop_create_default failed: %d\n", r);

    // Create default netifs for STA and AP (needed for esp_wifi_start etc.)
    esp_netif_create_default_wifi_sta();
    esp_netif_create_default_wifi_ap();

    // Initialize Wi-Fi driver
    if (!wifiInitialized) {
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        if (esp_wifi_init(&cfg) != ESP_OK)
            Serial.println("❌ esp_wifi_init failed");
        else
            Serial.println("✅ Wi-Fi driver initialized");

        esp_wifi_set_storage(WIFI_STORAGE_RAM);

        if (esp_wifi_set_mode(WIFI_MODE_APSTA) != ESP_OK) {
          Serial.println("⚠️ esp_wifi_set_mode failed");
        }

        wifi_config_t sta_config = {};
        sta_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
        sta_config.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
        sta_config.sta.threshold.authmode = WIFI_AUTH_OPEN;
        esp_wifi_set_config(WIFI_IF_STA, &sta_config);

        wifi_config_t ap_config = {};
        strncpy((char*)ap_config.ap.ssid, "OuroMini", sizeof(ap_config.ap.ssid)-1);
        ap_config.ap.ssid_len = strlen("OuroMini");
        ap_config.ap.channel = 1;
        strncpy((char*)ap_config.ap.password, "ouroboros", sizeof(ap_config.ap.password)-1);
        ap_config.ap.max_connection = 4;
        ap_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
        esp_wifi_set_config(WIFI_IF_AP, &ap_config);

        if (esp_wifi_start() != ESP_OK) {
          Serial.println("❌ esp_wifi_start failed");
        } else {
          Serial.println("✅ SoftAP + STA mode active");
        }

        wifiInitialized = true;
    } else {
      Serial.println("⚙️ Wi-Fi already initialized, skipping duplicate init");
    }

    // small pause to let stack come up
    delay(300);

    // Register scan event (use instance-register to avoid duplicate registrations)
    if (scan_done_handler_instance == NULL) {
      esp_err_t er = esp_event_handler_instance_register(WIFI_EVENT, WIFI_EVENT_SCAN_DONE, &onScanDone, NULL, &scan_done_handler_instance);
      if (er != ESP_OK) {
        Serial.printf("⚠️ esp_event_handler_instance_register failed: %d\n", er);
      } else {
        Serial.println("✅ Scan done handler registered");
      }
    } else {
      Serial.println("Scan done handler already registered (skipping)");
    }

    // --- Initialize Web Interface ---
    webIF.access_points = &accessPoints;
    webIF.WebStations = &webStations;
    webIF.probe_req_ssids = &probes;

    if (!webIF.begin("OuroMini")) Serial.println("❌ WebInterface failed to start!");
    else Serial.println("🌐 WebInterface started on http://192.168.4.1");

    // --- Bind Web Commands to CLI ---
    webIF.onCommand = [&](String cmd) {
        Serial.printf("[WEB CMD] %s\n", cmd.c_str());
        cli_obj.runCommand(cmd.c_str());  // ⬅️ direct CLI handler from CommandLine Engine.
    };

    // --- Kick off first scan ---
    startAsyncScan();
    Serial.println("🚀 Initial scan started...");
}

// --------------------
// Loop
// --------------------
void loop() {
    currentTime = millis();

    if (millis() - lastScan > scanIntervalMs) {
        lastScan = millis();
        startAsyncScan();
    }

    cli_obj.main(currentTime);
    wifi_scan_obj.main(currentTime);
    buffer_obj.save();
    settings_obj.main(currentTime);

    #ifdef HAS_BATTERY
      battery_obj.main(currentTime);
    #endif

    #ifdef HAS_SCREEN
      menu_function_obj.main(currentTime);
      display_obj.main(wifi_scan_obj.currentScanMode);
    #endif

    #ifdef HAS_FLIPPER_LED
      flipper_led.main();
    #elif defined(XIAO_ESP32_S3)
      xiao_led.main();
    #elif defined(MARAUDER_M5STICKC)
      stickc_led.main();
    #else
      led_obj.main(currentTime);
    #endif

    // --- Background scan resume logic ---
    if (backgroundScanPaused && !isPromiscuousEnabled()) {
        backgroundScanPaused = false;
        if (pendingBackgroundScan) {
            pendingBackgroundScan = false;

            // Wait a short adaptive period while driver settles.
            // Poll promiscuous state for up to 2s, then give the driver a
            // little breathing room (650 ms) before trying to start background scan.
            unsigned long t0 = millis();
            while (isPromiscuousEnabled() && (millis() - t0) < 2000) {
                delay(100);
            }

            // Breathe, you silicon piece of fucking driver
            Serial.println("DRIVER COOLDOWN [RX - AP/STA SWITCH]...");
            delay(1200);

            startAsyncScan();
            if (showScanLogs) Serial.println("▶ Background scan resumed");
            else Serial.printf("⚠️ Failed to resume background scan");
        }
    }

    delay(20);
}

// --------------------
// Backlight helpers
// --------------------
void backlightOn() {
    #ifdef HAS_SCREEN
      #ifdef MARAUDER_MINI
        digitalWrite(TFT_BL, LOW);
      #else
        digitalWrite(TFT_BL, HIGH);
      #endif
    #endif
}

void backlightOff() {
    #ifdef HAS_SCREEN
      #ifdef MARAUDER_MINI
        digitalWrite(TFT_BL, HIGH);
      #else
        digitalWrite(TFT_BL, LOW);
      #endif
    #endif
}

// --------------------
// Async Wi-Fi Scan (silent mode toggle)
// --------------------
void startAsyncScan() {
    if (!backgroundScanEnabled) return;       // master switch off
    if (backgroundScanPaused) {
        // we already paused due to sniff mode — mark that we wanted a scan
        pendingBackgroundScan = true;
        return;
    }

    // If radio is in promiscuous mode, pause background scanning and queue request
    if (isPromiscuousEnabled()) {
        backgroundScanPaused = true;
        pendingBackgroundScan = true;
        if (showScanLogs) Serial.println("⏸ Background scan paused (sniff active)");
        return;
    }

    wifi_scan_config_t scanConf = {};
    scanConf.show_hidden = true;
    scanConf.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    scanConf.scan_time.active.min = 100;
    scanConf.scan_time.active.max = 300;

    esp_err_t err = esp_wifi_scan_start(&scanConf, false);
    if (err != ESP_OK) {
        // Ignore expected state conflict (ESP_ERR_WIFI_STATE) and silence spam
        if (err != ESP_ERR_WIFI_STATE) {
            Serial.printf("⚠️ esp_wifi_scan_start failed: %d\n", err);
        } else {
            // If scan failed due to state, mark pending so we try later
            pendingBackgroundScan = true;
            backgroundScanPaused = true;
            if (showScanLogs) Serial.println("⏸ Background scan paused (ESP_WIFI_STATE_CONFLICT)");
        }
    } else {
        if (showScanLogs) {
            Serial.println("📡 Scan started (async)...");
        }
    }
}

// --------------------
// Scan done callback (silent mode toggle)
// --------------------
void onScanDone(void* arg, esp_event_base_t, int32_t, void* event_data) {
    wifi_event_sta_scan_done_t *info = (wifi_event_sta_scan_done_t*) event_data;

    if (showScanLogs)
        Serial.printf("✅ Scan done: status=%d, number=%d, scan_id=%d\n", info->status, info->number, info->scan_id);

    uint16_t apCount = 0;
    if (esp_wifi_scan_get_ap_num(&apCount) != ESP_OK) {
        if (showScanLogs) Serial.println("⚠️ Failed to get AP count");
        return;
    }

    if (apCount == 0) {
        accessPoints.clear();
        if (showScanLogs) Serial.println("No APs found");
        webIF.updateClients(); // still updates web dashboard
        return;
    }

    wifi_ap_record_t *ap_list = (wifi_ap_record_t*) malloc(sizeof(wifi_ap_record_t) * apCount);
    if (!ap_list) return;

    uint16_t outCount = apCount;
    if (esp_wifi_scan_get_ap_records(&outCount, ap_list) != ESP_OK) {
        free(ap_list);
        return;
    }

    accessPoints.clear();
    for (uint16_t i = 0; i < outCount; ++i) {
        wifi_ap_record_t &r = ap_list[i];
        String ssidStr = (r.ssid && strlen((char*)r.ssid) > 0) ? String((char*)r.ssid) : "";
        char bssidStr[18];
        snprintf(bssidStr, sizeof(bssidStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 r.bssid[0], r.bssid[1], r.bssid[2], r.bssid[3], r.bssid[4], r.bssid[5]);

        String encType;
        switch (r.authmode) {
            case WIFI_AUTH_OPEN: encType = "Open"; break;
            case WIFI_AUTH_WEP: encType = "WEP"; break;
            case WIFI_AUTH_WPA_PSK: encType = "WPA"; break;
            case WIFI_AUTH_WPA2_PSK: encType = "WPA2"; break;
            case WIFI_AUTH_WPA_WPA2_PSK: encType = "WPA/WPA2"; break;
            case WIFI_AUTH_WPA2_ENTERPRISE: encType = "WPA2-Enterprise"; break;
            case WIFI_AUTH_WPA3_PSK: encType = "WPA3"; break;
            default: encType = "Unknown"; break;
        }

        accessPoints.add(WebAccessPoint(
            ssidStr,
            r.primary,
            false,
            false,
            r.rssi,
            millis(),
            String(bssidStr),
            encType
        ));
    }

    free(ap_list);
    if (showScanLogs)
        Serial.printf("📋 Populated accessPoints with %d entries\n", accessPoints.size());

    // ✅ Always push updates to web dashboard
    webIF.updateClients();
}

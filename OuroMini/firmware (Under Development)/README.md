# Ouroboros Mini – Firmware Overview & Flow (Headless ESP32-WROOM32)

## Overview

The **Ouroboros Mini (OuroMini)** firmware is a **15-day rapid prototype** firmware optimized for **dual-use wireless security research** on a headless **ESP32-WROOM-32** board.
Focus areas: **Wi-Fi (2.4 GHz)** and **Bluetooth Low Energy (BLE)** scanning/telemetry, on-device capture/export, web-hosted dashboards, and modular demo sequences. Optional carrier-board peripherals (IR TX/RX, microSD, LEDs, kill switch) are supported if present.

**Scope**

* On-device scanning and capture for Wi-Fi (2.4 GHz) and BLE.
* Real-time telemetry for expo demos via a small web dashboard hosted by the ESP.
* Local logging to LittleFS (internal flash) and optional microSD.
* Modular architecture for rapid feature integration and iteration.
* High-visibility demo sequences for authorized expo/lab environments.

> ⚠️ **Legal/Operational Warning:** Any high-impact offensive features (deauth, Evil Portal, packet injection, active transmissions) must only be used in authorized, controlled environments. Follow local wireless regulations and venue rules.

---

## Repo Layout

```
firmware/
│
├── source/
│   ├── main.ino            # Core loop, setup, lightweight scheduler
│   ├── modules/            # wifi/, ble/, ir/ (if present), utils/
│   ├── libs/               # drivers: oled, websocket, logging utilities
│   └── config.h            # feature toggles & constants (expo_config.h variant)
│
├── binaries/               # prebuilt .bin (ouromini-expo.bin, ouromini-safe.bin)
├── docs/                   # docs/Expo_Presentation.md, Architecture.md, etc.
└── flashing.md             # flashing & quick start instructions
```

---

## Key Modules & Feature Matrix

> **Hardware baseline:** ESP32-WROOM-32 only (headless). Features marked *Optional HW* require extra components on the carrier board (microSD, IR LED/receiver, external sensors).

| Feature / Module       | Type              | Status       | Notes                                                                  |
| ---------------------- | ----------------- | ------------ | ---------------------------------------------------------------------- |
| Wi-Fi Scanner          | Defensive         | Stable       | Passive & active scan, AP/client enumeration, RSSI mapping.            |
| Wi-Fi Packet Capture   | Defensive         | Stable       | Promiscuous 2.4 GHz frame capture & basic logging (limited DPI).       |
| WPA Handshake Capture  | Defensive         | Stable       | Capture for export (offline cracking off-device).                      |
| Deauth / Flood         | Offensive         | Experimental | 2.4 GHz targeted deauth and rate-limited floods; expo/lab use only.    |
| Beacon / Fake AP       | Neutral           | Stable       | Create SSIDs / fake APs; flood intensity configurable.                 |
| Evil Portal            | Offensive         | Experimental | Captive portal hosting on AP — demo credential capture only.           |
| BLE Scanner            | Defensive         | Stable       | Advertisement scanning, RSSI logging, presence tracking.               |
| BLE Advertiser / GATT  | Neutral           | Stable       | Beacon/peripheral emulation, basic GATT server (demo control).         |
| IR Capture / Replay *  | Neutral           | Optional     | Requires IR TX/RX hardware on carrier board.                           |
| LittleFS / microSD Log | Defensive         | Stable       | Timestamped CSV/PCAP-lite logs; microSD optional for large captures.   |
| Web Dashboard / API    | Neutral           | Stable       | WebSocket telemetry, HTTP API endpoints (hosted by ESP).               |
| UART / Serial CLI      | Ops               | Stable       | Local serial CLI for interactive debugging.                            |
| Thermal Sensor Readout | Ops               | Stable       | Internal temperature sensor reporting.                                 |
| Kill-Switch GPIO       | Safety            | Stable       | Hardware input to immediately disable TX features when asserted.       |
| OTA Update (HTTP)      | Ops               | Stable       | Simple HTTP OTA for controlled environments.                           |
| BADUSB / Native USB*   | Offensive         | UNAVAILABLE  | **Not supported on WROOM32 (ESP32-S2/S3 required).**                   |
| Sub-GHz / NRF24 / NFC* | Neutral/Offensive | UNAVAILABLE  | Require external radio modules/shields; not part of headless baseline. |

* Optional or unavailable items are supported only if the carrier board includes the required hardware (marked clearly).

---

## Firmware Flow (High Level)

1. **Boot & Init**

   * Boot ROM → app starts.
   * Initialize logging (LittleFS), serial console, thermal sensor.
   * Probe for optional hardware (microSD, IR, LEDs); mount if present.
   * Load `config.h` / runtime config (expo vs safe build).

2. **Network & Radio Setup**

   * Wi-Fi driver: configure station/AP modes as requested; enable promiscuous if capture enabled.
   * BLE stack: start advertisement scanning and optional peripheral services.
   * IR module (if present): initialize capture hardware.
   * Configure web server & WebSocket endpoints.

3. **Main Loop — Scanning & Buffering**

   * Run periodic scan tasks (Wi-Fi, BLE) on configurable intervals.
   * Buffer captured frames/adv packets in RAM (ring buffer) for short-term visualization.
   * Flush logs to LittleFS or microSD every N seconds or when buffer full.

4. **Demo / Active Modules**

   * Operator triggers demo sequence via Web CLI or scheduled script.
   * Offensive modules (deauth, fake AP, Evil Portal) start only when explicitly commanded.
   * Respect configured rate-limits and enforce temporary TX backoff on errors.

5. **Visualization & Telemetry**

   * WebSocket pushes short history: device lists, RSSI timeseries, alerts.
   * Serial CLI available for live control and debug.
   * Optional minimal OLED or LED feedback if carrier board has them.

6. **Error Handling & Recovery**

   * File IO: retry writes; rotate logs on SD errors.
   * Watchdog timer resets on fatal deadlocks after graceful shutdown attempt.
   * Module restart on non-fatal driver failures (e.g., BLE stack hiccups).

---

## Development Notes & Tooling

* **Primary Framework:** Arduino-ESP32 (fast iteration). ESP-IDF port recommended for advanced/performance builds.
* **Toolchain:** PlatformIO (recommended) or Arduino CLI + esp32 core. Use `esp32dev` board profile for WROOM32 carriers.
* **Key libs:** `WiFi.h`, `esp_wifi_promiscuous.h` utilities, `NimBLE-Arduino` / `ESP32 BLE Arduino` stack, `AsyncWebServer` / `WebSockets`.
* **Structure tips:** Keep offensive TX code in isolated modules/files and call through guarded APIs to make auditing easier.
* **Prebuilt binaries:** Provide `ouromini-expo.bin` (full demo) and `ouromini-safe.bin` (observability only) if you want two release options — though the headless expo build can include all feasible features by default per your expo needs.

---

## Flashing Procedure (ESP32-WROOM-32 headless)

1. Connect via USB-to-serial (FTDI/CP210x/CH340) to your carrier board.
2. Use PlatformIO `pio run -t upload` or `esptool.py` / Espressif Flash Tool. Example `esptool.py` command:

```bash
esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z \
  0x1000 bootloader.bin 0x8000 partitions.bin 0x10000 ouromini-expo.bin
```

3. If using Arduino IDE, select `ESP32 Dev Module` / appropriate flash size & flash the `.bin`.
4. Verify: serial output should show boot banner, config, mounted LittleFS (or SD) and IP for captive AP (if started).

> Note: WROOM32 does not support native USB device HID (BADUSB). Do not attempt S2/S3 toolchain instructions on WROOM32 builds.

---

## Limitations & Notes (Headless Expo Build)

* **No native USB HID (BADUSB)** on WROOM32 — remove USB HID workflows or require S2/S3 hardware.
* **No built-in Sub-GHz / NRF24 / NFC / FM** — these need shields or external radios; the firmware contains hooks but will hide unavailable menus if hardware not present.
* **DPI is limited** — the MCU cannot perform full DPI; store captures for offline analysis on a PC.
* **Thermal & power:** Continuous TX + heavy logging increases device temp and power draw — monitor thermal values in the Web UI.
* **Regulatory:** Be sure to obtain permission for any active transmissions or disruptive demos.

---

## Recommended Expo Checklist (headless)

* Verify carrier board has microSD (if large logs), IR (if demo needs IR), and kill-switch wired.
* Preload `ouromini-expo.bin` and test offline handshake capture → export.
* Prepare one scripted demo sequence (scan → fake AP → evil portal → deauth burst) and rehearse in RF-safe area.
* Ensure venue permissions; inform neighboring booths if demo includes active TX.
* Keep physical kill-switch accessible and tested.

---

## Summary

This headless-focused firmware targets robust **Wi-Fi (2.4 GHz)** and **BLE** research & demo workflows on an **ESP32-WROOM-32** platform with optional carrier-board peripherals. The firmware is modular and optimized for quick expo demonstration while keeping a clear separation between passive monitoring and explicit active demo modules.

---
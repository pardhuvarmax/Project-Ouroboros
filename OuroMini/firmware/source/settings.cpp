#include "Settings.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "Globals.h"

// =======================
// GLOBAL VERSION
// =======================

// =======================
// BEGIN SETTINGS
// =======================
bool Settings::begin() {
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("Settings SPIFFS Mount Failed");
        return false;
    }

    File settingsFile;
    if (SPIFFS.exists("/settings.json")) {
        settingsFile = SPIFFS.open("/settings.json", FILE_READ);
        if (!settingsFile) {
            Serial.println(F("Could not open settings file"));
            return this->createDefaultSettings(SPIFFS);
        }
    } else {
        Serial.println("Settings file does not exist");
        return this->createDefaultSettings(SPIFFS);
    }

    DynamicJsonDocument jsonBuffer(2048);
    DeserializationError error = deserializeJson(jsonBuffer, settingsFile);
    if (error) {
        Serial.println("Error parsing settings file, regenerating defaults...");
        this->createDefaultSettings(SPIFFS);
    } else {
        serializeJson(jsonBuffer, this->json_settings_string);
    }
    settingsFile.close();
    return true;
}

// =======================
// CREATE DEFAULT SETTINGS
// =======================
bool Settings::createDefaultSettings(fs::FS &fs, bool flag, unsigned char val, String a, String b) {
    DynamicJsonDocument json(2048);
    JsonArray arr = json.createNestedArray("Settings");

    // Add dummy defaults
    JsonObject s1 = arr.createNestedObject();
    s1["name"] = "example_bool";
    s1["value"] = true;

    JsonObject s2 = arr.createNestedObject();
    s2["name"] = "example_string";
    s2["value"] = "default";

    File file = fs.open("/settings.json", FILE_WRITE);
    if (!file) return false;

    serializeJson(json, file);
    file.close();

    serializeJson(json, this->json_settings_string);
    return true;
}

// =======================
// PRINT JSON SETTINGS
// =======================
void Settings::printJsonSettings(const String &json) {
    Serial.println(json);
}

// =======================
// MAIN (CALLED FROM LOOP)
// =======================
void Settings::main(unsigned int currentTime) {
    static unsigned long lastUpdate = 0;
    const unsigned long UPDATE_INTERVAL = 5000; // 5 seconds

    // Only update periodically
    if (currentTime - lastUpdate < UPDATE_INTERVAL) return;
    lastUpdate = currentTime;

    // Reload settings from SPIFFS if file changed or auto-refresh flag is set
    File settingsFile = SPIFFS.open("/settings.json", FILE_READ);
    if (settingsFile) {
        DynamicJsonDocument jsonBuffer(2048);
        DeserializationError error = deserializeJson(jsonBuffer, settingsFile);
        settingsFile.close();
        if (!error) {
            String currentJson;
            serializeJson(jsonBuffer, currentJson);
            // Only update internal string if changed
            if (currentJson != this->json_settings_string) {
                this->json_settings_string = currentJson;
#ifdef HAS_SCREEN
                display_obj.print("Settings updated");
#endif
                Serial.println("Settings reloaded from SPIFFS");
            }
        } else {
            Serial.println("Failed to parse settings.json during main loop");
        }
    }

    // Optional: place for other recurring tasks, e.g., auto-save temp changes
}

// =======================================================
// TEMPLATE SPECIALIZATIONS IMPLEMENTATION
// =======================================================

// --------- LOAD SETTINGS ---------
template <>
bool Settings::loadSetting<bool>(const String &key) {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, this->json_settings_string);
    if (error) return false;
    for (JsonObject setting : doc["Settings"].as<JsonArray>()) {
        if (setting["name"].as<String>() == key)
            return setting["value"].as<bool>();
    }
    return false; // default
}

template <>
String Settings::loadSetting<String>(const String &key) {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, this->json_settings_string);
    if (error) return "";
    for (JsonObject setting : doc["Settings"].as<JsonArray>()) {
        if (setting["name"].as<String>() == key)
            return setting["value"].as<String>();
    }
    return "";
}

template <>
int Settings::loadSetting<int>(const String &key) {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, this->json_settings_string);
    if (error) return 0;
    for (JsonObject setting : doc["Settings"].as<JsonArray>()) {
        if (setting["name"].as<String>() == key)
            return setting["value"].as<int>();
    }
    return 0;
}

template <>
uint8_t Settings::loadSetting<uint8_t>(const String &key) {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, this->json_settings_string);
    if (error) return 0;
    for (JsonObject setting : doc["Settings"].as<JsonArray>()) {
        if (setting["name"].as<String>() == key)
            return setting["value"].as<uint8_t>();
    }
    return 0;
}

// --------- SAVE SETTINGS ---------
template <>
bool Settings::saveSetting<bool>(const String &key, const bool &value) {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, this->json_settings_string);
    if (error) return false;

    JsonArray arr = doc["Settings"].as<JsonArray>();
    bool found = false;
    for (JsonObject setting : arr) {
        if (setting["name"].as<String>() == key) {
            setting["value"] = value;
            found = true;
            break;
        }
    }

    if (!found) {
        JsonObject newSetting = arr.createNestedObject();
        newSetting["name"] = key;
        newSetting["value"] = value;
    }

    File file = SPIFFS.open("/settings.json", FILE_WRITE);
    if (!file) return false;
    serializeJson(doc, file);
    file.close();
    serializeJson(doc, this->json_settings_string);
    return true;
}

template <>
bool Settings::saveSetting<String>(const String &key, const String &value) {
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, this->json_settings_string);
    if (error) return false;

    JsonArray arr = doc["Settings"].as<JsonArray>();
    bool found = false;
    for (JsonObject setting : arr) {
        if (setting["name"].as<String>() == key) {
            setting["value"] = value;
            found = true;
            break;
        }
    }

    if (!found) {
        JsonObject newSetting = arr.createNestedObject();
        newSetting["name"] = key;
        newSetting["value"] = value;
    }

    File file = SPIFFS.open("/settings.json", FILE_WRITE);
    if (!file) return false;
    serializeJson(doc, file);
    file.close();
    serializeJson(doc, this->json_settings_string);
    return true;
}


// =======================
// GET SETTINGS STRING
// =======================
String Settings::getSettingsString() {
    return this->json_settings_string;
}

// =======================
// CONVENIENCE GETTERS
// =======================
bool Settings::getBool(const String &key) { return loadSetting<bool>(key); }
int Settings::getInt(const String &key) { return loadSetting<int>(key); }
String Settings::getString(const String &key) { return loadSetting<String>(key); }

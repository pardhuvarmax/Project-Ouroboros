#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H

#include "configs.h"
#include "SPIFFS.h"
#include <FS.h>
#include <ArduinoJson.h>

#define FORMAT_SPIFFS_IF_FAILED true

#ifdef HAS_SCREEN
#include "Display.h"
extern Display display_obj;
#endif

class Settings {
private:
    String json_settings_string;
    StaticJsonDocument<4096> settings_doc;

public:
    // Core methods
    bool begin();
    bool createDefaultSettings(fs::FS &fs, bool spec = false, uint8_t index = 0, String typeStr = "bool", String name = "");
    void printJsonSettings(const String &json_string);
    void main(uint32_t currentTime);
    String getSettingsString();

    // Convenience getters
    bool getBool(const String &key);
    int getInt(const String &key);
    String getString(const String &key);

    // Toggle and type info
    bool toggleSetting(const String &key);
    String getSettingType(const String &key);
    String setting_index_to_name(int i);
    int getNumberSettings();

    // =======================
    // LOAD & SAVE SETTINGS TEMPLATES
    // =======================
    template <typename T>
    T loadSetting(const String &key);

    template <typename T>
    bool saveSetting(const String &key, const T &value);
};

// =======================
// EXPLICIT TEMPLATE SPECIALIZATIONS
// =======================

// LOAD SETTINGS
template <>
bool Settings::loadSetting<bool>(const String &key);

template <>
String Settings::loadSetting<String>(const String &key);

template <>
int Settings::loadSetting<int>(const String &key);

template <>
uint8_t Settings::loadSetting<uint8_t>(const String &key);

// SAVE SETTINGS
template <>
bool Settings::saveSetting<bool>(const String &key, const bool &value);

template <>
bool Settings::saveSetting<String>(const String &key, const String &value);

#endif // SETTINGS_H

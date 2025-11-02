#include "utils.h"
#include "ouis.h"
#include <Arduino.h>
#include <vector>
#include <WiFi.h>
#include <stdlib.h>
#include <string.h>
#include <esp_heap_caps.h>

// DRAM usage
uint8_t getDRAMUsagePercent() {
    size_t free = ESP.getFreeHeap();
    size_t total = ESP.getHeapSize();

    if (total == 0) return 0;

    size_t used = total - free;
    return (used * 100) / total;
}

#ifdef HAS_PSRAM
uint8_t getPSRAMUsagePercent() {
    size_t total = ESP.getPsramSize();
    size_t free = ESP.getFreePsram();

    if (total == 0) return 0;

    size_t used = total - free;
    return (used * 100) / total;
}
#endif

// Convert byte array to hex string
String byteArrayToHexString(const std::vector<uint8_t>& byteArray) {
    String result;
    for (size_t i = 0; i < byteArray.size(); i++) {
        result += "0x";
        if (byteArray[i] < 0x10) result += "0";
        result += String(byteArray[i], HEX);
        if (i < byteArray.size() - 1) result += " ";
    }
    return result;
}

// Convert hex string to byte array
std::vector<uint8_t> hexStringToByteArray(const String& hexString) {
    std::vector<uint8_t> byteArray;
    int startIndex = 0;
    while (startIndex < hexString.length()) {
        int spaceIndex = hexString.indexOf(' ', startIndex);
        if (spaceIndex == -1) spaceIndex = hexString.length();
        String byteString = hexString.substring(startIndex, spaceIndex);
        if (byteString.startsWith("0x") || byteString.startsWith("0X")) {
            uint8_t byte = strtol(byteString.c_str() + 2, nullptr, 16);
            byteArray.push_back(byte);
        }
        startIndex = spaceIndex + 1;
    }
    return byteArray;
}

// Random name generators
void generateRandomName(char *name, size_t length) {
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    name[0] = 'A' + (rand() % 26);
    for (size_t i = 1; i < length - 1; ++i) {
        name[i] = alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    name[length - 1] = '\0';
}

const char* generateRandomName() {
    const char* charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = rand() % 10 + 1;
    char* randomName = (char*)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; ++i) {
        randomName[i] = charset[rand() % strlen(charset)];
    }
    randomName[len] = '\0';
    return randomName;
}

// Random MAC generation
void generateRandomMac(uint8_t* mac) {
    mac[0] = 0x02;
    for (int i = 1; i < 6; i++) {
        mac[i] = random(0, 255);
    }
}

// Convert Station MAC to String
String macToString(const Station& station) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             station.mac[0], station.mac[1], station.mac[2],
             station.mac[3], station.mac[4], station.mac[5]);
    return String(macStr);
}

// Convert uint8_t MAC array to String
String macToString(uint8_t macAddr[6]) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X", 
             macAddr[0], macAddr[1], macAddr[2],
             macAddr[3], macAddr[4], macAddr[5]);
    return String(macStr);
}

// Convert MAC string to uint8_t array
void convertMacStringToUint8(const String& macStr, uint8_t macAddr[6]) {
    if (macStr.length() != 17) {
        Serial.println("Invalid MAC address format");
        return;
    }
    for (int i = 0; i < 6; i++) {
        macAddr[i] = (uint8_t)strtol(macStr.substring(i * 3, i * 3 + 2).c_str(), nullptr, 16);
    }
}

// Get manufacturer from MAC
const char* getManufacturer(const char *addr) {
    static char oui[9];
    strncpy(oui, addr, 8);
    oui[8] = '\0';
    for (int i = 0; i < 8; i++) oui[i] = tolower(oui[i]);

    #define CHECK_OUI(manufacturer, list) \
        for (uint8_t i = 0; i < sizeof(list) / sizeof(list[0]); i++) { \
            char storedOUI[9]; \
            strcpy_P(storedOUI, list[i]); \
            for (int j = 0; j < 8; j++) storedOUI[j] = tolower(storedOUI[j]); \
            if (strcmp(oui, storedOUI) == 0) return manufacturer; \
        }

    CHECK_OUI("Apple", apple_ouis);
    CHECK_OUI("Asus", asus_ouis);
    CHECK_OUI("Belkin", belkin_ouis);
    CHECK_OUI("Cisco", cisco_ouis);
    CHECK_OUI("DLink", dlink_ouis);
    CHECK_OUI("Google", google_ouis);
    CHECK_OUI("Huawei", huawei_ouis);
    CHECK_OUI("LG", lg_ouis);
    CHECK_OUI("Linksys", linksys_ouis);
    CHECK_OUI("Netgear", netgear_ouis);
    CHECK_OUI("OnePlus", oneplus_ouis);
    CHECK_OUI("Samsung", samsung_ouis);
    CHECK_OUI("Sony", sony_ouis);
    CHECK_OUI("TP-Link", tplink_ouis);
    CHECK_OUI("Xiaomi", xiaomi_ouis);

    return "";
}

// Replace OUI with manufacturer name in MAC string
String replaceOUIWithManufacturer(const char *sta_addr) {
    const char *manufacturer = getManufacturer(sta_addr);
    if (manufacturer == nullptr || strlen(manufacturer) == 0) return String(sta_addr);
    const char *mac_suffix = sta_addr + 8;
    return String(manufacturer) + mac_suffix;
}

// IP helpers
IPAddress getNextIP(IPAddress currentIP, IPAddress subnetMask) {
    uint32_t ipInt = (currentIP[0] << 24) | (currentIP[1] << 16) | (currentIP[2] << 8) | currentIP[3];
    uint32_t maskInt = (subnetMask[0] << 24) | (subnetMask[1] << 16) | (subnetMask[2] << 8) | subnetMask[3];
    uint32_t networkBase = ipInt & maskInt;
    uint32_t broadcast = networkBase | ~maskInt;
    uint32_t nextIP = ipInt + 1;

    if (nextIP <= networkBase) nextIP = networkBase + 1;
    if (nextIP >= broadcast) return IPAddress(0, 0, 0, 0);

    return IPAddress(
        (nextIP >> 24) & 0xFF,
        (nextIP >> 16) & 0xFF,
        (nextIP >> 8) & 0xFF,
        nextIP & 0xFF
    );
}

IPAddress getPrevIP(IPAddress currentIP, IPAddress subnetMask, uint16_t stepsBack) {
    uint32_t ipInt = (currentIP[0] << 24) | (currentIP[1] << 16) | (currentIP[2] << 8) | currentIP[3];
    uint32_t maskInt = (subnetMask[0] << 24) | (subnetMask[1] << 16) | (subnetMask[2] << 8) | subnetMask[3];
    uint32_t networkBase = ipInt & maskInt;
    uint32_t prevIP = ipInt - stepsBack;
    if (prevIP <= networkBase) return IPAddress(0, 0, 0, 0);

    return IPAddress(
        (prevIP >> 24) & 0xFF,
        (prevIP >> 16) & 0xFF,
        (prevIP >> 8) & 0xFF,
        prevIP & 0xFF
    );
}

// Next port helper
uint16_t getNextPort(uint16_t port) {
    return port + 1;
}

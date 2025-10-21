# Ouroboros Mini – Firmware Overview & Flow (Updated)

## Overview
The **Ouroboros Mini (OuroMini)** firmware is designed for **rapid deployment in a 15-day experimental build**, optimized for **dual-use wireless security research**, telemetry logging, and **on-device visualization**. This firmware demonstrates **Wi-Fi, BLE, Sub-GHz, RFID/NFC, IR, NRF24, and FM scanning capabilities**.  

**Scope:**
- On-device scanning/security testing of multiple wireless protocols (Wi-Fi, BLE, Sub-GHz, NRF24, IR, RFID/NFC, FM)  
- Real-time visualization on OLED display  
- Local logging to SD card / LittleFS  
- Modular architecture for rapid feature integration and firmware experimentation  
- Experimental features for controlled, authorized environments only  

> ⚠️ **Experimental / Legal Warning:** High-risk features (jamming, deauth, Evil Portal, NFC/RFID writes, BADUSB scripting) **must only be used in controlled, authorized environments**. Ensure compliance with local laws and institutional policies.

---

## Firmware Structure
```
firmware/
│
├── source/
│ ├── .ino # Core loop, setup, and task scheduler
│ ├── modules/ # Protocol modules (Wi-Fi, BLE, Sub-GHz, RFID/NFC, IR, NRF24)
│ ├── libs/ # Custom and third-party libraries (OLED, WS2812, logging)
│ └── config.h # User-configurable constants & feature toggles
│
├── binaries/ # Precompiled firmware binaries (.bin)
└── flashing.md # Flashing instructions for prototype devices
```


---

## Key Modules & Features

| Feature / Module         | Type         | Status  | Notes                                                                                                  |
|--------------------------|-------------|---------|--------------------------------------------------------------------------------------------------------|
| Wi-Fi Scanner            | Defensive   | Stable  | Passive scanning, RSSI mapping, device enumeration, wardriving.                                        |
| Wi-Fi Analyzer           | Defensive   | Stable  | Deep packet inspection, network visualization, top N networks.                                         |
| Deauth / Flood           | Offensive   | Experimental | Targeted or full-channel; limited demo reliability, legal use only.                                   |
| Beacon Spam / Evil Portal| Offensive   | Experimental | Demo purposes only; configurable per target network.                                                 |
| BLE Scanner              | Defensive   | Stable  | Advertising monitoring, RSSI mapping, proximity visualization.                                        |
| BLE Spoofer / Injection  | Offensive   | Low     | Device emulation and basic BLE signal injection; controlled testing only.                             |
| Sub-GHz Capture / Replay | Neutral     | Stable  | Capture & replay of CC1101-compatible devices; TX disabled by default, dual-use depending on config.  |
| Sub-GHz Jammer           | Offensive   | Experimental | Only for controlled demo; PWM/intermittent waveform support.                                         |
| RFID / NFC Scanner       | Defensive   | Stable  | Passive scanning and logging of 125kHz/HF tags.                                                       |
| RFID / NFC Emulation     | Offensive   | Experimental | Writes and emulations; lab demo only.                                                                 |
| IR Capture / Replay      | Neutral     | Stable  | TV, NEC, SIRC, custom IR sequences; for demo visualization.                                           |
| NRF24 Packet Monitor     | Neutral     | Stable  | Mesh and packet inspection; jamming/demo optional.                                                    |
| FM Scan / Broadcast      | Neutral     | Experimental | Limited demo broadcast; regional compliance required.                                                |
| OLED Display UI          | Defensive   | Stable  | Waterfall/spectrum graphs, ghost traces, top device metrics, menu navigation.                         |
| WS2812 LEDs              | Neutral     | Stable  | Status and demo visual effects.                                                                      |
| Data Logging (SD/LittleFS)| Defensive  | Stable  | CSV logging of Wi-Fi/BLE/RF/IR/NFC captures, exportable for offline analysis.                        |
| USB / BADUSB             | Offensive   | Experimental | Keyboard scripting, JS interpreter, OpenHaystack demos.                                             |
| Connectivity / WebUI     | Neutral     | Stable  | Wi-Fi client/AP, WireGuard, TCP/UDP streaming, remote telemetry, Wigle upload.                       |

> **Legend:**  
> - **Defensive:** Passive monitoring, logging, visualization, or alerting features.  
> - **Neutral / Dual-Use:** Can be passive or active depending on configuration.  
> - **Offensive:** Active features for penetration testing, jamming, spoofing, or injection; strictly for controlled demos.

---

## Firmware Flow (High-Level)

1. **Initialization**
   - MCU boots and initializes OLED, SD card, WS2812 LEDs, and serial console.
   - Loads user config from `config.h` or SD card if available.
   - Initializes Wi-Fi, BLE, Sub-GHz, RFID/NFC, IR, NRF24 modules based on config.

2. **Network & RF Interface Setup**
   - Wi-Fi: Station + scan mode, RSSI mapping.
   - BLE: Advertising scanning active.
   - Sub-GHz: Optional capture/replay enabled if shield/module present.
   - RFID/NFC and IR: Passive capture initialized.
   - NRF24: Packet sniffing initialized.

3. **Scanning & Monitoring Loop**
   - Periodic scans for Wi-Fi, BLE, Sub-GHz, RFID/NFC, IR, NRF24.
   - Data buffered in memory for real-time visualization.
   - Optional passive logging to SD card/LittleFS.

4. **Active Features (Dual-Use / Demo)**
   - Offensive modules activated via config/menu: deauth, beacon spam, Evil Portal, BLE injection, Sub-GHz replay/jamming, RFID/NFC write, BADUSB scripts.
   - TX strictly controlled, disabled by default for dual-use safety.

5. **Visualization**
   - OLED: Real-time spectrum/waterfall, ghost traces, top devices, RSSI metrics.
   - WS2812: Status and interactive visual feedback.
   - Push buttons: Menu navigation, feature toggling, demo control.

6. **Error Handling & Recovery**
   - SD card: Retry and serial logging on write failures.
   - OLED: Skip frame on refresh errors, continue scanning.
   - Watchdog timer: Auto-reboot on MCU deadlocks or unresponsive modules.

---

## Development Notes

- Compatible with **Arduino IDE** and ESP32-S3 toolchain.  
- Key libraries: 
  - `WiFi.h` – Wi-Fi scanning & networking  
  - `ESP32 BLE Arduino` – BLE scanning & peripheral simulation  
  - `libs/` – Custom logging, module abstraction, Sub-GHz utilities  
- Precompiled `.bin` files available for rapid flashing.  
- OTA updates optional; recommended for controlled, demo-only environments.

---

## Limitations (Experimental Expo-Focused Build)

- TinyML anomaly detection & auto-healing not implemented.  
- Full multi-protocol jamming is **experimental only**; enable strictly in authorized environments.  
- Sub-GHz, NRF24, RFID/NFC, IR, and FM modules may require hardware shield for full capability.  
- Focused on **visual clarity and modular demo architecture** rather than production-grade stability.

---

## Recommended Flashing Procedure

1. Use **Espressif Flash Download Tool** or Arduino IDE.  
2. Load `.bin` from `binaries/` folder.  
3. Connect ESP32-S3 via USB, enter **Download Mode** (BOOT + RESET sequence).  
4. Set SPI flash offsets per ESP32 module type (0x10000 for main app, 0x8000 for partition table).  
5. Start flashing; verify OLED boot menu, WS2812 status, and SD logging functionality.

---

## Summary

The **Ouroboros Mini firmware** provides a **modular, multi-protocol experimental platform** for rapid demonstration of dual-use wireless security research:

- **Defensive / monitoring features:** Wi-Fi/BLE/Sub-GHz/RFID/NFC/IR passive scanning, logging, visualization.  
- **Neutral / dual-use features:** Replay, packet monitoring, remote telemetry, menu-controlled toggling.  
- **Offensive / demo-only features:** Deauth, beacon spam, Evil Portal, BLE injection, BADUSB, NFC/RFID writes.  

This firmware is **intended for expo demonstration, educational purposes, and controlled research**, with clear **legal and safety boundaries**.

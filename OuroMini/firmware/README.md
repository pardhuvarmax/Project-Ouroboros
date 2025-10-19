# Ouroboros Mini – Firmware Overview & Flow

## Overview
The Ouroboros Mini firmware is designed for rapid deployment in a 15-day experimental build, optimized for on-device wireless defensive and security testing, telemetry logging, and TFT visualization. This firmware prioritizes functional demonstration over full commercial-grade features. The architecture is modular, allowing rapid integration of Wi-Fi, BLE, and optional RF scanning modules.

**Scope:**
- On-device scanning/security testing of Wi-Fi and BLE signals  
- Local logging to SD card  
- Real-time visualization on ILI9341 TFT display  
- Simple modular firmware architecture for rapid development

---

## Firmware Structure

```
firmware/
│
├── source/
│   ├── .ino                       # Core firmware logic (setup, loop, task scheduling)
│   ├── .h & .cpp files            # User-configurable constants and module enables
│   └── libs/                      # Custom and third-party libraries (TFT, Wi-Fi/BLE)
│
├── binaries/               # Precompiled firmware binaries (.bin)
└── flashing.md       # Flashing instructions for prototype devices
```

### Key Modules

| Feature      | Status  | Reliability | Notes                                                                                          |
|--------------|---------|-------------|------------------------------------------------------------------------------------------------|
| Scanner      | Stable  | High        | Reliably scans the 2.4 GHz band to detect active channels and nearby devices. Occasional misses in high‑interference environments. |
| Analyzer     | Stable  | High        | Provides useful insights into detected signals, but additional updates are needed for improved accuracy and detailed analysis. |
| Jammer       | Stable  | High        | Basic jamming works but effectiveness varies by device type and signal strength. Testing on select channels is recommended. |
| BLE Jammer   | Stable  | High        | Disrupts BLE devices inconsistently. Further improvements are needed to ensure stability and effectiveness across BLE variants. |
| BLE Spoofer  | Stable  | Low         | Capable of simulating basic BLE signals but has limited compatibility. Best for controlled testing scenarios. |
| Sour Apple   | Stable  | Low         | Specialized attack method with limited reliability; effective only under specific conditions. Further tuning is required. |

---

## Firmware Flow (High-Level)

1. **Initialization**
   - MCU boots, initializes TFT display, SD card, and serial interface.
   - Loads configuration from `config.h` or SD card if present.

2. **Network Interface Setup**
   - Wi-Fi: Set to station + scan mode.
   - BLE: BLE scanning enabled.

3. **Scanning Loop**
   - Periodic Wi-Fi scan on all channels (1–13).
   - BLE advertising detection continuously active.
   - Optional RF scanning if shield present.

4. **Data Logging**
   - Capture scan results.
   - Write to CSV log file on SD card.
   - Maintain in-memory buffer for real-time TFT visualization.

5. **Visualization**
   - Update TFT display every scan cycle.
   - Display top N networks/devices with RSSI and basic spectrum chart.
   - Menu navigation via push buttons.

6. **Error Handling & Recovery**
   - SD card errors: retry + log to serial.
   - Display refresh errors: skip frame, continue scanning.
   - MCU watchdog enabled for auto-reboot in case of deadlock.

---

## Development Notes

- Firmware is **Arduino IDE compatible**.  
- Libraries used:
  - `TFT_eSPI` – TFT display management  
  - `WiFi.h` – Wi-Fi scanning  
  - `ESP32 BLE Arduino` – BLE scanning  
  - Custom logging utilities in `libs/`  
- For flash-based deployment, `.bin` files are precompiled and ready for USB or SD update.  
- OTA updates are **optional**, for demonstration purposes only.  

---

## Limitations (Expo-Focused Build)

- TinyML anomaly detection and self-healing not implemented.  
- Sub-GHz scanning omitted to prioritize time and stability.  
- Firmware optimized for **demo clarity** over long-term reliability.  

---

## Recommended Flashing Procedure

1. Use Espressif Flash Download Tool or Arduino IDE.  
2. Load `.bin` from `binaries/` folder.  
3. Connect ESP32 via USB, enter Download Mode (BOOT + RESET sequence).  
4. Set SPI flash offset per ESP32 module type (0x10000 for main application, 0x8000 for partition table).  
5. Start flashing; verify TFT boot menu and SD logging functionality after reboot.  

---

## Conclusion

The Ouroboros Mini firmware is engineered for **intense, rapid 15-day deployment**, balancing functional demonstration with code modularity. The architecture provides a clean foundation for iterative enhancements in later versions, such as AI-based anomaly detection, multi-protocol RF monitoring, and full dashboard integration.

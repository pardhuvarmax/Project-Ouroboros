# Ouroboros Mini – System Architecture (Updated)

## Overview
Ouroboros Mini (OuroMini) represents a compact, dual-use embedded system designed for real-time wireless analysis, visualization, and interactive cybersecurity demonstrations. Built under an accelerated 15-day development cycle, the architecture balances modular expandability with hardware efficiency — optimized for research expos, educational demos, and controlled security environments.

Its structure mirrors the core Ouroboros philosophy: the eternal cycle of defense and offense, unified under a single hardware and firmware ecosystem.

## Hardware Architecture

### Mainboard Core
- **ESP32-WROOM-32U (or 32E)** – Central MCU providing Wi-Fi (2.4GHz) and BLE capabilities with U.FL antenna connector for extended range.
- **TP4056** – Li-Ion charge controller with integrated protection (overcharge/overcurrent).
- **LF33 Regulator** – Stable 3.3V LDO powering MCU and modules.
- **CP2102 Interface** – USB-to-UART bridge for debugging, flashing, and USB power input.
- **OLED Display (SSD1306 / SH1106)** – Low-power visualization unit for live telemetry, menus, and signal waterfalls.
- **SD Card Slot (SPI)** – On-device logging of telemetry, configs, signal captures, and replay files.
- **Antenna Connectors (SMA/U.FL)** – External antennas for Wi-Fi, BLE, and Sub-GHz signal optimization.
- **Battery & Power System** – 3.7V Li-Ion cell with on-board charge and protection circuitry.

### Peripheral Expansion
- **CC1101 (Sub-GHz)** – Signal read/replay, spectrum visualization, replay profiles (315/433/868/915 MHz).
- **NRF24L01+** – Mesh/network testing, packet sniffing, and signal interference demos.
- **PN532 / RFID-NFC** – Tag scanning, cloning, and emulation for access system research.
- **IR Transceiver** – Capture/replay for consumer IR devices (NEC, RC5, Samsung, etc.).
- **FM & Audio (Optional)** – Basic frequency scanning and broadcast control for demo visualization.

### Signal Flow
1. **Acquisition:** Radios (Wi-Fi/BLE/Sub-GHz) capture and timestamp raw signal data.
2. **Processing:** MCU filters, classifies, and structures packets for visualization/logging.
3. **Visualization:** OLED renders RSSI bars, live waterfall spectrums, ghost traces, and packet activity.
4. **Storage:** Data logged to SD/LittleFS in structured folders (WiFi, BLE, SubGHz, Logs).
5. **Communication (optional):** Telemetry exported to web dashboard or WireGuard-tunneled relay.

## Firmware Architecture

### Modular Design
| Module | Function | Description |
|--------|-----------|-------------|
| Scanner Core | Acquisition | Cyclic Wi-Fi/BLE/Sub-GHz scanning with adaptive interval control. |
| Analyzer | Processing | Converts raw RSSI data into heatmaps, histograms, and trend buffers. |
| Logger | Storage | Writes logs to SD, timestamps events, and rotates files by protocol type. |
| Display/UI | Visualization | Handles OLED rendering, ghost-trace overlays, orientation, and dim control. |
| Configuration | Management | Centralized in `config.h` or `/config.json` on SD for runtime overrides. |
| Communication | Networking | Web server, WireGuard, Telnet/SSH, ESP-NOW exchange. |
| Defensive Suite | Protection | Passive intrusion detection, beacon pattern deviation alerts, wardriving telemetry. |
| Offensive Suite | Research | Beacon spam, deauth, Evil Portal, BLE spoof, RF replay (disabled by default). |
| Safety Core | Compliance | Watchdog, rate-limiter, and failsafe mode toggles for safe demo use. |

### Execution Flow
```
Boot → Init Hardware → Config Load 
    ↓
Scan Cycle: Wi-Fi / BLE / Sub-GHz
    ↓
Analyze + Log → OLED Render + Ghost Overlay
    ↓
Optional: Send JSON Telemetry → Dashboard
    ↓
Repeat (Adaptive Loop)
```

**Failsafe Layers:**
- Watchdog resets on scan or display timeout.
- SD card I/O errors trigger fallback to serial-only mode.
- Dual-mode toggle (Defensive / Research) enforces demo safety boundary.

## Dashboard & Telemetry Architecture (Optional)
- **Front-End:** HTML/JS-based dashboard visualizes device count, RSSI charts, and frequency heatmaps in real time.
- **Back-End:** Lightweight Python Flask API for receiving telemetry and broadcasting via WebSocket.
- **Transport:** ESP32 sends JSON payloads (Wi-Fi scan, BLE metrics, alerts) over HTTP or WireGuard-secured channel.
- **Integration:** Compatible with Grafana/InfluxDB backends for extended analysis or data archiving.

## Design Considerations
| Aspect | Description |
|--------|-------------|
| Dual-Nature Design | Hardware and firmware inherently support both passive defense and active testing modes, switchable via compile-time or menu configuration. |
| Modularity | Each subsystem (Wi-Fi, BLE, Sub-GHz, UI, Dashboard) is isolated for independent debugging and expansion. |
| Safety by Design | Built-in restrictions and toggles ensure demonstrations stay compliant. |
| Extensibility | Framework supports integration of TinyML models, new RF front-ends, and adaptive learning modules in later versions. |
| Reproducibility | Consistent hardware references, prebuilt `.bin` files, and modular code ensure identical deployment results. |

## Summary
Ouroboros Mini exemplifies a miniaturized yet scalable system architecture capable of demonstrating multi-protocol wireless introspection, on-device telemetry visualization, and ethical attack-defense research.

The design emphasizes:
- **Modularity** – Seamless swapping of radio modules.
- **Transparency** – Clear visual representation of wireless activity.
- **Safety** – Dual-mode architecture preventing misuse.
- **Reproducibility** – Ready-to-flash firmware for rapid expo deployment.

It stands as a proof-of-concept platform showcasing the balance between creation and destruction, defense and offense, and hardware and intelligence — true to the Ouroboros spirit.
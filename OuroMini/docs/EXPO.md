# Ouroboros Mini 15-Day Expo Presentation

## Overview
Ouroboros Mini (OuroMini) is a compact, dual-use experimental wireless monitoring and defense platform, built under an accelerated 15-day development cycle. Designed for research expos, educational demos, and controlled cybersecurity demonstrations, the prototype emphasizes modular expandability, real-time visualization, and interactive engagement over full-scale production features.

It embodies the Ouroboros philosophy: the eternal cycle of defense and offense, unified in a single hardware and firmware ecosystem.

## Project Objective
The primary objective of the Ouroboros Mini is to provide a tangible demonstration of multi-protocol wireless security and telemetry in a highly compressed development timeframe. It highlights:

- Real-time scanning and visualization for Wi-Fi, BLE, and Sub-GHz signals.
- Basic defensive analytics and simple offensive research demonstrations in a safe, expo-ready format.
- Interactive OLED visualization, including RSSI bars, waterfall spectrums, and ghost-trace overlays for audience comprehension.

## Key Highlights
- **Rapid Prototyping:** Complete functional prototype from PCB baseline to operational demo in 15 days.
- **Expo-Ready Visualization:** Interactive OLED display and optional web dashboard for clear audience engagement.
- **Dual-Use Demonstration:** Supports passive defense and controlled research operations, switchable for safety.
- **Simplified Engineering:** Focused on firmware modularity and visualization rather than complex AI/TinyML integration.

## Architecture & Integration
Ouroboros Mini merges hardware, firmware, and visualization into a single cohesive demonstration unit, emphasizing modularity, clarity, and rapid development.

### Main Components
- **ESP32-WROOM-32U/E (16MB):** MCU for wireless scanning, processing, and UI rendering.
- **OLED Display (SSD1306 / SH1106):** Low-power display for real-time telemetry, ghost traces, and menu navigation.
- **SD Card Slot (SPI):** Logging of Wi-Fi, BLE, Sub-GHz data, configuration, and replay files.
- **External Antennas (U.FL/SMA):** Optimized reception for Wi-Fi, BLE, and Sub-GHz.

**Peripheral Modules (Optional):**
- CC1101 (Sub-GHz)
- NRF24L01+ (mesh/network testing)
- PN532 / RFID-NFC (tag scanning & emulation)
- IR transceiver (capture/replay)
- FM/audio visualization

### Firmware Flow
- **Initialization:** Boot, hardware detection, configuration load.
- **Scan Cycle:** Wi-Fi, BLE, and Sub-GHz signal acquisition.
- **Analysis & Logging:** RSSI measurement, basic anomaly detection, and structured logging to SD.
- **Visualization:** OLED renders live bars, waterfall spectrums, and ghost traces.
- **Optional Telemetry:** JSON-formatted data sent to dashboard via HTTP or WireGuard tunnel.
- **Loop:** Adaptive scan → analysis → render → optional telemetry → repeat.

### Safety & Demo Constraints
- Watchdog timers reset on scan/display failures.
- SD card I/O errors fallback to serial-only logging.
- Dual-mode toggle (Defensive / Research) enforces safe demonstration limits.

## Hardware Setup for Expo
The 15-day build focused on **core demonstration hardware** for rapid deployment:
- Fully assembled mainboard with ESP32, OLED, and minimal peripherals.
- Battery connected via TP4056 module.
- External antennas attached for Wi-Fi/BLE demonstration.
- No additional Shield modules integrated to maintain assembly simplicity.

## Firmware & Flashing
- Firmware adapted from a pre-existing prototype `.bin` for fast deployment.
- Modular scanning routines and menu-driven OLED UI for live interaction.
- SD card logging and optional JSON telemetry for visual evidence.
- Flashing performed using **esptool or Arduino IDE**, supporting OTA updates and runtime adjustments.

## Demo Scenario
Audience demonstration workflow:
1. **Power-On:** Device boot sequence on OLED display.
2. **Signal Scan:** Real-time visualization of Wi-Fi, BLE, and Sub-GHz signals.
3. **Interaction:** Buttons or menu navigation to inspect specific channels/protocols.
4. **Event Indication:** Simple visual alerts for rogue APs, interference, or beacon deviations.

This scenario allows audiences to quickly grasp core wireless security principles through tangible, real-time feedback.

## Key Takeaways from 15-Day Build
- **Feasibility:** Rapid condensed development can produce a functional dual-use wireless defense prototype.
- **Team Coordination:** Effective delegation of firmware, PCB assembly, and UI visualization was critical.
- **Rapid Iteration:** Leveraging pre-existing firmware accelerated UI and scan visualization enhancements.
- **Demo Focus:** Audience comprehension prioritized over full technical depth ensured successful exposition.

## Future Directions
Post-expo, Ouroboros Mini can be enhanced by:
- Integrating Shield modules for BLE/Sub-GHz countermeasures.
- Adding TinyML/AI modules for anomaly detection and adaptive scanning.
- Expanding web dashboard for remote monitoring, historical logs, and analytics.
- Supporting additional RF modules and advanced offensive/defensive research tools.

## Conclusion
The Ouroboros Mini 15-Day Expo Build is a **proof-of-concept dual-use wireless security platform**, emphasizing interactive visualization, modular design, and rapid engineering feasibility. It demonstrates how condensed development can effectively showcase multi-protocol monitoring, ethical attack-defense research, and real-time telemetry to audiences in an expo-ready, visually engaging format.
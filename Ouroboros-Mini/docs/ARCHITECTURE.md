# Ouroboros Mini – System Architecture

## Overview
Ouroboros Mini employs a modular embedded system architecture optimized for rapid 15-day experimental development. The design prioritizes clear separation of hardware, firmware, and visualization components to facilitate integration, maintainability, and rapid deployment for expo demonstration purposes.

## Hardware Architecture
**Mainboard Components:**
- **ESP32-U (16MB):** Core MCU providing Wi-Fi and BLE capabilities. Handles scanning, logging, and TFT rendering.
- **TP4056:** Integrated Li-ion battery charger with overcurrent and overcharge protection.
- **LF33:** Voltage regulator ensuring stable 3.3V supply to MCU and peripherals.
- **CP2102:** USB-to-serial interface for firmware flashing and debugging.
- **ILI9341 TFT Display (2.8”):** On-device visualization of telemetry and signal metrics.
- **SD Card Slot:** Local storage for scan logs, telemetry, and demo data.
- **Antenna Connectors:** Optional external antennas for improved Wi-Fi/BLE reception.

**Signal Flow:**
1. Wi-Fi/BLE radios scan environment for nearby devices.
2. Data is logged to SD card and optionally streamed to web dashboard.
3. Metrics are rendered in real-time on TFT display.
4. Optional external dashboard aggregates telemetry for visualization beyond the device.

## Firmware Architecture
**Modules:**
- **Scanner Module:** Periodically scans Wi-Fi channels and BLE advertising packets.
- **Logger Module:** Stores detected device information, RSSI, and timestamp to SD card.
- **Display Module:** Handles TFT rendering, menu navigation, and visual feedback.
- **Configuration Module:** Centralized parameters (`config.h`) for scan intervals, logging, and display settings.
- **Communication Module (Optional):** HTTP POST/GET interface to web dashboard API for telemetry visualization.

**Execution Flow:**
> Initialize Hardware → Scan Wi-Fi/BLE → Log Data → Render TFT → Optional Dashboard Update → Repeat


**Error Handling:**
- Watchdog timers prevent system hangs.
- SD card errors and scan failures trigger safe retry mechanisms.

## Dashboard Architecture (Optional)
- **Front-End:** HTML/CSS/JS visualizes telemetry in graphs, heatmaps, and device tables.
- **Back-End:** Python Flask API serves as lightweight telemetry endpoint.
- **Integration:** ESP32 Mini sends JSON-formatted scan data over Wi-Fi to Flask API in real-time.
- **Design Principle:** Maximize visual clarity for expo presentation with minimal latency.

## Design Considerations
- **Modularity:** Hardware, firmware, and dashboard components are loosely coupled to allow rapid replacement or modification.
- **Scalability:** Although experimental, architecture supports future addition of Sub-GHz monitoring and advanced analytics.
- **Reproducibility:** Standardized firmware flashing procedure ensures consistent demo-ready deployments.

## Summary
Ouroboros Mini demonstrates a clean, modular embedded system architecture for rapid experimental development. It integrates wireless scanning, local visualization, data logging, and optional dashboard telemetry into a compact, expo-ready prototype, emphasizing clarity, maintainability, and demonstrable engineering rigor.

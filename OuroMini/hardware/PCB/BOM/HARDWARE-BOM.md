# Ouroboros Mini – Hardware Bill of Materials (BOM)

## Overview
This document enumerates the essential hardware components for Ouroboros Mini, designed as a rapid, 15-day experimental build for expo demonstration purposes. All listed items are integral to achieving functional wireless scanning, on-device visualization, and local data logging.

---

## Mainboard Components

| Component | Description | Part Number / Notes | Quantity |
|-----------|-------------|-------------------|----------|
| **ESP32-WROOM-32U** | Core microcontroller with integrated Wi-Fi & BLE, U.FL antenna interface | ESP32-WROOM-32U | 1 |
| **LF33** | 3.3V Voltage Regulator for stable MCU operation | LF33 | 1 |
| **TP4056** | Single-cell Li-Ion battery charger module, CC/CV | TP4056 | 1 |
| **CP2102** | USB-to-UART interface for flashing and debugging | CP2102 | 1 |
| **OLED 0.96” White SSD1306** | On-device visualization and menu display | OLED_0.96IN_WHITE_SSD1306 | 1 |
| **NRF24L01 Modules** | 2.4GHz transceivers for scanning/protocol monitoring | NRF24L01_GT24MINI_MS | 3 |
| **SD Card Slot (SPI Mode)** | Storage for logs and scan data | MICRO SD | 1 |
| **Push Buttons** | User input for menu navigation | B1–B7 | 7 |
| **Slide Switch (SPDT)** | Optional device control | SW1 | 1 |
| **Battery** | 3.7V Li-Ion rechargeable cell | BAT | 1 |
| **Antenna Connectors** | External RF antenna interface | ANT1–ANT3 | 3 |
| **SMA Connectors** | RF connector for external antennas | J2–J4 | 3 |
| **USB Type-C Connector** | USB power and data interface | J1 | 1 |

---

## Shield (Optional for Mini)
> Note: For the mini version, the shield may be omitted or partially integrated depending on time constraints.

| Component | Description | Part Number / Notes | Quantity |
|-----------|-------------|-------------------|----------|
| **NRF24 Modules** | 2.4GHz transceivers for scanning/protocol monitoring | NRF24L01_GT24MINI_MS | 0–3 |

---

## Power & Connectivity

| Component | Description | Part Number / Notes | Quantity |
|-----------|-------------|-------------------|----------|
| **Li-ion Battery** | 3.7V rechargeable cell | 18650 or Li-Po | 1 |
| **Battery Connector** | JST connector for Li-ion battery | JST PH 2.0mm | 1 |
| **USB Cable** | For flashing and power | USB-C or micro-USB | 1 |

---

## Optional Visualization & Demo Enhancements

| Component | Description | Notes | Quantity |
|-----------|-------------|-------|----------|
| **External Antenna** | Improves Wi-Fi/BLE scanning range | SMA/U.FL | 1 |
| **SD Card** | MicroSD for logs | FAT32, 8–32GB | 1 |

---

## Notes
1. Components marked as **optional** can be omitted for the 15-day experimental expo build.  
2. Quantity reflects a single Ouroboros Mini prototype. For multiple units, scale linearly.  
3. Ensure OLED display and SD card slot are compatible with ESP32-WROOM-32U SPI interfaces.  
4. Antenna connectors are plug-and-play; no additional soldering is required if modules come pre-mounted.  

---

## Summary
This BOM provides a compact yet functional set of components sufficient to demonstrate wireless scanning, telemetry logging, and on-device visualization for expo purposes. The selection prioritizes rapid assembly, demonstrable functionality, and integration simplicity over full commercial-grade coverage.


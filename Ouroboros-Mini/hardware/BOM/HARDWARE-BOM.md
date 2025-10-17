# Ouroboros Mini – Hardware Bill of Materials (BOM)

## Overview
This document enumerates the essential hardware components for Ouroboros Mini, designed as a rapid, 15-day experimental build for expo demonstration purposes. All listed items are integral to achieving functional wireless scanning, on-device visualization, and local data logging.

---

## Mainboard Components

| Component | Description | Part Number / Notes | Quantity |
|-----------|-------------|-------------------|----------|
| **ESP32-U** | Core microcontroller with integrated Wi-Fi & BLE, 16MB flash | ESP32-U Dev Module | 1 |
| **LF33** | 3.3V Voltage Regulator for stable MCU operation | LF33CV | 1 |
| **TP4056** | Lithium-ion battery charging and protection module | TP4056 | 1 |
| **CP2102** | USB-to-serial interface for flashing and debugging | CP2102 | 1 |
| **PCF8574** | I/O expander for managing buttons and interface | PCF8574 | 1 |
| **SD Card Slot** | FAT32 storage for logs and scan data | Standard microSD holder | 1 |
| **ILI9341 TFT Display (2.8”)** | On-device visualization and menu navigation | ILI9341 SPI | 1 |
| **Push Buttons** | User input for menu navigation | Tactile push buttons | 3–5 |
| **Antenna Connector** | External Wi-Fi/BLE antenna interface | SMA / U.FL | 1–2 |

---

## Shield (Optional for Mini)
> Note: For the mini version, the shield may be omitted or partially integrated depending on time constraints.

| Component | Description | Part Number / Notes | Quantity |
|-----------|-------------|-------------------|----------|
| **NRF24 Modules** | 2.4GHz transceivers for scanning/protocol monitoring | NRF24L01+ | 0–3 |
| **CC1101 Module** | Sub-GHz transceiver for RF scanning | CC1101 | 0–1 |

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
3. Ensure TFT display and SD card slot are compatible with ESP32-U SPI interfaces.  
4. Antenna connectors are plug-and-play; no additional soldering is required if modules come pre-mounted.  

---

## Summary
This BOM provides a compact yet functional set of components sufficient to demonstrate wireless scanning, telemetry logging, and on-device visualization for expo purposes. The selection prioritizes rapid assembly, demonstrable functionality, and integration simplicity over full commercial-grade coverage.

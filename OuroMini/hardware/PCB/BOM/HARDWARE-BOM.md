# Ouroboros Mini – Hardware Bill of Materials (BOM)

## Overview
This document lists the core hardware components for **Ouroboros Mini (OuroMini)** — a rapid, 15-day experimental dual-use build for expo demonstration and research purposes. The hardware enables **wireless scanning across multiple protocols (Wi-Fi, BLE, Sub-GHz, RFID/NFC, IR, NRF24, FM)**, **on-device visualization**, and **local data logging**. All components have been selected for **speed of assembly, demonstrable functionality, and modularity**.

> ⚠️ **Experimental Build:** The OuroMini is not a production device. Some features are dual-use (defensive/research vs offensive) and require careful legal compliance during demonstrations.

---

## Core Microcontroller & Power

| Component | Description | Part Number / Notes | Quantity |
|-----------|-------------|-------------------|----------|
| **ESP32-S3-WROOM-1 NR16R8** | Core MCU with Wi-Fi, BLE, and extended memory; handles all protocol monitoring & display | ESP32-S3-WROOM-1-N16R8 | 1 |
| **TPRT9080-33GJ5** | 3.3V Voltage regulator for MCU stability | TPRT9080-33GJ5 | 1 |
| **LT1963AEQ#PBF** | 5V → 3.3V LDO regulator for peripherals | LT1963AEQ#PBF | 1 |
| **BQ25896RTWT** | Battery charging & power management, single-cell Li-ion | BQ25896RTWT | 1 |
| **Li-ion Battery** | 3.7V rechargeable cell for standalone operation | 18650 / Li-Po | 1 |
| **Battery Connector** | JST PH 2.0mm for battery attachment | JST PH 2.0mm | 1 |

---

## Communication & Protocol Modules

| Component | Description | Notes | Quantity |
|-----------|-------------|-------|----------|
| **E01-2G4M27SX** | 2.4GHz transceiver (BLE/Wi-Fi experimental) | For scanning & protocol testing | 1 |
| **NRF24L01+ Modules** | 2.4GHz mesh & IoT testing | Optional/dual-use | 0–3 |
| **CC1101-compatible Sub-GHz (external)** | RF scanning, replay & demo | Optional add-on for demo | 1 |
| **PN532 RFID/NFC module** | 125 kHz & HF NDEF scanning/emulation | Optional | 1 |
| **TSOP4838 IR sensor** | Infrared capture & replay | Optional | 1 |
| **IR LEDs (IR26-51C/L110/TR8)** | Infrared emission for IR replay & demo | Optional | 8 |
| **FM TX/RX module (optional)** | FM spectrum scanning / demo broadcast | Regional compliance required | 1 |

---

## Display & User Interaction

| Component | Description | Notes | Quantity |
|-----------|-------------|-------|----------|
| **OLED Display (0.96")** | On-device visualization: waterfall, spectrum, ghost traces | SPI interface, high-contrast demo | 1 |
| **WS2812 RGB LEDs** | Status, visual effect, demo indication | Individually addressable | 16 |
| **Push Buttons** | Menu navigation, demo control | SKPMDAE011 / TSA016A2518C | 6 |
| **Slide Switch (SPDT)** | Power or mode selection | 450404015514_SW_SPDT | 1 |

---

## USB & Connectivity

| Component | Description | Notes | Quantity |
|-----------|-------------|-------|----------|
| **USB Type-C 16-pin** | Data & power interface, firmware upload | TYPE-C16PIN | 1 |
| **CP2102 (optional)** | USB-to-UART interface for flashing/debugging | Optional for rapid deploy | 1 |
| **Antenna Connectors** | External Wi-Fi/BLE/Sub-GHz antennas | SMA/U.FL compatible | 3 |

---

## Passive & Storage Components

| Component | Description | Notes | Quantity |
|-----------|-------------|-------|----------|
| **SD Card Slot (SPI)** | Persistent logging of scans, signals, IR/RF/NFC captures | FAT32, 8–32GB recommended | 1 |
| **Capacitors & Resistors** | Decoupling, voltage stability, filtering | Various SMD values (C1–C50, R1–R58) | Multiple |
| **Inductors** | Power conditioning | L1 | 1 |
| **Pull-up/pull-down resistors** | MCU peripheral stability | RN2, RN3 | 2 |

---

## Optional / Experimental Enhancements

| Component | Description | Notes | Quantity |
|-----------|-------------|-------|----------|
| **External Antennas** | Improves RF range (Wi-Fi/BLE/Sub-GHz) | SMA/U.FL | 1–3 |
| **BADUSB / USB scripting** | Automates demos with keyboard injection | Experimental only | n/a |
| **Web Dashboard connectivity** | ESP32-hosted telemetry streaming | Dual-use, visualization | n/a |

---

## Notes

1. **Experimental Build**: Designed for rapid 15-day expo deployment; some features are dual-use and controlled demonstration only.  
2. **Scaling**: Quantities reflect one unit; scale linearly for multiple prototypes.  
3. **Peripheral Modules**: Optional and swappable; can omit NRF24, Sub-GHz, IR, or FM for minimal builds.  
4. **Legal Compliance**: High-risk features like jamming, deauth, Evil Portal, NFC/RFID writes are **for authorized environments only**.  
5. **Integration**: All modules interface via SPI/I2C/UART; verify voltage compatibility and pull-ups/downs before assembly.  

---

## Summary
The new **OuroMini BOM** emphasizes:

- Multi-protocol scanning (Wi-Fi, BLE, Sub-GHz, IR, RFID/NFC, NRF24)  
- On-device interactive visualization (OLED + LEDs)  
- Persistent logging (SD Card / LittleFS)  
- Rapid, modular assembly for expo demonstrations  
- Controlled dual-use for research, educational, and demo purposes  

This BOM ensures a **functional, demonstrable, and legally mindful prototype** ready for high-visibility expo deployment.

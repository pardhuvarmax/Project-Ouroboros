# ![OuroMini Logo](https://github.com/user-attachments/assets/a79a3fb1-4c94-4892-a161-bd44abc40d88)

**Ouroboros Mini (OuroMini)** — *ESP32-based experimental wireless monitoring & security testing platform (headless variant)*
Engineered as a **15-day rapid prototype**, OuroMini focuses on **dual-use** capabilities (defensive monitoring + controlled offensive research) for educational, research and expo demonstrations.
This document is the **headless / ESP32-WROOM-32 only** edition — all features and notes reflect that hardware constraint.

---

## 🔬 Project Objective

1. Deliver a **compact, cross-protocol wireless research platform** focused on capabilities realistically supported by the ESP32-WROOM32: **Wi-Fi (2.4 GHz)** and **Bluetooth Low Energy (BLE)**, plus IR and simple GPIO peripherals where hardware is present.
2. Provide **real-time telemetry & visualization** via a web dashboard and serial/UART (headless device → browser/dashboard on host).
3. Enable **signal capture and export** for offline analysis and demonstration (handshake export, packet logs).
4. Demonstrate **wireless anomaly detection, telemetry visualization, and repeatable expo demo sequences**.
5. Act as a **modular research artifact** (firmware + logging + demo scripts) for teaching and conferences.

---

## ⚠️ Dual-Use & Legal Considerations

![Warning](media/WARNING.svg)

> **Warning:** OuroMini is intended solely for ethical research, education and authorized security testing. Unauthorized use on networks/devices you do not own or have explicit permission to test is illegal. Comply with local wireless regulations (FCC/CE/others). Operators are responsible for lawful use. The project authors disclaim liability for misuse.

---

## ⚙️ Full Feature Set

| Protocol Layer           | Features                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    | Notes                                                                                                                                                   |
| ------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Wi-Fi (2.4 GHz)**      | - Network scanning (active + passive), AP/client enumeration, RSSI mapping<br>- Promiscuous-mode packet capture (2.4 GHz frames) & basic frame logging<br>- WPA handshake capture (exportable for offline cracking workflows)<br>- Targeted 2.4 GHz deauthentication (single & multi-target)<br>- Beacon creation / fake AP (SSID advertise / SSID flood)<br>- Evil Portal (captive-AP + hosted captive web page for demo/credential capture)<br>- Wardriving (scan + time-stamped LittleFS/SD logging)                                                                     | **Headless ESP32-WROOM32 only — NO 5 GHz.** DPI beyond basic frame capture is limited by MCU resources. Use offensive actions only in authorized demos. |
| **Bluetooth (BLE)**      | - BLE scanning (advertisements, RSSI logging) and presence tracking<br>- BLE advertising (beacon / peripheral emulation)<br>- Basic GATT server (simple characteristic read/write demos)                                                                                                                                                                                                                                                                                                                                                                                    | BLE features use the ESP32 BLE stack. Complex OS-level HID injection or advanced MITM is unreliable and platform-dependent.                             |
| **IR / GPIO (optional)** | - IR capture & replay sequences (if IR TX/RX hardware present)<br>- GPIO inputs (kill-switch) and outputs for LED indicators / external triggers                                                                                                                                                                                                                                                                                                                                                                                                                            | Optional per-device hardware. IR active features require an IR transmitter module fitted to the board.                                                  |
| **System / UX / Ops**    | - LittleFS / SD capture logging (timestamped files)<br>- Web dashboard & WebSocket telemetry (hosted on AP/STA by the ESP)<br>- HTTP API / Web CLI endpoints for remote control (headless UI)<br>- OTA firmware update support (HTTP / PlatformIO compatible)<br>- UART / Serial CLI (local console) for interactive use<br>- Thermal sensor readout (internal temp) & runtime reporting<br>- Kill-switch GPIO input (hardware emergency disable handler)<br>- Rate-limiting controls for floods (configurable values)<br>- Timestamped operator/action logging to LittleFS | Headless operation — UI exposed via web dashboard or serial. All features above are implementable on stock WROOM32.                                     |

---

## OuroMini Feature Classification: Defensive, Dual-Use, and Offensive Capabilities

|               Category | Count | Example Features / Notes                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| ---------------------: | ----: | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|          **Defensive** |    12 | Passive monitoring and analysis: <br>- Wi-Fi scanning (passive/active), AP/client enumeration, RSSI mapping<br>- BLE scanning & beacon tracking<br>- Promiscuous frame capture (2.4 GHz) & WPA handshake capture (for offline analysis)<br>- Wardriving + timestamped LittleFS/SD logging<br>- LittleFS/SD logging & operator/action audit trail<br>- Web dashboard & WebSocket telemetry (read/visualize)<br>- Thermal sensor reporting & UART CLI.                                                                                  |
| **Neutral / Dual-Use** |     7 | Passive or active depending on operator intent: <br>- BLE advertising / peripheral emulation (demo uses)<br>- Basic GATT server (demo/control)<br>- Beacon creation / fake AP advertising (gentle demo → aggressive flood)<br>- ESP-NOW send/receive (monitoring vs transmit)<br>- HTTP API / Web CLI control (read vs trigger active modules)<br>- Rate-limiting controls (demo intensity tuning)<br>- OTA / firmware update (maintenance or remote update).                                                                         |
|          **Offensive** |     6 | Active disruption (expo/lab/demo usage only): <br>- Targeted 2.4 GHz deauthentication (single/multi target)<br>- Deauth flood (rate-limited by config)<br>- Beacon spam / fake AP floods (SSID flood)<br>- Evil Portal (captive page for credential capture — demo only)<br>- Active handshake capture (for export and offline cracking workflows)<br>- ESP-initiated ESP-NOW transmissions (control frames) <br>**Note:** These features exist on the WROOM32 and are available for authorized demos. Know local law and expo rules. |

---

## 🛠️ Hardware Architecture

* **MCU:** ESP32-WROOM-32 (single module headless board)
* **Storage:** LittleFS on internal flash; optional microSD for large capture volumes (if socket fitted)
* **I/O (common builds):** UART, SPI, I²C, ADC, GPIOs, optional IR TX/RX pins, kill-switch GPIO header
* **Power:** USB-C / 5V input (depending on carrier board) with basic power regulation and thermal monitoring

> Note: This README targets the *mainboard-only* headless variant. External radios (Sub-GHz, NFC, NRF24) and native USB HID (S2/S3) are **not present** on this variant.

---

## 💻 Firmware Overview

* **Framework:** Arduino-ESP32 (primary) — fast deploy + familiar toolchain. ESP-IDF variants possible for advanced builds.
* **Repository layout (recommended):**

```
firmware/
├── src/         # main.ino, config.h, core modules
├── libs/        # drivers: wifi-utils, ble-utils, ir (if present)
├── modules/     # scanning, capture, evil-portal, deauth, espnow
├── tools/       # export scripts (handshake, logs)
└── binaries/    # precompiled .bin for rapid flashing
```

* **Core functionality:** Wi-Fi/BLE scanning, handshake capture & export, packet logging, LittleFS logging, web dashboard endpoint, thermal reporting.
* **Build / Flash:** PlatformIO / Arduino CLI / Espressif Flash Tool. Provide `ouromini-expo.bin` prebuilt for the expo.

---

## 🌐 Web Dashboard (Headless → Host UI)

Minimal, high-visibility dashboard optimized for expo demos and headless operation:

* Device presence (Wi-Fi / BLE) table
* RSSI graphs (short history)
* Live detection flags & alert log (timestamped)
* Device health (temp, uptime, memory)
* Control endpoints: start/stop scan, trigger demo sequence, fetch logs

```
dashboard/
└── design/    # Figma / static prototypes
```

> The ESP hosts a tiny webapp on captive AP or on STA (if connected).

---

## 📄 Documentation (repo)

* `docs/Abstract.md` — Overview & research rationale
* `docs/Architecture.md` — Hardware & firmware mapping (headless board)
* `docs/Firmware_Flow.md` — Module descriptions & compile flags (expo build notes)
* `docs/Expo_Presentation.md` — Demo scripts, safety scripts, and operator checklist
* `docs/Dashboard_Design.md` — UI flows & API endpoints

---

## 🔧 Safety & Operational Guidelines

* **Operator responsibility:** Only run offensive features in authorized controlled demos. Document consent and locale rules.
* **Expo setup:** Prefer a controlled demo area; inform venue and nearby exhibitors if performing disruptive demos.
* **Kill switch:** Hardware kill switch connected to GPIO should immediately disable radio TX when asserted.
* **Rate limits:** Configure conservative defaults for floods during demos; set operator-controlled intensity.
* **Audit:** All active actions MUST be logged (timestamp + operator ID) to LittleFS for post-demo audit.

---

## 📜 License

**Project Ouroboros** © 2025 **REVA4 Research Initiative**
Licensed under **GNU AGPL-3.0** — use and redistribution under AGPL terms. See `LICENSE` for details.

---

# OuroMini — Dual-Use Experimental Rapid Build (Red Pill)

<img width="1918" height="953" alt="OuroMini" src="https://github.com/user-attachments/assets/085d83fb-c0c3-4fa0-bbd3-94b4ded8f8ed" />

**Ouroboros Mini (OuroMini)** is an **ESP32-based experimental wireless monitoring and security testing platform**. Engineered under a **15-day rapid prototype cycle**, it combines **dual-use capabilities** — both **defensive monitoring** and **controlled offensive research** — for educational, research, and expo demonstration purposes.  

> ⚠️ **Experimental Only:** This build is **not a production system** and should **never be used for unauthorized attacks**. All offensive functions are intended for **research, teaching, and controlled lab environments**.

---

## 🔬 Project Objective

1. Deliver a **compact cross-protocol wireless research platform**: Wi-Fi, BLE, Sub-GHz, IR, RFID/NFC, NRF24, and FM.
2. Provide **real-time visualization** on **OLED display** and optional **LED array indicators**.
3. Enable **signal capture, replay, and controlled jamming** for research and teaching.
4. Demonstrate **wireless anomaly detection, telemetry visualization, and interactive dashboards** in expos and labs.
5. Serve as a **modular research artifact**, showcasing integration between hardware, firmware, and visual analytics.

---

## ⚠️ Dual-Use & Legal Considerations

The platform includes features that can be **illegal or restricted**:

- Signal jamming & replay  
- Wi-Fi deauth/flood attacks  
- BLE spoofing & beacon spam  
- Evil Portal simulations  

**Always operate in a controlled lab or with explicit consent**. Follow **local laws and institutional policies**. Failure to comply may have legal consequences.

---

## ⚙️ Full Feature Set

| Protocol Layer | Features | Notes |
|---|---|---|
| **Sub‑GHz (CC1101)** | - Signal reading & emulation (capture & replay complex remotes)<br>- Spectrum analyzer with graphical visualization<br>- Signal jamming: full/intermittent PWM waveforms<br>- Organized signal storage, replay profiles | CC1101 support for Flipper Zero, LilyGO CC1101, ESP32, M5 devices. Demo/research only; comply with RF regulations. |
| **Wi‑Fi (2.4 / 5 GHz)** | - Network scanning, device enumeration, RSSI mapping<br>- Deauth & flood attacks (including 5GHz via RTL8720DN)<br>- Beacon spam, Evil Portal, WPS attacks<br>- Packet sniffing, deep packet inspection, advanced traffic analysis<br>- Wardriving, host scanning, WireGuard tunneling<br>- Pwnagotchi & Brucegotchi integration | Hardware-dependent (ESP32, RTL8720DN, SDR). Demo & pen-test research; not persistent defense. |
| **Bluetooth (BLE)** | - Advertising monitoring & RSSI mapping<br>- BLE spoofing/emulation (device cloning)<br>- BLE spam (iOS, Android, Windows)<br>- BLE beacon creation & manipulation<br>- Packet interception, BLE keyboard (Cardputer/T-Deck) | Platform-dependent. Focus on research, robustness testing, and educational demos. |
| **RFID / NFC** | - Scan, save, clone, and emulate 125 kHz/HF NDEF tags<br>- Write/erase tags, Amiibo/Chameleon workflows<br>- Tag emulation for access control testing | PN532 & compatible modules. Auditing & lab testing only. |
| **Infrared (IR)** | - Capture & send IR signals (NEC, SIRC, RC5, Samsung, custom sequences)<br>- TV-B-Gone mode for demo<br>- IR database with thousands of remotes | Visual demonstration focus; low legal risk but caution in public areas. |
| **NRF24L01+ / 2.4GHz ISM** | - 2.4GHz communication testing, packet capture & analysis<br>- Mesh network simulation & packet inspection<br>- NRF24 jamming & MouseJack-style demos | Requires NRF24 module; highlights IoT/mesh network security tradeoffs. |
| **FM (optional)** | - Spectrum scan, broadcast control, hijack traffic announcements (demo) | Use only reserved/demo channels. Dependent on regional regulations. |
| **On-Device Display (OLED)** | - Waterfall & spectrum graphs, ghost traces (fading signal history)<br>- Target/device lists, real-time metrics<br>- Brightness, orientation, color accents, boot sound control | Optimized for OLED; high visual impact demos. |
| **Data Storage & Filesystems** | - SD/LittleFS logging: configs, captured signals, IR/RF/RFID files, images, scripts<br>- SD Card & SPIFFS manager, image viewers, BADUSB storage integration | Persistent demo logs; export for offline analysis. |
| **USB / Scripts / BADUSB** | - USB keyboard scripting, JavaScript interpreter, OpenHaystack, iButton, QR Codes, PIX, WebUI support<br>- ESP-NOW send/receive files & commands | Only for demonstration; responsible use mandatory. |
| **Connectivity & Services** | - Wi-Fi client/AP, WireGuard, Telnet/SSH, TCP client/listener, Web server & WebUI, Wigle upload | Remote telemetry & demo control; sandbox for safety. |
| **Config / UI / Misc** | - Configurable UI, boot text, RTC/NTP clock, brightness/dim, sleep/restart<br>- Orientation, UI color, LED control | Polished UX; highlights rapid prototyping design. |
| **Design Intention** | High visual impact, interactive demonstration with cross-device compatibility (Flipper, LilyGO CC1101, ESP32, M5). | Not for continuous network defense; controlled dual-use only. |

---

## 🛠️ Hardware Architecture

- **MCU:** ESP32-S3-WROOM-1 (central processing & wireless control)  
- **Power Management:** TP4056 Li-ion charging, LDO voltage regulators  
- **Visual:** OLED 0.96-1.3” + WS2812 LED array  
- **Storage:** SD Card & LittleFS  
- **Inputs:** Buttons, tactile switches, slide switches, buzzer  
- **Peripheral Modules:** Optional Sub-GHz transceivers, NRF24, IR, CC1101  

> Designed as a **mainboard-only experimental platform** for rapid prototyping; optional modules extend dual-use research capabilities.

---

## 💻 Firmware Overview

- **Framework:** Arduino-ESP32 for fast deployment  
- **Structure:**
```
firmware/
├── src/       # main.ino, config.h
├── libs/      # drivers: Wi-Fi, BLE, Sub-GHz, IR, NFC, NRF24
├── modules/   # offensive/defensive dual-use feature toggles
└── binaries/  # precompiled .bin for rapid flashing
```
- **Core functionality:** Wi-Fi/BLE scanning, anomaly detection, signal capture/replay, SD logging, OLED visualization, minimal WebUI dashboard  
- **Upload:** Arduino IDE or Espressif Flash Download Tool  
- Modular design allows safe **feature toggling** to disable high-risk modules during demos

---

## 🌐 Web Dashboard (Expo-Focused)

- Minimalist dashboard to visualize telemetry:  
  - Device presence (Wi-Fi/BLE)  
  - Signal strength graphs (RSSI)  
  - Detection flags & alert logs  
  - Device status & uptime metrics  

```
dashboard/
├── webapp/    # index.html, dashboard.js, style.css
├── api/       # Python/Flask endpoint for telemetry
└── design/    # Figma/static visual prototypes
```

> Dashboard optimized for **high visibility in expo/lab demos**, not production analytics.

---

## 📄 Documentation

- `docs/Abstract.md` — Overview & research rationale  
- `docs/Architecture.md` — Full hardware/software mapping  
- `docs/Firmware_Flow.md` — Module descriptions & compile flags  
- `docs/Expo_Presentation.md` — Demo instructions & safety scripts  
- `docs/Dashboard_Design.md` — Data visualization & UI layout  

---

## 🔧 Safety & Operational Guidelines

- **Dual-Use:** Compile-time feature flags separate offensive/defensive modules  
- **Lab Isolation:** Use Faraday cages or dedicated RF testing environments  
- **Permission:** Obtain explicit consent before running offensive functions  
- **High-Risk Modules:** Segregate jamming, Evil Portal, BLE spoofing scripts  
- **Demonstration:** Keep visualizations and dashboard active to highlight research/education value

---

## 🧾 License

**MIT License** — Open for research, educational, and controlled demo use. **Not for commercial deployment or unauthorized offensive use.**

# Project Ouroboros – Unified Wireless Security Research
> ⚠️ **Disclaimer:** This project is for **educational, research, and ethical security purposes only**. Misuse of hardware or software is strictly the responsibility of the user.

---

## 🌐 Overview

**Project Ouroboros** is a **modular, dual-use cybersecurity platform** encompassing multiple ESP32-based hardware and firmware modules for **wireless defense, monitoring, and controlled research/offense experiments**.

It is structured as a parent ecosystem:

* **Blue Pill (Passive Development) :** Consumer-friendly, multi-layer defense shield (Wi-Fi, BLE, Sub-GHz) with anomaly detection and automated mitigation.
* **OuroMini:** Rapid-prototype dual-use demo board (15-day expo build) showcasing real-time wireless telemetry, visualization, and ghost traces.

The Ouroboros philosophy: **eternal cycle of attack & defense** — integrating visualization, telemetry, and interactive demos in a single hardware/firmware ecosystem.

---

## 🔹 Core Objectives

* **Defense:** Protect home, personal, and IoT networks from Wi-Fi, BLE, Sub-GHz attacks.
* **Research:** Safe experimentation of offensive tools for learning and controlled testing.
* **Visualization:** Real-time telemetry, ghost traces, waterfall spectrums, and dashboards for expos or lab demos.
* **Rapid Deployment:** Prebuilt `.bin` firmware, modular hardware, and standardized flashing for fast prototyping.
* **Extensibility:** Supports TinyML, AI-assisted anomaly detection, and additional RF front-ends.

---

## 🏗️ Sub-Projects & Modules

### Blue Pill – Defensive Shield

**Purpose:** Consumer-ready Wi-Fi/BLE/Sub-GHz network protection.

**Features:**

* Real-time intrusion detection (deauth, rogue AP, spoofing).
* TinyML anomaly detection for smarter threat recognition.
* Active countermeasures: automated mitigation, reconnection, and hardened configs.
* Spectrum visualization: waterfall graphs on OLED/TFT.
* Logging & optional dashboard telemetry.

**Hardware & Firmware:**

* ESP32-U/WROOM-32E, OLED/TFT, optional Sub-GHz & BLE modules.
* Firmware modularity allows independent updates for each protocol.

**Resources:**

* [Blue Pill Docs](./BluePill/Documentations)

---

### OuroMini – 15-Day Expo Prototype

**Purpose:** Rapid 15-day dual-use prototype for expos & demos.

**Highlights:**

* Real-time scanning: Wi-Fi, BLE, Sub-GHz.
* OLED visualization: RSSI bars, waterfall graphs, ghost-traces.
* Dual-mode toggle: Defensive vs. Research.
* SD card logging and optional dashboard telemetry.

**Hardware:** ESP32 MCU, OLED, minimal peripherals, external antennas.

**Firmware:** Modular scanning, menu-driven UI, safe demo constraints.

**Docs:** 
- [Ouromini Abstract](OuroMini/docs/ABSTRACT.md)
- [OuroMini Expo Documentation](./OuroMini/docs/EXPO.md)  
- [Architecture & Firmware Details](./OuroMini/docs/ARCHITECTURE.md)

---

### Modules

| Module           | Purpose                        | Notes                     |
| ---------------- | ------------------------------ | ------------------------- |
| CC1101 / Sub-GHz | RF monitoring & replay         | 315/433/868/915 MHz bands |
| NRF24L01         | Mesh/network testing           | 2.4 GHz experimentation   |
| PN532 / RFID-NFC | Tag scanning & emulation       | Access control research   |
| IR Transceiver   | Consumer device capture/replay | NEC, RC5, Samsung, etc.   |
| FM / Audio       | Frequency scanning & demo      | Visualization only        |

---

## 🛠️ Hardware Requirements

**Core MCU:**

* ESP32-U / S3 for more RAM and peripherals.

**Optional:**

* OLED / TFT display (visualization & menus)
* External antennas for Wi-Fi/BLE/Sub-GHz
* Shields/modules for advanced research

---

## 💻 Software Stack

**Firmware Base:**

* [ESP-IDF](https://github.com/espressif/esp-idf)
* [Arduino-ESP32](https://github.com/espressif/arduino-esp32)

**Key Libraries:**

* WiFi, BLE, RadioLib (Sub-GHz)
* TensorFlow Lite Micro (TinyML)
* ArduinoJson, LittleFS, ESPAsyncWebServer
* U8g2, TFT_eSPI, LVGL for visualization

**Optional Tools:**

* HackRF / RTL-SDR for advanced RF
* Edge Impulse / TinyML SDKs

---

## 📂 Directory Structure

```
├───.github
├───BluePill
├───RedPill
├───OuroMini
│   ├───dashboard
│   ├───docs
│   ├───firmware
│   ├───graphics
│   ├───hardware
│   ├───media
│   └───tools
└───Docs
```

---

## 📚 Learning & Contribution Roadmap

1. Learn **ESP32 basics** → Wi-Fi, BLE, FreeRTOS.
2. Implement **Wi-Fi monitoring & defense** → deauth, rogue AP detection.
3. Explore **BLE & Sub-GHz experimentation** → spoofing, jamming, replay attacks.
4. Add **visualization & dashboards** → OLED/TFT/ESPAsyncWebServer.
5. Integrate **TinyML / AI models** → anomaly detection for defense.
6. Combine **offensive & defensive modules** → multitasking with FreeRTOS.
7. Extend **Shields & peripherals** → advanced RF and sensor experiments.

---

## 🔗 References

* [Espressif ESP32 Documentation](https://docs.espressif.com)
* [OWASP Wi-Fi Security Guide](https://owasp.org/www-project-wi-fi-security-testing-guide/)
* [NIST Wi-Fi Security Guidelines (SP 800-153)](https://csrc.nist.gov/publications/detail/sp/800-153/final)
* [HackRF Spectrum Analyzer](https://github.com/pavsa/hackrf-spectrum-analyzer)
* [TensorFlow Lite Micro](https://www.tensorflow.org/lite/microcontrollers)
* [Edge Impulse](https://edgeimpulse.com)

---

## 📜 License

**Project Ouroboros** © 2025 
Licensed under **GNU AGPL-3.0** – use, modify, and redistribute under AGPL terms. See [LICENSE](LICENSE).

---

✅ **This README serves as the central hub** for the entire Ouroboros ecosystem: **Blue Pill, Red Pill, OuroMini, Shields, and optional modules**, providing newcomers and contributors with the **complete project overview, architecture, and references**.


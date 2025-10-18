# 🐍 Ouroboros Mini — Experimental Rapid Build

**Project Ouroboros Mini** is an ESP32-based experimental wireless monitoring and defensive/security research platform, engineered for a **high-intensity 15-day development cycle** with focus on **real-time demonstration and expo presentation**. This iteration is **not a fully featured production system**, but a functional proof-of-concept highlighting core wireless security monitoring, basic anomaly detection, and on-device visualization.  

The Mini aims to showcase the capabilities of **wireless intrusion detection**, **cross-protocol monitoring**, and **dashboard-based visualization** within a constrained development period, emphasizing rapid deployment, reproducibility, and demonstrable results.

---

## 🔬 Objective

- Deliver a **compact, deployable Cybersecurity & IoT Network Defense Prototype** using ESP32 with Wi-Fi and BLE capabilities.  
- Provide **visual feedback via TFT display** and a **minimal web dashboard** for demonstration.  
- Emphasize **system integration, signal acquisition, and telemetry visualization** rather than full-scale AI/TinyML processing.  
- Serve as a **research and educational artifact**, illustrating wireless defensive concepts in real-world scenarios.  

---

## ⚙️ Experimental Capabilities

| Protocol Layer | Functionality | Notes |
|----------------|---------------|-------|
| Wi-Fi 2.4 GHz | Scanning, device enumeration, RSSI mapping | Detects beacon floods, rogue APs (demo only) |
| BLE | Advertising monitoring, device presence detection | Minimal anomaly flags; presentation-focused |
| Sub-GHz RF | Basic signal detection and logging | Optional; limited to presence monitoring |
| On-Device Display | ILI9341 TFT visualizations | Real-time RSSI plots and basic metrics |
| Data Storage | SD card logging | Configurations, logs, signal captures for demo |

> Designed for **high visual impact and interactive demonstration**, not persistent network defense or comprehensive security enforcement.

---

## 🛠️ Hardware Architecture

**Core Components:**

- **ESP32-U (16 MB)** — central processing and wireless management MCU  
- **LF33 Voltage Regulator** — ensures stable 3.3V supply  
- **TP4056 Battery Management** — Li-ion protection and charging  
- **CP2102 USB-to-Serial** — flashing, debugging, serial telemetry  
- **ILI9341 TFT Display** — on-device data visualization  
- **SD Card Slot** — persistent log storage  
- **Antenna Connectors** — Wi-Fi/BLE external antennas for enhanced range  

**System Layout:**  
The Mini maintains a **mainboard-only design** for simplicity. Peripheral modules (e.g., external Sub-GHz transceivers) are optional and minimally integrated to maintain rapid development feasibility.

---

## 💻 Firmware Overview

- Built on **Arduino-ESP32** framework for fast prototyping.  
- **Source structure:**  
  ```
  firmware/
    ├── src/         → main.ino, config.h
    ├── libs/        → hardware drivers, TFT, SD card, Wi-Fi/BLE libraries
    └── binaries/    → compiled firmware (.bin) for deployment
  ```  
- **Core functional modules:** Wi-Fi scanning, BLE monitoring, basic anomaly detection, SD logging, TFT visualization.  
- **Upload methods:** Arduino IDE or Espressif Flash Download Tool.  
- Precompiled `.bin` available for rapid deployment.

> Firmware emphasizes **robust interfacing, data integrity, and modularity** for short-term deployment demonstrations.

---

## 🌐 Dashboard

The **Ouroboros Mini Dashboard** is a minimalistic web interface designed to visualize real-time telemetry:

- Device presence graphs (Wi-Fi/BLE)  
- RSSI signal strength plots  
- Detection flags for basic anomalies  
- Device status and uptime metrics  

**Structure:**
```
dashboard/
  ├── design/           → Figma or static prototype for visualization
  ├── webapp/           → index.html, dashboard.js, style.css
  └── api/              → Python endpoint for ESP32 telemetry streaming
```

> Dashboard is optimized for **expo visibility**, not for production analytics or full IoT integration.

---

## 📂 Repository Structure

```
Ouroboros-Mini/
├── docs/                → Abstract, Architecture, Expo Notes
├── hardware/            → Gerbers, Schematics, 3D renders
├── firmware/            → Source, binaries, libraries
├── dashboard/           → Web app and prototype visuals
├── tools/               → Utilities for logging, SD card updates
└── media/               → Photos, renders, and expo videos
```

---

## 📄 Documentation

- **Abstract.md** — Project overview and research rationale  
- **Architecture.md** — Hardware/software architecture for integration  
- **Hardware_BOM.md** — Component specification, suppliers, and cost notes  
- **Firmware_Flow.md** — Module-level firmware description  
- **Dashboard_Design.md** — Data visualization methodology and UI design  
- **Expo_Presentation.md** — Deployment instructions and demonstration scripts  

---

## ⚠️ Notes

- **Experimental Build:** Fully functional for demonstration, but **limited in scope**.  
- **Time-Constrained:** Developed under a **15-day intensive schedule** for expo showcase.  
- **No AI or TinyML** — proof-of-concept monitoring only.  
- **Open-Ended:** Suitable for research, prototyping, and educational purposes.  

---

## 🧾 License

**MIT License** — Open for research, educational use, and demonstration. Not intended for commercial deployment.

# Ouroboros Mini 15-Day Expo Presentation

## Overview
The Ouroboros Mini is a highly condensed, experimental wireless defense suite built on the ESP32 platform, designed and executed in an intense 15-day period specifically for exposition and demonstration purposes. Unlike full-scale production models, this version prioritizes **speed of implementation, visual clarity, and demonstrable functionality** over complete feature coverage. This presentation documents the technical workflow, hardware/software integration, and insights from rapid prototyping.

---

## Project Objective
The primary goal of the Ouroboros Mini was to produce a **functional, demonstrable wireless defense device** capable of illustrating key offensive and defensive mechanisms in Wi-Fi, BLE, and Sub-GHz domains. Given the 15-day timeframe, the project focused on showcasing **proof-of-concept functionalities** such as signal detection, basic anomaly indication, and a simple TFT visual interface.

### Key Highlights
- **Rapid Prototyping:** The system was designed and implemented from PCB and firmware baseline to operational demo in 15 days.
- **Expo-Ready Demonstration:** Simplified interaction with real-time signal visualization on TFT display for audience comprehension.
- **Lightweight Engineering:** Avoided complex AI/TinyML implementations; concentrated on robust, functional firmware and user interface.

---

## Architecture & Integration
The device architecture merges hardware and firmware into a **single cohesive demonstration unit**, emphasizing modularity for rapid development.

### Main Components
- **ESP32-U MCU (16MB):** Central processing for wireless monitoring and UI rendering.
- **TFT Display (ILI9341, 2.8 inch):** Provides real-time visualization of Wi-Fi, BLE, and Sub-GHz signals.
- **Push Buttons & PCF8574 I/O Expander:** Allows menu navigation and device interaction.
- **External Antenna Connectors:** For Wi-Fi and BLE signal reception.

### Firmware Flow
- **Real-Time Scanning:** Scans Wi-Fi channels 1–13, BLE advertisements, and Sub-GHz activity.
- **Signal Logging:** Stores minimal logs on SD card to demonstrate packet capture.
- **User Interface:** TFT display visualizes channel RSSI levels and active signals.
- **Simplified Countermeasures:** Visual indicators for deauth detection and rogue AP detection.

---

## Hardware Setup for Expo
While the full PCBA supports extensive offensive/defensive operations, the mini version was reduced to **core demonstration hardware**:
- Fully assembled Main Board with TFT display, push buttons, and ESP32.
- Battery connected to TP4056 module.
- External antennas attached for Wi-Fi/BLE demonstration.

**Note:** No Shield modules were integrated in this 15-day build to maintain simplicity and reduce assembly complexity.

---

## Firmware & Flashing
The firmware was adapted from a pre-existing prototype `.bin` to save time. It incorporates:
- Modular scanning routines.
- Simplified menu-driven UI for real-time demonstration.
- SD card logging for visual evidence.

Flashing to the device was performed using **esptool** or Arduino IDE, ensuring **OTA updates and SD card loading** are possible for live demonstration adjustments.

---

## Demo Scenario
For the expo, the following workflow is presented to the audience:
1. **Power-On:** Device initializes and shows boot sequence on TFT.
2. **Signal Scan:** Wi-Fi, BLE, and Sub-GHz signals appear in graphical form.
3. **Interaction:** Users press buttons to view specific channels or protocols.
4. **Event Indication:** Device highlights rogue APs or interference patterns with simple visual alerts.

This workflow allows the audience to quickly grasp **core cybersecurity functionalities** in a tangible, visual manner.

---

## Key Takeaways from 15-Day Build
- **Feasibility:** Complex wireless defense mechanisms can be condensed into a functional expo demonstration without fully implementing all modules.
- **Team Coordination:** Delegation of firmware, PCB management, and assembly tasks was critical under extreme time constraints.
- **Rapid Iteration:** Pre-existing firmware prototype accelerated development by focusing on UI and signal visualization enhancements.
- **Demonstration Focus:** Prioritizing audience comprehension over complete technical depth ensured the project met expo objectives successfully.

---

## Future Directions
Post-expo, the Ouroboros Mini can evolve into a more complete version by:
- Integrating Shield modules for BLE/Sub-GHz countermeasures.
- Adding lightweight AI/TinyML models for anomaly detection.
- Expanding web dashboard functionalities for remote monitoring.

---

**Conclusion:**
The Ouroboros Mini 15-Day Expo Build serves as a **proof-of-concept and demonstration platform**, highlighting core wireless security monitoring capabilities in a visually engaging and technically sound format. This intense prototype underscores **rapid engineering feasibility, modular firmware deployment, and effective demonstration strategy** in extremely limited timelines.
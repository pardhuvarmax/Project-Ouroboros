# Ouroboros Mini – Abstract

## Project Overview
Ouroboros Mini is a compact, high-intensity experimental prototype designed to demonstrate foundational concepts in wireless network monitoring, telemetry, and on-device visualization. Developed within a strict 15-day timeframe for expo demonstration purposes, this build prioritizes rapid deployment and visual impact over full-scale commercial-grade functionality.

## Objective
The primary objective of Ouroboros Mini is to present an interactive embedded system capable of detecting and visualizing Wi-Fi and BLE devices within its operational environment. The system serves as a tangible educational tool, allowing users to observe real-time spectrum activity, device presence, and signal metrics through a TFT display and optional web dashboard.

## Scope & Limitations
- No AI or TinyML-based anomaly detection is included due to time constraints.  
- Sub-GHz coverage and advanced mitigation features are minimal or omitted.  
- The build is intended strictly for expo demonstration and experimental research purposes, not for consumer deployment or commercial use.

## Technical Highlights
- **Embedded MCU:** ESP32-U (16MB) provides integrated Wi-Fi and BLE capabilities.  
- **On-Device Visualization:** 2.8-inch TFT display renders live telemetry, scanning results, and signal metrics.  
- **Data Logging:** SD card integration allows storage of captured device information and scan history.  
- **Rapid Firmware Deployment:** Pre-compiled `.bin` firmware enables quick flashing and reproducible demonstration.  
- **Dashboard Integration:** Optional lightweight web interface for visualizing real-time metrics beyond the device screen.

## Impact
Ouroboros Mini exemplifies a rapid-development, research-oriented approach to embedded wireless defense engineering. It provides an accessible platform for demonstrating spectrum monitoring and telemetry analysis in a visually engaging, expo-ready format.

**Note:** This project is experimental, focusing on proof-of-concept demonstrations rather than full-feature production. It reflects an intense, accelerated engineering effort within a limited timeframe.

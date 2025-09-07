<img width="1794" height="835" alt="Screenshot 2025-09-06 215240" src="https://github.com/user-attachments/assets/25e70f40-4bfa-4453-8d07-8d3e017d1424" />

---
> ⚠️ Disclaimer: This project is for educational and defensive security research purposes only.  
> The authors are not responsible for any misuse of the software or hardware.
---

# Project Ouroboros Blue Pill

**Project Ouroboros Blue Pill** is a wireless defense suite built on the ESP32 platform, designed to protect Wi-Fi, BLE, Sub-GHz, and RF-enabled IoT networks against real-world attacks.  
Unlike single-purpose shields, Blue Pill acts as a multi-layer defense system with detection, prevention, visualization, and self-healing capabilities.

- Real-time intrusion detection for Wi-Fi deauth, jamming, spoofing, rogue access points, BLE exploits, and Sub-GHz threats.  
- Lightweight AI/TinyML anomaly analysis to distinguish legitimate traffic from attacks.  
- Active countermeasures such as automated mitigation, hardened reconnections, and rogue AP identification.  
- **Spectrum analysis with waterfall visualization** (SDR/ESP32-based) to monitor RF activity across multiple bands.  
- Self-healing functions that re-establish secure connections and strengthen configurations after disruption.  
- Cross-protocol coverage beyond Wi-Fi, extending into BLE and Sub-GHz IoT/remote systems.  

The Blue Pill is intended as an affordable, consumer-ready shield for personal, home, and IoT network protection — while remaining fully open for researchers and developers to extend.  

---

## 🚀 Key Features
### Wi-Fi Security
- Detects and mitigates deauthentication & disassociation attacks.  
- Identifies rogue access points and beacon floods.  
- Monitors channel interference and spoofing attempts.  

### BLE Security
- Detects spoofing, jamming, and advertising spam.  
- Monitors nearby devices for anomalies.  

### Sub-GHz & RF Defense (433MHz, 868MHz, 915MHz, Zigbee, RF remotes)
- Detects replay and jamming signals.  
- Monitors for unusual RF activity.  
- Supports modular RF transceivers for extended coverage.  

### Advanced Capabilities
- **Waterfall Spectrum Analysis (2.4 GHz, Wi-Fi Channels 1–13):**  
  The ESP32 continuously scans all 2.4 GHz Wi-Fi channels, recording RSSI levels per channel to visualize interference, jamming, and rogue AP activity.  
  *(Channel support may vary: 1–11 in US, 1–13 in EU & India (Channel 14 ~ Not Allowed In India), 1–14 in JP — channel 14 limited.)*
- TinyML-based anomaly detection for smarter threat classification.
- Self-healing: automatic reconnection and adaptive security hardening.
- Logging and visualization (dashboard support planned).

---

## 🛠️ Hardware Requirements

**Core MCU**  
- ESP32 (recommended: ESP32-WROOM, ESP32-S3 for more resources)  

**Optional Modules**  
- External Wi-Fi antenna for extended range and better RSSI-based spectrum analysis.
- Sub-GHz transceiver (CC1101 / NRF24L01 depending on use case)  
- OLED or TFT touchscreen (for standalone UI with waterfall graphing)  

---

## 💻 Software Stack

**Firmware Base**  
- [ESP-IDF](https://github.com/espressif/esp-idf) – official framework (production-grade)  
- [Arduino-ESP32](https://github.com/espressif/arduino-esp32) – easier prototyping  

**Key Libraries & Dependencies**  
- [WiFi.h](https://www.arduino.cc/en/Reference/WiFi) / ESP-IDF Wi-Fi APIs – scanning & monitoring  
- [ESP32 BLE Arduino](https://github.com/nkolban/ESP32_BLE_Arduino) – BLE scanning/monitoring  
- [RadioLib](https://github.com/jgromes/RadioLib) – Sub-GHz RF transceivers  
- [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers) – TinyML anomaly detection  
- [ArduinoJson](https://arduinojson.org/) – configs, logs, API handling  
- [LittleFS](https://github.com/lorol/LITTLEFS) – filesystem storage  
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) – optional web dashboard  
- [U8g2](https://github.com/olikraus/u8g2) – OLED display driver  
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) – TFT display + spectrum visualizations  

---

## 📚 Required Knowledge
To understand, modify, or extend **Project Ouroboros Blue Pill**, familiarity with the following is recommended:  

- **Embedded Systems** → ESP32 programming with Arduino IDE or ESP-IDF  
- **Networking Basics** → Wi-Fi protocols, deauthentication, rogue AP concepts  
- **Bluetooth Low Energy (BLE)** → Advertising, connections, spoofing vulnerabilities  
- **Sub-GHz Systems** → IoT communication, RF jamming & replay concepts  
- **Spectrum Analysis** → Understanding waterfall graphs and RF signal behavior  
- **AI/ML Basics** → TinyML model training for anomaly detection  
- **Security Concepts** → Attack vectors vs. defense mechanisms in wireless security  

---

## 📘 Critical Firmware Programming Resources

### Core ESP32 Development
- [ESP-IDF (official SDK)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)  
- [Arduino-ESP32](https://github.com/espressif/arduino-esp32)  
- [ESP32 Technical Reference Manuals](https://www.espressif.com/en/support/download/documents)  

### Wi-Fi (Scanning, Monitoring, Deauth Defense)
- [ESP-IDF Wi-Fi Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html)  
- [ESP32 Wi-Fi Sniffer Example](https://github.com/espressif/esp-idf/tree/master/examples/wifi/sniffer)  

### Bluetooth Low Energy (BLE)
- [ESP32 BLE Arduino](https://github.com/nkolban/ESP32_BLE_Arduino)  
- [ESP-IDF BLE GAP Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/bluetooth/esp_gap_ble.html)  

### Sub-GHz / RF Integration
- [RadioLib](https://github.com/jgromes/RadioLib) – multi-protocol RF library  
- [NRF24L01 ESP32 Tutorial](https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/)  

### TinyML / Anomaly Detection
- [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)  
- [Arduino + TinyML Hello World](https://www.arduino.cc/pro/tutorials/ai/ml-kit-hello-world)  
- [Edge Impulse](https://edgeimpulse.com/) – no-code TinyML model training  

### Dashboards & Visualization
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)  
- [ArduinoJson](https://arduinojson.org/)  
- [U8g2](https://github.com/olikraus/u8g2)  
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) – spectrum/waterfall visualization  

---

## 🔗 References

### Core Documentation
- [Espressif ESP32 Documentation](https://docs.espressif.com)  

### Wireless Security & Defense
- [OWASP: Wifi Security](https://owasp.org/www-project-wi-fi-security-testing-guide/)  
- [NIST Wi-Fi Security Guidelines (SP 800-153)](https://csrc.nist.gov/publications/detail/sp/800-153/final)  

### 2.4 GHz Wi-Fi Channels
- **Nordic Semiconductor Wi-Fi Regulatory Support**  
  Provides insights into the 2.4 GHz channel support in Nordic Semiconductor's nRF70 Series devices, detailing the supported channels and their frequencies.
  - [Wifi Regulatory Information](https://docs.nordicsemi.com/bundle/ncs-2.9.2/page/nrf/protocols/wifi/regulatory_support.html)
- **Frequency Bands in Wi-Fi Networks (tbhaxor Blog)**  
  Explains the fundamentals of Wi-Fi frequency bands, including the 2.4 GHz band, and regulatory channel allocations.
  - [Frequency Bands](https://tbhaxor.com/frequency-bands-in-wifi/)

###  Waterfall Spectrum Analysis
- **HackRF Spectrum Analyzer (pavsa GitHub Repository)**  
  Project demonstrating spectrum analysis using HackRF with waterfall plots and frequency allocation insights.  
  - [HackRF Spectrum Analyzer](https://github.com/pavsa/hackrf-spectrum-analyzer)
- **WiFiAnalyzer (VREMSoftwareDevelopment GitHub Repository)**  
  Android Wi-Fi analysis app illustrating spectrum scanning and signal visualization techniques.  
  - [WiFiAnalyzer](https://github.com/VREMSoftwareDevelopment/WiFiAnalyzer)

### Additional Learning
- [TinyML Official Book (O’Reilly)](https://www.oreilly.com/library/view/tinyml/9781492052036/)  
- [Black Hat Wireless Attacks Training Materials (archived)](https://www.blackhat.com/html/archives.html)  
- [Wi-Fi Alliance Security Resources](https://www.wi-fi.org/discover-wi-fi/security)  

---

## Inspiration & Gratitude. 

The work of **ESP32-DIV** by [CiferTech](https://github.com/cifertech) has had a profound impact on my journey into cybersecurity and embedded hardware development. Their innovative approach to ESP32-based wireless systems opened my eyes to the possibilities of building low-cost, practical defense tools and experimenting with IoT security in a hands-on way. Studying their repository not only taught me technical techniques, but also inspired a mindset of creativity, persistence, and problem-solving that has fundamentally shaped the way I approach projects today. Without their work, Project Ouroboros Blue Pill — and my deep interest in bridging hardware with cybersecurity & the path I’ve chosen — wouldn’t have been possible. 
 
*"Ideas find and claim us; we are merely their vessels, not their architects."* ~ **CiferTech**

Repository: [ESP32-DIV](https://github.com/cifertech/ESP32-DIV/tree/main)

---

## LICENSE

Project Ouroboros (Blue Pill)
Copyright (C) 2025 PardhuVarma

Licensed under the GNU Affero General Public License v3.0
See [LICENSE](LICENSE) file for full license text.





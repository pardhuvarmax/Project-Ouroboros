# Dashboard Documentation for Ouroboros Mini

## Overview
The Ouroboros Mini Dashboard provides a real-time visualization interface for metrics collected by the device. It is designed for exhibition, quick monitoring, and light analysis of wireless network events without the need for the onboard TFT screen.

This dashboard is intended as an experimental, high-impact visualization tool for presentation purposes. It does not include advanced AI-based analytics or anomaly detection present in the full-scale Project Ouroboros Blue Pill.

---

## Structure
```
dashboard/
 ├─ design/
 │   └─ figma_prototype.png
 └─ webapp/
     ├─ index.html
     ├─ style.css
     ├─ dashboard.js
     └─ api/
         └─ data_endpoint.py
```

### design/
- **figma_prototype.png**: Prototype of the dashboard layout designed in Figma for reference.

### webapp/
- **index.html**: Main HTML structure of the dashboard.
- **style.css**: CSS for styling the dashboard.
- **dashboard.js**: JavaScript logic for updating and visualizing data.
- **api/data_endpoint.py**: Python backend API that exposes metrics collected from the Ouroboros Mini.

---

## Features
- **Live Metrics Display**: Visualizes Wi-Fi, BLE, and Sub-GHz activity in real-time.
- **Graphs and Charts**: Uses line charts, bar charts, and tables to provide a clear representation of network events.
- **Lightweight and Portable**: Can run on a local server or laptop connected to the Ouroboros Mini.
- **Expo Ready**: Designed for quick demonstration during exhibitions.

---

## Setup Instructions

### 1. API Setup
1. Ensure Python 3.x is installed.
2. Navigate to `dashboard/webapp/api/`.
3. Install required packages (example):
```bash
pip install flask flask_cors
```
4. Run the API server:
```bash
python data_endpoint.py
```

### 2. Frontend Setup
1. Open `index.html` in a browser.
2. Ensure the API endpoint URL in `dashboard.js` points to your running `data_endpoint.py` server.

### 3. Connecting Ouroboros Mini
- The device should be running firmware capable of sending metrics to the API endpoint (via Wi-Fi or USB connection).
- The dashboard will poll the API and update graphs accordingly.

---

## Notes
- This dashboard is **experimental** and intended for **expo presentation purposes**.
- Advanced features like AI-driven anomaly detection, spectrum heatmaps, or automated threat analysis are **not included** in this version.
- Layout and style can be further refined based on the Figma prototype.

---

## Contribution
- Frontend enhancements: update `style.css` and `dashboard.js`.
- Backend enhancements: extend `data_endpoint.py` to include new metrics.
- Any changes should maintain **expo-ready lightweight performance**.

---

## References
- Figma prototype design file: `dashboard/design/figma_prototype.png`
- Sample metrics from Ouroboros Mini firmware for API consumption.

#include "Globals.h"
#include "WebInterface.h"

// ===============================
// Global object definitions
// ===============================

// Core WiFi scanning lists
LinkedList<Station> stations;             // Runtime list of detected stations
LinkedList<WebAccessPoint> accessPoints;  // Access point list
LinkedList<WebProbeReqSsid> probes;       // Probe request list
LinkedList<WebStation> webStations;       // Web station list (used by CommandLine)

// Web interface instance
WebInterface webIF;

// Version strings
const char* version_number = "ESP32 OuroMini v1.0.0";
const char* cmd_version_number = "ESP32 OuroMini CMD v1.0.0";

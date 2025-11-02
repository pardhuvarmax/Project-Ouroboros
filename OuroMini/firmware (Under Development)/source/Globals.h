#pragma once
#include <LinkedList.h>
#include "WebAccessPoint.h"
#include "WebProbeReqSsid.h"
#include "WiFiScan.h"  // defines Station struct

// ===============================
// Global object declarations
// ===============================

// WiFi and probe lists
extern LinkedList<WebAccessPoint> accessPoints;
extern LinkedList<Station> stations;             // runtime struct used by WiFiScan
extern LinkedList<WebProbeReqSsid> probes;

// Optional station tracking (used by Web/CLI)
class WebStation;
extern LinkedList<WebStation> webStations;

// Web interface
class WebInterface;
extern WebInterface webIF;

// Version info
extern const char* version_number;
extern const char* cmd_version_number;

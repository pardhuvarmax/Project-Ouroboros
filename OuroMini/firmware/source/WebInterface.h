#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <Arduino.h>
#include <LinkedList.h>
#include <functional>

#include "WebStation.h"
#include "WebAccessPoint.h"
#include "WebProbeReqSsid.h"

class AsyncWebServer;
class AsyncWebSocket;

class WebInterface {
public:
    WebInterface();
    ~WebInterface();

    bool begin(const char* apName);
    void updateClients();  // pushes live updates to all connected clients

    // Linked lists populated by main firmware
    LinkedList<WebAccessPoint> *access_points = nullptr;
    LinkedList<WebStation> *WebStations = nullptr;
    LinkedList<WebProbeReqSsid> *probe_req_ssids = nullptr;

    // Callback the firmware can register to receive commands from web UI.
    // Example in setup():
    //   webIF.onCommand = [](const String &c){ enqueueWebCommand(c); };
    std::function<void(const String&)> onCommand = nullptr;

    // Push a single terminal line to all connected web clients (sent as JSON { "term": "..." })
    void pushTerminalLine(const String &line);

    // Make macToString public so it can be used by main firmware
    String macToString(const uint8_t *mac);

private:
    AsyncWebServer *webServer = nullptr;
    AsyncWebSocket *ws = nullptr;

    String serializeAPs();
    String serializeStations();
    String serializeProbeReqSSIDs();

    WebStation convertStation(const WebStation &sRaw);
    WebProbeReqSsid convertProbe(const WebProbeReqSsid &pRaw);
};

#endif // WEBINTERFACE_H

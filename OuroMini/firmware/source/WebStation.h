#ifndef STATION_H
#define STATION_H

#include <Arduino.h>

class WebStation {
public:
    String mac;
    int rssi = 0;
    bool selected = false;
    String ap;
    int packets = 0;

    WebStation() : mac(""), rssi(0), selected(false), ap(""), packets(0) {}
    WebStation(const String &m) : mac(m), rssi(0), selected(false), ap(""), packets(0) {}
};

#endif // WEBSTATION_H

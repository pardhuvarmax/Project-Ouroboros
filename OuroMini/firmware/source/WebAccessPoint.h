#ifndef WEBACCESSPOINT_H
#define WEBACCESSPOINT_H

#include <Arduino.h>

class WebAccessPoint {
public:
    String ssid;
    uint8_t channel;
    bool hidden;
    bool selected;
    int rssi;
    uint32_t timestamp;
    String mac;
    String encryption;

    WebAccessPoint()
        : ssid(""), channel(1), hidden(false), selected(false),
          rssi(-100), timestamp(0), mac(""), encryption("Unknown") {}

    WebAccessPoint(const String &s, uint8_t ch, bool isHidden, bool sel,
                   int r, uint32_t ts, const String &m, const String &enc)
        : ssid(s), channel(ch), hidden(isHidden), selected(sel),
          rssi(r), timestamp(ts), mac(m), encryption(enc) {}

    WebAccessPoint(const String &s, uint8_t ch, bool isHidden, bool sel,
                   int r, const String &m, const String &enc)
        : ssid(s), channel(ch), hidden(isHidden), selected(sel),
          rssi(r), timestamp(millis()), mac(m), encryption(enc) {}
};

#endif // WEBACCESSPOINT_H

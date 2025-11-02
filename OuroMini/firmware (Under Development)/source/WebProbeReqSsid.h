#ifndef WEBPROBEREQSSID_H
#define WEBPROBEREQSSID_H

#include <Arduino.h>

class WebProbeReqSsid {
public:
    String ssid;
    int requests = 0;

    WebProbeReqSsid() : ssid("") {}
    WebProbeReqSsid(const String &s) : ssid(s) {}
};

#endif // WEBPROBEREQSSID_H

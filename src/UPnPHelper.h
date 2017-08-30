#ifndef UPNPHELPER_H_
#define UPNPHELPER_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class UPnPHelper {
  private:
    // UDP connection for multicast and response to SSDP
    WiFiUDP UDP;

  public:
    UPnPHelper();
    ~UPnPHelper();
    bool Start();
    bool Read();
    void Respond();
};

#endif

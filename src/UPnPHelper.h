/////////////////////////////////////////////////////
//                    UPnPHelper.h                 //
/////////////////////////////////////////////////////
//                       Notes                     //
/////////////////////////////////////////////////////
//                     License                     //
// GNU Public License 3.0                          //
/////////////////////////////////////////////////////
#ifndef UPNPHELPER_H_
#define UPNPHELPER_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Provides an interface to UDP resources and methods to respond to UPnP
// searches and requests
class UPnPHelper {
  private:
    // UDP connection for multicast and response to SSDP
    WiFiUDP UDP;
    // The response to be sent out after M-SEARCH requests
    String response_packet;

  public:
    UPnPHelper();
    ~UPnPHelper();
    bool Start(const String &response);
    bool Read();
    void AwaitSearch();
    void Respond();
};

#endif

/////////////////////////////////////////////////////
//                   UPnPHelper.cpp                //
/////////////////////////////////////////////////////
//                       Notes                     //
// Provides resources for UPnP message             //
// and receiving on an Arduino using the WiFi      //
// libraries. Specifically, responds to M-Search   //
// packets with a message determined in the        //
// main Arduino sketch.                            //
//                                                 //
// Would like to remove dependency on "String"     //
/////////////////////////////////////////////////////
//                     License                     //
// GNU Public License 3.0                          //
/////////////////////////////////////////////////////
#include "UPnPHelper.h"

// UPnP multicast address
const IPAddress addr(239, 255, 255, 250);
// UPnP Port
const unsigned int port = 1900;
// Buffer for received packets
char in_packet[255];

// Constructor
UPnPHelper::UPnPHelper() { }

// Destructor
UPnPHelper::~UPnPHelper() { }

// Starts the UDP server
// Accepts the response packet to be sent to the searching device
bool UPnPHelper::Start(const String &response) {
  response_packet = response;
  // Attempt to multicast on the uPnP channel
  if(UDP.beginMulticast(WiFi.localIP(), addr, port)) {
    // If successful return true
    return true;
  }
  return false;
}

// Read incoming packets
bool UPnPHelper::Read() {
  int packet_size = UDP.parsePacket();
  // If data in the packet, read and return
  if (packet_size)
  {
    // Read the packet into the character array
    int len = UDP.read(in_packet, 255);
    if (len > 0)
    {
      in_packet[len] = 0;
      return true;
    }
  }
  return false;
}

// Await an M-SEARCH packet, and respond if search meets criteria
void UPnPHelper::AwaitSearch() {
  if(Read()) {
    // Put packet contents in string
    String packet_content = String((char *)in_packet);
    // If the packet is an M-SEARCH packet, respond
    if(packet_content.indexOf('M-SEARCH') > 0) {
      Respond();
    }
  }
}

// Send a packet to the address the last request came from
void UPnPHelper::Respond() {
  UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
  // Send the String's underlying byte array
  UDP.write(response_packet.c_str());
  UDP.endPacket();
}

#include "UPnPHelper.h"

// UPnP multicast address
IPAddress addr(239, 255, 255, 250);
// UPnP Port
const unsigned int port = 1900;
// Buffer for received packets
char in_packet[255];

// Constructor
UPnPHelper::UPnPHelper() { }

// Destructor
UPnPHelper::~UPnPHelper() { }

// Starts the UDP server
bool UPnPHelper::Start() {
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

// Send a packet to the address the last request came from
void UPnPHelper::Respond() {

}

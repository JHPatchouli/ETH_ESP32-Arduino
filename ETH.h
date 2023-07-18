#ifndef _ETH_H_
#define _ETH_H_

#include <Arduino.h>


void ETH_REST();
void ETH_CHA(int mode);
void ETH_CWDHCP(int mode, int en);
void ETH_CIPETH(String IP, String GW, String MK);
void ETH_CIPWIFI(String IP, String GW, String MK);
bool ETH_UARTSEND(String data, bool mode = false, int timeout = 200);
void ETH_WIFIMODE(int mode);
void ETH_CUDPS(String RomIP, int RPort, int LPort);
void ETH_WIFICON(String SSID, String Passwd);
void ETH_SHOWCF();
String ETH_GETDATA();
void SerialtoSerial1();
#endif
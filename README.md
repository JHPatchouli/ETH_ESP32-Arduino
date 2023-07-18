**# ETH_ESP32-Arduino**

 Example of Arduino 2560 for WT32-ETH01 module 

**# The project offers**

```c++
void ETH_REST(); //Restore default settings
void ETH_CHA(int mode); //Setting up the pass-through channel
void ETH_CWDHCP(int mode, int en); //DHCP settings(WIFI-related settings may not work)
void ETH_CIPETH(String IP, String GW, String MK); //Ethernet Static IP Settings
void ETH_CIPWIFI(String IP, String GW, String MK); //WIFI Static IP Settings（experimental）
bool ETH_UARTSEND(String data, bool mode = false, int timeout = 200); //Serial port executes commands to the module
void ETH_WIFIMODE(int mode); //WIFI working mode setting
void ETH_CUDPS(String RomIP, int RPort, int LPort); //UDP server settings
void ETH_WIFICON(String SSID, String Passwd); //Access Point Setting
void ETH_SHOWCF(); //Query all IPs of the device
String ETH_GETDATA(); //Getting UDP return data
void SerialtoSerial1(); //Master and Module Serial Passthrough(For debugging)
```


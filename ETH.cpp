#include "ETH.h"




/*-------------------以下为网络设置相关接口----------------------*/
/*-----以太网相关-----*/
/*ETH_IP设置
  参数IP:[
    静态IP
  ]
  参数GW:[
    网关地址
  ]
  参数MK:[
    网络掩码
  ]
*/
void ETH_CIPETH(String IP, String GW, String MK)
{
    // 准备AT指令
    if (ETH_UARTSEND("AT+CIPETH_DEF=\"" + IP + "\",\"" + GW + "\",\"" + MK + "\""))
    {
        Serial.println("IP配置完成");
    }
}

/*-----WIFI相关(存在无法验证功能请酌情使用)-------*/
/*WIFI_IP设置(存在一些问题，弃用且保留)
  参数IP:[
    静态IP
  ]
  参数GW:[
    网关地址
  ]
  参数MK:[
    网络掩码
  ]
*/
void ETH_CIPWIFI(String IP, String GW, String MK)
{
    // 准备AT指令
    if (ETH_UARTSEND("AT+CIPSTA_DEF=\"" + IP + "\",\"" + GW + "\",\"" + MK + "\""))
    {
        Serial.println("IP配置完成");
    }
}

/*WIFI模式设置(必须设置透传通道为WIFI才可设置)
  参数mode:[
    WIFI模式配置
  ]
*/
void ETH_WIFIMODE(int mode)
{
    // 准备AT指令
    if (ETH_UARTSEND("AT+CWMODE_DEF=" + String(mode)))
    {
        Serial.println("WIFI模式配置完成");
    }
}

/*WIFI连接
  参数SSID:[
    WIFI名称
  ]
  参数Passwd:[
    密码
  ]
*/
void ETH_WIFICON(String SSID, String Passwd)
{
    // 准备AT指令
    if (ETH_UARTSEND("AT+CWJAP=\"" + SSID + "\",\"" + Passwd + "\"", 0, 5000))
    {
        Serial.println("WIFI连接配置完成");
    }
}

/*------通信服务器相关------*/
/*UDP服务器设置
  参数RomIP:[
    远程IP
  ]
  参数RPort:[
    远程端口
  ]
  参数LPort:[
    本地端口
  ]
*/
void ETH_CUDPS(String RomIP, int RPort, int LPort)
{
    // 准备AT指令
    if (ETH_UARTSEND("AT+CIPSTART=\"UDPS\",\"" + RomIP + "\"," + RPort + "," + LPort))
    {
        Serial.println("udp服务器配置完成\r\n端口：" + String(LPort));
    }
}









/*-------------------以下为公共接口----------------------*/
/*重置函数*/
void ETH_REST()
{
    // 调用通信接口，传命令
    if (ETH_UARTSEND("AT+RESTORE"))
    {
        Serial.println("重置完成");
    }
}

/*透传通道模式设置
  参数mode:[
  1:串口以太网透传通道
  2:串口 wifi 透传通道
  3:串口蓝牙透传通道
  4:wifi 以太网透传通道
  5:wifi 蓝牙透传通道
  6:以太网蓝牙透传通道
  ]
*/
void ETH_CHA(int mode)
{
    // 调用通信接口，传命令
    if (ETH_UARTSEND("AT+PASSCHANNEL=" + String(mode)))
    {
        Serial.println("通道配置完成");
    }
}

/*DHCP模式设置(可能不生效，建议直接设置IP看是否能覆盖配置)
  参数mode:[
  0 设置 ESP8266 SoftAP
  1 设置 ESP8266 Station
  2 设置 ESP8266 SoftAP 和 Station
  3:设置 ETH
  ]
  参数en:[
  0：关闭 DHCP
  1：开启 DHCP
  ]
*/
void ETH_CWDHCP(int mode, int en)
{
    // 准备AT指令
    if (ETH_UARTSEND("AT+CWDHCP_DEF=" + String(mode) + "," + String(en)))
    {
        Serial.println("DHCP模式配置完成");
    }
    else
    {
        Serial.println("DHCP配置尝试修复");
        ETH_UARTSEND("AT+CWDHCP_DEF=" + String(mode) + "," + String(!en));
        if (ETH_UARTSEND("AT+CWDHCP_DEF=" + String(mode) + "," + String(en)))
        {
            Serial.println("DHCP模式配置完成");
        }
    }
}

/*查询设备所有IP
 */
void ETH_SHOWCF()
{
    ETH_UARTSEND("AT+CIFSR", 1);
}

/*查询缓冲区是否有新数据(以及开始交互数据时获取数据用)*/
String ETH_GETDATA()
{
    String msg = "";
    if (Serial1.available())
    {
        msg = Serial1.readStringUntil('\n');
    }
    return msg.substring(7);
}

/*公共通信接口
  参数data:[
    命令
  ]
  参数mode:[
    0(默认)：写入模式
    1:查询模式
  ]
*/
bool ETH_UARTSEND(String data, bool mode = false, int timeout = 200)
{
    Serial1.println(data);
    // 延时等待返回

    Serial1.println("\r\n");
    Serial.println("-------\r\ncmd:" + data);
    delay(timeout);
    // 判断是否有返回
    if (Serial1.available())
    {
        // 读取整个缓冲区
        String data = Serial1.readString();
        if (!mode)
        {
            if (data.indexOf("OK") != -1 || data.indexOf("ok") != -1)
            {
                // Serial.println("tsssssss");
                Serial1.flush();
                return true;
            }
            else
            {
                Serial.println("ETH错误返回:" + data);
                Serial1.flush();
                return false;
            }
        }
        else
        {
            Serial.println("ETH返回:" + data);
            Serial1.flush();
            return true;
        }
    }
    Serial.println("ETH无返回:请检查串口");
    Serial1.flush();
    return false;
}

/*预留调试接口(串口0对串口1双向转发)*/
void SerialtoSerial1()
{
    // 从串口0读取数据并发送到串口1
    if (Serial.available())
    {
        char data = Serial.read();
        Serial1.write(data);
    }

    // 从串口1读取数据并发送到串口0
    if (Serial1.available())
    {
        char data = Serial1.read();
        Serial.write(data);
    }
}
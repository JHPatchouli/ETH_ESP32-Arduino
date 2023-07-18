#include "ETH.h" //引用ETH库

void setup()
{
    Serial.begin(115200);                                      // 初始化串口0，波特率9600
    Serial1.begin(115200);                                     // 初始化串口1，波特率9600
    ETH_REST();                                                // 重置模块
    ETH_CHA(1);                                                // 设置透传通道
    ETH_CWDHCP(3, 0);                                          // 以太网DHCP关闭
    ETH_CIPETH("192.168.0.8", "192.168.0.1", "255.255.255.0"); // 设置以太网静态IP
    ETH_CUDPS("0.0.0.0", 3344, 3333);                      // 启动udp服务
    ETH_SHOWCF();                                              // 输出设备所有IP
}

void loop()
{
    String rt = ETH_GETDATA(); // 获取所有返回(udp数据包获取)
    if (rt != "")
    {
        Serial.println(rt); // 返回不为空就输出
    }
    // SerialtoSerial1();//预留串口转发(实现串口对串口1双向通信用于调试)
}

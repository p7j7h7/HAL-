#include<WiFi.h>
#include<PubSubClient.h>
#include<Arduino.h>
#include<stdio.h>

const char*ssid ="pjh";                //ESP32连接的WiFi账号
const char*password = "187178159xX";         //WiFi密码
const char*mqttServer = "120.79.133.42";   //要连接到的服务器IP
const int mqttPort =1883;                 //要连接到的服务器端口号
const char*mqttUser = "admin";            //MQTT服务器账号
const char*mqttPassword = "public";       //MQTT服务器密码
 
WiFiClient espClient;                     // 定义wifiClient实例
PubSubClient client(espClient);          // 定义PubSubClient的实例
 
void callback(char*topic, byte* payload, unsigned int length) ;
void setup() 
{
    Serial.begin(115200);                   //串口函数，波特率设置
    while(WiFi.status() != WL_CONNECTED)   //若WiFi接入成功WiFi.status()会返回 WL_CONNECTED
    {       
        Serial.println("连接wifi中");         //串口输出：连接wifi中
        WiFi.begin(ssid,password);          //接入WiFi函数（WiFi名称，密码）
        delay(2500);                         //若尚未连接WiFi，则进行重连WiFi的循环
    }
    Serial.println("wifi连接成功");             //连接wifi成功之后会跳出循环，串口并输出：wifi连接成功
    client.setServer(mqttServer,mqttPort);  //MQTT服务器连接函数（服务器IP，端口号）
    client.setCallback(callback);           //设定回调方式，当ESP32收到订阅消息时会调用此方法
    while (!client.connected())             //是否连接上MQTT服务器
    {
        Serial.println("连接服务器中");         //串口打印：连接服务器中
        if (client.connect("ESP32",mqttUser, mqttPassword ))  //如果服务器连接成功
        {
            Serial.println("服务器连接成功");          //串口打印：服务器连接成功
        }
        else 
        {
            Serial.print("连接服务器失败");            //串口打印：连接服务器失败
            Serial.print(client.state());       //重新连接函数
            delay(2000);                        
        }
    }
    client.subscribe("ESP32");                 //连接MQTT服务器后订阅主题
    Serial.println("已订阅主题，等待主题消息....");                  //串口打印：已订阅主题，等待主题消息
    client.publish("ESP32","Hello from ESP32");//向服务器发送的信息(主题，内容)
}
 void callback(char*topic, byte* payload, unsigned int length) 
{
    Serial.print("来自订阅的主题:");              //串口打印：来自订阅的主题:
    Serial.println(topic);                //串口打印订阅的主题
    Serial.print("信息：");              //串口打印：信息：
    for (int i = 0; i< length; i++)        //使用循环打印接收到的信息
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}
void loop()   
{
  client.loop();                              //回旋接收函数  等待服务器返回的数据
}

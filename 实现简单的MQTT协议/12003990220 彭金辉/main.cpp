#include <Arduino.h>
#include <stdio.h>
#include <HardwareSerial.h>

//const int led=2;
char x=0;
int flag=0,num=0;
void setup() {
  //pinMode(led,OUTPUT);
  Serial.begin(115200);
  printf("input 'A' show begin,input 'B' show end\n");
}

void loop() {
    //printf("12");
  if(Serial.available()>0)//判断是否有输入
  {
    x=Serial.read();
  }
  if(x=='A')
  {
      if(flag==0)
      {
      printf("begin\n");
      flag=1;
      }
      printf("%d\n",num++);
  }
  else if(x=='B')
  {
      if(flag==1)
      {
      printf("end\n");
      flag=0;
      }
  }
  delay(1000);
}

#include "Arduino.h"
#include "MorseBinNET2.h"
MorseBinNET2::MorseBinNET2(String address, int pinTransmit,int pinReceive){
	_pinTransmit = pinTransmit;
	_pinReceive = pinReceive;
	_address = address;
	pinMode(_pinTransmit,OUTPUT);
	pinMode(_pinReceive,INPUT);
}
void MorseBinNET2::send(String address, String data1, String data2){
		sendByte(address, _pinTransmit);
		sendByte(_address, _pinTransmit);
		sendByte(data1, _pinTransmit);
		sendByte(data2, _pinTransmit);
}
void MorseBinNET2::receive(){
	String receiverAddress = receiveByte(_pinReceive);
	if((receiverAddress == "errTimeout")){
		lastMessage[0] = "errTimeout";
		return;
	}
	String senderAddress = receiveByte(_pinReceive);
	if(senderAddress == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	}
	String data1 = receiveByte(_pinReceive);
	if(data1 == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	}
	String data2 = receiveByte(_pinReceive);
	if(data2 == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	}
	if(_address != receiverAddress){
		lastMessage[0] = "errWrongAddress";
		return;
	}
	lastMessage[1] = senderAddress;
	lastMessage[2] = data1;
	lastMessage[3] = data2;
	lastMessage[0] = "errSuccess";
}
String MorseBinNET2::placeRequest(String address, String data1, String data2) {
	return "errNotImplemented";
}
void MorseBinNET2::Send0(int sendpin) {
 	digitalWrite(sendpin,HIGH);
 	delay(time0);
 	digitalWrite(sendpin,LOW);
 	delay(time1);
  }
void MorseBinNET2::Send1(int sendpin) {
 	digitalWrite(sendpin,HIGH);
 	delay(time1);
 	digitalWrite(sendpin,LOW);
 	delay(time1);
  }
void MorseBinNET2::sendByte(String input,int sendpin){
    	//Serial.println("gotit");
	digitalWrite(sendpin,HIGH);
	delay(time0+time1);
	digitalWrite(sendpin,LOW);
	delay(time1);
   	 for (int i=0;i<8;i++){
    		if (input.charAt(i)=='1'){
     		 Send1(sendpin);
      		//Serial.println("gotit1");
      	}
      if (input.charAt(i)=='0'){
      		Send0(sendpin);
      		//Serial.println("gotit0");
      }
    }
  }
  String MorseBinNET2::receiveByte(int respin){
	  String buf;
  	int waitTimer = 0;
	int timeouttimer = 0;
	while(digitalRead(respin)==LOW){
		timeouttimer++;
    		delay(1);
    		if(timeouttimer>=10000){
      		return "errTimeout";
	  	}
	}
	while(digitalRead(respin) == HIGH){
		waitTimer++;
		delay(1);
	}
 	if(waitTimer>time0+time1-2){
	} else {
		return "errTimeout";
	}
 	for (int i=0;i<8;i++){
 	int timer = 0;
   	while (digitalRead(respin)==LOW){
    		timer++;
    		delay(1);
    		if(timer>=10000){
      		timer = 0;
      		return "errTimeout";
	  		}
    	}
    	int t = 0;
    	while(digitalRead(respin)==HIGH) {
      		t++;
      		delay(1);
     	}
      	if (t > (time0+time1)/2 && t < time0+time1) {
        	buf += "0";
        }
        else {
          	buf += "1";
          }   
    }
    	return buf;
  }
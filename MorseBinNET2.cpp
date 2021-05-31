#include "Arduino.h"
#include "MorseBinNET2.h"
MorseBinNET2::MorseBinNET2(String address, int pinTransmit){
	_pinTransmit = pinTransmit;
	_address = address;
	pinMode(_pinTransmit,INPUT);
	timeMiddle = ((time0+time1)/2);
	timeForStart = ((time0+time1)-(time1/2));
}
void MorseBinNET2::send(String address, String data1, String data2){
		sendByte(address, _pinTransmit);
		sendByte(_address, _pinTransmit);
		sendByte("00000000",_pinTransmit);
		sendByte(data1, _pinTransmit);
		sendByte(data2, _pinTransmit);
}
void MorseBinNET2::send(String address,String busID, String data1, String data2){
		sendByte(address, _pinTransmit);
		sendByte(_address, _pinTransmit);
		sendByte(busID,_pinTransmit);
		sendByte(data1, _pinTransmit);
		sendByte(data2, _pinTransmit);
}
void MorseBinNET2::receive(){
	String receiverAddress = receiveByte(_pinTransmit);
	if((receiverAddress == "errTimeout")){
		lastMessage[0] = "errTimeout";
		return;
	} else {
		if(receiverAddress == "errGrabledMessage"){
			lastMessage[0] = "errGrabledMessage";
			return;
		}
	}
	String senderAddress = receiveByte(_pinTransmit);
	if(senderAddress == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	} else {
		if(senderAddress == "errGrabledMessage"){
			lastMessage[0] = "errGrabledMessage";
			return;
		}
	}
	String senderBusID = receiveByte(_pinTransmit);
	if(senderBusID == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	} else {
		if(senderBusID == "errGrabledMessage"){
			lastMessage[0] = "errGrabledMessage";
			return;
		}
	}
	String data1 = receiveByte(_pinTransmit);
	if(data1 == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	} else {
		if(data1 == "errGrabledMessage"){
			lastMessage[0] = "errGrabledMessage";
			return;
		}
	}
	String data2 = receiveByte(_pinTransmit);
	if(data2 == "errTimeout"){
		lastMessage[0] = "errTimeout";
		return;
	} else {
		if(data2 == "errGrabledMessage"){
			lastMessage[0] = "errGrabledMessage";
			return;
		}
	}
	if(_address != receiverAddress){
		lastMessage[0] = "errWrongAddress";
		//Serial.println(_address + ":" + receiverAddress);
		return;
	}
	if(senderBusID == "00000000"){
		lastMessage[4] = "local";
	} else{
		lastMessage[4] = senderBusID;
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
 	delayMicroseconds(time0);
 	digitalWrite(sendpin,LOW);
 	delayMicroseconds(time1);
  }
void MorseBinNET2::Send1(int sendpin) {
 	digitalWrite(sendpin,HIGH);
 	delayMicroseconds(time1);
 	digitalWrite(sendpin,LOW);
 	delayMicroseconds(time1);
  }
void MorseBinNET2::sendByte(String input,int sendpin){
	while(digitalRead(sendpin) == HIGH){
		delayMicroseconds(time1+5);
		//Serial.println("StuckInTraffic");
	}
	pinMode(sendpin,OUTPUT);
    	//Serial.println("gotit");
	digitalWrite(sendpin,HIGH);
	delayMicroseconds(time0+time1);
	digitalWrite(sendpin,LOW);
	delayMicroseconds(time1);
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
	pinMode(sendpin,INPUT);
  }
  String MorseBinNET2::receiveByte(int respin){
	String buf;
  	int waitTimer = 0;
	int timeouttimer = 0;
	while(digitalRead(respin)==LOW){
		timeouttimer+=8;
    	delayMicroseconds(8);
    	if(timeouttimer>=30000){
      		return "errTimeout";
	  	}
	}
	int microTimer = micros();
	while(digitalRead(respin) == HIGH){
	}
	waitTimer = micros() - microTimer;
 	if(waitTimer>timeForStart){
	} else {
		//Serial.println(waitTimer);
		//Serial.print("StartTime should be: ");
		//Serial.println(timeForStart);
		return "errGrabledMessage";
	}
 	for (int i=0;i<8;i++){
		int timer = 0;
		while (digitalRead(respin)==LOW){
			timer++;
			delayMicroseconds(8);
			if(timer>=10000){
				timer = 0;
				return "errTimeout";
			}
		}
		int microStart = micros();
		while(digitalRead(respin)==HIGH) {
		}
		int t = micros() - microStart;
		if (t > timeMiddle && t < timeForStart) {
			buf += "0";
		}
		else {
			if(t < timeMiddle && t < timeForStart){
				buf += "1";
				} else {
					buf += "n";
				}      	
			}   
    }
    return buf;
  }
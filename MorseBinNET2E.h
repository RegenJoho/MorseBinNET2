#ifndef MorseBinNET2E_h
#define MorseBinNET2E_h
#include "Arduino.h"
	class MorseBinNET2E {
		public:
			MorseBinNET2E(String address, int pinTransmit);
			MorseBinNET2E(String address, int pinTransmit, int speed);
			void send(String address, String data1, String data2, String data3, String data4, String data5, String data6, String data7, String data8);
			void send(String address,String busID, String data1, String data2, String data3, String data4, String data5, String data6, String data7, String data8);
			void receive();
			String placeRequest(String address, String data1, String data2);
			void sendByte(String input , int sendpin);
			String receiveByte(int resPin);
			String lastMessage[11];
		private:
			String _address;
			int _pinTransmit;
			int _pinReceive;
			void Send0(int sendpin);
			void Send1(int sendpin);
			int time1 = 48;
			int time0 = 144;
			int timeMiddle = 0;
			int timeForStart = 0;
	};
#endif

#ifndef MorseBinNET2_h
#define MorseBinNET2_h
#include "Arduino.h"
	class MorseBinNET2 {
		public:
			MorseBinNET2(String address, int pinTransmit);
			void send(String address, String data1, String data2);
			void send(String address,String busID, String data1, String data2);
			void receive();
			String placeRequest(String address, String data1, String data2);
			void sendByte(String input , int sendpin);
			String receiveByte(int resPin);
			String lastMessage[5];
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

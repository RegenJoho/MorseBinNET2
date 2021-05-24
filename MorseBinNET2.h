#ifndef MorseBinNET2_h
#define MorseBinNET2_h
#include "Arduino.h"
	class MorseBinNET2 {
		public:
			MorseBinNET2(String address, int pinTransmit);
			void send(String address, String data1, String data2);
			void receive();
			String placeRequest(String address, String data1, String data2);
			String lastMessage[4];
		private:
			String _address;
			int _pinTransmit;
			int _pinReceive;
			void sendByte(String input , int sendpin);
			void Send0(int sendpin);
			void Send1(int sendpin);
			String receiveByte(int resPin);
			int time1 = 48;
			int time0 = 144;
			int timeMiddle = 0;
			int timeForStart = 0;
	};
#endif

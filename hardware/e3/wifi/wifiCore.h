#ifndef WIFICORE_H

	#define WIFICORE_H

	#include <SoftwareSerial.h>
	#include <avr/pgmspace.h>
	#include <Arduino.h>
	#include "../const.h"
	#include "../config/config.h"
	#include "../lcd/lcd.h"

	#define WIFI_TX 3
	#define WIFI_RX 4
	#define WIFI_RST 11
	#define LINE_BUFFER_SIZE 128
	#define WIFI_BUFFER_SIZE 256
	#define TIMEOUT 30000

	extern SoftwareSerial wifi;
	
	void wifiInit();
	void wifiLoop();
	void wifiBufferLoop();
	
	unsigned char wifiConnectToAP();
	unsigned char wifiExecute(char *command);
	unsigned char hasNewLine();
	
	char* useLineBuffer();

#endif
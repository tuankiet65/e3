#include <SoftwareSerial.h>
#include "commonVariables.h"
#include <avr/pgmspace.h>

#define WIFI_TX 3
#define WIFI_RX 4
#define WIFI_RST 11
#define WIFI_CHPD 12
#define LINE_BUFFER_SIZE 64
#define WIFI_BUFFER_SIZE 256

SoftwareSerial wifi(WIFI_RX, WIFI_TX);
char wifiBuffer[WIFI_BUFFER_SIZE], lineBuffer[LINE_BUFFER_SIZE];
int wifiMsgLen;
unsigned char lockNewLine = 0, hasNewLine = 0;

void wifiInit() {
    //pinMode(WIFI_RST, OUTPUT);
    //pinMode(WIFI_CHPD, OUTPUT);
    //wifiReset();
    wifi.begin(9600); // the lowest baudrate that works, 1200 don't work. 2400 is unstable, 4800?
    //wifiLoop();
    lcdUpdateWifiStatus(WIFI_STARTING);
    wifi.write("AT+RST\r\n");
    delay(2000);
    wifiExecute("ATE0");
    wifiExecute("AT+GMR");
    wifiExecute("AT+CWMODE_CUR=1");
}

void wifiReset(){
    digitalWrite(WIFI_RST, LOW);
    digitalWrite(WIFI_CHPD, LOW);
    delay(1000);
    digitalWrite(WIFI_RST, HIGH);
    delay(2000);
    digitalWrite(WIFI_CHPD, HIGH);
    delay(2000);
}

void wifiExecute(char* command) {
    wifi.write(command);
    wifi.write("\r\n");
    memset(wifiBuffer, 0, WIFI_BUFFER_SIZE);
    wifiMsgLen = 0;
    while (1) {
        wifiBufferLoop();
        if (lockNewLineBuffer()) {
            Serial.println(lineBuffer);
            if (strstr(lineBuffer, "OK") != NULL) {
                Serial.println(F("end of command, ok received"));
                unlockNewLineBuffer();
                delay(500);
                return;
            }
            if (strstr(lineBuffer, "ERROR") != NULL) {
                Serial.println(F("end of command, error received"));
                unlockNewLineBuffer();
                delay(500);
                return;
            }
            unlockNewLineBuffer();
        }
    }
}

void wifiBufferLoop() {
    while (wifi.available()) {
        if (wifiMsgLen == WIFI_BUFFER_SIZE - 2) {
            Serial.println("overflow");
            return;
        }
        wifiBuffer[wifiMsgLen] = wifi.read();
        if (wifiBuffer[wifiMsgLen] == '\n' && (!lockNewLine)) {
            wifiBuffer[wifiMsgLen] = '\0';
            memmove(lineBuffer, wifiBuffer, wifiMsgLen + 1);
            hasNewLine = 1;
            wifiMsgLen = 0;
        } else {
            wifiMsgLen++;
        }
    }
}

unsigned char lockNewLineBuffer() {
    if (hasNewLine) {
        hasNewLine = 0;
        lockNewLine = 1;
        return 1;
    } else {
        lockNewLine = 0;
        return 0;
    }
}

void unlockNewLineBuffer() {
    lockNewLine = 0;
}

void wifiLoop() {
    while (1) {
        if (wifi.available())
            Serial.write(wifi.read());
        if (Serial.available())
            wifi.write(Serial.read());
    }
}

void wifiConnectToAP() {
    lcdUpdateWifiStatus(WIFI_CONNECTING_AP);
    char commandBuf[128];
    sprintf_P(commandBuf, PSTR("AT+CWJAP_CUR=\"%s\",\"%s\""), config.ssidName, config.ssidPassword);
    wifiExecute(commandBuf);
}

void wifiSendHTTPRequest(float temperature, float humidity, float dustLevel, float coLevel) {
    char tempStr[6],
         humidStr[6],
         dustStr[5],
         coStr[5],
         sendBuffer[300],
         tmp[32];

    dtostrf(temperature, 5, 2, tempStr);
    dtostrf(humidity, 5, 2, humidStr);
    dtostrf(dustLevel, 4, 2, dustStr);
    dtostrf(coLevel, 4, 2, coStr);

    wifiExecute("AT+CIPMUX=0");
    lcdUpdateWifiStatus(WIFI_CONNECTING_HTTP);
    sprintf_P(sendBuffer, PSTR("AT+CIPSTART=\"TCP\",\"%s\",%d"), config.host, config.port);
    wifiExecute(sendBuffer);

    lcdUpdateWifiStatus(WIFI_SENDING);
    int bufferLen;
    sprintf_P(sendBuffer, PSTR("GET /api/add/event?client_id=%s&temperature=%s&humidity=%s&dustlevel=%s&colevel=%s&apikey=%s HTTP/1.1\r\n"
                               "Host: %s\r\n"
                               "\r\n"),
              config.clientID,
              tempStr,
              humidStr,
              dustStr,
              coStr,
              config.apiKey,
              config.host);

    bufferLen = strlen(sendBuffer);
    sprintf_P(tmp, PSTR("AT+CIPSEND=%d"), bufferLen);
    wifiExecute(tmp);
    wifiExecute(sendBuffer);
    wifiExecute("AT+CIPCLOSE");
    lcdUpdateWifiStatus(WIFI_SENDOK);
}
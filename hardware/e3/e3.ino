#include "const.h"
#include "sensors/DHT.h"
#include "sensors/dust.h"
#include "config/config.h"
#include "lcd/lcd.h"
#include "notification/led.h"
#include "wifi/wifiCore.h"
#include "wifi/wifiClient.h"
#include "wifi/wifiServer.h"
#include <avr/wdt.h>

void __attribute__((naked)) __attribute__((section(".init3"))) bwdt_init(void) {
    MCUSR = 0;
    wdt_disable();
}

float temperature, humidity, dustDensity, coLevel, voltage;
unsigned long t;

void setup() {
    wdt_enable(WDTO_2S);
    Serial.begin(38400);
    //attachInterrupt(digitalPinToInterrupt(2), configInterrupt, CHANGE);
    lcdInit();
    dustInit();
    dhtInit();
    ledInit();
    configRead();
    dustRead(&voltage, &dustDensity);
    dhtRead(&temperature, &humidity);
    lcdUpdateTempHumid(temperature, humidity);
    lcdUpdateDustCo(voltage, dustDensity);
}


void loop() {
    wifiInit();
    wifiClientInit();
    wifiSendHTTPRequest(temperature, humidity, dustDensity, voltage);
    t=millis();
    wifiDeepSleep(55L*1000L);
    lcdUpdateWifiStatus(WIFI_IDLE);
    while (millis()-t<=60L*1000L){
        wdt_reset();
        if (configEnabled==1){
            configStarted=1;
            wifiInit();
            wifiServerInit();
            wifiServerListener();
        }
    }
    dustRead(&voltage, &dustDensity);
    dhtRead(&temperature, &humidity);
    lcdUpdateTempHumid(temperature, humidity);
    lcdUpdateDustCo(voltage, dustDensity);
    if (dustDensity>0.2){
        ledSetRight(LED_RED);
        ledSetColor();
    } else {
        ledSetRight(LED_GREEN);
        ledSetColor();
    }
}

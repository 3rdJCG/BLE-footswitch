#include <Arduino.h>
#include <BleKeyboard.h>

#define footSW 16
#define LEDpin 17

#define LEDC_CH0 0

BleKeyboard bleKeyboard("BLE footswitch", "AYAME Electronics");

volatile unsigned long time_prev = 0;

void sendKeys();

void setup(){
	Serial.begin(115200);
	pinMode(LEDpin,OUTPUT);
	pinMode(footSW,INPUT);
	bleKeyboard.begin();
	attachInterrupt(footSW,sendKeys,CHANGE);
	ledcSetup(LEDC_CH0,5000,8);
	ledcAttachPin(LEDpin,LEDC_CH0);
}

void loop(){
	while(bleKeyboard.isConnected()){
		ledcWrite(LEDC_CH0,10);
	}
	ledcWrite(LEDC_CH0,70);
	delay(100);
	ledcWrite(LEDC_CH0,0);
	delay(1000);
}

void sendKeys(){
	if(millis()-time_prev>20.0&&digitalRead(footSW)){
		bleKeyboard.press(KEY_LEFT_ALT);
		bleKeyboard.press(0x60);
		bleKeyboard.releaseAll();
	}
	time_prev = millis();
}

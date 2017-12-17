#include <Arduino.h>

int fadePin[3] = {3, 5, 13};                 // LED connected to digital pin 13
boolean isStop = 0, isGo = 0, isStopGo = 0;
char stopPin = A1;
char goPin = A0;
boolean ledOn = false, ledAnAus = false;
unsigned long nextFade[2];
int fadeBrightness[2] = {150, 150};
char ledState = LOW, fadeDir[2] = {1, 1};


void fade(boolean isOn, boolean isBlink, int ledNr) {
    boolean action = true;
    unsigned long now;
    now = millis();
    if ((fadeBrightness[ledNr] > 254) && !isOn)  {action = false;} 
    if ((fadeBrightness[ledNr] < 1) && isOn)  {action = false;}
    if (isBlink)  {action = true;}
    if ((now >= nextFade[ledNr]) && action)  {
        nextFade[ledNr] = now + 1;
        if ((fadeDir[ledNr] > 0) && (fadeBrightness[ledNr] > 254)){
                fadeDir[ledNr] = - fadeDir[ledNr];
                nextFade[ledNr] += 1000;
        } 
        else if ((fadeDir[ledNr] < 0) && (fadeBrightness[ledNr] < 1)) {
                fadeDir[ledNr] = - fadeDir[ledNr];
                nextFade[ledNr] += 1000;
        }
        else {  fadeBrightness[ledNr] += fadeDir[ledNr];
        }
        analogWrite(fadePin[ledNr], fadeBrightness[ledNr]);
    }
}



void setup() {
    // put your setup code here, to run once:
    pinMode(fadePin[0], OUTPUT);      // sets the digital pin as output
    pinMode(fadePin[1], OUTPUT);
    pinMode(stopPin, INPUT_PULLUP);
    pinMode(goPin, INPUT_PULLUP);
    ledState = LOW;
    nextFade[0] = millis();
    nextFade[1] = millis() + 500;
    digitalWrite(fadePin[0], LOW);
    digitalWrite(fadePin[1], LOW);
}

void loop() {
    // put your main code here, to run repeatedly:
    isStop = digitalRead(stopPin);
    isGo = digitalRead(goPin);
    fade(isGo, (isStop && isGo), 0);
    fade(isStop, false, 1);
    //digitalWrite(fadePin[2], !isStop);
}
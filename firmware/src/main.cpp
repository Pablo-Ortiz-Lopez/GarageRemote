#include <Arduino.h>

using namespace std;

void setup() {
    Serial.begin(300);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
}

uint8_t getChannel(uint8_t current) {
    if (digitalRead(2))
        return 1;
    if (digitalRead(3))
        return 2;
    if (digitalRead(4))
        return 3;
    if (digitalRead(5))
        return 4;
    if (digitalRead(6))
        return 5;
    if (digitalRead(7))
        return 6;
    return 0;
}

uint8_t currentChannel = 0;

void loop() {
    uint8_t channel = getChannel(currentChannel);

    String channelNames[7] = {"None", "Casa 1", "Casa 2", "Javi 1", "Javi 2", "Piso 1", "Piso 2"};
    if (currentChannel != channel) {
        //Serial.println(channelNames[channel]);
        Serial.println("Hola");
        currentChannel = channel;
    }

    if (channel != 0) {
        delay(11);
    }
    delay(100);
}
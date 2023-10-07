#include <Arduino.h>
#include <SPI.h>

using namespace std;

#define CSN_MAX7060 10
#define ENABLE 8

void setup() {
  // Initialize SPI
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);  
  // Initialize Serial communication
  Serial.begin(300); // You can change the baud rate as needed
  
  // Set chipSelectPin as an output
  pinMode(CSN_MAX7060, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE,HIGH);
  delay(2);
}

void loop() {
  
  // Invert chip select to select the device
  digitalWrite(CSN_MAX7060, LOW);

  // Send command
  SPI.transfer(0x02);

  // Read address 0
  SPI.transfer(0x00);

  // Read value
  uint8_t signature = SPI.transfer(0x04);
  uint8_t tmux = SPI.transfer(0x12);
  uint8_t status = SPI.transfer(0x00);

  // Release the device by setting CS high
  digitalWrite(CSN_MAX7060, HIGH);

  // Print the value to the Serial monitor
  Serial.print("Signature: ");
  Serial.println(signature);
  Serial.print("tmux: ");
  Serial.println(tmux);
  Serial.print("status: ");
  Serial.println(status);

  // Now 'value' contains the byte read from address 0
  delay(2000);
}
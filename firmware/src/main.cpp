#include <Arduino.h>
#include <SPI.h>

using namespace std;

const int chipSelectPin = 10; // Chip select (CS) pin

void setup() {
  // Initialize SPI
  SPI.begin();
  
  // Initialize Serial communication
  Serial.begin(9600); // You can change the baud rate as needed
  
  // Set chipSelectPin as an output
  pinMode(chipSelectPin, OUTPUT);
  
  // Invert chip select to select the device
  digitalWrite(chipSelectPin, LOW);

  // Send command to read from address 0
  uint8_t read_command = 0x02; // Modify this command as needed
  SPI.transfer(read_command);

  // Read the value at address 0
  uint8_t value = SPI.transfer(0x00); // You may send a dummy byte here

  // Release the device by setting chipSelectPin high
  digitalWrite(chipSelectPin, HIGH);

  // Print the value to the Serial monitor
  Serial.print("Value at address 0: ");
  Serial.println(value);

  // Now 'value' contains the byte read from address 0
}

void loop() {
  // Your main code here
}
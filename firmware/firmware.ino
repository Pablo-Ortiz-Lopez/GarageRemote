#include "CC1101.h"
#include <SPI.h>

using namespace std;

void setup() {
  ELECHOUSE_cc1101.setSpiPin(13, 12, 11, 15);
  ELECHOUSE_cc1101.getCC1101();

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  ELECHOUSE_cc1101.Init();             // must be set to initialize the cc1101!
  ELECHOUSE_cc1101.setGDO(16,17);        // Set GDO0
  ELECHOUSE_cc1101.setCCMode(1);       // Set config for internal transmission mode.
  ELECHOUSE_cc1101.setPA(12);          // Set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12) Default is max!
  ELECHOUSE_cc1101.setSyncMode(0);     // Combined sync-word qualifier mode. 0 = No preamble/sync. 1 = 16 sync word bits detected. 2 = 16/16 sync word bits detected. 3 = 30/32 sync word bits detected. 4 = No preamble/sync, carrier-sense above threshold. 5 = 15/16 + carrier-sense above threshold. 6 = 16/16 + carrier-sense above threshold. 7 = 30/32 + carrier-sense above threshold.
  ELECHOUSE_cc1101.setAddr(0);         // Address used for packet filtration. Optional broadcast addresses are 0 (0x00) and 255 (0xFF).
  ELECHOUSE_cc1101.setWhiteData(0);    // Turn data whitening on / off. 0 = Whitening off. 1 = Whitening on.
  ELECHOUSE_cc1101.setLengthConfig(2); // 0 = Fixed packet length mode. 1 = Variable packet length mode. 2 = Infinite packet length mode. 3 = Reserved
  ELECHOUSE_cc1101.setCrc(0);          // 1 = CRC calculation in TX and CRC check in RX enabled. 0 = CRC disabled for TX and RX.
  ELECHOUSE_cc1101.setDcFilterOff(0);  // Disable digital DC blocking filter before demodulator. Only for data rates ≤ 250 kBaud The recommended IF frequency changes when the DC blocking is disabled. 1 = Disable (current optimized). 0 = Enable (better sensitivity).
  ELECHOUSE_cc1101.setPRE(0);          // Sets the minimum number of preamble bytes to be transmitted. Values: 0 : 2, 1 : 3, 2 : 4, 3 : 6, 4 : 8, 5 : 12, 6 : 16, 7 : 24
  ELECHOUSE_cc1101.setAppendStatus(0); // When enabled, two status bytes will be appended to the payload of the packet. The status bytes contain RSSI and LQI values, as well as CRC OK.
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

uint8_t codeDelays[3] = {10, 45, 7};
uint8_t codeLengths[6] = {13, 13, 20, 20, 216, 216};
uint8_t codes[6][216] = {
    {0xEE, 0x8E, 0xE8, 0x88, 0xEE, 0x8E, 0x88, 0xE8, 0xE8, 0xE8, 0x88, 0xE8, 0x80},                                           // Casa 1
    {0xEE, 0x8E, 0xE8, 0x88, 0xEE, 0x8E, 0x88, 0xE8, 0xE8, 0xE8, 0x88, 0x8E, 0x80},                                           // Casa 2
    {0x37, 0x17, 0x77, 0x71, 0x71, 0x71, 0x11, 0x17, 0x17, 0x17, 0x77, 0x71, 0x17, 0x11, 0x11, 0x71, 0x71, 0x11, 0x11, 0x00}, // Javi 1
    {0x37, 0x17, 0x77, 0x71, 0x71, 0x71, 0x11, 0x17, 0x17, 0x71, 0x77, 0x71, 0x17, 0x11, 0x11, 0x71, 0x71, 0x11, 0x11, 0x00}, // Javi 2
    {0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0,
     0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA,
     0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0,
     0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0,
     0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA,
     0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0,
     0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA,
     0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0,
     0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA,
     0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0}, // Piso 1
    {0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0,
     0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA,
     0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0,
     0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0,
     0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA,
     0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0,
     0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA,
     0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0,
     0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA,
     0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0xAA, 0xAA, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0, 0xAA, 0xAA, 0x0, 0x0, 0x0, 0x0} // Piso 2
};

uint8_t currentChannel = 0;

void loop() {
  uint8_t groups[7] = {0, 0, 0, 1, 1, 2, 2};
  uint8_t channel = getChannel(currentChannel);
  uint8_t group = groups[channel];

  String channelNames[7] = {"None", "Casa 1", "Casa 2", "Javi 1", "Javi 2", "Piso 1", "Piso 2"};
  float frequencies[3] = {
      433.812, // Casa
      433.812, // Javi
      433.812  // Piso
  };
  float baudrates[3] = {
      3,    // Casa
      2.64, // Javi
      13.43 // Piso
  };
  bool needsPreamble[3] = {
      false, // Casa
      true,  // Javi
      false  // Piso
  };

  if (currentChannel != channel) {
    if (channel != 0) {
      ELECHOUSE_cc1101.setMHZ(frequencies[group]);
      ELECHOUSE_cc1101.setDRate(baudrates[group]);
    }
    currentChannel = channel;
  }

  if (channel != 0) {
    uint8_t *code = codes[channel - 1];
    uint8_t codeLength = codeLengths[channel - 1];
    uint8_t codeDelay = codeDelays[group];
    ELECHOUSE_cc1101.SendData(code, codeLength);

    delay(codeDelay);
  }
}
/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender

IRsendRaw mySender;

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

const int BUTTON_PINS_NUMBER = 8;
int BUTTON_PINS[BUTTON_PINS_NUMBER]={2, 4, 5, 6, 9, 10, 11, 12};

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int lastPressedButton = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  for (int i = 0; i < BUTTON_PINS_NUMBER; i++) {
    pinMode(BUTTON_PINS[i], INPUT);
  }

  digitalWrite(ledPin, LOW);
  
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  Serial.println(F("GO!"));
}

void send_raw(uint16_t raw_data, int len, char *info) {
   digitalWrite(ledPin, HIGH);
   mySender.send(raw_data, len, 36);
   Serial.println(info);
   digitalWrite(ledPin, LOW);
}

void send_generic(uint32_t data,  uint8_t numBits,
  uint16_t headMark, uint16_t headSpace, uint16_t markOne,
  uint16_t markZero, uint16_t spaceOne, uint16_t spaceZero,
  uint8_t kHz, bool stopBits, char *info) {
   digitalWrite(ledPin, HIGH);
   mySender.sendGeneric(data, numBits, headMark, headSpace, markOne, markZero, spaceOne, spaceZero, kHz, stopBits);
   delay(10);
   Serial.println(info);
   digitalWrite(ledPin, LOW);
}
        

/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */

// 0x4b36d32c 32
void send_Onkyo_onOff() {
  send_generic(0x4b36d32c, 32, 9058, 4448, 535, 562, 1720, 593, 38, true, "Onkyo - onOff");
}

// 0x4bb6708f 32
void send_Onkyo_cblSat() {
  send_generic(0x4bb6708f, 32, 8994, 4500, 567, 565, 1688, 565, 38, true, "Onkyo - cblSat");
}

// 0x4bb639c6 32
void send_Onkyo_pc() {
  send_generic(0x4bb639c6, 32, 9020, 4475, 565, 565, 1690, 565, 38, true, "Onkyo - pc");
}

// 0x976d609 29
void send_Onkyo_game() {
  send_generic(0x976d609, 29, 9020, 4495, 565, 565, 1690, 565, 38, true, "Onkyo - game");
}

// 0x4bb640bf 32
void send_Onkyo_volumePlus() {
  send_generic(0x4bb640bf, 32, 9009, 4480, 562, 560, 1693, 570, 38, true, "Onkyo - volumePlus");
}

// 0x4bb6c03f 32
void send_Onkyo_volumeMinus() {
  send_generic(0x4bb6c03f, 32, 9016, 4494, 565, 564, 1691, 567, 38, true, "Onkyo - volumeMinus");
}

// 0x20df10ef 32
void send_LG_onOff() {
  send_generic(0x20df10ef, 32, 8960, 4501, 506, 505, 1729, 610, 38, true, "LG - onOff");
}

// 0x20df8877 32
void send_LG_num1() {
  send_generic(0x20df8877, 32, 8975, 4500, 505, 505, 1730, 610, 38, true, "LG - num1");
}

// 0x-3abafdb1 36
void send_Horizon_onOff() {
  uint16_t raw_data[78] = {4492,4503,485,515,480,520,450,545,456,514,481,1519,476,1514,481,520,479,516,485,514,480,1516,480,514,481,1514,481,519,455,1516,480,515,480,520,475,4510,480,520,480,1515,480,515,480,1515,479,521,479,516,480,520,479,516,480,520,480,515,479,1516,454,521,480,514,481,1515,479,520,480,516,479,1515,480,1515,480,1515,481,1514,455,10000};
  send_raw(raw_data, 78, "Horizon - onOff");
}

// 0x-3aba3a0f 36
void send_Horizon_channelPlus() {
  uint16_t raw_data[78] = {4500,4500,480,520,480,520,480,520,480,520,480,1520,480,1520,480,520,480,520,480,520,480,1520,480,520,480,1520,480,520,480,1520,480,520,480,520,480,4510,480,520,480,1520,480,520,480,1520,480,1520,480,1520,480,520,480,520,480,520,480,1520,480,520,480,1520,480,1520,480,1520,480,1520,480,1520,480,520,480,520,480,520,480,1520,460,10000};
  send_raw(raw_data, 78, "Horizon - channelPlus");
}

// 0x-3abada8f 36
void send_Horizon_channelMinus() {
  uint16_t raw_data[78] = {4500,4500,480,520,480,520,480,520,480,520,480,1520,480,1520,480,520,480,520,480,520,480,1520,480,520,480,1520,480,520,480,1520,480,520,480,520,480,4510,480,520,480,1520,480,520,480,1520,480,520,480,520,480,1520,480,520,480,520,480,1520,480,520,480,1520,480,520,480,1520,480,1520,480,1520,480,520,480,520,480,520,480,1520,460,10000};
  send_raw(raw_data, 78, "Horizon - channelMinus");
}

void loop() {
  lastPressedButton = 0;
  for (int i = 0; i < BUTTON_PINS_NUMBER; i++) {
    if (digitalRead(BUTTON_PINS[i]) == HIGH) {
      Serial.print("BTN: ");
      lastPressedButton = BUTTON_PINS[i];
      Serial.println(lastPressedButton);
      break;
    }
  }

  if(lastPressedButton == 2) {
      send_Horizon_onOff();
      send_LG_onOff();
      send_Onkyo_cblSat();
      send_LG_onOff();
      delay(200);
      send_LG_num1();
      delay(100);
      send_LG_num1();
  } else if(lastPressedButton == 4) {
      send_Horizon_onOff();
      send_LG_onOff();
      send_Onkyo_onOff();
  } else if(lastPressedButton == 5) {
      send_Onkyo_cblSat();
      //send_Onkyo_pc();
  } else if(lastPressedButton == 6) {
      send_Onkyo_cblSat();
  } else if(lastPressedButton == 9) {
      send_Horizon_channelPlus();
  } else if(lastPressedButton == 10) {
      send_Horizon_channelMinus();
  } else if(lastPressedButton == 11) {
      send_Onkyo_volumePlus();
  } else if(lastPressedButton == 12) {
      send_Onkyo_volumeMinus();
  }

  if (lastPressedButton != 0) {
       delay(200);
  }
}
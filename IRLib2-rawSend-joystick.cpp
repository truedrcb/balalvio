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

/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */

void send_Onkyo_onOff() {
        uint16_t raw_data[68] = {9058,4448,565,590,590,1665,590,515,615,515,565,1715,537,593,590,1640,615,1642,558,590,540,595,590,1640,560,1720,535,595,535,1695,560,1715,535,555,630,1665,590,1665,585,520,560,1720,537,593,590,540,535,1675,580,1715,540,590,592,513,565,1690,615,540,540,1715,535,1720,590,515,562,593,590,10000};
        send_raw(raw_data, 68, "Onkyo - onOff");
}

void send_Onkyo_cblSat() {
        uint16_t raw_data[68] = {8994,4500,565,565,565,1690,560,571,559,572,558,1695,560,570,562,1688,565,1690,565,1690,565,565,565,1690,565,1690,560,570,565,1690,565,1690,567,563,561,569,565,1692,563,1690,560,1695,567,563,565,565,565,565,565,565,565,1690,565,565,560,570,565,565,565,1691,564,1690,565,1690,567,1688,565,10000};
        send_raw(raw_data, 68, "Onkyo - cblSat");
}

void send_Onkyo_pc() {
        uint16_t raw_data[68] = {9020,4475,585,565,565,1690,565,565,565,565,565,1690,565,565,565,1690,565,1690,565,1670,585,565,565,1690,565,1690,560,570,565,1690,560,1695,560,570,560,570,560,570,560,1695,560,1695,560,1690,565,570,560,570,560,1690,565,1690,565,1690,565,565,565,565,565,570,560,1690,565,1690,565,565,565,10000};
        send_raw(raw_data, 68, "Onkyo - pc");
}

void send_Onkyo_game() {
        uint16_t raw_data[62] = {9020,4495,565,565,565,1690,565,565,565,565,565,1690,565,565,565,1685,570,1685,570,1685,565,565,565,1690,565,1690,565,565,565,1685,570,1685,565,565,565,1690,565,565,565,1685,570,1685,570,560,570,560,570,560,570,560,570,560,570,1685,565,565,565,565,565,1690,565,10000};
        send_raw(raw_data, 62, "Onkyo - game");
}

void send_Onkyo_volumePlus() {
        uint16_t raw_data[68] = {9009,4480,580,595,535,1695,555,570,565,570,560,1715,536,549,582,1693,560,1695,560,1690,565,570,560,1690,560,1695,560,570,560,1695,560,1695,562,568,560,570,560,1692,558,572,563,565,566,549,577,573,562,568,560,590,540,1690,560,570,560,1695,561,1694,560,1720,535,1692,563,1690,562,1693,560,10000};
        send_raw(raw_data, 68, "Onkyo - volumePlus");
}

void send_Onkyo_volumeMinus() {
        uint16_t raw_data[68] = {9016,4494,565,566,565,1690,565,564,565,565,566,1689,566,564,566,1689,563,1688,564,1693,562,565,566,1689,563,1693,564,565,565,1690,566,1689,561,565,564,1696,560,1691,563,568,563,565,565,569,562,569,559,571,560,565,564,572,564,567,562,1691,560,1689,565,1690,566,1690,564,1690,565,1691,562,10000};
        send_raw(raw_data, 68, "Onkyo - volumeMinus");
}

void send_LG_onOff() {
        uint16_t raw_data[68] = {8960,4501,509,607,508,610,510,1725,510,610,505,610,510,610,510,610,505,615,505,1730,505,1730,507,608,510,1731,504,1730,505,1730,505,1730,505,1730,505,616,504,612,508,610,505,1730,505,615,505,610,505,615,505,610,510,1732,503,1730,505,1730,505,610,510,1705,530,1730,505,1730,506,1729,505,10000};
        send_raw(raw_data, 68, "LG - onOff");
}

void send_LG_num1() {
        uint16_t raw_data[68] = {8975,4500,510,610,505,610,510,1725,510,610,505,615,505,610,510,610,505,615,505,1730,505,1730,505,610,510,1725,510,1730,505,1730,505,1730,505,1730,505,1730,505,615,505,610,510,610,505,1730,505,615,505,610,510,610,505,615,505,1725,510,1730,505,1730,505,610,510,1730,505,1730,505,1730,505,10000};
        send_raw(raw_data, 68, "LG - num1");
}

void send_Horizon_onOff() {
        uint16_t raw_data[78] = {4492,4503,485,515,480,520,450,545,456,514,481,1519,476,1514,481,520,479,516,485,514,480,1516,480,514,481,1514,481,519,455,1516,480,515,480,520,475,4510,480,520,480,1515,480,515,480,1515,479,521,479,516,480,520,479,516,480,520,480,515,479,1516,454,521,480,514,481,1515,479,520,480,516,479,1515,480,1515,480,1515,481,1514,455,10000};
        send_raw(raw_data, 78, "Horizon - onOff");
}

void send_Horizon_channelPlus() {
        uint16_t raw_data[78] = {4500,4500,480,520,480,520,480,520,480,520,480,1520,480,1520,480,520,480,520,480,520,480,1520,480,520,480,1520,480,520,480,1520,480,520,480,520,480,4510,480,520,480,1520,480,520,480,1520,480,1520,480,1520,480,520,480,520,480,520,480,1520,480,520,480,1520,480,1520,480,1520,480,1520,480,1520,480,520,480,520,480,520,480,1520,460,10000};
        send_raw(raw_data, 78, "Horizon - channelPlus");
}

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
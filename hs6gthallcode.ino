// Hall sensor sim shifter 5+1
// Tested with HS6-GT https://www.racedepartment.com/threads/hs6-gt-%E2%80%93-diy-h-pattern-shifter.176550/
// Arduino Micro / Leonardo only (tested with arduino micro)
// by Jakub Moskalik
// 11.03.2024
//--------------------------------------------------------------------
#include <Joystick.h>

//GEARS PINOUT
const int G1 = 8;
const int G2 = A3;
const int G3 = 9;
const int G4 = A2;
const int G5 = A0;
const int G6 = A1;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK, 6, 0,
                   false, false, false, false, false, false,
                   false, false, false, false, false);

bool checkPin(unsigned int pin) {
  const int numReadings = 5;
  int sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += digitalRead(pin);
    delay(5);
  }
  return (sum == 0);
}

void checkGear(int pin, int button, bool debug = false) {
  if (debug == true) {
    Serial.println(pin);
  }
  checkPin(pin) ? Joystick.pressButton(button) : Joystick.releaseButton(button);
}

void setup() {
//  Serial.begin(9600) // Uncomment for debugging
  pinMode(G1, INPUT);
  pinMode(G2, INPUT);
  pinMode(G3, INPUT);
  pinMode(G4, INPUT);
  pinMode(G5, INPUT);
  pinMode(G6, INPUT);
  
  //TURNS OFF ONBOARD LEDs
  pinMode(LED_BUILTIN_TX,INPUT);
  pinMode(LED_BUILTIN_RX,INPUT);
  
  Joystick.begin();
}

void loop() {
  // GEARS 1-6 CHECK
  checkGear(G1, 0);
  checkGear(G2, 1);
  checkGear(G3, 2);
  checkGear(G4, 3);
  checkGear(G5, 4);
  checkGear(G6, 5);
}
// Hall sensor sim shifter 6+1
// Tested with HS6-GT https://www.racedepartment.com/threads/hs6-gt-%E2%80%93-diy-h-pattern-shifter.176550/
// Arduino Micro / Leonardo only
// by Jakub Moskalik
// 11.03.2024
//--------------------------------------------------------------------
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_JOYSTICK, 7, 0,
                   false, false, false, false, false, false,
                   false, false, false, false, false);
//GEARS PINOUT
const int G1 = 8;
const int G2 = A3;
const int G3 = 9;
const int G4 = A2;
const int G5 = A0;
const int G6 = A1;
#define REV_GEAR_TIME = 2000 // Time in ms to shift into reverse

void setup() {
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
  // REVERSE GEAR CHECK
  bool G_rev = checkRev(G6, REV_GEAR_TIME);
  
  if (G_rev && checkPin(G6)) {
    Joystick.pressButton(6);
    Joystick.releaseButton(5);
    delay(200);
  } else {
    Joystick.releaseButton(6);
  }
  // GEARS 1-6 CHECK
  checkPin(G1) ? Joystick.pressButton(0) : Joystick.releaseButton(0);
  checkPin(G2) ? Joystick.pressButton(1) : Joystick.releaseButton(1);
  checkPin(G3) ? Joystick.pressButton(2) : Joystick.releaseButton(2);
  checkPin(G4) ? Joystick.pressButton(3) : Joystick.releaseButton(3);
  checkPin(G5) ? Joystick.pressButton(4) : Joystick.releaseButton(4);
  
  if (G_rev = false && checkPin(G6)) {
    Joystick.pressButton(5);
  } else {
    Joystick.releaseButton(5);
  }
  delay(200);
}

bool checkPin(unsigned int pin) {
  const int numReadings = 20;
  int sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += digitalRead(pin);
    delay(5);
  }
  return (sum == 0);
}

bool checkRev(int pin, unsigned long time_window) {
  unsigned long start_time = millis();
  unsigned long current_time = start_time;

  while (current_time - start_time <= time_window) {
    if (checkPin(pin)) {
      return true;
    }
    current_time = millis();
  }
  return false;
}



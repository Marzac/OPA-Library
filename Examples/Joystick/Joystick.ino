/*
 * OPA Shield - fredslab.net
 * Controling the OPA shield using an Atari / Amiga
 * gamepad or joystick (DB9 connector)
 * 10/07/16
 */
 
#include <OPA.h>
 
OPA opa;

/** Hardware setup */
void setup()
{
  opa.enable();
  
  pinMode(6, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(14, INPUT);

  opa.loadInternal(OPA_PROGRAM_0, 0);
  opa.loadInternal(OPA_PROGRAM_1, 21);
  opa.loadInternal(OPA_PROGRAM_2, 22);
  opa.loadInternal(OPA_PROGRAM_3, 23);
  digitalWrite(6, 1);
}

/** Main program */
bool lbb;
bool lbc;
int lnb = 0;
int lnc = 0;

void loop()
{
  bool bb = digitalRead(9);
  bool bc = digitalRead(10);
  
  int up = digitalRead(11) ? 0 : 1;
  int down = digitalRead(12) ? 0 : 1;
  int left = digitalRead(13) ? 0 : 1;
  int right = digitalRead(14) ? 0 : 1;

  if (!bb && lbb) {
    lnb = 60 - 5 * down - 3 * left;
    opa.noteOn(OPA_PROGRAM_0, lnb);
  }
    
  if (bb && !lbb) {
    opa.noteOff(OPA_PROGRAM_0, lnb);
  }

  if (!bc && lbc) {
    lnc = 60 - 5 * down - 3 * left;
    opa.noteOn(OPA_PROGRAM_0, lnc);
  }
  if (bc && !lbc) {
    opa.noteOff(OPA_PROGRAM_0, lnc);
  }

  lbb = bb;
  lbc = bc;
  
  delay(10);
}

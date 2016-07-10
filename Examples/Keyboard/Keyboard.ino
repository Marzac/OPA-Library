/*
 * OPA Shield - fredslab.net
 * Controling the OPA shield with a MIDI
 * compatible controler
 * 10/07/16
 */
 
#include <SoftwareSerial.h>
#include <OPA.h>

OPA opa;
SoftwareSerial midiSerial(8,9);

void setup()
{
  midiSerial.begin(31250);
  
  opa.enable();
  opa.loadInternal(OPA_PROGRAM_0, 0);
  opa.loadInternal(OPA_PROGRAM_1, 1);

  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A0, 0);
  digitalWrite(A2, 1);
  digitalWrite(A3, 0);
  digitalWrite(A5, 1);
}

/** Main program */
byte data[5];
byte offset = 0;

void loop()
{
  if (midiSerial.available()) {
    byte d = midiSerial.read();
    if (d & 0x80) offset = 0;
    data[offset++] = d;
  }

  int p1 = analogRead(1) >> 2;
  int p2 = analogRead(4) >> 2;
  
  opa.writeOperatorParam(OPA_PROGRAM_0, OPA_OPERATOR_2, OPA_OP_VOLUME, p1);
  opa.writeOperatorParam(OPA_PROGRAM_0, OPA_OPERATOR_0, OPA_OP_ENVRELEASE, p2);
  opa.writeOperatorParam(OPA_PROGRAM_0, OPA_OPERATOR_1, OPA_OP_ENVRELEASE, p2);

  if (offset == 3) {
    if (data[0] == 0x90) {
      if (data[2] != 0) {
        opa.noteOn(OPA_PROGRAM_0, data[1]);
        opa.noteOn(OPA_PROGRAM_1, data[1]);
      }else{
        opa.noteOff(OPA_PROGRAM_0, data[1]);
        opa.noteOff(OPA_PROGRAM_1, data[1]);
      }
      offset = 1;
    }else if (data[0] == 0x80) {
      opa.noteOff(OPA_PROGRAM_0, data[1]);
      opa.noteOff(OPA_PROGRAM_1, data[1]);
      offset = 1;
    }
  }
  delay(1);
 }

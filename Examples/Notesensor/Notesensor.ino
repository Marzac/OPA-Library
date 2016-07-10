/*
 * OPA Shield - fredslab.net
 * Controling the OPA shield with touch sensors
 * 10/07/16
 */
 
#include <OPA.h>

OPA opa;

/** Hardware setup */
void setup()
{
  opa.enable();
    
  opa.loadInternal(OPA_PROGRAM_0, 20);
  opa.loadInternal(OPA_PROGRAM_1, 21);
  opa.loadInternal(OPA_PROGRAM_2, 22);
  opa.loadInternal(OPA_PROGRAM_3, 23);
}

/** Main program */
void loop()
{
  int s1 = analogRead(5);
  int s2 = analogRead(4);
  opa.writeOperatorParam(OPA_PROGRAM_0, OPA_OPERATOR_1, OPA_OP_VOLUME, 20 + (s1 >> 2));
  opa.writeOperatorParam(OPA_PROGRAM_0, OPA_OPERATOR_2, OPA_OP_VOLUME, 20 + (s2 >> 2));
  opa.noteOn(OPA_PROGRAM_0, 60);
  delay(300);
  opa.noteOff(OPA_PROGRAM_0, 60);
  delay(300);
}


/*
 * OPA Shield
 * fredslab.net
 * Editor bridge sketch
 * 11/02/2016
 */
 
/** OPA shield pin mapping */
#define OPA_TX     0
#define OPA_RX     1
#define OPA_CS1    2
#define OPA_CS2    3
#define OPA_SWAP   4
#define OPA_RESET  7

/** Hardware setup */
void setup()
{
  pinMode(OPA_TX, INPUT);
  pinMode(OPA_RX, INPUT);
  pinMode(OPA_CS, OUTPUT);
  pinMode(OPA_SWAP, OUTPUT);

  digitalWrite(OPA_CS, 0);
  digitalWrite(OPA_SWAP, 1);
}

/** Main program */
void loop()
{
}

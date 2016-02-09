/**
	fredslab.net : OPA Shield library for Arduino

    The MIT License (MIT)

    Source code copyright (c) 2013-2016 Frédéric Meslin / Thomas Hopper
    Email: fredericmeslin@hotmail.com
    Website: www.fredslab.net
    Twitter: @marzacdev

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
 
#include "OPA.h"
#include "Arduino.h"

/*****************************************************************************/
#define OPA_CS1_STATE(a) (a & 0x01)
#define OPA_CS2_STATE(a) ((a >> 1) & 0x01)
		
/*****************************************************************************/
OPA::OPA() :
	address(OPA_ADDRESS_0),
	error(OPA_ERROR_NONE)
{
	initPins();
}

OPA::OPA(OPA_ADDRESSES address) :
	address(address),
	error(OPA_ERROR_NONE)
{
	initPins();
}

/*****************************************************************************/
void OPA::initPins()
{
	pinMode(OPA_TX_PIN, INPUT);
	pinMode(OPA_RX_PIN, INPUT);
	pinMode(OPA_CS1_PIN, OUTPUT);
	pinMode(OPA_CS2_PIN, OUTPUT);
	pinMode(OPA_SWAP_PIN, OUTPUT);
	pinMode(OPA_RESET_PIN, OUTPUT);
	
	digitalWrite(OPA_CS1_PIN, 1);
	digitalWrite(OPA_CS2_PIN, 1);
	digitalWrite(OPA_SWAP_PIN, 0);
	digitalWrite(OPA_RESET_PIN, 0);
}
	
/*****************************************************************************/
void OPA::enable()
{
	digitalWrite(OPA_CS1_PIN, OPA_CS1_STATE(address));
	digitalWrite(OPA_CS2_PIN, OPA_CS2_STATE(address));
	Serial.begin(OPA_BAUDRATE);
	Serial.setTimeout(OPA_SERIAL_TIMEOUT);
	clearErrors();
}

void OPA::disable()
{
	Serial.end();
	digitalWrite(OPA_CS1_PIN, 1);
	digitalWrite(OPA_CS2_PIN, 1);
}

/*****************************************************************************/
void OPA::reset()
{
	digitalWrite(OPA_RESET_PIN, 1);
	delay(2);
	digitalWrite(OPA_RESET_PIN, 0);
	delay(2);
	error = OPA_ERROR_NONE;
}

/*****************************************************************************/
void OPA::noteOn(OPA_PROGRAMS program, uint8_t note)
{
	char buffer[4];
    buffer[0] = OPA_CODE_NOTEON;
    buffer[1] = program;
    buffer[2] = note;
    buffer[3] = 0;
	Serial.write(buffer, 4);
}

void OPA::noteOff(OPA_PROGRAMS program, uint8_t note)
{
	char buffer[4];
    buffer[0] = OPA_CODE_NOTEOFF;
    buffer[1] = program;
    buffer[2] = note;
    buffer[3] = 0;
	Serial.write(buffer, 4);
}

void OPA::allNotesOff(OPA_PROGRAMS program)
{
	char buffer[2];
    buffer[0] = OPA_CODE_ALLNOTESOFF;
    buffer[1] = program;
	Serial.write(buffer, 2);
}

void OPA::allSoundsOff()
{
	char buffer[2];
    buffer[0] = OPA_CODE_ALLSOUNDSOFF;
	Serial.write(buffer, 1);
}

/*****************************************************************************/
void OPA::pitchBend(OPA_PROGRAMS program, int8_t coarse, int8_t fine)
{
    char buffer[4];
    buffer[0] = OPA_CODE_PITCHBEND;
    buffer[1] = program;
    buffer[2] = coarse;
    buffer[3] = fine;
	Serial.write(buffer, 4);
}

/*****************************************************************************/
void OPA::writeParameter(OPA_PROGRAMS program, uint8_t parameter, uint8_t value)
{
	char buffer[4];
    buffer[0] = OPA_CODE_PARAMWRITE;
	buffer[1] = program;
	buffer[2] = parameter;
    buffer[3] = value;
	Serial.write(buffer, 4);
}

uint8_t OPA::readParameter(OPA_PROGRAMS program, uint8_t parameter)
{
/** Send a request */
	char buffer[4];
    buffer[0] = OPA_CODE_PARAMREAD;
	buffer[1] = program;
	buffer[2] = parameter;
    buffer[3] = 0;
	Serial.write(buffer, 4);
	
/** Check the reply */
	uint8_t len = Serial.readBytes(buffer, 4);
	if (len == 4) {
		if (buffer[0] == OPA_CODE_PARAMWRITE)
			return buffer[3];
		error = OPA_ERROR_BADREPLY;
		return 0;
	}
	error = OPA_ERROR_TIMEOUT;
	return 0;
}

/*****************************************************************************/
void OPA::writeProgram(OPA_PROGRAMS program, OpaProgram &programData)
{

}

void OPA::readProgram(OPA_PROGRAMS program, OpaProgram &programData)
{
}

/*****************************************************************************/	
void OPA::storeProgram(OPA_PROGRAMS program, int slot)
{
}

void OPA::loadProgram(OPA_PROGRAMS program, int slot)
{
}

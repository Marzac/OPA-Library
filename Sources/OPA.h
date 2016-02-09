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
 
#ifndef OPA_H
#define OPA_H

#include <stddef.h>
#include <stdint.h>

/*****************************************************************************/
/** OPA shield configuration */
	const int OPA_BAUDRATE = 9600;			/** Communication baudrate in bauds */
	const int OPA_SERIAL_TIMEOUT = 500;		/** Communication timeout when reading */
 
/** OPA shield pin-mapping */
	const int OPA_TX_PIN = 0;
	const int OPA_RX_PIN = 1;
	const int OPA_CS1_PIN = 2;
	const int OPA_CS2_PIN = 3;
	const int OPA_SWAP_PIN = 4;
	const int OPA_RESET_PIN = 7;

	typedef enum{
	} OPA_PARAMETERS;
	
/*****************************************************************************/
	typedef enum{
		OPA_CODE_STATUS			= 0,
		OPA_CODE_NOTEON			= 1,
		OPA_CODE_NOTEOFF		= 2,
		OPA_CODE_ALLNOTESOFF	= 3,
		OPA_CODE_ALLSOUNDSOFF	= 4,
		OPA_CODE_PARAMWRITE		= 5,
		OPA_CODE_PARAMREAD		= 6,
		OPA_CODE_PROGRAMWRITE	= 7,
		OPA_CODE_PROGRAMREAD	= 8,
		OPA_CODE_PROGRAMSTORE	= 9,
		OPA_CODE_PROGRAMLOAD	= 10,
		OPA_CODE_PITCHBEND		= 11,
	}OPA_CODE_MESSAGES;

/*****************************************************************************/
	typedef enum{
		OPA_OP_DEFAULT      = 0,
		OPA_OP_ABSOLUTE     = 1,
		OPA_OP_SOFT_LOW     = 2,
		OPA_OP_HARD_LOW     = 4,
		OPA_OP_SOFT_HIGH    = 8,
		OPA_OP_HARD_HIGH    = 16,
	}OPA_OP_FLAGSBITS;

/*****************************************************************************/
	typedef struct{
		uint8_t volume;
		int8_t  coarse;
		int8_t  fine;
		uint8_t reserved1;
		uint8_t reserved2;
		uint8_t reserved3;
		uint8_t reserved4;
		uint8_t reserved5;
	}OpaGlobals;
	
/*****************************************************************************/
	typedef struct{
		uint8_t algorithm;
		int8_t  reserved;
		uint8_t volume;
		uint8_t panning;
	}OpaProgramParams;

	typedef struct{
		uint8_t volume;
		uint8_t coarse;
		int8_t  fine;
		uint8_t envAttack;
		uint8_t envDecay; 
		uint8_t envSusLevel;
		uint8_t envIniLevel;
		uint8_t envRelease;
		uint8_t LFOSpeed;
		uint8_t LFOAmount;
		uint8_t feedback;
		uint8_t flags;
		uint8_t reserved2;
		uint8_t reserved3;
		uint8_t reserved4;
		uint8_t reserved5;
	}OpaOperatorParams;

	typedef struct{
		OpaProgramParams params;
		OpaOperatorParams opParams[4];
	}OpaProgram;

/*****************************************************************************/
	typedef enum{
		OPA_ADDRESS_0 = 0,
		OPA_ADDRESS_1 = 1,
		OPA_ADDRESS_2 = 2,
	} OPA_ADDRESSES;

	typedef enum{
		OPA_PROGRAM_0 = 0,
		OPA_PROGRAM_1 = 1,
		OPA_PROGRAM_2 = 2,
		OPA_PROGRAM_3 = 3,
		OPA_PROGRAM_4 = 4,
		OPA_PROGRAM_5 = 5,
		OPA_PROGRAM_6 = 6,
		OPA_PROGRAM_7 = 4,
	} OPA_PROGRAMS;

	typedef enum{
		OPA_ERROR_NONE		= 0x00,
		OPA_ERROR_TIMEOUT	= 0x01,
		OPA_ERROR_BADREPLY	= 0x02,
	} OPA_ERRORS;
	
/*****************************************************************************/	
class OPA{
public:	
/** OPA class constructor **/
	OPA();
	OPA(OPA_ADDRESSES address);
	
	void enable();
	void disable();
	void reset();

/** Playing notes **/
	void noteOn(OPA_PROGRAMS program, uint8_t note);
	void noteOff(OPA_PROGRAMS program, uint8_t note);
	void pitchBend(OPA_PROGRAMS program, int8_t coarse, int8_t fine);
	void allNotesOff(OPA_PROGRAMS program);
	void allSoundsOff();
	
/** Reading & writing program parameters **/
	void writeParameter(OPA_PROGRAMS program, uint8_t parameter, uint8_t value);
	uint8_t readParameter(OPA_PROGRAMS program, uint8_t parameter);
	
/** Reading & writing full programs **/
	void writeProgram(OPA_PROGRAMS program, OpaProgram &programData);
	void readProgram(OPA_PROGRAMS program, OpaProgram &programData);
	
/** Store and load programs from internal memory **/
	void storeProgram(OPA_PROGRAMS program, int slot);
	void loadProgram(OPA_PROGRAMS program, int slot);

/** Error handling **/	
	void clearErrors() 
		{error = OPA_ERROR_NONE;}
		
	OPA_ERRORS getError()
		{return error;}
	
private:
	OPA_ADDRESSES address;
	OPA_ERRORS error;
	
	void initPins();
};

#endif
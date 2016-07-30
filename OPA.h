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
	
	Version 1.0, 30/07/2016
*/

#ifndef OPA_H
#define OPA_H

#include <stddef.h>
#include <stdint.h>

/*****************************************************************************/
/** Arduino board in use */
	#define ARDUINO_UNO
	//#define ARDUINO_MEGA
	//#define ARDUINO_LEONARDO
	
/** OPA shield configuration */
	const unsigned int OPA_BAUDRATE	= 57600;	/** Communication baudrate in bauds */
	const int OPA_SERIAL_TIMEOUT	= 500;		/** Communication timeout when reading */

/** OPA chip properties */
	const int OPA_MAX_SLOTS 		= 104;		/** Number of program slots in internal memory */

	const int OPA_PROGS_NB			= 8;		/** Number of programs in RAM */
	const int OPA_GLOBAL_PARAMS_NB	= 8;		/** Number of parameters in global configuration */
	const int OPA_PROGS_PARAMS_NB	= 12;		/** Number of parameters in each program */
	const int OPA_OP_PARAMS_NB		= 16;		/** Number of parameters in each operator */
	const int OPA_KIT_SAMPLES_NB	= 32;		/** Number of samples in kit */

	const int OPA_ALLPROGS_ID		= 255;

/** OPA shield pin-mapping */
	const int OPA_TX_PIN 			= 0;
	const int OPA_RX_PIN 			= 1;
	const int OPA_CS1_PIN 			= 2;
	const int OPA_CS2_PIN 			= 3;
	const int OPA_SWAP_PIN 			= 4;
	const int OPA_RESET_PIN 		= 7;

/*****************************************************************************/
	typedef enum{
		OPA_CODE_VERSION			= 0,
		OPA_CODE_NOTEON				= 1,
		OPA_CODE_NOTEOFF			= 2,
		OPA_CODE_ALLNOTESOFF		= 3,
		OPA_CODE_ALLSOUNDSOFF		= 4,
		OPA_CODE_FMPARAMWRITE		= 5,
		OPA_CODE_FMPARAMREAD		= 6,
		OPA_CODE_GLOBALSPARAMWRITE	= 7,
		OPA_CODE_GLOBALSPARAMREAD	= 8,
		OPA_CODE_PROGRAMWRITE		= 9,
		OPA_CODE_PROGRAMREAD		= 10,
		OPA_CODE_GLOBALSWRITE		= 11,
		OPA_CODE_GLOBALSREAD		= 12,
		OPA_CODE_INTERNALSTORE		= 13,
		OPA_CODE_INTERNALLOAD		= 14,
		OPA_CODE_INTERNALWRITE		= 15,
		OPA_CODE_INTERNALREAD		= 16,
		OPA_CODE_PITCHBEND			= 17,
		OPA_CODE_KITPARAMWRITE		= 18,
		OPA_CODE_KITPARAMREAD		= 19,
		OPA_CODE_KITWRITE			= 20,
		OPA_CODE_KITREAD			= 21,
	}OPA_CODE_MESSAGES;


/*****************************************************************************/
	typedef enum{
		OPA_GLOBAL_PROTECT		= 1,
		OPA_GLOBAL_MUTEFM		= 2,
		OPA_GLOBAL_MUTEKIT		= 4,
		OPA_GLOBAL_DEFAULT		= OPA_GLOBAL_PROTECT,
	}OPA_GLOBAL_FLAGBITS;

	typedef enum{
		OPA_PROGRAM_STEALING	= 1,
		OPA_PROGRAM_MUTED		= 2,
		OPA_PROGRAM_DEFAULT		= PROGRAM_STEALING,
	}OPA_PROGRAM_FLAGBITS;

	typedef enum{
		OPA_OP_ABSOLUTE			= 1,
		OPA_OP_SOFT_LOW			= 2,
		OPA_OP_HARD_LOW			= 4,
		OPA_OP_SOFT_HIGH		= 8,
		OPA_OP_HARD_HIGH		= 16,
		OPA_OP_MUTED			= 32,
		OPA_OP_DEFAULT			= 0,
	}OPA_OP_FLAGBITS;

/*****************************************************************************/
	typedef struct{
		uint8_t volume;
		int8_t  coarse;
		int8_t  fine;
		uint8_t flags;
		uint8_t fmVolume;
		uint8_t kitVolume;
		uint8_t reserved1;
		uint8_t reserved2;
	}OpaGlobals;

/*****************************************************************************/
	typedef struct{
		uint8_t name[8];
		uint8_t algorithm;
		uint8_t volume;
		uint8_t panning;
		uint8_t flags;
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
		uint8_t reserved1;
		uint8_t reserved2;
		uint8_t reserved3;
		uint8_t reserved4;
	}OpaOperatorParams;

	typedef struct{
		OpaProgramParams params;
		OpaOperatorParams opParams[4];
	}OpaProgram;

/*****************************************************************************/
	typedef struct{
		uint8_t volume;
		uint8_t panning;
		uint8_t decay;
		uint8_t reserved;
	}OpaKitParams;

	typedef struct{
		OpaKitParams params[OPA_KIT_SAMPLES_NB];
	}OpaKit;

/*****************************************************************************/
	typedef enum{
		OPA_ADDRESS_0			= 0,
		OPA_ADDRESS_1			= 1,
		OPA_ADDRESS_2			= 2,
	} OPA_ADDRESSES;

	typedef enum{
		OPA_PROGRAM_0			= 0,
		OPA_PROGRAM_1			= 1,
		OPA_PROGRAM_2			= 2,
		OPA_PROGRAM_3			= 3,
		OPA_PROGRAM_4			= 4,
		OPA_PROGRAM_5			= 5,
		OPA_PROGRAM_6			= 6,
		OPA_PROGRAM_7			= 7,
		OPA_PROGRAM_DRUMS		= 9,
		OPA_PROGRAM_ALL			= 255,
	} OPA_PROGRAMS;

	typedef enum{
		OPA_OPERATOR_0			= 0,
		OPA_OPERATOR_1			= 1,
		OPA_OPERATOR_2			= 2,
		OPA_OPERATOR_3			= 3,
	} OPA_OPERATORS;

	typedef enum{
		OPA_ERROR_NONE			= 0x00,
		OPA_ERROR_TIMEOUT		= 0x01,
		OPA_ERROR_BADREPLY		= 0x02,
		OPA_ERROR_BADPARAMETER	= 0x10,
	} OPA_ERRORS;

/*****************************************************************************/
	typedef enum{
		OPA_GLOBAL_VOLUME		= 0,
		OPA_GLOBAL_COARSE		= 1,
		OPA_GLOBAL_FINE			= 2,
		OPA_GLOBAL_FLAGS		= 3,
	} OPA_GLOBAL_PARAMETERS;

/*****************************************************************************/
	typedef enum{
		OPA_PROGRAM_NAME		= 0,
		OPA_PROGRAM_ALGORITHM	= 8,
		OPA_PROGRAM_VOLUME		= 9,
		OPA_PROGRAM_PANNING		= 10,
		OPA_PROGRAM_FLAGS		= 11,
	} OPA_PROGRAM_PARAMETERS;

	typedef enum{
		OPA_OP_VOLUME			= 0,
		OPA_OP_COARSE			= 1,
		OPA_OP_FINE				= 2,
		OPA_OP_ENVATTACK		= 3,
		OPA_OP_ENVDECAY			= 4,
		OPA_OP_ENVSUSTAINLEVEL	= 5,
		OPA_OP_ENVINITLEVEL		= 6,
		OPA_OP_ENVRELEASE		= 7,
		OPA_OP_LFOSPEED			= 8,
		OPA_OP_LFOAMOUNT		= 9,
		OPA_OP_FEEDBACK			= 10,
		OPA_OP_FLAGS			= 11,
	} OPA_OP_PARAMETERS;

	typedef enum{
		OPA_SAMPLE_VOLUME		= 0,
		OPA_SAMPLE_PANNING		= 1,
		OPA_SAMPLE_DECAY		= 2,
		OPA_SAMPLE_RESERVED		= 3,
	}OPA_KIT_PARAMETERS;

/*****************************************************************************/
class OPA{
public:
/** OPA class constructor **/
	OPA();
	OPA(OPA_ADDRESSES address);

	void enable();
	void disable();
	void reset();

/** Version / protection **/
	char * readVersion();
	void setMemoryProtection(bool protection);

/** Playing notes **/
	void noteOn(OPA_PROGRAMS program, uint8_t note, uint8_t fraction = 0, uint8_t nuance = 255);
	void noteOff(OPA_PROGRAMS program, uint8_t note, uint8_t fraction = 0, uint8_t nuance = 255);
	void pitchBend(OPA_PROGRAMS program, int8_t coarse, int8_t fine);
	void allNotesOff(OPA_PROGRAMS program);
	void allSoundsOff();

/** Reading & writing parameter helpers **/
	void writeGlobalParam(OPA_GLOBAL_PARAMETERS param, uint8_t value);
	void writeFMParam(OPA_PROGRAMS program, uint8_t param, uint8_t value);
	void writeOperatorParam(OPA_PROGRAMS program, OPA_OPERATORS op, OPA_OP_PARAMETERS param, uint8_t value);
	uint8_t writeKitParam(int sample, OPA_SAMPLE_PARAMETERS param, uint8_t value);

	uint8_t readGlobalParam(OPA_GLOBAL_PARAMETERS param);
	uint8_t readFMParam(OPA_PROGRAMS program, uint8_t param);
	uint8_t readOperatorParam(OPA_PROGRAMS program, OPA_OPERATORS op, OPA_OP_PARAMETERS param);
	uint8_t readKitParam(int sample, OPA_SAMPLE_PARAMETERS param);

/** Reading & writing full programs **/
	void writeGlobals(OpaGlobals &globalsData);
	void readGlobals(OpaGlobals &globalsData);
	void writeProgram(OPA_PROGRAMS program, OpaProgram &programData);
	void readProgram(OPA_PROGRAMS program, OpaProgram &programData);
	void writeKit(OpaKit &kitData);
	void readKit(OpaKit &kitData);

/** Store, load, write and read programs from internal memory **/
	void storeInternal(OPA_PROGRAMS program, uint8_t slot);
	void loadInternal(OPA_PROGRAMS program, uint8_t slot);
	void writeInternal(uint8_t slot, OpaProgram &programData);
	void readInternal(uint8_t slot, OpaProgram &programData);

/** Error handling **/
	void clearErrors()
		{error = OPA_ERROR_NONE;}

	OPA_ERRORS getErrors()
		{return error;}

private:
	OPA_ADDRESSES address;
	OPA_ERRORS error;

	void initPins();
};

#endif
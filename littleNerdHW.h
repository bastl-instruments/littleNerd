
#include "sekvojHW_settings.h"

#ifndef SEKVOJHW_H_
#define SEKVOJHW_H_

#include <IHWLayer.h>
#include <Arduino.h>


class sekvojHW : public IHWLayer {

enum TriggerState{ON,OFF};

public:

	// sets up all the pins, timers and SPI interface
	// call this before using any other method from this class
	void init(void(*buttonChangeCallback)(uint8_t number), void(*clockInCallback)());

	/***KNOBS***/

	//Disabled function in SEKVOJ
	virtual uint8_t getKnobValue(uint8_t index){return 0;};

	/***LEDS***/

	// set the state of a led
	virtual void setLED(uint8_t number, IHWLayer::LedState state);

	// set the state of a led
	virtual void setLED(uint8_t number, uint8_t number2, uint8_t number3 = 0) {}

	// print the state arrays to the Serial terminal
	void printLEDStates();


	/***BUTTONS***/

	// the the state of a button identified by its id
	virtual IHWLayer::ButtonState getButtonState(uint8_t number);

	// print the read button states to serial terminal
	void printButtonStates();
	/***TRIGGER***/
	void setTrigger(uint8_t number, TriggerState state, uint8_t pulseWidth=0);


	/***RAM***/

	// write a byte to the given address
	virtual void writeSRAM(long address, uint8_t data){}

	// write a number of bytes starting at the given address
	virtual void writeSRAM(long address, uint8_t* buf, uint16_t len){}

	// read the byte stored at the given address
	virtual uint8_t readSRAM(long address){return 0;}

	// read a number of bytes starting from the given address
	virtual void readSRAM(long address, uint8_t* buf, uint16_t len){}




	/**TIMING**/

	// the number of bastl cycles elapsed since startup
	// this number will overflow after some minutes; you have to deal with that in the layer above
	// using a longer datatype would prevent this but at the cost of longer computation time
	uint16_t getElapsedBastlCycles();

	// returns the relation between bastl cycles and seconds
	// this value is dependent on the hardware update frequency that you can set by a define
	// use this to map real time processes (like BMP) to bastlCycles
	uint16_t  getBastlCyclesPerSecond();




	// only called by ISR routine.
	// they would be declared private but this would prevent the ISR from accessing them
	// there are workarounds for this but as they come at a cost I just left it like this
	void isr_updateNextLEDRow();
	void isr_updateButtons();
	void isr_updateTriggerStates();
	void isr_updateClockIn();

	inline void incrementBastlCycles() {bastlCycles++;}

	/**EEPROM**/

	virtual void readEEPROM(uint8_t pageNumb, uint8_t* byteArray, uint16_t numbBytes){}
	virtual void readEEPROMDirect(uint16_t address, uint8_t* byteArray, uint16_t numbBytes){}
	virtual bool isEEPROMBusy(){return true;}


private:
	/**TIMING**/
	uint16_t bastlCycles;

	/**LEDS**/
	uint8_t ledStatesBeg[4];
	uint8_t ledStatesEnd[4];


	/**BUTTONS**/
	uint8_t newButtonStates[4];
	uint8_t buttonStates[4];
	void compareButtonStates();
	void (*buttonChangeCallback)(uint8_t number);
	void (*clockInCallback)();

	/**TRIGGERS**/
	uint8_t trigState;
	uint8_t triggerCountdown[8];





};




#endif

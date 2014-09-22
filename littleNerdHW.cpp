
/*** PERMANENT SETTINGS***/

#include "littleNerdHW_settings.h"


/*** ACTUAL CODE ***/

#include <Arduino.h>
#include "littleNerdHW.h"
#include <shiftRegisterFast.h>
#include <avr/pgmspace.h>

//#include <SdFat.h>

// Declaration of instance (for use in interrupt service routine)
littleNerdHW hardware;


#define UINT16_MAX 65535
#define MAX_ADDR 131067

// set by defines
static const uint8_t updateFreq = FREQ;
static const uint8_t blinkCompare[2] = {blinkDuty,blinkTotal};

// set by hardware
// cols are numbers of elements that are read 'at the same time'
// rows are multiplexed in time
static const uint8_t leds_cols = 8;
static const uint8_t leds_rows = 4;
static const uint8_t buttons_cols = 4;
static const uint8_t buttons_rows = 8;

static const uint8_t rowsTotal = 4; // for calculation of update frequency timer


//prog_uchar colorBit[NUMBER_OF_COLORS] PROGMEM = {

uint8_t colorBit[NUMBER_OF_COLORS]= {

  BLACK_BITS, RED_BITS,GREEN_BITS,BLUE_BITS,YELLOW_BITS,MAGENTA_BITS,CIAN_BITS,WHITE_BITS

};


unsigned char analogPin[6]={
  ANALOG_PIN_1, ANALOG_PIN_2, ANALOG_PIN_3,  ANALOG_PIN_4, ANALOG_PIN_5, ANALOG_PIN_6};

void littleNerdHW::init(void(*buttonChangeCallback)(uint8_t number),void(*clockInCallback)(uint8_t number)) {

	cli();

	shiftRegFast::setup();




	bit_dir_inp(INPUT_1);
	bit_dir_inp(INPUT_2);
	bit_dir_inp(BUTTON_PIN_1);
	bit_dir_inp(BUTTON_PIN_2);



	bit_dir_outp(LED_R_PIN);


	bit_set(INPUT_1);
	bit_set(INPUT_2);
	bit_set(BUTTON_PIN_1);
	bit_set(BUTTON_PIN_2);
	bit_set(LED_R_PIN);


	// store callback pointer for changed buttons
	 this->buttonChangeCallback = buttonChangeCallback;

	 this->clockInCallback = clockInCallback;

	// Disable Timer1 interrupt
	//TIMSK1 &= ~_BV(TOIE1);

	// TIMER 2
	TCCR2A = (1 << WGM21);  // turn on CTC mode
	TIMSK2 |= (1 << OCIE2A);// enable interrupt
	TCCR2B = B00000111;	    //prescaler = 1024
	OCR2A = (F_CPU/1024)/(updateFreq*rowsTotal);
	TCNT2  = 0;


	sei();
}


/**** LEDS ****/

void littleNerdHW::printLEDStates() {

}


void littleNerdHW::setLED(uint8_t number, IHWLayer::LedState state) {

}

void littleNerdHW::setColor(unsigned char _COLOR){

  //unsigned char _bits=pgm_read_word_near(colorBit + _COLOR)	;
	unsigned char _bits=colorBit[_COLOR];

  if(bitRead(_bits,0)) bit_set(LED_R_PIN);
  else bit_clear(LED_R_PIN);
  bitWrite(trigState,LED_G_PIN,bitRead(_bits,1));
  bitWrite(trigState,LED_B_PIN,bitRead(_bits,2));

}




/**** BUTTONS ****/


void littleNerdHW::isr_updateButtons() {


	newButtonStates[0]=bit_read_in(BUTTON_PIN_1);
	newButtonStates[1]=bit_read_in(BUTTON_PIN_2);

	compareButtonStates();

}

void littleNerdHW::compareButtonStates(){
	if(buttonChangeCallback!=0){

		for(int i=0;i<2;i++){
			if(buttonStates[i]!=newButtonStates[i]) buttonChangeCallback(i);
		}

	}
	for(int i=0;i<2;i++) buttonStates[i]=newButtonStates[i];


}


void littleNerdHW::printButtonStates() {
	for (uint8_t row=0; row<4; row++) {
		Serial.print("col "); Serial.print(row,DEC);Serial.print(": ");
		for (int8_t col=7; col>=0;col--) {
			if (bitRead(buttonStates[row],col)) {
				Serial.print("1");
			} else {
				Serial.print("0");
			}
		}
		Serial.println("");
	}
}

IHWLayer::ButtonState littleNerdHW::getButtonState(uint8_t number) {

	if (buttonStates[number] ) {
		return IHWLayer::UP;
	} else {
		return IHWLayer::DOWN;
	}

}


/**** TRIGGER ****/
void littleNerdHW::setTrigger(uint8_t number, littleNerdHW::TriggerState state, uint8_t pulseWidth){
	triggerCountdown[number]=pulseWidth;
		if(state==ON) bitWrite(trigState,number,1);
		if(state==OFF) bitWrite(trigState,number,0);
}

bool littleNerdHW::getTriggerState(uint8_t number){
		return bitRead(trigState,number);

};

uint8_t littleNerdHW::getKnobValue(uint8_t index){
	return knobValues[index];

}

void littleNerdHW::isr_updateKnobs(){
	static uint8_t knobCount;
	knobCount++;
	if(knobCount>=6) knobCount=0;
	knobValues[knobCount]=analogRead(analogPin[knobCount])>>2;

}

void littleNerdHW::isr_updateTriggerStates(){

	shiftRegFast::write_8bit(trigState);
	shiftRegFast::enableOutput();

	for(int i=0;i<6;i++){
		if(triggerCountdown[i]>0){
			if(triggerCountdown[i]==1) setTrigger(i,OFF,0);
			triggerCountdown[i]--;
		}
	}

}

void littleNerdHW::isr_updateClockIn(){
	if(clockInCallback!=0){
		static bool clockInState[2];
		bool newState=!bit_read_in(INPUT_1);
		if(newState && !clockInState[0]) clockInCallback(0);
		clockInState[0]=newState;

		newState=!bit_read_in(INPUT_2);
		if(newState && !clockInState[1]) clockInCallback(1);
		clockInState[1]=newState;
	}
}

/**** TIMING ****/

uint16_t littleNerdHW::getElapsedBastlCycles() {
	return bastlCycles;
}

uint16_t littleNerdHW::getBastlCyclesPerSecond() {
	return (F_CPU/1024)/OCR2A;
}


/**** INTERRUPT ****/

ISR(TIMER2_COMPA_vect) {


	//bit_set(PIN);
	hardware.incrementBastlCycles();
	hardware.isr_updateClockIn();
	hardware.isr_updateKnobs();
	hardware.isr_updateTriggerStates();
	hardware.isr_updateButtons();      // ~1ms
	//hardware.isr_updateNextLEDRow();   // ~84us

	//bit_clear(PIN);


}



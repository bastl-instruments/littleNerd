
#ifdef EXTERNAL_IDE

#include <Arduino.h>

int main(void) {

  init();
  setup();

  while(true) {
    loop();
  }
}

#endif

#include <portManipulations.h>
#include "littleNerdHW.h"
//#include <Player.h>
//#include <StepGenerator.h>
//#include <BPMConverter.h>
//#include <ArduinoMIDICommandProcessor.h>
//#include <PlayerSettings.h>
//#include <FlashStepMemory.h>
//#include <MIDI.h>
#include <SdFat.h>
//#include "MainMenuView.h"
//#include "InstrumentBar.h"
//#include <StepRecorder.h>
//#include <StepSynchronizer.h>

//MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

//Player * player;

//ArduinoMIDICommandProcessor * processor;
//FlashStepMemory * memory;
//PlayerSettings * settings;

//------------------------------------------------------------------------------
// global variables
Sd2Card card; // SD/SDHC card with support for version 2.00 features
SdVolume vol; // FAT16 or FAT32 volume
//SdFile root; // volume's root directory
//SdFile file; // current file

//MainMenuView mainMenu;
//StepGenerator stepper;
//StepRecorder recorder;
//InstrumentBar instrumentBar;
//SekvojButtonMap buttonMap;
//StepSynchronizer synchronizer;

extern littleNerdHW hardware;
/*
void stepperStep() {
	player->stepFourth();
	synchronizer.doStep();
}
*/
void noteOn(unsigned char note, unsigned char velocity, unsigned char channel) {
	/*
	 MIDI.sendNoteOn(35 + note, 127 ,channel);
	 unsigned char instrumentIndex;
	 if (settings->getDrumInstrumentIndexFromMIDIMessage(channel, note, instrumentIndex)) {
	 	instrumentBar.setInstrumentPlaying(instrumentIndex, true);
	 }
	 //hardware.clearDisplay();
	 //hardware.writeDisplayNumber(note * 10);
	  *
	  */
}

void noteOff(unsigned char note, unsigned char velocity, unsigned char channel) {
	/*
	MIDI.sendNoteOff(35 + note, velocity ,channel);
	//hardware.clearDisplay();
	//hardware.writeDisplayNumber(note * 10 + 1);
	unsigned char instrumentIndex;
	if (settings->getDrumInstrumentIndexFromMIDIMessage(channel, note, instrumentIndex)) {
		instrumentBar.setInstrumentPlaying(instrumentIndex, false);
	}
	*/
}

void midiNoteOnIn(unsigned char channel, unsigned char note, unsigned char velocity) {

	//recorder.recordMIDINote(channel, note/*, velocity << 3*/);
	//hardware.setLED(15 - channel, IHWLayer::ON);
	//hardware.setLED(35 - note, IHWLayer::ON);

}

void midiNoteOffIn() {

}

void test(uint8_t v) {
	//if(hardware.getButtonState(v) == IHWLayer::UP)

		//if(hardware.getButtonState(v)==IHWLayer::DOWN) hardware.setLED(v,IHWLayer::ON);
		//else hardware.setLED(v,IHWLayer::OFF);
}

void buttonCall(uint8_t v) {
	//if(hardware.getButtonState(v) == IHWLayer::UP)

		//if(hardware.getButtonState(v)==IHWLayer::DOWN) hardware.setLED(v,IHWLayer::ON);
		//else hardware.setLED(v,IHWLayer::OFF);
}

//enum ChannelMode{DIVIDER,FLOP_DIVIDER,MULTIPLIER,FILTER,OSC,PROBABILITY,GROOVE,EUCLID};
#define FILTER 0
#define DIVIDER 1
#define FLOP_DIVIDER 2
#define MULTIPLIER 3
#define OSC 4
#define PROBABILITY 5
#define GROOVE 6
#define EUCLID 7
#define DEFAULT_TRIGGER_LENGTH 4


uint8_t channelMode[6]={0,0,FLOP_DIVIDER,0,DIVIDER,OSC};
uint32_t clockInTime[6],lastClockInTime[6], channelTime[6], lastChannelTime[6];
uint16_t counter[6];
uint8_t parameter[6][2]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
//uint8_t parameter[6][2]={{0,0,0,0,0,0},{0,0,0,0,0,0}};


void delayTrigger(uint8_t _ch){


}

void clockInChannel(uint8_t _ch){
	lastClockInTime[_ch]=clockInTime[_ch];
	clockInTime[_ch]=millis();
	switch(channelMode[_ch]){
	case FILTER: //dodelat delay + otestovat

		if(hardware.getTriggerState(_ch)){
			if(parameter[_ch][1]==255) delayTrigger(_ch);
			else if(parameter[_ch][1]==0) hardware.setTrigger(_ch,littleNerdHW::ON,(parameter[_ch][0]>>2)+1);

		}
		else if(parameter[_ch][1]==255){
			delayTrigger(_ch);
		}
		else hardware.setTrigger(_ch,littleNerdHW::ON,(parameter[_ch][0]>>2)+1);
		break;
	case DIVIDER: //dodelat offset
		counter[_ch]++;
		//uint8_t divider=parameter[_ch][0]>>3;
		if((counter[_ch]%(parameter[_ch][0]>>3))==0){
			hardware.setTrigger(_ch,littleNerdHW::ON,DEFAULT_TRIGGER_LENGTH);
		}

		break;
	case FLOP_DIVIDER:
		counter[_ch]++;
		//uint8_t divider=parameter[_ch][0]>>3;
		if((counter[_ch]%(parameter[_ch][0]>>3))==0){
					if(hardware.getTriggerState(_ch)) hardware.setTrigger(_ch,littleNerdHW::OFF,0);
					else hardware.setTrigger(_ch,littleNerdHW::ON,0);
		}

		break;
	case MULTIPLIER: //vzit od martina
		break;
	case OSC:

		break;
	case PROBABILITY: //otestovat
		if(random(255)<=parameter[_ch][0]) hardware.setTrigger(_ch,littleNerdHW::ON,DEFAULT_TRIGGER_LENGTH);
		break;
	case GROOVE: //dodelat delay
		counter[_ch]++;
		if(counter[_ch]%2==1) delayTrigger(_ch);
		else hardware.setTrigger(_ch,littleNerdHW::ON,DEFAULT_TRIGGER_LENGTH);
		break;
	case EUCLID: //vymyslet a napsat algorytmus
		counter[_ch]++;

		break;

	}

}

void renderFilter(uint8_t _ch){
}
void renderDivider(uint8_t _ch){

}
void renderFlopDivider(uint8_t _ch){

}
void renderMultiplier(uint8_t _ch){

}
void renderOsc(uint8_t _ch){ //implement pulse width
	if((millis()-channelTime[_ch])>((255-parameter[_ch][0])<<2)){
		channelTime[_ch]=millis();
		if(hardware.getTriggerState(_ch)) hardware.setTrigger(_ch,littleNerdHW::OFF,0);
		else hardware.setTrigger(_ch,littleNerdHW::ON,0);
	}

}
void renderProbability(uint8_t _ch){

}
void renderGroove(uint8_t _ch){
}
void renderEuclid(uint8_t _ch){

}

void renderChannel(uint8_t _ch){
	switch(channelMode[_ch]){
	case FILTER:
		renderFilter(_ch);
		break;
	case DIVIDER:
		renderDivider(_ch);
		break;
	case FLOP_DIVIDER:
		renderFlopDivider(_ch);
		break;
	case MULTIPLIER:
		renderMultiplier(_ch);
		break;
	case OSC:
		renderOsc(_ch);
		break;
	case PROBABILITY:
		renderProbability(_ch);
		break;
	case GROOVE:
		renderGroove(_ch);
		break;
	case EUCLID:
		renderEuclid(_ch);
		break;

	}

}



uint8_t probability;
void renderClockIn(uint8_t in){
	hardware.setTrigger(in*4,littleNerdHW::ON,5);
	if(in==0){
		clockInChannel(0);
		clockInChannel(1);
		clockInChannel(2);

	}
	else if(in==1){
		clockInChannel(4);
		clockInChannel(5);


	}
}

void clockCall(uint8_t w) {

	if(w==0){
		renderClockIn(0);
	}

	static uint8_t nextClockFrom;
	if(nextClockFrom==w) renderClockIn(1);
	if(random(254)>=probability){
		nextClockFrom=1;
		Serial.println(1);
	}
	else {
		nextClockFrom=0;
		Serial.println(0);
	}

}



/*
void initFlashMemory(FlashStepMemory * memory) {
	DrumStep::DrumVelocityType inactiveSteps[4] = {DrumStep::OFF, DrumStep::OFF, DrumStep::OFF, DrumStep::OFF};
	DrumStep::DrumVelocityType activeSteps[4] = {DrumStep::NORMAL, DrumStep::OFF, DrumStep::OFF, DrumStep::OFF};
	DrumStep activeDrumStep(true, true, activeSteps);
	DrumStep emptyDrumStep(true, true , activeSteps);
	DrumStep muteDrumStep(true, true, inactiveSteps);

	// Initialize memory to empty
	for (unsigned char instrument = 0; instrument < 20; instrument++) {
		for (unsigned char step = 0; step < 64; step++) {
			memory->setDrumStep(instrument, 0, step, muteDrumStep);
		}
	}

	//Set some steps so something is playing
	DrumStep inactiveDrumStep(false, false, inactiveSteps);
	for (int i = 16; i < 64; i++) {
		memory->setDrumStep(0, 0, i, inactiveDrumStep);
	}
	for (int i = 0; i < 16; i++) {
		memory->setDrumStep(0, 0, i, emptyDrumStep);
	}
}
*/
void setup() {

	hardware.init(&buttonCall,&clockCall);

//	instrumentBar.init(&hardware, &buttonMap);
//	stepper.setTimeUnitsPerStep(BPMConverter::bpmToTimeUnits(100, hardware.getBastlCyclesPerSecond()));
//	stepper.setStepCallback(&stepperStep);
/*
	settings = new PlayerSettings();
	settings->setCurrentPattern(0);

	for (unsigned char i = 0; i < 10; i++) {
			settings->setInstrumentOn(InstrumentTypes::DRUM, i, i == 0);
			settings->setInstrumentChannel(InstrumentTypes::DRUM, i, 2);
			settings->setDrumInstrumentNote(i, i);
	}
	memory = new FlashStepMemory(&hardware);

	initFlashMemory(memory);

	processor = new ArduinoMIDICommandProcessor(&noteOn, &noteOff);
	player = new Player(memory, processor, settings, &synchronizer);
	Serial.end();
	MIDI.begin(0);
	MIDI.setHandleNoteOn(&midiNoteOnIn);

	hardware.clearDisplay();

	recorder.init(player, memory, settings);
	mainMenu.init(&hardware, player, & recorder, memory, settings, processor, &instrumentBar, &buttonMap);
	*/
	Serial.begin(9600);
}


uint32_t timeNow;
void loop() {
	probability=hardware.getKnobValue(3);


	for(int i=0;i<6;i++){
		renderChannel(i);
		parameter[i][0]=hardware.getKnobValue(i);
	}

	/*
	for(int i=0;i<32;i++) {
		if(hardware.getButtonState(i)==IHWLayer::UP) hardware.setLED(i,IHWLayer::ON);
		else hardware.setLED(i,IHWLayer::OFF);
	}
	hardware.printButtonStates();
	*/
	//MIDI.read();
	//stepper.update(hardware.getElapsedBastlCycles());
	//mainMenu.update();
}





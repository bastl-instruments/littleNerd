
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
#include "sekvojHW.h"
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

extern sekvojHW hardware;
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

		if(hardware.getButtonState(v)==IHWLayer::DOWN) hardware.setLED(v,IHWLayer::ON);
		else hardware.setLED(v,IHWLayer::OFF);
}

void buttonCall(uint8_t v) {
	//if(hardware.getButtonState(v) == IHWLayer::UP)

		if(hardware.getButtonState(v)==IHWLayer::DOWN) hardware.setLED(v,IHWLayer::ON);
		else hardware.setLED(v,IHWLayer::OFF);
}

void clockCall() {

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



void loop() {

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







/*** ACTUAL CODE ***/

#include <Arduino.h>
#include "eventMemory.h"


void eventMemory::init(void(*recEventNow)(uint8_t channel,uint8_t type, uint8_t cycles)) {
	this->recEventNow = recEventNow;
	numberOfEventsInBuffer=0;
}

void eventMemory::update(uint32_t time){
	if(state==RECORDING_STATE){


	}
	else if(state==LOOPING_STATE){

		if(recEventNow!=0){
				internalTime=time;
				if(numberOfEventsInBuffer!=0){


						while(time>=(timeBuffer[numberOfEventsPassed]+startTime)){
							if(time>=stopTime){
								startTime=time;
								stopTime+=stopTime;
								numberOfEventsPassed=0;
								return;
							}
							uint8_t channel=typeBuffer[numberOfEventsPassed]>>5;
							uint8_t type=0;
							uint8_t cycles=0;
							bitWrite(cycles,0,bitRead(typeBuffer[numberOfEventsPassed],2));
							bitWrite(cycles,1,bitRead(typeBuffer[numberOfEventsPassed],3));
							bitWrite(cycles,2,bitRead(typeBuffer[numberOfEventsPassed],4));

							bitWrite(type,0,bitRead(typeBuffer[numberOfEventsPassed],0));
							bitWrite(type,1,bitRead(typeBuffer[numberOfEventsPassed],1));

							recEventNow(channel,type, cycles);

							numberOfEventsPassed++;

						}

			}
			}

	}

}
void eventMemory::createEvent(uint8_t channel, uint8_t type, uint8_t cycles, uint32_t time){
	if(numberOfEventsInBuffer<BUFFER_SIZE){
		timeBuffer[numberOfEventsInBuffer]=time-startTime;
		typeBuffer[numberOfEventsInBuffer]=(cycles<<2) | (channel<<5) | type;
		numberOfEventsInBuffer++;
	}
/*
	Serial.print("  ");
	Serial.print(channel);
	Serial.print("  ");
	Serial.print(type);
	Serial.print("  ");
	Serial.print(time);
	Serial.println("  ");
*/

}

void eventMemory::fillBuffers(){
	for(uint8_t i=0;i<BUFFER_SIZE;i++){
		timeBuffer[i]=random(3000);
		typeBuffer[i]=random(255);
	}

}
void eventMemory::printBuffers(){
	numberOfEventsInBuffer=BUFFER_SIZE+1;
	Serial.println();
		Serial.println();
		Serial.println();
	for(uint8_t i=0;i<BUFFER_SIZE;i++){
		Serial.print(i);
		Serial.print(": ");
		Serial.print(timeBuffer[i]);
		Serial.print("  ");
		Serial.println(typeBuffer[i]);
	}
	Serial.println();
	Serial.println();
	Serial.println();
}

bool eventMemory::recording(){
	if(state==RECORDING_STATE) return true;
	else return false;
}
bool eventMemory::looping(){
	if(state==LOOPING_STATE) return true;
	else return false;
}

void eventMemory::startRecording(uint32_t time){
	state=RECORDING_STATE;
	startTime=time;

}
void eventMemory::loopRecorded(uint32_t time){
	state=LOOPING_STATE;
	stopTime=time+(time-startTime);
	startTime=time;
	numberOfEventsPassed=0;

}
void eventMemory::stopLoop(){
	state=STOP_STATE;
	clearBuffers();

}
void eventMemory::clearBuffers(){
	for (uint8_t i=0;i<BUFFER_SIZE;i++){
	 timeBuffer[i]=0;
	 typeBuffer[i]=0;
	}
	numberOfEventsInBuffer=0;
	numberOfEventsPassed=0;
}

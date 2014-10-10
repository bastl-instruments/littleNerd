
#include <Arduino.h>
#include "euclid.h"

void euclid::generateSequence( uint8_t fills, uint8_t steps){
	numberOfSteps=steps;
	if(fills>steps) fills=steps;
	if(fills<=steps){
	for(int i=0;i<32;i++) euclidianPattern[i]=false;
		if(fills!=0){
			euclidianPattern[0]=true;
			float coordinate=(float)steps/(float)fills;
			float whereFloat=0;
			while(whereFloat<steps){
				uint8_t where=(int)whereFloat;
				if((whereFloat-where)>=0.5) where++;
				euclidianPattern[where]=true;
				whereFloat+=coordinate;
			}
		}
	}
}

void euclid::generateRandomSequence( uint8_t fills, uint8_t steps){
	if(numberOfSteps!=steps && numberOfFills!=fills){
		numberOfSteps=steps;
		numberOfFills=fills;
		if(fills>steps) fills=steps;
		if(fills<=steps){
		for(int i=0;i<32;i++) euclidianPattern[i]=false;
			if(fills!=0){
				euclidianPattern[0]=true;
				for(int i=0;i<fills;i++){
					uint8_t where=random(steps);
					if(euclidianPattern[where]==false) euclidianPattern[where]=true;
					else{
					while(euclidianPattern[where]==false) {
						where=random(steps);
						if(euclidianPattern[where]==false) euclidianPattern[where]=true;
					}
					}
				}
			}
		}
	}
}


void euclid::rotate(uint8_t _steps){
	for(int i=0;i<_steps;i++){
		bool temp=euclidianPattern[numberOfSteps];
		for(int j=numberOfSteps;j>0;j--){
			euclidianPattern[j]=euclidianPattern[j-1];
		}
		euclidianPattern[0]=temp;
	}
}
bool euclid::getStep(uint8_t _step){
	return euclidianPattern[_step];
}
bool euclid::getCurrentStep(){
	return euclidianPattern[stepCounter];
}
void euclid::doStep(){
	if(stepCounter<(numberOfSteps-1)) stepCounter++;
	else stepCounter=0;
}

void euclid::resetSequence(){
	stepCounter=0;
}


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


extern sekvojHW hardware;
uint8_t latestButton;
uint8_t theButtonBefore;

uint8_t latestLED;
uint8_t theLEDBefore;

bool newEvent;


void callback(uint8_t v) {
	latestButton = v;

	if (hardware.getButtonState(v) == IHWLayer::DOWN) {
		newEvent = true;
	}
}




void setup() {

	hardware.init(callback);



	hardware.clearDisplay();


}



void loop() {

	if (newEvent) {

		newEvent = false;

		hardware.clearDisplay();
		hardware.writeDisplayNumber(latestButton);


		if (latestButton == 2) {
			theLEDBefore = latestLED;
			latestLED++;


		}

		if (latestButton == 3) {
			theLEDBefore = latestLED;
			latestLED--;
		}

		hardware.writeDisplayText(" ");
		hardware.writeDisplayNumber(latestLED);

		hardware.setLED(latestLED, IHWLayer::ON);
		hardware.setLED(theLEDBefore, IHWLayer::OFF);


	}



}





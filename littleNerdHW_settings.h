/*
 * sekvojHW-settings.h
 *
 *  Created on: 15.07.2014
 *      Author: user
 */

#ifndef SEKVOJHW_SETTINGS_H_
#define SEKVOJHW_SETTINGS_H_

// used pins
#define SHIFTREGISTER_SER C,5
#define SHIFTREGISTER_RCK B,1
#define SHIFTREGISTER_SRCK B,0

#define BUTTONCOL_0 C,3
#define BUTTONCOL_1 D,4
#define BUTTONCOL_2 D,2
#define BUTTONCOL_3 D,7

#define LEDCOL_0 C,4
#define LEDCOL_1 D,5
#define LEDCOL_2 D,3
#define LEDCOL_3 D,6

#define CLOCK_IN_PIN C,0

/*
#define BUTTON_PIN 	17
#define BUTTON_2_PIN 4
#define BUTTON_3_PIN 2
#define BUTTON_4_PIN 7


#define LED_PIN 18 //2
#define LED_2_PIN 5
#define LED_3_PIN 3
#define LED_4_PIN 6
*/



// the frequency at which the leds are updated.
// when set too high, resources are wasted, when set too low flikering occurs
// the value is in hertz and can be set from 16 to 255
#define FREQ 50


// properties of the led blinking
// total defines the frequency of one blink cycle
// duty defines when the led state is switched
// the values are relative to the frequency, so when you want dimming instead of blinking, you will need to increase that value
//  -------
//        |
//        |
//        -------------
//  0    duty         total

#define blinkTotal 2
#define blinkDuty  1



//
#define BUFFER_DEPTH 40


// debug Pin
#define PIN D,3

#endif /* SEKVOJHW_SETTINGS_H_ */

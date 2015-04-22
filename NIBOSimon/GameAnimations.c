/*
 * GameAnimations.c
 *
 * Created: 01.04.2015 08:07:10
 *  Author: LTI
 */ 
#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

#include "GameAnimations.h"

void ShowLostAnimation(){
	DrawCircle(800);
	DrawCircle(500);
	DrawCircle(200);		
}

void ShowEasterEggFoundAnimation(){	
		BlinkAll(300);
		DrawCircle(300);
		BlinkAll(200);
		BlinkAll(200);
		DrawCircle(100);
		DrawCircle(50);
		DrawCircle(25);
		BlinkAll(100);
		BlinkAll(100);
}


void ShowNextLevelAnimation(){	
		BlinkAll(500);
		delay(500);
		BlinkAll(500);
		delay(1000);
}

void DrawCircle(int aDelayMs){
		for (int led = 0; led<=3; led++)
			{
					led_set(led,1);
					delay(aDelayMs);
					led_set(led,0);
			}	
}

void BlinkAll(int aDelayMs){
		led_set(0,1);
		led_set(1,1);
		led_set(2,1);
		led_set(3,1);
		delay(aDelayMs);
		led_set(0,0);
		led_set(1,0);
		led_set(2,0);
		led_set(3,0);
}
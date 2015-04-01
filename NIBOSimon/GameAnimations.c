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
	
}


void ShowNextLevelAnimation(){
	
}

void DrawCircle(int aDelayMs){
	for (int led = 0; led<=3; led++)
	{
		led_set(led,1);
		delay(aDelayMs);
		led_set(led,0);
	}
}
#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

#include "Randomizer.h"

int main()
{
	led_init();//Led Initialization
	sens_init();//Fühler initialization
	int index = 0;//rename
	
	WaitForGameStartImput();
	
	//int actualLevel = 1;
	//int sequence[1000];
	
	//while(1)//Game loop
	//{
		//
	//}

}

int FillSequence(int aArray[1000]){
	
}
int WaitForGameStartImput()
{
	while(1){
		int left_Sens = sens_getLeft();
		int right_Sens = sens_getRight();
		if(left_Sens != 0){
			if(left_Sens == -1)
			{
				led_set(LED_L_YE, 1);
				led_set(LED_L_RD, 0);
			}
			if(left_Sens == 1)
			{
				led_set(LED_L_YE, 0);
				led_set(LED_L_RD, 1);
			}
		}
		else
		{
			led_set(LED_L_YE, 0);
			led_set(LED_L_RD, 0);
		}
		
		if(right_Sens != 0)
		{
			if(right_Sens == -1)
			{
				led_set(LED_R_YE, 1);
				led_set(LED_R_RD, 0);
			}
			if(right_Sens == 1)
			{
				led_set(LED_R_YE, 0);
				led_set(LED_R_RD, 1);
			}
		}
		else
		{
			led_set(LED_R_YE, 0);
			led_set(LED_R_RD, 0);
		}
		delay(5);
	}
	
}
int GetImput()
{
	
	
}

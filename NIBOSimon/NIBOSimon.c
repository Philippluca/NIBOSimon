#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

#include <windows.h>

#include "Randomizer.h"

int main()
{
	led_init();//Led Initialization
	sens_init();//Fühler initialization
	int index = 0;//rename
	
	WaitForGameStartImput();
	int[1000] gameArray = CreateSequence();
	
	int actualLevel = 3;
	//int sequence[1000];
	
	while(1)//Game loop
	{
		ShowLights(actualLevel);
		int status = GetImput(actualLevel, gameArray);
		if(status ==  0)
		{
			//Left
			led_set(LED_L_YE, 1);
			led_set(LED_L_RD, 1);
		}
		else
		{
			//Right
			led_set(LED_R_YE, 1);
			led_set(LED_R_RD, 1);
		}
		Sleep(1000);
		DisableAllLights();
		actualLevel++;
	}
}

void ShowLights(int index, int[] myArray)
{
	//1000 max / index = ms time to show
	int sleepTime = (int)(1000 / index);
	
	for (int i = 0; i <= index; i++)
	{
		ShowLight(myArray[i]);
		Sleep(sleepTime);
		
		DisableAllLights();
		Sleep(sleepTime);
	}
}

void ShowLight(int lightIndex)
{
	switch(lightIndex)
	{
		case 1:
		led_set(LED_L_YE, 1);
		break;

		case 2:
		led_set(LED_L_RD, 1);
		break;

		case 3:
		led_set(LED_R_YE, 1);
		break;
		
		case 4:
		led_set(LED_R_RD, 1);
		break;
	}
}

void DisableAllLights()
{
	//Left
	led_set(LED_L_YE, 0);
	led_set(LED_L_RD, 0);
	
	//Right
	led_set(LED_R_YE, 0);
	led_set(LED_R_RD, 0);
}

int[1000] CreateSequence(){
	int[1000] myArray = int[1000];
	
	for (int i = 0; i < sizeof(myArray);i++)
	{
		int random = rand() % 4 + 1;
		myArray[i] = random;
		
		return myArray;
	}
}
int WaitForGameStartImput()
{
	while(1){
		int left_Sens = sens_getLeft();
		int right_Sens = sens_getRight();
		
		//DEBUG
		if(left_Sens != 0){
			if(left_Sens == -1)
			{
				led_set(LED_L_YE, 1);
				led_set(LED_L_RD, 0);
			}
			if(left_Sens == 1)
			{
				ed_set(LED_L_YE, 0);
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
		
		if(left_Sens == 1 && right_Sens == 1)
		{
			//StartGame
			break;
		}
	}
}

int GetImput(int maxIndex, int[1000] sequence)
{
	//Return = 1 success, 0 = fail
	int currentIndex = 0;
	while (currentIndex <= maxIndex)
	{
		int left_Sens = sens_getLeft();
		int right_Sens = sens_getRight();
		int currentValue = sequence[currentIndex];
		
		switch(lightIndex)
		{
			case 1:
			if(right_Sens != 0)//Value 3&4
			{
				return 0;
			}
			if(left_Sens != 0)
			{
				if(left_Sens == 1)//value 2
				return 0;
			}
			break;

			case 2:
			if(right_Sens != 0)//Value 3&4
			{
				return 0;
			}
			if(left_Sens != 0)
			{
				if(left_Sens == -1)//value 1
				return 0;
			}
			break;

			case 3:
			if(left_Sens != 0)//Value 1&2
			{
				return 0;
			}
			if(right_Sens != 0)
			{
				if(right_Sens == 1)//value 4
				return 0;
			}
			break;
			
			case 4:
			if(left_Sens != 0)//Value 1&2
			{
				return 0;
			}
			if(right_Sens != 0)
			{
				if(right_Sens == -1)//value 3
				return 0;
			}
		}
		currentIndex++;
	}
	return 1;
}
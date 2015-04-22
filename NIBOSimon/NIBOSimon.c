#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>
#include "GameAnimations.h"
#include "Randomizer.h"

int main()
{
	led_init();//Led Initialization
	sens_init();//Fühler initialization
	int index = 0;//rename
	
	WaitForGameStartImput();
	
	int * gameArray = { 0 };
		
	CreateSequence(gameArray);
	
	int actualLevel = 2;
	//int sequence[1000];
	
	while(1)//Game loop
	{
		ShowLights(actualLevel, gameArray);
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
		delay(1000);
		DisableAllLights();
		actualLevel++;
	}
}

void ShowLights(int index, int* myArray)
{
	//1000 max / index = ms time to show
	int sleepTime = (int)(1000 / index);
	
	for (int i = 0; i <= index; i++)
	{
		delay(sleepTime);
		led_set(myArray[i], 1);

		delay(sleepTime);
		led_set(myArray[i], 0);
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

void CreateSequence(int myArray[], int size)
{	
	for (int i = 0; i < size;i++)
	{
		int random = irand(0,3);
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
		
		if(left_Sens == 1 && right_Sens == 1)
		{
			//StartGame
			break;
		}
	}
}

int GetImput(int maxIndex, int * sequence)
{
	//Return = 1 success, 0 = fail
	int currentIndex = 0;
	while (currentIndex <= maxIndex)
	{
		int left_Sens = sens_getLeft();
		int right_Sens = sens_getRight();
		int currentValue = sequence[currentIndex];
		int isPressed = 0;
		
		switch(currentValue)
		{
			case 0:
			if(right_Sens != 0)//Value 2&3
			{
				return 0;
			}
			if(left_Sens != 0)
			{
				if(left_Sens == 1)//value 1
				return 0;
			}
			break;

			case 1:
			if(right_Sens != 0)//Value 2&3
			{
				return 0;
			}
			if(left_Sens != 0)
			{
				if(left_Sens == -1)//value 0
				return 0;
			}
			break;

			case 2:
			if(left_Sens != 0)//Value 0&1
			{
				return 0;
			}
			if(right_Sens != 0)
			{
				if(right_Sens == 1)//value 3
				return 0;
			}
			break;
			
			case 3:
			if(left_Sens != 0)//Value 0&1
			{
				return 0;
			}
			if(right_Sens != 0)
			{
				if(right_Sens == -1)//value 2
				return 0;
			}
		}
		
		if(left_Sens != 0 || right_Sens != 0)
			isPressed = 1;
		
		if(isPressed && left_Sens != 0 && right_Sens != 0){
			isPressed = 0;
			currentIndex++;
		}
	}
	return 1;
}

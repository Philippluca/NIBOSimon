#include <nibobee/iodefs.h>
#include <nibobee/sens.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>
#include "GameAnimations.h"
#include "Randomizer.h"

static int  gameArray[100];

int main()
{
	led_init();//Led Initialization
	sens_init();//Fühler initialization
	int index = 0;//rename	
	int actualLevel = 2;
	int startParam = WaitForGameStartImput();
	
	if (startParam == -1)
	{
		actualLevel = 30;
	}
	
	DisableAllLights();
		
	CreateSequence(100);
	

	
	delay(1000);
	
	while(1)//Game loop
	{
		ShowLights(actualLevel);
		int status = GetImput(actualLevel);
		if(status ==  0)
		{
			ShowLostAnimation();
			actualLevel=1;
			CreateSequence(100);
		}
		else
		{
			ShowNextLevelAnimation();
		}
		delay(2000);
		DisableAllLights();
		actualLevel++;
	}
}

void ShowLights(int index)
{
	//1000 max / index = ms time to show
	int sleepTime = (int)(3000 / index);
	
	for (int i = 0; i <= index; i++)
	{
		delay(sleepTime);
		led_set(gameArray[i], 1);

		delay(sleepTime);
		led_set(gameArray[i], 0);
	}
	
	//For any case
	DisableAllLights();
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

void CreateSequence(int size)
{	
	for (int i = 0; i < size;i++)
	{
		int random = irand(0,3);
		gameArray[i] = random;
	}
}
int WaitForGameStartImput()
{
	int isPressedToStart = 0;
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
		if(left_Sens == -1 && right_Sens == -1)
		{
			isPressedToStart = -1;
		}
		if(left_Sens == 1 && right_Sens == 1)
		{
			isPressedToStart = 1;
		}
		if(isPressedToStart == -1 && left_Sens == 0 && right_Sens == 0)
		{
			ShowEasterEggFoundAnimation();
			break;
		}
		if(isPressedToStart == 1 && left_Sens == 0 && right_Sens == 0)
		{
			//Start game
			break;
		}
	}
	return isPressedToStart;
}

int GetImput(int maxIndex)
{
	//Return = 1 success, 0 = fail
	int currentIndex = 0;
	int isPressed = 0;
	while (currentIndex <= maxIndex)
	{
		int left_Sens = sens_getLeft();
		int right_Sens = sens_getRight();
		int currentValue = gameArray[currentIndex];
		
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
				if(right_Sens == -1)//value 3
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
				if(right_Sens == 1)//value 2
				return 0;
			}
		}
		
		if(left_Sens != 0 || right_Sens != 0)
			isPressed = 1;
		
		if(isPressed && left_Sens == 0 && right_Sens == 0){
			isPressed = 0;
			currentIndex++;
		}
	}
	return 1;
}
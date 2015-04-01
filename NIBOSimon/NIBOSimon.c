#include <nibobee/iodefs.h>
#include <nibobee/led.h>
#include <nibobee/delay.h>

#include "Randomizer.h"

int main()
{
	led_init();

	while(1==1)
	{
		int myLed = irand(0,3);
		led_set(myLed, 1);
		delay(10);
		led_set(myLed, 0);
		delay(10);
	}
}
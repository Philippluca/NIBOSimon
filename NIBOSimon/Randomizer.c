/*
 * Randomizer.c
 *
 * Created: 25.03.2015 11:48:29
 *  Author: LTI
 */ 
#include <stdio.h>
#include <stdlib.h>

#include "Randomizer.h"

int irand(int a, int e)
{
	double r = e - a + 1;
	return a + (int)(r * rand()/(RAND_MAX+1.0));

}
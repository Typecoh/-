#include "headfile.h"
#include "buzzer.h"

#define true 0
#define false 1
void buzzer(int res)
{
	P77 = res;
}


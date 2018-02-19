#include "main1.h"
#include "main2.h"
#include "data.h"
#include <stdio.h>
#include <stdafx.h>

 extern State state2[19305];
 extern State state[19305];

void main(void)
{
	
	main1();
	main2();
	printf("\n\n\n\n\n\n\n\n\n%ld\n\n\n", state[1].stateinbinary);

	/// creat state and matrix function, which need the parameter of g, here we can do a circling to get different g
}



/// combination state creator , 
////1 time values of up and down together
/// 2 figure out how many double occupation
/// 3 figure out the labeling for states (i-1)*TotalN1+j
////4 record the connected state (i, j's connections)+(i's connections, j)

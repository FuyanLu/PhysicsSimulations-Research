#include <stdio.h>  
#include <string>  
#include <math.h>
#include "data.h"
#include <stdafx.h>

/// define a structure array to store the states

 State state[19305];

/// Declare a state arrays and the variation for state.

  int TaltalN = 1;


///define the link function and define the hopping matrix 

static void statelink(int size)
{
	state[TaltalN].linknumber = 0;
	int a = 0, i, j;//to lable the link[a] then change the link of new state 
	int c = 0;
	///   printf("it is ok for define i,j,a");
	for (i = TaltalN - 1; i >= 1; i--){ // check with all other state

		for (j = 0; j < size - 1; j++){
			if ((state[TaltalN].stateinbinary - state[i].stateinbinary) == pow(2, j) || (state[TaltalN].stateinbinary - state[i].stateinbinary) == -pow(2, j))
			{
				c = 1;
				break;
			}
			else continue;

		}
		if ((state[TaltalN].stateinbinary - state[i].stateinbinary == (pow(2, size - 1) - 1)) || (state[TaltalN].stateinbinary - state[i].stateinbinary) == (1 - pow(2, size - 1)))
		{
			c = -1;
		}
		if (c == 0) continue;
		else if (c == 1){
			state[i].link[state[i].linknumber] = TaltalN;
			state[i].linknumber++;
			state[TaltalN].link[state[TaltalN].linknumber] = i;
			state[TaltalN].linknumber++;

		}
		else if (c == -1){     /// the minus sign record the matrix elements is negetive hopping term.
			state[i].link[state[i].linknumber] = -TaltalN;
			state[i].linknumber++;
			state[TaltalN].link[state[TaltalN].linknumber] = -i;
			state[TaltalN].linknumber++;
		}
		else printf("something wrong with statelink function!");
		c = 0;
	}
}




/// define a function to creat one state

static void statecreator(char *p, int size, int n){ // p is the string from combine, and n is the number of fermion

	state[TaltalN].stateinbinary = 0;
	/// printf("statecreator can be adopted!\n");
	int location, i;
	for (i = 0; i < n; i++)
	{
		//	printf("the new\n\n\n %s\n\n\n", p);
		location = p[i] - 'a';// transforme the elements of string to the number of site which is occupaid
		state[TaltalN].stateinbinary += pow(2, size - 1 - location);
		state[TaltalN].stateinarray[location] = 1;

	}
	printf("stateinbiary can be instructed!\n\n\n stateinbinary is %ld", state[TaltalN].stateinbinary);
	state[TaltalN].value = 1; /// we need a a function to figure out the 
	//determinant of coeffecient matrix.
	if (TaltalN>1) statelink(size); //// Link function, which can modify the linklist
	////of new state and old state.
	///printf("statecreator is working!");
	TaltalN++;
}


/// define the partial combination with recursion method

//// and every time creat a state with state_creat function

static void combine(char *src, char *out, int start, int rec, int end, int n, int fermion, int size)
{

	int i;
	if (n>end)
		n = end;
	for (i = start; i<end; i++){
		out[rec] = src[i];
		if (n == 1){
			out[rec + 1] = '\0';
			char *pp = out;
			printf("%s\n", out);
			statecreator(pp, size, fermion);  /// every printf means creat one state
		}
		else {
			combine(src, out, i + 1, rec + 1, end, n - 1, fermion, size);
		}
	}
}

/// the main function to input size of 1D system and the number of fermion for 1 kind of spin
//  and recall combination function



static void stateprintor(int size, int n)
{

	int i, j, k;
	for (i = 1; i < TaltalN; i++)
	{
		printf("the number %i state:   ", i);
		for (j = 0; j < size; j++)
		{
			printf("%i", state[i].stateinarray[j]);
		}

		printf("value is %i and ", state[i].value);
		printf("binary is %ld and link with states ", state[i].stateinbinary);
		for (k = 0; k < state[i].linknumber; k++)
		{
			printf("%i ", state[i].link[k]);
		}
		printf("\n");
	}

}


int main1(void)
{
	void stateprintor(int, int);
	char str[80] = "ABC", *p;
	int t, N;
	printf("give a the size of the system:\n");
	scanf_s("%i", &N);
	if (N > 15) {

		printf("size is too big please re-enture the size of system:\n");
		scanf_s("%i", &N);

	}
	for (int i = 0; i < N; i++)
	{
		str[i] = 'a' + i;
	};
	str[N] = '\0';
	p = str;
	printf("give a number for size of combination:\n");
	scanf_s("%i", &t);
	char out[80];
	combine(p, out, 0, 0, strlen(str), t, t, strlen(str));
	stateprintor(N, t);
	return 0;
}


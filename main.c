#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DRAW_SIZE 6
#define MAX_SIZE 10
#define MIN_BALL 1
#define MAX_BALL 49
#define NUM_TICKETS 100

int contains(int arr[], int size, int key);
void generateNumbers(int arr[], int size, int minimum, int maximum);
int countMatchingNumbers(int winners[], int size, int ticket_numbers[]);
void countPrizeWinners(int winning_numbers[], int size, int tickets[][MAX_SIZE],
                       int num_tickets, int winner_counts[]);

int main(void) {

  int todays_draw[DRAW_SIZE] = {0};
  int my_ticket[DRAW_SIZE] = {1, 2, 3, 4, 5, 6};
  int all_tickets[NUM_TICKETS][MAX_SIZE];
  int counts[DRAW_SIZE+1];
  int index;

  srand(time(NULL));

  /*getting the numbers from the user*/
  printf("Enter %d unique numbers between %d and %d to be your ticket\n", DRAW_SIZE, MIN_BALL, MAX_BALL);
	  for (index = 0; index < DRAW_SIZE-1; index++)
	  {
		  scanf("%d\n", &my_ticket[index]);
		  
	  }

  /*generating the winning numbers*/
  generateNumbers(todays_draw, DRAW_SIZE, MIN_BALL, MAX_BALL);

  /*generating the other tickets*/
  for (index = 1; index < NUM_TICKETS; index++)
  {
	  generateNumbers(all_tickets[index], DRAW_SIZE, MIN_BALL, MAX_BALL);
  }

  printf("Winning numbers: [%d", todays_draw[0]);
  for (index = 1; index < DRAW_SIZE; index++) {
    printf(", %d", todays_draw[index]);
  }
  printf("]\n");

  printf("Your ticket:     [%d", my_ticket[0]);
  for (index = 1; index < DRAW_SIZE; index++) {
    printf(", %d", my_ticket[index]);
  }
  printf("]\n");

  printf("Your ticket matched %d numbers.\n\n",
         countMatchingNumbers(todays_draw, DRAW_SIZE, my_ticket));

  countPrizeWinners(todays_draw, DRAW_SIZE, all_tickets, NUM_TICKETS, counts);

  for (index = 0; index <= DRAW_SIZE; index++) {
    printf("%d tickets got %d numbers right.\n", counts[index], index);
  }
  
  return 0;
}

/* Function: generateNumbers
 * Purpose: Generates random, distinct integers in the range of
 * minimum to maximum INCLUSIVE and stores these in the output array
 * PARAM: output array to contain generated values
 * PARAM: size of output array
 * PARAM: minimum value of each output number
 * PARAM: maximum value of each output number
 */
void generateNumbers(int arr[], int size, int minimum, int maximum)
{
	int nextNum;
	int range = maximum + 1 - minimum;

	for (int j = 0; j < size; j++)
	{
		arr[j] = -1;
	}

	for (int i = 0; i < size; i++)
	{
		nextNum = rand() % range + minimum;
		while (contains(arr, i, nextNum) == 1)
		{
			nextNum = rand() % range + minimum;
		}

		arr[i] = nextNum;
	}
}

void countPrizeWinners(int winning_numbers[], int size, int tickets[][MAX_SIZE],
	int num_tickets, int winner_counts[])
{
	int index = 0;
	for (int winnercounts = 0; winnercounts < num_tickets; winnercounts++)
	{
		for (int j = 0; j < num_tickets; j++)
		{
			if (countMatchingNumbers(winning_numbers, size, tickets[j]) == winnercounts)
			{
				index++;
			}
		}
		winner_counts[winnercounts] = index;
		index = 0;
	}
}

int contains(int arr[], int size, int key)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == key)
		{
			return 1;
		}
	}
	return 0;
}

int countMatchingNumbers(int winners[], int size, int ticket_numbers[])
{
	int matchingNumbers = 0;
	for (int i = 0; i < size; i++)
	{
		matchingNumbers += contains(ticket_numbers, size, winners[i]);
	}
	return matchingNumbers;
}
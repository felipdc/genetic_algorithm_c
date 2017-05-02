#define GENERATION_SIZE 10
#define MUTATION_RATE 0.8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char letters[27] = " abcdefghijklmnopqrstuvxywz";

const char *goal = "hello world";

void score_calc();	

char create_generation();

int sort_scores();

int main(){

	int i;

	srand(time(NULL));

	int size_of_goal = strlen(goal);

	char *indiv[GENERATION_SIZE];

	//allocating memory to *indiv (array of strings)

	for(i=0;i<=GENERATION_SIZE;i++){

		indiv[i] = malloc(sizeof(char)*size_of_goal);

		//if there is no memory left then

		if(!indiv[i]){

			printf("Could not allocate memory \n");

			free(*indiv);

			return -1;

		}

	}

	create_generation(indiv, size_of_goal);

	free(*indiv);

	return 0;

}

char create_generation(char **indiv, int size_of_goal){

	int i, j;

	printf("Geracao 1: \n --------------------------------- \n");

	for(i=0;i<GENERATION_SIZE;i++){

		for(j=0;j<size_of_goal;j++){

			//generating random char

			int random_select = rand() % 28;

			indiv[i][j] = letters[random_select];

			printf("%c", indiv[i][j]);			

		}

		printf("\n");

	}

	printf("--------------------------------- \n");

	score_calc(indiv, size_of_goal);

}



void score_calc(char **indiv, int size_of_goal){

	int i, j;

	int score[GENERATION_SIZE];

	for(i=0;i<GENERATION_SIZE;i++){

		score[i] = 0;

	}

	for(i=0;i<=GENERATION_SIZE;i++){

		for(j=0;j<size_of_goal;j++){

			if(goal[j] == indiv[i][j]){

				score[i]++;

			}

		}

	}

	//for(i=0;i<GENERATION_SIZE;i++){

	//	printf("score indiv[%d] = %d \n",i, score[i]);

	//}

	sort_scores(indiv, size_of_goal, score);

}


int sort_scores(char **indiv, int size_of_goal, int score[]){

	//organize score in crescent mode using insert sort

	int i, j, x;

	//for(i=0;i<GENERATION_SIZE;i++){

	//	printf("score %d \n", score[i]);

	//}

	printf("\n\n\n");


	for(i=0;i<GENERATION_SIZE;i++){

		for(j=GENERATION_SIZE-1; j>i || score[j] > score[j-1]; j--){

			x = score[j];

			if(score[j] < score[j-1]){

				x = score[j-1];

				score[j-1] = score[j];

				score[j] = x;

			}

		}

	}

	
	for(i=0;i<GENERATION_SIZE;i++){

		printf("score %d \n", score[i]);

	}




}
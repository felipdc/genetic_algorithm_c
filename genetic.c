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

int max_scores();

char crossing_over();

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

	max_scores(indiv, size_of_goal, score);

}


int max_scores(char **indiv, int size_of_goal, int score[]){

	// search for individuals that have the best score

	int x = -1;
	int y = x;	
	int i, max_1, max_2;

	//first maximum individual

	for(i=0;i<GENERATION_SIZE;i++){

		if(score[i] >= x){

			x = score[i];

			max_1 = i;

		}

	}

	//second maximum individual

	for(i=0;i<GENERATION_SIZE;i++){

		if(i==max_1){

			continue;
		}

		if(score[i] >= y){

			y = score[i];

			max_2 = i;


		}

	}

	crossing_over(indiv, size_of_goal, max_1, max_2);


}

char crossing_over(char **indiv, int size_of_goal, int max_1, int max_2){


	char *father_a = indiv[max_1];

	char *father_b = indiv[max_2];

	char new_indiv[size_of_goal];

	int i;

	printf("%s \n", father_a);

	printf("%s \n", father_b);

	//split best individuals into two and store in new_indiv

	for(i=0;i<=size_of_goal;i++){

		if(i<=6){

			new_indiv[i] = indiv[max_1][i];

		}

		else{

			new_indiv[i] = indiv[max_2][i];

		}

	}

	printf("%s \n", new_indiv);


}
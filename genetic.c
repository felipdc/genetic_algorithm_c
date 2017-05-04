/* Code made by Felipe Tiago De Carli
email: felipetdecarli@gmail.com
Feel free to use.
Please keep the authors name in the code.
*/



#define GENERATION_SIZE 12 //carefull, dont put an even value!
#define MUTATION_RATE 0.92

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char letters[27] = "abc defghijklmnopqrstuvxywz";

const char *goal = "luah debus";

int generation = 1;

void score_calc();	

char create_generation();

int max_scores();

char crossing_over();

char mutate_individuals();	

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

	return 0;

}

char create_generation(char **indiv, int size_of_goal){

	int i, j;

	printf("Geracao 1: \n --------------------------------- \n");

	generation++;

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

	//printf("%s \n", father_a);

	//printf("%s \n", father_b);

	//split best individuals into two and store in new_indiv

	for(i=0;i<=size_of_goal;i++){

		if(i <= size_of_goal/2){

			new_indiv[i] = indiv[max_1][i];

		}

		else{

			new_indiv[i] = indiv[max_2][i];

		}

	}


	//free(*indiv);	

	for(i=0;i<GENERATION_SIZE;i++){

		for(int j=0;j<size_of_goal;j++){

			indiv[i][j] = new_indiv[j];

		}
	}


	mutate_individuals(indiv, size_of_goal);

}


char mutate_individuals(char **indiv, int size_of_goal){

	int i,j;

	//creating arrays of random numbers

	int random_part[GENERATION_SIZE][size_of_goal];

	int random_char[GENERATION_SIZE][size_of_goal];

	//filling arrays with random numbers

	for(i=0;i<GENERATION_SIZE;i++){

		for(j=0;j<size_of_goal;j++){

			random_part[i][j] = rand() % 100;

			random_char[i][j] = rand() % 28;

		}

	}

	// mutation in each letter (chromossome) of each individual

	for(i=0;i<GENERATION_SIZE;i++){

		for(j=0;j<size_of_goal;j++){

			if (random_part[i][j] >= (MUTATION_RATE*100)){

				indiv[i][j] = letters[random_char[i][j]];

				//printf("%c", indiv[i][j]);

			}

			else{

				//printf("%c", indiv[i][j]);
			}

		}

		//printf("\n");

	}

	printf("Geracao %d: \n", generation);

	generation++;

	printf("--------------------------------- \n");

	for(i=0;i<GENERATION_SIZE;i++){

		printf("%s\n", indiv[i]);


	}

	printf("--------------------------------- \n");


	//check for solution

	for(i=0;i<GENERATION_SIZE;i++){

		if (strcmp(indiv[i],goal) == 0){

			printf("Solution found! \n");

			printf("Total individuals = %d \n", ((generation-1)*GENERATION_SIZE));

			return 0;

		}

	}

	fflush(stdout);

	score_calc(indiv, size_of_goal);

}
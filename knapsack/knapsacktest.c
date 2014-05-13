#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libknapsack.h"

int main(int argc, char *argv[])
{
	long budget;
	long max_precincts;
	int max_quality_layers;
	int **weights;
	double **profit;
	long *ordered_list;
	int i, j;

	if (argc < 4) {
		printf("Usage: %s <max_precincts> <max_quality_layers> <budget>\n",argv[0]);
		exit(0);
	}

	// Check the intial value
	max_precincts = atoi(argv[1]);

	if (max_precincts <= 0) {
		printf("The max number of precincts must be a positive integer\n");
		exit(0);
	}

	// Check the intial value
	max_quality_layers = atoi(argv[2]);

	if (max_quality_layers <= 0) {
		printf("The max number of quality layers must be a positive integer\n");
		exit(0);
	}

	// Check the intial value
	budget = atoi(argv[3]);

	if (budget <= 0) {
		printf("The budget must be a positive integer\n");
		exit(0);
	}

  	// Initialize random generator
  	srand (time(NULL));

	// Allocate memory for weights
	weights = (int **) malloc(max_precincts*(sizeof(int *)));
	for(i=0; i<max_precincts; i++) {
		weights[i] = (int *) malloc(max_quality_layers*(sizeof(int)));
	}

	// Allocate memory for profit
	profit = (double **) malloc(max_precincts*(sizeof(double *)));
	for(i=0; i<max_precincts; i++) {
		profit[i] = (double *) malloc(max_quality_layers*(sizeof(double)));
	}

	// Allocate memory for ordered_list
	ordered_list = (long *) malloc(max_precincts*(sizeof(long)));

	// Initial values for weights between [0, MAX_BYTES_SIZE]
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			weights[i][j] = rand_range_long(j*100, (j+1)*100);
		}
	}

	// Initial values for profit between [MIN_PSNR_VALUE, MAX_PSNR_VALUE]
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			profit[i][j] = rand_range_double(j*10, (j+1)*10);
		}
	}

	// Initial values for the ordered list
	for(i=0; i<max_precincts; i++) {
		ordered_list[i] = -1;
	}

	long ne = 0;
	while(ne<max_precincts) {
		long id = rand_range_long(0, max_precincts - 1);
		int found = 0;
		for(i=0; (i<max_precincts) && (!found); i++) {
			if (ordered_list[i] == id) {
				found = 1;
				break;
			}
		}
		if (!found) {
			ordered_list[ne++] = id;
		}
	}

	// Print weights values
	if (DEBUG) print_weights_values(max_precincts, max_quality_layers, weights);

	// Print profit values
	if (DEBUG) print_profit_values(max_precincts, max_quality_layers, profit);

	// Print ordered_list values
	if (DEBUG) print_ordered_list_values(max_precincts, ordered_list);

	// Print all the precincts with their weight and profit
	if (DEBUG) print_precincts_weight_profit(max_precincts, max_quality_layers, weights, profit, ordered_list);

	// Check the method 1
	solution sol1;
	method_1(max_precincts, max_quality_layers, budget, ordered_list, weights, profit, &sol1);

	// Check the method 2
	solution *sol2;

	// Allocate memory for the array of solutions
	sol2 = (solution *) malloc (max_quality_layers*sizeof(solution));

	for(i=0; i<max_quality_layers; i++) {
		method_2(max_precincts, max_quality_layers, budget, ordered_list, weights, profit, i, &sol2[i]);
	}

	// Print the results for all the solutions
	printf("\nSolution 1:\n###########");
	print_solution(sol1);

	printf("\nSolution 2:\n###########");
	for(i=0; i<max_quality_layers; i++) {
		printf("\n--- Quality Layer: %d", i);
		print_solution(sol2[i]);
	}

	// Find the best solution (max profit)	
	find_best_solution(sol1, sol2, max_quality_layers);

	return 0;
}
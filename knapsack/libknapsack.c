#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libknapsack.h"

long rand_range_long(long min_n, long max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

double rand_range_double(double min_n, double max_n)
{
    return (double)rand()/RAND_MAX * (max_n - min_n) + min_n;
}

void method_1(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, solution *sol) {

	if (DEBUG) printf("\n\n**** Method: 1 ****\n");

	int end = 0;
	int i, j;

	// Initialize the total number of bytes used and the profit
	sol->sum_bytes = 0;
	sol->sum_profit = 0;	

	// Allocate memory for the solution
	sol->list = (pre_id_ql *) malloc(max_precincts*max_quality_layers*(sizeof(pre_id_ql)));

	// Initialize the initial number of elements
	sol->ne = 0;

	for(j=0; j<max_quality_layers && !end; j++) { 	

		for (i=0; i<max_precincts && !end; i++) {
			long pos = ordered_list[i];

			if (weights[pos][j] >= budget) {
				end = 1;
				break;
			}

			if (DEBUG) printf("[%4ld][%d]\t", pos, j);
			
			sol->sum_profit = sol->sum_profit + profit[pos][j];
			sol->sum_bytes = sol->sum_bytes + weights[pos][j];
			budget = budget - weights[pos][j];

			// Add a new element to the solution list
			sol->list[sol->ne].precinct_id = pos;
			sol->list[sol->ne].quality_layer = j;
			sol->ne++;			
		}
		if (DEBUG) printf("\n");
	}
}

// max_ql: The number of the last layer that we are going to check
//
void method_2(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, int max_ql, solution *sol) {

	if (DEBUG) printf("\n\n**** Method: 2 \tmax_ql: %d ****\n", max_ql);

	int end = 0;
	int i, j;

	// Initialize the total number of bytes used and the profit
	sol->sum_bytes = 0;
	sol->sum_profit = 0;	

	// Allocate memory for the solution
	sol->list = (pre_id_ql *) malloc(max_precincts*max_quality_layers*(sizeof(pre_id_ql)));

	// Initialize the initial number of elements
	sol->ne = 0;

	for (i=0; i<max_precincts && !end; i++) {

		long pos = ordered_list[i];

		for(j=0; j<=max_ql && !end; j++) { 

			if (weights[pos][j] >= budget) {
				end = 1;
				break;
			}

			if (DEBUG) printf("[%4ld][%d]\t", pos, j);

			sol->sum_profit = sol->sum_profit + profit[pos][j];
			sol->sum_bytes = sol->sum_bytes + weights[pos][j];
			budget = budget - weights[pos][j];

			// Add a new element to the solution list
			sol->list[sol->ne].precinct_id = pos;
			sol->list[sol->ne].quality_layer = j;
			sol->ne++;
		}
		if (DEBUG) printf("\n");
	}
}

void print_solution(solution sol) {
	printf("\nSum (bytes): %ld\n", sol.sum_bytes);
	printf("Sum (profit): %f\n", sol.sum_profit);

	/*
	printf("Solution list:\n");
	int i;
	for(i=0; i<sol.ne; i++) {
		printf("id: %ld \t ql: %d\n", sol.list[i].precinct_id, sol.list[i].quality_layer);
	}
	*/
}

void find_best_solution(solution sol1, solution *sol2, int max_quality_layers) {
	int i;

	// Number of the method with the best solution (1 or 2)
	int sol_method;
	
	// If the best solution is 3, it is necessary to store the number of the quality layer
	// where we get the best value
	int sol_index_ql;

	double max_profit = -1;

	for(i=0; i<max_quality_layers; i++) {
		if (sol2[i].sum_profit > max_profit) {
			max_profit = sol2[i].sum_profit;
			sol_method = 2;
			sol_index_ql = i;
		}
	}

	if (sol1.sum_profit > max_profit) {
		max_profit = sol1.sum_profit;
		sol_method = 1;
		sol_index_ql = -1;
	}

	// Test
	if (sol_method == 2) {
		printf("\nThe best solution is the method: %d with: %d quality layer with a profit of: %lf\n", sol_method, sol_index_ql, max_profit);
		printf(" ** NOTE: The number of the quality layer is zero based **\n");
	} else {
		printf("\nThe best solution is the method: %d with a profit of: %lf\n", sol_method, max_profit);
	}
}

// Print weights values
void print_weights_values(long max_precincts, int max_quality_layers, int **weights) {
	int i, j;
	printf("\nweights (precincts sizes in bytes): \n");
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			printf(" %4d ", weights[i][j]);
		}
		printf("\n");
	}	
}

// Print profit values
void print_profit_values(long max_precincts, int max_quality_layers, double **profit) {
	int i, j;
	printf("\nprofit (psnr or ssim values): \n");
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			printf(" %4.2lf ", profit[i][j]);
		}
		printf("\n");
	}	
}

// Print ordered_list values
void print_ordered_list_values(long max_precincts, long *ordered_list) {
	int i;
	printf("\nordered_list: \n");
	for(i=0; i<max_precincts; i++) {
		printf(" %4ld ", ordered_list[i]);
	}
}

// Print all the precincts with their weight and profit
void print_precincts_weight_profit(long max_precincts, int max_quality_layers, int **weights, double **profit, long *ordered_list) {
	int i, j;
	printf("\n\n");
	for(i=0; i<max_precincts; i++) {

		long pos = ordered_list[i];

		for(j=0; j<max_quality_layers; j++) {
			printf("w[%ld][%d] = %d / %lf  \t", pos, j, weights[pos][j], profit[pos][j]);
		}
		printf("\n");
	}
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_BYTES_SIZE 1000
#define MIN_PSNR_VALUE 10
#define MAX_PSNR_VALUE 50
#define DEBUG 0

typedef struct {
	long precinct_id;
	int quality_layer;
} pre_id_ql;


typedef struct {
	long ne;
	pre_id_ql *list;
	long sum_bytes;
	double sum_profit;
} solution;

long rand_range_long(long min_n, long max_n);
double rand_range_double(double min_n, double max_n);
void method_1(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, solution *sol);
void method_2(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, solution *sol);
void method_3(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, int max_ql, solution *sol);
void print_solution(solution sol);
void find_best_solution(solution sol1, solution sol2, solution *sol3, int max_quality_layers);
void print_weights_values(long max_precincts, int max_quality_layers, int **weights);
void print_profit_values(long max_precincts, int max_quality_layers, double **profit);
void print_ordered_list_values(long max_precincts, long *ordered_list);
void print_precincts_weight_profit(long max_precincts, int max_quality_layers, int **weights, double **profit, long *ordered_list);

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
	solution sol2;
	method_2(max_precincts, max_quality_layers, budget, ordered_list, weights, profit, &sol2);

	// Check the method 3
	solution *sol3;

	// Allocate memory for the array of solutions
	sol3 = (solution *) malloc (max_quality_layers*sizeof(solution));

	for(i=0; i<max_quality_layers; i++) {
		method_3(max_precincts, max_quality_layers, budget, ordered_list, weights, profit, i, &sol3[i]);
	}

	// Print the results for all the solutions
	printf("\nSolution 1:\n###########");
	print_solution(sol1);

	printf("\nSolution 2:\n###########");
	print_solution(sol2);

	printf("\nSolution 3:\n###########");
	for(i=0; i<max_quality_layers; i++) {
		printf("\n--- Quality Layer: %d", i);
		print_solution(sol3[i]);
	}

	// Find the best solution (max profit)	
	find_best_solution(sol1, sol2, sol3, max_quality_layers);

	return 0;
}

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

	for (i=0; i<max_precincts && !end; i++) {

		long pos = ordered_list[i];

		for(j=0; j<max_quality_layers && !end; j++) { 

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

void method_2(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, solution *sol) {

	if (DEBUG) printf("\n\n**** Method: 2 ****\n");

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
void method_3(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, int max_ql, solution *sol) {

	if (DEBUG) printf("\n\n**** Method: 3 \tmax_ql: %d ****\n", max_ql);

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

void find_best_solution(solution sol1, solution sol2, solution *sol3, int max_quality_layers) {
	int i;

	// Number of the method with the best solution (1, 2 or 3)
	int sol_method;
	
	// If the best solution is 3, it is necessary to store the number of the quality layer
	// where we get the best value
	int sol_index_ql;

	double max_profit = -1;

	for(i=0; i<max_quality_layers; i++) {
		if (sol3[i].sum_profit > max_profit) {
			max_profit = sol3[i].sum_profit;
			sol_method = 3;
			sol_index_ql = i;
		}
	}

	if (sol1.sum_profit > max_profit) {
		max_profit = sol1.sum_profit;
		sol_method = 1;
		sol_index_ql = -1;
	}

	if (sol2.sum_profit > max_profit) {
		max_profit = sol2.sum_profit;
		sol_method = 2;
		sol_index_ql = -1;
	}

	// Test
	if (sol_method == 3) {
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
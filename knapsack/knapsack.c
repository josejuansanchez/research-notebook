#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_BYTES_SIZE 1000
#define MIN_PSNR_VALUE 10
#define MAX_PSNR_VALUE 50
#define BUDGET 2700

int rand_range_int(int min_n, int max_n);
float rand_range_float(float min_n, float max_n);
void method_1(int max_precincts, int max_quality_layers, int * ordered_list, int **weights, float **profit);
void method_2(int max_precincts, int max_quality_layers, int * ordered_list, int **weights, float **profit);
void method_3(int max_precincts, int * ordered_list, int **weights, float **profit, long max_ql);

int main()
{
	int max_precincts;
	int max_quality_layers;
	int **weights;
	float **profit;
	int *ordered_list;
	int i, j;

	// Initial values
	max_precincts = 8;
	max_quality_layers = 5;

  	// Initialize random generator
  	srand (time(NULL));

	// Allocate memory for weights
	weights = (int **) malloc(max_precincts*(sizeof(int *)));
	for(i=0; i<max_precincts; i++) {
		weights[i] = (int *) malloc(max_quality_layers*(sizeof(int)));
	}

	// Allocate memory for profit
	profit = (float **) malloc(max_precincts*(sizeof(float *)));
	for(i=0; i<max_precincts; i++) {
		profit[i] = (float *) malloc(max_quality_layers*(sizeof(float)));
	}

	// Allocate memory for ordered_list
	ordered_list = (int *) malloc(max_precincts*(sizeof(int)));

	// Initial values for weights between [0, MAX_BYTES_SIZE]
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			weights[i][j] = rand_range_int(j*100, (j+1)*100);
		}
	}

	// Initial values for profit between [MIN_PSNR_VALUE, MAX_PSNR_VALUE]
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			profit[i][j] = rand_range_float(j*10, (j+1)*10);
		}
	}

	// Initial values for the ordered list
	for(i=0; i<max_precincts; i++) {
		ordered_list[i] = -1;
	}

	int ne = 0;
	while(ne<max_precincts) {
		int id = rand_range_int(0, max_precincts - 1);
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
	printf("\nweights (precincts sizes in bytes): \n");
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			printf(" %4d ", weights[i][j]);
		}
		printf("\n");
	}

	// Print profit values
	printf("\nprofit (psnr or ssim values): \n");
	for(i=0; i<max_precincts; i++) {
		for(j=0; j<max_quality_layers; j++){
			printf(" %4.2f ", profit[i][j]);
		}
		printf("\n");
	}

	// Print ordered_list values
	printf("\nordered_list: \n");
	for(i=0; i<max_precincts; i++) {
		printf(" %4d ", ordered_list[i]);
	}

	printf("\n\n");
	for(i=0; i<max_precincts; i++) {

		int pos = ordered_list[i];
		//int sum_weights = 0;
		//float sum_profit = 0;

		for(j=0; j<max_quality_layers; j++) {
			//sum_weights = sum_weights + weights[pos][j];
			//sum_profit = sum_profit + profit[pos][j];
			printf("w[%d][%d] = %d / %f  \t", pos, j, weights[pos][j], profit[pos][j]);
		}
		printf("\n");
	}

	// Check the method 1
	method_1(max_precincts, max_quality_layers, ordered_list, weights, profit);

	// Check the method 2
	method_2(max_precincts, max_quality_layers, ordered_list, weights, profit);

	// Check the method 3
	for(i=0; i<max_quality_layers; i++) {
		method_3(max_precincts, ordered_list, weights, profit, i);
	}

	return 0;
}

int rand_range_int(int min_n, int max_n)
{
    return rand() % (max_n - min_n + 1) + min_n;
}

float rand_range_float(float min_n, float max_n)
{
    return (float)rand()/RAND_MAX * (max_n - min_n) + min_n;
}

void method_1(int max_precincts, int max_quality_layers, int * ordered_list, int **weights, float **profit) {

	printf("\n\n**** Method: 1 ****\n");

	long sum_bytes = 0;
	double sum_profit = 0;
	int end = 0;
	int i, j;

	long budget = BUDGET;

	for (i=0; i<max_precincts && !end; i++) {

		int pos = ordered_list[i];

		for(j=0; j<max_quality_layers && !end; j++) { 

			if (weights[pos][j] >= budget) {
				end = 1;
				break;
			}

			printf("[%d][%d]\t", pos, j);
			//printf("w[%d][%d] = %d / %f  \t", pos, j, weights[pos][j], profit[pos][j]);
			
			sum_profit = sum_profit + profit[pos][j];
			sum_bytes = sum_bytes + weights[pos][j];
			budget = budget - weights[pos][j];			
		}
		printf("\n");
	}

	printf("\nSum (bytes): %ld\n", sum_bytes);
	printf("Sum (profit): %lf\n", sum_profit);
}

void method_2(int max_precincts, int max_quality_layers, int * ordered_list, int **weights, float **profit) {

	printf("\n\n**** Method: 2 ****\n");

	long sum_bytes = 0;
	double sum_profit = 0;
	int end = 0;
	int i, j;

	long budget = BUDGET;

	for(j=0; j<max_quality_layers && !end; j++) { 	

		for (i=0; i<max_precincts && !end; i++) {
			int pos = ordered_list[i];

			if (weights[pos][j] >= budget) {
				end = 1;
				break;
			}

			printf("[%d][%d]\t", pos, j);
			//printf("w[%d][%d] = %d / %f  \n", pos, j, weights[pos][j], profit[pos][j]);
			
			sum_profit = sum_profit + profit[pos][j];
			sum_bytes = sum_bytes + weights[pos][j];
			budget = budget - weights[pos][j];
		}
		printf("\n");
	}

	printf("\nSum (bytes): %ld\n", sum_bytes);
	printf("Sum (profit): %lf\n", sum_profit);
}

// max_ql: The number of the last layer that we are going to check
//
void method_3(int max_precincts, int * ordered_list, int **weights, float **profit, long max_ql) {

	printf("\n\n**** Method: 3 \tmax_ql: %ld ****\n", max_ql);

	long sum_bytes = 0;
	double sum_profit = 0;
	int end = 0;
	int i, j;

	long budget = BUDGET;

	for (i=0; i<max_precincts && !end; i++) {

		int pos = ordered_list[i];

		for(j=0; j<=max_ql && !end; j++) { 

			if (weights[pos][j] >= budget) {
				end = 1;
				break;
			}

			printf("[%d][%d]\t", pos, j);
			//printf("w[%d][%d] = %d / %f  \t", pos, j, weights[pos][j], profit[pos][j]);
			
			sum_profit = sum_profit + profit[pos][j];
			sum_bytes = sum_bytes + weights[pos][j];
			budget = budget - weights[pos][j];			
		}
		printf("\n");
	}

	printf("\nSum (bytes): %ld\n", sum_bytes);
	printf("Sum (profit): %lf\n", sum_profit);
}
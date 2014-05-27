#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "libknapsack.h"
#include "parson/parson.h"

// Read JSON Files
int get_number_of_precincts_from_json_file(char *filename);
int get_number_of_quality_layers_from_json_file(char *filename);
int load_weights_from_json_file(char *filename, long max_precincts, int max_quality_layers, long **weights);
int load_profit_from_json_file(char *filename, long max_precincts, int max_quality_layers, double **profit);

int main(int argc, char *argv[])
{
	long budget;
	long max_precincts;
	int max_quality_layers;
	long **weights;
	double **profit;
	long *ordered_list;
	int i, j;

	if (argc < 3) {
		printf("Usage: %s <filename.json> <budget>\n",argv[0]);
		exit(0);
	}

	// Get the number of precincts from JSON file
	max_precincts = (long int) get_number_of_precincts_from_json_file(argv[1]);

	if (max_precincts <= 0) {
		printf("The max number of precincts must be a positive integer\n");
		exit(0);
	}

	// Get the number of quality layers from JSON file
	max_quality_layers = get_number_of_quality_layers_from_json_file(argv[1]);

	if (max_quality_layers <= 0) {
		printf("The max number of quality layers must be a positive integer\n");
		exit(0);
	}

	// Check the intial value
	budget = atoi(argv[2]);

	if (budget <= 0) {
		printf("The budget must be a positive integer\n");
		exit(0);
	}

  	// Initialize random generator
  	srand (time(NULL));	
	
	// Allocate memory for weights
	if (allocate_memory_for_weights(max_precincts, max_quality_layers, &weights) <= 0) {
		printf("Error allocating memory for weights.\n");
		exit(1);
	}

	// Allocate memory for profit
	if (allocate_memory_for_profit(max_precincts, max_quality_layers, &profit) <= 0) {
		printf("Error allocating memory for profit.\n");
		exit(1);
	}

	// Allocate memory for ordered_list
	if (allocate_memory_for_ordered_list(max_precincts, &ordered_list) <= 0) {
		printf("Error allocating memory for ordered list.\n");
		exit(1);
	}
	
	// Read the values for weights (This step is for checking the values)
	if (load_weights_from_json_file(argv[1], max_precincts, max_quality_layers, weights) <= 0) {
		printf("Error reading the JSON file and loading the weights: %s\n", argv[1]);
		exit(1);
	}

	// Read the values for profit (This step is for checking the values)
	if (load_profit_from_json_file(argv[1], max_precincts, max_quality_layers, profit) <= 0) {
		printf("Error reading the JSON file and loading the profit: %s\n", argv[1]);
		exit(1);
	}

	// Create initial values for ordered list
	if (create_file_ordered_list(ORDERED_LIST_FILENAME, max_precincts) <= 0) {
		printf("Error creating the file for the ordered list of precincts: %s\n", ORDERED_LIST_FILENAME);
		exit(1);
	}

	// Read the values for ordered list (This step is for checking the values)
	if (read_file_ordered_list(ORDERED_LIST_FILENAME, max_precincts, ordered_list) <= 0) {
		printf("Error reading the file for the ordered list of precincts: %s\n", ORDERED_LIST_FILENAME);
		exit(1);
	}

	if (DEBUG) {
		// Print weights values
		print_weights_values(max_precincts, max_quality_layers, weights);

		// Print profit values
		print_profit_values(max_precincts, max_quality_layers, profit);

		// Print ordered_list values
		print_ordered_list_values(max_precincts, ordered_list);

		// Print all the precincts with their weight and profit
		print_precincts_weight_profit(max_precincts, max_quality_layers, weights, profit, ordered_list);	
	}

	// Check all the methods in order to find the best solution
	check_methods(max_precincts, max_quality_layers, budget, ordered_list, weights, profit);

	return 0;
}

int get_number_of_precincts_from_json_file(char *filename) {
    JSON_Object *root_object;
    JSON_Value *root_value = NULL;
    root_value = json_parse_file(filename);
    root_object = json_value_get_object(root_value);
    return (int) json_object_get_number(root_object, "number_of_precincts");
}

int get_number_of_quality_layers_from_json_file(char *filename) {
    JSON_Object *root_object;
    JSON_Array *array;
    JSON_Value *root_value = NULL;
    root_value = json_parse_file(filename);

    root_object = json_value_get_object(root_value);
    unsigned int number_of_precincts = (int) json_object_get_number(root_object, "number_of_precincts");

    array = json_object_get_array(root_object, "precincts");
    if (array != NULL && json_array_get_count(array) == number_of_precincts) {
        JSON_Object *precinct_object = json_array_get_object(array, 0);
        JSON_Array *layers_array = json_object_get_array(precinct_object, "layers");
        return json_array_get_count(layers_array);
    } else {
    	return -1;
    }
}

// Load weights from json file
int load_weights_from_json_file(char *filename, long max_precincts, int max_quality_layers, long **weights) {
    JSON_Object *root_object;
    JSON_Array *array;
    JSON_Value *root_value = NULL;
    root_value = json_parse_file(filename);

    root_object = json_value_get_object(root_value);
    unsigned int number_of_precincts = (int) json_object_get_number(root_object, "number_of_precincts");

    array = json_object_get_array(root_object, "precincts");
    if (array != NULL && json_array_get_count(array) == number_of_precincts) {
        JSON_Object *precinct_object;
        JSON_Array *layers_array;
        int id, coord_x, coord_y;
        unsigned int p;
        
		int i = 0;
		int j = 0;

        for(p = 0; p < number_of_precincts; p++) {           
            precinct_object = json_array_get_object(array, p);
            layers_array = json_object_get_array(precinct_object, "layers");
            if (layers_array != NULL && json_array_get_count(layers_array) >= 1) {
                JSON_Object *layer_object;
                int bytes;
                unsigned l;

                for(l = 0; l < json_array_get_count(layers_array); l++) {
                    layer_object = json_array_get_object(layers_array, l);
                    bytes = (long) json_object_get_number(layer_object, "bytes");

                    weights[i][j++] = bytes;

                    if (j >= max_quality_layers) {
                    	j = 0;
                    	i++;
                    }
                }
                
            } else {
				return -1;
            }
        }
    } else {
        return -1;
    }

    json_value_free(root_value);
	return 1;
}

// Load profit from json file
int load_profit_from_json_file(char *filename, long max_precincts, int max_quality_layers, double **profit) {
    JSON_Object *root_object;
    JSON_Array *array;
    JSON_Value *root_value = NULL;
    root_value = json_parse_file(filename);

    root_object = json_value_get_object(root_value);
    unsigned int number_of_precincts = (int) json_object_get_number(root_object, "number_of_precincts");

    array = json_object_get_array(root_object, "precincts");
    if (array != NULL && json_array_get_count(array) == number_of_precincts) {
        JSON_Object *precinct_object;
        JSON_Array *layers_array;
        int id, coord_x, coord_y;
        unsigned int p;
        
		int i = 0;
		int j = 0;

        for(p = 0; p < number_of_precincts; p++) {           
            precinct_object = json_array_get_object(array, p);
            layers_array = json_object_get_array(precinct_object, "layers");
            if (layers_array != NULL && json_array_get_count(layers_array) >= 1) {
                JSON_Object *layer_object;
                int psnr;
                unsigned l;

                for(l = 0; l < json_array_get_count(layers_array); l++) {
                    layer_object = json_array_get_object(layers_array, l);
                    double psnr = (double) json_object_get_number(layer_object, "psnr");

                    profit[i][j++] = psnr;

                    if (j >= max_quality_layers) {
                    	j = 0;
                    	i++;
                    }
                }
                
            } else {
				return -1;
            }
        }
    } else {
        return -1;
    }

    json_value_free(root_value);
	return 1;
}

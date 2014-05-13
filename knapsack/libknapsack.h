#define MAX_BYTES_SIZE 1000
#define MIN_PSNR_VALUE 10
#define MAX_PSNR_VALUE 50
#define DEBUG 1

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
void method_2(long max_precincts, int max_quality_layers, long budget, long * ordered_list, int **weights, double **profit, int max_ql, solution *sol);
void print_solution(solution sol);
void find_best_solution(solution sol1, solution *sol2, int max_quality_layers);
void print_weights_values(long max_precincts, int max_quality_layers, int **weights);
void print_profit_values(long max_precincts, int max_quality_layers, double **profit);
void print_ordered_list_values(long max_precincts, long *ordered_list);
void print_precincts_weight_profit(long max_precincts, int max_quality_layers, int **weights, double **profit, long *ordered_list);
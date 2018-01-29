/*
** Florian BACHO, 2018
** value iteration algorithm exemple
** File description:
** Exemple with simple 2D environment
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAP_SIZE		8
#define NB_ITERATION		30
#define NB_TRAP			5

// Rewards
#define GOAL_REWARD		1.0f
#define NORMAL_REWARD		-0.2f
#define TRAP_REWARD		-1.0f

#define DISCOUNT_FACTOR		0.5f // 0.0f < DISCOUNT_FACTOR < 1.0f

// Point structure use to define goal or traps
typedef struct point_s {
	int x;
	int y;
} point;

static const point goal = {2, 2};
static const point traps[] = {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}};

// Write values on a .dat file that are printed on gnuplot
static bool print_values(const float values[MAP_SIZE][MAP_SIZE], int iteration)
{
	FILE *stream = fopen("data.dat", "w+");

	if (!stream)
		return (false);
	fprintf(stream, "%d ", MAP_SIZE);
	for (int i = 0; i < MAP_SIZE; i++)
		fprintf(stream, "%d ", i);
	fprintf(stream, "\n");
	for (int y = 0; y < MAP_SIZE; y++) {
		fprintf(stream, "%d ", y);
		for (int x = 0; x < MAP_SIZE; x++) {
			fprintf(stream, "%f ", values[y][x]);
			printf("%7.4f ", values[MAP_SIZE - y - 1][x]);
		}
		printf("\n");
		fprintf(stream, "\n");
	}
	printf("\n");
	fclose(stream);
	return (true);
}

// Reward of a state --> R(s)
static float get_reward(int x, int y)
{
	if (x == goal.x && y == goal.y)
		return (GOAL_REWARD);
	for (int i = 0; i < NB_TRAP; i++)
		if (x == traps[i].x && y == traps[i].y)
			return (TRAP_REWARD);
	return (NORMAL_REWARD);
}

static inline void change_if_greater(float *to_change, float value)
{
	if (value > *to_change)
		*to_change = value;
}

/*
** Compute the sum of expected futur rewards (there is no sum because
** transitions probabilities are always 1) --> Sigma(P(s | s',a) * V(s'))
*/
static float get_expected_futur_reward(const float values[MAP_SIZE][MAP_SIZE],
				      int x, int y)
{
	float out = values[y][x];

	if (y > 0) {
		change_if_greater(&out, values[y - 1][x]);
	}
	if (y < MAP_SIZE - 1)
		change_if_greater(&out, values[y + 1][x]);
	if (x > 0)
		change_if_greater(&out, values[y][x - 1]);
	if (x < MAP_SIZE - 1)
		change_if_greater(&out, values[y][x + 1]);
	return (out);
}

/*
** Iterate on all states and update values with the following formula:
** V(s) = R(s) + y * Sigma(P(s | s',a) * V(s'))
*/
static void value_iterate(const float values[MAP_SIZE][MAP_SIZE],
			  float new_values[MAP_SIZE][MAP_SIZE])
{
	for (int y = 0; y < MAP_SIZE; y++)
		for (int x = 0; x < MAP_SIZE; x++)
			new_values[y][x] = get_reward(x, y) + DISCOUNT_FACTOR *
				get_expected_futur_reward(values, x, y);
}

/*
** Launch gnuplot with plot_script.p script (auto-refresh) and launch the
** value iteration algotithm
*/
int main()
{
	FILE *gnuplot = popen("gnuplot plot_script.p", "w");
	float values[MAP_SIZE][MAP_SIZE] = {{0}};
        float new_values[MAP_SIZE][MAP_SIZE];

	if (!gnuplot)
		return (1);
	memset(values, 0, sizeof(values));
	printf("Initialization\n");
	print_values(values, 0);
	for (int i = 0; i < NB_ITERATION; i++) {
		sleep(1);
		value_iterate(values, new_values);
		memcpy(values, new_values, sizeof(new_values));
		printf("Iteration %d\n\n", i + 1);
		if (!print_values(values, i + 1))
			return (1);
	}
	pclose(gnuplot);
	return (0);
}

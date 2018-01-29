/*
** EPITECH PROJECT, 2018
** value iteration algorithm exemple
** File description:
** print values function definition
*/

#include "value_iteration.h"

// Write values on a .dat file that are printed on gnuplot
bool print_values(const float values[MAP_SIZE][MAP_SIZE])
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

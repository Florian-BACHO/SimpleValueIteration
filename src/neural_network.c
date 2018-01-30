/*
** EPITECH PROJECT, 2018
** simple value iteration algorithm
** File description:
** Implementation of neural network with Fann library
*/

#include "value_iteration.h"
#include "neural_network.h"

static void save(const float values[MAP_SIZE][MAP_SIZE])
{
	FILE *stream = fopen(TRAIN_FILE_NAME, "w+");

	if (!stream)
		return;
	fprintf(stream, "%d 2 1\n", MAP_SIZE * MAP_SIZE);
	for (int y = 0; y < MAP_SIZE; y++)
		for (int x = 0; x < MAP_SIZE; x++)
			fprintf(stream, "%d %d\n%f\n", x, y, values[y][x]);
	fclose(stream);
}

void test_learning(const float values[MAP_SIZE][MAP_SIZE])
{
	struct fann *ann = fann_create_standard(4, 2, 20, 20, 1);
	float entries[2];

	save(values);
	printf("=== Neural Network Training ===\n\n");
	if (!ann)
		return;
	fann_randomize_weights(ann, -0.5f, 0.5f);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_LINEAR);

	fann_train_on_file(ann, TRAIN_FILE_NAME,
			   MAX_EPOCH, EPOCH_BETWEEN_REPORTS, DESIRED_ERROR);

	for (int y = 0; y < MAP_SIZE; y++) {
		for (int x = 0; x < MAP_SIZE; x++) {
			entries[0] = x;
			entries[1] = MAP_SIZE - y - 1;
			printf("%7.4f ", *fann_run(ann, entries));
		}
		printf("\n");
	}
	fann_destroy(ann);
}

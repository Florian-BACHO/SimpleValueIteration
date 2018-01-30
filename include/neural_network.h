/*
** EPITECH PROJECT, 2018
** simple value iteration algorithm
** File description:
** Implementation of neural network with Fann library
*/

#ifndef NEURAL_NETWORK_H_
	#define NEURAL_NETWORK_H_

	#include "fann.h"
	#include "value_iteration.h"

	#define TRAIN_FILE_NAME		"environment.train"
	#define MAX_EPOCH		100000
	#define EPOCH_BETWEEN_REPORTS	1000
	#define DESIRED_ERROR		0.00001

	void test_learning(const float values[MAP_SIZE][MAP_SIZE]);

#endif

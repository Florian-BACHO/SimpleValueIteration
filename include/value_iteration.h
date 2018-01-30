/*
** EPITECH PROJECT, 2018
** value iteration algorithm exemple
** File description:
** header file
*/

#ifndef VALUE_ITERATION_H_
	#define VALUE_ITERATION_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	#include <unistd.h>

	#define MAP_SIZE		8
	#define NB_ITERATION		10
	#define NB_TRAP			5

	// Rewards
	#define GOAL_REWARD		1.0f
	#define NORMAL_REWARD		-0.2f
	#define TRAP_REWARD		-1.0f

	#define DISCOUNT_FACTOR         0.5f // 0.0f < DISCOUNT_FACTOR < 1.0f

	// Point structure use to define goal or traps
	typedef struct point_s {
		int x;
		int y;
	} point;

	bool print_values(const float values[MAP_SIZE][MAP_SIZE]);

#endif

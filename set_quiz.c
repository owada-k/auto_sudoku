// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - set quiz data
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include <stdio.h>

int set_start_value(int pos_x_size, int pos_y_size, 
	struct sudoku_cell cell[pos_x_size][pos_y_size], int sudoku_quiz[pos_x_size][pos_y_size])
{
	int			pos_x, pos_y;
	int			ret = OK;

	for(pos_y = 0; pos_y < pos_y_size; pos_y++) {
		for(pos_x = 0; pos_x < pos_x_size; pos_x++) {

			/* skip if quiz cell is empty */
			if (sudoku_quiz[pos_y][pos_x] == 0) continue;

			/* set quiz value in candidates, then use set_value() for set value */
			ret = check_candidate(sudoku_quiz[pos_y][pos_x], &cell[pos_x][pos_y]);
			if (ret != OK) goto exit_loop;

			ret = set_value(sudoku_quiz[pos_y][pos_x], &cell[pos_x][pos_y]);
			if (ret != OK) goto exit_loop;
		}
	}

exit_loop:

	return ret;
}

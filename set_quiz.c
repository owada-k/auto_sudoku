// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - set quiz data
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include <stdio.h>

int set_start_value(struct sudoku_cell cell[POS_SIZE][POS_SIZE], int sudoku_quiz[POS_SIZE][POS_SIZE])
{
	int			pos_x, pos_y;
	int			ret = OK;
	struct sudoku_cell_info cell_info;

	for(pos_y = 0; pos_y < POS_SIZE; pos_y++) {
		for(pos_x = 0; pos_x < POS_SIZE; pos_x++) {

			/* skip if quiz cell is empty */
			if (sudoku_quiz[pos_y][pos_x] == 0) continue;

			/* set quiz value in candidates, then use set_value() for set value */
			cell_info.value = sudoku_quiz[pos_y][pos_x];
			cell_info.cell_p = &cell[pos_x][pos_y];
			ret = check_candidate(&cell_info);
			if (ret != OK) goto exit_loop;

			ret = set_value(&cell_info);
			if (ret != OK) goto exit_loop;
		}
	}

exit_loop:

	return ret;
}

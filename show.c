// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - show cells
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include <stdio.h>

int cell_show(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size])
{
	int			pos_x, pos_y;

	printf("\033[14A");

	printf("  1 2 3 4 5 6 7 8 9\n");
	printf("  -----------------\n");

	for(pos_y = 0; pos_y < pos_y_size; pos_y++) {
		printf("%d|", pos_y + 1);
		for(pos_x = 0; pos_x < pos_x_size; pos_x++) {
			if (cell[pos_x][pos_y].value == 0) {
				printf(".");
			} else {
				printf("%d",cell[pos_x][pos_y].value);
			}
			if ((pos_x + 1) % BOX_SIZE == 0) {
				printf("|");
			} else {
				printf(" ");
			}
		}
		printf("\n");
		if ((pos_y + 1) % BOX_SIZE == 0) {
			printf("  ----------------- \n");
		}
	}

	return OK;
}

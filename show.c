// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - show cells
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include <stdio.h>

#define	SET_COLOR_JUST_FOUND	printf("\033[31m")
#define	SET_COLOR_default	printf("\033[39m")

int cell_show(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size])
{
	int			pos_x, pos_y;

	printf("  1 2 3 4 5 6 7 8 9\n");
	printf("  -----------------\n");

	for(pos_y = 0; pos_y < pos_y_size; pos_y++) {
		printf("%d|", pos_y + 1);
		for(pos_x = 0; pos_x < pos_x_size; pos_x++) {
			if (cell[pos_x][pos_y].value == 0) {
				printf(".");
			} else {
				if (cell[pos_x][pos_y].flag == NOT_FOUND) {
					SET_COLOR_JUST_FOUND;
					cell[pos_x][pos_y].flag = JUST_FOUND;
				}

				printf("%d",cell[pos_x][pos_y].value);

				if (cell[pos_x][pos_y].flag == JUST_FOUND) {
					SET_COLOR_default;
					cell[pos_x][pos_y].flag = FOUND;
				}
			}
			if ((pos_x + 1) % BOX_SIZE == 0) {
				printf("|");
			} else {
				printf(" ");
			}
		}
		printf("\n");
		if ((pos_y + 1) % BOX_SIZE == 0) {
			printf("  -----------------\n");
		}
	}

	return OK;
}

// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - show cells
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include <stdio.h>
#define SetColor_Frame	printf("\033[32m") /* Green */
#define SetColor_default	printf("\033[39m")

int cell_show(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size])
{
	int			pos_x, pos_y;

	SetColor_Frame;
	printf("  1 2 3 4 5 6 7 8 9\n");
	printf("  -----------------\n");
	SetColor_default;

	for(pos_y = 0; pos_y < pos_y_size; pos_y++) {
		SetColor_Frame;
		printf("%d|", pos_y + 1);
		SetColor_default;
		for(pos_x = 0; pos_x < pos_x_size; pos_x++) {
			if (cell[pos_x][pos_y].value == 0) {
				printf(".");
			} else {
				printf("%d",cell[pos_x][pos_y].value);
			}
			if ((pos_x + 1) % BOX_SIZE == 0) {
				SetColor_Frame;
				printf("|");
				SetColor_default;
			} else {
				printf(" ");
			}
		}
		printf("\n");
		if ((pos_y + 1) % BOX_SIZE == 0) {
			SetColor_Frame;
			printf("  -----------------\n");
			SetColor_default;
		}
	}

	return OK;
}

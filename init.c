// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - initialization
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"

int cell_init(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size])
{
	int			pos_x, pos_y;
	int			i;

	for(pos_y = 0; pos_y < pos_y_size; pos_y++) {
		for(pos_x = 0; pos_x < pos_x_size; pos_x++) {
			cell[pos_x][pos_y].value = 0;

			for(i=0; i < NUMBER_SIZE+1; i++) {
				cell[pos_x][pos_y].candidates[i] = POSSIBLE;
			}

			cell[pos_x][pos_y].pos_x = pos_x;
			cell[pos_x][pos_y].pos_y = pos_y;

			cell[pos_x][pos_y].link_x_p = &cell[pos_x][pos_y].link_x;
			cell[pos_x][pos_y].link_y_p = &cell[pos_x][pos_y].link_y;
			cell[pos_x][pos_y].link_box_p = &cell[pos_x][pos_y].link_box;
			cell[pos_x][pos_y].link_all_p = &cell[pos_x][pos_y].link_all;
		}
	}

	for(pos_y = 0; pos_y < pos_y_size; pos_y++) {
		for(pos_x = 0; pos_x < pos_x_size; pos_x++) {
			if (pos_x + 1 < pos_x_size) {
				cell[pos_x][pos_y].link_x_p->next_p = cell[pos_x+1][pos_y].link_x_p;
			} else {
				cell[pos_x][pos_y].link_x_p->next_p = cell[0][pos_y].link_x_p;
			}
			cell[pos_x][pos_y].link_x_p->this_cell_p = &cell[pos_x][pos_y];

			if (pos_y + 1 < pos_y_size) {
				cell[pos_x][pos_y].link_y_p->next_p = cell[pos_x][pos_y+1].link_y_p;
			} else {
				cell[pos_x][pos_y].link_y_p->next_p = cell[pos_x][0].link_y_p;
			}
			cell[pos_x][pos_y].link_y_p->this_cell_p = &cell[pos_x][pos_y];

			if (pos_x + 1 < ((pos_x + BOX_SIZE)/BOX_SIZE)*BOX_SIZE) {
				cell[pos_x][pos_y].link_box_p->next_p = cell[pos_x+1][pos_y].link_box_p;
			} else if (pos_y + 1 < ((pos_y + BOX_SIZE)/BOX_SIZE)*BOX_SIZE) {
				cell[pos_x][pos_y].link_box_p->next_p = cell[(pos_x/BOX_SIZE)*BOX_SIZE][pos_y+1].link_box_p;
			} else {
				cell[pos_x][pos_y].link_box_p->next_p = cell[(pos_x/BOX_SIZE)*BOX_SIZE][(pos_y/BOX_SIZE)*BOX_SIZE].link_box_p;
			}
			cell[pos_x][pos_y].link_box_p->this_cell_p = &cell[pos_x][pos_y];

			if (pos_x + 1 < ((pos_x + POS_SIZE)/POS_SIZE)*POS_SIZE) {
				cell[pos_x][pos_y].link_all_p->next_p = cell[pos_x+1][pos_y].link_all_p;
			} else if (pos_y + 1 < ((pos_y + POS_SIZE)/POS_SIZE)*POS_SIZE) {
				cell[pos_x][pos_y].link_all_p->next_p = cell[(pos_x/POS_SIZE)*POS_SIZE][pos_y+1].link_all_p;
			} else {
				cell[pos_x][pos_y].link_all_p->next_p = cell[(pos_x/POS_SIZE)*POS_SIZE][(pos_y/POS_SIZE)*POS_SIZE].link_all_p;
			}
			cell[pos_x][pos_y].link_all_p->this_cell_p = &cell[pos_x][pos_y];
		}
	}

	return OK;
}

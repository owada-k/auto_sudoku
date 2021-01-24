// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - struct definitions
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#define	NUMBER_SIZE		9
#define	POS_SIZE		NUMBER_SIZE
#define	BOX_SIZE		3 /* sqrt(NUMBER_SIZE) */
#define	POSSIBLE		1
#define	IMPOSSIBLE		0
#define	OK			0
#define	NG			1
#define ERROR			-1
#define NULL			0x0

struct cell_link;
struct sudoku_cell;

struct cell_link {
	struct cell_link	*next_p;
	struct sudoku_cell	*this_cell_p;
};

struct sudoku_cell {
	int			value;
	int			candidates[NUMBER_SIZE+1];
	int			pos_x, pos_y;
	struct cell_link	link_x, link_y, link_box, link_all;
	struct cell_link	*link_x_p, *link_y_p, *link_box_p, *link_all_p;
};

int cell_init(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size]);
int cell_show(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size]);
int set_start_value(int pos_x_size, int pos_y_size, struct sudoku_cell cell[pos_x_size][pos_y_size], int sudoku_quiz[pos_x_size][pos_y_size]);
int check_candidate(int cantidate_value, struct sudoku_cell *cell_p);
int set_value(int cantidate_value, struct sudoku_cell *cell_p);
int check_cells(struct sudoku_cell *cell_p);
int search_cell(struct sudoku_cell **cell_pp, int *val_p);


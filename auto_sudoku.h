// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - struct definitions
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include <pthread.h>

#define	NUMBER_SIZE		9
#define	POS_SIZE		NUMBER_SIZE
#define	BOX_SIZE		3 /* sqrt(NUMBER_SIZE) */
#define	POSSIBLE		1
#define	IMPOSSIBLE		0
#define	OK			0
#define	NG			1
#define ERROR			-1
#define TRUE			-1
#define FALSE			0x0

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

struct sudoku_cell_info {
	struct sudoku_cell	*cell_p;
	int			value;
};

int cell_init(struct sudoku_cell cell[POS_SIZE][POS_SIZE]);
int cell_show(struct sudoku_cell cell[POS_SIZE][POS_SIZE]);
int set_start_value(struct sudoku_cell cell[POS_SIZE][POS_SIZE], int sudoku_quiz[POS_SIZE][POS_SIZE]);
int check_candidate(struct sudoku_cell_info *cell_info_p);
int set_value(struct sudoku_cell_info *cell_info_p);
int check_cells(struct sudoku_cell *cell_p);
int search_cell(struct sudoku_cell_info *cell_info_p);

extern pthread_mutex_t	mtx;
extern pthread_cond_t cnd;
extern int data_updated;
extern int value_found;


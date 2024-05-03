// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - main
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include "quiz.h"
#include <stdio.h>
#include <pthread.h>

int main(void)
{
	int			ret;
	struct sudoku_cell	cell[POS_SIZE][POS_SIZE];
	int			sudoku_quiz[POS_SIZE][POS_SIZE] = QUIZ_DATA;
	struct sudoku_cell_info cell_info;
	int			search_iteration;

	ret = cell_init(cell);
	if (ret != OK) { ret = -1; goto exit_sub; }

	/* printf("\033[15B"); */
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n");
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n");
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n");
	printf("\n"); printf("\n"); printf("\n");
	
	ret = set_start_value(cell, sudoku_quiz);
	if (ret != OK) { ret = -3; goto exit_sub; }

	ret = cell_show(cell);
	if (ret != OK) { ret = -4; goto exit_sub; }

	/* start solving quiz */
	cell_info.cell_p = &cell[0][0];
	search_iteration = 0;
	do {
		search_iteration++;

		ret = search_cell(&cell_info);
		if (ret != OK) {
			/* error */
			goto exit_sub;
		}

		if (cell_info.cell_p != 0) {
			/* find cell to be decided */
                        ret = check_candidate(&cell_info);
                        if (ret != OK) goto exit_sub;

                        ret = set_value(&cell_info);
                        if (ret != OK) goto exit_sub;

			printf("*** iteration %d ***\n", search_iteration);
			printf("\033[1A");
			ret = cell_show(cell);
			getchar(); printf("\033[1A");
			if (ret != OK) { ret = -2; goto exit_sub; }

			cell_info.cell_p = cell_info.cell_p->link_all_p->next_p->this_cell_p;
		}
	} while (cell_info.cell_p != 0);
	ret = OK;

	printf("***** Finished *****\n");

exit_sub:
	if (ret != OK) printf("Error (ret = %d)\n", ret);

	return ret;
}

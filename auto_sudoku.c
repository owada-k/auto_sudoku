// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - main
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"
#include "quiz.h"
#include <stdio.h>

	pthread_mutex_t	mtx;
	pthread_cond_t cnd;
	int data_updated;
	int value_found;

int main(void)
{
	int			ret;
	struct sudoku_cell	cell[POS_SIZE][POS_SIZE];
	int			sudoku_quiz[POS_SIZE][POS_SIZE] = QUIZ_DATA;
	struct sudoku_cell_info cell_info;
	int			search_iteration;

	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cnd, NULL);
	data_updated = FALSE;
	value_found = FALSE;
	pthread_t show_thread, search_thread, update_thread;

	ret = cell_init(cell);
	if (ret != OK) { ret = -1; goto exit_sub; }

	/* printf("\033[15B"); */
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n");
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n");
	printf("\n"); printf("\n"); printf("\n"); printf("\n"); printf("\n");
	printf("\n"); printf("\n"); printf("\n");

	ret = pthread_create(&show_thread, NULL, (void *)cell_show, cell);
	if (ret != OK) { ret = -2; goto exit_sub; }

	ret = set_start_value(cell, sudoku_quiz);
	if (ret != OK) { ret = -3; goto exit_sub; }
	pthread_mutex_lock(&mtx);
		data_updated = TRUE;
		pthread_cond_broadcast(&cnd);
	pthread_mutex_unlock(&mtx);
	
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

			pthread_mutex_lock(&mtx);
				data_updated = TRUE;
				pthread_cond_broadcast(&cnd);
			pthread_mutex_unlock(&mtx);

			getchar(); printf("\033[1A");
			if (ret != OK) { ret = -2; goto exit_sub; }

			cell_info.cell_p = cell_info.cell_p->link_all_p->next_p->this_cell_p;
		}
	} while (cell_info.cell_p != 0);
	ret = OK;

	printf("***** Finished *****\n");

exit_sub:
	if (ret != OK) printf("Error (ret = %d)\n", ret);

	pthread_cancel(show_thread);
	pthread_join(show_thread, NULL);

	return ret;
}

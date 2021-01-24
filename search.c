// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - search cell to decide value
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"

int search_in_link(int val, struct cell_link *link_p);

/*
 * function diffinition
 *	If ret is OK then *cell_pp indicates ths cell which should be set
 *	*val_p as its value.
 *	When all cells has value, ret is OK and *cell_p is NULL.
 *	If ret is NG, there is no cell for setting value.
 * 	If ret is ERROR, there is something wrong.
 */
int search_cell(struct sudoku_cell **cell_pp, int *val_p)
{
	struct cell_link	*start_link_p;
	struct cell_link	*link_p;
	int			val, candidate;
	int			count, count_already_decided, count_candidate;
	int			ret, found;

	start_link_p = (*cell_pp)->link_all_p;
	link_p = start_link_p;
	count = 0;
	count_already_decided = 0;

	ret = NG;
	do {
		if (link_p->this_cell_p->value != 0) {
			/* already decided */
			count_already_decided++;
			goto next_link;
		}

		count_candidate = 0;
		found = NG;
		for (val = 1; val < NUMBER_SIZE + 1; val++) {
			if (link_p->this_cell_p->candidates[val] == POSSIBLE) {
				count_candidate++;
				candidate = val;

				found = search_in_link(val, link_p->this_cell_p->link_x_p);
				if (found == OK) {
					/* find candidate */
					break;
				} else if (found == NG) {
					/* val is not candidate */
				} else {
					/* error */
					ret = ERROR;
					goto exit_sub;
				}


				found = search_in_link(val, link_p->this_cell_p->link_y_p);
				if (found == OK) {
					/* find candidate */
					break;
				} else if (found == NG) {
					/* val is not candidate */
				} else {
					/* error */
					ret = ERROR;
					goto exit_sub;
				}

				found = search_in_link(val, link_p->this_cell_p->link_box_p);
				if (found == OK) {
					/* find candidate */
					break;
				} else if (found == NG) {
					/* val is not candidate */
				} else {
					/* error */
					ret = ERROR;
					goto exit_sub;
				}
			}
		}

		if ((found == OK) || (count_candidate == 1)) {
			*cell_pp = link_p->this_cell_p;
			*val_p = candidate;
			ret = OK;
			break;
		}

next_link:
		link_p = link_p->next_p;
		count++;
		if (count > (NUMBER_SIZE * NUMBER_SIZE)) {
			ret = ERROR;
			goto exit_sub;
		}
	} while(link_p != start_link_p);

	if (count_already_decided == (NUMBER_SIZE * NUMBER_SIZE)) {
		/* all cell has been decided */
		*cell_pp = (struct sudoku_cell *) NULL;
		ret = OK;
	}

exit_sub:
	return ret;
}

int search_in_link(int val, struct cell_link *link_p)
{
	struct cell_link	*start_link_p;
	int			count;
	int			ret;

	ret = OK;
	start_link_p = link_p;

	count = 0;
	for(link_p = start_link_p->next_p; link_p != start_link_p; link_p = link_p->next_p) {
		if (link_p->this_cell_p->candidates[val] == POSSIBLE) {
			ret = NG;
			break;
		}
		
		count++;
		if (count > NUMBER_SIZE) {
			/* iterate more than expected */
			ret = ERROR;
			break;
		}
	}

	return ret;
}

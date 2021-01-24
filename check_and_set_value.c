// SPDX-License-Identifier: BSD-2-Clause
/*
 *  Auto Sudoku program - check and set value
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#include "auto_sudoku.h"



int check_value_in_link(int value, struct cell_link *start_link_p);
int set_value_in_link(int value, struct cell_link *start_link_p);

int check_candidate(int candidate_value, struct sudoku_cell *cell_p)
{
	int			ret = OK;

	if (cell_p->value != 0) {
		ret = ERROR;
		goto exit_sub;
	}

	ret = check_value_in_link(candidate_value, cell_p->link_x_p);
	if (ret != OK) {
		goto exit_sub;
	}

	ret = check_value_in_link(candidate_value, cell_p->link_y_p);
	if (ret != OK) {
		goto exit_sub;
	}

	ret = check_value_in_link(candidate_value, cell_p->link_box_p);
	if (ret != OK) {
		goto exit_sub;
	}

exit_sub:
	return ret;
}

int check_value_in_link(int value, struct cell_link *start_link_p)
{
	struct cell_link	*link_p;
	int			val, candidate_count;
	int			count = 0;
	int			ret = OK;

	link_p = start_link_p->next_p;
	while(link_p != start_link_p) {
		if (link_p->this_cell_p->value == value) {
			ret = NG;
			goto exit_sub;
		}

		candidate_count = 0;
		for (val = 1; val < NUMBER_SIZE + 1; val++) {
			if (val == value) continue;

			if (link_p->this_cell_p->candidates[val] == POSSIBLE) {
				candidate_count++;
			}
		}
		if (candidate_count == 0) {
			ret = NG;
			break;
		}


		count++;
		if (count > NUMBER_SIZE) {
			ret = ERROR;
			break;
		}

		link_p = link_p->next_p;
	}

exit_sub:

	return ret;
}

int set_value(int value, struct sudoku_cell *cell_p)
{
	int			ret = OK;
	int			val;

	ret = set_value_in_link(value, cell_p->link_x_p);
	if (ret != OK) goto exit_sub;

	ret = set_value_in_link(value, cell_p->link_y_p);
	if (ret != OK) goto exit_sub;

	ret = set_value_in_link(value, cell_p->link_box_p);
	if (ret != OK) goto exit_sub;

exit_sub:
	if (ret == OK) {
		cell_p->value = value;

		for(val = 1; val < NUMBER_SIZE ; val++) {
			if (val == value) continue;

			cell_p->candidates[val] = IMPOSSIBLE;
		}
	}

	return ret;
}

int set_value_in_link(int value, struct cell_link *start_link_p)
{
	struct cell_link	*link_p;
	int			count = 0;
	int			ret = OK;

	link_p = start_link_p->next_p;
	while(link_p != start_link_p) {

		link_p->this_cell_p->candidates[value] = IMPOSSIBLE;

		count++;
		if (count > NUMBER_SIZE) {
			ret = ERROR;
			break;
		}

		link_p = link_p->next_p;
	}


	return ret;
}


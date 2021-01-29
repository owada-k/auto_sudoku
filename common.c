// SPDX-License-Identifier: BSD-2-Clause
/*
 *  common functions
 *
 *  Copyright (C) 2021 Kiyoshi Owada
 */

#define DBG_HOOK()	dbg_hook()

int dbg_hook(int ret)
{
	/* this is dummy function to break program for debugging */
	return ret;
}

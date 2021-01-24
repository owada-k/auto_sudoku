#// SPDX-License-Identifier: BSD-2-Clause
#
#  Auto Sudoku program - Makefile
#
# Copyright (C) Kiyoshi Owada (owada.kiyoshi@gmail.com), 2021
#

CC	= gcc
CFLAGS	= -O0 -Wall -MD -g

ifdef QUIZ_SEL
  CFLAGS	+= -DQUIZ_SEL=$(QUIZ_SEL)
endif

LDFLAGS	=

OBJS	= auto_sudoku.o init.o show.o set_quiz.o check_and_set_value.o \
	  search.o

PROGRAM	= auto_sudoku

$(PROGRAM):	$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

-include	$(OBJS:%.o=%.d)

.PHONY:	clean
clean:
	rm -f *.o *.d $(PROGRAM)


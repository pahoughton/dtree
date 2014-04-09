#
# Title:        Makefile
# Project:	dtree
# Author:	Paul A. Houghton - (paul4hough@gmail.com)
# Created:	05/12/99 12:55
#

CFLAGS		= # -Wall
CPPFLAGS	= -I.

C_SOURCES	=	\
	dtree.c		\
	dir_tree.c	\
	log_err.c	\

OBJECTS		= $(C_SOURCES:.c=.o)

default: dtree

clean:
	rm -f dtree $(OBJECTS)

dtree: $(OBJECTS)

check: dtree
	dtree

install:
	install dtree /usr/local/bin

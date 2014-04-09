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
	./dtree

install:
	install dtree /usr/local/bin

.wiki_tmp:
	mkdir -p $@

update_wiki: .wiki_tmp
	pushd .wiki_tmp;					\
	[ -d dtree.wiki ]					\
	  || git clone git@github.com:pahoughton/dtree.wiki;	\
	cd dtree.wiki && git pull;				\
	cp ../../README.md Home.md;				\
	if git diff --exit-code ; then				\
	  echo no changes;					\
	else							\
	  git add Home.md;					\
	  git commit -m 'updated from README.md';		\
	  git push;						\
	fi

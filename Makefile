#
# Title:        Makefile
# Project:	dtree
# Desc:
# 
#   
# 
# Notes:
# 
# Author:	Paul A. Houghton - (paul.houghton@wcom.com)
# Created:	05/12/99 12:55
#
# Revision History: (See end of file for Revision Log)
#
#   Last Mod By:    $Author$
#   Last Mod:	    $Date$
#   Version:	    $Revision$
#
#   $Id$
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




#
# $Log$
# Revision 1.4  1999/05/12 20:14:01  houghton
# Cleanup.
#
# Revision 1.3  1999/05/12 18:59:04  houghton
# Complete Rework.
#
#

# Local Variables:
# mode:makefile
# End:

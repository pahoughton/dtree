#
# Make rules for dtree
#
# 11/30/91
#
#	$Id$
#


PROGRAM	=	dtree

SOURCES = 		\
	dtree.c		\
	dir_tree.c
#
#	Base directory for local libs and includes
#
LCL_BASE_DIR	=	/usr/local

CC			=	/usr/lang/acc
CFLAGS		=	-O 
CPPFLAGS	=	 $(INC_DIRS)
LINT		=	/usr/lang/alint
LDFLAGS		=	


ANSI_INC_DIR	=	/usr/lang/SC1.0/ansi_include
SYB_INC_DIR		=	$(SYBASE)/include
LCL_INC_DIR 	=	$(LCL_BASE_DIR)/include

INC_DIRS		=	-I$(ANSI_INC_DIR) -I$(SYB_INC_DIR) -I$(LCL_INC_DIR)

SYB_LIBS 		=	$(SYBASE)/lib/libsybdb.a 
LCL_LIBS		=	$(LCL_BASE_DIR)/lib/libl.a

LIBS			=	$(LCL_LIBS) $(SYB_LIBS) -lm

OBJ_DIR			=	objects
DBG_DIR			=	debug
PROF_DIR		=	profile

OBJECTS			=	$(SOURCES:.c=.o)

LINTFILES 		=	$(SOURCES:.c=.ln)

DEBUG			=	$(PROGRAM:%=debug/%)
PROFILE			=	$(PROGRAM:%=profile/%)


all:			$(PROGRAM)
variants:		debug profile

debug:			$(DEBUG) 
profile:		$(PROFILE) 


$(DEBUG)	:=	CFLAGS= -g 
$(PROFILE)	:=	CFLAGS= -pg -O

$(PROGRAM)	:=	VARIANTS.o= $(OBJECTS:%=$(OBJ_DIR)/%)
$(DEBUG)	:=	VARIANTS.o= $(OBJECTS:%=$(DBG_DIR)/%)
$(PROFILE)	:=	VARIANTS.o= $(OBJECTS:%=$(PROF_DIR)/%)


$(DEBUG) $(PROFILE) $(PROGRAM): $$(VARIANTS.o) $(LCL_LIBS) $(SYB_LIBS)
	$(LINK.c) -o $@ $(VARIANTS.o) $(LIBS)
	
$(PROF_DIR)/%.o $(DBG_DIR)/%.o $(OBJ_DIR)/%.o: %.c $(INCLUDES)
	$(COMPILE.c) -o $@ $<



lint:	$(SOURCES)
	$(LINT) $(CPPFLAGS) $(SOURCES)

source_print:	cflow
	/usr/5bin/pr -o5 -e4  cflow.out Makefile $(INCLUDES) $(SOURCES) | lpr

cflow:
	cflow $(SOURCES) >cflow.out

	
linecount:
	@wc $(SOURCES) $(INCLUDES)
	@ls $(SOURCES) | wc

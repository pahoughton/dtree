/*********************************************************************
*
*	Title:			dtree
*
*	Description:
*
*		list directroy tree
*
*	Input Agrs:
*
*		NONE
*
*	Return Values:
*
*		NONE
*
*	DB access:
*
*		procs:
*
*		tables:		rw:
*
*	Notes:
*
*	Programmer:		Paul Houghton
*
*	Start Date:		12-04-1991
*
*	Modification History:
*
*		$Log$
*		Revision 1.3  1999/05/12 18:59:14  houghton
*		Cleanup.
*		
 * Revision 1.1  1991/12/19  01:31:56  paulh
 * Initial revision
 *
*
*********************************************************************/

static char RcsId[] = {"$Id$"};

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <memory.h>

#include <log_err.h>

char	usage_msg[] = 
	{"Usage: %s dirname [-[D|d][S|s][F|f]] [-l logfilename]\n"};
	
int main(int argc, char *argv[])
{

	int				optind;				/* program arg */
	int				flags;
	int				opt;				/* program option */
	int				req_arg_cnt = 0;	/* required arg count */	
	char			log_fn[FILENAME_MAX];
	
	char			dir_name[FILENAME_MAX];
	

strcpy(dir_name,".");	

	/* Default Log Options */
log_debug(OFF);
log_screen(ON);
log_file(OFF);

sprintf(log_fn,"%s.%s","error",argv[0]);
log_filename(log_fn);

	/* process program options and bp_begin/end */
	
if(argc < 1)
	{
	fprintf(stderr,usage_msg,argv[0],"Too Few Args");
	exit(1);
	}

	/* get begin bill period date */

for(optind = 1; optind < argc; optind++)
	{
	if(argv[optind][0] == '-')
		{
		flags = optind;
		for(opt = 1;argv[flags][opt] != 0; opt++)
			{
			switch(argv[optind][opt])	
				{
				case 'D':
					log_debug(ON);
					break;
				
				case 'd':
					log_debug(OFF);
					break;
				
				case 'F':
					log_file(ON);
					break;
				
				case 'f':
					log_file(OFF);
					break;
					
				case 'S':
					log_screen(ON);
					break;
				
				case 's':
					log_screen(OFF);
					break;
					
				case 'l':
					optind++;
					log_filename(argv[optind]);
					break;
									
					
				default:
					fprintf(stderr,usage_msg,argv[0],argv[optind]);
					exit(1);
				}
			}
		}
	else
		{
		switch(req_arg_cnt)
			{
			case 0:
				strcpy(dir_name,argv[optind]);
				req_arg_cnt++;
				break;
			
			default:
				fprintf(stderr,usage_msg,argv[0],argv[optind]);
				exit(1);
			
			}
		}
	}

dir_tree(dir_name,0);
exit(0);
}

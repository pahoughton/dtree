/*********************************************************************
*
*	Title:			
*
*	Description:
*
*
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
*		Revision 1.2  1999/05/12 18:59:11  houghton
*		Cleanup.
*		
 * Revision 1.1  1991/12/19  01:31:55  paulh
 * Initial revision
 *
*
*
*********************************************************************/
static char RcsId[] = {"$Id$"};

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <log_err.h>

int dir_tree(char *dir_name, int level)
{

	DIR				*dirp;
	struct	dirent	*dp;
	int				l;
	struct	stat	d_stat;
	char			path[FILENAME_MAX + 1];
	
	

dirp = opendir(dir_name);

if(dirp == NULL)
	{
	log_err(errno,0,1,"Error Opening Directory: %s",dir_name);
	return(-1);
	}

for(l = 0; l < level; l++)
	{
	printf("   |");
	}
if(level)
	{
	printf("---%s\n",strrchr(dir_name,'/') + 1);
	}
else
	{
	printf("%s\n",dir_name);
	}
	
while( (dp = readdir(dirp)) != NULL)
	{
	if(strcmp(dp->d_name,".") && strcmp(dp->d_name,".."))
		{
		sprintf(path,"%s/%s",dir_name,dp->d_name);
		
		stat(path,&d_stat);
		if( S_ISDIR(d_stat.st_mode) && !(S_ISLNK(d_stat.st_mode)) )
			{
			dir_tree(path,level + 1);
			}
		}
	}
closedir(dirp);
}

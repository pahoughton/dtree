/*********************************************************************
 *
 * File:        dir_tree.c
 * Project:	dtree
 * Desc:
 *
 *  
 *
 * Notes:
 *
 * Author:	Paul A. Houghton - (paul4hough@gmail.com)
 * Created:	12/04/1991
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 *********************************************************************/

const char dtree_dir_tree_RcsId[] = {
  "$Id$"
};

#include "dtree.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <log_err.h>

extern const char ** Ignore;

int dir_tree( const char *dir_name, int level)
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
      const char ** ign;
      
      for( ign = Ignore; *ign ; ++ ign )
	if( strcmp( dp->d_name, *ign ) == 0 )
	  break;
      
      if( ! *ign )
	{
	  /* not one of the ignore strings */
	  sprintf(path,"%s/%s",dir_name,dp->d_name);
		
	  stat(path,&d_stat);
	  if( S_ISDIR(d_stat.st_mode) && !(S_ISLNK(d_stat.st_mode)) )
	    {
	      dir_tree(path,level + 1);
	    }
	}
    }
  closedir(dirp);
  return( 0 );
}

/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 1.3  1999/05/12 20:13:48  houghton
 * Added 'ignore' support (ignore files named ... (CVS)).
 * More cleanup.
 *
 * Revision 1.1  1991/12/19  01:31:55  paulh
 * Initial revision
 *
 * Revision 1.2  1999/05/12 18:59:11  houghton
 * Cleanup.
 */

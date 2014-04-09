/**

   File:        dtree.c
   Project:     dtree
   Desc:

    list directroy tree

   Notes:

   Author:      Paul A. Houghton - (paul.houghton@wcom.com)
   Created:     12/04/1991

   Revision History: (See end of file for Revision Log)

    Last Mod By:    $Author$
    Last Mod:       $Date$
    Version:        $Revision$

  ********************************************************************/


const char dtree_RcsId[] = {
  "$Id$"
};

#include "dtree.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <memory.h>
#include <getopt.h>

#include <log_err.h>

char    usage_msg[] =
{
  "Usage: %s dirname [-[D|d][S|s][F|f]] [-l logfilename]\n"
  "\n"
  "  -D         turn on debug output\n"
  "  -d         turn off debug output (default)\n"
  "  -S         turn on log to screen (default)\n"
  "  -s         turn off log to screen\n"
  "  -F         turn on log to file\n"
  "  -s         turn of log to file\n"
  "  -l fn      log file name\n"
  "  -i ignore  file names to ignore (CVS|RCS|SCCS)\n"
};

const char ** Ignore = 0;

static const char * IgnoreSep = { " \t,|:" };

int main(int argc, char *argv[])
{

  int   opt;                    /* program option */
  char  log_fn[FILENAME_MAX];

  char *    ignoreArg = strdup( "CVS|RCS|SCCS" );

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

  while( (opt = getopt( argc, argv, "DdFfi:Ssl:" )) != EOF )
    {
      switch( opt )
        {
        case 'D':
          log_debug( ON );
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

        case 'i':
          ignoreArg = strdup( optarg );
          break;

        case 'S':
          log_screen(ON);
          break;

        case 's':
          log_screen(OFF);
          break;

        case 'l':
          optind++;
          log_filename( optarg );
          break;

        default:
          fprintf(stderr, usage_msg, argv[0] );
          exit(1);
        }
    }

  if( ignoreArg )
    {
      size_t  ig = 0;
      size_t  isize = 16;
      char *  tokarg = ignoreArg;
      char *  i;

      if( (Ignore = (const char **)malloc( sizeof( char * ) * isize ))
          == NULL )
        {
          log_err(errno,0,1,"malloc failed." );
          exit( 1 );
        }

      Ignore[ ig ] = strdup( "." );
      ++ ig;
      Ignore[ ig ] = strdup( ".." );
      ++ ig;
      Ignore[ ig ] = 0;

      while( ( i = strtok( tokarg, IgnoreSep )) != NULL )
        {
          tokarg = 0;
          if( ig + 2 > isize )
            {
              isize += 16;
              if( (Ignore = (const char **)realloc( Ignore,
                                                    sizeof(char *) * isize ) )
                  == NULL )
                {
                  log_err(errno,0,1,"realloc failed.");
                  exit( 1 );
                }
            }

          Ignore[ ig ] = strdup( i );
          ++ ig;
          Ignore[ ig ] = 0;
        }
    }

  {
    const char ** i;

    for( i = Ignore; *i; ++ i )
      {
        log_err( 0, 0, DEBUG_MSG, "will ignore '%s'", *i );
      }
  }

  if( optind >= argc )
    {
      dir_tree( ".", 0 );
    }
  else
    {
      for( ; optind < argc; ++ optind )
        dir_tree( argv[ optind ] ,0 );
    }

  return(0);
}

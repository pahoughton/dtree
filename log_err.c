/*********************************************************************
 *
 * File:        log_err.c
 * Project:	dtree
 * Desc:
 *
 *  Write messages to error log file.
 *
 *  Example:
 *
 *	log_err(errno,dberr,DB_BIND_ERROR,
 *		"db_bind failed executing command: %s",db_cmd_buf)
 *
 * Input Agrs:
 *
 *	os_err		operating system error number 
 *	db_err		database error number
 *	my_err		program  error number (see log_err.h)
 *	msg_fmt		error message format string (like printf)
 *	...			 
 *
 * Return Values:
 *		
 *	NONE
 *
 * Notes:
 *
 * Author:	Paul A. Houghton - (paul.houghton@wcom.com)
 * Created:	05/12/99 14:07
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 *********************************************************************/

const char * dtree_log_err_RcsId = 
{"$Id$"};

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <ctype.h>
#include <syslog.h>

#include "log_err.h"

#define	BUF_SZ	2000

char	log_file_name[256] = {"error.log"};
int	debug_msg = FALSE;		/* TRUE/FALSE log debug messages */
int	disp_msg = TRUE;
int	file_msg = TRUE;


void log_err(
  const int	os_err,
  const int	db_err,
  const int	my_err,
  const char	*msg_fmt,
  ...
  )
{

  FILE		*log_file;	/* file to write log file messages */

  va_list 	arglist;	/* for variable args */

  struct tm 	*cur_tm;	/* current date/time structure */
  time_t	cur_timeval;	/* current time (# of sec 1/1/70 */

  char		err_tm_str[20];	/* buffer for date/time string */

  char		in_msg[BUF_SZ];		

  char		err_msg_buf[BUF_SZ];	/* buffer for part of err message */

  char		err_msg[BUF_SZ];	/* buffer for error msgs */
	
  int		log_fp_err = 0;		/* log fputs error indicator */


  /* we'll be grabbing things from the stack... */
  va_start(arglist, msg_fmt);
	
  cur_timeval = time(0);
  cur_tm = localtime(&cur_timeval);		/* get current time */

  sprintf(err_tm_str,"%02d%02d%02d %02d:%02d:%02d ",
	  cur_tm->tm_year % 100,
	  cur_tm->tm_mon + 1,
	  cur_tm->tm_mday,		/* store time in string like: */
	  cur_tm->tm_hour,		/* 910829 14:15:59 */
	  cur_tm->tm_min,
	  cur_tm->tm_sec);

  /* clear that buffer */
  err_msg[0] = 0;

  strcat(err_msg, err_tm_str);

  /* first arg is os error number */

  if(os_err) 
    {
      sprintf(err_msg_buf,"OS ERR: %d - %s ",os_err,strerror(os_err));

      strncat(err_msg,err_msg_buf,sizeof(err_msg) - (strlen(err_msg) + 2));

      err_msg[sizeof(err_msg) - 1] = 0;
    }

  if(db_err) 
    {
      sprintf(err_msg_buf,"DB ERR: %d ",db_err);

      strncat(err_msg,err_msg_buf,sizeof(err_msg) - (strlen(err_msg) + 2));
	
      err_msg[sizeof(err_msg) - 1] = 0;
    }

  if(my_err) 
    {
	
      err_msg_buf[0] = 0;
	
      switch(my_err) 
	{

	  /* this message is for debugging only and should not  */
	  /* be logged unless the debug_msg is TRUE */


	case DEBUG_MSG:
	
	  if(debug_msg == FALSE) 
	    {
	      return;
	    } 
	  else 
	    {
	      strcpy(err_msg_buf,"DEBUG: <");
	    }
	  break;
			

	default: 
			
	  sprintf(err_msg_buf,"PROGRAM ERR: %d ",my_err);
	  break;
			
	} /* end switch */
		
      strncat(err_msg,err_msg_buf,sizeof(err_msg) - (strlen(err_msg) + 2));
      err_msg[sizeof(err_msg) - 2] = 0;
    }		


  /* format input message string */
  vsprintf(in_msg,msg_fmt,arglist);

  strncat(err_msg,in_msg,sizeof(err_msg) - (strlen(err_msg) + 2));

  err_msg[sizeof(err_msg) - 2] = 0;

  if(my_err == DEBUG_MSG)
    {
      strncat(err_msg,">",sizeof(err_msg) - (strlen(err_msg) + 2));
    }
	
  strncat(err_msg,"\n",sizeof(err_msg) - (strlen(err_msg) + 1));
  err_msg[sizeof(err_msg) - 1] = 0;

  /* write message to stderr */

  if(disp_msg)
    {
      fputs(err_msg,stderr);
    }

  /* write message to file -- if error write to syslog */

  if(file_msg)
    {
      log_file = fopen(log_file_name,"a");
	
      if(log_file && (log_fp_err != EOF)) 
	{
	  if( (log_fp_err = fputs(err_msg, log_file)) == EOF ) 
	    {
	      syslog(LOG_ERR,"error writing log file: %s",strerror(errno));
	      syslog(LOG_ERR,"%s",err_msg);
	    }		
	  fclose(log_file);
	}
      else
	{
	  syslog(LOG_ERR,"%s",err_msg);
	}
    }
}
/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 1.2  1999/05/12 20:14:05  houghton
 * Cleanup.
 *
 *
 * Revision 1.1  1999/05/12 18:59:23  houghton
 * Initial Version.
 *	
 */

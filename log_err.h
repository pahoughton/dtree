/*****************************************************************
*
* $Id$
*
* $Log$
* Revision 1.1  1999/05/12 18:59:26  houghton
* Initial Version.
*
 * Revision 1.1  1992/01/01  20:49:59  paulh
 * Initial revision
 *
*
*****************************************************************/
#ifndef _log_err_h_
#define _log_err_h_

#ifdef	__STDC__

#ifdef __cplusplus
extern "C" {
#endif
void	log_err(const int os, 
			const int db, 
			const int my, 
			const char *fmt, ...);
#ifdef __cplusplus
}
#endif

#endif

#define DEBUG_MSG	-20000

#define	SIG_RECEIVED	-10000

#ifndef TRUE
#define TRUE	(1==1)
#define FALSE	(!TRUE)
#endif

extern int	debug_msg;
extern int	disp_msg;
extern int	file_msg;

extern char	log_file_name[];


#ifndef ON
	#define	ON	TRUE
#elif	ON < 1
	#define ON	TRUE
#endif

#ifndef OFF
	#define OFF	FALSE
#elif	OFF != 0
	#define OFF FALSE
#endif

#define	log_debug(a)	(debug_msg = a)
#define	log_screen(a)	(disp_msg = a)
#define	log_filename(a)	(strcpy(log_file_name,a))
#define log_file(a)		(file_msg = a)

#endif

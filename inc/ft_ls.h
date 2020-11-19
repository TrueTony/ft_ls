#ifndef _FT_LS_H_
#define _FT_LS_H_

#include "../libft/libft/libft.h"
#include "../libft/inc/printf.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <attr/xattr.h>


typedef struct s_flags
{
	int		l;
	int 	r;
	int 	R;
	int 	a;
	int 	t;
}				t_flags;


#endif

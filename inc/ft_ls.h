#ifndef _FT_LS_H_
#define _FT_LS_H_

#include "../printf/src/libft/libft.h"
#include "../printf/includes/printf.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>

typedef struct	s_sizes
{
	size_t		link_size;
	size_t		owner_size;
	size_t 		group_size;
	size_t 		size_size;
	size_t 		total;
}				t_sizes;

typedef struct	s_flags
{
	int			l;
	int			r;
	int			R;
	int			a;
	int			t;
	int			elems;
	t_sizes		*sizes;
}				t_flags;

void	lexical_sort(char **names, t_flags *flags, struct stat **stat_s);
void	read_dir(t_flags *flags, char *path);
void	time_sort(t_flags *flags, struct stat **stat_s, char **names);
void 	str_toupper(char *str);
int		parse(int ac, char **av, t_flags *flags);
void	check_type(struct stat *stat);
void	check_access(struct stat *stat);
void 	get_sizes(t_flags *flags, struct stat *stat);
void	lexical_sort_av(t_flags *flags, char **av, int ac);
void	time_sort_av(t_flags *flags, char **av, int ac);
void	check_args(t_flags *fla, int ac, char **av);
void	print_lugs(t_flags *fla, struct stat *stat_s);
void 	print_simple(t_flags *flags, char **names);
void	length_of_stat(char *path, t_flags *flags);
void 	usage(t_flags *flags);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:17:29 by hlikely           #+#    #+#             */
/*   Updated: 2020/11/24 18:43:18 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../printf/src/libft/libft.h"
# include "../printf/includes/printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# define HALF_YEAR 1590397920

typedef struct	s_sizes
{
	size_t		link_size;
	size_t		owner_size;
	size_t		group_size;
	size_t		size_size;
	size_t		total;
	size_t		minors;
	size_t		majours;
	int			elems;
	int			h_elems;
}				t_sizes;

typedef struct	s_flags
{
	int			l;
	int			r;
	int			br;
	int			a;
	int			t;
	t_sizes		*sizes;
}				t_flags;

void			lexical_sort(char **names, t_flags *fla, struct stat **stat_s);
void			read_dir(t_flags *flags, char *path);
void			time_sort(t_flags *flags, struct stat **stat_s, char **names);
int				parse(int ac, char **av, t_flags *flags);
void			check_type(struct stat *stat);
void			check_access(struct stat *stat);
void			get_sizes(t_flags *flags, struct stat *stat);
void			lexical_sort_av(t_flags *flags, char **av, int ac);
void			time_sort_av(t_flags *flags, char **av, int ac);
void			check_args(t_flags *fla, int ac, char **av);
void			print_lugs(t_flags *fla, struct stat *stat_s);
void			print_simple(t_flags *flags, char **names);
int				length_of_stat(char *path, t_flags *flags);
void			usage(t_flags *flags);
int				check_dir(char *path);
void			print_time(struct stat *st, time_t time_now);
void			print_l(t_flags *fla, struct stat **stat_s, char **names);
void			ft_free_all(t_flags *flags, char **names, struct stat **stat_s);
char			*names_plus_paths(char *dirent_name, char *path);

#endif

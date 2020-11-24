/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:14:29 by hlikely           #+#    #+#             */
/*   Updated: 2020/11/24 18:37:57 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_ls.h"

void	print_major_min(struct stat *stat_s, t_flags *fla, size_t j)
{
	if (S_ISCHR(stat_s->st_mode) || S_ISBLK(stat_s->st_mode))
	{
		j = (fla->sizes->majours > 0) ? fla->sizes->majours -
				ft_numstr(major(stat_s->st_rdev)) : 0;
		while (j--)
			ft_putchar(' ');
		ft_printf(" %d,", major(stat_s->st_rdev));
		j = (fla->sizes->minors > 0) ? fla->sizes->minors -
				ft_numstr(minor(stat_s->st_rdev)) : 0;
		while (j--)
			ft_putchar(' ');
		ft_printf(" %d", minor(stat_s->st_rdev));
	}
	else
	{
		j = (fla->sizes->size_size > 0) ? fla->sizes->size_size -
				ft_numstr(stat_s->st_size) : 0;
		while (j--)
			ft_putchar(' ');
		ft_printf(" %d", stat_s->st_size);
	}
}

void	print_lugs(t_flags *fla, struct stat *stat_s)
{
	size_t j;

	j = (fla->sizes->link_size > 0) ? fla->sizes->link_size -
			ft_numstr(stat_s->st_nlink) : 0;
	while (j--)
		ft_putchar(' ');
	ft_printf("  %d ", stat_s->st_nlink);
	ft_printf("%s ", getpwuid(stat_s->st_uid)->pw_name);
	j = (fla->sizes->owner_size > 0) ? fla->sizes->owner_size -
			ft_strlen(getpwuid(stat_s->st_uid)->pw_name) : 0;
	while (j--)
		ft_putchar(' ');
	ft_printf(" %s ", getgrgid(stat_s->st_gid)->gr_name);
	j = (fla->sizes->group_size > 0) ? fla->sizes->group_size -
			ft_strlen(getgrgid(stat_s->st_gid)->gr_name) : 0;
	while (j--)
		ft_putchar(' ');
	print_major_min(stat_s, fla, j);
}

void	print_simple(t_flags *flags, char **names)
{
	int i;

	i = -1;
	while (++i < flags->sizes->elems)
	{
		if (flags->a != 1)
		{
			if (names[i][0] == '.')
			{
				continue;
			}
		}
		ft_printf("%s\n", names[i]);
	}
}

void	print_time(struct stat *st, time_t time_now)
{
	char	*tmp;
	char	*year;
	char	*month_date;

	tmp = ctime(&st->st_mtimespec.tv_sec);
	if ((st->st_mtimespec.tv_sec <= HALF_YEAR) ||
		(st->st_mtimespec.tv_sec > time_now))
	{
		month_date = ft_strndup(tmp + 4, 6);
		year = ft_strndup(tmp + 19, 5);
		ft_printf(" %s %s ", month_date, year);
		free(month_date);
		free(year);
	}
	else
	{
		tmp = ft_strndup(tmp + 4, 12);
		ft_printf(" %s ", tmp);
		free(tmp);
	}
}

void	print_l(t_flags *fla, struct stat **stat_s, char **names)
{
	int				i;
	char			buf[1024];
	time_t			tmp_time;

	i = -1;
	if ((fla->a) || (!fla->a && ((fla->sizes->elems -
							fla->sizes->h_elems) > 0)))
		ft_printf("total: %d\n", fla->sizes->total);
	time(&tmp_time);
	while (++i < fla->sizes->elems)
	{
		if (fla->a != 1 && names[i][0] == '.')
			continue;
		check_type(stat_s[i]);
		check_access(stat_s[i]);
		print_lugs(fla, stat_s[i]);
		print_time(stat_s[i], tmp_time);
		ft_printf("%s", names[i]);
		(readlink(names[i], buf, 1024) != -1) ? ft_printf(" -> %s", buf) : 0;
		ft_bzero(buf, 1024);
		ft_printf("\n");
	}
}

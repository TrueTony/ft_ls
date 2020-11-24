/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:14:52 by hlikely           #+#    #+#             */
/*   Updated: 2020/11/24 18:20:50 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_ls.h"

void	get_sizes(t_flags *flags, struct stat *stat)
{
	if (ft_numstr(stat->st_nlink) > flags->sizes->link_size)
		flags->sizes->link_size = ft_numstr(stat->st_nlink);
	if (ft_strlen(getpwuid(stat->st_uid)->pw_name) > flags->sizes->owner_size)
		flags->sizes->owner_size = ft_strlen(getpwuid(stat->st_uid)->pw_name);
	if (ft_strlen(getgrgid(stat->st_gid)->gr_name) > flags->sizes->group_size)
		flags->sizes->group_size = ft_strlen(getgrgid(stat->st_gid)->gr_name);
	if (ft_numstr(stat->st_size) > flags->sizes->size_size)
		flags->sizes->size_size = ft_numstr(stat->st_size);
	if ((S_ISCHR(stat->st_mode) || S_ISBLK(stat->st_mode)))
	{
		if (ft_numstr(minor(stat->st_rdev)) > flags->sizes->minors)
			flags->sizes->minors = ft_numstr(minor(stat->st_rdev));
		if (ft_numstr(major(stat->st_rdev)) > flags->sizes->majours)
			flags->sizes->majours = ft_numstr(major(stat->st_rdev));
	}
	flags->sizes->total += stat->st_blocks;
}

void	check_type(struct stat *stat)
{
	S_ISDIR(stat->st_mode) ? ft_putchar('d') : ft_putchar('\0');
	S_ISREG(stat->st_mode) ? ft_putchar('-') : ft_putchar('\0');
	S_ISCHR(stat->st_mode) ? ft_putchar('c') : ft_putchar('\0');
	S_ISBLK(stat->st_mode) ? ft_putchar('b') : ft_putchar('\0');
	S_ISFIFO(stat->st_mode) ? ft_putchar('p') : ft_putchar('\0');
	S_ISLNK(stat->st_mode) ? ft_putchar('l') : ft_putchar('\0');
	S_ISSOCK(stat->st_mode) ? ft_putchar('s') : ft_putchar('\0');
}

void	check_access(struct stat *stat)
{
	(stat->st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(stat->st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	if (stat->st_mode & S_ISUID)
		(S_IXUSR) ? ft_putchar('S') : ft_putchar('s');
	else
		(stat->st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(stat->st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(stat->st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if (stat->st_mode & S_ISGID)
		(S_IXGRP) ? ft_putchar('S') : ft_putchar('s');
	else
		(stat->st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(stat->st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(stat->st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	if (stat->st_mode & S_ISVTX)
		(S_ISDIR(stat->st_mode)) ? ft_putchar('t') : ft_putchar('T');
	else
		(stat->st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
}

void	check_args(t_flags *fla, int ac, char **av)
{
	int			i;
	struct stat	buf;

	i = 0;
	lexical_sort_av(fla, av, ac);
	fla->t ? time_sort_av(fla, av, ac) : 0;
	while (i < ac)
	{
		if (lstat(av[i], &buf) != 0)
		{
			perror(av[i]);
			av[i] = NULL;
		}
		else
		{
			if (!S_ISDIR(buf.st_mode))
			{
				read_dir(fla, av[i]);
				av[i] = NULL;
			}
		}
		i++;
	}
	i = -1;
	while (++i < ac)
	{
		if (av[i] != NULL)
			stat(av[i], &buf);
		if (av[i] != NULL && S_ISDIR(buf.st_mode))
		{
			if (!check_dir(av[i]))
				continue ;
			ft_printf("%s:\n", av[i]);
			read_dir(fla, av[i]);
		}
	}
}

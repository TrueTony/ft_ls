/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:14:15 by hlikely           #+#    #+#             */
/*   Updated: 2020/11/24 18:37:05 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_ls.h"

void	recurs(t_flags *flags, struct stat **stat_s, char **names, char *path)
{
	int		i;
	char	*p;
	int		ss;

	i = -1;
	ss = flags->sizes->elems;
	free(flags->sizes);
	while (++i < ss)
	{
		if ((ft_strcmp(names[i], ".") != 0) && (ft_strcmp(names[i], "..") != 0)
			&& S_ISDIR(stat_s[i]->st_mode))
		{
			if (flags->a != 1 && names[i][0] == '.')
				continue ;
			p = names_plus_paths(names[i], path);
			ft_printf("\n%s:\n", p);
			read_dir(flags, p);
			ft_strdel(&p);
		}
		free(stat_s[i]);
		free(names[i]);
	}
	free(stat_s);
	free(names);
}

int		is_file(t_flags *flags, char *path)
{
	struct stat *tmp;
	int			link;
	char		buf[1024];
	char		*time;

	if (!(tmp = (struct stat*)ft_memalloc(sizeof(struct stat))))
		return (0);
	lstat(path, tmp);
	if (((link = readlink(path, buf, 1024)) < 0) &&
	!S_ISREG(tmp->st_mode) && !S_ISFIFO(tmp->st_mode))
	{
		free(tmp);
		return (0);
	}
	if (S_ISDIR(tmp->st_mode) && !link)
	{
		free(tmp);
		return (0);
	}
	ft_bzero(buf, 1024);
	if (flags->l)
	{
		check_type(tmp);
		check_access(tmp);
		print_lugs(flags, tmp);
		time = ctime(&tmp->st_mtime);
		time = ft_strndup(time + 4, 12);
		ft_printf(" %s %s", time, path);
		if (readlink(path, buf, 1024) != -1)
			ft_printf(" -> %s", buf);
		ft_bzero(buf, 1024);
		free(time);
	}
	else
		ft_printf("% s", path);
	ft_printf("\n");
	free(tmp);
	free(flags->sizes);
	return (1);
}

void	make_stats(t_flags *flags, struct stat **st, char *path, char **names)
{
	DIR				*d;
	char			*p;
	struct dirent	*dir;
	int				i;

	i = 0;
	d = opendir(path);
	if (d == NULL)
		return ;
	while ((dir = readdir(d)))
	{
		p = names_plus_paths(dir->d_name, path);
		if (!(st[i] = (struct stat*)ft_memalloc(sizeof(struct stat))))
			return ;
		flags->l ? lstat(p, st[i]) : stat(p, st[i]);
		names[i] = ft_strdup(dir->d_name);
		names[i][0] == '.' ? flags->sizes->h_elems++ : 0;
		flags->a != 1 && names[i][0] == '.' ? 0 : get_sizes(flags, st[i]);
		ft_strdel(&p);
		i++;
	}
	closedir(d);
}

void	read_dir(t_flags *flags, char *path)
{
	char			**names;
	struct stat		**stat_s;

	if (!(flags->sizes = (t_sizes*)ft_memalloc(sizeof(t_sizes))))
		return ;
	if (is_file(flags, path))
		return ;
	if (!(length_of_stat(path, flags)))
		return ;
	if (!(names = (char**)ft_memalloc(sizeof(char*) * (flags->sizes->elems))))
		return ;
	if (!(stat_s = (struct stat**)ft_memalloc(sizeof(struct stat*) *
			(flags->sizes->elems))))
		return ;
	make_stats(flags, stat_s, path, names);
	lexical_sort(names, flags, stat_s);
	flags->t ? time_sort(flags, stat_s, names) : 0;
	flags->l ? print_l(flags, stat_s, names) : print_simple(flags, names);
	flags->br ? recurs(flags, stat_s, names, path) : 0;
	flags->br ? 0 : ft_free_all(flags, names, stat_s);
}

int		main(int ac, char **av)
{
	t_flags *flags;
	int		index;

	if (!(flags = (t_flags*)ft_memalloc(sizeof(t_flags))))
		return (0);
	flags->r = 1;
	if (ac > 1)
	{
		if ((index = parse(ac, av, flags)) == 0)
			read_dir(flags, "./");
		else
			check_args(flags, ac - index, &av[index]);
	}
	else
		read_dir(flags, "./");
	free(flags);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:14:42 by hlikely           #+#    #+#             */
/*   Updated: 2020/11/24 18:38:48 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_ls.h"

void	usage(t_flags *flags)
{
	ft_printf("--usage: ./ft_ls [Options: -alrRt] [Filename]\n");
	free(flags);
	exit(1);
}

int		length_of_stat(char *path, t_flags *flags)
{
	int	i;
	DIR	*dir;

	i = 0;
	dir = opendir(path);
	if (dir == NULL)
	{
		perror(path);
		ft_printf("\n");
		return (0);
	}
	while (readdir(dir))
		i++;
	flags->sizes->elems = i;
	closedir(dir);
	return (1);
}

int		check_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		perror(path);
		ft_printf("\n");
		return (0);
	}
	closedir(dir);
	return (1);
}

void	ft_free_all(t_flags *flags, char **names, struct stat **stat_s)
{
	int i;

	i = -1;
	ft_free_two_demention(names, flags->sizes->elems - 1);
	while (++i < flags->sizes->elems)
		free(stat_s[i]);
	free(stat_s);
	free(flags->sizes);
}

char	*names_plus_paths(char *dirent_name, char *path)
{
	char	*p;
	char	*tmp;

	if (ft_strcmp(path, "./") == 0)
		p = ft_strjoin(path, dirent_name);
	else
	{
		tmp = ft_strjoin(path, "/");
		p = ft_strjoin(tmp, dirent_name);
		free(tmp);
	}
	return (p);
}

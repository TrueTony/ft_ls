#include "inc/ft_ls.h"

void	lexical_sort(char **names, t_flags *flags, struct stat **stat_s)
{
	char		*tmp;
	struct stat	*tmp_stat;
	int			i;

	i = -1;
	if (flags->sizes->elems > 1)
	{
		while (++i < flags->sizes->elems)
		{
			if (names[i] != NULL && names[i + 1] != NULL &&
				(flags->r * ft_strcmp(names[i], names[i + 1]) > 0))
			{
				tmp_stat = stat_s[i];
				stat_s[i] = stat_s[i + 1];
				stat_s[i + 1] = tmp_stat;
				tmp = names[i];
				names[i] = names[i + 1];
				names[i + 1] = tmp;
				i = -1;
			}
		}
	}
}

void	time_sort(t_flags *flags, struct stat **stat_s, char **names)
{
	int			i;
	char		*tmp;
	struct stat	*tmp_stat;

	i = -1;
	if (flags->sizes->elems == 1)
		return ;
	while (++i < flags->sizes->elems)
	{
		if (stat_s[i] != NULL && stat_s[i + 1] != NULL &&
		(flags->r * stat_s[i]->st_mtime < flags->r * stat_s[i + 1]->st_mtime))
		{
			tmp_stat = stat_s[i];
			stat_s[i] = stat_s[i + 1];
			stat_s[i + 1] = tmp_stat;
			tmp = names[i];
			names[i] = names[i + 1];
			names[i + 1] = tmp;
			i = -1;
		}
	}
}

void	lexical_sort_av(t_flags *flags, char **av, int ac)
{
	char	*tmp;
	int		i;

	i = -1;
	if (ac > 1)
	{
		while (++i < ac)
		{
			if ((av[i] != NULL && av[i + 1] != NULL) &&
				(flags->r * ft_strcmp(av[i], av[i + 1]) > 0))
			{
				tmp = av[i];
				av[i] = av[i + 1];
				av[i + 1] = tmp;
				i = -1;
			}
		}
	}
}

void	time_sort_av(t_flags *flags, char **av, int ac)
{
	int			i;
	char		*tmp;
	struct stat	first;
	struct stat	second;

	i = -1;
	if (ac == 1)
		return ;
	while (++i < ac)
	{
		lstat(av[i], &first);
		lstat(av[i + 1], &second);
		if (flags->r * first.st_mtime < flags->r * second.st_mtime)
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = -1;
		}
	}
}

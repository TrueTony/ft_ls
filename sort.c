#include "inc/ft_ls.h"

void	lexical_sort(char **names, t_flags *flags, struct stat **stat_s)
{
	char *tmp;
	struct stat *tmp_stat;
	int i;

	i = -1;
	if (flags->elems > 1)
	{
		while (++i < flags->elems)
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
	int i;
	char *tmp;
	struct stat *tmp_stat;

	i = -1;
	if (flags->elems == 1)
		return ;
	while (++i < flags->elems)
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


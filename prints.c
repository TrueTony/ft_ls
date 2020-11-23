#include "inc/ft_ls.h"

void	print_lugs(t_flags *fla, struct stat *stat_s)
{
	size_t j;

	j = (fla->sizes->link_size > 0) ? fla->sizes->link_size - ft_numstr(stat_s->st_nlink) : 0;
	while (j--)
		ft_putchar(' ');
	ft_printf("  %d ", stat_s->st_nlink);
	j = (fla->sizes->owner_size > 0) ? fla->sizes->owner_size - ft_strlen(getpwuid(stat_s->st_uid)->pw_name) : 0;
	while (j--)
		ft_putchar(' ');
	ft_printf("%s ", getpwuid(stat_s->st_uid)->pw_name);
	j = (fla->sizes->group_size > 0) ? fla->sizes->group_size - ft_strlen(getgrgid(stat_s->st_gid)->gr_name) : 0;
	while (j--)
		ft_putchar(' ');
	ft_printf(" %s ", getgrgid(stat_s->st_gid)->gr_name);
	j = (fla->sizes->size_size > 0) ? fla->sizes->size_size - ft_numstr(stat_s->st_size) : 0;
	while (j--)
		ft_putchar(' ');
	ft_printf(" %d", stat_s->st_size);
}

void 	print_simple(t_flags *flags, char **names)
{
	int i;

	i = -1;
	while(++i < flags->sizes->elems)
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

#include "inc/ft_ls.h"

void 	usage(t_flags *flags)
{
	ft_printf("--usage: ./ft_ls [Options: -alrRt] [Filename]\n");
	free(flags);
	exit(1);
}

void 	str_toupper(char *str)
{
	int i;

	i = ft_strlen(str);
	while (i--)
		str[i] = (char)ft_toupper(str[i]);
}

void	length_of_stat(char *path, t_flags *flags)
{
	int	i;
	DIR	*dir;

	i = 0;
	dir = opendir(path);
	while (readdir(dir))
		i++;
	flags->sizes->elems = i;
	closedir(dir);
}
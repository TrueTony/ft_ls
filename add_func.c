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

int	length_of_stat(char *path, t_flags *flags)
{
	int	i;
	DIR	*dir;

	i = 0;
	dir = opendir(path);
	if (dir == NULL)
	{
		// ft_putstr_fd(path, 2);
		// ft_putstr_fd(": ", 2);
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

int	check_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		// ft_putstr_fd(path, 2);
		// ft_putstr_fd(": ", 2);
		perror(path);
		ft_printf("\n");
		return (0);
	}
	closedir(dir);
	return (1);
}
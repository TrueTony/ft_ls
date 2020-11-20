#include "inc/ft_ls.h"

void 	usage(t_fla *flags)
{
	ft_printf("This program can work only with this flags: a, l, r, R, a\n");
	free(flags);
	exit(1);
}

void	catch_flags(char *str, t_fla *flags)
{
	int	i;

	i = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == 'a')
			flags->a = 1;
		else if (str[i] == 'r')
			flags->r = 1;
		else if (str[i] == 'R')
			flags->R = 1;
		else if (str[i] == 't')
			flags->t = 1;
		else if (str[i] == 'l')
			flags->l = 1;
		else
			usage(flags) ;
	}
}

void	parse(int ac, char **av, t_fla *flags)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-' && ft_isalpha(av[i][1]))
			catch_flags(av[i], flags);
		else
			ft_error();
	}
}

int		length_of_stat(char *path)
{
	int	i;
	DIR	*dir;

	i = 0;
	dir = opendir(path);
	while (readdir(dir))
        i++;
	closedir(dir);
	return (i);
}

void	read_dir(t_fla *flags, char *path)
{
	DIR				*dir;
	struct stat		**stat_s;
	char			**names;
	int				i;
    struct dirent	*space_around;
	char			*p;


    i = length_of_stat(path) + 1;
    flags->elems = i - 1;
    dir = opendir(path);
	stat_s = (struct stat**)malloc(sizeof(struct stat*) * i);
	names = (char**)ft_memalloc(sizeof(char*) * i);
	i = 0;
    while ((space_around = readdir(dir)))
    {
//		ft_printf("%s\n", space_around->d_name);
		p = ft_strjoin("./", space_around->d_name);
        stat_s[i] = (struct stat*)malloc(sizeof(struct stat));
        stat(space_around->d_name, stat_s[i]);
		names[i] = ft_strdup(space_around->d_name);
		ft_strdel(&p);
		i++;
    }
	lexical_sort(names, flags, stat_s);
    time_sort(flags, stat_s, names);
    for (int k = 0; k < i; k++)
    	if (names[k][0] != '.')
    		ft_printf("%s\n", names[k]);
	closedir(dir);
}

int		main(int ac, char **av)
{
	t_fla *fla;

	if(!(fla = (t_fla*)ft_memalloc(sizeof(t_fla))))
		return (0);
	if (ac > 1)
	{
		parse(ac, av, fla);
		read_dir(fla, "./");
	}
	else
		read_dir(fla, "./");
	free(fla);
	return (0);
}

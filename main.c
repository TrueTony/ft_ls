#include "inc/ft_ls.h"

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

void	parse_l(t_flags *fla, struct stat	**stat_s, char **names)
{
	int	i;

	i = -1;
	ft_printf("total: %d\n", fla->sizes->total);
	while (++i < fla->elems)
	{
		check_type(stat_s[i]);
		check_access(stat_s[i]);

		ft_printf(" %d %s %s %d", stat_s[i]->st_nlink, getpwuid(stat_s[i]->st_uid)->pw_name,
			getgrgid(stat_s[i]->st_gid)->gr_name, stat_s[i]->st_size);

		char *tmp =  ctime(&stat_s[i]->st_atimespec.tv_sec);


		tmp = ft_strndup(tmp+4, 12);
		ft_printf(" %s %s", tmp, names[i]);

    		ft_printf("\n");
		// exit(1);
	}
}

void	read_dir(t_flags *flags, char *path)
{
	DIR				*dir;
	struct stat		**stat_s;
	char			**names;
	int				i;
    struct dirent	*dirent;
	char			*p;
	int				width;


    i = length_of_stat(path) + 1;
    flags->elems = i - 1;
    dir = opendir(path);
	stat_s = (struct stat**)malloc(sizeof(struct stat*) * i);
	names = (char**)ft_memalloc(sizeof(char*) * i);
	i = 0;
    while ((dirent = readdir(dir)))
    {
//		ft_printf("%s\n", dirent->d_name);
		p = ft_strjoin("./", dirent->d_name);
        stat_s[i] = (struct stat*)malloc(sizeof(struct stat));
		if (flags->l)
	        lstat(dirent->d_name, stat_s[i]);
		else
        	stat(dirent->d_name, stat_s[i]);
		get_sizes(flags, stat_s[i]);
		names[i] = ft_strdup(dirent->d_name);
		ft_printf("%s %d\n", names[i], stat_s[i]->st_blocks);
		ft_strdel(&p);
		i++;
    }
	lexical_sort(names, flags, stat_s);

    if (flags->t)
    	time_sort(flags, stat_s, names);
	if (flags->l)
        parse_l(flags, stat_s, names);
//    for (int k = 0; k < i; k++)
//    	if (names[k][0] != '.')
//    		ft_printf("%s\n", names[k]);
	closedir(dir);
}

int		main(int ac, char **av)
{
	t_flags *fla;

	if(!(fla = (t_flags*)ft_memalloc(sizeof(t_flags))))
		return (0);
	if(!(fla->sizes = (t_sizes*)ft_memalloc(sizeof(t_sizes))))
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

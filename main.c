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

void	print_lugs(t_flags *fla, struct stat *stat_s)
{
	size_t j;

	j = fla->sizes->link_size - ft_numstr(stat_s->st_nlink);
	while (j--)
		ft_putchar(' ');
	ft_printf("  %d ", stat_s->st_nlink);
	j = fla->sizes->owner_size - ft_strlen(getpwuid(stat_s->st_uid)->pw_name);
	while (j--)
		ft_putchar(' ');
	ft_printf("%s ", getpwuid(stat_s->st_uid)->pw_name);
	j = fla->sizes->group_size - ft_strlen(getgrgid(stat_s->st_gid)->gr_name);
	while (j--)
		ft_putchar(' ');
	ft_printf(" %s ", getgrgid(stat_s->st_gid)->gr_name);
	j = fla->sizes->size_size - ft_numstr(stat_s->st_size);
	while (j--)
		ft_putchar(' ');
	ft_printf(" %d", stat_s->st_size);
}

void	parse_l(t_flags *fla, struct stat **stat_s, char **names)
{
	int	i;

	i = 0;
	char	buf[1024];

	// buf = NULL;
	ft_printf("total: %d\n", fla->sizes->total);
	while (i < fla->elems)
	{
		if (fla->a != 1)
			if (names[i][0] == '.')
			{
				i++;
				continue;
			}
		check_type(stat_s[i]);
		check_access(stat_s[i]);
		print_lugs(fla, stat_s[i]);
		char *tmp =  ctime(&stat_s[i]->st_mtimespec.tv_sec);
		tmp = ft_strndup(tmp+4, 12);
		ft_printf(" %s %s", tmp, names[i]);
		if (readlink(names[i], buf, 1024) != -1)
		{
			ft_printf(" -> ");
			ft_printf("%s", buf);
		}
		ft_printf("\n");
		i++;
	}
}

void 	print_simple(t_flags *flags, char **names)
{
	int i;

	i = 0;
	while(names[i])
	{
		if (flags->a != 1)
			if (names[i][0] == '.')
			{
				i++;
				continue;
			}
		ft_printf("%s\n", names[i]);
		i++;
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


    i = length_of_stat(path) + 1;
    flags->elems = i - 1;
    dir = opendir(path);
	stat_s = (struct stat**)malloc(sizeof(struct stat*) * i);
	names = (char**)ft_memalloc(sizeof(char*) * i);
	i = 0;
    while ((dirent = readdir(dir)))
    {
		p = ft_strjoin("./", dirent->d_name);
        stat_s[i] = (struct stat*)malloc(sizeof(struct stat));
		if (flags->l)
	        lstat(dirent->d_name, stat_s[i]);
		else
        	stat(dirent->d_name, stat_s[i]);
		names[i] = ft_strdup(dirent->d_name);
		if (flags->a != 1 && names[i][0] == '.')
			;
		else
			get_sizes(flags, stat_s[i]);
		ft_strdel(&p);
		i++;
    }
	lexical_sort(names, flags, stat_s);
    if (flags->t)
    	time_sort(flags, stat_s, names);
	if (flags->l)
        parse_l(flags, stat_s, names);
	else
		print_simple(flags, names);
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
		fla->r = 1;
		parse(ac, av, fla);
		read_dir(fla, "./");
	}
	else
		read_dir(fla, "./");
	free(fla->sizes);
	free(fla);
	return (0);
}

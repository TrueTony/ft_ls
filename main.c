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

void	parse_l(t_flags *fla, struct stat **stat_s, char **names)
{
	int	i;
	char	buf[1024];
	i = 0;

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

int 	is_file(t_flags *flags, char *path)
{
	struct stat *tmp;
	int			link;
	char		buf[1024];
	char 		tp[1024];

	tmp = (struct stat*)ft_memalloc(sizeof(struct stat));
	lstat(path, tmp);
	if (((link = readlink(path, buf, 1024)) < 0) && !S_ISREG(tmp->st_mode) && !S_ISFIFO(tmp->st_mode))
		return 0;
	if (S_ISDIR(tmp->st_mode) && !link)
		return 0;
	if (flags->l)
	{
		check_type(tmp);
		check_access(tmp);
		print_lugs(flags, tmp);
		char *ttt = ctime(&tmp->st_mtimespec.tv_sec);
		ttt = ft_strndup(ttt+4, 12);
		ft_printf(" %s %s", ttt, path);
		if (readlink(path, tp, 1024) != -1)
		{
			ft_printf(" -> ");
			ft_printf("%s", tp);
		}
	}
	else
		ft_printf("% s", path);
	ft_printf("\n");
	return (1);
}

void	read_dir(t_flags *flags, char *path)
{
	DIR				*dir;
	struct stat		**stat_s;
	char			**names;
	int				i;
    struct dirent	*dirent;
	char			*p;


	if (is_file(flags, path))
		return;
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

void	lexical_sort_av(t_flags *flags, char **av, int ac)
{
	char *tmp;
	int i;

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
	int i;
	char *tmp;
	struct stat *first = NULL;
	struct stat *second = NULL;

	i = -1;
	if (ac == 1)
		return ;
	while (++i < ac - 1)
	{
		lstat(av[i], first);
		lstat(av[i + 1], second);
		if ((first != NULL && second != NULL) &&
		(flags->r * first->st_mtime < flags->r * second->st_mtime))
		{
			tmp = av[i];
			av[i] = av[i + 1];
			av[i + 1] = tmp;
			i = -1;
		}
	}
}

void	check_args(t_flags *fla, int ac, char **av)
{
	int i;
	struct stat buf;

	i = 0;
	lexical_sort_av(fla, av, ac);
	if (fla->t)
		time_sort_av(fla, av, ac);
	while (i < ac)
	{
		if (stat(av[i], &buf) != 0)
		{
			perror(av[i]);
			av[i] = NULL;
		}
		else
			get_sizes(fla, &buf);
		i++;
	}
	i = 0;
	while (i < ac)
	{
		if (av[i] != NULL)
			read_dir(fla, av[i]);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_flags *fla;
	int		index;

	if(!(fla = (t_flags*)ft_memalloc(sizeof(t_flags))))
		return (0);
	if(!(fla->sizes = (t_sizes*)ft_memalloc(sizeof(t_sizes))))
		return (0);
	if (ac > 1)
	{
		fla->r = 1;
		if ((index = parse(ac, av, fla)) == 0)
			read_dir(fla, "./");
		else
			check_args(fla, ac - index, &av[index]);
	}
	else
		read_dir(fla, "./");
	free(fla->sizes);
	free(fla);
	return (0);
}

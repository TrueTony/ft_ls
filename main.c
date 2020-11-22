#include "inc/ft_ls.h"

void	if_b(t_flags *flags, struct stat **buf, char **names)
{
	int	i;

	i = -1;
	while (buf[++i])
		if (names[i][0] != '.' && S_ISDIR(buf[i]->st_mode))
			read_dir(flags, names[i]);
}

void	parse_l(t_flags *fla, struct stat **stat_s, char **names)
{
	int		i;
	char	buf[1024];

	i = -1;
	ft_printf("total: %d\n", fla->sizes->total);
	while (++i < fla->elems)
	{
		if (fla->a != 1 && names[i][0] == '.')
			continue;
		check_type(stat_s[i]);
		check_access(stat_s[i]);
		print_lugs(fla, stat_s[i]);
		char *tmp = ctime(&stat_s[i]->st_mtime);
		tmp = ft_strndup(tmp+4, 12);
		ft_printf(" %s %s", tmp, names[i]);
		readlink(names[i], buf, 1024) != -1 ? ft_printf(" -> %s", buf) : 0;
		ft_bzero(buf, 1024);
		ft_printf("\n");
	}
}

int 	is_file(t_flags *flags, char *path)
{
	struct stat *tmp;
	int			link;
	char		buf[1024];
	char 		*time;

	tmp = (struct stat*)ft_memalloc(sizeof(struct stat));
	lstat(path, tmp);
	if (((link = readlink(path, buf, 1024)) < 0) &&
	!S_ISREG(tmp->st_mode) && !S_ISFIFO(tmp->st_mode))
		return 0;
	if (S_ISDIR(tmp->st_mode) && !link)
		return 0;
	ft_bzero(buf, 1024);
	if (flags->l)
	{
		check_type(tmp);
		check_access(tmp);
		print_lugs(flags, tmp);
		time = ctime(&tmp->st_mtime);
		time = ft_strndup(time + 4, 12);
		ft_printf(" %s %s", time, path);
		if (readlink(path, buf, 1024) != -1)
			ft_printf(" -> %s", buf);
		ft_bzero(buf, 1024);
	}
	else
		ft_printf("% s", path);
	ft_printf("\n");
	return (1);
}

void	make_stats(t_flags *flags, struct stat **st, char *path, char **names)
{
	DIR				*d;
	char			*p;
	struct dirent	*dir;
	int i;

	d = opendir(path);
	i = 0;
	while ((dir = readdir(d)))
	{
		p = ft_strjoin("./", dir->d_name);
		st[i] = (struct stat*)malloc(sizeof(struct stat));
		flags->l ? lstat(dir->d_name, st[i]) : stat(dir->d_name, st[i]);
		names[i] = ft_strdup(dir->d_name);
		flags->a != 1 && names[i][0] == '.' ? 0 : get_sizes(flags, st[i]);
		ft_strdel(&p);
		i++;
	}
	closedir(d);
}

void	read_dir(t_flags *flags, char *path)
{
	char			**names;
	struct stat		**stat_s;

	if (is_file(flags, path))
		return;
	length_of_stat(path, flags);
	names = (char**)ft_memalloc(sizeof(char*) * flags->elems + 1);
	stat_s = (struct stat**)malloc(sizeof(struct stat*) * flags->elems + 1);
    make_stats(flags, stat_s, path, names);
	lexical_sort(names, flags, stat_s);
    flags->t ? time_sort(flags, stat_s, names) : 0;
	flags->l ? parse_l(flags, stat_s, names) : print_simple(flags, names);
	flags->R ? if_b(flags, stat_s, names) : 0;
}

int		main(int ac, char **av)
{
	t_flags *flags;
	int		index;

	if(!(flags = (t_flags*)ft_memalloc(sizeof(t_flags))))
		return (0);
	if(!(flags->sizes = (t_sizes*)ft_memalloc(sizeof(t_sizes))))
		return (0);
	flags->r = 1;
	if (ac > 1)
	{
		if ((index = parse(ac, av, flags)) == 0)
			read_dir(flags, "./");
		else
			check_args(flags, ac - index, &av[index]);
	}
	else
		read_dir(flags, "./");
	free(flags->sizes);
	free(flags);
	return (0);
}

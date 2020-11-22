#include "inc/ft_ls.h"

char	*names_plus_paths(char* dirent_name, char *path)
{
	char	*p;
	char	*tmp;


	if (ft_strcmp(path, "./") == 0)
		p = ft_strjoin(path, dirent_name);
	else
	{
		tmp = ft_strjoin(path, "/");
		p = ft_strjoin(tmp, dirent_name);
		free(tmp);
	}
	return (p);
}

void 	sizes_to_zero(t_flags *flags)
{
	flags->sizes->link_size = 0;
	flags->sizes->owner_size = 0;
	flags->sizes->group_size = 0;
	flags->sizes->size_size = 0;
	flags->sizes->total = 0;
}

void	if_R(t_flags *flags, struct stat **stat_s, char **names, char *path)
{
	int		i;
	char	*p;
	int		ss;

	i = -1;
	ss = flags->sizes->elems;
	while (++i < ss)
	{
		if ((ft_strcmp(names[i], ".") != 0) && (ft_strcmp(names[i], "..") != 0)
			&& S_ISDIR(stat_s[i]->st_mode))
		{
			if (flags->a != 1 && names[i][0] == '.')
				continue ;
			p = names_plus_paths(names[i], path);
			ft_printf("\n%s:\n", p);
			read_dir(flags, p);
			ft_printf("");
			ft_strdel(&p);

		}
		 free(stat_s[i]);
		 free(names[i]);
	}
	 free(stat_s);
	 free(names);
}

void	parse_l(t_flags *fla, struct stat **stat_s, char **names)
{
	int		i;
	char	buf[1024];

	i = -1;
	if((fla->a) || (!fla->a && ((fla->sizes->elems - fla->sizes->h_elems) > 0)))
		ft_printf("total: %d\n", fla->sizes->total);
	while (++i < fla->sizes->elems)
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

	i = 0;
	d = opendir(path);
	while ((dir = readdir(d)))
	{
		p = names_plus_paths(dir->d_name, path);
		st[i] = (struct stat*)ft_memalloc(sizeof(struct stat));
		flags->l ? lstat(p, st[i]) : stat(p, st[i]);
		names[i] = ft_strdup(dir->d_name);
		names[i][0] == '.' ? flags->sizes->h_elems++ : 0;
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

	if(!(flags->sizes = (t_sizes*)ft_memalloc(sizeof(t_sizes))))
		return ;
	if (is_file(flags, path))
		return ;
	length_of_stat(path, flags);
	names = (char**)ft_memalloc(sizeof(char*) * flags->sizes->elems + 1);
	names[flags->sizes->elems] = NULL;
	stat_s = (struct stat**)ft_memalloc(sizeof(struct stat*) * flags->sizes->elems + 1);
	stat_s[flags->sizes->elems] = NULL;
	make_stats(flags, stat_s, path, names);
	lexical_sort(names, flags, stat_s);
    flags->t ? time_sort(flags, stat_s, names) : 0;
	flags->l ? parse_l(flags, stat_s, names) : print_simple(flags, names);
	flags->R ? if_R(flags, stat_s, names, path) : 0;
}

int		main(int ac, char **av)
{
	t_flags *flags;
	int		index;

	if(!(flags = (t_flags*)ft_memalloc(sizeof(t_flags))))
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

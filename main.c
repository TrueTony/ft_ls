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

void	parse_l(t_fla *fla, struct stat	**stat_s, char **names)
{
	int	i;

	i = -1;
	ft_printf("total: %d\n", fla->blocks);
	while (++i < fla->elems)
	{
		S_ISDIR(stat_s[i]->st_mode) ? ft_putchar('d') : ft_putchar('\0'); // is papka
		S_ISREG(stat_s[i]->st_mode) ? ft_putchar('-') : ft_putchar('\0'); // is file
		S_ISCHR(stat_s[i]->st_mode) ? ft_putchar('c') : ft_putchar('\0'); //symboly spec file
		S_ISBLK(stat_s[i]->st_mode) ? ft_putchar('b') : ft_putchar('\0'); // block file
		S_ISFIFO(stat_s[i]->st_mode) ? ft_putchar('p') : ft_putchar('\0'); // fifo channel
		S_ISLNK(stat_s[i]->st_mode) ? ft_putchar('l') : ft_putchar('\0'); // sym link
		S_ISSOCK(stat_s[i]->st_mode) ? ft_putchar('s') : ft_putchar('\0'); // socket

		// ft_printf("%d ", stat_s[i]->st_mode);
		(stat_s[i]->st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
		(stat_s[i]->st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
		if (stat_s[i]->st_mode & S_ISUID)
			(S_IXUSR) ? ft_putchar('S') : ft_putchar('s');
		else
			(stat_s[i]->st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');

		(stat_s[i]->st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
		(stat_s[i]->st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
		if (stat_s[i]->st_mode & S_ISGID)
			(S_IXGRP) ? ft_putchar('S') : ft_putchar('s');
		else
			(stat_s[i]->st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');

		(stat_s[i]->st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
		(stat_s[i]->st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
		if (stat_s[i]->st_mode & S_ISVTX)
			(S_ISDIR(stat_s[i]->st_mode)) ? ft_putchar('t') : ft_putchar('T');
		else
			(stat_s[i]->st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');

		ft_printf(" %d %s %s %d", stat_s[i]->st_nlink, getpwuid(stat_s[i]->st_uid)->pw_name,
			getgrgid(stat_s[i]->st_gid)->gr_name, stat_s[i]->st_size);

		char *tmp =  ctime(&stat_s[i]->st_atim);


		tmp = ft_strndup(tmp+4, 12);
		ft_printf(" %s %s", tmp, names[i]);

    		ft_printf("\n");
		// exit(1);
	}
}

void	read_dir(t_fla *flags, char *path)
{
	DIR				*dir;
	struct stat		**stat_s;
	char			**names;
	int				i;
    struct dirent	*space_around;
	char			*p;
	int				width;


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
		if (flags->l)
	        lstat(space_around->d_name, stat_s[i]);
		else
        	stat(space_around->d_name, stat_s[i]);
		if ((width = ft_numstr(stat_s[i]->st_size)) > flags->width)
			flags->width = width;
		flags->blocks += stat_s[i]->st_blocks;
		names[i] = ft_strdup(space_around->d_name);
		ft_printf("%s %d\n", names[i], stat_s[i]->st_blocks);
		ft_strdel(&p);
		i++;
    }
	lexical_sort(names, flags, stat_s);

    if (flags->t)
    	time_sort(flags, stat_s, names);
	if (flags->l)
        parse_l(flags, stat_s, names);
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

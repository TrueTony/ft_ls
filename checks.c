#include "inc/ft_ls.h"


void 	get_sizes(t_flags *flags, struct stat *stat)
{
	if (ft_numstr(stat->st_nlink) > flags->sizes->link_size)
		flags->sizes->link_size = ft_numstr(stat->st_nlink);
	if (ft_strlen(getpwuid(stat->st_uid)->pw_name) > flags->sizes->owner_size)
		flags->sizes->owner_size = ft_strlen(getpwuid(stat->st_uid)->pw_name);
	if (ft_strlen(getgrgid(stat->st_gid)->gr_name) > flags->sizes->group_size)
		flags->sizes->group_size = ft_strlen(getgrgid(stat->st_gid)->gr_name);
	if (ft_numstr(stat->st_size) > flags->sizes->size_size)
		flags->sizes->size_size = ft_numstr(stat->st_size);
	flags->sizes->total += stat->st_blocks;
}

void	check_type(struct stat *stat)
{
	S_ISDIR(stat->st_mode) ? ft_putchar('d') : ft_putchar('\0'); // is papka
	S_ISREG(stat->st_mode) ? ft_putchar('-') : ft_putchar('\0'); // is file
	S_ISCHR(stat->st_mode) ? ft_putchar('c') : ft_putchar('\0'); //symboly spec file
	S_ISBLK(stat->st_mode) ? ft_putchar('b') : ft_putchar('\0'); // block file
	S_ISFIFO(stat->st_mode) ? ft_putchar('p') : ft_putchar('\0'); // fifo channel
	S_ISLNK(stat->st_mode) ? ft_putchar('l') : ft_putchar('\0'); // sym link
	S_ISSOCK(stat->st_mode) ? ft_putchar('s') : ft_putchar('\0'); // socket
}

void	check_access(struct stat *stat)
{
	(stat->st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(stat->st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	if (stat->st_mode & S_ISUID)
		(S_IXUSR) ? ft_putchar('S') : ft_putchar('s');
	else
		(stat->st_mode & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');

	(stat->st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(stat->st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if (stat->st_mode & S_ISGID)
		(S_IXGRP) ? ft_putchar('S') : ft_putchar('s');
	else
		(stat->st_mode & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');

	(stat->st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(stat->st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	if (stat->st_mode & S_ISVTX)
		(S_ISDIR(stat->st_mode)) ? ft_putchar('t') : ft_putchar('T');
	else
		(stat->st_mode & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
}
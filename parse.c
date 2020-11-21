#include "inc/ft_ls.h"

void 	usage(t_flags *flags)
{
	ft_printf("This program can work only with this flags: a, l, r, R, a\n");
	free(flags);
	exit(1);
}

void	catch_flags(char *str, t_flags *flags)
{
	size_t	i;

	i = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == 'a')
			flags->a = 1;
		else if (str[i] == 'r')
			flags->r = -1;
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

void	parse(int ac, char **av, t_flags *flags)
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
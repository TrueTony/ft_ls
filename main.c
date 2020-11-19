#include "inc/ft_ls.h"

void 	usage(t_flags *flags)
{
	ft_printf("This program can work only with this flags: a, l, r, R, a\n");
	free(flags);
	exit(1);
}

void	catch_flags(char *str, t_flags *flags)
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

int		main(int ac, char **av)
{
	t_flags *flags;
	if(!(flags = (t_flags*)ft_memalloc(sizeof(t_flags))))
		return (0);
	if (ac > 1)
	{
		parse(ac, av, flags);
		show_your_boobs(av, flags);
	}
	else
		show_your_boobs(av, flags);
	free(flags);
	return (0);
}

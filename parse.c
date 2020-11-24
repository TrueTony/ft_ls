/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:15:00 by hlikely           #+#    #+#             */
/*   Updated: 2020/11/24 18:21:46 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_ls.h"

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
			flags->br = 1;
		else if (str[i] == 't')
			flags->t = 1;
		else if (str[i] == 'l')
			flags->l = 1;
		else
			usage(flags);
	}
}

int		parse(int ac, char **av, t_flags *flags)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-' && ft_isalpha(av[i][1]))
			catch_flags(av[i], flags);
		else if (av[i][0] != '-')
			return (i);
	}
	return (0);
}

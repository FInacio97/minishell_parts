/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/16 19:02:05 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"


int	is_flag(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 2)
		return (1);
	if (s[i] == '-' && s[i + 1] == 'n')
		i+= 2;
	else
		return (1);
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] == 0)
		return (0);
	return (1);
}

void	echo(char **prompt)
{
	int	nl;
	int	i;
	int	tolk_nbr;

	nl = 0;
	i = -1;
	tolk_nbr = 0;
	while (prompt[tolk_nbr])
		tolk_nbr++;
	while (prompt[++i] && is_flag(prompt[i]) == 0)
		nl = 1;
	if (is_flag(prompt[i]) == 0)
		return ;
	while(i < tolk_nbr - 1)
	{
		ft_printf("%s ", prompt[i]);
		i++;
	}
	if (i == tolk_nbr - 1)
		ft_printf("%s", prompt[i]);
	if (nl == 0)
		printf("\n");
}

int	main()
{
	char	*s;
	char	**mtx;

	while (1)
	{
		s = readline(":---");
		if (ft_strncmp(s, "end", 5) == 0)
		{
			free (s);
			break ;
		}
		mtx = tokenizer(s);
		free (s);
		echo(mtx);
		matrix_deleter(mtx);
	}
}



/*
	echo       -nnnnnnn   "-n " " -n"      skjdcsnc
 
 -nnnnnnn   "-n ""' -n'"      skjdcsnc

 -nnnnnnn

 -n 

' -n'

skjdcsnc
*/
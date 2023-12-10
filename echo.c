/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/09 22:31:08 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	is_flag(char *s)
{
	int	i;

	i = 0;
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

	nl = 0;
	i = -1;
	while (is_flag(prompt[++i]) == 0)
		nl = 1;
	i--;
	while(prompt[++i + 1])
		printf("%s ", prompt[i]);///////////////////////////////////
	printf("%s", prompt[i]);////////////////////////////////////////
	if (nl == 1)
		printf("\n");///////////////////////////////////////////////
}

int	main()
{
	char *s;
	int	i = -1;
	char c;
	
	s = readline(":---");
	tokenizer(s);
	
	free (s);
}



/*
	echo       -nnnnnnn   "-n " " -n"      skjdcsnc
 
 -nnnnnnn   "-n ""' -n'"      skjdcsnc

 -nnnnnnn

 -n 

' -n'

skjdcsnc
*/
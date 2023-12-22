/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:27:31 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/22 11:10:12 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief removes the limmiter opperand from the redirection
* @param (redirection)
* @return a mem alloc string containing the limmiter isolated
*/
char	*get_limiter(char *redirect)
{
	int		i;
	int		j;
	char	*prod;

	i = 0;
	j = 0;
	while (redirect[i] && (redirect[i] == '>' || redirect[i] == ' '))
		i++;
	while (redirect[i + j])
		j++;
	prod = malloc(j + 1);
	if (!prod)
		return (NULL);
	prod[j] = 0;
	j = -1;
	while (redirect[i + ++j])
		prod[j] = redirect[i + j];
	return (prod);	
}

/*
* @brief The name says it all: simulates a here_doc. It does it by reading from
* the standard input, within the command itself and the limiter word.
*/
void	here_doc(t_commands *cmd, int lst_redirect)
{
	int		fd[2];
	char	*s;
	char	*limiter;

	limiter = get_limiter(cmd->redirect_in[lst_redirect]);
	if (pipe(fd) == 1)
		ft_printf("Error\n");//			Error treatment!
	while (1)
	{
		ft_printf(">");
		s = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, s, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == (ft_strlen(s) - 1))
			break ;
		write(fd[1], s, ft_strlen(s));
		free (s);
	}
	free (s);
	free (limiter);
	close(fd[1]);
	cmd->in_fd = fd[0];
}

/*
* @brief It reproduces the visible behavior of the here_doc, without
* reading anything from anywhere
*/
void	fake_here_doc(char *redirect)
{
	char	*s;
	char	*limiter;

	limiter = get_limiter(redirect);
	while (1)
	{
		ft_printf(">");
		s = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, s, ft_strlen(limiter)) == 0
			&& ft_strlen(limiter) == (ft_strlen(s) - 1))
			break ;
		free (s);
	}
	free (s);
	free (limiter);
}

/*
* @brief Checks if theres any here_doc in the redirections of each command
* and executes them, in case of it's existence.
*/
void	here_doc_check(t_commands *cmd)
{
	int	i;
	int	last_redirect;

	last_redirect = 0;
	while (cmd->redirect_in[last_redirect + 1])
		last_redirect++;
	i = -1;
	while (cmd->redirect_in[++i])
	{
		if (ft_strncmp("<<", cmd->redirect_in[i], 2) != 0)
			continue ;
		if (i == last_redirect)
			here_doc(cmd, last_redirect);
		else
			fake_here_doc(cmd->redirect_in[i]);
	}
}

/*
* @brief Manages all here_docs
*/
void	here_doc_manager(t_data *data)
{
	t_commands *current;

	current = data->first_cmd;
	while (current)
	{
		if (current->redirect_in)
			here_doc_check(current);
		current = current->next;
	}
}
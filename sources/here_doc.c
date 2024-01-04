/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:27:31 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/04 12:46:49 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
// * @brief removes the limmiter opperand from the redirection
// * @param (redirection)
// * @return a mem alloc string containing the limmiter isolated
// */
// char	*get_limiter(char *redirect)
// {
// 	int		i;
// 	int		j;
// 	char	*prod;

// 	i = 0;
// 	j = 0;
// 	while (redirect[i] && (redirect[i] == '>' || redirect[i] == ' '))
// 		i++;
// 	while (redirect[i + j])
// 		j++;
// 	prod = malloc(j + 1);
// 	if (!prod)
// 		return (NULL);
// 	prod[j] = 0;
// 	j = -1;
// 	while (redirect[i + ++j])
// 		prod[j] = redirect[i + j];
// 	return (prod);	
// }

/*
* @brief The name says it all: simulates a here_doc. It does it by reading from
* the standard input, within the command itself and the limiter word.
*/
void	here_doc(t_redirection *rdir, int fd[2])
{
	char	*s;
	int		len;

	len = ft_strlen(rdir->key_wrd);
	while (1)
	{
		ft_printf(">");
		s = get_next_line(STDIN_FILENO);
		if (ft_strncmp(rdir->key_wrd, s, len) == 0 && len == (int)(ft_strlen(s) - 1))
			break ;
		write(fd[1], s, ft_strlen(s));
		free (s);
	}
	free (s);
	close(fd[0]);
	close(fd[1]);
	//All the memory has to be cleared here!
	exit(0);
}

/*
* @brief Checks if theres any here_doc in the redirections of each command
* and executes them, in case of it's existence.
*/
void	here_doc_check(t_commands *cmd)
{
	int				fd[2];
	pid_t			pid;
	t_redirection	*redir;

	redir = cmd->redirect;
	while (redir)
	{
		if (redir->type != RDIR_HDOC)
			continue ;
		to_close(cmd->hd_fd);
		if (pipe(fd) == 1)
			ft_printf("Error\n");//			Error treatment!
		pid = fork();
		if (pid == 0)
			here_doc(redir, fd);
		wait(NULL);
		fd[1] = to_close(fd[1]);
		cmd->hd_fd = fd[0];
		redir = redir->next;
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
		if (current->redirect)
			here_doc_check(current);
		current = current->next;
	}
}

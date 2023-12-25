/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handeling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:08 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/24 19:17:56 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ATENTION! Still to do the error handeling */

/*
* @brief Creates an array with the directories to the binaries. If
* PATH environment variable doesn't exists, the array is set to NULL
*/
void	bin_finder(t_exec *exec)
{
	int	i;

	i = -1;
	while (exec->data->env[i])
	{
		if (ft_strncmp("PATH=", exec->data->env[i], 5) == 0)
			break ;
	}
	if (!exec->data->env[i])
		return ;
	exec->bin_dir = ft_split(exec->data->env, ':');
	i = -1;
	while (exec->bin_dir[++i])
		exec->bin_dir[i] = ft_strjoin_free(exec->bin_dir, "/", 1);
	while (exec->bin_dir[exec->nbr_bin])
		exec->nbr_bin++;
	
}

/*
* @brief It finds and associates the correct path to the binary of each
 corresponding command
*/
void	path_finder(t_exec *exec, t_commands *cmd)
{
	int	i;

	i = -1;
	while (exec->bin_dir[++i])
	{
		cmd->cmd_path = ft_strjoin(exec->bin_dir[i], cmd->cmds[0]);
		if (access(cmd->cmd_path, F_OK) == 0 || i == exec->bin_dir - 1)
			break ;
		free (cmd->cmd_path);
	}
	if (access(cmd->cmd_path, F_OK) != 0)
		ft_printf("Error\n") ;			// Error handeling
}

// /*
// * @brief takes the environment array and atributes to each command the
// * correct path to it's binary
// */
// void	command_path(t_data *data, t_exec *exec)
// {
// 	t_commands *current;

// 	current = data->first_cmd;
// 	bin_finder(exec);
// 	while (current)
// 	{
// 		if (!exec->bin_dir)
// 		{
// 			current->cmd_path = ft_strdup(current->cmds[0]);
// 			continue ;
// 		}
// 		path_finder(exec, current);
// 	}

// }


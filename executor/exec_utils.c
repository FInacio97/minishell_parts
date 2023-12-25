/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:52:11 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/25 15:13:47 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief Calls the builtins functions
*/
void	biltin_check(t_exec *exec, t_commands *cmd)
{
	if (ft_strncmp("echo", cmd->cmds[0], 5) == 0)
		echo(cmd->cmds + 1);
	else if (ft_strncmp("cd", cmd->cmds[0], 3) == 0)
		cd(cmd->cmds + 1);
	else if (ft_strncmp("pwd", cmd->cmds[0], 4) == 0)
		pwd();
	else if (ft_strncmp("export", cmd->cmds[0], 7) == 0)
		export(cmd->cmds + 1);
	else if (ft_strncmp("unset", cmd->cmds[0], 6) == 0)
		unset(cmd->cmds + 1);
	else if (ft_strncmp("env", cmd->cmds[0], 4) == 0)
		env(cmd->cmds + 1);
	else if (ft_strncmp("exit", cmd->cmds[0], 5) == 0)
		exit(cmd->cmds + 1);
}

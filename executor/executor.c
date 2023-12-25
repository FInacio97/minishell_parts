/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:45:20 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/25 18:27:07 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief Initializes all variables in the executor struct
*/
void	initializer_exec(t_data *data, t_exec *exec)
{
	exec->bin_dir = NULL;
	exec->nbr_bin = 0;
	exec->fd[0] = -1;
	exec->fd[1] = -1;
	exec->remainder_fd = -1;
	exec->data = data;
	exec->pid = malloc(sizeof(pid_t) * data->nbr_cmds);
	bin_finder(exec);
}

/*
* @brief Rearanges the standardin/out to accomudate the proper file descriptors
*/
void	dupper(t_commands *cmd)
{
	if (cmd->read_fd != STDIN_FILENO)
	{
		dup2(cmd->read_fd, STDIN_FILENO);
		cmd->read_fd = to_close(cmd->read_fd);
	}
	if (cmd->write_fd != STDOUT_FILENO)
	{
		dup2(cmd->write_fd, STDOUT_FILENO);
		cmd->write_fd = to_close(cmd->write_fd);
	}
}
/*
* @brief Deals with redirections, with file permissions 
* and executes the command
* @param exec executor's struct
* @param cmd the command to be executed
*/
void	executor(t_exec *exec, t_commands *cmd)
{
	redirection(exec, cmd);
	dupper(cmd);
	close(exec->remainder_fd);
	builtin_check(cmd);
	if (cmd->cmds)				//	this has to be here in case theres no command (ex: << EOF)
	{									// it will execute without any errors
		path_finder(exec, cmd);
		execve(cmd->cmd_path, cmd->cmds, exec->data->env);
		printf("Error\n");		//	Error handeling
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(0);						//	Exit function to clean all memory, put a proper exit status
}

/*
* @brief Managed all open file descriptors at the begging of the execution
*/
void	fd_handeler_in(t_exec *exec, t_commands *cmd)
{
	if (exec->remainder_fd > 0)
		cmd->read_fd = exec->remainder_fd;
	else
		cmd->read_fd = STDIN_FILENO;
	if (exec->fd[1] > 0)
		cmd->write_fd = exec->fd[1];
	else
		cmd->write_fd = STDOUT_FILENO;
}

/*
* @brief Managed all open file descriptors at the end of the execution
*/
void	fd_handeler_out(t_exec *exec)
{
	exec->remainder_fd = to_close(exec->remainder_fd);
	exec->remainder_fd = exec->fd[0];
	exec->fd[1] = to_close(exec->fd[1]);
	
}

/*
* @brief Waits for all children processes to finish their execution,
* recording the latest exit status
*/
void	wait_loop(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_cmds)
		wait(data->exit_status);
}

/*
* @brief Manages the creation of the children processes and its
* pipes
*/
void	process_generator(t_data *data)
{
	t_exec		*exec;
	t_commands	*current;
	int			i;

	current = data->first_cmd;
	initializer_exec(data, exec);
	i = -1;
	while (current)
	{

		if (current->next && pipe(exec->fd) != 0)
			ft_printf("Error\n"); //	Error handeling
		fd_handeler_in(exec, current);
		exec->pid[++i] = fork();
		if (exec->pid[i] == 0)
			executor(exec, current);
		fd_handeler_out(exec);
		current = current->next;
	}
	wait_loop(data);
	//	Wait func

}
/* EXECUTOR
			[ ]	verifies if files path exists
			[ ]	verifies permissions
			[ ]	(it does both steps 1 and 2 in the order of which they were prompted)
			[ ]	check if command is a builtin
			[ ]	creates path of binary
			[ ]	redirections ????
			[ ]	executes command (verifies if command exists)
*/

/*PROCESS GENERATOR
			Initialize the struct
			create array with binary directories
			wait for the exit status of every child process
			free all the memory and close all fds; (Maybe do it inside
				of the fd_handeling function)
*/
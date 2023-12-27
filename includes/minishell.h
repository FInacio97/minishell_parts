/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:34:32 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/26 16:47:11 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef enum
{
	IN,											//	input file (<)
	HD,											//	here document (<<)
	OUT,										//	truncate output file (>)
	APP,										//	append output file (>>)
}			t_redir_type;

typedef struct s_redirection
{
	char					*key_wrd;			//	[X]	The key word after the operand: limiter or file name
	int						type;				//	[X]	Redirection type (t_redir_type)
	struct s_redirection	*next;	 			//	[X]	Pointer to the next redirection struct
	
}				t_redirection;


typedef struct s_commands
{
	char				**cmds;					//	[X] The command and it respective arguments
	char				*cmd_path;				//	[ ] The path to the command's binary
	t_redirection		*redirect;				//	[X] All redirections
	int					hd_fd;					//	[ ] The fd corresponding to the here_doc
	int					read_fd;				//	[ ] The fd corresponding to the here_doc
	int					write_fd;				//	[ ] The fd corresponding to the here_doc
	struct s_commands	*next;					//	[X] Next command in the pipeline
	
}				t_commands;

typedef struct s_exec
{
	char			**bin_dir;					//	the splited binary directories
	int				nbr_bin;					//	number of binary directories
	int				fd[2];						//	pipe's file descriptors (in front)
	int				remainder_fd;				//	reading end of the back pipe
	pid_t			*pid;						//	pids of the command's processes
	struct s_data	*data;						//	pointer to the data struct
}				t_exec;

typedef struct s_data
{
	t_commands	*first_cmd;						//	[X] Pointer to the struct of fist command in the pipeline
	char		**env;							//	[X] Environment variables
	int			nbr_cmds;						//	[X] Number of commands
	int			exit_status;					//	[ ] Exit status of the last child process
}				t_data;


/* HERE DOC */

// char	*get_limiter(char *redirect);
void	here_doc(t_redirection *redir, int fd[2]);
void	here_doc_check(t_commands *cmd);
void	here_doc_manager(t_data *data);


/* TOKENIZER */

void	token_divider(char *s);
int		quotes_neutralizer(char *tolk, char quote);
char	*unquoter(char *tolken);
char	**tokenizer(char *s);


/* ECHO */

int		is_flag(char *s);
void	echo(char **prompt);


/* UTILS */

int		to_close(int fd);

/* *************************************************** */
/* EXECUTOR */

void	initializer_exec(t_data *data, t_exec *exec);
void	dupper(t_commands *cmd);
void	executor(t_exec *exec, t_commands *cmd);
void	fd_handeler_in(t_exec *exec, t_commands *cmd);
void	fd_handeler_out(t_exec *exec);
void	wait_loop(t_data *data);
void	process_generator(t_data *data);


/* REDIRECTIONS */

void	redir_in(t_exec *exec, t_commands *cmd, t_redirection *redir);
void	redir_out_trunc(t_exec *exec, t_commands *cmd, t_redirection *redir);
void	redir_out_append(t_exec *exec, t_commands *cmd, t_redirection *redir);
void	redirect(t_exec *exec, t_commands *cmd);

/* EXEC_UTILS */

void	biltin_check(t_exec *exec, t_commands *cmd);


/* PATH HANDELING */

void	bin_finder(t_exec *exec);
void	path_finder(t_exec *exec, t_commands *cmd);

#endif
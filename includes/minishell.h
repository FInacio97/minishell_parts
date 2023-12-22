/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:34:32 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/22 11:10:00 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct s_commands
{
	char				**cmds;
	char				**redirect_in;
	char				**redirect_out;
	int					in_fd;
	struct s_commands	*next;
	
}				t_commands;

typedef struct s_data
{
	t_commands	*first_cmd;
}				t_data;


/* HERE DOC */
char	*get_limiter(char *redirect);
void	here_doc(t_commands *cmd, int lst_redirect);
void	fake_here_doc(char *redirect);
void	here_doc_check(t_commands *cmd);
void	here_doc_manager(t_data *data);

/* TOKENIZER */
void	token_divider(char *s);
char	**tokenizer(char *s);
char	*unquoter(char *tolken);
int		quotes_neutralizer(char *tolk, char quote);

/* ECHO */
int		is_flag(char *s);
void	echo(char **prompt);

/* UTILS */
int	to_close(int fd);

#endif
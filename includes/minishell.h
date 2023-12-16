/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:34:32 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/16 18:59:55 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"

/* TOKENIZER */
void	token_divider(char *s);
char	**tokenizer(char *s);
char	*unquoter(char *tolken);
int		quotes_neutralizer(char *tolk, char quote);

/* ECHO */
int		is_flag(char *s);
void	echo(char **prompt);

#endif
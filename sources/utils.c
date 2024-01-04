/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:02:04 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/04 12:56:52 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief closes an fd in a safe way
* @param (fd)
* @returns -1, so it can be associated to the fd variable that was closed
*/
int	to_close(int fd)
{
	if (fd > 0)
		close (fd);
	return (-1);
}

/*
* @brief checks if a token is a redirection
* @param the first char of a token
* @returns 1 if its a redirection and 0 if it isn't
*/
int    is_redir_token(char c)
{
    if (c && (c == '>' * -1 || c == '<' * -1 || c == '|' * -1))
        return (1);
    return (0);
}

/*
* @brief sets a token as a redirection
* @param str the toke
* @returns the redirection value if str represents one
* and the first char of str if it isnt a redirectrion
*/
int    what_redir_token(char *str)
{
    if (str && *str && is_redir_token(*str))
    {
        if (str[0] != str[1])
        {
            if (*str == '<' * -1)
                return (RDIR_IN);
            else if (*str == '>' * -1)
                return (RDIR_OUT);
            else if (*str == '|' * -1)
                return (RDIR_PIPE);
        }
        else
        {
            if (*str == '<'  * -1)
                return (RDIR_APP);
            else if (*str == '>' * -1)
                return (RDIR_HDOC);
            else if (*str == '|' * -1)
                return (RDIR_DPIPE);
        }
    }
    return (str[0]);
}
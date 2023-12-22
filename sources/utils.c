/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:02:04 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/21 14:29:09 by fda-estr         ###   ########.fr       */
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

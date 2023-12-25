/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:30:35 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/25 18:44:00 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
* @brief Marks all white spaces, so it can be splited
* @param s a portion of the prompt corresponding to a command
*/
void	token_divider(char *s)
{
	int		i;
	char	quote;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
			i++;		
		}
		while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\'' && s[i] != '\"')
			i++;
		if (s[i] == ' ' || s[i] == '\t')
			s[i] = -1;
		// if (s[i] == '\'' || s[i] == '\"')
		// 	i--;
	}
}

/*
* @brief Marks all outer quotes for further removal
* @param tolk pointer to the tolken
* @param the type of quote to be replaced
* @return the number of caracters inbetween outer quotes
*/
int	quotes_neutralizer(char *tolk, char quote)
{
	int	i;

	i = -1;
	tolk[++i] = -1;
	while (tolk[++i])
	{
		if (quote == '\'' && tolk[i] == '$')
			tolk[i] = -2;
		if (tolk[i] == quote)
		{
			tolk[i] = -1;
			return (i);
		}
	}
	return (i);
}

/*
* @brief Removes all marked quotes
* @param tolk pointer to the tolken
*/
char	*unquoter(char *tolken)
{
	int		nbr_quotes;
	int		i;
	int		j;
	char	*prod;

	nbr_quotes = 0;
	i = 0;
	while (tolken[i])
	{
		if (tolken[i] == '\'' || tolken[i] == '\"')
		{
			i += quotes_neutralizer(tolken + i, tolken[i]);
			nbr_quotes += 2;
		}
		while (tolken[i] && tolken[i] != '\"' && tolken[i] != '\'')
			i++;
	}
	prod = malloc(ft_strlen(tolken) - nbr_quotes + 1);
	i = -1;
	j = 0;
	while (tolken[++i])
	{
		if (tolken[i] == -1)
		{
			j++;
			continue ;
		}
		prod[i - j] = tolken[i];
	}
	prod[i - j] = 0;
	free (tolken);
	return (prod);
}

/*
* @brief Splits the prompt in tolkens
* @param the portion of the prompt to be tolkenized
*/
char	**tokenizer(char *s)
{
	char	**tolkens;
	int		i;

	i = -1;
	token_divider(s);
	tolkens = ft_split(s, -1);
	while (tolkens[++i])
		tolkens[i] = unquoter(tolkens[i]);
	return (tolkens);
}

// char	*quotes(char *s, char quote)
// {
// 	int		i;
// 	int		j;
// 	char	*prod;

// 	i = 0;
// 	while (s[i] =! quote)
// 		i++;
// 	while (s[i] != ' ')
// 		i++;
// 	prod = malloc(i -1);
// 	if (!prod)
// 		return (NULL);
// 	i = -1;
// 	j = -1;
// 	s++;
// 	while (s[++i] != quote)
// 		prod[i] = s[i];
// 	if (s[++i] == ' ')
	 
	
// }

// char	token_filler(char ** tokens, char *s)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = 0;
// 	while (s[++i])
// 	{
// 		if (s[i] == '\'' || s[i] == '\"')
// 			tokens[j] = quotes(s + i, s[i]);
// 	}
// }
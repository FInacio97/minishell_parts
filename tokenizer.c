/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:30:35 by fda-estr          #+#    #+#             */
/*   Updated: 2023/12/09 23:06:10 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	token_counter(char *s)
{
	int		i;
	int		nbr;
	char	quote;

	nbr = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;			
		}
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
		nbr++;
	}
	return (nbr);
}

char	token_filler(char ** tokens, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			quotes()
	}
}

char	**tokenizer(char *s)
{
	int	token_nbr;
	char **tokens;

	token_nbr = token_counter(s);
	tokens = (char *)malloc(token_nbr + 1);
	return (token_filler(tokens, s));
}
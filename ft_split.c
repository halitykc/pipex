/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:08:55 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/29 12:09:01 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_wc(char const *s, char c)
{
	int	i;
	int	inword;
	int	count;

	inword = 0;
	count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] != c && inword == 0)
		{
			inword = 1;
			count++;
		}
		else if (s[i] == c && inword != 0)
			inword = 0;
	}
	return (count);
}

static void	ft_free(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
}

static void	ft_findnword(int *start, int *end, char const *s, char c)
{
	*start = *end;
	while (s[*start] && s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] && s[*end] != c)
		(*end)++;
}

static int	ft_fill_w(char **res, char const *s, char c, int num)
{
	int	i;
	int	start;
	int	end;
	int	len;

	start = 0;
	end = 0;
	i = 0;
	while (i < num)
	{
		ft_findnword(&start, &end, s, c);
		len = end - start;
		res[i] = ft_substr(s, (unsigned int)start, (size_t)len);
		if (!res[i])
		{
			ft_free(res, i);
			return (0);
		}
		i++;
	}
	res[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		wnumber;

	if (!s)
		return (NULL);
	wnumber = ft_wc(s, c);
	res = malloc((wnumber + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	if (!ft_fill_w(res, s, c, wnumber))
		return (NULL);
	return (res);
}

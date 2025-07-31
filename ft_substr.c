/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:09:12 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/31 14:08:05 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	alen;

	if ((!s || !len) || start >= ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s) - start)
		alen = ft_strlen(s) - start;
	else
		alen = len;
	sub = malloc(alen + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start] && i < ft_strlen(s) && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

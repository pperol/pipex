/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:48:56 by pperol            #+#    #+#             */
/*   Updated: 2022/10/13 11:09:38 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*init_str(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = ft_calloc(1, i + 1);
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}

char	**ft_split_non_ptr(char **ptr, int i)
{
	if (!ptr)
	{
		while (i > 0)
			free(ptr[i--]);
		free(ptr);
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**ptr;

	if (!s)
		return (NULL);
	len = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		while (s[0] == c)
			s++;
		ptr[i] = init_str(s, c);
		ft_split_non_ptr(ptr, i);
		s = s + ft_strlen(ptr[i]);
	}
	ptr[i] = NULL;
	return (ptr);
}

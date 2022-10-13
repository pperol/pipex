/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 08:50:16 by pperol            #+#    #+#             */
/*   Updated: 2022/10/13 11:05:12 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(char const *s)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s);
	dup = ft_calloc(1, size + 1);
	if (dup)
	{
		ft_memcpy(dup, s, size);
		return (dup);
	}
	return (0);
}

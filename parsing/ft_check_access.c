/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:29:38 by pperol            #+#    #+#             */
/*   Updated: 2022/10/12 17:34:24 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
// man : access()  checks  whether the calling process can access the file path‐
// name.  If pathname is a symbolic link, it is dereferenced.

int	ft_check_access(char *file_path_name)
{
	if (access(file_path_name, F_OK) == 0)
		return (1);
	else
		return (0);
}
*/

#include "../pipex.h"

int	ft_check_access(char *file_path_name)
{
	if (access(file_path_name, F_OK) == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:56:13 by pperol            #+#    #+#             */
/*   Updated: 2022/12/06 13:41:54 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path(char **env)
{
	int	i;

	i = 0;
	if (!*env)
		return (NULL);
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	return (env[i] + 5);
}

char	*ft_get_cmd(char **path, char *cmd)
{
	size_t	i;
	char	*tmp;
	char	*command;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK && X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

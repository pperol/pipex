/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:22:10 by pperol            #+#    #+#             */
/*   Updated: 2022/10/13 15:45:23 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

char	*ft_find_path(char **env)
{
	int i;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	return (env[i] + 5);
}

char	*ft_get_cmd(char **path, char *cmd)
{
	size_t	i;
	char	*tmp;
	char	*command;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_free_child(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	ft_putstr_fd("Usage:\n./pipex file1 cmd1 cmd2 file2\n", 2);
	ft_error(ERR_CMD);
	exit (1);
}

void	ft_child(size_t child, t_pipe pipex, char **av, char **env)
{
	char	*cmd;
	char	**args;

	if (child == 1)
	{
		dup2(pipex.pipe[1], 1);
		close(pipex.pipe[0]);
		dup2(pipex.infile, 0);
		args = ft_split(av[2], ' ');
	}
	if (child == 2)
	{
		dup2(pipex.pipe[0], 0);
		close(pipex.pipe[1]);
		dup2(pipex.outfile, 1);
		args = ft_split(av[3], ' ');
	}	
	cmd = ft_get_cmd(pipex.path, args[0]);
	if (!cmd)
	{
		ft_free_child(args);	
		free(cmd);
	}
	execve(cmd, args, env);
}

void	ft_free_cmd_path(t_pipe *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->path[i])
	{
		free(pipex->path[i]);
		i++;
	}
	free(pipex->path);
}

void	ft_pipex(char **av, char **env)
{
	t_pipe	pipex;
	pid_t	pid1;
	pid_t 	pid2;
	char	*path;

	path = ft_find_path(env);
	pipex.path = ft_split(path, ':');
	pid1 = fork();
	if (pid1 == 0)
		ft_child(1, pipex, av, env);
	pid2 = fork();
	if (pid2 == 0)
		ft_child(2, pipex, av, env);
	close(pipex.pipe[0]);
	waitpid(pid1, NULL, 0);
	close(pipex.pipe[1]);
	waitpid(pid2, NULL, 0);
	ft_free_cmd_path(&pipex);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;

	if (ac != 5)
	{
		ft_error(ERR_INPUT);
		ft_putstr_fd("Usage:\n./pipex file1 cmd1 cmd2 file2\n", 2);
		return (EXIT_FAILURE);
	}
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (EXIT_FAILURE);
	ft_pipex(av, env);
	return (0);
}

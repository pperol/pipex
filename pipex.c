/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:22:10 by pperol            #+#    #+#             */
/*   Updated: 2022/10/12 18:03:51 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipe pipex, char **av, char **env)
{
	int	i;

	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	execve(pipex.cmd, pipex.cmd_args, env);
	if (!pipex.cmd)
	{
		i = 0;
		while (pipex.cmd_args[i])
		{
			free(pipex.cmd_args[i]);
			i++;
		}
		free(pipex.cmd_args);
		free(pipex.cmd);
		ft_msg_err(ERR_CMD);
		//exit ;
	}
}

void	second_child(t_pipe pipex, char **av, char **env)
{
	int	i;

	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	execve(pipex.cmd, pipex.cmd_args, env);
	if (!pipex.cmd)
	{
		i = 0;
		while (pipex.cmd_args[i])
		{
			free(pipex.cmd_args[i]);
			i++;
		}
		free(pipex.cmd_args);
		free(pipex.cmd);
		ft_msg_err(ERR_CMD);
		//exit ;
	}
}

void	ft_free_cmd(t_pipe *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	ft_pipex(char **av, char **env)
{
	t_pipe	pipex;

	pipex.paths = ft_find_path(env);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, env);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free_cmd(&pipex);
}


int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;

	if (ac != 5 || ft_check_access(av[1]))
	{
		ft_putstr_fd("Usage:\n./pipex file1 cmd1 cmd2 file2\n", 2);
		return (ft_msg_err(ERR_INPUT));
	}
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (EXIT_FAILURE);
	ft_pipex(av, env);
	return (0);
}

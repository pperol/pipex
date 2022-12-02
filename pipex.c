/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:46:12 by pperol            #+#    #+#             */
/*   Updated: 2022/12/02 13:32:26 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(size_t child, t_pipe *pipex, char **av, char **env)
{
	char	*cmd;
	char	**args;

	args = NULL;
	if (child == 1)
	{
		dup2(pipex->pipefd[1], 1);
		close(pipex->pipefd[0]);
		dup2(pipex->infile, 0);
		args = ft_split(av[2], ' ');
	}
	if (child == 2)
	{
		dup2(pipex->pipefd[0], 0);
		close(pipex->pipefd[1]);
		dup2(pipex->outfile, 1);
		args = ft_split(av[3], ' ');
	}	
	cmd = ft_get_cmd(pipex->path, args[0]);
	if (!cmd)
	{
		ft_putstr_fd(args[0], 2);
		ft_free_child(args, cmd, pipex->path);
	}
	execve(cmd, args, env);
}

void	ft_pipex(t_pipe *pipex, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	char	*path;

	path = ft_find_path(env);
	pipex->path = ft_split(path, ':');
	pid1 = fork();
	if (pid1 == 0)
		ft_child(1, pipex, av, env);
	pid2 = fork();
	if (pid2 == 0)
		ft_child(2, pipex, av, env);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_free_cmd_path(pipex);
}

void	ft_open_fail(char **av, t_pipe pipex)
{
	if (pipex.infile < 0)
	{
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
	if (pipex.outfile < 0)
	{
		ft_putstr_fd(av[4], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;

	if (ac != 5)
	{
		ft_putstr_fd("Error input. Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!env || !*env || !**env)
	{
		ft_putstr_fd("Error env. Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (pipe(pipex.pipefd) == -1)
		ft_print_error();
	ft_open_fail(av, pipex);
	ft_pipex(&pipex, av, env);
	return (0);
}

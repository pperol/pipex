/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:46:12 by pperol            #+#    #+#             */
/*   Updated: 2022/12/05 15:26:44 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(size_t child, t_pipe *pipex, char **av, char **env)
{
	char	*cmd;
	char	**args;

	args = NULL;
	dup2(pipex->pipefd[(child - 2) * -1], ((child - 2) * -1));
	close(pipex->pipefd[child - 1]);
	if (child == 1)
		dup2(pipex->infile, 0);
	if (child == 2)
		dup2(pipex->outfile, 1);
	args = ft_split(av[child + 1], ' ');
	cmd = ft_get_cmd(pipex->path, args[0]);
	if (!cmd)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(args);
		free(cmd);
		ft_free_tab(pipex->path);
		exit(EXIT_FAILURE);
	}
	execve(cmd, args, env);
}

void	ft_pipex(t_pipe *pipex, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	char	*path;

	path = ft_find_path(env);
	if (!path)
		pipex->path = ft_split("", ' ');
	else
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
	close(pipex->infile);
	close(pipex->outfile);
	ft_free_tab(pipex->path);
}

void	ft_open_fail(char **av, t_pipe pipex)
{
	if (pipex.infile < 0)
	{
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
	if (pipex.outfile < 0)
	{
		ft_putstr_fd(av[4], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		close(pipex.pipefd[0]);
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
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	ft_open_fail(av, pipex);
	if (pipe(pipex.pipefd) == -1)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_pipex(&pipex, av, env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:46:12 by pperol            #+#    #+#             */
/*   Updated: 2022/12/02 12:15:36 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
We can divide the pipex workload on different children, while the parent waits 
for the job to be done and supervise the children’s status.
We will thus have to fork twice, and assign child1 to execute cmd1, and child2 
to execute cmd2. 
The parent will wait at the end. 

# ./pipex infile cmd1 cmd2 outfile

pipe()
 |
 |-- fork()
 :    |
 :    |-- child1 // cmd1
 :    :     |--dup2()
 :    :     |--close end[0]
 :    :     |--execve(cmd1)
 :    :
 |-- fork()
      |
      |-- child2 (cf. parent) // cmd2
      :     |--dup2()
      :     |--close end[1]
      :     |--execve(cmd2)

Cf.:
	--- http://www.man-linux-magique.net/man7/pipe.html
	--- http://www.man-linux-magique.net/man2/pipe.html
	--- http://www.man-linux-magique.net/man2/fork.html
	--- http://www.man-linux-magique.net/man2/dup.html
	--- http://www.man-linux-magique.net/man3/execl.html
	--- http://www.man-linux-magique.net/man2/execve.html
	--- https://fr.wikipedia.org/wiki/Variable_d%27environnement

void	ft_child(size_t child, t_pipe *pipex, char **av, char **env)
{
	char	*cmd;
	// Initialisation de cmd a NULL || (char *)0
	char	**args;
	// Initialisation de cmd a NULL || (char **)0

	if (child == 1)
	{
		dup2(pipex->pipefd[1], 1);

		close(pipex->pipefd[0]);

		dup2(pipex->infile, 0);
		
		args = ft_split(av[2], ' ');
		// Si tonn split fail quelles en sonnt les consequences ?
	}
	if (child == 2)
	{
		dup2(pipex->pipefd[0], 0);

		close(pipex->pipefd[1]);
		
		dup2(pipex->outfile, 1);
		
		args = ft_split(av[3], ' ');
		// Si tonn split fail quelles en sonnt les consequences ?
	}
	// check F_OK et X_OK Separement
	cmd = ft_get_cmd(pipex->path, args[0]);
	if (!cmd)
		ft_free_child(args, cmd, pipex->path);
	execve(cmd, args, env);
	// en cas d'erreur de ton exec_ve (il peux fail et dans ce cas, tu a un process zombie);
}

void	ft_pipex(t_pipe *pipex, char **av, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
	
	path = ft_find_path(env);
	pipex->path = ft_split(path, ':');
	// Si tonn split fail quelles en sonnt les consequences ?
	pid1 = fork();
	// Verifie la valeur de retour de ton fork car il peux fail
	//		Par exemple, dans le cas ou on t'envoie beaucoup  de pipe.
	// 
	if (pid1 == 0)
		ft_child(1, pipex, av, env);
	pid2 = fork();
	// Verifie la valeur de retour de ton fork car il peux fail
	//		Par exemple, dans le cas ou on t'envoie beaucoup  de pipe.
	// 
	if (pid2 == 0)
		ft_child(2, pipex, av, env);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_free_cmd_path(pipex);
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
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		perror("Error test_main");
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipex.pipefd) == -1)
		ft_print_error();
	ft_pipex(&pipex, av, env);
	return (0);
}	

*/

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
	//perror(strerror(errno));
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
	//printf("%s\n", *pipex->path);
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
	if (pipe(pipex.pipefd) == -1)
		printf("test pipe");
		//ft_print_error();
	ft_pipex(&pipex, av, env);
	return (0);
}
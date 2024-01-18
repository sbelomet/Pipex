/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/18 14:58:07 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	char *grep_args[] = {"/usr/bin/grep", "a", NULL};
	char *wc_args[] = {"/usr/bin/wc", "-w", NULL};
	int in;
	int	out;
	int pid;
	int pipefd[2];

	if (ac != 3)
		return (-1);
	in = open(av[1], O_RDONLY);
	out = open(av[2], O_WRONLY);
	pipe(pipefd);
	pid = fork();
	ft_printf("yesyes\n");
	if (pid == 0)
	{
		printf("i am child\n");
		close(pipefd[0]);
		close(out);
		dup2(in, STDIN_FILENO);
		close(in);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve("/usr/bin/grep", grep_args, env);
		
	}
	else
	{
		printf("i am parent\n");
		close(pipefd[1]);
		close(in);
		dup2(out, STDOUT_FILENO);
		close(out);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execve("/usr/bin/wc", wc_args, env);
		//dup2(STDOUT_FILENO, out);
		//ft_putstr_fd("before end\n", STDOUT_FILENO);
	}
	printf("end\n");
	int status;
	waitpid(pid, &status, 0);
	exit(0);
}

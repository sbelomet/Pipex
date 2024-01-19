/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:00:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/01/19 15:49:46 by sbelomet         ###   ########.fr       */
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
	//int stdin_copy = dup(0);
	int stdout_copy;
	int status;

	if (ac != 3)
		return (-1);

	stdout_copy = dup(1);
	in = open(av[1], O_RDONLY);
	out = open(av[2], O_WRONLY);
	pipe(pipefd);
	pid = fork();
	//printf("in: %d, out: %d, stdout_copy: %d\n", in, out, stdout_copy);
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
		//wait(&status);
		printf("i am parent\n");
		close(pipefd[1]);
		close(in);
		dup2(out, STDOUT_FILENO);
		close(out);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		execve("/usr/bin/wc", wc_args, env);
		//dup2(STDOUT_FILENO, out);
		
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdout_copy);
		ft_putstr_fd("before end\n", STDOUT_FILENO);
	}
	ft_putstr_fd("before end almost\n", STDOUT_FILENO);
	waitpid(pid, &status, 0);
	ft_putstr_fd("end\n", STDOUT_FILENO);
	exit(0);
}
/* 
int main(void)
{
	int f = open("test.txt", O_RDWR);
	int out = dup(1);

	if(f == -1)
			perror("open()");

	dup2(f, 1);

	printf("Hello world\n");

	printf("%d\n",close(f));

	dup2(out, 1);

	printf("test\n");

	return 0;
} */

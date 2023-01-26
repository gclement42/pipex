/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:08:43 by gclement          #+#    #+#             */
/*   Updated: 2023/01/26 14:34:56 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

int	main(int argc, char	*argv[], char *envp[])
{
	char	**cmd;
	char	**argxec;
	char	**all_path;
	pid_t	pid;
	int		fd[2];
	int 	in_fd;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit (0);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		all_path = create_array_path(envp);
		in_fd = open(argv[1], O_RDONLY);
		if (pid == 0)
		{
			close(fd[0]);
			dup2(in_fd, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			cmd = ft_split(argv[2], ' ');
			argxec = set_argxec(cmd);
			call_cmd(argxec, cmd, all_path);
			exit (0);
		}
		else
			parent(fd, argv, all_path);
	}
}

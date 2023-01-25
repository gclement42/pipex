/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:08:43 by gclement          #+#    #+#             */
/*   Updated: 2023/01/25 13:40:57 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char	*argv[], char *envp[])
{
	char	**cmd;
	char	**argxec;
	char	**all_path;
	pid_t	pid;
	int		fd[2];

	(void) argc;
	pid = fork();
	if (pipe(fd) == -1)
		exit (0);
	if (pid == -1)
		exit(EXIT_FAILURE);
	all_path = create_array_path(envp);
	if (pid == 0)
		child(fd, argv, all_path);
	else
	{
		close(STDOUT_FILENO);
		dup2(fd[1], 1);
		cmd = ft_split(argv[2], ' ');
		argxec = set_argxec(cmd, argv[1]);
		call_cmd(argxec, cmd, all_path);
	}
	free_2d_array(all_path);
	exit (EXIT_SUCCESS);
}

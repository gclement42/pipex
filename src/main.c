/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:08:43 by gclement          #+#    #+#             */
/*   Updated: 2023/02/13 13:53:28 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char	*argv[], char *envp[])
{
	char	**all_path;
	pid_t	pid;
	pid_t	pid2;
	int		fd[2];
	int		status;

	if (argc == 5 && (argv[2][0] != '\0' && argv[3][0] != '\0'))
	{
		if (pipe(fd) == -1)
			exit (0);
		pid = fork();
		all_path = create_array_path(envp);
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			set_frst_cmd(fd, argv, all_path);
		pid2 = fork();
		if (pid2 == 0)
		{
			waitpid(pid2, &status, 0);
			set_scnd_cmd(fd, argv, all_path);
		}
		free_2d_array(all_path);
	}
}

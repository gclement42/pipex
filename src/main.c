/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:08:43 by gclement          #+#    #+#             */
/*   Updated: 2023/01/27 10:20:56 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char	*argv[], char *envp[])
{
	char	**all_path;
	pid_t	pid;
	int		fd[2];

	if (argc == 5 && (argv[2][0] != '\0' && argv[3][0] != '\0'))
	{
		if (pipe(fd) == -1)
			exit (0);
		if (open(argv[1], O_RDONLY) == -1)
			exit (0);
		all_path = create_array_path(envp);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_frst_cmd(fd, argv, all_path);
		else
			execute_scnd_cmd(fd, argv, all_path);
	}
}

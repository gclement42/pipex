/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:21:51 by gclement          #+#    #+#             */
/*   Updated: 2023/02/13 14:09:33 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

char	**set_argxec(char **cmd);
void	call_cmd(char **argxec, char **cmd, char **all_path);
char	**create_array_path(char *envp[]);
void	set_frst_cmd(int fd[2], char **argv, char **all_path);
void	set_scnd_cmd(int fd[2], char **argv, char **all_path);

void	*free_2d_array(char **ptr);
void	exit_wrong_cmd(char **cmd, char **all_path);
void	free_and_exit(char **all_path);
void	free_in_execmd(char **all_path, char **cmd, char **argxec);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:21:51 by gclement          #+#    #+#             */
/*   Updated: 2023/01/26 18:45:09 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../Libft/libft.h"

char	**set_argxec(char **cmd);
void	call_cmd(char **argxec, char **cmd, char **all_path);
char	**create_array_path(char *envp[]);
void	set_frst_cmd(int fd[2], char **argv, char **all_path);
void	set_scnd_cmd(int fd[2], char **argv, char **all_path);

void	*free_2d_array(char **ptr);
void	exit_wrong_cmd(char **cmd);

#endif

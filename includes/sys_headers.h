/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_headers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:44:53 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 14:54:42 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYS_HEADERS_H
# define SYS_HEADERS_H

# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef S_APPEND
#  define S_APPEND 02000
# endif

#endif

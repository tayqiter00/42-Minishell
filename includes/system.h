/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:03:22 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 10:29:50 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__linux__)
#define OS_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC
#else
#error "Unknown operating system"
#endif

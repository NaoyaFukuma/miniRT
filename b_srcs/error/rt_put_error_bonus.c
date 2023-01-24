/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_put_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:54:43 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/18 11:41:41 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	rt_put_error_exit(const char *msg)
{
	ft_putstr_fd("\e[31mError\n", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	rt_put_rt_file_format_error_exit(const char *msg)
{
	ft_putstr_fd("\e[31mError\n*.rt file invalid format:  ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	rt_perror_exit(const char *msg)
{
	ft_putstr_fd("\e[31mError\n", STDERR_FILENO);
	perror(msg);
	exit(EXIT_FAILURE);
}

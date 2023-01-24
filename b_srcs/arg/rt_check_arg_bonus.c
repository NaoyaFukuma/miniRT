/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_arg_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:49:09 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 17:03:31 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_put_error_bonus.h"
#include <fcntl.h>
#include <stdbool.h>

static bool	rt_extension(const char *file);
bool		rt_open(const char *file);

void	rt_check_arg(int ac, const char **av)
{
	if (ac != 2)
		rt_put_error_exit("Only two arguments are required");
	if (rt_extension(av[1]))
		rt_put_error_exit("The file name format is *.rt");
	if (rt_open(av[1]))
		rt_perror_exit("File open failure");
}

static bool	rt_extension(const char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (true);
	if (file[len - 1] != 't')
		return (true);
	if (file[len - 2] != 'r')
		return (true);
	if (file[len - 3] != '.')
		return (true);
	return (false);
}

bool	rt_open(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (true);
	if (close(fd) < 0)
		return (true);
	return (false);
}

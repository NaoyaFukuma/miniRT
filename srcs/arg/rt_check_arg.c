/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:49:09 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/14 13:04:12 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt_put_error.h"
#include <fcntl.h>
#include <stdbool.h>

static bool	rt_extension(char *file);
bool		rt_open(char *file);

void	rt_check_arg(int ac, char **av)
{
	if (ac != 2)
		rt_put_error_exit("Only two arguments are required");
	if (rt_extension(av[1]))
		rt_put_error_exit("The file name format is *.rt");
	if (rt_open(av[1]))
		rt_perror_exit(NULL);
}

static bool	rt_extension(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (true);
	if (file[len - 1] != 't')
		return (true);
	if (file[len - 2] != 'r')
		return (true);
	if (file[len - 3] != '.')
		return (true);
	return (false);
}

bool	rt_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (true);
	close(fd);
	return (false);
}

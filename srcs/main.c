/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:49:07 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 17:38:30 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "rt_draw.h"
#include "rt_check_arg.h"
#include "rt_init.h"
#include "rt_structs.h"
#include "libft.h"

/* #include <stdlib.h>

__attribute__((destructor))
static void destructor(void)
{
	system("leaks -q miniRT");
} */

int	main(int ac, char **av)
{
	t_rt_data	rt;

	ft_bzero(&rt, sizeof(t_rt_data));
	rt_check_arg(ac, av);
	rt_init(&rt, av[1]);
	rt_draw(&rt);
	ft_putchar_fd('\n', STDOUT_FILENO);
	mlx_loop(rt.mlx.mlx);
	return (ac);
}

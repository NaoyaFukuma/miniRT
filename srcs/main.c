/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:49:07 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/14 14:58:22 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_strucs.h" // for struct t_rt_data
#include "rt_check_arg.h" // for rt_check_arg()
#include "rt_init.h" // for rt_init()

int	main(int ac, char **av)
{
	t_rt_data	rt;

	rt_check_arg(ac, av);
	rt_init(&rt, av[1]);
	// rt_draw(rt);
	return (ac);
}
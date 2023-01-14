/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/14 15:01:21 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_strucs.h"
#include "mlx.h"

void	rt_init(t_rt_data *rt, char *file)
{
	// rt_import_scene(rt, file);
	(void)file;
	rt->mlx.mlx = mlx_init();
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, 465, 262, "miniRT");
	mlx_loop(rt->mlx.mlx);
}

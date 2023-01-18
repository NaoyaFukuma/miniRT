/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:08:13 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 16:18:47 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "rt_define.h"
#include "rt_strucs.h"
#include <stdlib.h>

static int	rt_KeyPress_hook(int keycode, t_rt_data *rt);
static int	rt_DestroyNotify_hook(t_rt_data *rt);
// static int	rt_draw_loop_hook(t_rt_data *rt);

void	rt_hooks(t_rt_data *rt)
{
	mlx_hook(rt->mlx.win, KeyPress, 0, rt_KeyPress_hook, rt);
	mlx_hook(rt->mlx.win, DestroyNotify, 0, rt_DestroyNotify_hook, rt);
	// mlx_loop_hook(rt->mlx.mlx, rt_draw_loop_hook, ,rt);
}

static int	rt_KeyPress_hook(int keycode, t_rt_data *rt)
{
	(void)rt;
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static int	rt_DestroyNotify_hook(t_rt_data *rt)
{
	(void)rt;
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

// static int	rt_draw_loop_hook(t_rt_data *rt)
// {
// 	rt_draw(rt);
// 	mlx_put_image_to_window(rt->mlx.mlx, rt->mlx.win, rt->mlx.image.img, 0, 0);
// 	return (EXIT_SUCCESS);
// }
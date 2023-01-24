/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:08:13 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 16:23:47 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "rt_define.h"
#include "rt_draw.h"
#include "rt_structs.h"
#include <stdlib.h>

static int	rt_keypress_hook(int keycode, t_rt_data *rt);
static int	rt_destroynotify_hook(t_rt_data *rt);

void	rt_hooks(t_rt_data *rt)
{
	mlx_hook(rt->mlx.win, KEYPRESS, 0, rt_keypress_hook, rt);
	mlx_hook(rt->mlx.win, DESTROYNOTIFY, 0, rt_destroynotify_hook, rt);
}

static int	rt_keypress_hook(int keycode, t_rt_data *rt)
{
	(void)rt;
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static int	rt_destroynotify_hook(t_rt_data *rt)
{
	(void)rt;
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:08:13 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/20 13:59:57 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "rt_define.h"
#include "rt_structs.h"
#include "rt_draw.h"
#include <stdlib.h>

static int	rt_KeyPress_hook(int keycode, t_rt_data *rt);
static int	rt_DestroyNotify_hook(t_rt_data *rt);

void	rt_hooks(t_rt_data *rt)
{
	mlx_hook(rt->mlx.win, KeyPress, 0, rt_KeyPress_hook, rt);
	mlx_hook(rt->mlx.win, DestroyNotify, 0, rt_DestroyNotify_hook, rt);
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

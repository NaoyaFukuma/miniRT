/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/16 10:48:37 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "rt_put_error.h"
#include "rt_strucs.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>


#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease		5
#define MotionNotify		6
#define EnterNotify		7
#define LeaveNotify		8
#define FocusIn			9
#define FocusOut		10
#define KeymapNotify		11
#define Expose			12
#define GraphicsExpose		13
#define NoExpose		14
#define VisibilityNotify	15
#define CreateNotify		16
#define DestroyNotify		17
#define UnmapNotify		18
#define MapNotify		19
#define MapRequest		20
#define ReparentNotify		21
#define ConfigureNotify		22
#define ConfigureRequest	23
#define GravityNotify		24
#define ResizeRequest		25
#define CirculateNotify		26
#define CirculateRequest	27
#define PropertyNotify		28
#define SelectionClear		29
#define SelectionRequest	30
#define SelectionNotify		31
#define ColormapNotify		32
#define ClientMessage		33
#define MappingNotify		34
#define LASTEvent		35
#define StructureNotifyMask (1L << 17)

void	rt_mlx(t_rt_data *rt);
void	rt_import(t_rt_data *rt, char *file);

int rt_KeyPress(int keycode, t_rt_data *rt)
{
	(void)rt;
	printf("rt_KeyPress");
	printf("keycode == %d\n", keycode);
	return (0);
}

int rt_KeyRelease(int keycode, t_rt_data *rt)
{
	(void)rt;
	printf("rt_KeyRelease");
	printf("keycode == %d\n", keycode);

	return (0);
}

int rt_ButtonPress(int b, int x, int y, t_rt_data *rt)
{
	(void)rt;
	printf("rt_ButtonPress");
	printf("bottom == %d\n", b);
	printf("x == %d\n", x);
	printf("y == %d\n", y);

	return (0);
}

int rt_ButtonRelease(int b, int x, int y, t_rt_data *rt)
{
	(void)rt;
	printf("rt_ButtonRelease");
	printf("bottom == %d\n", b);
	printf("x == %d\n", x);
	printf("y == %d\n", y);

	return (0);
}

int rt_MotionNotify(int x, int y, t_rt_data *rt)
{
	(void)rt;
	printf("rt_MotionNotify");
	printf("x == %d\n", x);
	printf("y == %d\n", y);

	return (0);
}

int rt_EnterNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_EnterNotify");

	return (0);
}

int rt_LeaveNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_LeaveNotify");

	return (0);
}

int rt_FocusIn(t_rt_data *rt)
{
	(void)rt;
	printf("rt_FocusIn");

	return (0);
}

int rt_FocusOut(t_rt_data *rt)
{
	(void)rt;
	printf("rt_FocusOut");

	return (0);
}

int rt_KeymapNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_KeymapNotify");

	return (0);
}

int rt_Expose(t_rt_data *rt)
{
	(void)rt;
	printf("rt_Expose");

	return (0);
}

int rt_GraphicsExpose(t_rt_data *rt)
{
	(void)rt;
	printf("rt_GraphicsExpose");

	return (0);
}

int rt_NoExpose(t_rt_data *rt)
{
	(void)rt;
	printf("rt_NoExpose");

	return (0);
}

int rt_VisibilityNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_VisibilityNotif");

	return (0);
}

int rt_CreateNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_CreateNotify");

	return (0);
}

int rt_DestroyNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_DestroyNotify");

	return (0);
}

int rt_UnmapNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_UnmapNotify");

	return (0);
}

int rt_MapNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_MapNotify");

	return (0);
}

int rt_MapRequest(t_rt_data *rt)
{
	(void)rt;
	printf("rt_MapRequest");

	return (0);
}

int rt_ReparentNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_ReparentNotify");

	return (0);
}

int rt_ConfigureNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_ConfigureNotify");

	return (0);
}

int rt_ConfigureRequest(t_rt_data *rt)
{
	(void)rt;
	printf("rt_ConfigureReques");

	return (0);
}

int rt_GravityNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_GravityNotify");

	return (0);
}

int rt_ResizeRequest(t_rt_data *rt)
{
	(void)rt;
	printf("rt_ResizeRequest");

	return (0);
}

int rt_CirculateNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_CirculateNotify");

	return (0);
}

int rt_CirculateRequest(t_rt_data *rt)
{
	(void)rt;
	printf("rt_CirculateReques");

	return (0);
}

int rt_PropertyNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_PropertyNotify");

	return (0);
}

int rt_SelectionClear(t_rt_data *rt)
{
	(void)rt;
	printf("rt_SelectionClear");

	return (0);
}

int rt_SelectionRequest(t_rt_data *rt)
{
	(void)rt;
	printf("rt_SelectionReques");

	return (0);
}

int rt_SelectionNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_SelectionNotify");

	return (0);
}

int rt_ColormapNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_ColormapNotify");

	return (0);
}

int rt_ClientMessage(t_rt_data *rt)
{
	(void)rt;
	printf("rt_ClientMessage");

	return (0);
}

int rt_MappingNotify(t_rt_data *rt)
{
	(void)rt;
	printf("rt_MappingNotify");

	return (0);
}

int rt_LASTEvent(t_rt_data *rt)
{
	(void)rt;
	printf("rt_LASTEvent");

	return (0);
}

int rt_StructureNotifyMask(t_rt_data *rt)
{
	(void)rt;
	printf("rt_StructureNotifyMask");
	return (0);
}


void	rt_hooks(t_rt_data *rt)
{
	// mlx_do_key_autorepeaton(rt->mlx.mlx);
	// mlx_do_sync(rt->mlx.mlx);

	mlx_hook(rt->mlx.win, KeyRelease, INT32_MAX, rt_KeyRelease, rt);
	mlx_hook(rt->mlx.win, KeyPress, INT32_MAX, rt_KeyPress, rt);
	mlx_hook(rt->mlx.win, ButtonPress, INT32_MAX, rt_ButtonPress, rt);
	mlx_hook(rt->mlx.win, ButtonRelease, INT32_MAX, rt_ButtonRelease, rt);
	mlx_hook(rt->mlx.win, MotionNotify, INT32_MAX, rt_MotionNotify, rt);
	mlx_hook(rt->mlx.win, EnterNotify, INT32_MAX, rt_EnterNotify, rt);
	mlx_hook(rt->mlx.win, LeaveNotify, INT32_MAX, rt_LeaveNotify, rt);
	mlx_hook(rt->mlx.win, FocusIn, INT32_MAX, rt_FocusIn, rt);
	mlx_hook(rt->mlx.win, FocusOut, INT32_MAX, rt_FocusOut, rt);
	mlx_hook(rt->mlx.win, KeymapNotify, INT32_MAX, rt_KeymapNotify, rt);
	mlx_hook(rt->mlx.win, Expose	, INT32_MAX, rt_Expose	, rt);
	mlx_hook(rt->mlx.win, GraphicsExpose, INT32_MAX, rt_GraphicsExpose, rt);
	mlx_hook(rt->mlx.win, NoExpose, INT32_MAX, rt_NoExpose, rt);
	mlx_hook(rt->mlx.win, VisibilityNotify, INT32_MAX, rt_VisibilityNotify, rt);
	mlx_hook(rt->mlx.win, CreateNotify, INT32_MAX, rt_CreateNotify, rt);
	mlx_hook(rt->mlx.win, DestroyNotify, 0, rt_DestroyNotify, rt);
	mlx_hook(rt->mlx.win, UnmapNotify, INT32_MAX, rt_UnmapNotify, rt);
	mlx_hook(rt->mlx.win, MapNotify, INT32_MAX, rt_MapNotify, rt);
	mlx_hook(rt->mlx.win, MapRequest, INT32_MAX, rt_MapRequest, rt);
	mlx_hook(rt->mlx.win, ReparentNotify, INT32_MAX, rt_ReparentNotify, rt);
	mlx_hook(rt->mlx.win, ConfigureNotify, INT32_MAX, rt_ConfigureNotify, rt);
	mlx_hook(rt->mlx.win, ConfigureRequest, INT32_MAX, rt_ConfigureRequest, rt);
	mlx_hook(rt->mlx.win, GravityNotify, INT32_MAX, rt_GravityNotify, rt);
	mlx_hook(rt->mlx.win, ResizeRequest, INT32_MAX, rt_ResizeRequest, rt);
	mlx_hook(rt->mlx.win, CirculateNotify, INT32_MAX, rt_CirculateNotify, rt);
	mlx_hook(rt->mlx.win, CirculateRequest, INT32_MAX, rt_CirculateRequest, rt);
	mlx_hook(rt->mlx.win, PropertyNotify, INT32_MAX, rt_PropertyNotify, rt);
	mlx_hook(rt->mlx.win, SelectionClear, INT32_MAX, rt_SelectionClear, rt);
	mlx_hook(rt->mlx.win, SelectionRequest, INT32_MAX, rt_SelectionRequest, rt);
	mlx_hook(rt->mlx.win, SelectionNotify, INT32_MAX, rt_SelectionNotify, rt);
	// mlx_hook(rt->mlx.win, ColormapNotify, StructureNotifyMask, rt_ColormapNotify, rt);
	// mlx_hook(rt->mlx.win, ClientMessage, INT32_MAX, rt_ClientMessage, rt);
	// mlx_hook(rt->mlx.win, MappingNotify, INT32_MAX, rt_MappingNotify, rt);
	// mlx_hook(rt->mlx.win, LASTEvent, INT32_MAX, rt_LASTEvent, rt);
	// mlx_hook(rt->mlx.win, StructureNotifyMask, INT32_MAX, rt_StructureNotifyMask, rt);

	// mlx_loop_hook(rt->mlx.mlx, draw_loop, rt);
}

void	rt_init(t_rt_data *rt, const char *file)
{
	rt_import(rt, file);
	rt_mlx(rt);
	rt_hooks(rt);
	// mlx_loop(rt->mlx.mlx);

	(void)file;
}

void	rt_mlx(t_rt_data *rt)
{
	int	x;
	int	y;

	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		rt_put_error_exit("mlx_init() fatal.");
	mlx_get_screen_size(rt->mlx.mlx, &x, &y);
	// 指定されたFOVと実行環境のディスプレイを比較して、実行環境のディスプレイが小さければ、その大きさで描画する。ということは、、、
	printf("width == %d height == %d\n", x, y);
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, 1440, 900, "miniRT");
	if (!rt->mlx.win)
		rt_put_error_exit("mlx_new_window() fatal.");
	// image 作成
	// image のアドレス取得
}

void	rt_import(t_rt_data *rt, const char *file)
{
	int		fd;
	char	*line;

	(void)rt;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		rt_perror_exit(NULL);
	line = get_next_line(fd);
	printf("%s\n", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		printf("%s\n", line);
	}
}

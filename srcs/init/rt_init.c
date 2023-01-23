/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/23 13:21:44 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "rt_define.h"
#include "rt_init_utils.h"
#include "rt_put_error.h"
#include "rt_structs.h"
#include "rt_vector.h"
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h> // for debug

static void	rt_mlx_init(t_rt_data *rt);
static void	rt_import_rt_file(t_rt_data *rt, const char *file);
void	rt_hooks(t_rt_data *rt);                         // in rt_init_hook.c
void	rt_fill_struct(t_rt_data *rt, const char *line);
			// in rt_init_fill_struct.c

void	rt_init(t_rt_data *rt, const char *file)
{
	rt_mlx_init(rt);
	rt_import_rt_file(rt, file);
	rt_hooks(rt);
	rt->scene.material.amb_fact = rt_rgb_vec_constructor(0.50f, 0.50f, 0.50f);
	rt->scene.material.spec_fact = rt_rgb_vec_constructor(0.30f, 0.30f, 0.30f);
	rt->scene.material.shininess = 8.0f;
	printf("rt->scene.material.amb_fact r[%f] g[%f] b[%f]\n",
			rt->scene.material.amb_fact.r,
			rt->scene.material.amb_fact.g,
			rt->scene.material.amb_fact.b);
	printf("rt->scene.material.spec_fact r[%f] g[%f] b[%f]\n",
			rt->scene.material.spec_fact.r,
			rt->scene.material.spec_fact.g,
			rt->scene.material.spec_fact.b);
	printf("rt->scene.material.shininess [%f]\n", rt->scene.material.shininess);
}

static void	rt_mlx_init(t_rt_data *rt)
{
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		rt_put_error_exit("mlx_init() failure\n");
	mlx_get_screen_size(rt->mlx.mlx, &rt->scene.scr_width,
			&rt->scene.scr_height);
	rt->scene.scr_width = rt->scene.scr_width * 2 / 3;
	rt->scene.scr_height = rt->scene.scr_height * 2 / 3;
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, rt->scene.scr_width,
			rt->scene.scr_height, "Bravo! Bravo!! Bravo!!!!!");
	rt->mlx.image.width = rt->scene.scr_width;
	rt->mlx.image.height = rt->scene.scr_height;
	if (!rt->mlx.win)
		rt_put_error_exit("mlx_new_window() failure");
	rt->mlx.image.img = mlx_new_image(rt->mlx.mlx, rt->mlx.image.width,
			rt->mlx.image.height);
	if (!rt->mlx.image.img)
		rt_put_error_exit("mlx_new_window() failure");
	rt->mlx.image.addr = mlx_get_data_addr(rt->mlx.image.img,
											&rt->mlx.image.bits_per_pixel,
											&rt->mlx.image.line_length,
											&rt->mlx.image.endian);
	if (!rt->mlx.image.addr)
		rt_put_error_exit("mlx_new_window() failure");
}

static void	rt_import_rt_file(t_rt_data *rt, const char *file)
{
	char	*line;
	int		fd;

	rt->scene.amb_color = rt_rgb_vec_constructor(-1, -1, -1);
	rt->scene.cam.scr_dist = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		rt_perror_exit("open() failure");
	line = get_next_line(fd);
	while (line)
	{
		printf("\e[32m");
		fflush(stdout);
		printf("\n%s", line);
		printf("\e[m");
		fflush(stdout);
		rt_fill_struct(rt, line);
		free(line);
		line = get_next_line(fd);
	}
	if (rt_check_camera_or_lite_in_sphere(rt))
		rt_put_rt_file_format_error_exit("The camera or lite is inside the sphere");
	if (rt->scene.amb_color.r == -1)
		rt_put_rt_file_format_error_exit("No ambient light");
	if (rt->scene.cam.scr_dist == -1)
		rt_put_rt_file_format_error_exit("No camera");
	if (rt->scene.pls_s == NULL)
		rt_put_rt_file_format_error_exit("No lites");
	if (close(fd) < 0)
		rt_perror_exit("close() failure");
}

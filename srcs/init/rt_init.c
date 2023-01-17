/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 16:11:17 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "rt_define.h"
#include "rt_put_error.h"
#include "rt_strucs.h"
#include "rt_vector.h"
#include "rt_init_utils.h"
#include <fcntl.h>
#include <limits.h>
#include <math.h>

#include <stdio.h> // for debug

static void	rt_mlx_init(t_rt_data *rt);
static void	rt_import_rt_file(t_rt_data *rt, const char *file);
void	rt_hooks(t_rt_data *rt); // in rt_init_hook.c
void	rt_fill_struct(t_rt_data *rt, const char *line); // in rt_init_fill_struct.c

void	rt_init(t_rt_data *rt, const char *file)
{
	rt_mlx_init(rt);
	rt_import_rt_file(rt, file);
	rt_hooks(rt);
	mlx_loop(rt->mlx.mlx);
	MATERIAL_AMBIENTFACTOR = rt_rgb_vec_constructor(1.00f, 1.00f, 1.00f);
	MATERIAL_DIFFUSEFACTOR = rt_rgb_vec_constructor(0.69f, 0.69f, 0.69f);
	MATERIAL_SPECULARFACTOR = rt_rgb_vec_constructor(0.30f, 0.30f, 0.30f);
	MATERIAL_SHININESS = 8.0f;
	printf("MATERIAL_AMBIENTFACTOR r[%f] g[%f] b[%f]\n",
			MATERIAL_AMBIENTFACTOR.r,
			MATERIAL_AMBIENTFACTOR.g,
			MATERIAL_AMBIENTFACTOR.b);
	printf("MATERIAL_DIFFUSEFACTOR r[%f] g[%f] b[%f]\n",
			MATERIAL_DIFFUSEFACTOR.r,
			MATERIAL_DIFFUSEFACTOR.g,
			MATERIAL_DIFFUSEFACTOR.b);
	printf("MATERIAL_SPECULARFACTOR r[%f] g[%f] b[%f]\n",
			MATERIAL_SPECULARFACTOR.r,
			MATERIAL_SPECULARFACTOR.g,
			MATERIAL_SPECULARFACTOR.b);
	printf("MATERIAL_SHININESS [%f]\n", MATERIAL_SHININESS);
}

static void	rt_mlx_init(t_rt_data *rt)
{
	rt->mlx.mlx = mlx_init();
	if (!rt->mlx.mlx)
		rt_put_error_exit("mlx_init() fatal.\n");
	mlx_get_screen_size(rt->mlx.mlx, &rt->scene.screean_width,
			&rt->scene.screean_height);
	rt->scene.screean_width /= 2;
	rt->scene.screean_height /= 2;
	rt->mlx.win = mlx_new_window(rt->mlx.mlx, rt->scene.screean_width,
			rt->scene.screean_height, "Bravo! Bravo!! Bravo!!!!!");
	rt->mlx.image.width = rt->scene.screean_width;
	rt->mlx.image.height = rt->scene.screean_height;
	if (!rt->mlx.win)
		rt_put_error_exit("mlx_new_window() fatal.\n");
	rt->mlx.image.img = mlx_new_image(rt->mlx.mlx, rt->mlx.image.width,
			rt->mlx.image.height);
	if (!rt->mlx.image.img)
		rt_put_error_exit("mlx_new_window() fatal.\n");
	rt->mlx.image.addr = mlx_get_data_addr(rt->mlx.image.img,
											&rt->mlx.image.bits_per_pixel,
											&rt->mlx.image.line_length,
											&rt->mlx.image.endian);
	if (!rt->mlx.image.addr)
		rt_put_error_exit("mlx_new_window() fatal.\n");
}

static void	rt_import_rt_file(t_rt_data *rt, const char *file)
{
	char	*line;
	int		fd;

	rt->scene.ambient_color = rt_rgb_vec_constructor(-1, -1, -1);
	rt->scene.camara.screen_distance = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		rt_perror_exit(NULL);
	line = get_next_line(fd);
	while (line)
	{
		printf("\n%s", line);
		rt_fill_struct(rt, line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) < 0)
		rt_perror_exit(NULL);
}

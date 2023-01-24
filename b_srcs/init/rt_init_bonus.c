/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:53:32 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/24 10:38:52 by nfukuma          ###   ########.fr       */
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
void		rt_hooks(t_rt_data *rt);
void		rt_fill_struct(t_rt_data *rt, const char *line);

void	rt_init(t_rt_data *rt, const char *file)
{
	rt_mlx_init(rt);
	rt_import_rt_file(rt, file);
	rt_hooks(rt);
	rt->scene.material.amb_fact = rt_rgb_vec_constructor(0.50f, 0.50f, 0.50f);
	rt->scene.material.spec_fact = rt_rgb_vec_constructor(0.30f, 0.30f, 0.30f);
	rt->scene.material.shininess = 8.0f;
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
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line != '\n')
			rt_fill_struct(rt, line);
		free(line);
	}
	if (rt_check_camera_or_lite_in_sphere(rt))
		rt_put_rt_file_format_error_exit(ER_CAM_IN_SP);
	if (rt->scene.amb_color.r == -1 || rt->scene.cam.scr_dist == -1
		|| rt->scene.pls_s == NULL)
		rt_put_rt_file_format_error_exit(ER_NO_AMB_CAM_P);
	if (close(fd) < 0)
		rt_perror_exit("close() failure");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strucs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:54:16 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 00:53:41 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCS_H
# define RT_STRUCS_H

enum							vector
{
	X,
	Y,
	Z,
};

enum							color
{
	R,
	G,
	B,
};

enum							shapes
{
	plane,
	sphere,
	cylinder,
	cone,
};

typedef struct s_3d_vec
{
	double						x;
	double						y;
	double						z;
}								t_3d_vec;

typedef struct s_rgb_vec
{
	double						r;
	double						g;
	double						b;
}								t_rgb_vec;
typedef struct s_material
{
	t_rgb_vec					ambientFactor;
	t_rgb_vec					diffuseFactor;
	t_rgb_vec					specularFactor;
	double						shininess;
}								t_material;

typedef struct s_plane
{
	t_3d_vec					position;
	t_3d_vec					unit_normal_vec;
	t_material					material;
}								t_plane;
typedef struct s_sphere
{
	t_3d_vec					center_position;
	double						radius;
	t_material					material;
}								t_sphere;

typedef struct s_cylinder
{
	t_3d_vec					center_position;
	double						radius;
	double						height;
	t_material					material;
}								t_cylinder;

typedef struct s_cone
{
	t_3d_vec					center_position;
	double						radius;
	double						height;
	t_material					material;
}								t_cone;

typedef struct s_obj
{
	int							shape;
	t_plane						*plane;
	t_sphere					*sphere;
	t_cylinder					*cylinder;
	t_cone						*cone;
	void						*shape_ptr;
	struct s_obj				*next;
}								t_obj;

typedef struct s_point_lite_source
{
	t_3d_vec					position;
	t_3d_vec					unit_direction;
	t_3d_vec					lite_color;
	struct s_point_lite_source	*next;
}								t_point_lite_source;

typedef struct s_camera
{
	t_3d_vec					camera_position;
	t_3d_vec					unit_camera_direction;

	double						screen_distance;
	t_3d_vec					screen_center_position;

	t_3d_vec					unit_screen_direction_x_vec;
	t_3d_vec					unit_screen_direction_y_vec;
}								t_camera;
#define CAMERA_POSITION rt->scene.camara.camera_position
#define UNIT_CAMERA_DIRECTION rt->scene.camara.unit_camera_direction
#define SCREEN_DISTANCE rt->scene.camara.screen_distance
#define SCREEN_CENTER_POSITION rt->scene.camara.screen_center_position
#define UNIT_SCREEN_DIRECTION_X_VEC rt->scene.camara.unit_screen_direction_x_vec
#define UNIT_SCREEN_DIRECTION_Y_VEC rt->scene.camara.unit_screen_direction_y_vec

typedef struct s_scene
{
	int							screean_width; // default mlx_getdispley_sizeのwidthの半分
	int							screean_height; // default mlx_getdispley_sizeのheightの半分
	t_camera					camara;
	t_point_lite_source			*pls_s;
	t_obj						*objs;
	t_rgb_vec					ambient_color;
}								t_scene;


typedef struct s_img
{
	void						*img;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
	int							width;
	int							height;
}								t_img;

typedef struct s_mlx
{
	void						*mlx;
	void						*win;
	t_img						image;
}								t_mlx;

typedef struct s_rt_data
{
	t_mlx						mlx;
	t_scene						scene;
}								t_rt_data;

#endif

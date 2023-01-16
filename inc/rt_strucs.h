/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strucs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:54:16 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/16 12:49:31 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCS_H
# define RT_STRUCS_H

enum					vector
{
	X,
	Y,
	Z,
};

enum					color
{
	R,
	G,
	B,
};

enum					shapes
{
	plane,
	sphere,
	cylinder,
	cone,
};

typedef struct s_material
{
	double				ambientFactor[3];
	double				diffuseFactor[3];
	double				specularFactor[3];
	double				shininess;
}						t_material;

typedef struct s_plane
{
	double				position[3];
	double				unit_normal_vec[3];
	t_material			material;
}						t_plane;
typedef struct s_sphere
{
	double				center_position[3];
	double				radius;
	t_material			material;
}						t_sphere;

typedef struct s_cylinder
{
	double				center_position[3];
	double				radius;
	double				height;
	t_material			material;
}						t_cylinder;

typedef struct s_cone
{
	double				center_position[3];
	double				radius;
	double				height;
	t_material			material;
}						t_cone;

typedef struct s_obj
{
	int					shape;
	t_plane				*plane;
	t_sphere			*sphere;
	t_cylinder			*cylinder;
	t_cone				*cone;
	void				*shape_ptr;
	t_obj				*next;
}						t_obj;

typedef struct s_point_lite_source
{
	double				position[3];
	double				unit_direction[3];
	double				lite_color[3];
	t_point_lite_source	*next;
}						t_point_lite_source;

typedef struct s_camera
{
	double				camara_position[3];
	double				unit_camera_direction[3];

	double				screen_distance;
	double				screen_center_position[3];

	double				unit_screen_direction_x_vec[3];
	double				unit_screen_direction_y_vec[3];
}						t_camera;
typedef struct s_scene
{
	int					screean_width;
	int					screean_height;
	t_camera			camara;
	t_point_lite_source	*pls_s;
	t_obj				*objs;
	double				ambient_color[3];
}						t_scene;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_img				image;
}						t_mlx;

typedef struct s_rt_data
{
	t_mlx				mlx;
	t_scene				scene;
}						t_rt_data;

#endif

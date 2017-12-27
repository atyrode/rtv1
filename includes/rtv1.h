/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 20:01:46 by atyrode           #+#    #+#             */
/*   Updated: 2017/12/09 22:03:48 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "./../libft/includes/libft.h"
# include "./../minilibx_macos/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <time.h>

# define W_WIDTH 896
# define W_HEIGHT 800
# define FOV 90
# define SQR(x) x * x

typedef struct 				s_sph
{
	int 		sphere_x;
	int 		sphere_y;
	int 		sphere_z;
	int 		sphere_radius;
	int 		sphere_color;
}											t_sph;

typedef struct				s_env
{
	int			s_x;
	int			s_y;
	int 		w_x;
	int 		w_y;
	int 		w_z;
	int 		ray_x;
	int 		ray_y;
	int 		ray_z;
	int 		camera_x;
	int 		camera_y;
	int 		camera_z;
	int 		amplitude;
	int 		dist_to_plane;
	int 		constant;
	int 		n_sphere;
	int 		n_square;
	int			n_cone;
	int 		n_plane;
	int			color;
}						      	  t_env;

typedef struct				s_img
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}						       	  t_img;

typedef struct 				s_shapes
{
	t_sph 	*sph;
}											t_shapes;

typedef struct			 	s_mlx
{
	int			*mlx;
	int			*win;
  int     keycode;
  int     button;
	t_img  	*img;
	t_env		*env;
}						         t_mlx;

void	 	  *new_image(t_mlx *mlx);
void	  	*delete_image(t_mlx *mlx);
void	   	image_set_pixel(t_mlx *mlx);
void	   	redraw(t_mlx *mlx, t_shapes *shapes);
t_mlx		 	*mlx_free(t_mlx *mlx);
t_shapes	*parsing(char *filename, t_mlx *mlx);
void		  rtv1(t_mlx *mlx, t_shapes *shapes);
t_mlx			*initialize(void);
void			hooks(t_mlx *mlx);
int 			check_ray(t_mlx *mlx, t_shapes *shapes);

#endif

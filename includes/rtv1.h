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
# define FOV 60
# define SQR(x) x * x
#ifdef DEBUG
#	define PRINTD printf
#	define RED   "\x1B[31m"
#	define GRN   "\x1B[32m"
#	define YEL   "\x1B[33m"
#	define BLU   "\x1B[34m"
#	define MAG   "\x1B[35m"
#	define CYN   "\x1B[36m"
#	define WHT   "\x1B[37m"
#	define RESET "\x1B[0m"
# define SEPUP "\n\n╔═════════════════════════════════╗\n"
# define X_Y "║SCREEN [X = "MAG"%-3i"RESET" | Y = "MAG"%-3i"RESET"] COORDS║\n", mlx->env->s_x, mlx->env->s_y
# define SEPDO "╚═════════════════════════════════╝\n"
# define CONST "constant = "RED"%f"RESET" \n", mlx->env->constant
# define W_XYZ "wrld_x = "BLU"%.5f"RESET" | wrld_y = "BLU"%.5f"RESET" | wrld_z = "BLU"%.5f"RESET" \n", mlx->env->w_x, mlx->env->w_y, mlx->env->w_z
# define SPH "sph[x] = " GRN "%.5f" RESET " | sph[y] = " GRN "%.5f" RESET " | sph[z] = " GRN "%.5f" RESET " (sph[r] = " GRN "%.5f" RESET ") \n", shapes->sph->sphere_x, shapes->sph->sphere_y, shapes->sph->sphere_z, shapes->sph->sphere_radius
# define RAY "ray[x] = " GRN "%.5f" RESET " | ray[y] = " GRN "%.5f" RESET " | ray[z] = " GRN "%.5f" RESET " \n", mlx->env->ray_x, mlx->env->ray_y, mlx->env->ray_z
# define B "b = " YEL "%f" RESET "\n", -(dot_product(sphere, ray, 3))
# define DET "det = %f - (%f) + %f = " YEL "%f\n" RESET, b * b, dot_product(sphere, sphere, 3), shapes->sph->sphere_radius * shapes->sph->sphere_radius, det
# define SQRTDET "√det = "YEL"%f"RESET" \n", sqrt(det)
# define T1 "t1 = (b - det) = ["CYN"%f"RESET"]\n", b - det
# define SUM "sum (%f) += tab1[%i] (%f) * tab2[%i] (%f)\n", sum, i, tab1[i], i, tab2[i]
# define SUM_F "sum = "RED"%f"RESET"\n", sum
#else
#	define PRINTD(format, args...) ((void)0)
#endif

typedef struct 				s_sph
{
	float 		sphere_x;
	float 		sphere_y;
	float 		sphere_z;
	float 		sphere_radius;
	int 		sphere_color;
}											t_sph;

typedef struct				s_env
{
	int			s_x;
	int			s_y;
	float 	w_x;
	float 	w_y;
	float 	w_z;
	float 	ray_x;
	float 	ray_y;
	float 	ray_z;
	float 	camera_x;
	float 	camera_y;
	float 	camera_z;
	float		amplitude;
	float 	dist_to_plane;
	float 	constant;
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
int				parsing(char *filename, t_mlx *mlx, t_shapes *shapes);
void		  rtv1(t_mlx *mlx, t_shapes *shapes);
t_mlx			*initialize(void);
t_shapes	*initialize_shapes(void);
void			hooks(t_mlx *mlx);
float 		check_ray(t_mlx *mlx, t_shapes *shapes);

#endif

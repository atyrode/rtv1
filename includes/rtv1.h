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

/* COLORS */

#ifdef DEBUG

#	define RED   "\x1B[31m"
#	define GRN   "\x1B[32m"
#	define YEL   "\x1B[33m"
#	define BLU   "\x1B[34m"
#	define MAG   "\x1B[35m"
#	define CYN   "\x1B[36m"
#	define WHT   "\x1B[37m"
#	define RESET "\x1B[0m"

#endif

/* GENERAL */
#if defined(DEBUG) && defined(GENERAL)

# 	define PRINTD printf
# define SEPUP "\n\n╔═════════════════════════════════╗\n"
# define X_Y "║SCREEN [X = "MAG"%-3i"RESET" | Y = "MAG"%-3i"RESET"] COORDS║\n", mlx->env->screen_x, mlx->env->screen_y
# define SEPDO "╚═════════════════════════════════╝\n"
# define CONST "constant = "RED"%f"RESET" \n", mlx->env->constant
# define W_XYZ "wrld_x = "BLU"%.5f"RESET" | wrld_y = "BLU"%.5f"RESET" | wrld_z = "BLU"%.5f"RESET" \n", mlx->env->viewplane[1], mlx->env->viewplane[2], mlx->env->viewplane[3]
# define SPH "sph[x] = " GRN "%.5f" RESET " | sph[y] = " GRN "%.5f" RESET " | sph[z] = " GRN "%.5f" RESET " (sph[r] = " GRN "%.5f" RESET ") \n", shapes->sph->sphere[1], shapes->sph->sphere[2], shapes->sph->sphere[3], shapes->sph->sphere_radius
# define RAY "ray[x] = " GRN "%.5f" RESET " | ray[y] = " GRN "%.5f" RESET " | ray[z] = " GRN "%.5f" RESET " \n", mlx->env->ray[1], mlx->env->ray[2], mlx->env->ray[3]
# define A "a = (%f) + (%f) + (%f) = " YEL "%f" RESET "\n", SQR(mlx->env->ray[1]), SQR(mlx->env->ray[2]), SQR(mlx->env->ray[3]), a
# define B "b = 2 * (%f * -(%f) + %f * -(%f) + %f * -(%f)) = "YEL"%f"RESET"\n", mlx->env->ray[1], shapes->sph->sphere[1], mlx->env->ray[1], shapes->sph->sphere[2], mlx->env->ray[1], shapes->sph->sphere[3], b
# define C "c = (%f) + (%f) + (%f) + (%f) = "YEL"%f"RESET"\n", SQR(shapes->sph->sphere[1]), SQR(shapes->sph->sphere[2]), SQR(shapes->sph->sphere[3]), SQR(shapes->sph->sphere_radius), c
# define SUM "sum (%f) += tab1[%i] (%f) * tab2[%i] (%f)\n", sum, i, tab1[i], i, tab2[i]
# define SUM_F "sum = "RED"%f"RESET"\n", sum

#else
#	define PRINTD(format, args...) ((void)0)
#endif

/*SOLUTIONS*/
#if defined(DEBUG) && defined(SOLUTION)

#	define PRINTS printf
# define ZERO "no solution\n"
# define ONE "["RED"one"RESET"] solution = ["CYN"%f"RESET"]\n", det
# define TWO "["YEL"two"RESET"] solutions : t1 = ["CYN"%f"RESET"] | t2 = ["CYN"%f"RESET"]\n", t1, t2

#else
#	define PRINTS(format, args...) ((void)0)
#endif

/* STRUCTURES */

typedef struct 		s_sph
{
	double 		sphere[4];
	double 		sphere_radius;
	int 		sphere_color;
}					t_sph;

typedef struct		s_env
{
	int			screen_x;
	int			screen_y;
	double 		viewplane[4];
	double 		viewplane_dist;
	double 		ray[4];
	double 		camera[4];
	double		camera_fov;
	double		constant;
	double		amplitude;
	int			color;
}					t_env;

typedef struct		s_img
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}					t_img;

typedef struct 		s_shapes
{
	int 		n_sphere;
	int 		n_square;
	int			n_cone;
	int 		n_plane;
	t_sph 		*sph;
}					t_shapes;

typedef struct		s_mlx
{
	int			*mlx;
	int			*win;
  	int    		keycode;
  	int     	button;
	t_img  		*img;
	t_env		*env;
}					t_mlx;

/* PROTOTYPES */

void	 	*new_image(t_mlx *mlx);
void	  	*delete_image(t_mlx *mlx);
void	   	image_set_pixel(t_mlx *mlx);
void	   	redraw(t_mlx *mlx, t_shapes *shapes);
t_mlx		*mlx_free(t_mlx *mlx);
int			parsing(char *filename, t_mlx *mlx, t_shapes *shapes);
void		rtv1(t_mlx *mlx, t_shapes *shapes);
t_mlx		*initialize(void);
t_shapes	*initialize_shapes(void);
void		hooks(t_mlx *mlx);
double 		check_ray(t_mlx *mlx, t_shapes *shapes);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:41:24 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/13 19:54:02 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/rtv1.h"

void rtvinit(t_mlx *mlx)
{
	mlx->env->s_x = -1;
	mlx->env->s_y = -1;
}

int 	check_ray(t_mlx *mlx, t_shapes *shapes)
{
	if (mlx && shapes)
		return (1);
	else
		return (0);
}

void	rtv1(t_mlx *mlx, t_shapes *shapes)
{
	int tmp;
	rtvinit(mlx);
	while (++mlx->env->s_x < W_WIDTH)
	{
		while (++mlx->env->s_y < W_HEIGHT)
		{
			//determine real-world pixel coordinates
			mlx->env->dist_to_plane = 100;
			mlx->env->constant = W_WIDTH / (mlx->env->dist_to_plane * tan(FOV));
			mlx->env->w_x = mlx->env->dist_to_plane;
			mlx->env->w_y = (mlx->env->s_x - W_WIDTH / 2) / mlx->env->constant;
			mlx->env->w_z = (mlx->env->s_y - W_HEIGHT / 2) / mlx->env->constant;

			//determine the ray direction vector
			mlx->env->ray_x = mlx->env->w_x - mlx->env->camera_x;
			mlx->env->ray_x = mlx->env->w_y - mlx->env->camera_y;
			mlx->env->ray_x = mlx->env->w_z - mlx->env->camera_z;
			mlx->env->amplitude = 1 / sqrt(SQR(mlx->env->ray_x) +
																			SQR(mlx->env->ray_y) +
																			SQR(mlx->env->ray_z));

			//get the amplitude of this vector and normalize it
			mlx->env->ray_x *= mlx->env->amplitude;
			mlx->env->ray_y *= mlx->env->amplitude;
			mlx->env->ray_z *= mlx->env->amplitude;

			//loop through all spheres in the scene
			tmp = mlx->env->n_sphere;
			while(tmp-- > 0)
			{
				if (check_ray(mlx, shapes))
				{
					mlx->env->color = shapes->sph->sphere_color;
					image_set_pixel(mlx);
				}
			}
		}
	}
	return ;
}

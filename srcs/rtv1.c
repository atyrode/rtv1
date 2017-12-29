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

void rtvinit(t_mlx *mlx, t_shapes *shapes)
{
	mlx->env->n_sphere = 1;
	shapes->sph->sphere_x = 2.;
	shapes->sph->sphere_y = 0.;
	shapes->sph->sphere_z = 0.;
	shapes->sph->sphere_radius = 1.;
	shapes->sph->sphere_color = 0xFEFEFE;
	mlx->env->camera_x = 0.;
	mlx->env->camera_y = 0.;
	mlx->env->camera_z = 0.;
}

float 	dot_product(float *tab1, float *tab2, int n)
{
		float 	sum;
		int 	i;

		sum = 0.;
		i = -1;
		while (++i < n)
		{
			sum += tab1[i] * tab2[i];
			//PRINTD(SUM);
		}
		//PRINTD(SUM_F);
		return (sum);
}

// Ray-sphere intersection.
// px,py,pz=(ray origin position - sphere position),
float 	check_ray(t_mlx *mlx, t_shapes *shapes)
{
		float det;
		float b;
		float sphere[3] = {shapes->sph->sphere_x,
											shapes->sph->sphere_y, shapes->sph->sphere_z};
		float ray[3] = {mlx->env->ray_x, mlx->env->ray_y, mlx->env->ray_z};

    //calculate the determinant
		PRINTD(SPH);
		PRINTD(RAY);
    b = -(dot_product(sphere, ray, 3));
		PRINTD(B);
		det = SQR(b) - (dot_product(sphere, sphere, 3)) + SQR(shapes->sph	->sphere_radius);
		PRINTD(DET);
    if (det < 0) //if it's less than 0, there's no intersection, return -1
        return (0);

    //calculate the two values for t
    det = sqrt(det);
		PRINTD(SQRTDET);
    //always return t1, as it'll always be the shortest distance
		//t1 = b - det;
		//t2 = b + det;
		PRINTD(T1);
    return (b - det);
}

void	rtv1(t_mlx *mlx, t_shapes *shapes)
{
	int tmp;
	rtvinit(mlx, shapes);
	mlx->env->s_x = -1;
	while (++mlx->env->s_x < W_WIDTH)
	{
		mlx->env->s_y = -1;
		while (++mlx->env->s_y < W_HEIGHT)
		{
			PRINTD(SEPUP);
			PRINTD(X_Y);
			PRINTD(SEPDO);
			//determine real-world pixel coordinates
			mlx->env->dist_to_plane = 100;
			mlx->env->constant = W_WIDTH / (mlx->env->dist_to_plane * tan(FOV));
			PRINTD(CONST);
			mlx->env->w_x = mlx->env->dist_to_plane;
			mlx->env->w_y = (mlx->env->s_x - W_WIDTH / 2) / mlx->env->constant;
			mlx->env->w_z = (mlx->env->s_y - W_HEIGHT / 2) / mlx->env->constant;
			PRINTD(W_XYZ);

			//determine the ray direction vector
			mlx->env->ray_x = mlx->env->w_x - mlx->env->camera_x;
			mlx->env->ray_y = mlx->env->w_y - mlx->env->camera_y;
			mlx->env->ray_z = mlx->env->w_z - mlx->env->camera_z;
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
			#ifdef DEBUG
				if (mlx->env->s_y == 100)
					break;
			}
			if (mlx->env->s_x == 100)
				break;
			#else
			}
			#endif
	}
	return ;
}

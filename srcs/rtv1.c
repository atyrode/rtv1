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
	shapes->sph->sphere_x = 1.;
	shapes->sph->sphere_y = 1.;
	shapes->sph->sphere_z = 1.;
	shapes->sph->sphere_radius = 2.;
	shapes->sph->sphere_color = 0xFEFEFE;
	mlx->env->camera_x = 0.;
	mlx->env->camera_y = 0.;
	mlx->env->camera_z = 0.;
}

int 	dot_product(int *sphere, int *ray, int n)
{
		int 	sum;
		int 	i;

		sum = 0;
		i = -1;
		while (++i < n)
		{
			sum += sphere[i] * ray[i];
		}
		//printf ("sum = %i\n", sum);
		return (sum);
}

// Ray-sphere intersection.
// px,py,pz=(ray origin position - sphere position),
int 	check_ray(t_mlx *mlx, t_shapes *shapes)
{
		float det;
		float b;
		int sphere[3] = {shapes->sph->sphere_x,
											shapes->sph->sphere_y, shapes->sph->sphere_z};
		int ray[3] = {mlx->env->ray_x, mlx->env->ray_y, mlx->env->ray_z};

    //calculate the determinant

		#ifdef DEBUG
		printf ("sphere[1] = %f | sphere[2] = %f | sphere[3] = %f\n",
		shapes->sph->sphere_x, shapes->sph->sphere_y, shapes->sph->sphere_z);
		printf ("ray[1] = %f | ray[2] = %f | ray[3] = %f\n",
		mlx->env->ray_x, mlx->env->ray_y, mlx->env->ray_z);
		#endif

    b = -(dot_product(sphere, ray, 3));

		#ifdef DEBUG
		printf ("b = -(%i) = %f\n", dot_product(sphere, ray, 3), b);
		#endif

		det = SQR(b) - (dot_product(ray, ray, 3)) + SQR(shapes->sph->sphere_radius);

		#ifdef DEBUG
		printf ("det = %f - (%i) + %f = %f\n", b * b, dot_product(ray, ray, 3),
		 shapes->sph->sphere_radius * shapes->sph->sphere_radius, det);
		#endif

		//printf ("b = %f \n", b);
		//printf ("det = %f \n", det);
    if (det < 0) //if it's less than 0, there's no intersection, return -1
        return (0);

    //calculate the two values for t
    det = sqrt(det);
    //t1 = b - det;
    //t2 = b + det;  //not really necessary -> longest distance!

    //always return t1, as it'll always be the shortest distance

		#ifdef DEBUG
		printf ("t1 = %f - %f = [%f]\n\n", b, det, b - det);
		#endif

    return (b - det);
}

void	rtv1(t_mlx *mlx, t_shapes *shapes)
{
	int tmp;
	rtvinit(mlx, shapes);
	mlx->env->s_x = -1;
	while (++mlx->env->s_x < W_WIDTH)
	{
		//printf ("s_x = %i\n", mlx->env->s_x);

		mlx->env->s_y = -1;
		while (++mlx->env->s_y < W_HEIGHT)
		{
			//if (mlx->env->s_y == 1)
				//printf ("s_y = %i\n", mlx->env->s_y);

			//determine real-world pixel coordinates
			mlx->env->dist_to_plane = 100;
			mlx->env->constant = W_WIDTH / (mlx->env->dist_to_plane * tan(FOV));
			mlx->env->w_x = mlx->env->dist_to_plane;
			mlx->env->w_y = (mlx->env->s_x - W_WIDTH / 2) / mlx->env->constant;
			mlx->env->w_z = (mlx->env->s_y - W_HEIGHT / 2) / mlx->env->constant;

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

					#ifdef DEBUG
					printf ("x = %i | y = %i\n", mlx->env->s_x, mlx->env->s_y);
					#endif
				}
				else
				exit (0);
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

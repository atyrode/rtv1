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

void 			rtvinit(t_mlx *mlx, t_shapes *shapes)
{
	shapes->n_sphere = 1;
	shapes->sph->sphere[1] = 200.;
	shapes->sph->sphere[2] = 0.;
	shapes->sph->sphere[3] = 0.;
	shapes->sph->sphere_radius = 1.;
	shapes->sph->sphere_color = 0xFEFEFE;
	mlx->env->camera[1] = 1.;
	mlx->env->camera[2] = 1.;
	mlx->env->camera[3] = 1.;
	mlx->env->camera_fov = 80;
	mlx->env->viewplane_dist = 100;
	mlx->env->constant = W_WIDTH /
			(mlx->env->viewplane_dist * tan(mlx->env->camera_fov));
}

double 			dot_product(double *tab1, double *tab2, int n)
{
		double 	sum;
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

double 			delta(t_mlx *mlx, t_shapes *shapes)
{
		double 	a;
		double	b;
		double 	c;
		double 	det;
		double 	t1;
		double 	t2;

		a = SQR(mlx->env->ray[1]) + SQR(mlx->env->ray[2])
									+ SQR(mlx->env->ray[3]);
		PRINTD(A);
		//simplification par dot product de a possible
		b = 2 * (mlx->env->ray[1] * -(shapes->sph->sphere[1]) +
							mlx->env->ray[2] * -(shapes->sph->sphere[2]) +
							mlx->env->ray[3] * -(shapes->sph->sphere[3]));
		PRINTD(B);
		//simplification par dot product de b possible
		c = SQR(shapes->sph->sphere[1]) + SQR(shapes->sph->sphere[2])
				+ SQR(shapes->sph->sphere[3]) + SQR(shapes->sph->sphere_radius);
		PRINTD(C);
		//simplification par dot product de c possible

		if ((det = SQR(b) - (4 * a * c)) < 0)
		{
			PRINTS(ZERO);
			return (0);
		}
		else if (det == 0)
		{
			PRINTS(ONE);
			return ((-(b)) / (2 * a));
		}
		else
		{
			t1 = (-(b) - sqrt(det)) / (2 * a);
			t2 = (-(b) + sqrt(det)) / (2 * a);
			PRINTS(TWO);
			if (t1 < t2)
				return (t1);
			else
				return (t2);
		}
		return (0);
}

// px,py,pz=(ray origin position - sphere position),
double			check_ray(t_mlx *mlx, t_shapes *shapes)
{
		double 	det;
		/*double 	b;
		double	t1;
		double	t2;

		//PRINTD(SPH);
		//PRINTD(RAY);

		b = -dot_product(mlx->env->ray, shapes->sph->sphere, 3);
		det = (SQR(b)) - dot_product(mlx->env->ray, mlx->env->ray, 3) +
											(SQR(shapes->sph->sphere_radius));

		PRINTS(ONE);
		if (det < 0)
		{
			PRINTS(ZERO);
			return (0);
		}

		det = sqrt(det);
		t1 = b - det;
		t2 = b + det;

		PRINTS(TWO);
		return (t1);*/

		//code tenté avec Olivier

		if ((det = delta(mlx, shapes)) == 0)
			return (0);
		else
    	return (det);

}

void			rtv1(t_mlx *mlx, t_shapes *shapes)
{
	int			tmp;

	rtvinit(mlx, shapes);
	mlx->env->screen_x = -1;
	while (++mlx->env->screen_x < W_WIDTH)
	{
		mlx->env->screen_y = -1;
		while (++mlx->env->screen_y < W_HEIGHT)
		{
			//PRINTD(SEPUP);
			//PRINTD(X_Y);
			//PRINTD(SEPDO);

			//x = [1] | y = [2] | z = [3]

			//determine real-world pixel coordinates
			mlx->env->viewplane[1] = mlx->env->viewplane_dist;
			mlx->env->viewplane[2] = (mlx->env->screen_x - W_WIDTH / 2) / mlx->env->constant;
			mlx->env->viewplane[3] = (mlx->env->screen_y - W_HEIGHT / 2) / mlx->env->constant;
			//PRINTD(W_XYZ);

			//determine the ray direction vector
			mlx->env->ray[1] = mlx->env->viewplane[1] - mlx->env->camera[1];
			mlx->env->ray[2] = mlx->env->viewplane[2] - mlx->env->camera[2];
			mlx->env->ray[3] = mlx->env->viewplane[3] - mlx->env->camera[3];
			mlx->env->amplitude = 1 / sqrt(SQR(mlx->env->ray[1]) +
											SQR(mlx->env->ray[2]) +
											SQR(mlx->env->ray[3]));

			//get the amplitude of this vector and normalize it
			mlx->env->ray[1] *= mlx->env->amplitude;
			mlx->env->ray[2] *= mlx->env->amplitude;
			mlx->env->ray[3] *= mlx->env->amplitude;

			//loop through all spheres in the scene*/
			tmp = shapes->n_sphere;
			while(tmp-- > 0)
			{
				if (check_ray(mlx, shapes))
				{
					mlx->env->color = shapes->sph->sphere_color;
					image_set_pixel(mlx);
				}
			}
			#ifdef LIMIT
				if (mlx->env->screen_y == 100)
					break;
			}
			if (mlx->env->screen_x == 100)
				break;
			#else
			}
			#endif
	}
	return ;
}

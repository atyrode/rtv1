/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:42:48 by atyrode           #+#    #+#             */
/*   Updated: 2017/12/09 22:03:33 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/rtv1.h"

void	image_set_pixel(t_mlx *mlx)
{
	if (mlx->env->x < 0 || mlx->env->x >= W_WIDTH
			|| mlx->env->y < 0 || mlx->env->y >= W_HEIGHT)
		return ;
	*(int *)(mlx->img->ptr + ((mlx->env->x + mlx->env->y * W_WIDTH)
																					* mlx->img->bpp)) = mlx->env->color;
}

void	*delete_image(t_mlx *mlx)
{
	if (mlx->img != NULL)
	{
		if (mlx->img->image != NULL)
			mlx_destroy_image(mlx->mlx, mlx->img->image);
		ft_memdel((void **)&mlx->img);
	}
	return (NULL);
}

void	*new_image(t_mlx *mlx)
{
	if ((mlx->img = ft_memalloc(sizeof(t_img))) == NULL)
		return (NULL);
	if ((mlx->img->image = mlx_new_image(mlx->mlx, W_WIDTH, W_HEIGHT))
			== NULL)
		return (delete_image(mlx));
	mlx->img->ptr = mlx_get_data_addr(mlx->img->image, &mlx->img->bpp,
			&mlx->img->stride, &mlx->img->endian);
	mlx->img->bpp /= 8;
	return (mlx->img);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:40:36 by atyrode           #+#    #+#             */
/*   Updated: 2017/12/09 22:09:15 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

void	redraw_raytracing(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	delete_image(mlx);
	new_image(mlx);
	raytracing(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->image, 0, 0);
	mlx_do_sync(mlx->mlx);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (!(argc == 2) || !(argv))
		return (-1);
	if ((mlx = initialize()) == NULL)
		return (-1);
	parsing("maps/map.wolf", mlx);
	hooks(mlx);
	rt_init(mlx);
	raytracing(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->image, 0, 0);
	mlx_loop(mlx->mlx);
	return (0);
}

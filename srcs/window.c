/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 19:23:07 by atyrode           #+#    #+#             */
/*   Updated: 2017/12/09 22:05:35 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/rtv1.h"

t_mlx		*mlx_free(t_mlx *mlx)
{
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img != NULL)
		delete_image(mlx);
	if (mlx->env != NULL)
		ft_memdel((void **)&mlx->env);
	ft_memdel((void **)&mlx);
	exit(-1);
}

t_mlx		*initialize(void)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL
			|| (mlx->win = mlx_new_window(mlx->mlx, W_WIDTH, W_HEIGHT,
					"RTv1")) == NULL
			|| (mlx->img = new_image(mlx)) == NULL
			|| (mlx->env = ft_memalloc(sizeof(t_env))) == NULL)
		return (mlx_free(mlx));
	return (mlx);
}

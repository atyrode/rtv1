/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:27:01 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/13 19:49:15 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/rtv1.h"

int			key_press(int keycode, t_mlx *mlx)
{
	mlx->keycode = keycode;
	if (mlx->keycode == 53)
		mlx_free(mlx);
	redraw(mlx, NULL);
	return (0);
}

int			hook_close(t_mlx *mlx)
{
	mlx_free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

void		hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 17, 1L << 0, hook_close, mlx);
}

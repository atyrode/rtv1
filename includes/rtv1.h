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

typedef struct			 s_env
{
	int			x;
	int			y;
	int			color;
}						         t_env;

typedef struct			 s_img
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}						         t_img;

typedef struct			 s_mlx
{
	int			*mlx;
	int			*win;
  int     keycode;
  int     button;
	t_img  	*img;
	t_env		*env;
}						         t_mlx;

void	   *new_image(t_mlx *mlx);
void	   *delete_image(t_mlx *mlx);
void	   image_set_pixel(t_mlx *mlx);
void	   redraw(t_mlx *mlx);
t_mlx		 *mlx_free(t_mlx *mlx);
int		   parsing(char *filename, t_mlx *mlx);
void	   rtv1(t_mlx *mlx);
t_mlx		 *initialize(void);
void		 hooks(t_mlx *mlx);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/13 17:43:46 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <mlx.h>

static int	ft_usage(void)
{
	ft_putendl("usage: ./fract_ol <fractal type>");
	ft_putendl("\tjulia");
	ft_putendl("\tmandelbrot");
	ft_putendl("\tpoop");
	return (1);
}

static t_mlx_data	*ft_init_mlx_data(char *title, int w, int h)
{
	t_mlx_data *mlx_data;
	mlx_data = (t_mlx_data*)malloc(sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, w, h, title);
	return (mlx_data);
}

static int			on_key_press(int key, void *param)
{
	if (key == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int			main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;

	if (argc == 2)
	{
		mlx_data = ft_init_mlx_data("fract_ol", 1280, 720);
	}
	else
		return (ft_usage());

	mlx_hook(mlx_data->win_ptr, 2, 0, on_key_press, (void*)mlx_data);
	//mlx_loop_hook(fdf_data->mlx_ptr, on_render, (void*)fdf_data);
	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}

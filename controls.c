/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:45:24 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/17 20:42:59 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

int			key_press(int key, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (key == KEY_1)
		mlx_data->fractal_type = FRAC_JULIA;
	if (key == KEY_2)
		mlx_data->fractal_type = FRAC_MANDELBROT;
	plot_fractal(mlx_data, WIN_W, WIN_H);
	return (0);
}

int mouse_move(int x, int y, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	if (x < 0 || x > WIN_W)
		x = x < 0 ? 0 : WIN_W;
	if (y < 0 || y > WIN_H)
		y = y < 0 ? 0 : WIN_H;
	mlx_data->mouse_x = x;
	mlx_data->mouse_y = y;
	plot_fractal(mlx_data, WIN_W, WIN_H);
	return (0);
}

int 	mouse_press(int button, int x, int y, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;

	if (button == 4)
		mlx_data->zoom += 0.01f;
	if (button == 5)
		mlx_data->zoom -= 0.01f;
	return (0);
}

int expose(void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	ft_putendl("expose");
	return (0);
}

int close(void *param)
{
	(void)param;
	exit(0);
}

void	setup_controls(t_mlx_data *mlx_data)
{
	mlx_hook(mlx_data->win_ptr, 2, (1L << 0), key_press, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 4, 0, mouse_press, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 6, 0, mouse_move, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 12, 0, expose, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 17, (1L << 17), close, (void*)mlx_data);
}

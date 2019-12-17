/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/17 17:59:37 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <mlx.h>

static int	ft_usage(void)
{
	ft_putendl("usage: ./fract_ol <fractal type>");
	ft_putendl("\t0: julia");
	ft_putendl("\t1: mandelbrot");
	ft_putendl("\t2: poop");
	return (1);
}

static t_mlx_data	*ft_init_mlx_data(char *title, int w, int h)
{
	t_mlx_data *mlx_data;
	mlx_data = (t_mlx_data*)malloc(sizeof(t_mlx_data));
	mlx_data->mlx_ptr = mlx_init();
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, w, h, title);
	mlx_data->frame_buffer = create_frame_buffer(mlx_data);
	mlx_data->zoom = 1.0;
	mlx_data->move_x = 0.0;
	mlx_data->move_y = 0.0;
	mlx_data->mouse_x = WIN_W;
	mlx_data->mouse_y = WIN_H;
	return (mlx_data);
}

static void plot_fractal(t_mlx_data *mlx_data, int width, int height)
{
	if (mlx_data->fractal_type == FRAC_JULIA)
		plot_julia(mlx_data, WIN_W, WIN_H);
	else if (mlx_data->fractal_type == FRAC_MANDELBROT)
		plot_mandelbrot(mlx_data, WIN_W, WIN_H);
}


int close(void *param)
{
	(void)param;
	exit(0);
}

static int			key_press(int key, void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	if (key == ESC)
		exit(EXIT_SUCCESS);
	else
		plot_mandelbrot(mlx_data, WIN_W, WIN_H);
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

static int	render(void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;

	return (0);
}

int expose(void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;
	ft_putendl("expose");
	return (0);
}


int			main(int argc, char const *argv[])
{
	t_mlx_data *mlx_data;

	if (argc == 2)
	{
		mlx_data = ft_init_mlx_data("fract_ol", WIN_W, WIN_H);
		mlx_data->fractal_type = ft_atoi(argv[1]);
	}
	else
		return (ft_usage());

	mlx_hook(mlx_data->win_ptr, 2, 0, key_press, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 4, 0, mouse_press, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 6, 0, mouse_move, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 12, 0, expose, (void*)mlx_data);
	mlx_hook(mlx_data->win_ptr, 17, 0, close, (void*)mlx_data);
	//mlx_loop_hook(mlx_data->mlx_ptr, render, (void*)mlx_data);
	plot_fractal(mlx_data, WIN_W, WIN_H);
	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}

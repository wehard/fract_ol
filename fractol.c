/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/17 20:46:31 by wkorande         ###   ########.fr       */
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
	mlx_data->zoom = 0.5;
	mlx_data->move_x = 0.0;
	mlx_data->move_y = 0.0;
	mlx_data->mouse_x = WIN_W;
	mlx_data->mouse_y = WIN_H;
	return (mlx_data);
}

void plot_fractal(t_mlx_data *mlx_data, int width, int height)
{
	if (mlx_data->fractal_type == FRAC_JULIA)
		plot_julia(mlx_data, WIN_W, WIN_H);
	else if (mlx_data->fractal_type == FRAC_MANDELBROT)
		plot_mandelbrot(mlx_data, WIN_W, WIN_H);
	else
		plot_julia(mlx_data, WIN_W, WIN_H);
}

static int	render(void *param)
{
	t_mlx_data *mlx_data;

	mlx_data = (t_mlx_data*)param;

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

	setup_controls(mlx_data);
	plot_fractal(mlx_data, WIN_W, WIN_H);
	mlx_loop(mlx_data->mlx_ptr);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/21 23:47:40 by wkorande         ###   ########.fr       */
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

static t_env	*init_env(char *title, int w, int h)
{
	int 	i;
	t_env	*env;

	env = (t_env*)malloc(sizeof(t_env));
	env->mlx = (t_mlx*)malloc(sizeof(t_mlx));
	env->mlx->mlx_ptr = mlx_init();
	env->mlx->win_ptr = mlx_new_window(env->mlx->mlx_ptr, w, h, title);
	env->width = w;
	env->height = h;
	env->thread_index = 0;
	//env->thread_data = (int*)malloc(sizeof(int*) * NUM_THREADS);
	//i = 0;
	//while (i < NUM_THREADS)
	//	env->thread_data[i++] = malloc(sizeof(int) * (w * (h / NUM_THREADS)));
	env->frame_buffer = create_frame_buffer(env);
	env->zoom = 0.5;
	env->move_x = 0.0;
	env->move_y = 0.0;
	env->mouse_x = WIN_W;
	env->mouse_y = WIN_H;
	return (env);
}

static void			del_env(t_env *env)
{
	mlx_destroy_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
	mlx_destroy_image(env->mlx->mlx_ptr, env->frame_buffer->img);
	free(env->mlx);
	free(env->frame_buffer);
	free(env);
	exit(EXIT_SUCCESS);
}

void plot_fractal(t_env *env, int width, int height)
{
	//clear_frame_buffer(env->frame_buffer);
	if (env->fractal_type == FRAC_JULIA)
		plot_julia(env, WIN_W, WIN_H);
	else if (env->fractal_type == FRAC_MANDELBROT)
		plot_mandelbrot(env, WIN_W, WIN_H);
	else
		plot_julia(env, WIN_W, WIN_H);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->frame_buffer->img, 0, 0);
}

static int	render(void *param)
{
	t_env *env;

	env = (t_env*)param;

	return (0);
}

int			main(int argc, char const *argv[])
{
	t_env *env;

	if (argc == 2)
	{
		env = init_env("fract_ol", WIN_W, WIN_H);
		env->fractal_type = ft_atoi(argv[1]);
	}
	else
		return (ft_usage());

	setup_controls(env);
	plot_fractal(env, WIN_W, WIN_H);
	mlx_loop(env->mlx->mlx_ptr);
	del_env(env);
	return (0);
}

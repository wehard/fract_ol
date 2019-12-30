/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 13:40:17 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <mlx.h>
#include "pthread.h"

static int	ft_usage(void)
{
	ft_putendl("usage: ./fract_ol <fractal type>");
	ft_putendl("\t0: julia");
	ft_putendl("\t1: mandelbrot");
	ft_putendl("\t2: burning ship");
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
	env->width = w/3*2;
	env->height = h;
	env->thread_index = 0;
	//env->thread_data = (int*)malloc(sizeof(int*) * NUM_THREADS);
	//i = 0;
	//while (i < NUM_THREADS)
	//	env->thread_data[i++] = malloc(sizeof(int) * (w * (h / NUM_THREADS)));
	env->fractal_img = create_mlx_image(env, env->width, env->height);
	env->zoom = 0.5;
	env->move_x = 0.0;
	env->move_y = 0.0;
	env->mouse_x = WIN_W;
	env->mouse_y = WIN_H;
	env->color_palette = 0;
	ui_init(env);
	return (env);
}

static void			del_env(t_env *env)
{
	mlx_destroy_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
	mlx_destroy_image(env->mlx->mlx_ptr, env->fractal_img->img);
	mlx_destroy_image(env->mlx->mlx_ptr, env->ui->img->img);
	free(env->mlx);
	free(env->fractal_img);
	free(env->ui->img);
	free(env->ui->buttons);
	free(env->ui);
	free(env);
	exit(EXIT_SUCCESS);
}

static t_fractal_func get_fractal_function(t_env *env)
{
	if (env->fractal_type == FRAC_JULIA)
		return (plot_julia);
	else if (env->fractal_type == FRAC_MANDELBROT)
		return (plot_mandelbrot);
	else if (env->fractal_type == FRAC_BURNING_SHIP)
		return (plot_burning_ship);
	else
		return (plot_julia);
}

void plot_fractal(t_env *env, int width, int height)
{
	pthread_t 	threads[NUM_THREADS];
	t_env		thread_env[NUM_THREADS];
	int i;

	i = 0;
	while (i < NUM_THREADS)
	{
		ft_memcpy((void*)&thread_env[i], (void*)env, sizeof(t_env));
		thread_env[i].thread_index = i;
		thread_env[i].thread_range_start = i * (height / NUM_THREADS);
		thread_env[i].thread_range_end = (i + 1) * (height / NUM_THREADS);
		pthread_create(&threads[i], NULL, get_fractal_function(env), &thread_env[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->fractal_img->img, 0, 0);
	draw_ui(env);
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

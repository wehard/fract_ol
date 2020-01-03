/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/03 13:55:04 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <mlx.h>
#include "pthread.h"

static int				ft_usage(void)
{
	ft_putendl("usage: ./fractol <fractal type>");
	ft_putendl("\t1: julia");
	ft_putendl("\t2: mandelbrot");
	ft_putendl("\t3: burning ship");
	return (1);
}

static t_fractal_func	get_fractal_function(t_env *env)
{
	if (env->fractal_type == FRAC_JULIA &&
		(env->fractal_name = FRAC_JULIA_STR))
		return (plot_julia);
	else if (env->fractal_type == FRAC_MANDELBROT &&
		(env->fractal_name = FRAC_MANDEL_STR))
		return (plot_mandelbrot);
	else if (env->fractal_type == FRAC_BURNING_SHIP &&
		(env->fractal_name = FRAC_BURNING_STR))
		return (plot_burning_ship);
	else
		return (plot_julia);
}

void					plot_fractal(t_env *env)
{
	pthread_t	threads[NUM_THREADS];
	t_env		thread_env[NUM_THREADS];
	int			i;
	int			num_threads;

	num_threads = NUM_THREADS == 0 ? 1 : NUM_THREADS;
	i = 0;
	while (i < num_threads)
	{
		ft_memcpy((void*)&thread_env[i], (void*)env, sizeof(t_env));
		thread_env[i].thread_index = i;
		thread_env[i].thread_range_start = i * (env->height / num_threads);
		thread_env[i].thread_range_end = (i + 1) * (env->height / num_threads);
		pthread_create(&threads[i], NULL,
			get_fractal_function(env), &thread_env[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->fractal_img->img, 0, 0);
	draw_ui(env);
}

int						main(int argc, char const *argv[])
{
	t_env	*env;
	int		arg;

	if (NUM_THREADS == 0)
	{
		ft_putendl("error: NUM_THREADS is 0. this will not work!");
		return (1);
	}
	if (argc == 2)
	{
		arg = ft_atoi(argv[1]);
		if (arg <= 0 || arg > 3)
			return (ft_usage());
		env = init_env("fract_ol", WIN_W, WIN_H);
		env->fractal_type = arg;
	}
	else
		return (ft_usage());
	setup_controls(env);
	plot_fractal(env);
	mlx_loop(env->mlx->mlx_ptr);
	del_env(env);
	return (0);
}

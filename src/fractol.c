/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:17:07 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 17:35:30 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <mlx.h>
#include "pthread.h"

static int				ft_usage(void)
{
	ft_putendl("usage: ./fract_ol <fractal type>");
	ft_putendl("\t1: julia");
	ft_putendl("\t2: mandelbrot");
	ft_putendl("\t3: burning ship");
	return (1);
}

static t_fractal_func	get_fractal_function(t_env *env)
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

void					plot_fractal(t_env *env, int width, int height)
{
	pthread_t	threads[NUM_THREADS];
	t_env		thread_env[NUM_THREADS];
	int			i;

	i = 0;
	while (i < NUM_THREADS)
	{
		ft_memcpy((void*)&thread_env[i], (void*)env, sizeof(t_env));
		thread_env[i].thread_index = i;
		thread_env[i].thread_range_start = i * (height / NUM_THREADS);
		thread_env[i].thread_range_end = (i + 1) * (height / NUM_THREADS);
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

	if (argc == 2)
	{
		if (!(arg = ft_atoi(argv[1])))
			return (ft_usage());
		env = init_env("fract_ol", WIN_W, WIN_H);
		env->fractal_type = arg;
	}
	else
		return (ft_usage());
	setup_controls(env);
	plot_fractal(env, WIN_W, WIN_H);
	mlx_loop(env->mlx->mlx_ptr);
	del_env(env);
	return (0);
}

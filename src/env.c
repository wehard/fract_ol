/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:30:56 by wkorande          #+#    #+#             */
/*   Updated: 2020/01/02 13:35:03 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include "mlx.h"

static void	panic(t_env *env)
{
	ft_putstr("panic: env failed! freeing everything!");
	if (env)
	{
		if (env->mlx)
		{
			if (env->mlx->mlx_ptr && env->mlx->win_ptr)
				mlx_destroy_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
			free(env->mlx);
		}
		if (env->fractal_img)
		{
			mlx_destroy_image(env->mlx->mlx_ptr, env->fractal_img->img);
			free(env->fractal_img);
		}
		if (env->ui && env->ui->img)
		{
			mlx_destroy_image(env->mlx->mlx_ptr, env->ui->img->img);
			free(env->ui->img);
			free(env->ui);
		}
		free(env);
	}
	exit(EXIT_FAILURE);
}

t_env		*init_env(char *title, int w, int h)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	if (!(env->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		panic(env);
	env->mlx->mlx_ptr = mlx_init();
	env->mlx->win_ptr = mlx_new_window(env->mlx->mlx_ptr, w, h, title);
	env->width = w / 3 * 2;
	env->height = h;
	env->iterations = MAX_ITER;
	env->thread_index = 0;
	env->fractal_img = create_mlx_image(env, env->width, env->height);
	env->zoom = 0.5;
	env->move_x = 0.0;
	env->move_y = 0.0;
	env->mouse_x = WIN_W;
	env->mouse_y = WIN_H;
	env->color_palette = 0;
	env->free_julia = 0;
	env->fractal_type = 0;
	env->fractal_name = "NONE";
	ui_init(env);
	return (env);
}

void		del_env(t_env *env)
{
	mlx_destroy_window(env->mlx->mlx_ptr, env->mlx->win_ptr);
	mlx_destroy_image(env->mlx->mlx_ptr, env->fractal_img->img);
	mlx_destroy_image(env->mlx->mlx_ptr, env->ui->img->img);
	free(env->mlx);
	free(env->fractal_img);
	free(env->ui->img);
	free(env->ui);
	free(env);
	exit(EXIT_SUCCESS);
}

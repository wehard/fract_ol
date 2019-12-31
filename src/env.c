/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:30:56 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 12:55:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include "mlx.h"

t_env	*init_env(char *title, int w, int h)
{
	int		i;
	t_env	*env;

	env = (t_env*)malloc(sizeof(t_env));
	env->mlx = (t_mlx*)malloc(sizeof(t_mlx));
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

void	del_env(t_env *env)
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

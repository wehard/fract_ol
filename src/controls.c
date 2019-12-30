/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:45:24 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 16:13:39 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

int			key_press(int key, void *param)
{
	t_env *env;
	float move;

	move = 0.05f;
	env = (t_env*)param;
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	if (key == KEY_1)
		env->fractal_type = FRAC_JULIA;
	if (key == KEY_2)
		env->fractal_type = FRAC_MANDELBROT;
	if (key == KEY_3)
		env->fractal_type = FRAC_BURNING_SHIP;
	if (key == KEY_LEFT)
		env->move_x += move / env->zoom;
	if (key == KEY_RIGHT)
		env->move_x -= move / env->zoom;
	if (key == KEY_DOWN)
		env->move_y -= move / env->zoom;
	if (key == KEY_UP)
		env->move_y += move / env->zoom;
	if (key == KEY_SPACE)
		env->free_julia = !env->free_julia;
	if (key == KEY_P)
		env->color_palette < NUM_PALETTE - 1 ? (env->color_palette++) : (env->color_palette = 0);
	if (key == KEY_NUM_PLUS || key == KEY_NUM_MINUS)
		key == KEY_NUM_PLUS ? env->iterations++ : env->iterations--;
	env->ui->buttons[env->fractal_type].selected = 1;
	plot_fractal(env, WIN_W, WIN_H);
	return (0);
}

int mouse_move(int x, int y, void *param)
{
	t_env *env;

	env = (t_env*)param;
	if (x < 0 || x > WIN_W)
		x = x < 0 ? 0 : WIN_W;
	if (y < 0 || y > WIN_H)
		y = y < 0 ? 0 : WIN_H;
	env->mouse_x = x;
	env->mouse_y = y;
	if (env->fractal_type == FRAC_JULIA && env->free_julia)
		plot_fractal(env, WIN_W, WIN_H);
	int i;
	i = 0;
	while (i < 4)
	{
		t_p2i pos = env->ui->pos;
		pos.x +=  env->ui->buttons[i].pos.x;
		pos.y +=  env->ui->buttons[i].pos.y;
		t_p2i size = env->ui->buttons[i].size;
		if ((x > pos.x && x < pos.x + size.x) && (y > pos.y && y < pos.y + size.y))
		{
			env->ui->buttons[i].selected = 1;
		}
		else
		{
			env->ui->buttons[i].selected = 0;
		}
		i++;
	}

	return (0);
}

int 	mouse_press(int button, int x, int y, void *param)
{
	t_env *env;

	env = (t_env*)param;

	if (button == 4 || button == 5)
	{
		if (button == 5)
			env->zoom *= 1.1f;
		if (button == 4)
			env->zoom *= 0.9f;
	}
	plot_fractal(env, WIN_W, WIN_H);
	return (0);
}

int expose(void *param)
{
	t_env *env;

	env = (t_env*)param;
	ft_putendl("expose");
	return (0);
}

int close(void *param)
{
	(void)param;
	exit(0);
}

void	setup_controls(t_env *env)
{
	mlx_hook(env->mlx->win_ptr, 2, (1L << 0), key_press, (void*)env);
	mlx_hook(env->mlx->win_ptr, 4, (1L<<2), mouse_press, (void*)env);
	mlx_hook(env->mlx->win_ptr, 6, (1L<<6), mouse_move, (void*)env);
	mlx_hook(env->mlx->win_ptr, 12, 0, expose, (void*)env);
	mlx_hook(env->mlx->win_ptr, 17, (1L << 17), close, (void*)env);
}

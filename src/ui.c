/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:40:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/31 13:09:51 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>
#include "ft_printf.h"

int				ui_init(t_env *env)
{
	if (!(env->ui = (t_ui*)malloc(sizeof(t_ui))))
		return (0);
	env->ui->pos = make_p2i((WIN_W / 3) * 2, 0);
	env->ui->img = create_mlx_image(env, WIN_W / 3, WIN_H);
	return (1);
}

static void		draw_ui_bg(t_env *env)
{
	draw_rect(env->ui->img, make_p2i(0, 0),
		make_p2i(env->ui->img->w, env->ui->img->h), UI_BG);
	draw_rect(env->ui->img, make_p2i(0, 0),
		make_p2i(env->ui->img->w, 50), UI_FG);
	draw_rect(env->ui->img, make_p2i(0, 300),
		make_p2i(env->ui->img->w, 50), UI_FG);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->ui->img->img, env->ui->pos.x, env->ui->pos.y);
}

static void		draw_fractal_info(t_env *env)
{
	char	str[128];

	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 140,
		env->ui->pos.y + 15, UI_TEXT, env->fractal_name);
	ft_bzero(str, 128);
	ft_sprintf(str, "%-17s%.3f", "Zoom level:", env->zoom);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 50, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%-17s%.3f, %.3f", "Pos:", env->move_x, env->move_y);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 70, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%-17s%d", "Palette:", env->color_palette);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 90, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%-17s%d", "Iterations:", env->iterations);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 110, UI_TEXT, str);
	ft_sprintf(str, "Space to set Julia free!");
	if (env->fractal_type == FRAC_JULIA)
		mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr,
			env->ui->pos.x + 10, env->ui->pos.y + 460, UI_TEXT, str);
}

static void		draw_controls(t_env *env)
{
	char	str[128];

	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 160,
		env->ui->pos.y + 315, UI_TEXT, "CONTROLS");
	ft_bzero(str, 128);
	ft_sprintf(str, "%s", "Use [1-3] to select fractal type");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 360, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%s", "Use mousewheel to zoom");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 380, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%s", "Use arrow keys to move");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 400, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%s", "P to change color palette");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 420, UI_TEXT, str);
	ft_bzero(str, 128);
	ft_sprintf(str, "%s", "Numpad + and - to change iterations");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10,
		env->ui->pos.y + 440, UI_TEXT, str);
}

void			draw_ui(t_env *env)
{
	draw_ui_bg(env);
	draw_fractal_info(env);
	draw_controls(env);
}

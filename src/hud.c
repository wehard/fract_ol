/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:38:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/28 14:50:27 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>

t_ui_button	create_ui_button(t_p2i pos, t_p2i size, char *label)
{
	t_ui_button button;

	button.pos = pos;
	button.size = size;
	button.label = label;
	return (button);
}

int			create_ui_buttons(t_env *env)
{
	if (!env)
		return (0);
	env->ui_buttons = malloc(sizeof(t_ui_button) * 4);
	env->ui_buttons[0] = create_ui_button(make_p2i(0, 0), make_p2i(100, 50), "BUTTON");
	env->ui_buttons[1] = create_ui_button(make_p2i(0, 60), make_p2i(100, 50), "BUTTON");
	env->ui_buttons[2] = create_ui_button(make_p2i(0, 120), make_p2i(100, 50), "BUTTON");
	env->ui_buttons[3] = create_ui_button(make_p2i(0, 180), make_p2i(100, 50), "BUTTON");
	return (1);
}

static void draw_rectangle(t_mlx_img *img, t_p2i pos, t_p2i size, int color)
{
	t_p2i cur;

	cur.y = pos.y;
	while (cur.y < pos.y + size.y)
	{
		cur.x = pos.x;
		while (cur.x < pos.x + size.x)
		{
			put_pixel_mlx_img(img, cur.x, cur.y, color);
			cur.x++;
		}
		cur.y++;
	}
}

static void draw_hud_bg(t_env *env)
{
	draw_rectangle(env->hud_img, make_p2i(0, 0), make_p2i(env->hud_img->w, env->hud_img->h), HUD_BG);
	draw_rectangle(env->hud_img, make_p2i(0, 0), make_p2i(env->hud_img->w, 50), HUD_FG);
	draw_rectangle(env->hud_img, make_p2i(0, 300), make_p2i(env->hud_img->w, 50), HUD_FG);
}

static void draw_ui_buttons(t_env *env, t_p2i hud_pos)
{
	int i;

	i = 0;
	while (i < 4)
	{
		draw_rectangle(env->hud_img, env->ui_buttons[i].pos, env->ui_buttons[i].size, HUD_BTN);
		i++;
	}
}


void	draw_hud(t_env *env)
{
	int hudx;
	int hudy;

	hudx = (WIN_W / 3) * 2;
	hudy = 0;
	draw_hud_bg(env);
	draw_ui_buttons(env, make_p2i(hudx, hudy));
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->hud_img->img, hudx, hudy);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, hudx + 180, hudy + 30, HUD_TEXT, "FRACTAL_NAME");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, hudx + 190, hudy + 330, HUD_TEXT, "CONTROLS");
}

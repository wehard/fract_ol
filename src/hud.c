/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:38:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/24 00:36:18 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

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

void	draw_hud(t_env *env)
{
	int hudx;
	int hudy;

	hudx = (WIN_W / 3) * 2;
	hudy = 0;
	draw_hud_bg(env);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr,
		env->hud_img->img, hudx, hudy);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, hudx + 180, hudy + 30, HUD_TEXT, "FRACTAL_NAME");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, hudx + 190, hudy + 330, HUD_TEXT, "CONTROLS");
}

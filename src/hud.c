/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:38:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/23 18:05:16 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

static void draw_rectangle(t_mlx *mlx, t_p2i pos, t_p2i size, int color)
{
	t_p2i cur;

	cur.y = pos.y;
	while (cur.y < pos.y + size.y)
	{
		cur.x = pos.x;
		while (cur.x < pos.x + size.x)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, cur.x, cur.y, color);
			cur.x++;
		}
		cur.y++;
	}
}

void	draw_hud(t_env *env)
{
	draw_rectangle(env->mlx, make_p2i(WIN_W/3*2, 0), make_p2i(WIN_W / 3, WIN_H), HUD_BG);
}

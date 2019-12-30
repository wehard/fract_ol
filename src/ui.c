/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:40:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/30 17:43:55 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>
#include "ft_printf.h"

static void		draw_rectangle(t_mlx_img *img, t_p2i pos, t_p2i size, int color)
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

static void		draw_ui_bg(t_ui *ui)
{
	draw_rectangle(ui->img, make_p2i(0, 0), make_p2i(ui->img->w, ui->img->h), UI_BG);
	draw_rectangle(ui->img, make_p2i(0, 0), make_p2i(ui->img->w, 50), UI_FG);
	draw_rectangle(ui->img, make_p2i(0, 300), make_p2i(ui->img->w, 50), UI_FG);
}

int				ui_init(t_env *env)
{
	if (!(env->ui = (t_ui*)malloc(sizeof(t_ui))))
		return (0);
	env->ui->pos = make_p2i((WIN_W / 3) * 2, 0);
	env->ui->img = create_mlx_image(env, WIN_W / 3, WIN_H);
	return (1);
}

static char		*get_fractal_name(int i)
{
	if (i == 1)
		return ("    JULIA   ");
	else if (i == 2)
		return (" MANDELBROT ");
	else if (i == 3)
		return ("BURNING SHIP");
	else
		return ("FRACTAL_NAME");
}

void			draw_ui(t_env *env)
{
	draw_ui_bg(env->ui);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->img->img, env->ui->pos.x, env->ui->pos.y);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 140, env->ui->pos.y + 15, UI_TEXT, get_fractal_name(env->fractal_type));
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 160, env->ui->pos.y + 315, UI_TEXT, "CONTROLS");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 50, UI_TEXT, "Zoom level:");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 140, env->ui->pos.y + 50, UI_TEXT, ft_dtoa(env->zoom, 6));
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 70, UI_TEXT, "Pos:");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 140, env->ui->pos.y + 70, UI_TEXT, ft_dtoa(env->move_x, 3));
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 200, env->ui->pos.y + 70, UI_TEXT, ft_dtoa(env->move_y, 3));
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 90, UI_TEXT, "Palette: ");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 140, env->ui->pos.y + 90, UI_TEXT, ft_itoa(env->color_palette));
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 110, UI_TEXT, "Iterations: ");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 140, env->ui->pos.y + 110, UI_TEXT, ft_itoa(env->iterations));
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 360, UI_TEXT, "Zoom:");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 380, UI_TEXT, "Move:");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 10, env->ui->pos.y + 400, UI_TEXT, "Color palette:");
}

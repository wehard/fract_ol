/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:38:57 by wkorande          #+#    #+#             */
/*   Updated: 2019/12/28 15:11:48 by wkorande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>

static t_ui_button	create_ui_button(t_p2i pos, t_p2i size, char *label)
{
	t_ui_button button;

	button.pos = pos;
	button.size = size;
	button.label = label;
	button.selected = 0;
	return (button);
}

static int			create_ui_buttons(t_ui *ui)
{
	if (!ui)
		return (0);
	ui->buttons = malloc(sizeof(t_ui_button) * 4);
	ui->buttons[0] = create_ui_button(make_p2i(10, 60), make_p2i(60, 40), "0");
	ui->buttons[1] = create_ui_button(make_p2i(80, 60), make_p2i(60, 40), "1");
	ui->buttons[2] = create_ui_button(make_p2i(150, 60), make_p2i(60, 40), "2");
	ui->buttons[3] = create_ui_button(make_p2i(220, 60), make_p2i(60, 40), "3");
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

static void draw_ui_bg(t_ui *ui)
{
	draw_rectangle(ui->img, make_p2i(0, 0), make_p2i(ui->img->w, ui->img->h), UI_BG);
	draw_rectangle(ui->img, make_p2i(0, 0), make_p2i(ui->img->w, 50), UI_FG);
	draw_rectangle(ui->img, make_p2i(0, 300), make_p2i(ui->img->w, 50), UI_FG);
}

static void draw_ui_buttons(t_ui *ui)
{
	int i;

	i = 0;
	while (i < 4)
	{
		draw_rectangle(ui->img, ui->buttons[i].pos, ui->buttons[i].size, ui->buttons[i].selected ? UI_BTN_SELECTED : UI_BTN);
		i++;
	}
}

static void draw_ui_button_labels(t_env *env, t_ui *ui)
{
	int i;
	t_p2i label_pos;

	i = 0;
	while (i < 4)
	{
		label_pos.x = ui->pos.x + ui->buttons[i].pos.x + (ui->buttons[i].size.x / 2) - 5;
		label_pos.y = ui->pos.y + ui->buttons[i].pos.y + (ui->buttons[i].size.y / 2) - 10;
		mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, label_pos.x, label_pos.y, UI_TEXT, ui->buttons[i].label);
		i++;
	}
}

int			ui_init(t_env *env)
{
	if (!(env->ui = (t_ui*)malloc(sizeof(t_ui))))
		return (0);
	env->ui->pos = make_p2i((WIN_W / 3) * 2, 0);
	env->ui->img = create_mlx_image(env, WIN_W / 3, WIN_H);
	create_ui_buttons(env->ui);
	return (1);
}

void	draw_ui(t_env *env)
{
	draw_ui_bg(env->ui);
	draw_ui_buttons(env->ui);
	mlx_put_image_to_window(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->img->img, env->ui->pos.x, env->ui->pos.y);
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 180, env->ui->pos.y + 30, UI_TEXT, "FRACTAL_NAME");
	mlx_string_put(env->mlx->mlx_ptr, env->mlx->win_ptr, env->ui->pos.x + 190, env->ui->pos.y + 330, UI_TEXT, "CONTROLS");
	draw_ui_button_labels(env, env->ui);
}

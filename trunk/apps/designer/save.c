/*
 * File: save.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief: ui to save xul file.
 *
 * Copyright (c) 2009 - 2011  Li XianJing <xianjimli@hotmail.com>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2011-09-27 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "save.h"
#include "code_gen.h"
#include "ftk_file_system.h"

static char s_last_file[FTK_MAX_PATH+1] = {0};

typedef struct _Info
{
	FtkWidget* widget;
	FtkWidget* widget_file_name;
}Info;

static Info* info_create(void)
{
	Info* info = FTK_NEW(Info);
	
	return info;
}

static void info_destroy(void* data)
{
	FTK_FREE(data);
	
	return;
}

static Ret button_ok_clicked(void* ctx, void* obj)
{
	char* ext = NULL;
	char filename[FTK_MAX_PATH+1] = {0};
	FtkWidget* win = (FtkWidget*)ctx;
	Info* info = (Info*)ftk_widget_user_data(win);
	ftk_strncpy(filename, ftk_widget_get_text(info->widget_file_name), FTK_MAX_PATH);

	return_val_if_fail(strlen(filename) > 0, RET_FAIL);

	ext = strrchr(filename, '.');
	if(ext != NULL)
	{
		*ext = '\0';
	}
	else 
	{
		ext = filename + strlen(filename);
	}

	strcpy(ext, ".xul");
	code_gen_xul(info->widget, filename);
	ftk_strncpy(s_last_file, filename, FTK_MAX_PATH);

	strcpy(ext, ".c");
	code_gen_c(info->widget, filename, 0);

	ftk_widget_unref(win);

	return RET_OK;
}

static Ret button_cancel_clicked(void* ctx, void* obj)
{
	FtkWidget* win = (FtkWidget*)ctx;

	ftk_widget_unref(win);

	return RET_OK;
}

Ret ftk_widget_editor_save(FtkWidget* widget)
{
	int width = 0;
	int height = 0;
	int y_offset = 0;
	
	Info* info = NULL;
	FtkWidget* win = NULL;
	FtkWidget* label = NULL;
	FtkWidget* entry = NULL;	
	FtkWidget* button = NULL;
	
	info = info_create();
	return_val_if_fail(info != NULL, RET_FAIL);

	win = ftk_app_window_create();
	ftk_widget_set_user_data(win, info_destroy, info);
	ftk_widget_set_text(win, _("Save..."));
	
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);

	info->widget = widget;
	
	y_offset = height/3;
	label = ftk_label_create(win, 0, y_offset, width/5, 30);
	ftk_widget_set_text(label, _("Name:"));
	info->widget_file_name = entry = ftk_entry_create(win, width/5, y_offset, width*4/5-2, 30);
	if(s_last_file[0] == '\0')
	{
		ftk_fs_get_cwd(s_last_file);
	}
	ftk_widget_set_text(entry, s_last_file);

	button = ftk_button_create(win, width/5, height-60, width/5, 50);
	ftk_widget_set_text(button, _("OK"));
	ftk_button_set_clicked_listener(button, button_ok_clicked, win);

	button = ftk_button_create(win, width*3/5, height-60, width/5, 50);
	ftk_widget_set_text(button, _("Cancel"));
	ftk_button_set_clicked_listener(button, button_cancel_clicked, win);
	
	ftk_widget_show_all(win, 1);

	return RET_OK;
}

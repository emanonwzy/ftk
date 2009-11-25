/*
 * File: ftk_source_manager.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   sources manager
 *
 * Copyright (c) 2009  Li XianJing <xianjimli@hotmail.com>
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
 * 2009-10-15 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "ftk_sources_manager.h"

struct _FtkSourcesManager
{
	int read_fd;
	int write_fd;
	int source_nr;
	int max_source_nr;
	int need_refresh;
	FtkSource* sources[1];
};

typedef enum _FtkRequestType
{
	FTK_REQUEST_ADD_SOURCE,
	FTK_REQUEST_REMOVE_SOURCE,
}FtkRequestType;

typedef struct _FtkRequest
{
	int   type;
	void* data;
}FtkRequest;

#define MAX_SOURCES 32
FtkSourcesManager* ftk_sources_manager_create(int max_source_nr)
{
	FtkSourcesManager* thiz = NULL;
	max_source_nr = max_source_nr < MAX_SOURCES ? MAX_SOURCES : max_source_nr;

	thiz = (FtkSourcesManager*)FTK_ZALLOC(sizeof(FtkSourcesManager) + sizeof(FtkSource*)*(max_source_nr + 1));

	if(thiz != NULL)
	{
		int pipes[2] = {0};
		pipe(pipes);
		thiz->read_fd  = pipes[0];
		thiz->write_fd = pipes[1];
		thiz->max_source_nr = max_source_nr;
	}

	return thiz;
}

Ret  ftk_sources_manager_add(FtkSourcesManager* thiz, FtkSource* source)
{
	return_val_if_fail(thiz != NULL && source != NULL, RET_FAIL);
	return_val_if_fail(thiz->source_nr < thiz->max_source_nr, RET_FAIL);

	thiz->sources[thiz->source_nr++] = source;

	return RET_OK;
}

Ret  ftk_sources_manager_remove(FtkSourcesManager* thiz, FtkSource* source)
{
	int i = 0;
	return_val_if_fail(thiz != NULL && source != NULL, RET_FAIL);

	for(i = 0; i < thiz->source_nr; i++)
	{
		if(thiz->sources[i] == source)
		{
			break;
		}
	}
	
	if(i < thiz->source_nr)
	{
		for(; (i + 1) < thiz->source_nr; i++)
		{
			thiz->sources[i] = thiz->sources[i+1];
		}
		thiz->source_nr--;
		thiz->sources[thiz->source_nr] = NULL;
		ftk_source_unref(source);
	}

	return RET_OK;
}

int  ftk_sources_manager_get_count(FtkSourcesManager* thiz)
{
	return_val_if_fail(thiz != NULL, 0);

	return thiz->source_nr;
}

FtkSource* ftk_sources_manager_get(FtkSourcesManager* thiz, int i)
{
	return_val_if_fail(thiz != NULL && i < thiz->source_nr, NULL);

	return thiz->sources[i];
}

Ret  ftk_sources_manager_add_async(FtkSourcesManager* thiz, FtkSource* source)
{
	int ret = 0;
	FtkRequest request = {0};
	return_val_if_fail(thiz != NULL && source != NULL, RET_FAIL);

	request.data = source;
	request.type = FTK_REQUEST_ADD_SOURCE;
	ret = write(thiz->write_fd, &request, sizeof(FtkRequest));

	return ret == sizeof(FtkRequest) ? RET_OK : RET_FAIL;
}

Ret  ftk_sources_manager_remove_async(FtkSourcesManager* thiz, FtkSource* source)
{
	int ret = 0;
	FtkRequest request = {0};
	return_val_if_fail(thiz != NULL && source != NULL, RET_FAIL);

	request.data = source;
	request.type = FTK_REQUEST_REMOVE_SOURCE;
	ret = write(thiz->write_fd, &request, sizeof(FtkRequest));

	return ret == sizeof(FtkRequest) ? RET_OK : RET_FAIL;
}

Ret  ftk_sources_manager_handle_async(FtkSourcesManager* thiz)
{
	int ret = 0;
	FtkRequest request = {0};

	ret = read(thiz->read_fd, &request, sizeof(FtkRequest));
	return_val_if_fail(ret == sizeof(FtkRequest), RET_FAIL);

	switch(request.type)
	{
		case FTK_REQUEST_ADD_SOURCE:
		{
			ftk_sources_manager_add(thiz, request.data);
			break;
		}
		case FTK_REQUEST_REMOVE_SOURCE:
		{
			ftk_sources_manager_remove(thiz, request.data);
			break;
		}
		default:break;
	}

	return RET_OK;
}

int  ftk_sources_manager_get_async_pipe(FtkSourcesManager* thiz)
{
	return_val_if_fail(thiz != NULL, -1);

	return thiz->read_fd;
}

int ftk_sources_manager_need_refresh(FtkSourcesManager* thiz)
{
	int need_refresh = 0;
	return_val_if_fail(thiz != NULL, 0);

	if(thiz->need_refresh > 0)
	{
		need_refresh = thiz->need_refresh;
		thiz->need_refresh--;
	}

	return need_refresh;
}

Ret  ftk_sources_manager_set_need_refresh(FtkSourcesManager* thiz)
{
	return_val_if_fail(thiz != NULL, RET_FAIL);

	thiz->need_refresh++;

	return RET_OK;
}

void ftk_sources_manager_destroy(FtkSourcesManager* thiz)
{
	int i = 0;

	if(thiz != NULL)
	{
		for(i = 0; i < thiz->source_nr; i++)
		{
			ftk_source_unref(thiz->sources[i]);
			thiz->sources[i] = NULL;
		}

		FTK_ZFREE(thiz, sizeof(FtkSourcesManager) + sizeof(FtkSource*)*(thiz->max_source_nr + 1));
	}

	return;
}


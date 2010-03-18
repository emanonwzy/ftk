/*
 * File: ftk_allocator.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   memory allocator interface.
 *
 * Copyright (c) 2009 - 2010  Li XianJing <xianjimli@hotmail.com>
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
 * 2010-01-31 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "ftk_allocator_default.h"


void* ftk_allocator_default_alloc(FtkAllocator* thiz, size_t size)
{
	return malloc(size);	
}

void* ftk_allocator_default_realloc(FtkAllocator* thiz, void* ptr, size_t new_size)
{
	return realloc(ptr, new_size);
}

void  ftk_allocator_default_free(FtkAllocator* thiz, void* ptr)
{
	free(ptr);

	return;
}

void  ftk_allocator_default_destroy(FtkAllocator* thiz)
{

	return;
}

static const FtkAllocator g_default_allocator =
{
	ftk_allocator_default_alloc,
	ftk_allocator_default_realloc,
	ftk_allocator_default_free,
	ftk_allocator_default_destroy
};

FtkAllocator* ftk_allocator_default_create(void)
{
	return (FtkAllocator*)&g_default_allocator;
}
/*
 * File:    coder.c 
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   some common used functions for coder.
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
 * 2010-07-31 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "coder.h"
#include <ctype.h>

char* coder_name_to_upper(const char* src, char* dst, int skip)
{
	int i = 0;
	int j = 0;

	dst[0] = toupper(src[0]);
	for(i = 1, j = 1; src[i]; i++)
	{
		if(src[i] == '_')
		{
			continue;
		}
		else if(src[i-1] == '_')
		{
			dst[j++] = toupper(src[i]);
		}
		else
		{
			dst[j++] = src[i];
		}
	}
	dst[j] = '\0';

	return dst + skip;
}

char* coder_name_to_lower(const char* src, char* dst)
{
	int i = 0;
	int j = 0;

	for(i = 0, j = 0; src[i] != '\0'; i++, j++)
	{
		if(isupper(src[i]))
		{
			if(i > 0 && !isupper(src[i-1]))
			{
				dst[j++] = '_';
			}
		}
		dst[j] = tolower(src[i]);
	}
	dst[j] = '\0';

	return dst;
}

const char* coder_to_upper(char* src)
{
	int i = 0;
	for(i = 0; src[i] != '\0'; i++)
	{
		src[i] = toupper(src[i]);
	}

	return src;
}

const char* coder_to_lower(char* src)
{
	int i = 0;
	for(i = 0; src[i] != '\0'; i++)
	{
		src[i] = tolower(src[i]);
	}

	return src;
}


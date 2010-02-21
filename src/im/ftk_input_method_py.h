/*
 * File: ftk_input_method_py.h    
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   handwrite input method.
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
 * 2010-02-08 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef FTK_INPUT_METHOD_PY_H
#define FTK_INPUT_METHOD_PY_H

#include "ftk_input_method.h"

FTK_BEGIN_DECLS

FtkInputMethod* ftk_input_method_py_create(void);
FtkInputMethod* ftk_input_method_wb_create(void);

FTK_END_DECLS

#endif/*FTK_INPUT_METHOD_PY_H*/


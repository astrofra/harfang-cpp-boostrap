// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

struct lua_State;

namespace gs {

class TypeValue;

bool BindLuaGS(lua_State *L);

bool PushTypeValueToLua(lua_State *L, const TypeValue &val);
bool GetTypeValueFromLua(lua_State *L, TypeValue &out, int index, const char *cast_to);

} // gs

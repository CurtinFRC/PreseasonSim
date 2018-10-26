/*
* Copyright (c) 2015-2018 JlnWntr (jlnwntr@gmail.com)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef MINI_LUA_H
#include "MiniLua.hpp"
#include <iostream>
#endif

MiniLua::MiniLua(const std::string &filename) : Lua{nullptr} {
  Load(filename); 
}

void MiniLua::Load(const std::string &filename) {
  this->Lua = luaL_newstate();
  luaL_openlibs(this->Lua);

  if (this->Lua && (filename.length() > 0)) {
    luaL_loadfile(this->Lua, filename.c_str());
    lua_pcall(this->Lua, 0, 0, 0);
  }
}

bool MiniLua::GetGlobal(const char *name) {
  if ((!this->Lua) || (!name))
    return false;
  lua_getglobal(this->Lua, name);
  return true;
}

bool MiniLua::Get(const char *name, int &result) {
  if (this->GetGlobal(name) == false)
    return false;
  if (lua_isnumber(this->Lua, -1) == false) {
    lua_pop(this->Lua, 1);
    return false;
  }
  result = lua_tointeger(this->Lua, -1);
  lua_pop(this->Lua, 1);
  return true;
}

bool MiniLua::Get(const char *name, std::string &result) {
  if (this->GetGlobal(name) == false)
    return false;
  if (lua_type(this->Lua, -1) != LUA_TSTRING) {
    lua_pop(this->Lua, 1);
    return false;
  }
  result = lua_tostring(this->Lua, -1);
  lua_pop(this->Lua, 1);
  return true;
}

bool MiniLua::Get(const char *name, double &result) {
  if (this->GetGlobal(name) == false)
    return false;
  if (lua_isnumber(this->Lua, -1) == false) {
    lua_pop(this->Lua, 1);
    return false;
  }
  result = lua_tonumber(this->Lua, -1);
  lua_pop(this->Lua, 1);
  return true;
}

bool MiniLua::Get(const char *name, float &result) {
  double temp {};
  if (this->Get(name, temp) == false)
    return false;
  result = (float){(float)temp};
  return true;
}

bool MiniLua::Get(const char *name, bool &result) {
  if (this->GetGlobal(name) == false)
    return false;
  if (lua_isboolean(this->Lua, -1) == false) {
    lua_pop(this->Lua, 1);
    return false;
  }
  result = lua_toboolean(this->Lua, -1);
  lua_pop(this->Lua, 1);
  return true;
}

void MiniLua::PushNumber(double val) {
  lua_pushnumber(this->Lua, val);
}

void MiniLua::Call(const char *name, int nret, int nargs, ...) {
  va_list args;
  va_start(args, nret);

  lua_getglobal(this->Lua, name);
  for (int i = 0; i < nargs; i++) {
    double arg = va_arg(args, double);
    lua_pushnumber(this->Lua, arg);
  }
  
  if (lua_pcall(this->Lua, nargs, nret, 0) != 0) {
    std::cout << "ERROR: running function: " << lua_tostring(this->Lua, -1) << std::endl;
  }
}

double MiniLua::PopNumber() {
  double num = lua_tonumber(this->Lua, -1);
  lua_pop(this->Lua, 1);
  return num;
}

void MiniLua::Close() {
  if (!this->Lua)
    return;
  lua_close(this->Lua);
  this->Lua = nullptr;
}

MiniLua::~MiniLua() { this->Close(); }
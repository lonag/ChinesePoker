#include "scripting/lua-bindings/auto/lua_cocos2dx_navmesh_auto.hpp"
#include "lua_socket.hpp"
#include "scripting/lua-bindings/manual/navmesh/lua_cocos2dx_navmesh_conversions.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "net/Socket.h"

int lua_cocos2dx_socket_constructor(lua_State* tolua_S)
{
    int argc = 0;
    net::Socket* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_navmesh_NavMesh_constructor'", nullptr);
            return 0;
        }
        cobj = new net::Socket();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"cc.NavMesh");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.NavMesh:NavMesh",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_navmesh_NavMesh_constructor'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_cocos2dx_socket_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NavMesh)");
    return 0;
}

int lua_register_cocos2dx_socket(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.Socket");
    tolua_cclass(tolua_S,"Socket","cc.Socket","cc.Ref",nullptr);
    
    tolua_beginmodule(tolua_S,"Socket");
    tolua_function(tolua_S,"new",lua_cocos2dx_socket_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(net::Socket).name();
    g_luaType[typeName] = "cc.Socket";
    g_typeCast["Socket"] = "cc.Socket";
    return 1;
}
TOLUA_API int register_all_cocos2dx_socket(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,"cc",0);
    tolua_beginmodule(tolua_S,"cc");
    
    lua_register_cocos2dx_socket(tolua_S);
    
    tolua_endmodule(tolua_S);
    return 1;
}

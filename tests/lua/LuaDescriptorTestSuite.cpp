#include <lua/LuaDescriptorTestSuite.h>


void
LuaDescriptorTestSuite::setUp()
{
}

void
LuaDescriptorTestSuite::tearDown()
{
}

/*!
 * \test Check that lua_State is correclty initialized.
 *
 * \post
 * \li Lua state descriptor is initialized and valid.
 */
void
LuaDescriptorTestSuite::openTest1()
{
    LuaState luaState;

    CPPUNIT_ASSERT(luaState);
}

/*!
 * \test Check the execution of a function when the smart Lua descriptor is used.
 *
 * \pre
 * \li Lua descriptor is initialized and valid.
 *
 * \post
 * \li Function arguments are correctly passed to the function and no data corruption
 * occured.
 * \li The function is correctly executed.
 * \li The function return value can be accessed and no data corruption occurs.
 */
void
LuaDescriptorTestSuite::execFunctionTest1()
{
    LuaState luaState;

    std::string code = "func = function(arg) return -arg; end";
    CPPUNIT_ASSERT_EQUAL(0, luaL_loadbuffer(luaState, code.c_str(), code.size(), "luacode"));
    CPPUNIT_ASSERT_EQUAL(0, lua_pcall(luaState, 0, LUA_MULTRET, 0));

    lua_getglobal(luaState, "func");

    int value = 7;
    lua_pushinteger(luaState, value);

    CPPUNIT_ASSERT_EQUAL(0, lua_pcall(luaState, 1, 1, 0));

    CPPUNIT_ASSERT(lua_isnumber(luaState, -1));
    int retval = lua_tointeger(luaState, -1);
    CPPUNIT_ASSERT_EQUAL(value, -retval);
    lua_pop(luaState, 1);
}


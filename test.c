// if we're using g++ compiler
#ifdef __cplusplus
    extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
static int print(lua_State* L) {
    int i, bytes, lbytes; // declare i for bucle. bytes and lbytes for relloc function
    char *str = malloc(0); // inits with 0 bytes
    *str = '\0'; // starts with null
    int options = lua_gettop(L); // gets arguments number
    const char *t_string; //
    for (i=1; i<=options; i++) { // goes element by element, needs i=1 because tables starts in index 0
        lbytes = strlen(str); // gets total bytes of str last value
        t_string = luaL_tolstring(L, i, NULL);  // converts to string
        bytes = strlen(t_string); // gets total bytes of argument value
        if (i==1) { // prevents to add a \t and sum 2 bytes
            str = realloc(str, bytes+lbytes); // sum total bytes
            sprintf(str, "%s%s", str, t_string); // adds to "str": "str" again, and at the end "t_string"
        } else { // adds \t to next value
            str = realloc(str, bytes+lbytes+2); // sum total bytes, \t needs 2 bytes
            sprintf(str, "%s\t%s", str, t_string); // adds to "str": "str" again, and at the end "\t" "t_string"
        }
    }
    //printf("%s\n", str); // prints result and adds "\n"
    printf("%s", str); // prints result
    free(str); // free "str" memory
    return 1;
}
static int get_char_binary(lua_State* L) {
    const char *binary = luaL_checkstring(L, 1); // gets number, argument 1
    int length = strlen(binary); // goes by len
    char character=0; // starts character with 0
    int weight=1; // starts weight with 0
    binary+=length-1;
    int i;
    for(i=0; i<length; ++i, --binary) {
        if(*binary == '1')
        character+=weight;
        weight*=2;
    }
    char value_return[8]; // 8 bytes, or size
    sprintf(value_return, "%c", character); // prints on value_return the character
    lua_pushstring(L, value_return); // returns character
    return 1;
}
static int sum(lua_State* L) {
    int number_one = luaL_checknumber(L, 1); // gets number, argument 1
    int number_two = luaL_checknumber(L, 2); // gets number, argument 2
    lua_pushnumber(L, number_one+number_two); // returns number
    return 1;
}
static int multiply(lua_State* L) {
    int number_one = luaL_checknumber(L, 1); // gets number, argument 1
    int number_two = luaL_checknumber(L, 2); // gets number, argument 2
    lua_pushnumber(L, number_one*number_two); // returns number
    return 1;
}
static int len(lua_State *L) {
    int length = luaL_len(L, 1); // get length argument 1
    lua_pushnumber(L, length); // returns length
    return 1;
}
static const struct luaL_Reg test[] = {
    {"print", print},
    {"sum", sum},
    {"multiply", multiply},
    {"len", len},
    {"get_char_binary", get_char_binary},
    {NULL, NULL}
};
int luaopen_test(lua_State* L) { // returns library in table: library.function, must be luapen_libname
    luaL_newlibtable(L, test); // adds "test" struct (those are the commands), only creates the table
    luaL_setfuncs(L, test, 0); // im not sure what does mean '0', i think 0 means start of struct, not sure.
    return 1;
}
#ifdef __cplusplus
}
#endif

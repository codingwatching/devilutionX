include(functions/FetchContent_ExcludeFromAll_backport)

# Workaround for deprecation of older CMake versions
set(CMAKE_POLICY_VERSION_MINIMUM 3.22)

set(LUA_ENABLE_TESTING OFF)
set(LUA_BUILD_COMPILER OFF)
if(DEVILUTIONX_STATIC_LUA)
  set(LUA_ENABLE_SHARED OFF)
else()
  set(LUA_ENABLE_SHARED ON)
endif()

include(FetchContent)
FetchContent_Declare_ExcludeFromAll(Lua
    URL https://github.com/walterschell/Lua/archive/3ed55a56eaa05c9221f40b3c07d0e908eb1067b0.tar.gz
    URL_HASH MD5=77907b8209f77c65cb681a5012f2d804
)
FetchContent_MakeAvailable_ExcludeFromAll(Lua)

# Needed for sol2
set(LUA_VERSION_STRING "5.4.7" PARENT_SCOPE)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin" AND DARWIN_MAJOR_VERSION VERSION_EQUAL 8)
  # We need legacy-support from MacPorts for:
  # localtime_r gmtime_r
  find_package(MacportsLegacySupport REQUIRED)
  target_link_libraries(lua_static PRIVATE MacportsLegacySupport::MacportsLegacySupport)
elseif(ANDROID AND ("${ANDROID_ABI}" STREQUAL "armeabi-v7a" OR "${ANDROID_ABI}" STREQUAL "x86"))
  target_compile_definitions(lua_static PUBLIC -DLUA_USE_C89)
elseif(NINTENDO_3DS OR VITA OR NINTENDO_SWITCH OR NXDK)
  target_compile_definitions(lua_static PUBLIC -DLUA_USE_C89)
elseif(IOS)
  target_compile_definitions(lua_static PUBLIC -DLUA_USE_IOS)
endif()

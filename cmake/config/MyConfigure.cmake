set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14  -Wno-sign-compare -fPIC -o3 ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fPIC -o3 ")

set(CMAKE_SKIP_BUILD_RPATH FALSE)                 # 编译时加上RPATH
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)         # 编译时RPATH不使用安装的RPATH
set(CMAKE_INSTALL_RPATH "")                       # 安装RPATH为空
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)      # 安装的执行文件不加上RPATH







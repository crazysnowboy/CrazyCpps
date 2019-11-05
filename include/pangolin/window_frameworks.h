// CMake generated file. Do Not Edit.

#pragma once

namespace pangolin {

//void RegisterWaylandWindowFactory();
void RegisterX11WindowFactory();

inline bool LoadBuiltInWindowFrameworks()
{
//    RegisterWaylandWindowFactory();
    RegisterX11WindowFactory();
    return true;
}

} // pangolin

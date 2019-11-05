//
// Created by collin on 18-11-10.
//

#ifndef GLFW_RENDER_CRAZYWINDOW_H
#define GLFW_RENDER_CRAZYWINDOW_H
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include "utilities/config.h"
#include <GLFW/glfw3.h>
#include "CMatrix.hpp"
#include <Eigen/Eigen>



class CrazyWindow
{
public:
    CrazyWindow(config_parameters &conf);
    bool SetCallbackFunctions();
    bool ShouldExit();
    void Precall();
    void PostCall();
    void my_glfw_mouse_click_callback( GLFWwindow *window, int button, int action, int mods );

    Eigen::Matrix4f GetProjectMatrix(int w, int h, double fu, double fv, int u0, int v0, double zNear, double zFar);
    Eigen::Matrix4f GetViewPortMatrix();
private:
    GLFWwindow* window;
    Eigen::Matrix4f ProjectMatrix;
    config_parameters &conf;
};

static CrazyWindow *win_class = nullptr;
static void glfw_mouse_click_callback( GLFWwindow *window, int button, int action, int mods )
{
    if(win_class!= nullptr)
    {
        win_class->my_glfw_mouse_click_callback(window,button,action,mods);
    }
}

#endif //GLFW_RENDER_CRAZYWINDOW_H

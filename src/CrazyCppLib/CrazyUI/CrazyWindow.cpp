//
// Created by collin on 18-11-10.
//

#include "utilities/config.h"
#include "CrazyWindow.h"
CrazyWindow::CrazyWindow(config_parameters &conf):conf(conf)
{

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_VISIBLE, false);.0
    window = glfwCreateWindow(conf.width,conf.height,"CrazyWindow", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    this->SetCallbackFunctions();
    glfwWindowHint( GLFW_SAMPLES, 4 );
    glewInit();

    ProjectMatrix = this->GetProjectMatrix(conf.width, conf.height, conf.cam_fx, conf.cam_fy, conf.width/2, conf.height/2, conf.cam_zNear, conf.cam_zFar);

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
}
bool CrazyWindow::SetCallbackFunctions()
{
    glfwSetMouseButtonCallback( window, glfw_mouse_click_callback );
    win_class = this;

}
bool CrazyWindow::ShouldExit()
{
    return glfwWindowShouldClose (window);

}

void CrazyWindow::my_glfw_mouse_click_callback( GLFWwindow *window, int button, int action, int mods )
{
    std::cout <<"mouse click  button= "<<button<<std::endl;
    std::cout <<"mouse click  action= "<<action<<std::endl;
    std::cout <<"mouse click  mods= "<<mods<<std::endl;

}
void CrazyWindow::PostCall()
{
    glfwPollEvents();

    glfwSwapBuffers (window);

}

void CrazyWindow::Precall()
{
    glClearColor(0.1, 0.1, 0.1 , 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

Eigen::Matrix4f CrazyWindow::GetProjectMatrix(int w, int h, double fu, double fv, int u0, int v0, double zNear, double zFar)
{
    double L = +((double)u0) * zNear / -fu;
    double T = +((double)v0) * zNear / fv;
    double R = -(double)(w-u0) * zNear / -fu;
    double B = -(double)(h-v0) * zNear / fv;

    Eigen::Matrix4f P=Eigen::Matrix4f::Identity();
    P(0,0) = (float)(2 * zNear / (R-L));
    P(1,1) = (float)(2 * zNear / (T-B));
    P(2,2) = (float)(-(zFar +zNear) / (zFar - zNear));
    P(3,3) = 0.0f;

    P(0,2) = (float)((R+L)/(R-L));
    P(1,2) = (float)((T+B)/(T-B));
    P(3,2) = (float)(-1.0);
    P(2,3) = (float)( -(2*zFar*zNear)/(zFar-zNear));

//    std::cout <<"P = "<<P<<std::endl;


    return  P;

}
Eigen::Matrix4f CrazyWindow::GetViewPortMatrix()
{
    int w=conf.width;
    int h =conf.height;
    glfwGetWindowSize(window,&w,&h);
    if(conf.width!=w || conf.height !=h)
    {
        conf.width = w;
        conf.height =h;
        std::cout <<"w = "<<w<<std::endl;
        std::cout <<"h = "<<h<<std::endl;

        ProjectMatrix = this->GetProjectMatrix(conf.width, conf.height, conf.cam_fx, conf.cam_fy, conf.width/2, conf.height/2, conf.cam_zNear, conf.cam_zFar);

    }


    Eigen::Matrix4f VewMatrix = Eigen::Matrix4f::Identity();


    VewMatrix(2,3)=-2.0f;

    Eigen::Matrix4f ViewPort = ProjectMatrix*VewMatrix;

//    std::cout <<"ProjectMatrix = "<<ProjectMatrix<<std::endl;
//    std::cout <<"VewMatrix  = "<<VewMatrix<<std::endl;

    return ViewPort;
}

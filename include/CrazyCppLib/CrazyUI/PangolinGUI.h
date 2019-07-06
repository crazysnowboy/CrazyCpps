/*
 * This file is part of ElasticFusion.
 *
 * Copyright (C) 2015 Imperial College London
 *
 * The use of the code within this file and all code within files that
 * make up the software that is ElasticFusion is permitted for
 * non-commercial purposes only.  The full terms and conditions that
 * apply to the code within this file are detailed within the LICENSE.txt
 * file and at <http://www.imperial.ac.uk/dyson-robotics-lab/downloads/elastic-fusion/elastic-fusion-license/>
 * unless explicitly stated.  By downloading this file you agree to
 * comply with these terms.
 *
 * If you wish to use any of this code for commercial purposes then
 * please email researchcontracts.engineering@imperial.ac.uk.
 *
 */

#ifndef PangolinGUI_H_
#define PangolinGUI_H_

#include <pangolin/pangolin.h>
#include <pangolin/gl/gl.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/display/opengl_render_state.h>
#include <map>
#include <Shaders.h>
#include "CrossDatum.h"
#include "DualMap.h"
#include "utilities/config.h"
#include <string>
#include "Event.h"
#include <CArray.hpp>
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

namespace crazy
{

class PangolinGUI:private pangolin::Handler3D
{
public:

    MouseAction mouse;


    PangolinGUI(config_parameters &conf);
    void GL_Init();
    bool SetUpUI(config_parameters &config);

    bool SetUpBoxUI(config_parameters &config);
    bool SetUpButtonUI(config_parameters &config);
    bool SetUpDataBarUI(config_parameters &config);

    bool DeleteBoxUI();
    bool DeleteButtonUI();
    bool DeleteDataBarUI();

    ~PangolinGUI();


    bool ShouldExit();
    void Precall();
    void PostCall();
    bool ProcessEvent(CrossDatum &tDatum);

    void Command(const char *cmd);
    bool CheckControl(const char *cmd);
    double GetData(const char *cmd);
    bool  SetData(const char *cmd,float data);
    pangolin::OpenGlMatrix GetViewMatrix();
    void UpdateShowImage(CArray<cv::Mat> images);
private:

    void SetShowImage(int img_w,int img_h,int index,int total);


private:




    pangolin::Var<int> * gpuMem;
    pangolin::OpenGlRenderState s_cam;
    pangolin::View d_cam;
    CArray<pangolin::View*> d_image;
    CArray<pangolin::GlTexture *>imageTexture;

    pangolin::View ui_view;
    pangolin::View data_view;

    config_parameters &conf;



    DualMap<std::string,pangolin::Var<bool> *>  Buttons;
    DualMap<std::string,pangolin::Var<bool> *>  CheckBoxs;
    DualMap<std::string,pangolin::Var<float> *> DataBars;



    void myMouseHandle(pangolin::View&, pangolin::MouseButton button, int x, int y, bool pressed, int button_state);
    void myKeyHandle(pangolin::View&, unsigned char key, int x, int y, bool pressed);
    void myMouseMotion(pangolin::View&, int x, int y, int button_state);


};
}





#endif /* GUI_H_ */

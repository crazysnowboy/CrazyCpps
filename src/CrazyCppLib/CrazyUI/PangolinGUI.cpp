#include "PangolinGUI.h"

namespace crazy
{
PangolinGUI::PangolinGUI(config_parameters& conf):pangolin::Handler3D(s_cam),conf(conf)
{



    pangolin::Params windowParams;

    windowParams.Set("SAMPLE_BUFFERS", 0);
    windowParams.Set("SAMPLES", 0);



    printf("w =%d h=%d \r\n",conf.width,conf.height);
    if(conf.WithPanel)
    {
        pangolin::CreateWindowAndBind("CrazyWindow", conf.width+conf.panel*2, conf.height, windowParams);

    }
    else
    {
        pangolin::CreateWindowAndBind("CrazyWindow", conf.width, conf.height, windowParams);

    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    pangolin::SetFullscreen(conf.fullScreen);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);


    s_cam = pangolin::OpenGlRenderState(pangolin::ProjectionMatrix(conf.width, conf.height, conf.cam_fx, conf.cam_fy, conf.width/2, conf.height/2, conf.cam_zNear, conf.cam_zFar),
                                        pangolin::ModelViewLookAt(0, 0, 2, 0, 0, 0, pangolin::AxisY));

    pangolin::Display("cam").SetBounds(0, 1.0f, 0, 1.0f, (float)conf.width / (float)conf.height).SetHandler(this);




    if(conf.WithPanel)
    {

        // Add named OpenGL viewport to window and provide 3D Handler
        d_cam = pangolin::Display("cam")
                .SetBounds(0.0, 1.0, pangolin::Attach::Pix(conf.panel),pangolin::Attach::Pix(-conf.panel), 640.0f/480.0f);

        // Add named Panel and bind to variables beginning 'ui'
        // A Panel is just a View with a default layout and input handling
        ui_view = pangolin::CreatePanel("ui").SetBounds(0.0, 1.0, 0.0,pangolin::Attach::Pix(conf.panel));
        data_view = pangolin::CreatePanel("float").SetBounds(0.0, 1.0, pangolin::Attach::Pix(-conf.panel), 1.0);

        gpuMem = new pangolin::Var<int>("ui.GPU memory free", 0);

        SetUpUI(conf);



    }

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
    {
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    }
}

PangolinGUI:: ~PangolinGUI()
{

    delete gpuMem;
    this->DeleteDataBarUI();
    this->DeleteBoxUI();
    this->DeleteButtonUI();


}
bool PangolinGUI::DeleteDataBarUI()
{

    for(MapIterator<std::string,pangolin::Var<float> *>  it = DataBars.Begin(); it != DataBars.End(); it++)
    {
        delete(it->second);

    }
    DataBars.clear();


}
bool PangolinGUI::DeleteBoxUI()
{


    for(MapIterator<std::string,pangolin::Var<bool> *>  it = CheckBoxs.Begin(); it != CheckBoxs.End(); it++)
    {
        delete(it->second);
    }
    CheckBoxs.clear();

}
bool PangolinGUI::DeleteButtonUI()
{

    for(MapIterator<std::string,pangolin::Var<bool> *>   it = Buttons.Begin(); it != Buttons.End(); it++)
    {
        delete(it->second);
    }
    Buttons.clear();


}
bool PangolinGUI::SetUpUI(config_parameters &config)
{


    this->SetUpBoxUI(config);
    this->SetUpButtonUI(config);
    this->SetUpDataBarUI(config);


}

bool PangolinGUI::SetUpBoxUI(config_parameters &config)
{



    this->DeleteBoxUI();

    for(std::map<std::string,bool>::iterator it = config.GUI_CHECKBOX.begin(); it != config.GUI_CHECKBOX.end(); it++)
    {
        CheckBoxs.Insert(it->first,new pangolin::Var<bool>("ui."+it->first, false, true));
    }

    for(auto  it = CheckBoxs.Begin(); it != CheckBoxs.End(); it++)
    {

        it->second->Ref().Set(config.GUI_CHECKBOX[it->first]);
    }

}


bool PangolinGUI::SetUpButtonUI(config_parameters &config)
{


    this->DeleteButtonUI();


    for(int j=0; j<config.GUI_BUTTON.size(); j++)
    {
        Buttons.Insert(config.GUI_BUTTON[j],new pangolin::Var<bool>("ui."+config.GUI_BUTTON[j], false, false));
    }


}

bool PangolinGUI::SetUpDataBarUI(config_parameters &config)
{


    this->DeleteDataBarUI();


    for(std::map<std::string,std::vector<float>>::iterator it = config.GUI_DataBar.begin(); it != config.GUI_DataBar.end(); it++)
    {
        DataBars.Insert(it->first,new pangolin::Var<float>("float."+it->first, it->second[0], it->second[1], it->second[2]));
    }

//    int cnt=0;
    for(auto  it = DataBars.Begin(); it != DataBars.End(); it++)
    {

        it->second->Ref().Set(config.GUI_DataBar[it->first][0]);

//        cnt++;
    }
//    printf("cnt=%d \r\n",cnt);

}


void PangolinGUI::SetShowImage(int img_w,int img_h,int index,int total)
{
    std::string names="img_"+std::to_string(index);

    float start = (float)conf.panel/(float)(conf.width+conf.panel*2);
    float end = 1.0f - (float)conf.panel/(float)(conf.width+conf.panel*2);



    float left = start + (end -start)/total*index;
    float right =  left + (end - start)/total;
//    std::cout << "[" <<left <<" " <<right <<"]"<<std::endl;

    pangolin::View& temp_d_image=pangolin::Display(names)
                                 .SetBounds(0.0f,1/3.0f,left,right,(float)img_w/(float)img_h);

    d_image.push_back(&temp_d_image);

    pangolin::GlTexture * temp_imageTexture = new pangolin::GlTexture (img_w,img_h,GL_RGB,false,0,GL_RGB,GL_UNSIGNED_BYTE);

    imageTexture.push_back(temp_imageTexture);
}

void PangolinGUI::UpdateShowImage(CArray<cv::Mat> images)
{

    for(int k=0; k<imageTexture.size(); k++)
    {
        delete this->imageTexture[k];
    }
    d_image.clear();
    imageTexture.clear();

    for(int j=0; j<images.GetSize(); j++)
    {
        cv::Mat temp_image = images.Get(j).clone();
        if(temp_image.empty() )
        {
            std::cout <<"iamges empty "<<std::endl;

            continue;
        }

        this->SetShowImage(temp_image.cols, temp_image.rows, j, images.GetSize());
        cv::cvtColor(temp_image,temp_image,cv::COLOR_RGB2BGR);
        cv::flip(temp_image,temp_image,0);
        this->imageTexture[j]->Upload(temp_image.data, GL_RGB, GL_UNSIGNED_BYTE);
        this->d_image[j]->Activate();
        glColor3f(1.0, 1.0, 1.0);
        this->imageTexture[j]->RenderToViewport();
    }
    pangolin::Display("cam").Activate(s_cam);


}
void PangolinGUI::myMouseHandle(pangolin::View&, pangolin::MouseButton button, int x, int y, bool pressed, int button_state)
{

    if(button_state & pangolin::KeyModifierCtrl && button_state != MouseButtonUp)
    {
        mouse.x=x;
        mouse.y=y;
        mouse.state = button_state;
        mouse.Pressed=true;
//        std::cout <<"x = "<<x <<" y="<<y<<std::endl;

    }



}
void PangolinGUI::myKeyHandle(pangolin::View&, unsigned char key, int x, int y, bool pressed)
{
//    std::cout <<"x = "<<x <<" y="<<y<<std::endl;

}
void PangolinGUI::myMouseMotion(pangolin::View&, int x, int y, int button_state)
{
    if(button_state&pangolin::KeyModifierShift)
    {

//        std::cout <<"x = "<<x <<" y="<<y<<std::endl;

    }
}

void PangolinGUI::Precall()
{
    glClearColor(0.1, 0.1, 0.1 , 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    conf.width = pangolin::DisplayBase().v.w;
//    conf.height = pangolin::DisplayBase().v.h;

//    d_cam.Activate(s_cam);
    pangolin::Display("cam").Activate(s_cam);
}

void PangolinGUI::GL_Init()
{

//    //材质反光性设置
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 10.0 };  //镜面反射参数
//    GLfloat mat_shininess[] = { 100.0 };               //高光指数
//
//
//
//    GLfloat light1_position[] = { 0.0, 0.0, 10.0, 1.0 };
//    GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数
//    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//
//    glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
//
//
//    //材质属性
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
//    //灯光设置
//    glLightfv(GL_LIGHT0,  GL_DIFFUSE/*漫反射*/,  light1_diffuse);
//    glLightfv(GL_LIGHT0,  GL_POSITION,  light1_position);
//
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

//    glEnable(GL_LIGHTING);   //开关:使用光
//    glEnable(GL_LIGHT0);     //打开0#灯
//    glEnable(GL_DEPTH_TEST); //打开深度测试




}

bool PangolinGUI::ShouldExit()
{
    return this->CheckControl("Quit");
}

void PangolinGUI::PostCall()
{
    GLint cur_avail_mem_kb = 0;
    glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &cur_avail_mem_kb);

    int memFree = cur_avail_mem_kb / 1024;

    if(conf.WithPanel)
    {
        gpuMem->operator=(memFree);
    }

    pangolin::FinishFrame();

    glFinish();
}
void PangolinGUI::Command(const char *cmd)
{
    std::string cmd_str = cmd;

    if (cmd_str == "preCall")
    {
        this->Precall();
    }
    else if (cmd_str == "GL_Init")
    {
        GL_Init();
    }
    else if (cmd_str == "postCall")
    {
        this->PostCall();
    }
    else if (cmd_str == "OpenLight")
    {
        glEnable(GL_LIGHTING);   //开关:使用光
        glEnable(GL_LIGHT0);     //打开0#灯

    }
    else if (cmd_str == "CloseLight")
    {

        glDisable(GL_LIGHTING);   //开关:使用光
        glDisable(GL_LIGHT0);     //打开0#灯
    }


}
bool PangolinGUI::CheckControl(const char *cmd)
{
    std::string cmd_str = cmd;

    if(!conf.WithPanel)
    {
        return false;
    }
    for(auto it = Buttons.Begin(); it != Buttons.End(); it++)
    {
        if (cmd_str == it->first)
        {
            return pangolin::Pushed(*(it->second));
        }
    }
    for(auto  it = CheckBoxs.Begin(); it != CheckBoxs.End(); it++)
    {
        if (cmd_str == it->first)
        {
            return it->second->Get();
        }
    }
    if (cmd_str == "Quit")
    {
        return pangolin::ShouldQuit();
    }

    else if(cmd_str == "Mouse")
    {
        bool mouse_pressed =  this->mouse.Pressed;
        this->mouse.Pressed=false;
        return mouse_pressed;

    }
    else
    {
        return false;
    }
}
double PangolinGUI::GetData(const char *cmd)
{
    std::string cmd_str = cmd;

    if(!conf.WithPanel)
    {
        return 0;
    }
    for(MapIterator<std::string,pangolin::Var<float> *> it = DataBars.Begin(); it != DataBars.End(); it++)
    {
        if (cmd_str == it->first)
        {
            return it->second->Get();
        }
    }
}
bool  PangolinGUI::SetData(const char *cmd,float data)
{
    std::string cmd_str = cmd;

    if(!conf.WithPanel)
    {
        return false;
    }

//        std::cout <<"pangolin gui setdata"<<std::endl;

    for(MapIterator<std::string,pangolin::Var<float> *> it = DataBars.Begin(); it != DataBars.End(); it++)
    {
        if (cmd_str == it->first)
        {
            it->second->Ref().Set(data);
//                std::cout <<"pdata = "<<data<<std::endl;
        }
    }
}
bool PangolinGUI::ProcessEvent(CrossDatum &tDatum)
{


    tDatum.ViewMatrix =  this->GetViewMatrix();
    tDatum.mouse = mouse;
    mouse.clear();
    for(int j=0; j<conf.GUI_BUTTON.size(); j++)
    {
        tDatum.SetButton(conf.GUI_BUTTON[j].c_str(),this->CheckControl(conf.GUI_BUTTON[j].c_str()));

    }

    for(std::map<std::string,bool>::iterator it = conf.GUI_CHECKBOX.begin(); it != conf.GUI_CHECKBOX.end(); it++)
    {

        tDatum.SetBox(it->first.c_str(),this->CheckControl(it->first.c_str()));
    }

//    int cnt=0;
    for(std::map<std::string,std::vector<float>>::iterator it = conf.GUI_DataBar.begin(); it != conf.GUI_DataBar.end(); it++)
    {
        tDatum.SetData(it->first.c_str(),this->GetData(it->first.c_str()));
//        cnt++;
//        printf("%s ",it->first.c_str());
    }
//    printf("cnt = %d \r\n",cnt);
//    printf("\r\n");
    conf.draw_mode = tDatum.CheckBox("SR_Wired") == true ? "Wired":"Triangles";

    tDatum.win_height = 480;
    tDatum.win_width = 640;



    return true;

}


pangolin::OpenGlMatrix PangolinGUI::GetViewMatrix()
{
    return s_cam.GetProjectionModelViewMatrix();
}

}

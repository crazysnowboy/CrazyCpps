

#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include <map>
#include <vector>



class config_parameters
{


public:
    //UI configuration
    int  panel = 305;
    bool fullScreen =false;
    bool WithPanel = true;

    int width = 640;
    int height = 480;


    double cam_fx = height;
    double cam_fy = height;

    double cam_zNear=0.001;
    double cam_zFar = 100000.0;

    //rendering configuration
    std::string draw_mode = "Triangles";
    std::string render_mode = "OnScreen";

    std::vector<std::string> GUI_BUTTON;

    std::map<std::string,bool> GUI_CHECKBOX
    {
        std::make_pair("SR_Wired",false),

    };


    std::map<std::string ,std::vector<float>> GUI_DataBar;
public:

    const char * GetDrawMode()
    {
        return draw_mode.c_str();
    }

    bool SetGUI_DataBar(const char *name,float s,float m,float e)
    {
        std::string name_str = name;
        GUI_DataBar[name_str] = std::vector<float> {s,m,e};
    }
    bool SetGUI_BUTTON(const char *name)
    {
        std::string name_str = name;
        GUI_BUTTON.push_back(name_str);

    }
    bool SetGUI_CHECKBOX(const char *name,bool d)
    {
        std::string name_str = name;

        GUI_CHECKBOX[name_str]=d;

    }
    bool Clear(const char *name)
    {
        std::string name_str = name;
        if(name_str=="button")
        {
            GUI_BUTTON.clear();
        }
        else if(name_str=="box")
        {
            GUI_CHECKBOX.clear();
        }
        else if(name_str=="data")
        {
            GUI_DataBar.clear();
        }
    }
}
;


#endif //_CONFIG_H

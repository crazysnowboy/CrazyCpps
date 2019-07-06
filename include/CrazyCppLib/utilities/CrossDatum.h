

#ifndef MESHPRO_CROSSDATUM_H
#define MESHPRO_CROSSDATUM_H


#include <string>
#include "Mesh.h"
#include "Event.h"
#include "BaseIO.h"
#include "config.h"
#include <Eigen/Eigen>
class CrossDatum
{
public:
    Eigen::Matrix4d ViewMatrix;
    MouseAction mouse;

    int win_height=480;
    int win_width=640;

private:
    std::map<std::string,bool> CheckBoxState;
    std::map<std::string,bool> PushButtonState;
    std::map<std::string,float> DataBarState;
public:


    bool CheckBox(const char *cmd);
    bool CheckSwitchBox(const char *cmd,bool state);
    bool CheckSwitch(const char *cmd);
    bool CheckButton(const char *cmd);
    float GetData(const char *cmd);

    bool CheckMouseButton(const char* cmd);
    int GetMousePosition(const char* cmd);

    bool  SetBox(const char *cmd,bool state);
    bool  SetButton(const char *cmd,bool state);
    bool SetData(const char *cmd,float data);


    bool  InsertBox(const char *cmd,bool state);
    bool  InsertButton(const char *cmd,bool state);
    bool  InsertData(const char *cmd,float data);

};


#endif //MESHPRO_CROSSDATUM_H

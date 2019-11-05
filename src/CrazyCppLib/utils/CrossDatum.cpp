

#include "utilities/config.h"
#include "CrossDatum.h"


bool CrossDatum::CheckSwitchBox(const char *cmd,bool state)
{

    bool response = false;
    std::string cmd_str =cmd;
    bool res = CheckBoxState[cmd_str];
    if(this->CheckSwitch(cmd) && res == state)
    {
        response= true;
    }
    return response;

}
bool CrossDatum::CheckSwitch(const char *cmd)
{
    static std::map<std::string ,bool> box_map;
    std::string cmd_str =cmd;
    bool res = CheckBoxState[cmd_str];
    bool response = false;

    if(res !=box_map[cmd_str])
    {
        response =  true;
    }

    box_map[cmd_str] = res;

    return response;
}


bool CrossDatum::CheckBox(const char *cmd)
{

    std::string cmd_str =cmd;
    bool res = CheckBoxState[cmd_str];
    return res;

}

bool CrossDatum::CheckButton(const char *cmd)
{
    std::string cmd_str =cmd;
    bool res = PushButtonState[cmd_str];
    PushButtonState[cmd_str]=false;
    return res;
}
float CrossDatum::GetData(const char *cmd)
{
    std::string cmd_str =cmd;
    return  DataBarState[cmd_str];
}
bool CrossDatum::CheckMouseButton(const char *cmd)
{
    std::string cmd_str =cmd;
    if(cmd_str=="left")
    {
        return this->mouse.state ==MouseButtonLeftDown;

    }
    else if (cmd_str=="right")
    {
        return this->mouse.state ==MouseButtonRightDown;

    }

}
int CrossDatum::GetMousePosition(const char* cmd)
{
    std::string cmd_str =cmd;
    if(cmd_str=="x")
    {
        return this->mouse.x;

    }
    else if (cmd_str=="y")
    {
        return this->mouse.y;

    }
    return 0;
}
bool CrossDatum::SetBox(const char *cmd,bool state)
{
    std::string cmd_str =cmd;
    CheckBoxState[cmd_str]=state;
}
bool CrossDatum::SetButton(const char *cmd,bool state)
{
    std::string cmd_str =cmd;
    PushButtonState[cmd_str]=state;

}
bool CrossDatum::SetData(const char *cmd,float data)
{
    std::string cmd_str =cmd;
    DataBarState[cmd_str]=data;
}


bool  CrossDatum::InsertBox(const char *cmd,bool state)
{
    std::string cmd_str =cmd;
    PushButtonState.insert(std::make_pair(cmd_str,state));
}
bool  CrossDatum::InsertButton(const char *cmd,bool state)
{
    std::string cmd_str =cmd;
    CheckBoxState.insert(std::make_pair(cmd_str,state));
}
bool  CrossDatum::InsertData(const char *cmd,float data)
{
    std::string cmd_str =cmd;
    DataBarState.insert(std::make_pair(cmd_str,data));
}
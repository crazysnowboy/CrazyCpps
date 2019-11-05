
#ifndef MESHPRO_EVENT_H
#define MESHPRO_EVENT_H


enum ButtonState
{

    MouseButtonLeftDown = 131073,
    MouseButtonRightDown = 131076,
    MouseButtonUp =  131072
};

typedef struct
{
    int x;
    int y;
    int state;
    bool Pressed;
    bool clear()
    {
        x=0;
        y=0;
        state=0;
        Pressed=false;
    }


} MouseAction;

#endif //MESHPRO_EVENT_H

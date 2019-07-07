

#ifndef EXPERIMENTPROJECT_BasicDraw_H
#define EXPERIMENTPROJECT_BasicDraw_H


#include "Mesh.h"
#include <algorithm>
#include <GL/gl.h>
#include <GL/glut.h>
#include "BaseOperator.h"
namespace crazy
{

#define GlobalOffSet 0.42
#define PI_1 3.141592654
#define PI_2 PI_1*2.0
class BasicDraw
{

public:

    BasicDraw();


    static bool Array_Draw_myMesh(Mesh &mesh,const char* draw_mode);

    bool DrawObject(float x,float y,float z,float r,float g,float b,float scale);
    bool DrawLine(float x1,float y1,float z1,float x2,float y2,float z2,float r,float g,float b);

    static int PickNearestObject(Mesh &mesh,int x, int y,double cam_zNear,double cam_zFar);


private:

    Mesh::VertexType getPoint(double u,double v);
    Mesh get_sphere_mesh(int uStepsNum,int vStepNum,double scale);

private:
    Mesh object_mesh;

};
}



#endif //EXPERIMENTPROJECT_BasicDraw_H

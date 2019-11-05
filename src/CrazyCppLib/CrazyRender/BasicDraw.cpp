

#include "BasicDraw.h"

namespace crazy
{
BasicDraw::BasicDraw()
{

    object_mesh = this->get_sphere_mesh(10,10,1.0);
    BaseOperator::_Compute_Face_Vertices_Normals(object_mesh);
    BaseOperator::_NormalizeVertices(object_mesh);


}
Mesh::VertexType BasicDraw::getPoint(double u,double v)
{
    double x = sin(PI_1*v)*cos(PI_2*u);
    double y = sin(PI_1*v)*sin(PI_2*u);
    double z = cos(PI_1*v);
    return Mesh::VertexType(x,y,z);
}

Mesh BasicDraw::get_sphere_mesh(int uStepsNum,int vStepNum,double scale)
{

    Mesh object_mesh;

    double ustep = 1/(double)uStepsNum, vstep = 1/(double)vStepNum;
    double u = 0,v = 0;

    //绘制下端三角形组
    for(int i = 0; i<uStepsNum; i++)
    {
        Mesh::VertexType a = getPoint(0,0);
        Mesh::VertexType b = getPoint(u,vstep);
        Mesh::VertexType c = getPoint(u+ustep,vstep);
        u += ustep;

        int v_size = object_mesh.Vertices().GetSize();

        object_mesh.Vertices().Add(a);
        object_mesh.Vertices().Add(b);
        object_mesh.Vertices().Add(c);

        object_mesh.VertexFlags().Add(UFlag::Used);
        object_mesh.VertexFlags().Add(UFlag::Used);
        object_mesh.VertexFlags().Add(UFlag::Used);

        object_mesh.Faces().Add(Mesh::TriangleType(v_size+0,v_size+1,v_size+2));
        object_mesh.FaceFlags().Add(UFlag::Used);

    }
    //绘制中间四边形组
    u = 0, v = vstep;
    for(int i=1; i<vStepNum-1; i++)
    {
        for(int j=0; j<uStepsNum; j++)
        {
            Mesh::VertexType a = getPoint(u,v);
            Mesh::VertexType b = getPoint(u+ustep,v);
            Mesh::VertexType c = getPoint(u+ustep,v+vstep);
            Mesh::VertexType d = getPoint(u,v+vstep);
            int v_size = object_mesh.Vertices().GetSize();

            object_mesh.Vertices().Add(a);
            object_mesh.Vertices().Add(b);
            object_mesh.Vertices().Add(c);

            object_mesh.VertexFlags().Add(UFlag::Used);
            object_mesh.VertexFlags().Add(UFlag::Used);
            object_mesh.VertexFlags().Add(UFlag::Used);

            object_mesh.Faces().Add(Mesh::TriangleType(v_size+0,v_size+1,v_size+2));
            object_mesh.FaceFlags().Add(UFlag::Used);

            v_size = object_mesh.Vertices().GetSize();
            object_mesh.Vertices().Add(b);
            object_mesh.Vertices().Add(c);
            object_mesh.Vertices().Add(d);

            object_mesh.VertexFlags().Add(UFlag::Used);
            object_mesh.VertexFlags().Add(UFlag::Used);
            object_mesh.VertexFlags().Add(UFlag::Used);

            object_mesh.Faces().Add(Mesh::TriangleType(v_size+0,v_size+1,v_size+2));
            object_mesh.FaceFlags().Add(UFlag::Used);


            u += ustep;
        }
        v += vstep;
    }
    //绘制下端三角形组
    u = 0;
    for(int i=0; i<uStepsNum; i++)
    {
        Mesh::VertexType a = getPoint(0,1);
        Mesh::VertexType b = getPoint(u,1-vstep);
        Mesh::VertexType c = getPoint(u+ustep,1-vstep);

        int v_size = object_mesh.Vertices().GetSize();

        object_mesh.Vertices().Add(a);
        object_mesh.Vertices().Add(b);
        object_mesh.Vertices().Add(c);

        object_mesh.VertexFlags().Add(UFlag::Used);
        object_mesh.VertexFlags().Add(UFlag::Used);
        object_mesh.VertexFlags().Add(UFlag::Used);

        object_mesh.Faces().Add(Mesh::TriangleType(v_size+0,v_size+1,v_size+2));
        object_mesh.FaceFlags().Add(UFlag::Used);

    }
    return object_mesh;
}


bool BasicDraw::DrawObject(float x,float y,float z,float r,float g,float b,float scale)
{

    //设置光照后依然有颜色
    glEnable( GL_COLOR_MATERIAL );
    glLightModeli( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );// 这个表示模型的正面接受环境光和

    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    for (int j = 0;  j < object_mesh.Faces().GetSize();  j++)
    {

        for(int k=0; k<3; k++)
        {
            int v_id = object_mesh.Face(j).Id(k);

            glVertex3f(object_mesh.Vertex(v_id).GetCX()*scale+x,
                       object_mesh.Vertex(v_id).GetCY()*scale+y,
                       object_mesh.Vertex(v_id).GetCZ()*scale+z);

            glNormal3f(object_mesh.V_Normal(v_id).GetCX(),
                       object_mesh.V_Normal(v_id).GetCY(),
                       object_mesh.V_Normal(v_id).GetCZ());

        }
    }

    glEnd();



}

bool BasicDraw::DrawLine(float x1,float y1,float z1,float x2,float y2,float z2,float r,float g,float b)
{

    glLineWidth(1);

    glBegin(GL_LINES);
    glColor3f(r, g, b);

    glVertex3f(x1,y1,z1);
    glVertex3f(x2,y2,z2);

    glEnd();



}

bool BasicDraw::Array_Draw_myMesh(Mesh &mesh,const char* draw_mode)
{
    auto vertices =mesh.vertices;
    auto vertex_normals =mesh.vertex_normals;
    std::string _draw_mode = draw_mode;

    if (_draw_mode == "Triangles") // -----------------------------------
    {
        if(vertices.size()>0 && vertex_normals.size() >0)
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertices.data());

            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, vertex_normals.data());

            glBegin(GL_TRIANGLES);
            glColor3f(0.7f, 0.7f, 0.7f);
            glShadeModel(GL_SMOOTH);
            for (int t=0; t <mesh.Faces().GetSize(); t++)
            {
                if(mesh.CheckFacesFlags(t,UFlag::Used))
                {

                    glArrayElement(mesh.Face(t).v_id[0]);

                    glArrayElement(mesh.Face(t).v_id[1]);

                    glArrayElement(mesh.Face(t).v_id[2]);
                }

            }
            glEnd();

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else
        {
            std::cerr << "vertices.size()>0 && vertex_normals.size() >0 not meeted "<<std::endl;
        }

    }
    else if( _draw_mode == "Wired" ) // -----------------------------------------
    {

//        glEnable(GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.5f, 0.5f);
        for (int j = 0;  j < mesh.Faces().GetSize();  j++)
        {

            if(mesh.CheckFacesFlags(j,UFlag::Used))
            {
                for(int k=0; k<3; k++)
                {

                    int v_id = mesh.Face(j).v_id[k];


                    glVertex3f(vertices.Get(v_id).GetCX(), vertices.Get(v_id).GetCY(),
                               vertices.Get(v_id).GetCZ());

                    glNormal3f(vertex_normals.Get(v_id).GetCX(),
                               vertex_normals.Get(v_id).GetCY(),
                               vertex_normals.Get(v_id).GetCZ());
                }
            }

        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    }
    else if( _draw_mode == "RenderTrianglesForPicking" ) // -----------------------------------------
    {

        for (int j = 0;  j < mesh.Faces().GetSize();  j++)
        {
            glLoadName((GLuint)j);
            glBegin(GL_TRIANGLES);

            for(int k=0; k<3; k++)
            {
                glVertex3f(vertices[mesh.Face(j).v_id[k]].Mutable_X(), vertices[mesh.Face(j).v_id[k]].Mutable_Y(),
                           vertices[mesh.Face(j).v_id[k]].Mutable_Z());
                glNormal3f(vertex_normals[mesh.Face(j).v_id[k]].Mutable_X(),
                           vertex_normals[mesh.Face(j).v_id[k]].Mutable_Y(),
                           vertex_normals[mesh.Face(j).v_id[k]].Mutable_Z());
            }


            glEnd();

        }


    }
    else
    {
        printf("mode = %s is not supported \r\n",_draw_mode.c_str());
    }
}

int BasicDraw::PickNearestObject(Mesh &mesh,int x, int y,GLdouble cam_zNear,GLdouble cam_zFar)
{
#define PICK_TOL 0.0000001

    GLuint selectBuf[512];
    GLint hits;
    GLint viewport[4];


    glGetIntegerv(GL_VIEWPORT, viewport);

    /* Initialize object name stack */
    glSelectBuffer(sizeof(selectBuf)/sizeof(GLuint), selectBuf);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);

    /* Start Picking... specifying pick projection */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();


    /* Define an selection region, the coordnate specified in gluPickMatrix
       should be converted from screen coordinate to viewport coordinate */

    gluPickMatrix(x, y, PICK_TOL, PICK_TOL, viewport);

    const GLdouble cam_fovy = 50; //default parameters
    gluPerspective(cam_fovy,
                   ((GLdouble)viewport[2])/((GLdouble)viewport[3]),
                   cam_zNear, cam_zFar);

    Array_Draw_myMesh(mesh,"RenderTrianglesForPicking");
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();

    /* Done! */
    hits = glRenderMode(GL_RENDER);

    if (hits)
    {
        GLuint Triangle_id = selectBuf[3];  /* name of the first hitten object */
        GLuint min_z = selectBuf[1];  /* initialize min_z with the depth value of the
                                  first hitten object */
        for (int i = 1; i < hits; i++)
        {
            GLuint depth = selectBuf[i*4 + 1];
            if (depth < min_z)   /* if this is an upper layer object? */
            {
                Triangle_id = selectBuf[i*4 + 3]; /* name of this object */
                min_z = depth;
            }
        }


        return (int)Triangle_id;


    }
    else
    {
        return -1;  /* no object is hitten (picked up) */
    }
}

}




#include "CrazyGUI.h"
#include "CrazyRender.h"

#include "BaseOperator.h"



int main(int argc, char *argv[])
{
    config_parameters conf;
    CrossDatum cross_datum;
    conf.WithPanel = true;
    Mesh RenderingMesh;
    Mesh mesh1;



    BaseIO::TinyLoadOBJ(RenderingMesh,"data/face_mesh.obj");
    BaseIO::LoadTexture("data",RenderingMesh);
    BaseOperator::_Compute_Face_Vertices_Normals(RenderingMesh);
    BaseOperator::_NormalizeVertices(RenderingMesh);


    BaseIO::TinyLoadOBJ(mesh1,"data/blender_obj/cube2.obj");
    BaseIO::LoadTexture("data/blender_obj",mesh1);
    BaseOperator::_Compute_Face_Vertices_Normals(mesh1);
    BaseOperator::_NormalizeVertices(mesh1);


    mesh1.Vertices() += Mesh::VertexType(2.5,0.0,0);
    RenderingMesh.add_mesh(mesh1);


    conf.SetGUI_BUTTON("test_button");

    CrazyGUI* crazy_gui = new CrazyGUI(conf);
    CrazyRender RenderTool(loadProgramFromFile("TransformVertexShader.vert", "TextureFragmentShader.frag","shader"));


    RenderTool.Update(RenderingMesh);


    while(crazy_gui->ShouldExit()==false)
    {

        /////////////////////////
        crazy_gui->Precall();
        /////////////////////////


        crazy_gui->ProcessEvent(cross_datum);


        RenderTool.Rendering(crazy_gui->GetViewMatrix(), conf.GetDrawMode());


        ///////////////////////
        crazy_gui->PostCall();
        /////////////////////////

    }


}
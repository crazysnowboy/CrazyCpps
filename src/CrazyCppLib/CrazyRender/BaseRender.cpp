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

#include "BaseRender.h"


BaseRender::BaseRender(std::shared_ptr<Shader> program):drawProgram(program)
{

    With_Texture = false;
    With_Geometry = false;
    Triangle_Num = 0;


    light0.position(0)=0.0f;
    light0.position(1)=0.0f;
    light0.position(2)=0.0f;


    light0.intensities(0)=1.0f;
    light0.intensities(1)=1.0f;
    light0.intensities(2)=1.0f;


}

BaseRender::~BaseRender()
{

    DeleteVerticesNormalsBuffer();
    DeleteVerticesPositionBuffer();
    DeleteUVsBuffer();

}
bool BaseRender::UploadVerticesPosition(Mesh &mesh)
{



    Triangle_Num= mesh.triangles.size();
    GLfloat *g_vertex_buffer_data = new GLfloat[Triangle_Num*3*3];

    for (int j = 0;  j < Triangle_Num;  j++)
    {

        for (int k = 0; k < 3; k++)
        {

            int v_id =  mesh.triangles[j].v_id[k];
            if (mesh.vertices.size() >v_id &&mesh.CheckFacesFlags(j,UFlag::Used))
            {
                g_vertex_buffer_data[(j * 3 + k) * 3 + 0] = (GLfloat) mesh.vertices[v_id].Mutable_X();
                g_vertex_buffer_data[(j * 3 + k) * 3 + 1] = (GLfloat) mesh.vertices[v_id].Mutable_Y();
                g_vertex_buffer_data[(j * 3 + k) * 3 + 2] = (GLfloat) mesh.vertices[v_id].Mutable_Z();

//
//                if(cnt++%10 ==0)
//                    printf("[%f %f %f] ",g_vertex_buffer_data[(j * 3 + k) * 3 + 0],g_vertex_buffer_data[(j * 3 + k) * 3 + 1],g_vertex_buffer_data[(j * 3 + k) * 3 + 2]);

            }
            else
            {
                g_vertex_buffer_data[(j * 3 + k) * 3 + 0] = 0;
                g_vertex_buffer_data[(j * 3 + k) * 3 + 1] = 0;
                g_vertex_buffer_data[(j * 3 + k) * 3 + 2] = 0;

            }
        }
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, Triangle_Num*3*3*sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete g_vertex_buffer_data;
    With_Geometry=true;

    return true;
}

bool BaseRender::UploadVerticesNormals(Mesh &mesh)
{
//
    Triangle_Num= mesh.triangles.size();
    GLfloat *g_vertex_normal_buffer_data = new GLfloat[Triangle_Num*3*3];
    for (int j = 0;  j < Triangle_Num;  j++)
    {
        for (int k = 0; k < 3; k++)
        {

            int v_id =  mesh.triangles[j].v_id[k];
            if(mesh.vertex_normals.size()>v_id &&mesh.CheckFacesFlags(j,UFlag::Used))
            {
                g_vertex_normal_buffer_data[(j*3+k)*3+0]=(GLfloat) mesh.vertex_normals[v_id].Mutable_X();
                g_vertex_normal_buffer_data[(j*3+k)*3+1]=(GLfloat) mesh.vertex_normals[v_id].Mutable_Y();
                g_vertex_normal_buffer_data[(j*3+k)*3+2]=(GLfloat) mesh.vertex_normals[v_id].Mutable_Z();
            }
            else
            {
                g_vertex_normal_buffer_data[(j*3+k)*3+0]=0;
                g_vertex_normal_buffer_data[(j*3+k)*3+1]=0;
                g_vertex_normal_buffer_data[(j*3+k)*3+2]=0;

            }
        }
    }
    glGenBuffers(1, &vno);
    glBindBuffer(GL_ARRAY_BUFFER, vno);
    glBufferData(GL_ARRAY_BUFFER, Triangle_Num*3*3*sizeof(GLfloat), g_vertex_normal_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete g_vertex_normal_buffer_data;
    With_Geometry=true;

    return true;

}
bool BaseRender::UploadUVs(Mesh &mesh)
{

    GLfloat *g_uv_buffer_data = new GLfloat[mesh.Faces().GetSize()*3*2];

    for (int f = 0;  f < mesh.Faces().GetSize();  f++)
    {

        for (int k = 0; k < 3; k++)
        {

            int face_uv_id = f*3+k;

            if(mesh.CheckFacesFlags(f,UFlag::Used))
            {
                g_uv_buffer_data[(f*3+k)*2+0]= mesh.Face_UV(face_uv_id).GetCX();
                g_uv_buffer_data[(f*3+k)*2+1]= mesh.Face_UV(face_uv_id).GetCY();

//                static int cnt = 0;
//                if(cnt++%10 ==0)
//                    printf("[%d--> %f %f] \r\n",face_uv_id,mesh.Face_UV(face_uv_id).GetCX(),mesh.Face_UV(face_uv_id).GetCY());
//

            }
            else
            {
                g_uv_buffer_data[(f*3+k)*2+0]=0;
                g_uv_buffer_data[(f*3+k)*2+1]=0;
            }

        }
    }

    glGenBuffers(1, &uvo);
    glBindBuffer(GL_ARRAY_BUFFER, uvo);
    glBufferData(GL_ARRAY_BUFFER, mesh.triangles.size()*3*2*sizeof(GLfloat), g_uv_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    delete g_uv_buffer_data;
    With_Geometry=true;

    return true;

}
bool BaseRender::UploadGeometry(Mesh &mesh)
{

    DeleteVerticesNormalsBuffer();
    DeleteVerticesPositionBuffer();

    UploadVerticesPosition(mesh);
    UploadVerticesNormals(mesh);

}
bool BaseRender::DeleteVerticesNormalsBuffer()
{

    if(vno!=0)
    {
        glDeleteBuffers(1, &vno);
        vno=0;
    }
    return true;


}
bool BaseRender::DeleteVerticesPositionBuffer()
{
    if(vbo!=0)
    {
        glDeleteBuffers(1, &vbo);
        vbo=0;
    }
    return true;


}
bool BaseRender::DeleteUVsBuffer()
{
    if(uvo!=0)
    {
        glDeleteBuffers(1, &uvo);
        uvo=0;
    }
    return true;

}


bool BaseRender::CreateVAO()
{

    //可以把同一个渲染对象的顶点数据和颜色存储在处于同一个VAO中的不同VBO中
    // – VAO  是包含一个或者多个VBOs的对象，被设计用来存储被完整渲染对象的相关数据信息，如渲染对象的顶点信息和每一个顶点的颜色信息
    // –VBO是显卡高速显存的缓冲区，用来保存顶点的信息

    // create Vertex Array Object (VAO)
    // OpenGL用来处理顶点数据的一个缓冲区对象，它不能单独使用，都是结合VBO来一起使用的
    glGenVertexArrays(1, &VertexArrayID);



}
bool BaseRender::BindVAO()
{

    //在创建VAO之后，需要使用glBindVertexArray设置它为当前操作的VAO
    glBindVertexArray(VertexArrayID);

}
bool BaseRender::UnBindVAO()
{
    glBindVertexArray(0);
}
bool BaseRender::Set_VAO_Attributes()
{



    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvo);
    glVertexAttribPointer(
            1,                                // attribute
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // 3rd attribute buffer : normals
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, vno);
    glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );


}
bool BaseRender::CreateFBO()
{

    glGenFramebuffers(1, &FramebufferName);
}

bool BaseRender::BindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

}

bool BaseRender::UnBindFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

bool BaseRender::DeleteFBO()
{

    glDeleteFramebuffers(1, &FramebufferName);

}

bool BaseRender::CreateTextureBuffer(int windowWidth, int windowHeight)
{

    glGenTextures(1, &rendered_Texture_Color);
    glBindTexture(GL_TEXTURE_2D, rendered_Texture_Color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, windowWidth, windowHeight, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    glGenTextures(1, &rendered_Texture_Depth);
    glBindTexture(GL_TEXTURE_2D, rendered_Texture_Depth);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);


    return true;
}
bool BaseRender::AttachTexture2Pipeline()
{


    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,rendered_Texture_Color , 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, rendered_Texture_Depth, 0);//optional

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    //Check for FBO completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Error! FrameBuffer is not complete" << std::endl;
        std::cin.get();
        std::terminate();
    }


}
bool BaseRender::DeleteRenderedTexture()
{
    glDeleteTextures(1,&rendered_Texture_Color);
    glDeleteTextures(1,&rendered_Texture_Depth);

}

cv::Mat BaseRender::ConvertTextureAndUvs(Mesh &mesh)
{

    // merge all texture to one image
    int max_cols=0,total_rows=0;
    std::map<std::string,Mesh::TextureType> name_mat_map;
    std::map<std::string,int> base_rows_map;

    for(int j=0; j<mesh.TexturesName().GetSize(); j++)
    {
        name_mat_map[mesh.TextureName(j)]=mesh.Texture(j);
    }

    for(std::map<std::string,Mesh::TextureType>::iterator it = name_mat_map.begin(); it != name_mat_map.end(); it++)
    {

        base_rows_map[it->first]=total_rows;
        if(it->second.Width()>max_cols)
        {
            max_cols=it->second.Width();
        }
        total_rows+=it->second.Height();
    }

//    std::cout <<"total_rows = "<<total_rows <<"  max_cols = "<<max_cols<<std::endl;

    cv::Mat all_textures = cv::Mat(total_rows,max_cols,CV_8UC4);

    int j=0;
    for(std::map<std::string,Mesh::TextureType>::iterator it = name_mat_map.begin(); it != name_mat_map.end(); it++)
    {

//        bool NeedTransparency = (it->first.find("hair_texture") != std::string::npos)||(it->first.find("eyelashes") != std::string::npos);
        bool NeedTransparency = (it->first.find("eye") != std::string::npos)||(it->first.find("eyelashes") != std::string::npos);

        cv::Mat texture =Tool::convert_ImageMatrix2CVImage(it->second.GetData());//crazy bug

//        cv::namedWindow("test",0);
//        cv::imshow("test",texture);
//        cv::waitKey(0);



        int src_changles = texture.channels();
        int dis_changles = all_textures.channels();

        cv::resize(texture,texture,cv::Size(max_cols,texture.rows));

        for(int h=0; h<texture.rows; h++)
        {

            const uchar* srcData=texture.ptr<uchar>(h);
            uchar * dstData=all_textures.ptr<uchar>(base_rows_map[it->first]+h);

            for(int x=0; x<texture.cols; x++)
            {
                dstData[dis_changles*x+0]=srcData[src_changles*x+0];
                dstData[dis_changles*x+1]=srcData[src_changles*x+1];
                dstData[dis_changles*x+2]=srcData[src_changles*x+2];

                if(dis_changles==4)
                {
                    if(NeedTransparency)
                    {
                        dstData[dis_changles*x+3] = srcData[src_changles*x+3]*10;
                        continue;
                    }

                }
                dstData[dis_changles*x+3] = 255;


            }
        }
        j++;

    }

    /**
     * convert uv coordinates
     */
    for(int f=0; f<mesh.Faces().GetSize(); f++)
    {

        int texture_id = mesh.FaceMateriaID(f);
//        std::cout <<"f="<<f<<" texture_id ="<<texture_id <<std::endl;

        if(texture_id >= mesh.TexturesName().size())
        {
//            std::cerr<<" texture_id >= mesh.Textures().size() texture_id ="<<texture_id<<" mesh.TexturesName().size()= "<<mesh.TexturesName().size()<<std::endl;
            continue;
        }

        for(int k=0; k<3; k++)
        {
            int face_uv_id = f *3 +k;


            float ux= mesh.Face_UV(face_uv_id).Mutable_X();
            float uy= mesh.Face_UV(face_uv_id).Mutable_Y();


            int base_row = base_rows_map[mesh.TextureName(texture_id)];
            uy = (float)(uy*mesh.Texture(texture_id).Height()+base_row)/all_textures.rows;

            mesh.Face_UV(face_uv_id).Mutable_X() = ux;
            mesh.Face_UV(face_uv_id).Mutable_Y() = uy;



        }



    }
    return all_textures;

}

bool BaseRender::DeleteTexture()
{

    if(ImageTextures!=NULL)
    {
        delete(ImageTextures);
        ImageTextures=NULL;
    }

}
bool BaseRender::UploadTexture(Mesh &mesh)
{

    cv::Mat Texture = ConvertTextureAndUvs(mesh);
    this->DeleteTexture();
    ImageTextures = new GlTexture(Texture.cols, Texture.rows, GL_RGBA, true, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    ImageTextures->Upload(Texture.data, GL_RGBA, GL_UNSIGNED_BYTE);

    With_Texture=true;
    this->UploadUVs(mesh);

    return true;
}



bool BaseRender::ShaderRendering(crazy::DMatrix project_matrix, const char *render_mode)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Eigen::Matrix4f ProjectionModelViewMatrix;
    for(int j=0; j<4; j++)
    {
        for(int i=0; i<4; i++)
        {
            ProjectionModelViewMatrix(i,j) = project_matrix.Get(i,j);
        }
    }

    drawProgram->Bind();
    drawProgram->setUniform(Uniform("ProjectionModelViewMatrix", ProjectionModelViewMatrix));
    drawProgram->setUniform(Uniform("light.position", light0.position));
    drawProgram->setUniform(Uniform("light.intensities", light0.intensities));

    /////////////// vertex ////////////////
    int vertex_location_id = 0;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(vertex_location_id);
    glVertexAttribPointer(
        vertex_location_id, // attribute. No particular reason for *, but must match the layout in the shader.
        3,                  // size x+y+z->3
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        0            // array buffer offset
    );



    ///////3rd attribute buffer : normals ///////
    int v_normals_location_id = 1;
    glBindBuffer(GL_ARRAY_BUFFER, vno);
    glEnableVertexAttribArray(v_normals_location_id);
    glVertexAttribPointer(
        v_normals_location_id,            // attribute. No particular reason for *, but must match the layout in the shader.
        3,                                // size :  x+y+z->3
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        0                                 // array buffer offset
    );


    int uv_location_id = 2;
    if(With_Texture==true)
    {

        /////////////// texture ////////////////
        ///////　bind texture id and texture 绑////////
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ImageTextures->tid);
        GLint texLoc  = glGetUniformLocation(drawProgram->programId(), "Texture");
        glUniform1i(texLoc, 0);

        ///////2nd attribute buffer : UVs///////

        glBindBuffer(GL_ARRAY_BUFFER, uvo);
        glEnableVertexAttribArray(uv_location_id);
        glVertexAttribPointer(
            uv_location_id,                   // attribute. No particular reason for *, but must match the layout in the shader.
            2,                                // size : U+V -> 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            0                                 // array buffer offset
        );
    }


    glEnable(GL_BLEND);
//    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//--------------------draw start-------------------------------//

    std::string Drawing_mode = render_mode;

    if(Drawing_mode == "Points")//     Points
    {

        glDrawArrays(GL_POINTS, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num
    }
    else if(Drawing_mode == "Triangles")     // Triangles
    {
        glDrawArrays(GL_TRIANGLES, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num
    }
    else if(Drawing_mode == "Wired")        //Wired frame
    {
        glLineWidth(0.1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

//---------------------draw end------------------------------//


    //vertex
    glDisableVertexAttribArray(vertex_location_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //vertex normals
    glDisableVertexAttribArray(v_normals_location_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(With_Texture==true)
    {
        //texture uv
        glDisableVertexAttribArray(uv_location_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glDisable(GL_BLEND);
    drawProgram->Unbind();

    return  true;

}
bool BaseRender::ShaderRendering_Test(crazy::DMatrix project_matrix, const char *render_mode)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Eigen::Matrix4f ProjectionModelViewMatrix;
    for(int j=0; j<4; j++)
    {
        for(int i=0; i<4; i++)
        {
            ProjectionModelViewMatrix(i,j) = project_matrix.Get(i,j);
        }
    }

    drawProgram->Bind();
    drawProgram->setUniform(Uniform("ProjectionModelViewMatrix", ProjectionModelViewMatrix));
    drawProgram->setUniform(Uniform("light.position", light0.position));
    drawProgram->setUniform(Uniform("light.intensities", light0.intensities));

    /////////////// vertex ////////////////
    int vertex_location_id = 0;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(vertex_location_id);
    glVertexAttribPointer(
            vertex_location_id, // attribute. No particular reason for *, but must match the layout in the shader.
            3,                  // size x+y+z->3
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            0            // array buffer offset
    );



    ///////3rd attribute buffer : normals ///////
    int v_normals_location_id = 1;
    glBindBuffer(GL_ARRAY_BUFFER, vno);
    glEnableVertexAttribArray(v_normals_location_id);
    glVertexAttribPointer(
            v_normals_location_id,            // attribute. No particular reason for *, but must match the layout in the shader.
            3,                                // size :  x+y+z->3
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            0                                 // array buffer offset
    );


    int uv_location_id = 2;
    if(With_Texture==true)
    {

        /////////////// texture ////////////////
        ///////　bind texture id and texture 绑////////
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ImageTextures->tid);
        GLint texLoc  = glGetUniformLocation(drawProgram->programId(), "Texture");
        glUniform1i(texLoc, 0);

        ///////2nd attribute buffer : UVs///////

        glBindBuffer(GL_ARRAY_BUFFER, uvo);
        glEnableVertexAttribArray(uv_location_id);
        glVertexAttribPointer(
                uv_location_id,                   // attribute. No particular reason for *, but must match the layout in the shader.
                2,                                // size : U+V -> 2
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                0                                 // array buffer offset
        );
    }


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//--------------------draw start-------------------------------//

    std::string Drawing_mode = render_mode;

    if(Drawing_mode == "Points")//     Points
    {

        glDrawArrays(GL_POINTS, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num
    }
    else if(Drawing_mode == "Triangles")     // Triangles
    {
        glDrawArrays(GL_TRIANGLES, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num
    }
    else if(Drawing_mode == "Wired")        //Wired frame
    {
        glLineWidth(0.1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, Triangle_Num*3); // Triangle_Num*3 = vertex num
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

//---------------------draw end------------------------------//


    //vertex
    glDisableVertexAttribArray(vertex_location_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //vertex normals
    glDisableVertexAttribArray(v_normals_location_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(With_Texture==true)
    {
        //texture uv
        glDisableVertexAttribArray(uv_location_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glDisable(GL_BLEND);
    drawProgram->Unbind();

    return  true;

}

cv::Mat BaseRender::GetColorTexture(crazy::DMatrix project_matrix, const char *render_mode, int windowWidth,int windowHeight)
{



    int width=windowWidth, height = windowHeight;
    unsigned char* color_buffer = new unsigned char[width*height*3];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, color_buffer);
    cv::Mat color_image(height, width, CV_8UC3, color_buffer);

    cv::flip(color_image,color_image,0);
    cv::cvtColor(color_image,color_image,cv::COLOR_RGB2BGR);

    return color_image;
}
cv::Mat BaseRender::GetDepthTexture(crazy::DMatrix project_matrix, const char *render_mode, int windowWidth,int windowHeight)
{



    int width=windowWidth, height = windowHeight;

    float* depth_buffer = new float[width*height];
    glReadnPixels( 0, 0, width, height, GL_DEPTH_COMPONENT, GL_FLOAT,width*height, &depth_buffer);
    cv::Mat image_depth(height, width, CV_32FC1, depth_buffer);



    return image_depth;
}
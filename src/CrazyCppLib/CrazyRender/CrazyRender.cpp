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

#include "CrazyRender.h"
namespace crazy
{



/////////////////////////////////////////////////////////////
CrazyRender::CrazyRender(std::shared_ptr<Shader> program):BaseRender(program)
{


}
CrazyRender::~CrazyRender()
{

}
bool CrazyRender::Update(Mesh &mesh)
{

    this->UploadTexture(mesh);
    this->UploadGeometry(mesh);

}
bool CrazyRender::UpdateTexture(Mesh &mesh)
{
    this->UploadTexture(mesh);

}
bool CrazyRender::UpdateGe(Mesh &mesh)
{
    this->UploadGeometry(mesh);
}
bool CrazyRender::Rendering(crazy::DMatrix project_matrix, const char *render_mode)
{


    // draw to show on origin windows
    ShaderRendering(project_matrix,render_mode);

    this->CreateFBO();
    this->BindFBO();
    this->CreateTextureBuffer(640,480);
    this->AttachTexture2Pipeline();


    glViewport(0,0,640,480); //set draw area for your model
    // draw to texture
    ShaderRendering(project_matrix,render_mode);

    cv::Mat color_texture = this->GetColorTexture(project_matrix,render_mode,640,480);
    cv::Mat depth_texture = this->GetDepthTexture(project_matrix,render_mode,640,480);

    this->UnBindFBO();
    this->DeleteFBO();
    this->DeleteRenderedTexture();


//    cv::namedWindow("color_texture",0);
//    cv::imshow("color_texture",color_texture);
//
////    cv::namedWindow("rendered_texture",0);
////    cv::imshow("rendered_texture",depth_texture);
//    cv::waitKey(1);


//

}

}


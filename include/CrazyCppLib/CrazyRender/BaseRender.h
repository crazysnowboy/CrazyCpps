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

#ifndef BaseRender_H_
#define BaseRender_H_

#include "Shaders.h"

#include "GlTexture.h"

#include "Uniform.h"
#include "Eigen/Eigen"
#include "Mesh.h"
#include "Defines.h"
#include <zconf.h>
#include "crazy_tools.h"
#include "CMatrix.hpp"
struct myLight
{
    Eigen::Vector3f position;  // the position of the light  4x4 matrix
    Eigen::Vector3f intensities; //the color of the light  4x4 matrix
};


////////////////////
class BaseRender
{
public:


    myLight light0;

    BaseRender(std::shared_ptr<Shader> program);
    ~BaseRender();

    // texture
    cv::Mat ConvertTextureAndUvs(Mesh &mesh);
    bool UploadTexture(Mesh &mesh);
    bool DeleteTexture();


    bool UploadVerticesPosition(Mesh &mesh);
    bool UploadVerticesNormals(Mesh &mesh);

    bool UploadUVs(Mesh &mesh);

    bool UploadGeometry(Mesh &mesh);

    bool DeleteVerticesPositionBuffer();
    bool DeleteVerticesNormalsBuffer();
    bool DeleteUVsBuffer();

public:
    bool Set_VAO_Attributes();

    bool CreateVAO();
    bool BindVAO();
    bool UnBindVAO();

    bool CreateFBO();
    bool BindFBO();
    bool UnBindFBO();
    bool DeleteFBO();

    bool CreateTextureBuffer(int windowWidth, int windowHeight);
    bool AttachTexture2Pipeline();
    bool DeleteRenderedTexture();

public:

    bool ShaderRendering(crazy::DMatrix project_matrix, const char *render_mode);
    bool ShaderRendering_Test(crazy::DMatrix project_matrix, const char *render_mode);

    cv::Mat GetColorTexture(crazy::DMatrix project_matrix, const char *render_mode,int windowWidth, int windowHeight);
    cv::Mat GetDepthTexture(crazy::DMatrix project_matrix, const char *render_mode,int windowWidth, int windowHeight);

private:

    GLuint VertexArrayID=0;
    GLuint FramebufferName=0;
    GLuint rendered_Texture_Color=0;
    GLuint rendered_Texture_Depth=0;

private:
    GLuint vbo=0;
    GLuint tid=0;
    GLuint vno=0;  //vertex normal
    GLuint uvo=0;

    int Triangle_Num;
    std::shared_ptr<Shader> drawProgram;
    GlTexture* ImageTextures = NULL;

    bool With_Geometry;
    bool With_Texture;



};

#endif /* FEEDBACKBUFFER_H_ */

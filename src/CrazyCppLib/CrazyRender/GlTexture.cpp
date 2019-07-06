//
// Created by collin on 18-11-9.
//

#include "GlTexture.h"



GlTexture::GlTexture(GLint width, GLint height, GLint internal_format, bool sampling_linear, int border, GLenum glformat, GLenum gltype, GLvoid* data )
    : internal_format(0), tid(0)
{
    Reinitialise(width,height,internal_format,sampling_linear,border,glformat,gltype,data);
}


GlTexture::~GlTexture()
{
    // We have no GL context whilst exiting.
    if(internal_format!=0 )
    {
        glDeleteTextures(1,&tid);
    }
}

void GlTexture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, tid);
}

void GlTexture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GlTexture::Reinitialise(GLsizei w, GLsizei h, GLint int_format, bool sampling_linear, int border, GLenum glformat, GLenum gltype, GLvoid* data )
{
    if(tid!=0)
    {
        glDeleteTextures(1,&tid);
    }

    internal_format = int_format;
    width = w;
    height = h;

    glGenTextures(1,&tid);
    Bind();

    // GL_LUMINANCE and GL_FLOAT don't seem to actually affect buffer, but some values are required
    // for call to succeed.
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, border, glformat, gltype, data);

    if(sampling_linear)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

void GlTexture::Upload(const void* data, GLenum data_format, GLenum data_type)
{
    Bind();
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,data_format,data_type,data);
}



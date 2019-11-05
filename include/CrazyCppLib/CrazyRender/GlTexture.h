//
// Created by collin on 18-11-9.
//

#ifndef CRAZY_PICKER_GLTEXTURE_H
#define CRAZY_PICKER_GLTEXTURE_H

#include "GL/gl.h"
#include <string>
class  GlTexture
{
public:
    //! internal_format normally one of GL_RGBA8, GL_LUMINANCE8, GL_INTENSITY16
    GlTexture(GLint width, GLint height, GLint internal_format = GL_RGBA8, bool sampling_linear = true, int border = 0, GLenum glformat = GL_RGBA, GLenum gltype = GL_UNSIGNED_BYTE, GLvoid* data = NULL  );


    virtual ~GlTexture();


    //! Reinitialise teture width / height / format
    virtual void Reinitialise(GLsizei width, GLsizei height, GLint internal_format = GL_RGBA8, bool sampling_linear = true, int border = 0, GLenum glformat = GL_RGBA, GLenum gltype = GL_UNSIGNED_BYTE,
                              GLvoid* data = NULL );

    void Bind() const;
    void Unbind() const;

    //! data_layout normally one of GL_LUMINANCE, GL_RGB, ...
    //! data_type normally one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_FLOAT
    void Upload(const void* image, GLenum data_format = GL_LUMINANCE, GLenum data_type = GL_FLOAT);




    GLint internal_format;
    GLuint tid;
    GLint width;
    GLint height;

};

#endif //CRAZY_PICKER_GLTEXTURE_H

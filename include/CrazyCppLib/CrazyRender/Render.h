

#ifndef MESHPRO_RENDER_H
#define MESHPRO_RENDER_H
#include "BaseRender.h"

namespace crazy
{
class Render
{
public:

    virtual bool Update(Mesh &mesh) =0;
    virtual bool UpdateTexture(Mesh &mesh) = 0;
    virtual bool UpdateGe(Mesh &mesh) = 0;
    virtual bool Rendering(crazy::DMatrix project_matrix,const char *render_mode) = 0;

};

}

#endif //MESHPRO_RENDER_H

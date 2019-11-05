

#ifndef CRAZY_MESH_H
#define CRAZY_MESH_H

#include "CMesh.h"
class Mesh:public CMesh
{
public:

    Mesh()
    {

    }
    ~Mesh()
    {

    }
    bool IsEmpty()
    {
        if(Vertices().GetSize()==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    void clear()
    {

        Vertices().clear();
        VertexFlags().clear();

        FaceFlags().clear();
        Faces().clear();

        Landmarks().clear();

        V_Normals().clear();
        F_Normals().clear();

        Textures().clear();
        Vertex_UVS().clear();
        Face_UVS().clear();

        TexturesName().clear();

        FaceMateriaIDs().clear();
        Origin_UVS().clear();
        FaceUVIDs().clear();
        StoredPts().clear();



    }
    CMesh& add_mesh(CMesh m)
    {
        *this += m;
        return *this;
    }

    CMesh& operator+=(CMesh m)
    {

        int Base_n_vertices =Vertices().GetSize();
        int Base_n_faces =Faces().GetSize();
        int Base_n_textures = TexturesName().size();
        //faces and face flags
        for(int f=0; f<m.Faces().GetSize(); f++)
        {

            Mesh::TriangleType t_id = m.Face(f);
            for(int k=0; k<3; k++)
            {
                t_id.v_id[k]+=Base_n_vertices;
            }

            FaceFlags().Add(m.FaceFlag(f));

//            if (m.FaceMateriaID(f)<0)
//                std::cerr <<"m.FaceMateriaID(f) = "<<m.FaceMateriaID(f)<<std::endl;
//
            FaceMateriaIDs()[Base_n_faces+f] = Base_n_textures + m.FaceMateriaID(f);
            Faces().Add(t_id);

        }
        // face uvs
        for(int f=0; f< m.Faces().GetSize(); f++)
        {
            for(int k=0; k<3; k++)
            {
                int face_uv_id = f*3+k;
                Face_UVS().Add(m.Face_UV(face_uv_id).GetCX(),m.Face_UV(face_uv_id).GetCY());
            }


        }

        //vertices
        for(int v=0; v< m.Vertices().GetSize(); v++)
        {
            Vertices().Add(m.Vertex(v).GetCX(),m.Vertex(v).GetCY(),m.Vertex(v).GetCZ());
            VertexFlags().Add(m.VertexFlag(v));

        }

        //normals
        for(int n=0; n<m.V_Normals().GetSize(); n++)
        {
            V_Normals().Add(m.V_Normal(n).GetCX(),m.V_Normal(n).GetCY(),m.V_Normal(n).GetCZ());
        }


        // textures
        for(int t=0; t<m.TexturesName().GetSize(); t++)
        {
            bool res =  Textures().Insert(m.TextureName(t),m.Texture(t).clone());
            if(res== false)
            {
                std::cerr <<"texture  name conflict "<<m.TextureName(t)<<std::endl;
            }


        }
        // textures name
        for(int a=0; a<m.TexturesName().GetSize(); a++)
        {
            TexturesName().Add(m.TextureName(a));

        }

        // landmarks_index
        for(int a=0; a<m.Landmarks().GetSize(); a++)
        {
            Landmarks().Add(m.Landmarks().Get(a)+Base_n_vertices);

        }



        return *this;


    }

};




#endif //CRAZY_MESH_H

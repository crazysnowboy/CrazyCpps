

#ifndef CRAZY_CMesh_H
#define CRAZY_CMesh_H
#include <vector>
#include <map>
#include "utilities/CrazyLog.hpp"
#include "CPoint2D.h"
#include "CPoint3D.h"
#include "CArray.hpp"
#include <fstream>
#include "cereal/mat_cerealisation.hpp"
#include "cereal/cereal.hpp"
#include "cereal/access.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/archives/binary.hpp"
#include "CMatrix.hpp"

namespace crazy
{
class TripletID
{
public:
    TripletID()
    {

    }
    TripletID(int id0,int id1,int id2)
    {
        v_id[0] = id0;
        v_id[1] = id1;
        v_id[2] = id2;

    }
    int Id0()
    {
        return v_id[0];
    };
    int Id1()
    {
        return v_id[1];
    };
    int Id2()
    {
        return v_id[2];
    };

    int Id(int idx)
    {
        return v_id[idx];

    }
public:
    int v_id[3];
};

class RGB
{
public:
    float R;
    float G;
    float B;
public:
    RGB(float r,float g,float b)
    {
        R = r;
        G = g;
        B = b;
    };

};



namespace UFlag
{
enum Flag
{
    NON        = 0x00,
    Used       = 0x01,
    Selected   = 0x02,
    IsEdge     = 0x04,
    Corresponding=0x08

};
}
using namespace UFlag;


class CMeshData
{
public:

    cv::Mat Vertices_MAT;
    cv::Mat Vertices_UV_MAT;

    CArray<cv::Mat> Faces_MAT;
    CArray<cv::Mat> Faces_UV_MAT;
    CArray<cv::Mat> textures_MAT;


    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& archive, const std::uint32_t version)
    {
        archive(
            Vertices_MAT,
            Faces_MAT,
            Vertices_UV_MAT,
            Faces_UV_MAT,
            textures_MAT

        );

    };

    bool load_model(std::string filename)
    {

        std::ifstream file(filename, std::ios::binary);
        if (file.fail())
        {
            throw std::runtime_error("Error opening given file: " + filename);
        }
        cereal::BinaryInputArchive input_archive(file);
        input_archive((*this));

        return true;
    };
    bool load_model(std::istream* dataStream)
    {
        cereal::BinaryInputArchive input_archive((*dataStream));
        input_archive((*this));

        return true;
    };


    bool save_model(std::string filename)
    {
        std::ofstream file(filename, std::ios::binary);
        cereal::BinaryOutputArchive output_archive(file);
        output_archive((*this));
        return true;
    };


};


class CTexture
{
public:

    CTexture()
    {
    }
    ~CTexture()
    {
    }
    CTexture(ImageMatrix mat_data_int)
    {
        mat_data = mat_data_int;
    }

    int Width()
    {
        return mat_data.cols();

    }
    int Height()
    {
        return mat_data.rows();
    }
    bool empty()
    {
        bool empty = (mat_data.rows()==0||mat_data.cols()==0);
        return empty;
    }
    bool operator =(const ImageMatrix mat_data_int)
    {
        mat_data = mat_data_int;
        return true;
    }

    CTexture clone()
    {
        CTexture tex(mat_data);
        return tex;
    }
    ImageMatrix GetData()
    {
        return mat_data;
    }

private:
    ImageMatrix mat_data;

};


class CMesh
{
public:

    CMesh()
    {
    }
    ~CMesh()
    {

    }


public:

    typedef TripletID TriangleType;
    typedef CArray<TriangleType> TrianglesType;

    typedef TripletID FaceUVIDType;
    typedef CArray<FaceUVIDType> FaceUVSIDType;


    typedef CArray<int> VertexIndexType;
    typedef std::map<int,int> FaceToMateriaIDsMapType;
    typedef CArray<RGB> IndexColorType;


    typedef  CArray<Flag> VFlagsType;
    typedef  CArray<Flag> FFlagsType;

    typedef  CPoint3D<float> point_3d;
    typedef  CPoint2D<float> point_2d;

    typedef  point_3d VertexType;
    typedef  point_3d NormalType;
    typedef  point_2d UVType;


private:
    class CVertexArray3D:public CArray<VertexType>
    {
    public:

        bool Add(VertexType pt)
        {
            return CArray::Add(pt);
        }

        bool Add(float x,float y,float z)
        {
            point_3d pt(x,y,z);
            this->push_back(pt);

            return true;

        }
        bool Set(int id,float x,float y,float z)
        {
            if(id<this->GetSize())
            {
                point_3d pt(x,y,z);
                this->at(id) = pt;
                return true;
            }
            else
            {
                std::cerr <<"crazy log: id number > array size"<<std::endl;
                return false;
            }
        }

        CVertexArray3D& operator+=(VertexType p)
        {
            try
            {
                //vertices
                for(int v=0; v< this->GetSize(); v++)
                {
                    this->Get(v).Mutable_X()+=p.GetCX();
                    this->Get(v).Mutable_Y()+=p.GetCY();
                    this->Get(v).Mutable_Z()+=p.GetCZ();
                }

                return *this;
            }
            catch (const std::exception& e)
            {
                error(e.what(), __LINE__, __FUNCTION__, __FILE__);
                return *this;
            }
        }
        CVertexArray3D& operator*=(float s)
        {
            try
            {
                //vertices
                for(int v=0; v< this->GetSize(); v++)
                {
                    this->Get(v).Mutable_X()*=s;
                    this->Get(v).Mutable_Y()*=s;
                    this->Get(v).Mutable_Z()*=s;
                }

                return *this;
            }
            catch (const std::exception& e)
            {
                error(e.what(), __LINE__, __FUNCTION__, __FILE__);
                return *this;
            }
        }
        CVertexArray3D& operator/=(float s)
        {
            try
            {
                //vertices
                for(int v=0; v< this->GetSize(); v++)
                {
                    this->Get(v).Mutable_X()/=s;
                    this->Get(v).Mutable_Y()/=s;
                    this->Get(v).Mutable_Z()/=s;
                }

                return *this;
            }
            catch (const std::exception& e)
            {
                error(e.what(), __LINE__, __FUNCTION__, __FILE__);
                return *this;
            }
        }
        CVertexArray3D& operator-=(VertexType p)
        {
            try
            {
                //vertices
                for(int v=0; v< this->GetSize(); v++)
                {
                    this->Get(v).Mutable_X()-=p.GetCX();
                    this->Get(v).Mutable_Y()-=p.GetCY();
                    this->Get(v).Mutable_Z()-=p.GetCZ();
                }

                return *this;
            }
            catch (const std::exception& e)
            {
                error(e.what(), __LINE__, __FUNCTION__, __FILE__);
                return *this;
            }
        }
    };

    class CNormalArray3D:public CArray<NormalType>
    {
    public:

        bool Add(NormalType pt)
        {
            return CArray::Add(pt);
        }

        bool Add(float x,float y,float z)
        {
            point_3d pt(x,y,z);
            CArray::Add(pt);

            return true;
        }

        bool Set(int id,float x,float y,float z)
        {
            if(id<this->GetSize())
            {
                point_3d pt(x,y,z);
                this->at(id) = pt;
                return true;
            }
            else
            {
                std::cerr <<"crazy log: id number > array size"<<std::endl;
                return false;
            }
        }

        CNormalArray3D& operator+=(NormalType p)
        {
            try
            {
                //vertices
                for(int v=0; v< this->GetSize(); v++)
                {
                    this->Get(v).Mutable_X()+=p.GetCX();
                    this->Get(v).Mutable_Y()+=p.GetCY();
                    this->Get(v).Mutable_Z()+=p.GetCZ();
                }

                return *this;
            }
            catch (const std::exception& e)
            {
                error(e.what(), __LINE__, __FUNCTION__, __FILE__);
                return *this;
            }
        }
    };

    class CGArray2D:public CArray<UVType>
    {
    public:


        bool Add(float x,float y)
        {
            point_2d pt(x,y);
            this->push_back(pt);

            return true;
        }
        bool Set(int id,float x,float y)
        {
            if(id<this->GetSize())
            {
                point_2d pt(x,y);
                this->at(id) = pt;
                return true;
            }
            else
            {
                std::cerr<<"crazy log: id number > array size"<<std::endl;
                return false;

            }

        }
    };


public:


    typedef  CVertexArray3D VsType;
    typedef  CNormalArray3D NsType;
    typedef  CGArray2D UVsType;

    typedef CTexture TextureType;
    typedef std::string NameType;

    typedef CArray<TextureType> TexturesType;
    typedef CArray<NameType> TexturesNameType;
private:
    class N2T
    {

    public:

        typedef std::map<NameType,TextureType>::iterator Iter_ptr;


    public:

        bool operator =(N2T name2texture_map)
        {
            map_data = name2texture_map.map_data;
        }
        TextureType operator [](NameType name)
        {
            return map_data[name];
        }
        bool Set(NameType n,TextureType t)
        {
            map_data[n]=t;
            return true;
        }
        bool Insert(NameType n,TextureType t)
        {

            std::pair<std::map<NameType, TextureType>::iterator, bool> ret = map_data.insert(std::pair<NameType,TextureType>(n,t));

            return ret.second;
        }
        TextureType Get(NameType n)
        {
            return map_data[n];
        }
        int size()
        {
            return map_data.size();
        }
        bool clear()
        {
            map_data.clear();
        }
        int GetSize()
        {
            return size();
        }
        Iter_ptr Begin()
        {
            return map_data.begin();
        }
        Iter_ptr End()
        {
            return map_data.end();
        }

        std::map<NameType,TextureType> & Map()
        {
            return map_data;
        };


    private:

        std::map<NameType,TextureType> map_data;



    };

public:
    typedef N2T Name2TextureType;


public:
    TrianglesType& Faces()
    {
        return triangles;
    }


    TriangleType& Face(int id)
    {
//            printf("face id = %d \r\n",id);
        if(id<triangles.size())
        {
            return triangles[id];
        }
        else
        {
            error("crazy log :id > triangles size %d vs %d ",__LINE__,__FUNCTION__,__FILE__);
        }
    }

    FaceUVSIDType& FaceUVIDs()
    {
        return faceuvs_id;
    }
    FaceUVIDType& FaceUVID(int id)
    {
//            printf("face id = %d \r\n",id);
        if(id<faceuvs_id.size())
        {
            return faceuvs_id[id];
        }
    }


    FaceToMateriaIDsMapType& FaceMateriaIDs()
    {
        return face_to_materia_id;
    }

    int& FaceMateriaID(int idx)
    {
        return face_to_materia_id[idx];
    }



    bool CheckVerticesFlags(int v_id, Flag flag)
    {
        if (verticesFlag.size()>v_id)
        {
            return 0!=(verticesFlag[v_id] & flag);
        }
        else
        {
            error("verticesFlag.size() <=v_id",__LINE__,__FUNCTION__,__FILE__);
        }
        return false;
    }

    void SetVerticesFlags(int v_id, Flag flag)
    {
        if (verticesFlag.size() <= v_id)
        {
            for (size_t j = verticesFlag.size(); j < v_id+1; j++)
            {
                verticesFlag.push_back(UFlag::NON);
            }
        }
//            verticesFlag[v_id] = (Flag)(verticesFlag[v_id]|flag);
        verticesFlag[v_id] = flag;
    }

    bool CheckFacesFlags(int f_id, Flag flag,int phase=1)
    {
        if(trianglesFlag.size()>f_id)
        {
            if(phase == 1)
            {
                return trianglesFlag[f_id] & flag
                       &&(CheckVerticesFlags(Face(f_id).v_id[0],flag)
                          ||CheckVerticesFlags(Face(f_id).v_id[1],flag)
                          ||CheckVerticesFlags(Face(f_id).v_id[2],flag))
                       ;
            }
            else if(phase ==2)
            {
                return trianglesFlag[f_id] & flag
                       &&(CheckVerticesFlags(Face(f_id).v_id[0],flag)
                          &&CheckVerticesFlags(Face(f_id).v_id[1],flag)
                          &&CheckVerticesFlags(Face(f_id).v_id[2],flag))
                       ;
            }


        }
        else
        {
            error("trianglesFlag.size()<=f_id",__LINE__,__FUNCTION__,__FILE__);
        }
        return false;
    }

    void SetFacesFlags(int f_id, Flag flag)
    {

        if(trianglesFlag.size() <= f_id)
        {
            error("trianglesFlag.size() <= f_id",__LINE__,__FUNCTION__,__FILE__);

        }

        if(flag != NON)
        {
            trianglesFlag[f_id] = (Flag)(trianglesFlag[f_id]|flag);
        }
        else
        {
            trianglesFlag[f_id] = NON;
        }
    }

    Flag& FaceFlag(int f_id)
    {
        return trianglesFlag[f_id];
    }
    Flag& VertexFlag(int v_id)
    {
        return verticesFlag[v_id];
    }

    VFlagsType& FaceFlags()
    {
        return trianglesFlag;
    }
    VFlagsType& VertexFlags()
    {
        return verticesFlag;
    }


    VsType &Vertices()
    {
        return vertices;
    }
    VsType &StoredPts()
    {
        return stored_pts;
    }

    NsType &V_Normals()
    {
        return vertex_normals;
    }
    NsType &F_Normals()
    {
        return face_normals;
    }

    VertexType &Vertex(int id)
    {
        return vertices.Get(id);
    };
    NormalType &V_Normal(int id)
    {
        return vertex_normals.Get(id);
    }
    NormalType &F_Normal(int id)
    {
        return face_normals.Get(id);
    }



    UVsType& Vertex_UVS()
    {
        return vertices_uv;
    }


    UVType& Vertex_UV(int idx)
    {
        return vertices_uv.Get(idx);
    }


    UVsType& Origin_UVS()
    {
        return origin_uv;
    }
    UVType& Origin_UV(int idx)
    {
        return origin_uv.Get(idx);
    }


    UVsType& Face_UVS()
    {
        return face_uv;
    }

    UVType& Face_UV(int idx)
    {
        if(idx<face_uv.GetSize())
        {
            return  face_uv.Get(idx);
        }
        else if(idx<faceuvs_id.GetSize())
        {
            int index = idx%3;
            int uv_id = faceuvs_id.Get(idx).v_id[index];
            return vertices_uv.Get(uv_id);
        }
    }


    Name2TextureType& Textures()
    {
        return  name_texture;
    }

    TextureType Texture(int id)
    {
        if(id<texture_names.GetSize())
        {
            return  name_texture.Get(texture_names.Get(id));
        }
        else
        {
            std::cerr << " id > textures size " <<std::endl;
        }
    };

    TexturesNameType& TexturesName()
    {
        return  texture_names;
    }
    NameType& TextureName(int idx)
    {
        return  texture_names.Get(idx);
    }
    VertexIndexType& Landmarks()
    {
        return  landmarks_index;
    }

public:
    DMatrix GetFacesMat(void)
    {
        DMatrix faces_mat(Faces().GetSize(),3,0);
        for(int j=0; j<Faces().GetSize(); j++)
        {
            faces_mat.Set(j,0,Faces().Get(j).Id0());
            faces_mat.Set(j,1,Faces().Get(j).Id1());
            faces_mat.Set(j,2,Faces().Get(j).Id2());
        }
        return faces_mat;
    }

    DMatrix GetVerticesMat(void)
    {
        DMatrix vertices_mat(Vertices().GetSize(),3,0.0);
        for(int j=0; j<Vertices().GetSize(); j++)
        {
            vertices_mat.Set(j,0,Vertices().Get(j).GetCX());
            vertices_mat.Set(j,1,Vertices().Get(j).GetCY());
            vertices_mat.Set(j,2,Vertices().Get(j).GetCZ());
        }
        return vertices_mat;
    }

    DMatrix GetStoredPointMat(void)
    {
        DMatrix stroed_pts_mat(StoredPts().GetSize(),3,0.0);
        for(int j=0; j<StoredPts().GetSize(); j++)
        {
            stroed_pts_mat.Set(j,0,StoredPts().Get(j).GetCX());
            stroed_pts_mat.Set(j,1,StoredPts().Get(j).GetCY());
            stroed_pts_mat.Set(j,2,StoredPts().Get(j).GetCZ());
        }
        return stroed_pts_mat;
    }

    DMatrix GetVertexUVsMat(void)
    {
        DMatrix v_uvs_mat(Vertex_UVS().GetSize(),2,0.0);
        for(int j=0; j<Vertex_UVS().GetSize(); j++)
        {
            v_uvs_mat.Set(j,0,Vertex_UVS().Get(j).GetCX());
            v_uvs_mat.Set(j,1,Vertex_UVS().Get(j).GetCY());
        }
        return  v_uvs_mat;
    }
    DMatrix GetVertexNormalsMat(void)
    {
        DMatrix v_nor_mat(V_Normals().GetSize(),3,0.0);
        for(int j=0; j<V_Normals().GetSize(); j++)
        {
            v_nor_mat.Set(j,0,V_Normals().Get(j).GetCX());
            v_nor_mat.Set(j,1,V_Normals().Get(j).GetCY());
            v_nor_mat.Set(j,2,V_Normals().Get(j).GetCZ());
        }
        return  v_nor_mat;
    }
    DMatrix GetFacesUVsMat(void)
    {
        DMatrix f_uvs_mat(Face_UVS().GetSize(),2,0.0);
        for(int j=0; j<Face_UVS().GetSize(); j++)
        {
            f_uvs_mat.Set(j,0,Face_UVS().Get(j).GetCX());
            f_uvs_mat.Set(j,1,Face_UVS().Get(j).GetCY());
        }
        return  f_uvs_mat;
    }

    DMatrix GetLandmarks(void)
    {
        DMatrix L_mat(Landmarks().GetSize(),1,0);
        for(int j=0; j<Landmarks().GetSize(); j++)
        {
            L_mat.Set(j,0,Landmarks().Get(j));

        }
        return L_mat;
    }

    int GetTextures_Size(void)
    {
        return Textures().GetSize();
    }
    int GetTextureNames_Size(void)
    {
        return TexturesName().GetSize();
    }

    TextureType GetTexture(int j)
    {
        if(j<GetTextures_Size())
        {
            return Texture(j);
        }
        else
        {
            std::cerr <<"index out of range"<<std::endl;

        }
    }

    std::string GetTextureName(int j)
    {

        if(j<GetTextureNames_Size())
        {
            return TexturesName().Get(j).c_str();
        }
        else
        {
            std::cerr <<"index out of range"<<std::endl;

        }
        return "";
    }


public:

    bool SetLandmarks(DMatrix l_mat)
    {
        assert(l_mat.cols() == 1);

        Landmarks().clear();
        for(int j=0; j<l_mat.rows(); j++)
        {
            int v_id = (int)(l_mat.Get(j,0));
            Landmarks().Add(v_id);
        }
        return true;
    }
    bool SetFacesMat(DMatrix faces_mat)
    {

        assert(faces_mat.cols() == 3);

        Faces().clear();
        for(int j=0; j<faces_mat.rows(); j++)
        {
            TriangleType f(faces_mat.Get(j,0),
                           faces_mat.Get(j,1),
                           faces_mat.Get(j,2));

            Faces().Add(f);

        }
        return true;

    }
    bool SetVerticesMat(DMatrix vertices_mat)
    {

        assert(vertices_mat.cols() == 3);

        Vertices().clear();
        for(int j=0; j<vertices_mat.rows(); j++)
        {
            float x = vertices_mat.Get(j,0);
            float y = vertices_mat.Get(j,1);
            float z = vertices_mat.Get(j,2);
            VertexType v(x,y,z);
//            printf("v=[%f %f %f] \r\n",x,y,z);
            Vertices().Add(v);

        }
        return true;
    }
    bool SetVertexUVsMat(DMatrix vertices_uv_mat)
    {

        assert(vertices_uv_mat.cols() == 2);
        for(int j=0; j<vertices_uv_mat.rows(); j++)
        {
            Vertex_UVS().Set(j,vertices_uv_mat.Get(j,0),vertices_uv_mat.Get(j,1));

        }
        for(int f=0; f<Faces().GetSize(); f++)
        {
            for(int k=0; k<3; k++)
            {
                int v_id = Face(f).Id(k);
//                int face_uv_id =FaceUVID(f).Id(k);
                int face_uv_id = f *3 +k;

                Face_UV(face_uv_id).SetX(Vertex_UV(v_id).GetCX());
                Face_UV(face_uv_id).SetY(Vertex_UV(v_id).GetCY());


            }
        }

        return true;
    }
    bool SetStoredPoint(DMatrix stord_pts_mat)
    {
        assert(stord_pts_mat.cols() == 3);

        StoredPts().clear();
        for(int j=0; j<stord_pts_mat.rows(); j++)
        {
            float x = stord_pts_mat.Get(j,0);
            float y = stord_pts_mat.Get(j,1);
            float z = stord_pts_mat.Get(j,2);
            VertexType v(x,y,z);
            StoredPts().Add(v);

        }
        return true;
    }

    bool SetTexture(ImageMatrix texture,int idx)
    {

        name_texture.Set(texture_names.Get(idx),CTexture(texture));
        return true;
    }


public:
    TrianglesType triangles;
    FaceUVSIDType faceuvs_id;

    VertexIndexType selected_faces_ids;
    VertexIndexType landmarks_index;
    std::map<int,int> mesh_to_basis_map;

    FaceToMateriaIDsMapType face_to_materia_id;

    VFlagsType verticesFlag;
    FFlagsType trianglesFlag;

    VsType vertices;
    VsType stored_pts;

    NsType vertex_normals;
    NsType face_normals;


    UVsType vertices_uv;
    UVsType origin_uv;
    TexturesType textures;
    TexturesNameType texture_names;
    Name2TextureType name_texture;

    point_3d max = {0.0,0.0,0.0};
    point_3d min = {1000.0,1000.0,1000.0};

private:
    UVsType face_uv;


};

}

using namespace crazy;
#endif //CRAZY_CMesh_H

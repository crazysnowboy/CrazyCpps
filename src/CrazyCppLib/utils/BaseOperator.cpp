

#include "BaseOperator.h"
namespace crazy
{


cv::Vec3d BaseOperator::ComputeNormalVector(cv::Vec3d &p1,cv::Vec3d &p2,cv::Vec3d &p3)
{

    cv::Vec3d a = p2 - p1;
    cv::Vec3d b = p3 - p1;
    cv::Vec3d n = a.cross(b);
    cv::normalize(n,n);

    return n;
}
Mesh::VertexType BaseOperator::_ComputeNormalVector(Mesh::VertexType &p1,Mesh::VertexType &p2,Mesh::VertexType &p3)
{
    Mesh::VertexType a, b;
    Mesh::VertexType n;

    a = p2 - p1;
    b = p3 - p1;

    n.Mutable_X() = (a.GetCY() * b.GetCZ()) - (a.GetCZ() * b.GetCY());
    n.Mutable_Y() = (a.GetCZ() * b.GetCX()) - (a.GetCX() * b.GetCZ());
    n.Mutable_Z() = (a.GetCX() * b.GetCY()) - (a.GetCY() * b.GetCX());

    double l = sqrt(n.GetCX() * n.GetCX() + n.GetCY() * n.GetCY() + n.GetCZ() * n.GetCZ());
    n  /= l;

    return n;
}
DMatrix BaseOperator::Compute_Face_Vertices_Normals(DMatrix v,DMatrix f,float scale,int flag)
{


    cv::Mat Vertices = Tool::CvtDMatrix2CVMat(v);
    cv::Mat Faces = Tool::CvtDMatrix2CVMat(f);



    CArray<cv::Vec3d> VertexNormals(Vertices.rows,0);
    for (int j = 0; j < Faces.rows; j++)
    {
        cv::Vec3d pts[3];
        cv::Vec3i face_v_id = Faces.row(j);
        for(int k=0; k<3; k++)
        {
            if(face_v_id[k]<Vertices.rows)
            {
                pts[k] = Vertices.row(face_v_id[k]);
            }
        }
        int index[2][3]= {0,1,2,0,2,1};

        cv::Vec3d Face_Nor=ComputeNormalVector(pts[index[flag][0]],pts[index[flag][1]],pts[index[flag][2]]);

        for (int k = 0; k < 3; k++)
        {

            if(face_v_id[k]<Vertices.rows)
            {
                VertexNormals.Get(face_v_id[k])  += Face_Nor;

            }
        }
    }
    for(int j=0; j<VertexNormals.GetSize(); j++)
    {
        cv::normalize(VertexNormals.Get(j),VertexNormals.Get(j));

    }


    cv::Mat Normals = cv::Mat(VertexNormals.GetSize(),3,CV_64FC1);
    for(int j=0; j<VertexNormals.GetSize(); j++)
    {
        Normals.at<double>(j,0) = VertexNormals.Get(j)[0];
        Normals.at<double>(j,1) = VertexNormals.Get(j)[1];
        Normals.at<double>(j,2) = VertexNormals.Get(j)[2];

//        std::cout <<"VertexNormals.Get(j)[0] = "<<VertexNormals.Get(j)[0]<<std::endl;

    }

    crazy::DMatrix n_dmatrix = Tool::CvtCVMat2DMatrix(Normals);

    return n_dmatrix;
}

bool BaseOperator::_Compute_Face_Vertices_Normals(Mesh & mesh,float scale,int flag)
{

    mesh.F_Normals().clear();
    mesh.F_Normals().resize(mesh.Faces().GetSize());

    mesh.V_Normals().clear();
    mesh.V_Normals().resize(mesh.Vertices().GetSize());



    for (int j = 0; j < mesh.Faces().size(); j++)
    {
        if(mesh.CheckFacesFlags(j,UFlag::Used,1) == false)
        {
            continue;
        }

        Mesh::VertexType pts[3];
        int face_v_id[3];

        for(int k=0; k<3; k++)
        {
            face_v_id[k]= mesh.triangles[j].v_id[k];
            if(face_v_id[k]<mesh.vertices.size())
            {
                pts[k].x = mesh.vertices[face_v_id[k]].x;
                pts[k].y = mesh.vertices[face_v_id[k]].y;
                pts[k].z = mesh.vertices[face_v_id[k]].z;
            }
        }

        int index[2][3]= {0,1,2,0,2,1};
        Mesh::VertexType tri_Nor=_ComputeNormalVector(pts[index[flag][0]],pts[index[flag][1]],pts[index[flag][2]]);

        mesh.face_normals[j]=tri_Nor;

        for (int k = 0; k < 3; k++)
        {
            if(face_v_id[k]<mesh.vertices.size())
            {
                mesh.vertex_normals[face_v_id[k]].Mutable_X()+= tri_Nor.Mutable_X();
                mesh.vertex_normals[face_v_id[k]].Mutable_Y()+= tri_Nor.Mutable_Y();
                mesh.vertex_normals[face_v_id[k]].Mutable_Z()+= tri_Nor.Mutable_Z();
                mesh.SetVerticesFlags(face_v_id[k], UFlag::Used);


            }


        }
    }
    for(int j=0; j<mesh.vertex_normals.size(); j++)
    {

        float nx= mesh.vertex_normals[j].Mutable_X();
        float ny= mesh.vertex_normals[j].Mutable_Y();
        float nz= mesh.vertex_normals[j].Mutable_Z();
        float l=sqrt(nx*nx+ny*ny+nz*nz);

        mesh.vertex_normals[j].Mutable_X() = nx / l * scale;
        mesh.vertex_normals[j].Mutable_Y() = ny / l * scale;
        mesh.vertex_normals[j].Mutable_Z() = nz / l * scale;



    }
}
double BaseOperator::_NormalizeVertices(Mesh & mesh,float scale)
{
    Mesh::VertexType Max_= {0.,0.0,0.0};
    Mesh::VertexType Min_= {10000000.0,10000000.0,10000000.0};

    for(int j=0; j<mesh.Vertices().GetSize(); j++)
    {
//        int j=i;
        if(mesh.vertices[j].Mutable_X()> Max_.Mutable_X())
        {
            Max_.Mutable_X() = mesh.vertices[j].Mutable_X();
        }
        if(mesh.vertices[j].Mutable_Y()> Max_.Mutable_Y())
        {
            Max_.Mutable_Y() = mesh.vertices[j].Mutable_Y();
        }

        if(mesh.vertices[j].Mutable_Z()> Max_.Mutable_Z())
        {
            Max_.Mutable_Z() = mesh.vertices[j].Mutable_Z();
        }

        if(mesh.vertices[j].Mutable_X()< Min_.Mutable_X())
        {
            Min_.Mutable_X() = mesh.vertices[j].Mutable_X();
        }
        if(mesh.vertices[j].Mutable_Y()< Min_.Mutable_Y())
        {
            Min_.Mutable_Y() = mesh.vertices[j].Mutable_Y();
        }

        if(mesh.vertices[j].Mutable_Z()< Min_.Mutable_Z())
        {
            Min_.Mutable_Z() = mesh.vertices[j].Mutable_Z();
        }

    }
//    printf("Min_.Mutable_X() = %f Min_.Mutable_Y() = %f Min_.GetZ() = %f \r\n",Min_.Mutable_X(),Min_.Mutable_Y(),Min_.Mutable_Z());
//    printf("Max_.Mutable_X() = %f Max_.Mutable_Y() = %f Max_.GetZ() = %f \r\n",Max_.Mutable_X(),Max_.Mutable_Y(),Max_.Mutable_Z());
    float max_axis_range_size =std::max((Max_.Mutable_Z()- Min_.Mutable_Z()),std::max((Max_.Mutable_X()- Min_.Mutable_X()),(
                                            Max_.Mutable_Y()-
                                            Min_.Mutable_Y())));
    if(scale >1.0)
    {
        max_axis_range_size = scale;
    }

    Mesh::VertexType base ;
    base.Mutable_X()= 0.5*(Max_.Mutable_X() + Min_.Mutable_X());
    base.Mutable_Y()= 0.5*(Max_.Mutable_Y() + Min_.Mutable_Y());
    base.Mutable_Z()= 0.5*(Max_.Mutable_Z() + Min_.Mutable_Z());

    for(int j=0; j<mesh.vertices.size(),j<mesh.verticesFlag.size(); j++)
    {

        mesh.vertices[j].Mutable_X()  = (mesh.vertices[j].Mutable_X() - base.Mutable_X())/(max_axis_range_size!=0 ?(max_axis_range_size):1)*scale;
        mesh.vertices[j].Mutable_Y()  = (mesh.vertices[j].Mutable_Y() - base.Mutable_Y())/(max_axis_range_size!=0 ?max_axis_range_size:1)*scale;
        mesh.vertices[j].Mutable_Z()  = (mesh.vertices[j].Mutable_Z() - base.Mutable_Z())/(max_axis_range_size!=0 ?max_axis_range_size:1)*scale;

    }

    for(int j=0; j<mesh.StoredPts().GetSize(); j++)
    {


        mesh.StoredPts().Get(j).Mutable_X() = (mesh.StoredPts().Get(j).Mutable_X() -  base.Mutable_X())/(max_axis_range_size!=0 ?(max_axis_range_size):1)*scale;
        mesh.StoredPts().Get(j).Mutable_Y() = (mesh.StoredPts().Get(j).Mutable_Y() -  base.Mutable_Y())/(max_axis_range_size!=0 ?(max_axis_range_size):1)*scale;
        mesh.StoredPts().Get(j).Mutable_Z() = (mesh.StoredPts().Get(j).Mutable_Z() -  base.Mutable_Z())/(max_axis_range_size!=0 ?(max_axis_range_size):1)*scale;

    }

    return max_axis_range_size;

}


DMatrix BaseOperator::SelectTrangleVertices(Mesh &src_mesh,DMatrix src_face_ids,Mesh &dst_mesh)
{
    return this->_SelectTrangleVertices2DMat(src_mesh,src_face_ids,dst_mesh);

}



DMatrix BaseOperator::_SelectTrangleVertices2DMat(Mesh &src_mesh,DMatrix src_face_ids,Mesh &dst_mesh)
{
    std::map<int,int> UsedVertices_index,UsedFaces_index;
    std::tie(UsedVertices_index, UsedFaces_index) = BaseOperator::_SelectTrangleVertices2Map(src_mesh,src_face_ids,dst_mesh);

    DMatrix res_mat(UsedVertices_index.size(),2);

    int cnt=0;
    for(std::map<int, int>::iterator iter = UsedVertices_index.begin(); iter != UsedVertices_index.end(); iter++)
    {
        int src_vertex_id = iter->first;
        int dst_vertex_id = iter->second;

        res_mat.Set(cnt,0,src_vertex_id);
        res_mat.Set(cnt,1,dst_vertex_id);

        cnt++;

    }
    return res_mat;
}

std::pair<std::map<int,int>, std::map<int,int>> BaseOperator::_SelectTrangleVertices2Map(Mesh &src_mesh,DMatrix src_face_ids,Mesh &dst_mesh)
{
    using namespace std;
    dst_mesh.clear();
    std::map<int,int> UsedVertices_index;
    std::map<int,int> UsedOriginUVS_index;
    std::map<int,int> UsedFaces_index;
    CArray<int> selected_faces_ids;
    for(int r=0; r<src_face_ids.rows(); r++)
        for(int c=0; c<src_face_ids.cols(); c++)
        {
            selected_faces_ids.push_back(src_face_ids.Get(r,c));
        }


    for(int s=0, new_v_id = 0,new_vt_id = 0; s<selected_faces_ids.GetSize(); s++)
    {
        int src_face_id = selected_faces_ids.Get(s);
        Mesh::TriangleType new_tri_id;
        Mesh::FaceUVIDType new_uv_id;

        for(int k=0; k<3; k++)
        {
            new_tri_id.v_id[k] = new_v_id;
            int temp_v_id = src_mesh.Face(src_face_id).v_id[k];
            pair<map<int, int>::iterator, bool> ret = UsedVertices_index.insert(std::pair<int,int>(temp_v_id,new_v_id));
            if (ret.second == false)
            {
                new_tri_id.v_id[k] = UsedVertices_index[temp_v_id];

            }
            else
            {
                new_v_id++;
            }


            new_uv_id.v_id[k] = new_vt_id;
            int temp_vt_id = src_mesh.FaceUVID(src_face_id).v_id[k];
            pair<map<int, int>::iterator, bool> ret2 = UsedOriginUVS_index.insert(std::pair<int,int>(temp_vt_id,new_vt_id));
            if (ret2.second == false)
            {
                new_uv_id.v_id[k] = UsedOriginUVS_index[temp_vt_id];
            }
            else
            {

                new_vt_id++;
            }

            float ux = src_mesh.Face_UV(src_face_id*3+k).GetCX();
            float uy = src_mesh.Face_UV(src_face_id*3+k).GetCY();
//                printf("ux=%f uy= %f \r\n",ux,uy);
            dst_mesh.Face_UVS().Add(ux,uy);


        }

        dst_mesh.Faces().push_back(new_tri_id);
        dst_mesh.FaceMateriaID(s)=src_mesh.FaceMateriaID(src_face_id);
        dst_mesh.FaceUVIDs().push_back(new_uv_id);
        dst_mesh.FaceFlags().push_back(UFlag::Used);


        pair<map<int, int>::iterator, bool> ret = UsedFaces_index.insert(std::pair<int,int>(src_face_id,s));
        if (ret.second == false)
        {
            std::cerr<<"failed to insert used faces indexs src_face_id ="<<src_face_id<<" s = "<<s<<std::endl;
        }
    }


    dst_mesh.vertices.Resize(UsedVertices_index.size());
    dst_mesh.vertex_normals.Resize(UsedVertices_index.size());
    dst_mesh.verticesFlag.Resize(UsedVertices_index.size());
    dst_mesh.Origin_UVS().Resize(UsedOriginUVS_index.size());

    for(map<int, int>::iterator iter = UsedVertices_index.begin(); iter != UsedVertices_index.end(); iter++)
    {
        int src_vertex_id = iter->first;
        int dst_vertex_id = iter->second;

        dst_mesh.vertices[dst_vertex_id] = src_mesh.vertices[src_vertex_id];
        dst_mesh.vertex_normals[dst_vertex_id] = src_mesh.vertex_normals[src_vertex_id];
        dst_mesh.verticesFlag[dst_vertex_id] = src_mesh.verticesFlag[src_vertex_id];

    }

    for(map<int, int>::iterator iter = UsedOriginUVS_index.begin(); iter != UsedOriginUVS_index.end(); iter++)
    {
        int src_uv_id = iter->first;
        int dst_uv_id = iter->second;
        dst_mesh.Origin_UV(dst_uv_id) = src_mesh.Origin_UV(src_uv_id);
    }



    dst_mesh.Vertex_UVS().resize(dst_mesh.Vertices().GetSize());
    for(int f=0; f <dst_mesh.Faces().GetSize(); f++)
    {
        for(int k=0; k<3; k++)
        {
            int face_uv_id = f*3+k;
            int v_id = dst_mesh.Face(f).v_id[k];
            dst_mesh.Vertex_UV(v_id)=dst_mesh.Face_UV(face_uv_id);

        }
    }

    dst_mesh.min = src_mesh.min;
    dst_mesh.max = src_mesh.max;

    dst_mesh.Textures() = src_mesh.Textures();
    dst_mesh.TexturesName() = src_mesh.TexturesName();

    return {UsedVertices_index,UsedFaces_index};

}
}
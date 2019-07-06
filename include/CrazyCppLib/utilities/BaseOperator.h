

#ifndef CRAZY_BASEOPERATOR_H
#define CRAZY_BASEOPERATOR_H

#include "Datastructure/CArray.hpp"
#include <vector>
#include <opencv2/opencv.hpp>
#include "Mesh.h"
#include "utilities/crazy_tools.h"
namespace crazy
{
class BaseOperator
{
private:

    cv::Vec3d ComputeNormalVector(cv::Vec3d &p1,cv::Vec3d &p2,cv::Vec3d &p3);

public:

    DMatrix Compute_Face_Vertices_Normals(DMatrix v,DMatrix f,float scale,int flag=0);
    DMatrix SelectTrangleVertices(Mesh &src_mesh,DMatrix src_face_ids,Mesh &dst_mesh);

public:

    static Mesh::VertexType _ComputeNormalVector(Mesh::VertexType &p1,Mesh::VertexType &p2,Mesh::VertexType &p3);
    static bool _Compute_Face_Vertices_Normals(Mesh &mesh,float scale=1.0,int flag=1);
    static double _NormalizeVertices(Mesh &mesh,float scale=1.0);
    static std::pair<std::map<int,int>, std::map<int,int>> _SelectTrangleVertices2Map(Mesh &src_mesh,DMatrix src_face_ids,Mesh &dst_mesh);

    static DMatrix _SelectTrangleVertices2DMat(Mesh &src_mesh,DMatrix src_face_ids,Mesh &dst_mesh);

};
}



#endif //CRAZY_BASEOPERATOR_H

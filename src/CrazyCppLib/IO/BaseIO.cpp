

#include "BaseIO.h"
#include <tiny_obj_loader.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "utilities/CrazyString.h"
#include "crazy_tools.h"
namespace BaseIO
{
// Split a string with specified delimiter character.
// http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string> SplitString(const std::string &s, const char delim)
{

    std::vector<std::string> elems;
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}
std::string GetBaseDir(const std::string &filepath)
{
    if (filepath.find_last_of("/\\") != std::string::npos)
    {
        return filepath.substr(0, filepath.find_last_of("/\\"));
    }
    return "";
}

bool ReadVector(CArray<int> &id_vector, std::istream& infile)
{
    int feat_onePoint;
    std::string feature;
    while (getline(infile, feature))
    {
        std::stringstream stringin(feature);
        while (stringin >> feat_onePoint)
        {
            id_vector.push_back(feat_onePoint);
        }
    }
    return true;
}

bool TinyLoadOBJ(Mesh &mesh,const char* obj_path,float scale,int tri_offset)
{

    std::cout << "load:" << obj_path << std::endl;

    std::vector<tinyobj::material_t> materials;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;

    std::string base_dir = GetBaseDir(obj_path);
    if (base_dir.empty())
    {
        base_dir = ".";
    }

    base_dir += "/";

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, obj_path,base_dir.c_str());

    if (!err.empty())
    {
        std::cerr << err << std::endl;
    }
    if (!ret)
    {
        std::cerr << "Failed to load " << obj_path << std::endl;
        return false;
    }
    int n_vertices = (int)(attrib.vertices.size()) / 3;
    int n_normals = (int)(attrib.normals.size()) / 3;
    printf("#TinyLoadOBJ of vertices  = %d\n", n_vertices);
    printf("#TinyLoadOBJ of normals   = %d\n", n_normals);
    printf("#TinyLoadOBJ of texcoords = %d\n", (int)(attrib.texcoords.size()) / 2);
    printf("#TinyLoadOBJ of materials = %d\n", (int)materials.size());
    printf("#TinyLoadOBJ of shapes    = %d\n", (int)shapes.size());

    for (int i = 0; i < materials.size(); ++i)
    {
//        if(materials[i].diffuse_texname !="")
        {
            printf("material[%d].diffuse_texname = %s\n", int(i), materials[i].diffuse_texname.c_str());


            mesh.TexturesName().push_back(materials[i].diffuse_texname);


        }
    }

    mesh.Vertex_UVS().resize(n_vertices);

    for(int i=0; i<n_vertices; i++)
    {
        Mesh::VertexType pt;

        pt.Mutable_X() = attrib.vertices[3*i+0]*scale;
        pt.Mutable_Y() = attrib.vertices[3*i+1]*scale;
        pt.Mutable_Z() = attrib.vertices[3*i+2]*scale;
//        printf("v[%d] = %f %f %f \r\n",i,pt.Mutable_X(),pt.Mutable_Y(),pt.Mutable_Z());

        mesh.Vertices().Add(pt);
        mesh.VertexFlags().Add(UFlag::NON);
    }
    for(int i=0; i<n_normals; i++)
    {
        Mesh::NormalType Normal;

        Normal.Mutable_X() = attrib.normals[3*i+0];
        Normal.Mutable_Y() = attrib.normals[3*i+1];
        Normal.Mutable_Z() = attrib.normals[3*i+2];

        mesh.V_Normals().Add(Normal);
    }


    mesh.Origin_UVS().clear();
    for( int j=0; j<attrib.texcoords.size(); j+=2)
    {
        float ux = attrib.texcoords[j];
        float uy = attrib.texcoords[j+1];
        mesh.Origin_UVS().Add(ux,uy);
    }

    mesh.FaceFlags().clear();
    mesh.Faces().clear();
    mesh.FaceUVIDs().clear();
    int face_id_cnt=0;
    for (int s = 0; s < shapes.size(); s++)
    {
//        printf("GroupID= %d vs %d \r\n",mesh.FaceMateriaIDsSize(),s);
        printf("shape name = %s \r\n",shapes[s].name.c_str());

        for (int f = 0; f < shapes[s].mesh.indices.size() / 3; f++)
        {


            Mesh::TriangleType Tri_id;
            Mesh::FaceUVIDType Uv_id;
            for(int k=0; k<3; k++)
            {


                int v_id = shapes[s].mesh.indices[3 * f + k].vertex_index;
                int tex_coor_id = shapes[s].mesh.indices[3 * f + k].texcoord_index;

                Tri_id.v_id[k] = v_id + tri_offset;
                Uv_id.v_id[k] = tex_coor_id;
//                printf("[%d] =%d vs %d \r\n",tex_coor_id,attrib.texcoords.size() ,(2*tex_coor_id + 1));
                if (attrib.texcoords.size() > (2*tex_coor_id + 1))
                {
                    Mesh::UVType uv;
                    uv.Mutable_X() = attrib.texcoords[2*tex_coor_id + 0];
                    uv.Mutable_Y() = 1-attrib.texcoords[2*tex_coor_id + 1];

                    // to fixe some situation that uv >1.0
                    uv.Mutable_X() = uv.Mutable_X() - std::floor(uv.Mutable_X());
                    uv.Mutable_Y() = uv.Mutable_Y() - std::floor(uv.Mutable_Y());

//                    printf("## read   ux=%f uy =%f \r\n",uv.x,uv.y);

                    mesh.Face_UVS().Add(uv.GetCX(),uv.GetCY());

                    mesh.Vertex_UVS().Set(v_id,uv.GetCX(),uv.GetCY());


                }
                mesh.VertexFlag(v_id)=UFlag::Used;
            }



            if (shapes[s].mesh.material_ids[f]<0)
            {
//                std::cerr <<"######= "<<shapes[s].mesh.material_ids[f]<<std::endl;
                continue;

            }
            mesh.FaceMateriaIDs()[face_id_cnt++] = shapes[s].mesh.material_ids[f];

//            std::cout <<"f="<<f<<" shapes[s].mesh.material_ids[f]; ="<< shapes[s].mesh.material_ids[f]<<std::endl;


            mesh.Faces().Add(Tri_id);
            mesh.FaceUVIDs().Add(Uv_id);
            mesh.FaceFlags().Add(UFlag::Used);


        }
    }
    Mesh::VertexType Max_= {0.,0.0,0.0};
    Mesh::VertexType Min_= {10000000.0,10000000.0,10000000.0};

    for(int i=0; i<mesh.triangles.size(); i++)
    {
        int j= mesh.triangles[i].v_id[0];
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
    mesh.min = Min_;
    mesh.max = Max_;


    return true;
}


cv::Mat  LoadBasis2(std::string file_name)
{
    //! expression basis
    std::vector<cv::Mat> basis_vector;

    std::ifstream infile(file_name);
    if( !infile )
    {
        std::cerr << "Error opening " << file_name << " for input" << std::endl;
    }
    std::string feature;
    int basis_dimention =0;
    while(getline(infile,feature))
    {
        std::stringstream stringin(feature);

        std::vector<float> temp;
        float feat_onePoint;

        temp.clear();
        while (stringin >> feat_onePoint)
        {
            temp.push_back(feat_onePoint);
        }
        basis_dimention = temp.size();
        cv::Mat expression(1, basis_dimention, CV_32FC1, cv::Scalar::all(0.0));
        for (int i = 0; i < basis_dimention; ++i)
        {
            expression.at<float>(0, i) = temp[i];

        }
        basis_vector.push_back(expression);
    }

    int basis_num = basis_vector.size();
    cv::Mat basis(basis_num,basis_dimention,CV_32FC1,cv::Scalar::all(0.0));
    for(int h=0; h<basis_num; h++)
    {
        basis_vector[h].row(0).copyTo(basis.row(h));
    }

    std::cout <<"basis file_name = "<<file_name<<std::endl;
    std::cout <<"basis_num = "<<basis_num<<"   basis_dimention = "<<basis_dimention<<std::endl;

    return basis;

}

std::vector<cv::Mat>  LoadBasis(std::string file_name)
{
    //! expression basis
    std::vector<cv::Mat> basis;

    std::ifstream infile(file_name);
    if( !infile )
    {
        std::cerr << "Error opening " << file_name << " for input" << std::endl;
    }
    std::string feature;
    while(getline(infile,feature))
    {
        std::stringstream stringin(feature);

        std::vector<float> temp;
        float feat_onePoint;

        temp.clear();
        while (stringin >> feat_onePoint)
        {
            temp.push_back(feat_onePoint);
        }
        cv::Mat expression(3, temp.size()/3, CV_32FC1, cv::Scalar::all(0.0));
        for (int i = 0; i < temp.size() / 3; ++i)
        {
            expression.at<float>(0, i) = temp[3 * i + 0];
            expression.at<float>(1, i) = temp[3 * i + 1];
            expression.at<float>(2, i) = temp[3 * i + 2];
        }
        basis.push_back(expression);
    }
    return basis;

}


cv::Mat LoadEigenValues(std::string file_name)
{
    std::vector<float> eigen_values;
    std::ifstream infile(file_name);
    if( !infile )
    {
        std::cerr << "Error opening " << file_name << " for input" << std::endl;
    }
    std::string temp_line;
    while(getline(infile,temp_line))
    {
        std::stringstream stringin(temp_line);
        float eigen_value;
        while (stringin >> eigen_value)
        {
            eigen_values.push_back(eigen_value);
        }


    }
    cv::Mat Shape_SIgma(eigen_values.size(), 1, CV_32FC1, cv::Scalar::all(0.0));
    for(int j=0; j<eigen_values.size(); j++)
    {
        Shape_SIgma.at<float>(j, 0) = eigen_values[j];

    }
    return Shape_SIgma;

}
bool ReadMat(cv::Mat &data_mat, const char *path)
{
    crazy::CArray<crazy::CArray<float>> MatList;
    ReadMat(MatList,path);
    if(MatList.GetSize()>0)
    {
        data_mat = cv::Mat(MatList.GetSize(),MatList.Get(0).GetSize(),CV_32FC1);
        for(int j=0; j<data_mat.rows; j++)
        {
            for(int i=0; i<data_mat.cols; i++)
            {
                data_mat.at<float>(j,i)=MatList.Get(j).Get(i);
            }
        }

    }

}

bool save_tensor(const char* filename_out,DMatrix mat,int m_nVertices,int m_nExpressions,int m_nIdentities)
{


    Eigen::MatrixXf m_tensor;
    m_tensor.resize(m_nVertices * 3, m_nExpressions*m_nIdentities);

    for(int r=0;r<m_tensor.rows();r++)
    {
        for(int c=0;c<m_tensor.cols();c++)
        {

            m_tensor(r, c) = mat.Get(r,c);
        }
    }

    std::ofstream outTensor(filename_out, std::ifstream::binary);
    if (outTensor.fail())
    {
        std::cerr <<std::string("write tensor failed: ")<<std::endl;
        return false;
    }
    outTensor.write((char*)(&m_nVertices), sizeof(int));
    outTensor.write((char*)(&m_nExpressions), sizeof(int));
    outTensor.write((char*)(&m_nIdentities), sizeof(int));
    outTensor.write((char*)m_tensor.data(), sizeof(float)*m_nExpressions*m_nIdentities*m_nVertices * 3);
    outTensor.close();


}


bool ReadLandmarks(Mesh &mesh, const char* path)
{
    printf("read landmarks index file =  %s \r\n",path);
    ReadVector(mesh.landmarks_index, path);

}


bool WriteOBJ(Mesh &mesh,const char* obj_path,float scale,int tri_offset)
{


    FILE *fd = fopen(obj_path, "w");
    if (fd != NULL)
    {
        for (int i = 0; i < mesh.Vertices().GetSize(); i++)
        {
            fprintf(fd, "v %12.9f %12.9f %12.9f\n", mesh.Vertex(i).x, mesh.Vertex(i).y, mesh.Vertex(i).z);
        }
        for (int i = 0; i < mesh.Vertex_UVS().GetSize(); i++)
        {
            fprintf(fd, "vt %12.9f %12.9f\n", mesh.Vertex_UV(i).GetCX(),mesh.Vertex_UV(i).GetCY());

        }
        for (int i = 0; i < mesh.triangles.size(); i++)
        {

            fprintf(fd, "f %d/%d %d/%d %d/%d\n",
                    mesh.triangles[i].v_id[0]+ tri_offset, mesh.FaceUVID(i).v_id[0]+tri_offset,
                    mesh.triangles[i].v_id[1]+ tri_offset, mesh.FaceUVID(i).v_id[1]+tri_offset,
                    mesh.triangles[i].v_id[2]+ tri_offset, mesh.FaceUVID(i).v_id[2]+tri_offset);
        }

        fclose(fd);
        return 0;
    }
    else
    {
        return -1;
    }

    return true;
}

bool ReadVector(crazy::CArray<int> &id_vector, const char *path)
{


    int feat_onePoint;
    std::string feature;

    std::ifstream infile(path);
    if( !infile )
    {
        std::cerr << "Error opening " << path << " for input" << std::endl;
    }
    while(getline(infile,feature))
    {
        std::stringstream stringin(feature);
        while (stringin >> feat_onePoint)
        {
            id_vector.push_back(feat_onePoint);

        }

    }
//    printf("read landmarks index file =  %s size=%d \r\n",path,id_vector.size());




}
bool ReadVector(crazy::CArray<std::string> &names, const char *path)
{

    std::string feature;

    std::ifstream infile(path);
    if( !infile )
    {
        std::cerr << "Error opening " << path << " for input" << std::endl;
    }
    while(getline(infile,feature))
    {
        names.push_back(feature);

    }


}

DMatrix ReadVector2DMat( const char *path)
{

    crazy::CArray<int> id_vector;
    int feat_onePoint;
    std::string feature;

    std::ifstream infile(path);
    if( !infile )
    {
        std::cerr << "Error opening " << path << " for input" << std::endl;
    }
    while(getline(infile,feature))
    {
        std::stringstream stringin(feature);
        while (stringin >> feat_onePoint)
        {
            id_vector.push_back(feat_onePoint);

        }

    }

    DMatrix id_mat(id_vector.GetSize(),1);

    for (int i=0; i<id_vector.GetSize(); i++)
    {
        id_mat.Set(0,i,id_vector.Get(i));

    }

    return id_mat;

}
bool ReadMap(std::map<int ,int> &map,const char* path,bool inverse)
{
    printf("read mapfile =  %s \r\n",path);

    int first_data;
    int second_data;
    std::string feature;

    std::ifstream infile(path);
    if( !infile )
    {
        std::cerr << "Error opening " << path << " for input" << std::endl;
        exit(-1);
    }
    while(getline(infile,feature))
    {
        std::stringstream stringin(feature);
        if(inverse)
        {
            stringin >> second_data;
            stringin >> first_data;
        }
        else
        {
            stringin >> first_data;
            stringin >> second_data;
        }

        map[first_data]=second_data;
    }



}
bool ReadSelectedIds(CArray<int> &id_vector,std::map<int,int> Human_to_selected_Head_UsedVertices_index, const char* path)
{
    printf("read  index file =  %s \r\n",path);
    crazy::CArray<int> selected_vertex_ids;
    ReadVector(selected_vertex_ids, path);
    id_vector.resize(selected_vertex_ids.size());
    for(int j=0; j<selected_vertex_ids.size(); j++)
    {
        id_vector[j]=Human_to_selected_Head_UsedVertices_index[selected_vertex_ids[j]];
    }
    return true;
}
bool SaveFacesVids(std::map<int ,int> &face_map,Mesh mesh,const char* obj_path)
{
    std::ofstream outfile(obj_path);
    if (outfile.is_open())
    {
        for (std::map<int, int>::iterator iter = face_map.begin(); iter != face_map.end(); iter++)
        {
//            outfile<<iter->first<< " " << iter->second <<std::endl;
            int face_id = iter->first;
            int v_id =  mesh.Face(face_id).Id0();
            outfile<<v_id<<std::endl;

            v_id =  mesh.Face(face_id).Id1();
            outfile<<v_id<<std::endl;

            v_id =  mesh.Face(face_id).Id2();
            outfile<<v_id<<std::endl;

        }
        outfile.close();
        return true;
    }
    else
    {
        printf("file opened failed \r\n");
        return false;
    }


}
bool SaveVector(std::vector<int> &list,const char* obj_path)
{
    printf("save list as %s \r\n",obj_path);
    std::ofstream outfile(obj_path);
    if (outfile.is_open())
    {
        /* save vertex information */
        for (int i = 0; i < list.size(); i++)
        {
            outfile<<list[i]<<std::endl;

        }
        outfile.close();
        return true;
    }
    else
    {
        std::cerr <<"file: "<< obj_path<<" opened failed "<<std::endl;
        return false;
    }


}

bool SaveVectors(std::vector<std::vector<int>> &lists,const char* obj_path)
{
    printf("save lists as %s \r\n",obj_path);
    std::ofstream outfile(obj_path);
    if (outfile.is_open())
    {
        /* save vertex information */
        for (int i = 0; i < lists.size(); i++)
        {
            for(int j=0; j<lists[i].size(); j++)
            {
                outfile<<lists[i][j]<< " ";
            }
            outfile<<std::endl;

        }
        outfile.close();
        return true;
    }
    else
    {
        printf("file opened failed \r\n");
        return false;
    }


}

bool SaveCArrays(CArray<CArray<Mesh::VertexType>> &lists,const char* obj_path)
{
    printf("save lists as %s \r\n",obj_path);
    std::ofstream outfile(obj_path);
    if (outfile.is_open())
    {
        /* save vertex information */
        for (int i = 0; i < lists.GetSize(); i++)
        {
            for(int j=0; j<lists.Get(i).GetSize(); j++)
            {
                outfile<<lists.Get(i).Get(j).GetCX()<< " "
                       <<lists.Get(i).Get(j).GetCY()<< " "
                       <<lists.Get(i).Get(j).GetCZ()<< " ";

            }
            outfile<<std::endl;

        }
        outfile.close();
        return true;
    }
    else
    {
        printf("file opened failed \r\n");
        return false;
    }


}
bool SaveMap(std::map<int ,int> &map,const char* obj_path)
{
    printf("save map as %s \r\n",obj_path);
    std::ofstream outfile(obj_path);
    if (outfile.is_open())
    {
        for (std::map<int, int>::iterator iter = map.begin(); iter != map.end(); iter++)
        {
            outfile<<iter->first<< " " << iter->second <<std::endl;
//                outfile<<iter->first<<std::endl;

        }
        outfile.close();
        return true;
    }
    else
    {
        printf("file opened failed \r\n");
        return false;
    }


}
bool LoadTexture(const char * root_path,Mesh &mesh,const int texture_scale)
{
    std::string root_path_str =  root_path;
    root_path_str+="/";

//    std::cout <<"root_path_str ="<<root_path_str<<std::endl;

    mesh.Textures().clear();
    Mesh::TextureType mesh_texture ;


    std::map<std::string,int> unique_texture_name;
    for(int k=0,new_v_id=0; k<mesh.texture_names.size(); k++)
    {
        std::string image_path =mesh.texture_names[k];
        std::pair<std::map<std::string, int>::iterator, bool> ret = unique_texture_name.insert(std::pair<std::string,int>(image_path,new_v_id));
        if (ret.second == true)
        {
            new_v_id++;
        }
    }

    for(std::map<std::string, int>::iterator iter = unique_texture_name.begin(); iter != unique_texture_name.end(); iter++)
    {
        std::string image_path = iter->first;
        int texture_id = iter->second;

        std::cout <<"read img ="<<root_path_str+image_path<<std::endl;

        cv::Mat texture= cv::imread(root_path_str+image_path,cv::IMREAD_UNCHANGED);

//        std::cout <<"texture ="<<texture<<std::endl;

//        cv::namedWindow("texture",0);
//        cv::imshow("texture",texture);
//        cv::waitKey(0);

        cv::resize(texture,texture,cv::Size(texture.cols/texture_scale,texture.rows/texture_scale));

//        cv::namedWindow("texture",0);
//        cv::imshow("texture",texture);

        mesh_texture = Tool::convert_CVImage2ImageMatrix(texture);

        cv::Mat test_texture =Tool::convert_ImageMatrix2CVImage(mesh_texture.GetData());
//        cv::namedWindow("test_texture",0);
//        cv::imshow("test_texture",test_texture);
//        cv::waitKey(0);


        if(texture.empty())
        {
            std::cerr <<"failed to read image ="<<root_path_str+image_path<<std::endl;

            texture = cv::Mat::eye(100,100,CV_8UC3);

            mesh.Textures().Set(image_path,mesh_texture);

            continue;

        }
////    cv::imshow("texture",texture);
////    cv::waitKey(0);
////    cv::flip(texture,texture,0);
////    cv::cvtColor(texture,texture,CV_RGB2RGBA);

        mesh.Textures().Set(image_path,mesh_texture);


    }
    std::cout <<"mesh texture sizes ="<<mesh.Textures().GetSize()<<std::endl;



    return true;
}


//! Write cv::Mat as binary
/*!
\param[out] ofs output file stream
\param[in] out_mat mat to save
*/
bool writeMatBinary(std::ofstream& ofs, const cv::Mat& out_mat)
{
    if(!ofs.is_open())
    {
        return false;
    }
    if(out_mat.empty())
    {
        int s = 0;
        ofs.write((const char*)(&s), sizeof(int));
        return true;
    }
    int type = out_mat.type();
    ofs.write((const char*)(&out_mat.rows), sizeof(int));
    ofs.write((const char*)(&out_mat.cols), sizeof(int));
    ofs.write((const char*)(&type), sizeof(int));
    ofs.write((const char*)(out_mat.data), out_mat.elemSize() * out_mat.total());

    return true;
}


//! Save cv::Mat as binary
/*!
\param[in] filename filaname to save
\param[in] output cvmat to save
*/
bool SaveMatBinary(const std::string& filename, const cv::Mat& output)
{

    std::cout << "saved bin file = "<<filename<<std::endl;
    std::ofstream ofs(filename, std::ios::binary);
    if(ofs.is_open() ==false)
    {
        std::cerr <<" can not open file : "<<filename<<std::endl;
    }
    return writeMatBinary(ofs, output);
}


//! Read cv::Mat from binary
/*!
\param[in] ifs input file stream
\param[out] in_mat mat to load
*/
bool readMatBinary(std::istream& ifs, cv::Mat& in_mat)
{
    int rows, cols, type;
    ifs.read((char*)(&rows), sizeof(int));
    if(rows==0)
    {
        return true;
    }
    ifs.read((char*)(&cols), sizeof(int));
    ifs.read((char*)(&type), sizeof(int));

    in_mat.release();
    in_mat.create(rows, cols, type);
    ifs.read((char*)(in_mat.data), in_mat.elemSize() * in_mat.total());

    return true;
}
bool LoadMatBinary(const std::string& filename, cv::Mat& intput)
{
    std::ifstream ifs(filename, std::ios::binary);
    if(ifs.is_open()==false)
    {
        std::cerr <<"can not open file :"<<filename<<std::endl;
        return false;

    }
    return readMatBinary(ifs, intput);
}
DMatrix LoadMatBinary2Dmat(const char * filename)
{
    cv::Mat cv_mat;
    std::string path = filename;
    LoadMatBinary(path,cv_mat);
    DMatrix result =Tool::CvtCVMat2DMatrix(cv_mat);
    return result;

}


}

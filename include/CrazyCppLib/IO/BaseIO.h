//
// Created by collin on 18-1-8.
//

#ifndef CRAZY_BASEIO_H
#define CRAZY_BASEIO_H

#include <sstream>
#include <math.h>
#include "Mesh.h"
#include <fstream>
#include <opencv2/core/core.hpp>
#include <fstream>
#include <istream>
#include "ZipLib/ZipFile.h"


namespace BaseIO
{

std::vector<std::string> SplitString(const std::string &s, char delim);


template <typename Dtype>
bool ReadMat( crazy::CArray<crazy::CArray<Dtype>>&Mat, const char *path)
{

    std::cout <<"read from file="<<path<<std::endl;
    Dtype feat_onePoint;
    std::string feature;

    std::ifstream infile(path);
    if( infile.is_open() == false)
    {
        std::cerr << "Error opening " << path << " for input" << std::endl;
    }
    while(getline(infile,feature))
    {
        std::stringstream stringin(feature);
        crazy::CArray<Dtype> line_data;
        while (stringin >> feat_onePoint)
        {
            line_data.push_back(feat_onePoint);

//                std::cout <<"data = "<<feat_onePoint<<std::endl;

        }
        Mat.push_back(line_data);

    }
    std::cout <<"Mat shape=["<<Mat.GetSize()<<" , "<< Mat.Get(0).GetSize()<<" ] "<<std::endl;

}

bool ReadMat(cv::Mat &data_mat, const char *path);

std::string GetBaseDir(const std::string &filepath);
bool TinyLoadOBJ(Mesh &mesh,const char* obj_path,float scale=1,int tri_offset = 0);


cv::Mat  LoadBasis2(std::string file_name);

std::vector<cv::Mat>  LoadBasis(std::string file_name);

cv::Mat LoadEigenValues(std::string file_name);


bool save_tensor(const char* filename_out,DMatrix mat,int m_nVertices,int m_nExpressions,int m_nIdentities);

bool ReadLandmarks(Mesh &mesh, const char* path);
bool WriteOBJ(Mesh &mesh,const char* obj_path,float scale,int tri_offset);
bool ReadVector(crazy::CArray<int> &id_vector, const char *path);

DMatrix ReadVector2DMat( const char *path);

bool ReadVector(crazy::CArray<std::string> &id_vector, const char *path);
bool ReadVector(crazy::CArray<int> &id_vector, std::istream& infile);


bool ReadSelectedIds(crazy::CArray<int> &id_vector,std::map<int,int> Human_to_selected_Head_UsedVertices_index, const char* path);

bool SaveFacesVids(std::map<int ,int> &face_map,Mesh mesh,const char* obj_path);

bool SaveVector(std::vector<int> &list,const char* obj_path);

bool SaveVectors(std::vector<std::vector<int> > &lists,const char* obj_path);

bool SaveCArrays(crazy::CArray<crazy::CArray<Mesh::VertexType>> &lists,const char* obj_path);

bool SaveMap(std::map<int,int > &map,const char* obj_path);

bool LoadTexture(const char * root_path,Mesh &mesh,const int texture_scale=1);

bool ReadMap(std::map<int ,int> &map,const char* path,bool inverse = false);

bool readMatBinary(std::istream& ifs, cv::Mat& in_mat);

bool SaveMatBinary(const std::string& filename, const cv::Mat& output);

bool readMatBinary(std::istream& ifs, cv::Mat& in_mat);

bool LoadMatBinary(const std::string& filename, cv::Mat& intput);

DMatrix LoadMatBinary2Dmat(const char * filename);

}



#endif //CRAZY_BASEIO_H

//
// Created by collin on 18-2-23.
//

#ifndef MESHPRO_CRAZYSTRING_H
#define MESHPRO_CRAZYSTRING_H

#include <string>
#include <vector>
#include <iomanip>
namespace std
{
template <typename Dtype>
std::string to_string(Dtype data)
{
    std::stringstream string_stream;
    string_stream << std::setw(2) << std::setfill('0') << data ;
    return string_stream.str();
}

}
namespace crazy
{

template <typename Dtype>
std::vector<std::string> SplitString(const Dtype& s, const Dtype& c)
{

    std::vector<std::string> v;
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
    {
        v.push_back(s.substr(pos1));
    }

    return v;
}
template <typename Dtype>
Dtype get_string_element(Dtype input_str,Dtype template_str,int index)
{
    std::vector<std::string> name_list = SplitString(input_str,template_str);
    if(index>=0)
    {
        return name_list[index];
    }
    else
    {
        return name_list[name_list.size()+index];

    }



}
template <typename Dtype>
Dtype get_file_name(Dtype file_path)
{

    std::string file_name = crazy::get_string_element(file_path,std::string("/"),-1);
    std::string base_name = crazy::get_string_element(file_name,std::string("."),0);
    return base_name;


}

template <typename Dtype>
Dtype ReplaceString(const Dtype& str, const Dtype& src, const Dtype& dest)
{
    std::string ret;

    std:: string::size_type pos_begin = 0;
    std::string::size_type pos       = str.find(src);
    while (pos != std::string::npos)
    {
        ret.append(str.data() + pos_begin, pos - pos_begin);
        ret += dest;
        pos_begin = pos + 1;
        pos       = str.find(src, pos_begin);
    }
    if (pos_begin < str.length())
    {
        ret.append(str.begin() + pos_begin, str.end());
    }
    return ret;
}

}

#endif //MESHPRO_CRAZYSTRING_H

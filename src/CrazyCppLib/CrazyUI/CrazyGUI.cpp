#include "CrazyGUI.h"

namespace crazy
{

CrazyGUI::CrazyGUI()
{

}
CrazyGUI::CrazyGUI(config_parameters& conf)
{

    this->Init(conf);


}
bool CrazyGUI::Init(config_parameters& conf)
{


    pangolin_gui= new PangolinGUI(conf);
    pangolin_gui->SetUpUI(conf);


}
bool CrazyGUI::ShouldExit()
{
    return  pangolin_gui->ShouldExit();
}

bool CrazyGUI::UpdateUI(config_parameters& temp_conf)
{

    pangolin_gui->SetUpUI(temp_conf);

}
bool CrazyGUI::UpdataDataBar(config_parameters& temp_conf)
{

    pangolin_gui->SetUpDataBarUI(temp_conf);

}
bool CrazyGUI::UpdataCheckbox(config_parameters& temp_conf)
{

    pangolin_gui->SetUpBoxUI(temp_conf);

}
void CrazyGUI::Precall()
{
    pangolin_gui->Precall();
}

void CrazyGUI::PostCall()
{
    pangolin_gui->PostCall();

}
crazy::DMatrix CrazyGUI::GetViewMatrix(void )
{
    Eigen::Matrix4f view_matrix = pangolin_gui->GetViewMatrix();
    crazy::DMatrix view_mat(4,4,0.0);
    for(int j=0; j<4; j++)
        for(int i=0; i<4; i++)
        {
            view_mat.Set(i,j,view_matrix(i,j));
        }
    return view_mat;

}
CrazyGUI:: ~CrazyGUI()
{




}

bool CrazyGUI::ProcessEvent(CrossDatum &tDatum)
{

    pangolin_gui->ProcessEvent(tDatum);

    return true;
}

}

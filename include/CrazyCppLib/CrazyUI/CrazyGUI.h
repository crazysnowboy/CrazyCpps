/*
 * This file is part of ElasticFusion.
 *
 * Copyright (C) 2015 Imperial College London
 *
 * The use of the code within this file and all code within files that
 * make up the software that is ElasticFusion is permitted for
 * non-commercial purposes only.  The full terms and conditions that
 * apply to the code within this file are detailed within the LICENSE.txt
 * file and at <http://www.imperial.ac.uk/dyson-robotics-lab/downloads/elastic-fusion/elastic-fusion-license/>
 * unless explicitly stated.  By downloading this file you agree to
 * comply with these terms.
 *
 * If you wish to use any of this code for commercial purposes then
 * please email researchcontracts.engineering@imperial.ac.uk.
 *
 */

#ifndef CrazyGUI_H_
#define CrazyGUI_H_
#include "CrazyWindow.h"
#include <map>
#include "CrossDatum.h"
#include "utilities/config.h"
#include <string>
#include "PangolinGUI.h"
namespace crazy
{


class CrazyGUI
{
public:


    CrazyGUI();
    CrazyGUI(config_parameters &conf);
    bool Init(config_parameters &conf);

    ~CrazyGUI();

    bool ShouldExit();
    void Precall();
    void PostCall();
    bool ProcessEvent(CrossDatum &tDatum);

    bool UpdateUI(config_parameters &temp_conf);
    bool UpdataDataBar(config_parameters &temp_conf);
    bool UpdataCheckbox(config_parameters &temp_conf);



    crazy::DMatrix GetViewMatrix(void);

private:

    PangolinGUI* pangolin_gui = nullptr;
};
}





#endif /* GUI_H_ */

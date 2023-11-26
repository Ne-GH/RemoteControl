/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/23 00:47
*******************************************************************************/


#pragma once
#include <tuple>

class CursorListen {

    bool move = false;
    int last_x = 0,last_y = 0;


public:
    CursorListen();
    std::tuple<int,int> GetGlobalPos();
    void SetGlobalPos(std::tuple<int,int>);
    ~CursorListen();

};

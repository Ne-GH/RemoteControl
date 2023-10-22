/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/23 00:47
*******************************************************************************/


#pragma once
#include <tuple>

class Cursor {

public:
    Cursor();
    std::tuple<int,int> GetGlobalPos();
    void SetGlobalPos(std::tuple<int,int>);
    ~Cursor();

};

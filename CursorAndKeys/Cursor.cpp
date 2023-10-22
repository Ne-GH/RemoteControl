/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/23 00:47
*******************************************************************************/

#include "Cursor.h"

#include <QCursor>

Cursor::Cursor() {

}

std::tuple<int, int> Cursor::GetGlobalPos() {
    auto pos = QCursor::pos();
    return {pos.x(),pos.y()};
}

void Cursor::SetGlobalPos(std::tuple<int, int> new_pos) {
    auto [x,y] = new_pos;
    QCursor::setPos(x,y);
}

Cursor::~Cursor() {

}

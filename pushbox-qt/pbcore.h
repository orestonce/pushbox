#pragma once

#include <string>
#include <vector>
#include <cstdint>
//Qt Creator 需要在xxx.pro 内部增加静态库的链接声明
//LIBS += -L$$PWD -lpbcore-impl

int32_t Go2Cpp_GetStageMax();
void Go2Cpp_SetStage(int32_t in0);
struct Point{
	int32_t X;
	int32_t Y;
};
struct PushBoxMap{
	int32_t Stage;
	int32_t MapMaxY;
	int32_t MapMaxX;
	std::string LastAction;
	std::vector<Point> Tree;
	std::vector<Point> Box;
	std::vector<Point> Goal;
	Point Boy;
};
PushBoxMap Go2Cpp_GetDataForQt();
bool Go2Cpp_DoAction(std::string in0);
bool Go2Cpp_GetIsGamePass();

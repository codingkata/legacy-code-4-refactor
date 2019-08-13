// Copyright 2019 <carryzhao>
#include "demo.h"

void mars_practice::CMarsHandle::Init() {
    // 操作符号限制
    setOperation.insert('L');
    setOperation.insert('M');
    setOperation.insert('R');

    // 表示4个方向的位置数据,用于方向改变处理
    vecCircleDirection.push_back('E');  // 规定东方向为0位置，顺时针方向递增位置
    vecCircleDirection.push_back('S');
    vecCircleDirection.push_back('W');
    vecCircleDirection.push_back('N');

    // 表示方位对应的下标位置和移动方向，用于移动操作处理数据
    mapDirectionDatas.insert(std::make_pair('E', STLocation(0, +1))); // 规定东方向为X正轴方向+1
    mapDirectionDatas.insert(std::make_pair('S', STLocation(1, -1)));
    mapDirectionDatas.insert(std::make_pair('W', STLocation(2, -1)));
    mapDirectionDatas.insert(std::make_pair('N', STLocation(3, +1)));
}

void mars_practice::CMarsHandle::TurnLeft(int &iDcur) {
    iDcur = (iDcur + 4 - 1) % 4;
}

void mars_practice::CMarsHandle::TurnRight(int &iDcur) {
    iDcur = (iDcur + 1) % 4;
}

void mars_practice::CMarsHandle::MoveStep(int iDcur, int iXmax, int iYmax, int &iXcur, int &iYcur, bool &bRip) {
    int iXnext = iXcur + mapDirectionDatas[vecCircleDirection[iDcur]].iLocationWeight;    // x轴下一个移动位置
    int iYnext = iYcur + mapDirectionDatas[vecCircleDirection[iDcur]].iLocationWeight;    // y轴下一个移动位置
    if (iDcur % 2 == 0 && iXnext <= iXmax && iXnext >= 0)        // x轴方向移动满足要求
        iXcur = iXnext;
    else if (iDcur % 2 == 1 && iYnext <= iYmax && iYnext >= 0)   // Y轴方向移动满足要求
        iYcur = iYnext;
    else
        bRip = true;
}

int mars_practice::CMarsHandle::GetDirection(char cDirection) {
    return mapDirectionDatas[cDirection].iLocation;
}

char mars_practice::CMarsHandle::GetDirection(int iDirection) {
    return vecCircleDirection[iDirection];
}

int mars_practice::CMarsHandle::checkPara(int iXmax, int iYmax) {
    if (iXmax <= 0 || iYmax <= 0) return -1;
    return 0;
}

int mars_practice::CMarsHandle::checkPara(int iXmax, int iYmax, int iXcur, int iYcur, char cDirectionInput) {
    if (iXcur < 0 || iXcur > iXmax || iYcur < 0 || iYcur > iYmax) return -2;
    if (mapDirectionDatas.count(cDirectionInput) == 0) return -3;
    return 0;
}

int mars_practice::CMarsHandle::checkPara(const std::string &strOperation) {
    for (unsigned i = 0; i < strOperation.size(); ++i) {
        if (setOperation.count(strOperation[i]) == 0) return -4;
    }
    return 0;
}

int MarsMain() {
    mars_practice::CMarsHandle cMarsHandle;
    cMarsHandle.Init();

    // 用户输入处理
    int iXmax = 5, iYmax = 5;                // 最大边界X值/Y值
    int iXinput = 1, iYinput = 2;            // 用户输入位置
    char cDirectionInput = 'N';              // 用户输入方向
    std::string strOperation = "LMLMLMLMM";  // 具体操作内容
    int iLineInputCur = 1;                   // 当前输入的正确行数
    std::string strTmpInput;                 // 用户每行内容
    std::vector <mars_practice::STParaGroup> vecUserInput;// 用户输入参数组
    while (std::getline(std::cin, strTmpInput)) {
        std::stringstream ss;
        ss << strTmpInput;
        if (iLineInputCur == 1) {            // 表示最大边界输入行
            ss >> iXmax >> iYmax;
            if (cMarsHandle.checkPara(iXmax, iYmax) != 0)
                std::cout << "max boundary input err, input again:" << std::endl;
            else
                iLineInputCur++;
        } else if (iLineInputCur % 2 == 0) { // 表示起始位置输入行
            ss >> iXinput >> iYinput >> cDirectionInput;
            if (cMarsHandle.checkPara(iXmax, iYmax, iXinput, iYinput, cDirectionInput) != 0)
                std::cout << "start location input err, input again:" << std::endl;
            else
                iLineInputCur++;
        } else if (iLineInputCur % 2 == 1) { // 表示操作内容输入行
            strOperation = strTmpInput;
            if (cMarsHandle.checkPara(strOperation) != 0)
                std::cout << "operation input err, input again:" << std::endl;
            else {
                iLineInputCur++;
                mars_practice::STParaGroup stUserPara(iXinput, iYinput, cDirectionInput, strOperation);
                vecUserInput.push_back(stUserPara); // 写入用户的多组输入
            }
        }
        if (strTmpInput.empty()) break; // 输入空行为结束
    }

    // 主处理逻辑
    for (unsigned i = 0; i < vecUserInput.size(); ++i) {
        bool bRip = false;
        int iDcur = cMarsHandle.GetDirection(vecUserInput[i].cDirectionInput); // 当前方向位置
        // 按操作步骤遍历处理
        for (unsigned j = 0; j < vecUserInput[i].strOperation.size(); ++j) {
            switch (vecUserInput[i].strOperation[j]) {
                case 'L':    // 左转
                    cMarsHandle.TurnLeft(iDcur);
                    break;
                case 'R':    // 右转
                    cMarsHandle.TurnRight(iDcur);
                    break;
                case 'M':    // 前进一步
                    cMarsHandle.MoveStep(iDcur, iXmax, iYmax, vecUserInput[i].iXinput, vecUserInput[i].iYinput, bRip);
                    break;
            }
        }
        // 结果输出
        std::cout << vecUserInput[i].iXinput << " " << vecUserInput[i].iYinput << " "
                  << cMarsHandle.GetDirection(iDcur);
        if (bRip == true) std::cout << " RIP" << std::endl;
        else std::cout << std::endl;
    }
    return 0;
}


// Copyright 2019 <carryzhao>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>

namespace mars_practice {

    struct STLocation {
        int iLocation;          // 下标位置
        int iLocationWeight;    // 位置代表的权重
        STLocation() {}

        STLocation(int iLocat, int iLocatWeight) {
            iLocation = iLocat;
            iLocationWeight = iLocatWeight;
        }
    };

    struct STParaGroup {
        int iXinput;
        int iYinput;
        char cDirectionInput;
        std::string strOperation;

        STParaGroup() {}

        STParaGroup(int iX, int iY, char cD, std::string &strOper) {
            iXinput = iX;
            iYinput = iY;
            cDirectionInput = cD;
            strOperation = strOper;
        }
    };

    class CMarsHandle {
    public:
        void Init();

        void TurnLeft(int &iDcur);

        void TurnRight(int &iDcur);

        void MoveStep(int iDcur, int iXmax, int iYmax, int &iXcur, int &iYcur, bool &bRip);

        int GetDirection(char cDirection);   // 获取方向-数值
        char GetDirection(int iDirection);   // 获取方向-字符
        int checkPara(int iXmax, int iYmax); // 参数检查
        int checkPara(int iXmax, int iYmax, int iXcur, int iYcur, char cDeriction);

        int checkPara(const std::string &strOperation);

    public:
        std::vector<char> vecCircleDirection;         // 表示方位对应的下标位置和移动方向
        std::map<char, STLocation> mapDirectionDatas; // 表示4个方向的位置数据
        std::set<char> setOperation;                  // 操作符号限制
    };

}

int MarsMain();


#include <vector>
#include <iostream>
#include <cmath>
#include "const.hpp"
#include "./lib_IdealMHD_1D/idealMHD_1D.hpp"
#include "./lib_pic1D_cpp/pic1D.hpp"


class MHDPIC1D
{
private:
    IdealMHD1D idealMHD1D;
    PIC1D pIC1D;

public:

    void initialize();

    void oneStep();

    void save();

private:

};



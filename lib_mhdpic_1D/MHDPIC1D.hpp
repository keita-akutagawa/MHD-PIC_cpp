#include <vector>
#include <iostream>
#include <cmath>
#include "const.hpp"
#include "./lib_IdealMHD_1D/idealMHD_1D.hpp"
#include "./lib_pic1D_cpp/pic1D.hpp"


class MHDPIC1D
{
private:
    FluxSolver mhdFluxSolver1, mhdFluxSolver2;
    Flux mhdFluxF1, mhdFluxF2;
    std::vector<std::vector<double>> mhdU1;
    std::vector<std::vector<double>> mhdU1Bar;
    std::vector<std::vector<double>> mhdU2;
    std::vector<std::vector<double>> mhdU2Bar;

    std::vector<Particle> picParticlesIon;
    std::vector<Particle> picParticlesElectron;
    std::vector<std::vector<double>> picE;
    std::vector<std::vector<double>> picB;
    std::vector<std::vector<double>> picCurrent;
    std::vector<std::vector<double>> picTmpE;
    std::vector<std::vector<double>> picTmpB;
    std::vector<std::vector<double>> picTmpCurrent;

    InitializeParticle picInitializeParticle;
    ParticlePush picParticlePush;
    FieldSolver picFieldSolver;
    CurrentCalculater picCurrentCalculater;

    std::vector<double> interlockingFunction;

public:
    MHDPIC1D() : 
    mhdU1(8, std::vector<double>(MHD::nx, 0.0)),
    mhdU1Bar(8, std::vector<double>(MHD::nx, 0.0)), 
    mhdU2(8, std::vector<double>(MHD::nx, 0.0)),
    mhdU2Bar(8, std::vector<double>(MHD::nx, 0.0)), 

    picParticlesIon(PIC::totalNumIon), 
    picParticlesElectron(PIC::totalNumElectron), 
    picE(3, std::vector<double>(PIC::nx, 0.0)), 
    picB(3, std::vector<double>(PIC::nx, 0.0)), 
    picCurrent(3, std::vector<double>(PIC::nx, 0.0)), 
    picTmpE(3, std::vector<double>(PIC::nx, 0.0)), 
    picTmpB(3, std::vector<double>(PIC::nx, 0.0)), 
    picTmpCurrent(3, std::vector<double>(PIC::nx, 0.0)), 

    interlockingFunction(interfaceLength, 0.0)
    
    {
        for (int i = 0; interfaceLength; i++) {
            interlockingFunction[i] = 0.5 * (
                1.0 + std::cos(PI * (static_cast<double>(i) - 0.0) / interfaceLength)
            );
        }
    }


    virtual void initialize();

    void oneStep();

    void save();

private:

};



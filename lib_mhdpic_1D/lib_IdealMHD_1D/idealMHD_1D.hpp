#include <vector>
#include <string>
#include "const.hpp"
#include "flux_solver.hpp"
#include "boundary.hpp"


class IdealMHD1D
{
private:
    FluxSolver fluxSolver;
    Flux fluxF;
    std::vector<std::vector<double>> U;
    std::vector<std::vector<double>> UBar;
    Boundary boundary;

public:
    IdealMHD1D() : 
    U(8, std::vector<double>(MHD::nx, 0.0)),
    UBar(8, std::vector<double>(MHD::nx, 0.0))
    {}

    virtual void initializeU(); 

    void oneStepRK2();

    void save(
        std::string directoryname, 
        std::string filenameWithoutStep, 
        int step
    );

    std::vector<std::vector<double>> getU();

    void calculateDt();
};




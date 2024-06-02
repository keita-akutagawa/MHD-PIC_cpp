#include "const.hpp"
#include "hlld.hpp"


using namespace MHD;

class FluxSolver
{
private:
    HLLD hLLD;
    Flux flux;

public:
    Flux getFluxF(
        const std::vector<std::vector<double>> U
    );
};



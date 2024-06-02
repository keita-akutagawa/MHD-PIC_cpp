#include "flux_solver.hpp"


using namespace MHD;

Flux FluxSolver::getFluxF(
    const std::vector<std::vector<double>> U
)
{
    hLLD.calculateFlux(U);
    flux = hLLD.getFlux();

    return flux;
}


#include <cmath>
#include "filter.hpp"


using namespace PIC;

void Filter::resetRho()
{
    for (int i = 0; i < nx; i++) {
        rho[i] = 0.0;
    }
}


void Filter::calculateRhoOfOneSpecies(
    const std::vector<Particle>& particlesSpecies, 
    double q, int nStart, int nEnd
)
{
    double cx1, cx2; 
    int xIndex1, xIndex2;
    double xOverDx;
    int wallXCondition;

    for (int i = nStart; i < nEnd; i++) {
        xOverDx = particlesSpecies[i].x / dx;

        xIndex1 = std::floor(xOverDx);
        xIndex2 = xIndex1 + 1;
        xIndex2 = (xIndex2 == nx) ? 0 : xIndex2;
        wallXCondition = (xIndex2 == 0) ? 0 : 1;

        cx1 = xOverDx - xIndex1;
        cx2 = 1.0 - cx1;

        rho[xIndex1] += q * cx2;
        rho[xIndex2] += q * cx1 * wallXCondition;
    }
}


void Filter::calculateRho(
    const std::vector<Particle>& particlesIon, 
    const std::vector<Particle>& particlesElectron
)
{
    calculateRhoOfOneSpecies(particlesIon, qIon, 0, totalNumIon);
    calculateRhoOfOneSpecies(particlesElectron, qElectron, 0, totalNumElectron);
}



void Filter::langdonMarderCorrection(
    std::vector<double>& F, 
    std::vector<std::vector<double>>& E, 
    const std::vector<Particle>& particlesIon, 
    const std::vector<Particle>& particlesElectron
)
{
    resetRho();
    calculateRho(particlesIon, particlesElectron);

    for (int i = 1; i < nx; i++) {
        F[i] = (E[0][i] - E[0][i - 1])/dx - rho[i] / epsilon0;
    }
    F[0] = (E[0][0] - 0.0)/dx - rho[0] / epsilon0;

    for (int i = 0; i < nx-1; i++) {
        E[0][i] += dt * dOfLangdonMarderCorrection * (F[i + 1] - F[i]) / dx;
    }
    E[0][nx - 1] += dt * dOfLangdonMarderCorrection * (0.0 - F[nx - 1]) / dx;
}


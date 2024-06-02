#include <vector>
#include <string>


using namespace MHD;

class Boundary
{
private:

public:
    std::string boundaryType;

    void periodicBoundary(
        std::vector<std::vector<double>>& U
    );

    void symmetricBoundary2nd(
        std::vector<std::vector<double>>& U
    );

private:

};



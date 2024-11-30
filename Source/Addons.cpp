#include "Addons.h"

Point::Point() {

}

Point::Point(int x, int y) : x(x), y(y) {}


int RegionDestination::maxX = 0;
int RegionDestination::maxY = 0;

int RegionDestination::regionSize = 0;
int RegionDestination::maxHeight = 0;
int RegionDestination::minHeight = 0;
int RegionDestination::maxWidth = 0;
int RegionDestination::minWidth = 0;

RegionDestination::RegionDestination() {

}

RegionDestination::RegionDestination(int rowsPos, int columnPos) : rowsPos(rowsPos), columnPos(columnPos) {

    this->rowsPos = ((columnPos - RegionDestination::maxHeight) / RegionDestination::regionSize);
    this->columnPos = ((rowsPos - RegionDestination::minWidth) / RegionDestination::regionSize);


    if (this->rowsPos > RegionDestination::maxX || this->columnPos > RegionDestination::maxY) {
        std::cout << "Error Region Calculation out of Bounds to Big\n";
    }

    if (this->rowsPos < 0 || this->columnPos < 0) {
        std::cout << "Error Region Calculation out of Bounds to low\n";
    }
}

void RegionDestination::CalculateRegionPos(int rowsPos, int columnPos) {
    this->rowsPos = ((columnPos - RegionDestination::maxHeight) / RegionDestination::regionSize);
    this->columnPos = ((rowsPos - RegionDestination::minWidth) / RegionDestination::regionSize);

    if (this->rowsPos > RegionDestination::maxX || this->columnPos > RegionDestination::maxY) {
        std::cout << "Error Region Calculation out of Bounds to Big\n";
    }

    if (this->rowsPos < 0 || this->columnPos < 0) {
        std::cout << "Error Region Calculation out of Bounds to low\n";
    }
}
void RegionDestination::CalculateTilePos(int regionRowsPos, int regionColumnPos) {
    regionRowsPos -= RegionDestination::minWidth;
    regionColumnPos -= RegionDestination::maxHeight;
    regionRowsPos -= (this->columnPos * 600);
    regionColumnPos -= (this->rowsPos * 600);
    regionRowsPos /= 40;
    regionColumnPos /= 40;
    this->columnTilePos = regionRowsPos;
    this->rowsTilePos = regionColumnPos;
    /*To powinno byæ odwrotnie dlatego na koniec zemieniam je ze sob¹ */
}

void RegionDestination::CalculateAbsoluteTilePos() {
    absoluteRowsTilePos = (rowsPos * 15) + rowsTilePos;
    absoluteColumnTilePos = (columnPos * 15) + columnTilePos;
}

double CalculateEuclidean(int x1,int x2,int y1,int y2) {
    double x = std::pow(x2 - x1, 2);
    double y = std::pow(y2 - y1, 2);;
    return std::sqrt(x+y);
}

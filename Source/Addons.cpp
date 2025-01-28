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

void RegionDestination::RecalculateFromAbsolute() { // not tested
	rowsPos = absoluteRowsTilePos / 15;
	columnPos = absoluteColumnTilePos / 15;
	rowsTilePos = absoluteRowsTilePos % 15;
	columnTilePos = absoluteColumnTilePos % 15;
}

bool CheckBoundaries(RegionDestination& start, unsigned short rowsSize, unsigned short columnSize) {
	if (start.rowsTilePos > 14) {
		start.rowsTilePos = 0;
		start.rowsPos++;
		if (start.rowsPos > rowsSize - 1) {
			std::cout << "Out of bounds row to big\n";
			return false;
		}
	}

	if (start.rowsTilePos < 0) {
		start.rowsTilePos = 14;
		start.rowsPos--;
		if (start.rowsPos < 0) {
			std::cout << "Out of bounds row to small\n";
			return false;
		}
	}
	if (start.columnTilePos > 14) {
		start.columnTilePos = 0;
		start.columnPos++;
		if (start.columnPos > columnSize) {
			std::cout << "Out of bounds columns to big\n";
			return false;
		}
	}
	if (start.columnTilePos < 0) {
		start.columnTilePos = 14;
		start.columnPos--;
		if (start.columnPos < 0) {
			std::cout << "Out of bounds columns to small\n";
			return false;
		}
	}
	return true;
}

bool CheckBoundariesAdvanced(RegionDestination& start, unsigned short rowsSize, unsigned short columnSize) {
	if (start.rowsTilePos > 14) {
		start.rowsTilePos -= 15;
		start.rowsPos++;
		if (start.rowsPos >= rowsSize) {
			//std::cout << "Out of bounds row too big\n";
			return false;
		}
	}

	if (start.rowsTilePos < 0) {
		start.rowsTilePos = 15 + (start.rowsTilePos % 15);
		if (start.rowsTilePos == 15) start.rowsTilePos = 0;
		if (start.rowsPos == 0) {
			//std::cout << "Out of bounds row too small\n";
			return false;
		}
		start.rowsPos--;
	}

	if (start.columnTilePos > 14) {
		start.columnTilePos -= 15;
		start.columnPos++;
		if (start.columnPos >= columnSize) {
			//std::cout << "Out of bounds column too big\n";
			return false;
		}
	}

	if (start.columnTilePos < 0) {
		start.columnTilePos = 15 + (start.columnTilePos % 15);
		if (start.columnTilePos == 15) start.columnTilePos = 0;
		if (start.columnPos == 0) {
			//std::cout << "Out of bounds column too small\n";
			return false;
		}
		start.columnPos--;
	}

	if (start.rowsTilePos < 0 || start.rowsTilePos > 14) {
		//std::cout << "Error: rowsTilePos is out of bounds! rowsTilePos = " << start.rowsTilePos << "\n";
		return false;
	}
	if (start.columnTilePos < 0 || start.columnTilePos > 14) {
		//std::cout << "Error: columnTilePos is out of bounds! columnTilePos = " << start.columnTilePos << "\n";
		return false;
	}

	return true;
}

bool CheckSimpleBoundaries(RegionDestination& start, unsigned short rowsSize, unsigned short columnSize) {
	if (start.rowsPos > rowsSize - 1) {
		std::cout << "Out of bounds row to big\n";
		return false;
	}
	if (start.rowsPos < 0) {
		std::cout << "Out of bounds row to small\n";
		return false;
	}
	if (start.columnPos > columnSize) {
		std::cout << "Out of bounds columns to big\n";
		return false;
	}
	if (start.columnPos < 0) {
		std::cout << "Out of bounds columns to small\n";
		return false;
	}
	return true;
}

bool CheckBoundariesAbsolute(RegionDestination& dest) {
	if (dest.absoluteRowsTilePos < 0) { return false; }
	if (dest.absoluteColumnTilePos < 0) { return false; }
	if (dest.absoluteRowsTilePos > 299) { return false; } // Ta liczba z dupy ale niech narazie zostanie
	if (dest.absoluteColumnTilePos > 299) { return false; }
	return true;
}

double CalculateEuclidean(int x1,int x2,int y1,int y2) {
    double x = std::pow(x2 - x1, 2);
    double y = std::pow(y2 - y1, 2);;
    return std::sqrt(x+y);
}

Point GetRectangleCenter(const SDL_Rect rect) {
	Point point;
	point.x = rect.x + (rect.w * 0.5);
	point.y = rect.y + (rect.h * 0.5);
	return point;

}

unsigned int RectanglePointDistance(const SDL_Rect rect, const Point point) {
	return std::abs(rect.x - point.x) + std::abs(rect.y - point.y);

}

unsigned int PointsDistance(const Point point, const Point point2) {
	return std::abs(point.x - point2.x) + std::abs(point.y - point2.y);
}


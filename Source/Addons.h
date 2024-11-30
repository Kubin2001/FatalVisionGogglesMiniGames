#pragma once
#include <iostream>
#include <math.h>

struct Point
{
	int x = 0;
	int y = 0;
	Point();
	Point(int x, int y);
};



struct RegionDestination {
	int rowsPos = 0; //Du¿e Regiony
	int columnPos = 0;

	int rowsTilePos = 0; //Pole w regionie 
	int columnTilePos = 0;

	int absoluteRowsTilePos = 0;
	int absoluteColumnTilePos = 0;

	static int maxX;
	static int maxY;

	static int regionSize;
	static int maxHeight;
	static int minHeight;
	static int maxWidth;
	static int minWidth;

	RegionDestination();
	RegionDestination(int x, int y);

	void CalculateRegionPos(int rowsPos, int columnPos);
	void CalculateTilePos(int regionRowsPos, int regionColumnPos);
	void CalculateAbsoluteTilePos();

	bool operator==(const RegionDestination& other) const {
		return absoluteRowsTilePos == other.absoluteRowsTilePos &&
			absoluteColumnTilePos == other.absoluteColumnTilePos;
	}


};



double CalculateEuclidean(int x1, int x2, int y1, int y2);
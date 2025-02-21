#pragma once
#include <iostream>
#include <math.h>
#include <SDL.h>
#include <vector>

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
	void RecalculateFromAbsolute();

	bool operator==(const RegionDestination& other) const {
		return absoluteRowsTilePos == other.absoluteRowsTilePos &&
			absoluteColumnTilePos == other.absoluteColumnTilePos;
	}


};

bool CheckBoundaries(RegionDestination& start, unsigned short rowsSize, unsigned short columnSize);

bool CheckBoundariesAdvanced(RegionDestination& start, unsigned short rowsSize, unsigned short columnSize);

bool CheckSimpleBoundaries(RegionDestination& start, unsigned short rowsSize, unsigned short columnSize);

bool CheckBoundariesAbsolute(RegionDestination& dest);

double CalculateEuclidean(int x1, int x2, int y1, int y2);

Point GetRectangleCenter(const SDL_Rect rect);

unsigned int RectanglePointDistance(const SDL_Rect rect, const Point point);

unsigned int PointsDistance(const Point point, const Point point2);




class AnyData {
    public:
    virtual ~AnyData() = default;

    template <typename T>
    T& Get();

    template <typename T>
    void Set(T tempData);
};





template <typename T>
class AnyContatiner : public AnyData {
    public:
    T data;

    AnyContatiner() = default;

    AnyContatiner(T temp) {
        data = temp;
    }


};

template <typename T>
T& AnyData::Get() {
    auto temp = static_cast<AnyContatiner<T>*>(this); // Can be static not dynamic cause only one class is using inheritance
    if (!temp) {
        std::cerr << "Error: Wrong cast in AnyDataGet deafault value returned\n";
    }
    return temp->data;
}


template <typename T>
void AnyData::Set(T tempData) {
    auto temp = static_cast<AnyContatiner<T>*>(this); // Can be static not dynamic cause only one class is using inheritance
    if (!temp) {
        std::cerr << "Error: Data set uncorrectly in any data\n";
        return;
    }
    temp->data = tempData;
}

/*Pointer for ref safety in containers like std vector for use with ref Pointer*/

template <typename T>
class WrappedPointer {
    private:
        T* pointer = nullptr;

    public:

        T*& Get() {
            return pointer;
        }

        T& GetVal() {
            return *pointer;
        }

        T& operator*() {
            return *pointer;
        }

        T* operator->() {
            return pointer;
        }
};

/*Designed to work only with Warped Pointer Class*/

template <typename T>
class RefPointer {
    private:
        T* mainArgument = nullptr;
        std::vector<T**> references;
    public:

        RefPointer() {

        }


        RefPointer(T* mainArg) {
            mainArgument = mainArg;
        }


        void Make(T* mainArg) {
            mainArgument = mainArg;
        }

        T* Get() {
            return mainArgument;
        }

        T& GetVal() {
            return *mainArgument;
        }

        void AddRef(T*& ref) {
            ref = mainArgument;
            references.push_back(&ref);
        }

        ~RefPointer() {
            for (auto& it : references) {
                *it = nullptr;
            }
            delete mainArgument;
        }

        T& operator*() {
            return *mainArgument;
        }

        T* operator->() {
            return mainArgument;
        }

        size_t RefCount() {
            return references.size();
        }

        void ClearRef(T*& ref) {

            for (size_t i = 0; i < references.size(); i++) {
                if (references[i] == &ref) {
                    references.erase(references.begin() + i);
                    break;
                }
            }
        }

        void ClearRefs() {
            for (auto& it : references) {
                *it = nullptr;
            }
            references.clear();
        }

};
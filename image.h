#pragma once
#include <string>
#include "airport.h"
#include "datReader.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;


using namespace std;


class image{
    public:
    PNG* createImage(vector<airport> airportSplitDATA, vector<datReader::path> pathDATA);
    PNG* connect(PNG* pathMap, unsigned startX, unsigned startY, unsigned endX, unsigned endY);
    unsigned int lonCoordinateConvert(unsigned int lon, unsigned int width);
    unsigned int latCoordinateConvert(unsigned int lat, unsigned int height);
};
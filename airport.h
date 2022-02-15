#pragma once
#include <string>
#include <map>
using namespace std;
#include "cs225/PNG.h"
class airport {
        public:
                string IATA;
                double lat;
                double lon; 
                airport();
                airport(string inputIATA, string inputlat,string inputlon);

                cs225::PNG* createImage();
                cs225::PNG* mergeImage();
                void print();
                             
};
        
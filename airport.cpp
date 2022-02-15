#include "airport.h"
#include <string>
#include "datReader.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;
airport::airport(){

};
airport::airport(string inputIATA, string inputlat, string inputlon): IATA(inputIATA){
        // double curLat = -33333;
        // double curLon = -33333;
        // if (inputlat.substr(0,1) == "-") {
        //         curLat = -stod(inputlat.substr(1));
        // } else {
        //         curLat = stod(inputlat);
        // }
        // if (inputlon.substr(0,1) == "-") {
        //         curLon = -stod(inputlon.substr(1));
        // } else {
        //         curLon = stod(inputlon);
        // }
        try {
                lat = std::stod(inputlat);
        } catch (const std::invalid_argument&) {
                lat = 0;
        } catch (const std::out_of_range&) {
                std::cerr << "Argument is out of range for a double\n";
        }
        try {
                lon = std::stod(inputlon);
        } catch (const std::invalid_argument&) {
                lon = 0;
        } catch (const std::out_of_range&) {
                std::cerr << "Argument is out of range for a double\n";
        }
}

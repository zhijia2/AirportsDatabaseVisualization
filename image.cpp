#include "airport.h"
#include "image.h"
#include <string>
#include <math.h>
#include "datReader.h"
#include "cs225/HSLAPixel.h"
using namespace std;
using namespace cs225;

PNG* image::createImage(vector<airport> airportSplitDATA, vector<datReader::path> pathDATA) {
    HSLAPixel black = HSLAPixel(0, 0, 0);
    HSLAPixel red = HSLAPixel(0, 1, 0.5);
    HSLAPixel green = HSLAPixel(86, 1, 0.31, 1);
    std::map<std::string,airport >nodes;
    for (auto i: airportSplitDATA){
      nodes[i.IATA] = i;
    }
    unsigned int width = 2400;
    unsigned int height = 1200;
    PNG* map_path = new PNG(width, height);
    for (auto it : pathDATA) {
      airport source = nodes[it.source];
      airport destination = nodes[it.destination];
      unsigned int y_coord_source = latCoordinateConvert(abs(90-source.lat), height);
      unsigned int x_coord_source = lonCoordinateConvert(180+source.lon, width);
      unsigned int y_coord_destination = latCoordinateConvert(abs(90-destination.lat), height); 
      unsigned int x_coord_destination = lonCoordinateConvert(180+destination.lon, width);
      connect(map_path, x_coord_source, y_coord_source, x_coord_destination, y_coord_destination);
    }
    PNG* map_layout = new PNG(width, height);
    for (auto it :airportSplitDATA){
        unsigned int y_coord = latCoordinateConvert(abs(90-it.lat), height);
        unsigned int x_coord = lonCoordinateConvert(180+it.lon, width);
        if (x_coord != 0 && x_coord != width-1) {
          if (y_coord != 0 && y_coord != height-1) {
            map_layout->getPixel(x_coord - 1, y_coord) = black;
            map_layout->getPixel(x_coord - 2, y_coord) = black;

            map_layout->getPixel(x_coord, y_coord + 1) = black;
            map_layout->getPixel(x_coord, y_coord + 2) = black;

            map_layout->getPixel(x_coord + 1, y_coord) = black;
            map_layout->getPixel(x_coord + 2, y_coord) = black;

            map_layout->getPixel(x_coord, y_coord - 1) = black;
            map_layout->getPixel(x_coord, y_coord - 2) = black;

          }
        }
        map_layout->getPixel(x_coord, y_coord) = black;
    }
    PNG* map_image = new PNG(width, height);
    map_image->readFromFile("data/map.png");

    for (unsigned int x = 0; x < map_image->width(); x++ ) {
      for (unsigned int y = 0; y < map_image->height(); y++) {
        HSLAPixel &path = map_path->getPixel(x, y);
        HSLAPixel &layout = map_layout->getPixel(x, y); 
        HSLAPixel &base = map_image->getPixel(x, y);
        if (path == black) base = green;
        if (layout == black) base = red;
      }
    }
    return map_image;
}
PNG* image::connect(PNG* pathMap, unsigned startX, unsigned startY, unsigned endX, unsigned endY) {
    HSLAPixel black = HSLAPixel(0, 0, 0);
    unsigned tempSY = startY - 180;
    unsigned tempEY = endY - 180;
    int m_new = 2 * (tempEY - tempSY);
    int slope_error_new = m_new - (endX - startX);


    unsigned int y = startY;
    for (unsigned int x = startX; x <= endX; x++) {
      // Add slope to increment angle formed
      slope_error_new += m_new;
 
      // Slope error reached limit, time to
      // increment y and update slope error.
      if (slope_error_new >= 0) {
         y++;
         slope_error_new  -= 2 * (endX - startX);
      }
      pathMap->getPixel(x, y) = black;
   }
    return pathMap;
}

unsigned int image::latCoordinateConvert(unsigned int lat, unsigned int height) {
  int correctionVal = 65;
  if (lat < 90) {
    correctionVal += -20;
  }
  double temp = (height/180);
  return (lat * temp) + correctionVal;
}

unsigned int image::lonCoordinateConvert(unsigned int lon, unsigned int width) { 
  int correctionVal = 85;
  if (lon > 150 && lon < 240) {
    correctionVal += 70;
  } else if (lon > 240 && lon < 300) {
    correctionVal += 110;
  } else if (lon > 300)
    correctionVal += 130;
  double temp = (width/360);
  return (lon * temp) + correctionVal;
}
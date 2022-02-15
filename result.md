#Result
## Final Project CS225 Spring 2021

The first thing we did is convert the raw data into two vectors. The first one is the collection of a struct we created called path, which stores the route information, and include the information of source and destination airports name as well as  the route distance.
The second one is the collection of the airports, which store the airport objects including the position and other information of the airports.

The equation we used to calculate the distance called Haversine Formula, which is a method used to determine the great-circle distance between two points on a sphere given their longitudes and latitudes.

The algorithm we used to get the shortest path is the BFS.

After convert the data to a usable formation, we begin to visualize the information which we got from the dataset and our work.
We use the function connect() to convert the path and use the function CreateImage() to visualize the airports. In the visualization process, we using function latCoordinateConvert() and lonCoordinateConvert() converting the Lat-Long position to a position suit the image and using an variable called slope_error_new to adjust the specific point in the path.

After above work we get this output you can see red points in the picture which represent the airport and the green lines in the picture which represent the path we gotten.
![Output](output.png)

#pragma once

//#include <LinkedList.h>
#include <ArduinoQueue.h>
#include "helper.h"

#define NUM_DATA_POINTS 70 

// Class that builds a graph of time-series data
// The data is 1 dimensional with time being inferred from a given (consistent) interval
// The data is displayed (in displayHandler.cpp) from right to left (right having the most recent data)
class Graph {
    public:

        //LinkedList<uint32_t> dataPoints = LinkedList<uint32_t>();
        ArduinoQueue<float> dataPoints = ArduinoQueue<float>(NUM_DATA_POINTS);
        uint32_t dataPointInterval; // ms between each data point

        uint32_t xpos; // of 0,0 (For best results - make this divisble by the NUM_DATA_POINTS)
        uint32_t ypos; // of 0,0
        uint32_t screenWidth;
        uint32_t yScaler; // if x, every +1 change in a data point will correlate to that data point being displayed x pixels higher (This can be changed on the fly to rescale the graph)
        uint32_t col;

        uint32_t dataCollectionTimer;

        uint32_t ptp_distance_x;  // X-distance between each data point on the graph


        float *trackedVar;

    public:
        Graph(uint32_t posx, uint32_t posy, uint32_t screen_width, uint32_t scale, uint32_t colour, uint32_t dataCollectionInterval);

        void trackVariable(float *var); // Takes float and converts it to uint32 to be stored in dataPoints Linked List

        void runDataCollector();

        void clearDataPoints();

};
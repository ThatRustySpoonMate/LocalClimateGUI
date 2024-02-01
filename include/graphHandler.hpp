#include "displayHandler.hpp"
//#include <LinkedList.h>
#include <ArduinoQueue.h>
#include "helper.h"

#define NUM_DATA_POINTS 30

class Graph {
    protected:

        //LinkedList<uint32_t> dataPoints = LinkedList<uint32_t>();
        ArduinoQueue<uint32_t> dataPoints = ArduinoQueue<uint32_t>(NUM_DATA_POINTS);
        uint32_t dataPointInterval; // ms between each data point

        uint32_t xpos; // of 0,0
        uint32_t ypos; // of 0,0

        uint32_t ptp_distance_x;  // X-distance between each data point on the graph


        float *trackedVar;

    public:
        Graph(uint32_t posx, uint32_t posy, uint32_t dataCollectionInterval);

        void trackVariable(float *var); // Takes float and converts it to uint32 to be stored in dataPoints Linked List

        void runDataCollector();

};
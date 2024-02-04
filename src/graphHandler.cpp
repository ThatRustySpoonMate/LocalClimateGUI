#include "graphHandler.hpp"


Graph::Graph(uint32_t posx, uint32_t posy, uint32_t screen_width, uint32_t scale, uint32_t colour, uint32_t dataCollectionInterval) {
    xpos = posx;
    ypos = posy;
    screenWidth = screen_width;
    yScaler = scale;
    col = colour;
    dataPointInterval = dataCollectionInterval;
    dataCollectionTimer = 0;

    // Determine the distance between all data points
    //ptp_distance_x = screenWidth / NUM_DATA_POINTS;
    ptp_distance_x = xpos / NUM_DATA_POINTS;

    // Initialize datapoints to all 0
    for(uint32_t i = 0; i < NUM_DATA_POINTS; i++) {
        dataPoints.enqueue(0);
    }

    return;
}


void Graph::trackVariable(float *var) {
    trackedVar = var;

    return;
}


void Graph::runDataCollector() {
    //static uint32_t dataCollectionTimer;

    if(every_n_ms(dataPointInterval, &dataCollectionTimer)) {
        // Remove oldest data item (if applicable)
        dataPoints.dequeue();

        // Add new element
        dataPoints.enqueue( *trackedVar  );

        // Debug - print all elements
        /*
        ArduinoQueue<uint32_t>::Node* currentNode = dataPoints.getHeadNode();
        while (currentNode != nullptr) {
            int element = currentNode->item;
            Serial.println(element);

            currentNode = currentNode->next;
        }
        */
        
    }


    return;
}


void Graph::clearDataPoints() {

    for(uint32_t i = 0; i < NUM_DATA_POINTS; i++) {
        dataPoints.dequeue();
    }

    return;
}
#include "graphHandler.hpp"


Graph::Graph(uint32_t posx, uint32_t posy, uint32_t dataCollectionInterval) {
    xpos = posx;
    ypos = posy;
    dataPointInterval = dataCollectionInterval;

    ptp_distance_x = ypos / NUM_DATA_POINTS;

    return;
}


void Graph::trackVariable(float *var) {
    trackedVar = var;

    return;
}


void Graph::runDataCollector() {
    static uint32_t dataCollectionTimer;

    if(every_n_ms(dataPointInterval, &dataCollectionTimer)) {
        // Remove oldest data item (if applicable)


        // Add new element
        dataPoints.enqueue( ( (uint32_t)*trackedVar ) );
        dataPoints.enqueue( ( (uint32_t)*trackedVar ) + 1 );
        dataPoints.enqueue( ( (uint32_t)*trackedVar ) + 2);
        dataPoints.enqueue( ( (uint32_t)*trackedVar ) + 3);
        dataPoints.enqueue( ( (uint32_t)*trackedVar ) + 4);
        dataPoints.enqueue( ( (uint32_t)*trackedVar ) + 5);

        // Debug - print all elements
        // Iterate through the temporary queue and print each element
        ArduinoQueue<uint32_t>::Node* currentNode = dataPoints.getHeadNode();
        while (currentNode != nullptr) {
            int element = currentNode->item;
            Serial.println(element);

            currentNode = currentNode->next;
        }

    }


    return;
}
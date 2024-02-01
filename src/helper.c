#include "helper.h"

#ifdef __cplusplus
  extern "C" {
#endif

uint8_t every_n_ms(uint32_t delay, uint32_t *timer) {

    if(millis() > *timer + delay) {
        *timer = millis();
        return true;
    } else {
        // Handle overflow of uint32_t type
        if(*timer >= (0xffffffff - delay)  ) {
            if(millis() < delay) {
                *timer = millis();
                return true;
            }
        }
        return false;
    }
}

#ifdef __cplusplus
}
#endif
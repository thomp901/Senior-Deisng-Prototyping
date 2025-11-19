//THIS CODE WAS GENERATED USING AI
//THIS IS INSTANTIATING THE C++ Library
//DEFINING THE C Functions



#include "Adafruit_MPL3115A2.h" // <-- CHANGE THIS!
#include "mpl3115a2_interface.h" 



// Instantiate the static C++ sensor object
static Adafruit_MPL3115A2 baro;

// Ensure C-style linking for the function DEFINITIONS
extern "C" {
    
    int32_t baro_init(void) {
        return baro.begin();
    }

    float baro_get_pressure_pascal(void) {
        return baro.getPressure();
    }
    
    float baro_get_altitude_meters(void) {
        return baro.getAltitude();
    }
}
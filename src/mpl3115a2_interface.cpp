#include "Adafruit_MPL3115A2.h"
#include "hardware/i2c.h"
#include "pico/types.h" // For int32_t and bool

// 1. Define the global C++ sensor object
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

// 2. Define C wrappers using extern "C"
extern "C" {
    
    int32_t baro_init() {
        // Calls the C++ library's begin function which handles WHOAMI check and mode setting.
        // It returns a bool, which we convert to the int32_t status expected by main.c
        bool success = baro.begin(i2c0); 
        return success ? 0 : -1; // Return 0 for success
    }

    float baro_get_pressure_pascal() {
        return baro.getPressure();
    }
    
    float baro_get_altitude_meters() {
        return baro.getAltitude();
    }

    float baro_get_temperature() {
        return baro.getTemperature();
    }
}
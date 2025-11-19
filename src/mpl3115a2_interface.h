//Utilized Ai to set up the enviorment:
//From C++ to C for the sensor

// src/mpl3115a2_interface.h

#ifdef __cplusplus
// If compiled by a C++ compiler, tell it to use C linkage for the functions below
extern "C" {
#endif

// Function Prototypes for C-compatible functions
int32_t baro_init(); 
float baro_get_pressure_pascal();
float baro_get_altitude_meters();
float baro_get_temperature();

#ifdef __cplusplus
// Close the extern "C" block
}
#endif
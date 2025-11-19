//This was generated using AI 
//Needed to be able to utilize the Librarys that were written
//for an ardiunio but wanted to utilize the Purdue Proton Board
#ifdef __cplusplus
// If compiled by a C++ compiler, tell it to use C linkage for the functions below
extern "C" {
#endif

// Function Prototypes for C-compatible functions
int32_t baro_init(void); 
float baro_get_pressure_pascal(void);
float baro_get_altitude_meters(void);

#ifdef __cplusplus
// Close the extern "C" block
}
#endif
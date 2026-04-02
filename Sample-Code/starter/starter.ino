/**
 * PROGRAM_OR_PROJECT_NAME
 *
 * SHORT_DESCRIPTION
 *
 * Assessment Name: InterRIoT-AT2-POR-Pt1-SimpleCircuits
 * Due:             YYYY-MM-DD
 * Name:            YOUR_NAME <STUDENT_ID@tafe.wa.edu.au>
 *
 */

/**--------------------------------------------------------------------------
 * External Source, Package, Module includes
 *---------------------------------------------------------------------------*/
// Includes


/**--------------------------------------------------------------------------
 * Declarations 
 *---------------------------------------------------------------------------*/

// Debugging Macros
//   1 = Debugging on
//   0 = Debugging off
#define DEBUG 1

#if DEBUG
  #define DEBUG_PRINT(x) Serial.print(x); Serial.print(" ");
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_BEGIN(x) Serial.begin(x); while(!Serial) {}
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_BEGIN(x)
#endif

// Macros


// Constants


// Variables


/**--------------------------------------------------------------------------
 * Hardware/Software Configuration
 *---------------------------------------------------------------------------*/
// Setting Up Hardware

void setup()
{
/**
 * This code executes ONCE per Power-up or Wake 
 */

}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop()
{
  /**
   * This code executes for as long as the hardware
   * is turned on, or not asleep
   */


}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/


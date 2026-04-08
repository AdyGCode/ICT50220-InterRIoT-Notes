/**
 * Debug Macros
 *
 * Use case:
 * - Allow for serial debugging of code
 *
 * Filename:        debug.h
 *
 * Name:            Adrian Gould
 *
 */

// Debugging Macros
//   1 = Debugging on
//   0 = Debugging off
// #define DEBUG 1

#if DEBUG
#define DEBUG_BEGIN(speed) \
  Serial.begin(speed); \
  while (!Serial) {}
#define DEBUG_PRINT(data) \
  Serial.print(data); \
  Serial.print(" ");
#define DEBUG_PRINTF(ifsh, ...) Serial.printf(ifsh, ##__VA_ARGS__)
#define DEBUG_PRINTLN(data) Serial.println(data);
#define DEBUG_FLUSH() Serial.flush();
#else
#define DEBUG_BEGIN(speed)
#define DEBUG_PRINT(debug)
#define DEBUG_PRINTLN(debug)
#define DEBUG_PRINTF(ifsh, ...)
#define DEBUG_FLUSH()
#endif

#ifndef ESC_MOTOR_HEADER
#define ESC_MOTOR_HEADER

#include <Arduino.h>

typedef void(*voidFunctionPointer)(); // Used for making commutation arrays

extern volatile byte sequenceStep; // Stores step in spinning sequence
extern volatile voidFunctionPointer motorSteps[6]; // Stores the functions to copmmute in the current commutation order
extern volatile voidFunctionPointer bemfSteps[6]; // Stores the functions to set the BEMF in the current commutation order

// PWM variables
extern volatile byte maxDuty;    // Upper limit to PWM (MUST be less than 254)
extern volatile byte duty;       // Current PWM duty
extern byte endClampThreshold;   // Stores how close you need to be to either extreme before the PWM duty is clamped to that extreme

// Other variables
extern volatile byte cyclesPerRotation;
extern volatile byte cycleCount;

extern volatile unsigned int currentRPM;
extern volatile unsigned int targetRPM;
extern volatile byte controlScheme;

extern bool reverse;
extern volatile bool motorStatus; // Stores if the motor is disabled (false) or not

extern const unsigned int spinUpStartPeriod;
extern const unsigned int spinUpEndPeriod;
extern const byte stepsPerIncrement;
extern const unsigned int spinUpPeriodDecrement;

// Buzzer period limits
extern const unsigned int maxBuzzPeriod;
extern const unsigned int minBuzzPeriod;



////////////////////////////////////////////////////////////
// Function declarations

/** @name setPWMDuty
   *  @brief Set the PWM duty of the motor
   *  @param deisredDuty Desired duty
   */
void setPWMDuty(byte deisredDuty);

/** @name enableMotor
   *  @brief Use this to enable the motor
   *  @param startDuty Motor duty to start with
   *  @return Returns true if the motor was enabled without issue
   */
bool enableMotor(byte startDuty);

/** @name windUpMotor
   *  @brief Winds up the motor to start spinning
   */
void windUpMotor();

/** @name setupMotor
   *  @brief Setup microcontroller to operate the motor
   */
void setupMotor();

/** @name disableMotor
   *  @brief Disables motor immediately
   */
void disableMotor();

/** @name buzz
   *  @brief Use this for a buzzes for user awareness. Motor needs to be disabled to work.
   *  @param  periodMicros Period of buzz tone in microseconds
   *  @param  durationMillis Duration of buzz overall in milliseconds
   */
void buzz(int periodMicros, int durationMillis);

void AHBL();      // Set A high, B low, C floating
void AHCL();      // Set A high, C low, B floating
void BHCL();      // Set B high, C low, A floating
void BHAL();      // Set B high, A low, C floating
void CHAL();      // Set C high, A low, B floating
void CHBL();      // Set C high, B low, A floating
void allFloat();  // Set all outputs to float

// Comparator configuration functions 

void aRisingBEMF();   // Set AC to interrupt on A rising edge 
void aFallingBEMF();  // Set AC to interrupt on A falling edge 
void bRisingBEMF();   // Set AC to interrupt on B rising edge 
void bFallingBEMF();  // Set AC to interrupt on B falling edge 
void cRisingBEMF();   // Set AC to interrupt on C rising edge 
void cFallingBEMF();  // Set AC to interrupt on C falling edge 

#endif
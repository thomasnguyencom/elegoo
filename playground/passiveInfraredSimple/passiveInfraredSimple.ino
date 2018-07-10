// ------------------------------------------------------------------------------------------------------------------------
// HC-SR501 - Passive IR Sensor
// http://henrysbench.capnfatz.com/henrys-bench/arduino-sensors-and-input/arduino-hc-sr501-motion-sensor-tutorial/
// ------------------------------------------------------------------------------------------------------------------------
// VCC Power (5V)
// OUT inputPin
// GND Ground
// ------------------------------------------------------------------------------------------------------------------------
// When the dials are facing you
// Left: sensitivity
// Right: time delay

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
int ledPin = 8;                // choose the pin for the LED

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================
// ------------------------------------------------------------------------------------------------------------------------
// INIT : SR501 Sensor
// ------------------------------------------------------------------------------------------------------------------------
int pirPin = 7;                // choose the pin for the PIR
// ------------------------------------------------------------------------------------------------------------------------

// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(pirPin, INPUT);     // declare sensor as input

  digitalWrite(ledPin, LOW);
}

// ------------------------------------------------------------------------------------------------------------------------
// loop
// ------------------------------------------------------------------------------------------------------------------------
void loop(){
  boolean pirValue = digitalRead(pirPin);
  digitalWrite(ledPin, pirValue);
}

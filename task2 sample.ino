const int SIGNAL_PIN = 2; // the pin connected to the signal
const int MEASURE_INTERVAL = 20; // in milliseconds
const int SAMPLES = 10; // the number of signal edges to count
const float MIN_FREQUENCY = 333; // in Hz
const float MAX_FREQUENCY = 1000; // in Hz
const float ACCEPTABLE_ERROR = 0.025; // 2.5% error
const int PERIOD = 20000; // in microseconds
const int RATE = 50; // in Hz

volatile unsigned long risingEdgeTime = 0;
volatile unsigned long fallingEdgeTime = 0;
volatile bool risingEdgeDetected = false;
volatile bool fallingEdgeDetected = false;

void setup() {
  pinMode(SIGNAL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SIGNAL_PIN), onSignalChange, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // Wait for the next measurement interval
  delay(PERIOD);

  // Reset the edge detection variables
  risingEdgeDetected = false;
  fallingEdgeDetected = false;

  // Count the number of signal edges in the sample window
  int edgeCount = 0;
  while (edgeCount < SAMPLES) {
    if (risingEdgeDetected && fallingEdgeDetected) {
      // Calculate the frequency of the signal
      float period = (fallingEdgeTime - risingEdgeTime) * 1e-6; // in seconds
      float frequency = 1.0 / period; // in Hz

      // Check if the frequency is within the acceptable range
      if (frequency >= MIN_FREQUENCY && frequency <= MAX_FREQUENCY) {
        // Print the frequency and exit the loop
        Serial.print("Frequency: ");
        Serial.print(frequency);
        Serial.println(" Hz");
        break;
      }

      // Reset the edge detection variables
      risingEdgeDetected = false;
      fallingEdgeDetected = false;
    }
  }
}

void onSignalChange() {
  if (digitalRead(SIGNAL_PIN) == HIGH) {
    risingEdgeTime = micros();
    risingEdgeDetected = true;
  } else {
    fallingEdgeTime = micros();
    fallingEdgeDetected = true;
  }
}

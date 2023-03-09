const int ANALOG_PIN = A0; // the analog input pin
const int LED_PIN = 13; // the LED pin
const float MAX_VOLTAGE = 3.3; // in volts
const float MAX_ANALOG_VALUE = 1023.0; // the maximum value returned by analogRead()
const float FILTER_FACTOR = 0.25; // the weight of the current reading in the moving average
const float ERROR_THRESHOLD = MAX_VOLTAGE / 2; // in volts
const int PERIOD = 20; // in milliseconds
const int RATE = 50; // in Hz

float filteredAnalogValue = 0;
bool error = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Read the analog input and convert the value to voltage
  float analogValue = analogRead(ANALOG_PIN);
  float voltage = analogValue * MAX_VOLTAGE / MAX_ANALOG_VALUE;

  // Compute the filtered analog value using a moving average
  filteredAnalogValue = filteredAnalogValue * (1 - FILTER_FACTOR) + voltage * FILTER_FACTOR;

  // Check if the average analog value is greater than the error threshold
  error = (filteredAnalogValue > ERROR_THRESHOLD);

  // Visualize the error using a LED
  digitalWrite(LED_PIN, error);

  // Print the analog values to the serial monitor
  Serial.print("Analog value: ");
  Serial.print(analogValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 2);
  Serial.print("\tFiltered voltage: ");
  Serial.print(filteredAnalogValue, 2);
  Serial.print("\tError: ");
  Serial.println(error);

  // Wait for the next measurement interval
  delay(PERIOD);
}

const int HIGH_DURATION = 200; // in microseconds
const int LOW_DURATION = 50; // in microseconds
const int EXTRA_LOW_DURATION = 30; // in microseconds
const int PERIOD = 4000; // in microseconds
const int PIN = 13; // the pin to output the signal

void setup() {
  pinMode(PIN, OUTPUT);
}

void loop() {
  digitalWrite(PIN, HIGH);
  delayMicroseconds(HIGH_DURATION);

  digitalWrite(PIN, LOW);
  delayMicroseconds(LOW_DURATION);

  digitalWrite(PIN, HIGH);
  delayMicroseconds(HIGH_DURATION);

  digitalWrite(PIN, LOW);
  delayMicroseconds(LOW_DURATION);

  digitalWrite(PIN, LOW);
  delayMicroseconds(EXTRA_LOW_DURATION);

  digitalWrite(PIN, HIGH);
  delayMicroseconds(HIGH_DURATION);

  digitalWrite(PIN, HIGH);
  delayMicroseconds(EXTRA_LOW_DURATION);

  digitalWrite(PIN, LOW);
  delayMicroseconds(LOW_DURATION);

  digitalWrite(PIN, HIGH);
  delayMicroseconds(HIGH_DURATION);

  delayMicroseconds(PERIOD - (6 * HIGH_DURATION) - (3 * LOW_DURATION) - EXTRA_LOW_DURATION);
}

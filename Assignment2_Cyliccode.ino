//Cyclic Executive Assignment-2

#include <B31DGMonitor.h>

#include<Ticker.h>

B31DGCyclicExecutiveMonitor
monitor;
int time1_out = 1;
int p1_in = 8;
float p1;
int p1_1;
float p1_read;
unsigned long time1;
unsigned long time2;
int p2_in = 9;
float p2;
int p2_1;
float p2_read;
unsigned long time3;
unsigned long time4;
int potPin = 4;
int ERROR_LED = 19;
float potval;
float cal_val =0;
float s1 = 0;
float s2 = 0;
float s3 = 0;
float s4 = 0;
float ana_avg;
float half_max;
unsigned long frameTime = 0;
unsigned long frameCounter = 0;
Ticker ticker;
void setup() {
  // Insert your setup code here for a single run:
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Start");
  pinMode(time1_out, OUTPUT);
  pinMode(p1_in, INPUT);
  pinMode(p2_in, INPUT);
  pinMode(potPin, INPUT);
  pinMode(ERROR_LED, OUTPUT);
  monitor.startMonitoring();
  frame();
  ticker.attach_ms(4, frame);
}
void loop() {
  // Put your core code here for repeated execution:
  //frame();

}
void frame()
{
  unsigned int slot = frameCounter % 50;
  switch (slot)
  {
    case 0:  operation1();            operation3();              break;
    case 1:  operation1();  operation2();                        break;
    case 2:  operation1();            operation3();              break;
    case 3:  operation1();                      operation4();    break;
    case 4:  operation1();            operation3();              break;
    case 5:  operation1();  operation2();                        break;
    case 6:  operation1();            operation3();              break;
    case 7:  operation1();                                  break;
    case 8:  operation1();            operation3();              break;
    case 9:  operation1();                      operation4();    break;
    case 10: operation1();            operation3();              break;
    case 11: operation1();  operation2();                        break;
    case 12: operation1();            operation3();              break;
    case 13: operation1();                      operation4();    break;
    case 14: operation1();            operation3();              break;
    case 15: operation1();  operation2();                        break;
    case 16: operation1();            operation3();              break;
    case 17: operation1();                                  break;
    case 18: operation1();            operation3();              break;
    case 19: operation1();                      operation4();    break;
    case 20: operation1();            operation3();              break;
    case 21: operation1();  operation2();                        break;
    case 22: operation1();            operation3();              break;
    case 23: operation1();                      operation4();  operation5();    break;
    case 24: operation1();            operation3();              break;
    case 25: operation1();  operation2();                        break;
    case 26: operation1();            operation3();              break;
    case 27: operation1();                                  break;
    case 28: operation1();            operation3();              break;
    case 29: operation1();                      operation4();    break;
    case 30: operation1();            operation3();              break;
    case 31: operation1();  operation2();                        break;
    case 32: operation1();            operation3();              break;
    case 33: operation1();                      operation4();    break;
    case 34: operation1();            operation3();              break;
    case 35: operation1();  operation2();                        break;
    case 36: operation1();            operation3();              break;
    case 37: operation1();                                  break;
    case 38: operation1();            operation3();              break;
    case 39: operation1();                      operation4();    break;
    case 40: operation1();            operation3();              break;
    case 41: operation1();  operation2();                        break;
    case 42: operation1();            operation3();              break;
    case 43: operation1();                      operation4();    break;
    case 44: operation1();            operation3();              break;
    case 45: operation1();  operation2();                        break;
    case 46: operation1();            operation3();              break;
    case 47: operation1();                                  break;
    case 48: operation1();            operation3();              break;
    case 49: operation1();                      operation4();  operation5();   ;  break;
  }
  frameCounter++;
}

//The pattern should be HIGH for 200 s, LOW for 50 s, then HIGH s, LOW for 50 s, then HIGH s, then HIGH again for 30 s
//LOW for 50 s, then HIGH s, and repeat once every 4 ms.
void operation1()
{
  monitor.jobStarted(1);
  digitalWrite(time1_out, HIGH);
  delayMicroseconds(200);
  digitalWrite(time1_out, LOW);
  delayMicroseconds(50);
  digitalWrite(time1_out, HIGH);
  delayMicroseconds(30);  
  digitalWrite(time1_out, LOW);
  monitor.jobEnded(1);
}
//At every 20 ms, measure the frequency of a 3.3 v square wave signal. 
//The signal will be a normal square wave with a duty cycle of 50%, and the frequency will be in the range of 333Hz to 1000Hz. 2.5% accuracy is acceptable.
void operation2()
{
  monitor.jobStarted(2);
  while (digitalRead(p1_in) == LOW);
  time1 = micros();
  while (digitalRead(p1_in) == HIGH);
  time2 = micros();
  p1_read = (time2 - time1)*0.000001;
  p1 = 1/(p1_read*2);
  monitor.jobEnded(2);
}
//Once every 8 ms, take a second 3.3v square wave signal's frequency into consideration.
//The signal will be a regular square wave with a frequency in the 500Hz to 1000Hz range and a 50% duty cycle. 2.5% accuracy is acceptable.
void operation3()
{
  monitor.jobStarted(3);
  while (digitalRead(p2_in) == LOW);
  time3 = micros();
  while (digitalRead(p2_in) == HIGH);
  time4 = micros();
  p2_read = (time4 - time3)*0.000001;
  p2 = 1/(p2_read*2);
  monitor.jobEnded(3);
}
//By averaging the latest 4 measurements of a single analogue input, a filtered analogue value is calculated. [Period: 20 ms; Rate: 50 Hz]
//With a potentiometer, the analogue input must be linked to a voltage of no more than 3.3 volts. When the average analogue value is greater than half of the maximum range, 
//the job should additionally display an error (using an LED).

void operation4()
{
  monitor.jobStarted(4);
  potval = analogRead(potPin);
  cal_val = (3.3*potval)/4095;
  s1 = s2;
  s2 = s3;
  s3 = s4;
  s4 = cal_val;
  ana_avg = (s1 + s2 + s3 + s4)/4;
  half_max = 3.3/2;
  if (ana_avg > half_max)  {digitalWrite(ERROR_LED, HIGH);}
  else {digitalWrite(ERROR_LED, LOW);}
  monitor.jobEnded(4);
}

//Record the following data to the serial port at a baud rate of 9600 bits per second, once every 100 milliseconds 
//[Period = 100ms / Rate = 10Hz] in comma delimited format, i.e. "%d,%d".
//Value of frequency determined by operation 2 (Hz, as integer)
//Value of frequency determined by operation 3 (Hz, as integer)

void operation5()
{
  monitor.jobStarted(5);
  p1_1 = 0;
  p2_1 = 0;
  p1_1 = ((p1 - 333)*99)/(1000 - 333);
  p2_1 = ((p2 - 500)*99)/(1000 - 500);
  if(p1_1<=0){p1_1 = 0;}
  else if(p1_1 > 99){p1_1 = 99;}
  else{p1_1 = p1_1;}
  if(p2_1<=0){p2_1 = 0;}
  else if(p2_1 > 99){p2_1 = 99;}
  else{p2_1 = p2_1;}
  Serial.printf("%d, %d\n",p1_1, p2_1);
  monitor.jobEnded(5);
}
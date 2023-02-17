int mySwitchOne = 5; // the declaring pin 5 as switch 1
int mySwitchTwo = 6; // the declaring pin 6 as switch 2

int waveFormOne = 1;// the declaring pin 1 as signal A or LED 1
int waveFormTwo = 3;// the declaring pin 3 as signal B or LED 2

int mySwitchOneValue = 0;// the declaring variable to read from a switch 1 initially set as LOW
int mySwitchTwoValue = 0;// the declaring  variable to read from a switch 2 initially set as LOW

int parameterOne = 800;// the parameter 'parameterOne' calculated as first letter(s)*100 = 8*100 = 800 // THE LETTER ARE SANJAY: S-8,A-1,N-13,J-10,A-1,Y-2
int parameterTwo = 1000;// the parameter used in mode '2' where we reverse the signal, hence highest value is parameterOne+(c-1)*parameterThree = 1000
int parameterThree = 100;// the parameter 'parameterThree' calculated as second letter(a)*100 = 1*100 = 100
int parameterFour = 17; // the parameter 'parameterFour' calculated as third letter(n)+4 = 13+4=17
int parameterFive = 3500;//the parameter 'parameterFive' calculated as fourth letter(j)*500 = 10*500 = 3500

void setup() {
  pinMode(mySwitchOne, INPUT); // the setting mySwitchOne pin(switch 1) as INPUT
  pinMode(mySwitchTwo, INPUT); // the setting mySwitchTwo pin(switch 2) as INPUT
  pinMode(waveFormOne, OUTPUT);// the setting waveFormOne pin(LED 1/signal A) as OUTPUT
  pinMode(waveFormTwo, OUTPUT);// the setting waveFormTwo pin(LED 2/signal B) as OUTPUT

}

void loop() {
  mySwitchOneValue = digitalRead(mySwitchOne); // the  reading from mySwitchOne and storing it in mySwitchOneValue
  mySwitchTwoValue = digitalRead(mySwitchTwo); // the reading from mySwitchTwo and storing it in mySwitchTwoValue
  
  if(mySwitchOneValue == HIGH)         // by using if else to 
  {
    digitalWrite(waveFormOne, LOW);
    digitalWrite(waveFormTwo, LOW);

  }

  else{

    if(mySwitchTwoValue == LOW)
    {
      digitalWrite(waveFormTwo, HIGH);
      delay(50);
      digitalWrite(waveFormTwo, LOW);

      for(int i =0;i<parameterFour;i++)
      {
        digitalWrite(waveFormOne, HIGH);
        delay(parameterOne);
        digitalWrite(waveFormOne, LOW);
        delay(parameterThree);
        parameterOne = parameterOne+50;
      }
      digitalWrite(waveFormOne, LOW);
      delay(parameterFive);
    }

    else
    {
      digitalWrite(waveFormTwo, HIGH);
      delay(50);
      digitalWrite(waveFormTwo, LOW);

      for(int i =0; i<parameterFour;i++)
      {

        digitalWrite(waveFormOne, HIGH);
        delay(parameterTwo);
        digitalWrite(waveFormOne, LOW);
        delay(parameterThree);
        
        parameterTwo = parameterTwo-50;
      }

      digitalWrite(waveFormOne, LOW);  
      delay(parameterFive);


    }

  }

}
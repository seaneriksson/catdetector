/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see http://learn.adafruit.com/photocells */
 
bool lightActivated = 0; 
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int photoReferenceValue = 0;  // set initial light value
bool referenceSet = false;
bool nightMode = false; 
bool modeSwitch = false;




void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop(void) {

  photocellReading = analogRead(photocellPin);   //detect light in environment
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading


  if (referenceSet == false)  //set the initial reference and daytime or night mode
  {
    photoReferenceValue = photocellReading;
    referenceSet = true;

    if (photocellReading >= 400)
    {
      Serial.print("Day time mode ");
      nightMode = false;
    }
  
    if (photocellReading <= 399)
    {
      Serial.print("Night time mode ");
      nightMode = true;
    }
  } 

  //check for large change in light conditions if so change day/night mode
  if (abs(photocellReading - photoReferenceValue) >= 300)
  {
    photoReferenceValue = photocellReading;

    if (photocellReading >= 400)
    {
      Serial.print("Day time mode ");
      nightMode = false;
    }
  
    if (photocellReading <= 399)
    {
      Serial.print("Night time mode ");
      nightMode = true;
    }
  }
 
  if (nightMode == true)
  {
    //detect if cat has entered garage
    if (abs(photocellReading - photoReferenceValue) >= 40 && lightActivated == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      lightActivated = 1;  //cat has entered garage
      Serial.print("Cat Motion Detected ");
      delay(3000);
      photocellReading = 9999;
    }

    //detect if cat is leaving garage
    if (abs(photocellReading - photoReferenceValue) >= 40 && lightActivated == 1 && photocellReading != 9999)
    {
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
      lightActivated = 0;  //cat has left garage
      Serial.print("Cat Motion Detected ");
      delay(3000);
    }
  }

  if (nightMode == false)
  {
    //detect if cat has entered garage
    if (abs(photocellReading - photoReferenceValue) >= 50 && lightActivated == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
      lightActivated = 1;  //cat has entered garage
      Serial.print("Cat Motion Detected ");
      delay(3000);
      photocellReading = 9999;
    }

    //detect if cat is leaving garage
    if (abs(photocellReading - photoReferenceValue) >= 50 && lightActivated == 1 && photocellReading != 9999)
    {
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
      lightActivated = 0;  //cat has left garage
      Serial.print("Cat Motion Detected ");
      delay(3000);
    }
  }
 
  delay(100);
}
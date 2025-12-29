#define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD
#define INCLUDE_SMS_SHIELD

/* Include 1Sheeld library.*/
#include <OneSheeld.h>
#include <string.h>

#define trigPinL 4 // ground level sensor
#define echoPinL 5 // ground level sensor
#define trigPinH 6 // body level 
#define echoPinH 7 // body level
#define buzzer 3 // buzzer
#define SW 8 // touch sensor

// Define global variables
float lat;
float lon;
String PhoneNumber = "9736705208";
String Message;
String Message1;
String Message2;

void setup()
{
  // Assign pins roles
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinH, OUTPUT);
  pinMode(echoPinH, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(SW, INPUT);
  // Start communication
  OneSheeld.begin();
}

void loop()
{
  // Get latitude and longitude and convert them to strings
  lat = GPS.getLatitude();
  lon = GPS.getLongitude();
  Message1 = String(lat,8);
  Message2 = String(lon,8);

  // If touch sensor receives input send SMS messages
  if (digitalRead(SW) == 1){
    Message = "I need your Help! I'm at latitude: " + Message1 + " and longitude: " + Message2;
    SMS.send(PhoneNumber, Message);
    Message = "Google Maps - https://www.google.com/maps/place/" + Message1 + "," + Message2;
    SMS.send(PhoneNumber,Message);
    delay(2000);
  }

  // Calculate ground distance
  long durationL, distanceL, durationH, distanceH, MixDist;
  digitalWrite(trigPinL, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);

  
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = (durationL/2) / 29.1; // Convert to cm
  
  // Calculate body distance
  digitalWrite(trigPinH, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPinH, HIGH);
 
 
  delayMicroseconds(10);
  digitalWrite(trigPinH, LOW);

  durationH = pulseIn(echoPinH, HIGH);
  distanceH = (durationH/2) / 29.1; //Convert to cm

  // Play buzzer for half a second if ground distance is greater than 50cm
  if (distanceL > 50){
    tone(buzzer, 261.625, 500);
    delay(1000);
  }
  else{
    noTone(buzzer);
  }

  // Play buzzer for a second if body distance is less than 70cm
  if (distanceH < 70){
    tone(buzzer, 2093, 1000);
    delay(1500);
  }
  else{
    noTone(buzzer);
  }
}

# AlertCane
Arduino + 1Sheeld powered cane for the visually impaired with obstacle detection and emergency SMS + GPS support.

## How it works

- Two ultrasonic sensors measure distance. One points at the ground and one at body height.
- The buzzer sounds a low tone when the ground is more than 50 cm away, such as at a step or a curb, and a high tone when something is closer than 70 cm at body height.
- Pressing the touch sensor texts the wearer's GPS position, with a Google Maps link, to one emergency contact. The 1Sheeld board supplies GPS and SMS through a paired phone.

## Run it

Set `PhoneNumber` in `cane.c` to the emergency contact's number. Upload the sketch with the Arduino IDE and the OneSheeld library installed. Pin assignments are at the top of the file.

Built in 2018 as an undergraduate project. Bug fixes in 2025.

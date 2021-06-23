# [TinkerCad Project Link:](https://www.tinkercad.com/things/j4pGuvq0QKi-home-automation-original-/editel?sharecode=0O0ztq9Jh3AUHyNvl75hlrVt44fWDGzvYwUtgVvaiPI)

Home automation system using Arduino Uno R3 with LCD Display.
# Working
The status of all appliances will be reflected in the LCD.

Fan control:
- If temperature is greater than 30 degree celcius, fan(DC Motor) is switched on automatically. Use temperature sensor to control the same.
- The PIR sensor detects motion in the room and switches the fan on when moment is detected in the room.
- Fan is also provided with a switch of manual control.

Light Control:
- Use photoresistor to control the light in the room. If it is dark, the bulbs will switch on and vice versa.
- The PIR sensor detects motion in the room and switches the bulb on when moment is detected in the room.

Door Control:
- Ulrasonic Distance sensor is used to open and shut the door if the owner is within 100cms from the door.

Gas Leak:
- The buzzer is set off if gas level in the house exceeds 600. The Gas sensor detects the level of gas in the house.

![alt text](https://github.com/RishithaRamesh/home-automation-simulation/blob/main/circuit.png?raw=true)

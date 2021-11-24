This section is all about learning the simple built in arduino function. 
Functions to learn:
*	setup	:: initialization method
*	loop	:: main method, constantly looping
*	pinMode :: sets the pin mode (input/output) of a given pin
*	digitalRead	:: reads a digital pin (2,13) (HIGH/LOW)
*	digitalWrite	:: write to a digital pin (HIGH/LOW)
*	analogRead	:: reads analog pin (A0,A5) (0-1023) (0,5v)
*	attachInterrupt :: attaches an interrupt to a capable pin
*	delay	:: delays processor for x milliseconds 

Data types to learn:
*	int	:: Integer 
*	boolean/bool	:: (0,1 || false,true)

Qualifiers to learn:
*	const	:: tells the compiler to not allow for the value to change
*	volatile	:: tells the compiler that the value can change at anytime

Projects:
1.	Blinking Light with Button :: using digitalRead, change the pase of the LED flashing base on whether or not the button is pressed
2.	Blinking Light with Potentiometer :: using analogRead, change the pase of the LED based on the potentiometer
3.	Blinking Light with Interrupt	:: using an interrupt, toggle the LED when the button is pressed
F.	Line OF LEDs Arcade Game

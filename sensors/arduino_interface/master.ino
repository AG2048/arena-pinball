/*
Copy older code or rewrite it

send() and receive() for the master

Master handling user input and i2c

Master will be doing polling


2 arduinos:
- master blinks 5 times, and let slave blink 5 times
- After slave blinks 7 times, and let the master blink back that many time

Error code system
- e.g. if anything transmits all 1s, then its error
- Master: send me your location
- Master: what is your location
- Slave: ???
- Slave: respond the error code
*/

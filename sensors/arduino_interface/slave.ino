/*
send() and receive() for the slave

send():
	on request

receive():
	on transmission
	or on receive

Global variable: RECEIVED_INFORMATION: false

A universal recieve function for all the slaves
- the recieve is going to be the same for every slave anyways

For each individual slave we write a parsing function

set 2 global variables before setup()
RECEIVED_INFORMATION = false;
INFORMATION = 

if INFORMATION true:
	process information()

for user input:
	atmega
*/

// Global flags
int RECEIVED_INFORMATION = false;

void processInformation() {
}

void onReceive() {
	processInformation()
	// Master: hey I would like this info back
	// *50ms*
	// Master: hey what is the information I wanted
	// So process info ASAP
	RECEIVED_INFORMATION = true;
}

void setup() {
}

void loop() {
	if (RECEIVED_INFORMATION) {
		// Act according to the information
	}
	// Check if information is true,
	// if it is true, set it to false, process the information
	// Process information
}

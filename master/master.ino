/*
 * master.ino
 *
 * Created: 5/29/2014 3:59:20 PM
 * Author: annim
 */ 

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define BAUD_RATE 9600

#define CE 8
#define CSN 9
#define T0 4

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(CE, CSN);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };



void setup(void)
{
	//enable booster
	pinMode(T0, OUTPUT);
	digitalWrite(T0, HIGH);
	//////////////////////////////////////////////////////////////////////////
	
	Serial.begin(BAUD_RATE);
	//
	// Setup and configure RF radio
	//
	Serial.println("initiating radio...");
	radio.begin();

	// optionally, increase the delay between retries & # of retries
	radio.setRetries(15,15);
	 
	radio.openReadingPipe(1,pipes[1]);
	radio.startListening();
	Serial.println("now listening to clients...");
	delay(1000);
}

void loop()
{
	 if ( radio.available() )
	 {
		 unsigned long got_response;
		 radio.read( &got_response, sizeof(unsigned long) );
		 Serial.println("Got request from one client...");

		 // Spew it
		 Serial.print("Response received...");
		 Serial.print(got_response);		 
		 Serial.println();
	 }
	 else{
		 Serial.println("waiting so any client may request to connect...");
	 }
	 delay(1000);
}

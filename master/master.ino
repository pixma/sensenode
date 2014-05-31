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
#define MAXIMUM_LEN 512
#define FIELDS 2
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
int got_response[FIELDS] ;


void setup(void)
{
	//enable booster
	pinMode(T0, OUTPUT);
	digitalWrite(T0, HIGH);
	//////////////////////////////////////////////////////////////////////////
	
	Serial.begin(BAUD_RATE);
        Serial.println("master started.");
	//
	// Setup and configure RF radio
	//
	radio.begin();

	// optionally, increase the delay between retries & # of retries
	radio.setRetries(15,15);
	 
	radio.openReadingPipe(1,pipes[1]);
	radio.startListening();
	delay(1000);
}

void loop()
{
	 if ( radio.available() )
	 {
		 radio.read( got_response, sizeof(got_response) );
		 Serial.print(got_response[0]);		 
		 Serial.print(",");		 
		 Serial.print(got_response[1]);		 
		 Serial.println();
	 }
	 else{
		 Serial.println("waiting so any client may request to connect...");
	 }
	 delay(1000);
}

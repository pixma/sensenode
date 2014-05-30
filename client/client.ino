/*
* client.ino
*
* Created: 5/29/2014 4:47:42 PM
* Author: annim
*/

/*
Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.
*/

/**
* Example for Getting Started with nRF24L01+ radios.
*
* This is an example of how to use the RF24 class.  Write this sketch to two
* different nodes.  Put one of the nodes into 'transmit' mode by connecting
* with the serial monitor and sending a 'T'.  The ping node sends the current
* time to the pong node, which responds by sending the value back.  The ping
* node can then see how long the whole cycle took.
*/
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"



#define BAUD_RATE 9600
#define MAXLEN 1024

#define CE 8
#define CSN 9
#define BOOSTER 4

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(8,9);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[1] = {0xF0F0F0F0D2LL };
int nSendData = 0;
	


void setup()
{
        pinMode(BOOSTER, OUTPUT);
        digitalWrite(BOOSTER, HIGH);
	Serial.begin(BAUD_RATE);
	//
	// Setup and configure rf radio
	//

	radio.begin();

	// optionally, increase the delay between retries & # of retries
	radio.setRetries(15,15);
	radio.openWritingPipe(pipes[0]);
	
	Serial.println("now sending data...");

}

void loop()
{
	nSendData = 35;
	bool ok = radio.write( &nSendData, sizeof(int) );
	if (ok)
		Serial.println("data send, ok...");
	else
		Serial.println("data sending process failed!");
	
}

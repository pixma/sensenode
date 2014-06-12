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
    randomSeed(MAXIMUM_LEN);
	radio.setAutoAck(pipes[0], false);
	

}

void loop()
{
	nSendData = (int)random(35, 38);
        csendData[0] = nSendData;
        csendData[1] = CLIENT_ID;
        radio.write(csendData, sizeof(csendData));
		
        delay(1000);
}

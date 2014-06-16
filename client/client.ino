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


#include <stdio.h>
#include <string.h>
#include <SPI.h>
#include <stdlib.h>
#include "nRF24L01.h"
#include "RF24.h"

#define CE 8
#define CSN 9
#define BOOSTER 4
#define CLIENT_ID 3
#define TYP_SIZE 10

#define BAUD_RATE 9600

#define WITH_SERIAL

#include "MasterNode.h"
MasterNode node;
int nSendData = 0;
int csendData[2] = {0};

//int buf[TYP_SIZE] = {0};
int *buf;

void setup()
{
	node.beginDevice(1);
}

void loop()
{
	nSendData = (int)random(35, 38);
	csendData[0] = nSendData;
	csendData[1] = CLIENT_ID;
	
	if (node.http_request(csendData, sizeof(csendData)))
	{
		//send success
		#ifdef WITH_SERIAL
		Serial.println("Data send successfully");
		#endif
	}
	else{
		//send failed.
	}
	
	buf = node.listen(10000, TYP_SIZE);// a blocking call till timeout.
	//listen if some instruction comes from server via master node of the network.
	
	if (buf[0] == 0)
	{
		//nothing received hence continue;
		#ifdef WITH_SERIAL
		Serial.println("nothing received hence continue;");
		#endif
	}
	else{
		//something received.
		// behave accordingly as per instruction.
		#ifdef WITH_SERIAL
		Serial.println("received something...");
		#endif
	}
	
	
	
	delay(1000);
}

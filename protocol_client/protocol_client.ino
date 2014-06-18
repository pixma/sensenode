/*
 * protocol_client.ino
 *
 * Created: 6/18/2014 12:43:38 PM
 * Author: annim
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
	

void setup()
{
	node.beginDevice(CLIENT_ID);
}

void loop()
{

}

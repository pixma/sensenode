/*
 * MasterNode.h
 *
 * Created: 6/12/2014 3:25:49 PM
 *  Author: annim
 */ 


#ifndef MASTERNODE_H_
#define MASTERNODE_H_


#include <stdio.h>
#include <string.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"



#define BAUD_RATE 9600
#define MAXLEN 1024

#define CLIENT_ID 3
#define MAXIMUM_LEN 512
#define FIELDS 2

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

const uint64_t pipes[1] = {0xF0F0F0F0D2LL };
int nSendData = 0;
int csendData[FIELDS] ;


/************************************************************************/
/*                                      class  MasterNode

/************************************************************************/
class MasterNode{
	private:
	
	
	public:
	/************************************************************************/
	/* void beginDevice(int type);
	begin the device and performs all necessary steps for setting up this device.
	Type:
	1 - Client
	2 - Master
	This API will create a start network topology. Many to One.
	/************************************************************************/
	};


#endif /* MASTERNODE_H_ */
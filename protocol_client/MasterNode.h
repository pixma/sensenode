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
#include <stdlib.h>
#include "nRF24L01.h"
#include "RF24.h"


#define CE 8
#define CSN 9
#define T0 4
#define SEEK_SERVER_TIME 5000
#define BOOSTER 4

#define SLAVE_ID_1 3



#define MAXLEN 1024


#define MAXIMUM_LEN 512
#define FIELDS 2



//
// Topology

const uint64_t pipes[1] = {0xF0F0F0F0D2LL };


/************************************************************************/
/*                                      class  MasterNode

/************************************************************************/
class MasterNode{
	private:
	
	/************************************************************************/
	/* int mode: keeps what mode this device is running on
	                                                                     */
	/************************************************************************/
	int mode;
	int device_id;
	
	
	public:
	/************************************************************************/
	/* void beginDevice(int id);
	begin the device and performs all necessary steps for setting up this device.
	id- associate some number to this device, keep the id unique in the network.
	This API will create a start network topology. Many to One.
	/************************************************************************/
	void beginDevice(int);
	
	/************************************************************************/
	/*
	int http_request( int *param , int nsize);
	returns true if successfully send the request. 
	returns false if fails.
	- pass an array of int type data                                                                     
	- pass the size of the array
	Shall be commonly used by client ot send data to Internet via master node of the network.
	*/
	int http_request( int *param , int nsize);
	
	/************************************************************************/
	
	/************************************************************************/
	/* void enableAck(bool enable);
	true: enables the ack packet generation.
	false:disables auto-ack packets.                                                                     */
	/************************************************************************/
	void enableAck(bool enable);	
	
	/************************************************************************/
	/* int [] listen(int timeout, int nsize);
	start listening to other with timeout mentioned in ms
	nsize: number of size to read.
	Once the timeout meets, it will fall back to writing mode.
	                                                                     */
	/************************************************************************/
	
	int * listen(int timeout, int nsize);	
	
	/************************************************************************/
	/* bool writeToClient(int clientId, int data[], int nsize);
	clientid- to which client you want to write data .
	data- an array of data.
	nsize- size of data you want to write.
	                                                                     */
	/************************************************************************/
	bool writeToClient(int clientId, int data[], int nsize);
	};


#endif /* MASTERNODE_H_ */
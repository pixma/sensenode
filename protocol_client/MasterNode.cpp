/*
* MasterNode.cpp
*
* Created: 6/13/2014 11:02:21 AM
*  Author: annim
*/
#include "MasterNode.h"

RF24 radio(CE,CSN);

void MasterNode::beginDevice( int id)
{
	pinMode(BOOSTER, OUTPUT);
	digitalWrite(BOOSTER, HIGH);
	
	#ifdef WITH_SERIAL
	Serial.begin(BAUD_RATE);
	#endif
	
	device_id = id;
	
	radio.begin();
	// optionally, increase the delay between retries & # of retries
	radio.setRetries(15,15);
}

int MasterNode::http_request( int *param , int nsize)
{
	/************************************************************************/
	/* RTS = -13
	   RTR =  13
	   Device id will be echoed back to the sender
	   ACK format: 13 0                                                                  */
	/************************************************************************/

	
	int rts[2];
	int rtr[2];
	int ack[2];
	bool complete = false;
	
	rts[0] = -13;//rts flag set. -13 will be an indication that this data packet is an RTS data packet.
	rts[1] = id;// sets the id of this device.
	while (!complete)
	{
		radio.openWritingPipe(pipes[0]);// open pipe for writing .
		
		while (!radio.write(rts, sizeof(rts)));// on successful sending of rts, it will come out of the loop.
		
		//open the same pipe for listening now.
		radio.openReadingPipe(1, pipes[0]);// open pipe for reading.
		while (!radio.available());	// till something is available, the point of execution statys here.
		radio.read(rtr, sizeof(rtr));
		
		if (rtr[0] == 13 && rtr[1] == id )
		{
			// now send data as connection is established between this client and master.
			radio.openWritingPipe(pipes[0]);// open pipe for writing .
			while (!radio.write(param, sizeof(nsize)));
			radio.openReadingPipe(1, pipes[0]);// open pipe for reading.
			while (!radio.available());
			radio.read(rtr, sizeof(rtr));
			if(ack[0] == 13 && ack[1]== 0){
				complete = true;
			}
			else{
				complete = false;
			}
		}
	}
	
	return 1;	
}

void MasterNode::enableAck(bool enable){
	radio.setAutoAck(enable);
}

int * MasterNode::listen(int timeout, int nsize){
	
	//will enable device to listen the device.
	int *got_response;
	got_response = (int *)malloc(nsize*sizeof(int));// this creates 1 d array.
	int start = millis();
	
	
	while ((millis()-start) < timeout)
	{
		if (radio.available())
		{
			radio.openReadingPipe(1,pipes[0]);//open pipe for listening.
			radio.read(got_response, nsize);
			
			#ifdef WITH_SERIAL
				Serial.print("Size of the buffer:");
				Serial.println(nsize);
				for(int i=0;i < sizeof(got_response); i++){
					Serial.println(got_response[i]);
				}
			#endif
			break;
		}
		else if( mode == 2){
			#ifdef WITH_SERIAL
				 Serial.println("waiting so any client may request to connect...");
			#endif
			//else waiting to get some data from any of the slave/client node.
		}
	}
	if (mode == 1)
	{
		radio.openWritingPipe(pipes[0]);//open pipe for writing back again.
	}
	
	return got_response;
}

bool MasterNode::writeToClient(int clientId, int data[], int nsize){
	
	radio.openWritingPipe(pipes[0]);// open pipe for writing .
	
	radio.write((const void *)clientId, sizeof(int));
	
	if (radio.write(data,nsize)  == true)
	{
		//success
		radio.openReadingPipe(1,pipes[0]);// open pipe for listening now...
		return true;
	}
	else{
		//failed
		radio.openReadingPipe(1,pipes[0]);// open pipe for listening now...
		return false;
	}
	
	radio.openReadingPipe(1,pipes[0]);// open pipe for listening now...
	return false;
	
}


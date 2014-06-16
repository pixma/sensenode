/*
* MasterNode.cpp
*
* Created: 6/13/2014 11:02:21 AM
*  Author: annim
*/
#include "MasterNode.h"

RF24 radio(CE,CSN);

void MasterNode::beginDevice( int type)
{
	pinMode(BOOSTER, OUTPUT);
	digitalWrite(BOOSTER, HIGH);
	
	#ifdef WITH_SERIAL
	Serial.begin(BAUD_RATE);
	#endif
	
	radio.begin();
	// optionally, increase the delay between retries & # of retries
	radio.setRetries(15,15);
	
	
	switch( type ){
		case 1:
		//client side code goes here
		radio.openWritingPipe(pipes[0]);// open pipe for writing .
		mode = 1;//client
		break;
		case 2:
		//master side code goes here.
		radio.openReadingPipe(1, pipes[0]);//open pipe for listening.
		mode = 2;
		//master mode
		break;
	}
}

int MasterNode::http_request( int param[] , int nsize)
{
	if(radio.write(param, nsize) == true){
		return 1;
	}
	else{
		return 0;
	}
	
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


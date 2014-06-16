/*
 * master.ino
 *
 * Created: 5/29/2014 3:59:20 PM
 * Author: annim
 */ 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#define TYP_SIZE 10

#define BAUD_RATE 9600


#define WITH_SERIAL


#include "MasterNode.h"
MasterNode node;



int startTime = 0;

int *buf;
int incomebytes[1] = {0};

void setup(void)
{
	node.beginDevice(2);
	delay(1000);
}

void loop()
{
	buf = node.listen(1000, TYP_SIZE);
	
	#ifdef WITH_SERIAL
	for(int i = 0; i< TYP_SIZE; i++){
		Serial.print(buf[i]);
		Serial.print(",");
	}
	#endif
	
	startTime = millis();
	while((millis()-startTime) < SEEK_SERVER_TIME){
		if (Serial.available() > 0)
		{
			incomebytes[0] = Serial.read();
			if(node.writeToClient(SLAVE_ID_1, incomebytes, sizeof(incomebytes) )){
				//success.
			}
			else{
				//fail.
			}
		}
		
	}
	
		
}

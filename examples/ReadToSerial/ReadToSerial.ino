#include "ADS131M03.h"


adc_channel_data adcInData;

const int Chip_Select = 10;
const int DRDY_Pin = 8;
const int Sync_Reset_Pin = 9;
const int MAX_CLK = 15000000;

volatile bool flag = false;


void setup() {
	InitADC(Chip_Select, DRDY_Pin, Sync_Reset_Pin, MAX_CLK, DRDY_ISR);		//Chip select pin, DRDY Pin, Sync/Reset Pin, Max SPI Clock, DRDY ISR function
	ChangeOSR(CLOCK_OSR_1024);									//Change OSR Clock

	delay(5000);
}


void loop() {

	if(flag == true){
		flag = false;
		readData(&adcInData);
	
		Serial.print(adcInData.channel0);
		Serial.print(adcInData.channel1);
		Serial.println(adcInData.channel2);
	}
}


void DRDY_ISR()
{
	flag = true;
}
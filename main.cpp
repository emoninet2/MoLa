#include "mbed.h"
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "LCD03/LCD03.h"
#include "NRF24L01p/NRF24L01p.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
 
NRF24L01p Radio;
NRF24L01p::Payload_t TxPayload;
NRF24L01p::Payload_t RxPayload;

LCD03 lcd(LCD03::LCD03_SERIAL,LCD03::LCD03_20_4,LCD03::LCD03_I2C_ADDRESS_0xc8);
 
PwmOut lampRed(PC_9);//PB_9
PwmOut lampGreen(PB_8);//PC_9
PwmOut lampBlue(PB_9);//PB_8
 

void lcd03_command_handler(int arg_count, char **args){
	if(!strcmp(args[0], "lcd") ) {
		if(!strcmp(args[1], "bl") ) {
			if(!strcmp(args[2], "0")) {
				lcd.backlight(0);
			}
			else if(!strcmp(args[2], "1")) {
				lcd.backlight(1);
			}
		}
		else if(!strcmp(args[1], "cs") ) {
			lcd.clear_screen();
		}
		else if(!strcmp(args[1], "cl") ) {
			lcd.clear_line(atoi(args[2]));
		}
		else if(!strcmp(args[1], "pc") ) {
			int row = atoi(args[2]);
			int col = atoi(args[3]);
			lcd.set_cursor_coordinate(row,col);
			lcd.print_string(args[4], 1);
		}
		else if(!strcmp(args[1], "pl") ) {
			int line = atoi(args[2]);
			if( (line>=1) && (line <=4)){
				lcd.set_cursor_coordinate(line,1);
				lcd.print_line(atoi(args[2]), args[3], strlen(args[3]));
			}

		}
		else if(!strcmp(args[1], "cm") ) {
			lcd.cursor_display_mode(LCD03::LCD03_CURSOR_DISP_t(atoi(args[2])));
		}
	}

}

bool charIsDelim(char c, char *delim){

    char * pch = delim;
    pch=strchr(delim,c);
    
    if((pch-delim)>=0){
        return 1;
    }else{
        return 0;
    }
}


int parseString(char * s, int len,  char * delim, int maxTokens, char ** argv){
    int argc ;
       
    int i;
    bool removeWhiteSpace = 1;
    for(i=0;i<len;i++){

        if(  charIsDelim(s[i],delim)   && (removeWhiteSpace)  ){
            s[i] = 0;
        }

        if(s[i] == '"' ){
            s[i] = 0;
            removeWhiteSpace = !removeWhiteSpace;
        }
        
    }
    
    int start = 0;
    argc = 0;
    for(i=0;i<len;i++){
        if(s[i] != 0){
            start = i;
            argv[argc++] = &s[i];
            break;
        }
    }
    
    for(i=start+1;i<len;i++){
        if( (s[i] != 0) && (s[i-1] == 0)  ){
            argv[argc++] = &s[i];
            if(argc > maxTokens){
                break;
            }
        }
    }
    
    
    return argc;
}




void setLampColorFromStr(char *colorCodeStr){
    uint32_t colorCode;
    colorCode = strtol(colorCodeStr,NULL,16);
    printf("your color code is : %x\r\n", colorCode);
    lampRed = (float) (((colorCode>>16)&0xFF) )/255;
    lampGreen = (float) (((colorCode>>8)&0xFF) )/255;
    lampBlue = (float) (((colorCode>>0)&0xFF) )/255;
}

void setLampColor(uint32_t colorCode){
 
    lampRed = (float) (((colorCode>>16)&0xFF) )/255;
    lampGreen = (float) (((colorCode>>8)&0xFF) )/255;
    lampBlue = (float) (((colorCode>>0)&0xFF) )/255;
}

void NRF24L01p_RadioReset(){

    Radio.RadioConfig.DataReadyInterruptEnabled = 1;
    Radio.RadioConfig.DataSentInterruptEnabled = 1;
    Radio.RadioConfig.MaxRetryInterruptEnabled = 1;
    Radio.RadioConfig.Crc = NRF24L01p::CONFIG_CRC_16BIT;
    Radio.RadioConfig.AutoReTransmissionCount = 15;
    Radio.RadioConfig.AutoReTransmitDelayX250us = 15;
    Radio.RadioConfig.frequencyOffset = 2;
    Radio.RadioConfig.datarate = NRF24L01p::RF_SETUP_RF_DR_2MBPS;
    Radio.RadioConfig.RfPowerDb = NRF24L01p::RF_SETUP_RF_PWR_0DBM;
    Radio.RadioConfig.PllLock = 0;
    Radio.RadioConfig.ContWaveEnabled = 0;
    Radio.RadioConfig.FeatureDynamicPayloadEnabled = 1;
    Radio.RadioConfig.FeaturePayloadWithAckEnabled = 1;
    Radio.RadioConfig.FeatureDynamicPayloadWithNoAckEnabled = 1;

    Radio.RxPipeConfig[0].address = 0xe7e7e7e7e7;
    Radio.RxPipeConfig[1].address = 0x6C616d7091;
    Radio.RxPipeConfig[2].address = 0x6C616d7092;
    Radio.RxPipeConfig[3].address = 0x6C616d7093;
    Radio.RxPipeConfig[4].address = 0x6C616d7094;
    Radio.RxPipeConfig[5].address = 0x6C616d7095;
 
    int i;
    for(i=0;i<6;i++){
        Radio.RxPipeConfig[i].PipeEnabled = 1;
        Radio.RxPipeConfig[i].autoAckEnabled = 1;
        Radio.RxPipeConfig[i].dynamicPayloadEnabled = 1;
    }
    
    //Radio.Initialize(&RadioConfig, RxPipeConfig);

    Radio.Initialize();
}

 
void radio_thread(void const *args) {
    Thread::wait(500);
    printf("starting Radio\r\n");
    NRF24L01p_RadioReset();

    while(1){
	printf("%#x %#x %#x %#x %#x\r\n",  Radio.read_register(0),  Radio.read_register(0x17), Radio.get_status() , Radio.read_register(0x5), Radio.read_register(0x6) );

	if(Radio.fifo_waiting(&Radio.RxFifo) > 0){
            printf("received data\r\n");
            Radio.ReceivePayloadViaFifo(&RxPayload);
            RxPayload.data[RxPayload.length] = '\0';
            printf("pipe %d : %s\r\n",RxPayload.pipe, RxPayload.data);
            Radio.flush_rx();
         

            if(RxPayload.pipe == 1){
                    printf("new message on pipe 1\r\n");
		    char *str = (char*)RxPayload.data;
		    char *tokenV[10];
		    int n = parseString(str, strlen(str),  " -/," , 10, tokenV);
		    int i;

		    lcd03_command_handler(n,tokenV);
		    //for(i=0;i<n;i++){
		    //	printf("\ttoken %d --> %s\r\n", i, tokenV[i]);
		    //}
            }
            if(RxPayload.pipe == 2){
                printf("new message on pipe 2\r\n");
		setLampColorFromStr((char*)RxPayload.data);
            }
        }
        Radio.process();

        //printf("%#x %#x %#x %#llx [%#llx]\r\n",  Radio.read_register(0),  Radio.read_register(0x17), Radio.get_status(), Radio.get_RX_pipe_address((NRF24L01p::pipe_t)1) , Radio.RxPipeConfig[1].address);
        Thread::wait(200);
        //Radio.hardwareCheck();
    }
    
    
    
    
}
 
void lcd_thread(void const *args) {
	lcd.clear_screen();
	lcd.set_cursor_coordinate(1,1);
	lcd.print_line(1, "MoLa", strlen("MoLa"));

    while (true) {
        //lcd.backlight(1);
        Thread::wait(1000);
        //lcd.backlight(0);
        Thread::wait(1000);
    }
}
 
int main() {
    lampRed.period_us(100);
    lampGreen.period_us(100);
    lampBlue.period_us(100);
  
    setLampColor(0x000000);
    //Create a thread to execute the function led2_thread
    Thread thread(radio_thread);
    Thread thread2(lcd_thread);
    //led2_thread is executing concurrently with main at this point
    
    while (true) {
        //led1 = !led1;
	//setLampColor(0xFF0000);
        //Thread::wait(1000);
	//setLampColor(0x00FF00); 
	//Thread::wait(1000);
	//setLampColor(0x0000FF );
	//Thread::wait(1000);
    }

    return 0;
}



#include <SI_EFM8BB1_Register_Enums.h>

//Initialize my device
void InitDevice(void)
{
	//Disable Watchdog Timer
	//Disable Watchdog with key sequence
	WDTCN = 0xDE; //First key
	WDTCN = 0xAD; //Second key
	//[WDTCN – Watchdog Timer Control]$

	//Setup Defaults for P1
	P1MDOUT = P1MDOUT_B0__OPEN_DRAIN | P1MDOUT_B1__OPEN_DRAIN 
	| P1MDOUT_B2__OPEN_DRAIN | P1MDOUT_B3__OPEN_DRAIN
	| P1MDOUT_B4__PUSH_PULL | P1MDOUT_B5__OPEN_DRAIN
	| P1MDOUT_B6__OPEN_DRAIN | P1MDOUT_B7__OPEN_DRAIN;
	
	//Setup Defaults for P0
	P0MDOUT = P0MDOUT_B0__PUSH_PULL | P0MDOUT_B1__PUSH_PULL
	| P0MDOUT_B2__PUSH_PULL | P0MDOUT_B3__PUSH_PULL
	| P0MDOUT_B4__PUSH_PULL | P0MDOUT_B5__PUSH_PULL
	| P0MDOUT_B6__PUSH_PULL | P0MDOUT_B7__PUSH_PULL;
	
	//Enable Weak Pullups
	XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED;

	//Disable Interrupts
	IE = IE_EA__DISABLED | IE_EX0__DISABLED | IE_EX1__DISABLED
	| IE_ESPI0__DISABLED | IE_ET0__DISABLED | IE_ET1__DISABLED
	| IE_ET2__ENABLED | IE_ES0__DISABLED;
}
//Declare my global variable for servo
unsigned char angle;

//Delay function for LCD
void delay(void){
	unsigned char a, b;
	for(a=0; a<0xFF; a++){
		for(b=0; b<0x70; b++){
		}
	}
}
//Data Write function for LCD
void LCD_Data_Write(unsigned char x){
	P0 = P0|(0x01<<3);    //RS = 1
	P0 = P0&~(0x01<<4);   //RW = 0
	P1 = x;               //D0-D7 gets written to P1
	P0 = P0|(0x01<<5);    //E = 1
	delay();              //Call delay function
	P0 = P0 &~ (0x01<<5); //E = 0
}
//Command Write function for LCD
void LCD_Command_Write (unsigned char y){
	P0 = P0&~(0x01<<3);   //RS = 0
	P0 = P0&~(0x01<<4);   //RW = 0
	P1 = y;               //D0-D7 gets written to P1
	P0 = P0|(0x01<<5);    //E = 1
	delay();              //Call delay function
	P0 = P0&~(0x01<<5);   //E = 0
}
//Main function
void main(void){
	InitDevice();
	angle = 10;            //Starts at midpoint
	IE = 0x82;             //Global enable and timer 0 Interrupt
	TMOD = 0x11;           //Set timer 0 and timer 1 to 16 Bit mode
	TL0 = 0x10;            //Load in hex value for 20ms
	TH0 = 0xEC;
	TCON = TCON|(0x01<<4); //Start timer0 TR0 = 1
	
	while(1){
		if(!(P0&(0x04))){      //When pressing MCU button, connected to P0.2
			angle = angle + 1;   //Decrement
			while(!(P0&(0x04))){ //polling MCU pushbutton
			}
		}
		if(!(P0&(0x02))){      //When pressing external button, connected to P0.1
			angle = angle - 1;   //Increment
			while(!(P0&(0x02))){ //Polling external button
			}
		}
		LCD_Command_Write(0x38); //8bit interface, 2 lines, 5x7 font
		LCD_Command_Write(0x0E); //autoincrement, no display shift
		LCD_Command_Write(0x01); //display on, cursor on, no blinking
		LCD_Command_Write(0x06); //clear display, set cursor to 0
		
		if(angle == 0){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x39);
			LCD_Data_Write(0x30);
		}
		if(angle == 1){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x38);
			LCD_Data_Write(0x31);
		}
		if(angle == 2){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x37);
			LCD_Data_Write(0x32);
		}
		if(angle == 3){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x36);
			LCD_Data_Write(0x33);
		}
		if(angle == 4){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x35);
			LCD_Data_Write(0x34);
		}
		if(angle == 5){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x34);
			LCD_Data_Write(0x35);
		}
		if(angle == 6){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x33);
			LCD_Data_Write(0x36);
		}
		if(angle == 7){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x32);
			LCD_Data_Write(0x37);
		}
		if(angle == 8){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x31);
			LCD_Data_Write(0x38);
		}
		if(angle == 9){
			LCD_Data_Write(0x2D);
			LCD_Data_Write(0x39);
		}
		if(angle == 10){
			LCD_Data_Write(0x30);
		}
		if(angle == 11){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x39);
		}
		if(angle == 12){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x31);
			LCD_Data_Write(0x38);
		}
		if(angle == 13){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x32);
			LCD_Data_Write(0x37);
		}
		if(angle == 14){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x33);
			LCD_Data_Write(0x36);
		}
		if(angle == 15){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x34);
			LCD_Data_Write(0x35);
		}
		if(angle == 16){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x35);
			LCD_Data_Write(0x34);
		}
		if(angle == 17){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x36);
			LCD_Data_Write(0x33);
		}
		if(angle == 18){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x37);
			LCD_Data_Write(0x32);
		}
		if(angle == 19){
			LCD_Data_Write(0x2B);
			LCD_Data_Write(0x38);
			LCD_Data_Write(0x31);
		}
	}
}
//ISR function
void Timer0_ISR(void) interrupt 1{
	unsigned int Value_THTL;
	unsigned int Value;
	P0 = P0|(0x01);                                //set signal pin high, set servo signal, P0.0
	Value = 13;
	TCON = TCON&~(0x01<<4);                        //TR0 = 0, stop timer0
	TL0 = 0x10;                                    //Reload values for another 20ms
	TH0 = 0xEC;
	TCON = TCON|(0x01<<4);                         //TR0 = 1, restart timer0
	TCON = TCON&~(0x01<<6);                        //TR1 = 0, stop timer1
	TCON = TCON&~(0x01<<7);                        //TF1 = 0, clear timer1 flag
	Value_THTL = 0xFF01 - (Value * angle);         //Variable pulse 1ms~2ms for servo angle
	TL1 = (unsigned char)((Value_THTL)&0x00FF);    //Typecasting
	TH1 = (unsigned char)((Value_THTL>>8)&0x00FF);
	TCON = TCON|(0x01<<6);                         //TR1 = 1, restart timer1
	while (!(TCON&(0x01<<7))){                     //Polling, do nothing untill TF1 = 1
	}
	TCON = TCON&~(0x01<<6);                        //TR1 = 0, stop timer1
	TCON = TCON&~(0x01<<7);                        //TF1 = 0, clear timer1 flag
	P0 = P0&~(0x01);                               //set signal pin low, clear servo signal, P0.0
}
#include<reg51.h>

sbit Out = P2^0;		   // Pin P2.0 is named as Out
sbit In = P1^0;

//Enter


sbit Step1 = P1^1;
sbit Step2 = P1^2;
sbit Step3 = P1^3;
sbit Step4 = P1^4;
sbit Step5 = P1^5;

//Function declarations
void cct_init(void);
void delay_usec(unsigned int);

// Global Variables
unsigned char TimeUp = 0;  // variable used to generate delay

// Main function
int main(void)
{
   cct_init(); 	// Make all ports zero
   while(1)                // Rest is done in Timer0 interrupt
   {
		 if(Step5==0)
				 Out = 0xFF;
		 else if(In==1)
		 {
			 
			 if(Step1==0)
			 {
						Out = 0xFF;
						delay_usec(2000);
			 }
			 if(Step2==0)
			 {
						Out = 0xFF;
						delay_usec(2000*2);
			 }
			 if(Step3==0)
			 {
						Out = 0xFF;
						delay_usec(2000*3);
			 }
			 if(Step4==0)
			 {
						Out = 0xFF;
						delay_usec(2000*4);
			 }
			 if(Step5==0)
			 {
						Out = 0xFF;
						delay_usec(2000*5);
			 }
			 
		 }
		 else
			 Out=0;
   }
}

// Circuit Initialize function
void cct_init(void)
{
	P0 = 0xFF;   
	P1 = 0xFF;   
	P2 = 0x00;   
	P3 = 0xFF;  
}

// Delay function, it generates delay in micro seconds
void delay_usec(unsigned int d)   // d can have a value from 0 to 65535 only.
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x01;    // Set timer0 in mode 1 = 16bit mode
	
	TH0  = 0xFF - (d>>8)&0xFF;	// Load timer0 registers with 
	TL0  = 0xFF - d&0xFF;		// delay value							   
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TimeUp = 0;      // When timer expires then this variable will become 1

	TR0 = 1;         // Start Timer 0

	while(!TimeUp);  // Wait for timeup

	TR0 = 0;         // Done
}

// Timer0 ISR function
void Timer0_ISR (void) interrupt 1   // It is called after every 250usec
{
	TimeUp = 1;  // Make TimeUp variable 1 to indicate timer0 overflow
	TF0 = 0;     // Clear the interrupt flag
}


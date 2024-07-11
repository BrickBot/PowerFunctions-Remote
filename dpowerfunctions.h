// LEGO Power Function protocol for BrickOS
//
//Bob Kojima 01-28-2008
//bob@fial.com
//v1.0.1

#include <conio.h>
#include <unistd.h>

#include <lnp/lnp-logical.h>
#include <sys/h8.h>
#include <sys/time.h>
 
//channel
#define CH1 0x0
#define CH2 0x1
#define CH3 0x2
#define CH4 0x3

//mode
#define COMBO_DIRECT_MODE 0x01
#define SINGLE_PIN_CONTINUOUS 0x2
#define SINGLE_PIN_TIMEOUT 0x3
#define SINGLE_OUTPUT 0x4

//speed
#define RED_FLT 0x0
#define RED_FWD 0x1
#define RED_REV 0x2
#define RED_BRK 0x3
#define BLUE_FLT 0x0
#define BLUE_FWD 0x4
#define BLUE_REV 0x8
#define BLUE_BRK 0xC

//PWM speed steps
#define PWM_FLT 0x0
#define PWM_FWD1 0x1
#define PWM_FWD2 0x2
#define PWM_FWD3 0x3
#define PWM_FWD4 0x4
#define PWM_FWD5 0x5
#define PWM_FWD6 0x6
#define PWM_FWD7 0x7
#define PWM_BRK 0x8
#define PWM_REV7 0x9
#define PWM_REV6 0xA
#define PWM_REV5 0xB
#define PWM_REV4 0xC
#define PWM_REV3 0xD
#define PWM_REV2 0xE
#define PWM_REV1 0xf

//Clear - Set - Toggle
#define CL_C1_CL_C2 0x0
#define ST_C1_CL_C2 0x1
#define CL_C1_ST_C2 0x2
#define ST_C1_ST_C2 0x3
#define INC_PWM 0x4
#define DEC_PWM 0x5
#define FULL_FWD 0x6
#define FULL_REV 0x7
#define TOG_FWD_REV 0x8

//output
#define RED 0x0
#define BLUE 0x1

//pin
#define PIN_C1 0x0
#define PIN_C2 0x1

//functions
#define NO_CHANGE 0x0
#define CLEAR 0x1
#define SET 0x2
#define TOGGLE 0x3

int toggle[4] = {0,0,0,0};

inline void MSpause(unsigned char a)
{
	//microsecond pause
  unsigned char b, c;

  for (b = 0; b < a; b++)
    for (c = 0; c < 1; c++);
}

inline void start_pause()
{
	//start bit pause for 1014탎
	MSpause(255);
	MSpause(85);
}

inline void high_pause()
{
	//high bit pause for 546탎
  MSpause(185);
}

inline void low_pause()
{
	//low bit pause for 260탎
	MSpause(90);
}

inline void tx_pause()
{
	//ir pause 156탎
	MSpause(55);
}

inline void mark_pause()
{
	//ir pause 78탎
	MSpause(26);
}

inline void message_pause(int channel, int count)
{
  unsigned char a = 0;
  
  if(count == 0)
    a = 4 - channel + 1;
  else if(count == 1 || count == 2)
    a = 5;
  else if(count == 3 || count == 4)
    a = 5 + (channel + 1) * 2;
      
  MSpause(a * 16);
}

//There are 1,000 milliseconds in 1 second; 1,000 microseconds in 1 millisecond;
//0,000 001 [ millionth ] microsecond [ 탎 ]  
//0,001 [ thousandth ] millisecond [ ms ] 

void IRMark()
{
	int i;
	
	asm("ORC #128, ccr");  // clear interrupts

  // clear TE and RE bits 
  S_CR = S_CR & 0xCF;

  // set direction on the P50 (TxD) to out
  PORT5_DDR = 5;
	
  for(i = 0; i < 6; i++)
  {
  	PORT5 = 0;
    mark_pause();
    PORT5 = 1;
    mark_pause();
  }	
  
  // set again TE and RE bits
  S_CR = S_CR | 0x30;

  asm("ANDC #127, ccr"); // set interrupts
}

void ir_send(int code1, int code2)
{
  int x;// = 128;//128 2048 16384 32768

  asm("ORC #128, ccr");  // clear interrupts

  // clear TE and RE bits 
  S_CR = S_CR & 0xCF;

  // set direction on the P50 (TxD) to out
  PORT5_DDR = 5;

  //start
  PORT5 = 0;
  
  tx_pause();
  PORT5 = 1;
  start_pause();
  
  x = 128;
  while (x)
  {
  	PORT5 = 0;
    tx_pause();
    PORT5 = 1;
    
    if (code1 & x) //high bit
      high_pause();
    else //low bit
      low_pause();
    
    x >>= 1;  //next bit
  }
  
  x = 128;
  while (x)
  {
  	PORT5 = 0;
    tx_pause();
    PORT5 = 1;
    
    if (code2 & x) // high bit
      high_pause();
    else //low bit
      low_pause();

    x >>= 1;  //next bit
  }

  //stop
  PORT5 = 0;
  tx_pause();
  PORT5 = 1;
  start_pause();

  // set again TE and RE bits
  S_CR = S_CR | 0x30;

  asm("ANDC #127, ccr"); // set interrupts
  
  //sometimes if we send 2 packets in a row to the same channel one of them gets ignored 
  //this little pause fixes that 
  //msleep(10);
}

void pf_send(int code1, int code2, int channel, int tog)
{
   int i;
 
   IRMark(); 
   for(i = 0; i < 5; i++)
   {
   	 message_pause(channel, i);
     ir_send(code1, code2);    
   }
   
   if(tog)
   {
     if(toggle[channel] == 0)
       toggle[channel] = 8;
     else
       toggle[channel] = 0;
   }	
}

void ComboMode(int blue_speed, int red_speed, int channel)
{
   int nib1, nib2, nib3, nib4;
   
   //set nibs
   nib1 = 0 | channel;
   nib2 = COMBO_DIRECT_MODE;
   nib3 = blue_speed | red_speed;
   nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

   pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4, channel, 0);
}

void SinglePin(int mode, int function, int pin, int output, int channel)
{
  int nib1, nib2, nib3, nib4;

   //set nibs
   nib1 = toggle[channel] | channel;
   nib2 = 0x00 | mode;
   nib3 = output << 4 | pin << 3 | function;
   nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

   pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4, channel, 1);    
}

void SingleOutput(int pwm, int output, int channel)
{
  int nib1, nib2, nib3, nib4;

   //set nibs
   nib1 = toggle[channel] | channel;
   nib2 = SINGLE_OUTPUT | output;
   nib3 = pwm;
   nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

   pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4, channel, 1); 
}

void SingleOutputCST(int cst, int output, int channel)
{
  int nib1, nib2, nib3, nib4;

   //set nibs
   nib1 = toggle[channel] | channel;
   nib2 = SINGLE_OUTPUT | 0x2 | output;
   nib3 = cst;
   nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

   pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4, channel, 1); 
}

void ComboPWM(int blue_pwm, int red_pwm, int channel)
{
  int nib1, nib2, nib3, nib4;

   //set nibs
   nib1 = 0 | 0x4 | channel;
   nib2 = blue_pwm;
   nib3 = red_pwm;
   nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

   pf_send(nib1 << 4 | nib2, nib3 << 4 | nib4, channel, 0); 
}
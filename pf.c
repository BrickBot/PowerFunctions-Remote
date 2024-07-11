// LEGO Power Function PWM Remote
//
//Bob Kojima 01-28-2008
//bob@fial.com
//v1.0.1

#include <dpowerfunctions.h>
#include <dsensor.h> 
#include <dbutton.h> 
 

int main(int argc, char **argv)
{
  char ra,rb, ba,bb;
  int R[4] = {8,8,8,8};
  int B[4] = {8,8,8,8};
  
  int S[15] = {7,6,5,4,3,2,1,8,15,14,13,12,11,10,9};
  int SS[15] = {7,6,5,4,3,2,1,0,1,2,3,4,5,6,7};
  
  int c = 0;
  
  systime_set_timeslice(255);
  lnp_logical_range(1);
  
  ds_active (&SENSOR_1);
	ds_rotation_on (&SENSOR_1);
	ds_rotation_set (&SENSOR_1, 8);

  ds_active (&SENSOR_3);
	ds_rotation_on (&SENSOR_3);
	ds_rotation_set (&SENSOR_3, 8);
  
  while(1)
  {
  	 if(PRESSED(dbutton(),BUTTON_VIEW))
  	 {  
  	 	 c--;
  	   if(c < 0)
  	     c = 3;
  	   ds_rotation_set (&SENSOR_1, R[c]);
  	   ds_rotation_set (&SENSOR_3, B[c]);
  	 }
  	 if(PRESSED(dbutton(),BUTTON_PROGRAM))
  	 {
  	   c++;
  	   if(c > 3)
  	     c = 0;
  	   ds_rotation_set (&SENSOR_1, R[c]);
  	   ds_rotation_set (&SENSOR_3, B[c]);
  	 }
     if(PRESSED(dbutton(),BUTTON_RUN))
     {
     	 ComboMode(BLUE_FLT, RED_FLT, CH1); 
       ComboMode(BLUE_FLT, RED_FLT, CH2);
       ComboMode(BLUE_FLT, RED_FLT, CH3); 
       ComboMode(BLUE_FLT, RED_FLT, CH4);
     }

  	 
  	 if(ROTATION_1 != R[c])
  	 {  	 	  
  	 	  if(ROTATION_1 > -1 && ROTATION_1 < 15)
  	 	  {
  	 	  	 R[c] = ROTATION_1;
  	 	  	 SingleOutput(S[R[c]], RED, c);
  	 	  }
  	 }
  	 
  	 if(ROTATION_3 != B[c])
  	 {  	 	  
  	 	  if(ROTATION_3 > -1 && ROTATION_3 < 15)
  	 	  {
  	 	  	 B[c] = ROTATION_3;
  	 	  	 SingleOutput(S[B[c]], BLUE, c);
  	 	  }
  	 }
  	 
  	 
  	 if (R[c] > 8)
  	   ra = '-';
  	 else ra = 'r';
  	 
  	 if (B[c] > 8)
  	   ba = '-';
  	 else ba = 'b';
  	 
  	 rb = SS[R[c]] + 48;
  	 bb = SS[B[c]] + 48;
  	  
  	 cputc_0(c+48+1); //Channel
  	 cputc_1(bb); //blue
     cputc_2(ba); //B
     cputc_3(rb);//red
     cputc_4(ra);//R
     //cputc_5('5');
     msleep(200);
  }


  
/*   
  SingleOutput(PWM_FWD6, BLUE, CH1);
  SingleOutput(PWM_FWD6, RED, CH1);
  SingleOutput(PWM_FWD6, BLUE, CH2);
  SingleOutput(PWM_FWD6, RED, CH2);
  SingleOutput(PWM_FWD6, BLUE, CH3);
  SingleOutput(PWM_FWD6, RED, CH3);
  SingleOutput(PWM_FWD6, BLUE, CH4);
  SingleOutput(PWM_FWD6, RED, CH4);
sleep(4);  
  ComboMode(BLUE_REV, RED_REV, CH1); 
  ComboMode(BLUE_REV, RED_REV, CH2);
  ComboMode(BLUE_REV, RED_REV, CH3); 
  ComboMode(BLUE_REV, RED_REV, CH4);
sleep(4);

  ComboPWM(PWM_FWD3, PWM_FWD3, CH1);
  ComboPWM(PWM_FWD3, PWM_FWD3, CH2);
  ComboPWM(PWM_FWD3, PWM_FWD3, CH3);
  ComboPWM(PWM_FWD3, PWM_FWD3, CH4);
*/

  //SinglePin(SINGLE_PIN_CONTINUOUS, SET, PIN_C1, BLUE, CH1);

  cputs("done ");
  sleep(1);

  cls();

  return 0;
}

//dll -v -tusb pf.lx

// LEGO Power Function sample code
//just shows how to use some of the library fuctions
//
//Bob Kojima 01-28-2008
//bob@fial.com
//v1.0.1

#include <dpowerfunctions.h>
#include <dsensor.h> 
#include <dbutton.h> 
 

int main(int argc, char **argv)
{ 
  systime_set_timeslice(255);
  lnp_logical_range(1);
   
  SingleOutput(PWM_FWD6, BLUE, CH1);
  SingleOutput(PWM_FWD6, BLUE, CH2);
  SingleOutput(PWM_FWD6, BLUE, CH1);
  SingleOutput(PWM_FWD6, BLUE, CH2);
  sleep(4);
  SingleOutput(PWM_FWD6, RED, CH1);  
  SingleOutput(PWM_FWD6, RED, CH2);
  
  //SingleOutput(PWM_FWD6, BLUE, CH3);
  //SingleOutput(PWM_FWD6, RED, CH3);
  //SingleOutput(PWM_FWD6, BLUE, CH4);
  //SingleOutput(PWM_FWD6, RED, CH4);
 
sleep(4);  
  ComboMode(BLUE_REV, RED_REV, CH1); 
  ComboMode(BLUE_REV, RED_REV, CH2);
sleep(2);  
  ComboMode(BLUE_FWD, RED_FWD, CH1); 
  ComboMode(BLUE_FWD, RED_FWD, CH2);
  //ComboMode(BLUE_REV, RED_REV, CH3); 
  //ComboMode(BLUE_REV, RED_REV, CH4);
sleep(2);

  ComboPWM(PWM_FWD6, PWM_FWD6, CH1);
  ComboPWM(PWM_FWD6, PWM_FWD6, CH2);

sleep(2);

  //ComboPWM(PWM_FWD3, PWM_FWD3, CH3);
  //ComboPWM(PWM_FWD3, PWM_FWD3, CH4);

  SingleOutputCST(INC_PWM, RED, CH1);
  SingleOutputCST(INC_PWM, RED, CH2);

sleep(2);
  SingleOutputCST(DEC_PWM, RED, CH1);
  SingleOutputCST(DEC_PWM, RED, CH2);
sleep(2);
  SingleOutputCST(FULL_FWD, RED, CH1);
  SingleOutputCST(FULL_REV, RED, CH2);
sleep(2);
  SingleOutputCST(INC_PWM, RED, CH1);
  SingleOutputCST(INC_PWM, RED, CH2);
  SingleOutputCST(ST_C1_ST_C2, RED, CH1);
  SingleOutputCST(ST_C1_ST_C2, RED, CH2);
sleep(2);
  SinglePin(SINGLE_PIN_CONTINUOUS, TOGGLE, PIN_C1, RED, CH1);
  SinglePin(SINGLE_PIN_CONTINUOUS, TOGGLE, PIN_C2, RED, CH1);
  SinglePin(SINGLE_PIN_CONTINUOUS, TOGGLE, PIN_C1, RED, CH2);
  SinglePin(SINGLE_PIN_CONTINUOUS, TOGGLE, PIN_C2, RED, CH2);

  SinglePin(SINGLE_PIN_CONTINUOUS, SET, PIN_C1, BLUE, CH1);
  sleep(2);
  SinglePin(SINGLE_PIN_CONTINUOUS, TOGGLE, PIN_C1, BLUE, CH1);
  sleep(2);
  SinglePin(SINGLE_PIN_CONTINUOUS, CLEAR, PIN_C1, BLUE, CH1);

  cputs("done ");
  sleep(1);

  cls();

  return 0;
}

//dll -v -tusb pf-test.lx

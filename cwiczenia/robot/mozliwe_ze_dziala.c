#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ethernet.h"
#include "driverlib/ethernet.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
//#include "drivers/display96x16x1.h"
#include "drivers/io.h"
#include "drivers/motor.h"
#include "drivers/sensors.h"

typedef enum
{
    STATE_STOPPED,
    STATE_RUNNING,
    STATE_LEWY,
    STATE_PRAWY
} tMotorState;

static volatile unsigned long g_ulTickCount,cofanie;

#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
    for(;;)
    {
    }
}
#endif

void
SysTickHandler(void)
{
    g_ulTickCount++;
    cofanie++;

    if((g_ulTickCount % 100) == 0)
    {
        LED_Toggle(BOTH_LEDS);
    }
    PushButtonDebouncer();
    BumpSensorDebouncer();
}

int sterowanie(tDirection kierunek,int pwmL,int pwmP)
{
	 MotorDir((tSide)1,(tDirection)kierunek);
	 MotorDir((tSide)0,(tDirection)kierunek);
	 MotorSpeed((tSide)0, pwmL << 8);
	 MotorSpeed((tSide)1, pwmP << 8);
	 cofanie=0;
	 MotorRun((tSide)0);
	 MotorRun((tSide)1);
	
	 return 0;
}

int
main(void)
{
    unsigned long ulPHYMR0;
    tBoolean bButtonWasPressed = false;
    tMotorState sMotorState=STATE_STOPPED;

    
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
    ulPHYMR0 = ROM_EthernetPHYRead(ETH_BASE, PHY_MR0);
    ROM_EthernetPHYWrite(ETH_BASE, PHY_MR0, ulPHYMR0 | PHY_MR0_PWRDN);

    //
    // Initialize the board display
    //
   // Display96x16x1Init(true);

    //
    // Print a simple message to the display
    //
  //  Display96x16x1StringDraw("MOTOR", 29, 0);
  //  Display96x16x1StringDraw("DEMO", 31, 1);

    //
    // Initialize the LED driver, then turn one LED on
    //
    LEDsInit();
    LED_On(LED_1);

    PushButtonsInit();
    BumpSensorsInit();
    MotorsInit();
    ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / 100);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();
    for(;;)
    {

       
            tBoolean bButtonIsPressed;
            tBoolean bBumperIsPressed[2];

            bButtonIsPressed = !PushButtonGetDebounced((tButton)1);
            bBumperIsPressed[0] = !BumpSensorGetDebounced((tBumper)0);
            bBumperIsPressed[1] = !BumpSensorGetDebounced((tBumper)1);

            switch(sMotorState)
            {
                case STATE_STOPPED:
                {
                    if(bButtonIsPressed && !bButtonWasPressed)
                    {
                    	sterowanie(0,50,50);
                        sMotorState = STATE_RUNNING;
                    }
                    break;
                }

                 case STATE_RUNNING:
                {
                	 
                    if(bButtonIsPressed && !bButtonWasPressed)
                    {
                        MotorStop((tSide)0);
                        MotorStop((tSide)1);
                        sMotorState = STATE_STOPPED;
                    }

                    else if(bBumperIsPressed[0])
                    {
                         MotorStop((tSide)0);
                         MotorStop((tSide)1);
                         sterowanie(1,15,60);
                         sMotorState = STATE_LEWY;
                    }

                    else if(bBumperIsPressed[1]){
                          MotorStop((tSide)0);
                          MotorStop((tSide)1);
                          sterowanie(1,60,15);
                          sMotorState = STATE_PRAWY;
                          }
                    break;
                }

               case STATE_PRAWY:
                {
                        while(cofanie<250);
                        MotorStop((tSide)0);
                        MotorStop((tSide)1);
                        sterowanie(0,50,50);
                        sMotorState = STATE_RUNNING;

                    break;
                }
                case STATE_LEWY:
                               {
					
                	while(cofanie<250);
                	MotorStop((tSide)0);
                      	MotorStop((tSide)1);
                      	sterowanie(0,50,50);
                      	sMotorState = STATE_RUNNING;
                        break;
                               }

               default:
                {
                    MotorStop((tSide)1);
                    MotorStop((tSide)0);
                    sMotorState = STATE_STOPPED;
                  break;
                }
            } 

           bButtonWasPressed = bButtonIsPressed;

         
    } 
}

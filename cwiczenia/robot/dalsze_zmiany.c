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
#include "driverlib/udma.h"
#include "drivers/sound.h"
#include "drivers/wav.h"
#include "sounds.h"
//https://github.com/hrshygoodness/Luminary-Micro-Library/blob/master/boards/ek-evalbot/sound_demo/sound_demo.c
//http://wklej.org/id/1731827/
//http://www68.zippyshare.com/v/obaaYPKA/file.html
typedef enum
{
    STATE_STOPPED,
    STATE_RUNNING,
    STATE_TYL
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

#ifdef ewarm
#pragma data_alignment=1024
tDMAControlTable sDMAControlTable[64];
#elif defined(ccs)
#pragma DATA_ALIGN(sDMAControlTable, 1024)
tDMAControlTable sDMAControlTable[64];
#else
tDMAControlTable sDMAControlTable[64] __attribute__ ((aligned(1024)));
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
    tWaveHeader sWaveHeader;
    unsigned long ulWaveIndex = 1;
    int losL,losH;
    
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
    ulPHYMR0 = ROM_EthernetPHYRead(ETH_BASE, PHY_MR0);
    ROM_EthernetPHYWrite(ETH_BASE, PHY_MR0, ulPHYMR0 | PHY_MR0_PWRDN);

	         	 // Display96x16x1Init(true);
	        	//  Display96x16x1StringDraw("MOTOR", 29, 0);
	         	 //  Display96x16x1StringDraw("DEMO", 31, 1);

    LEDsInit();
    LED_On(LED_1);
    PushButtonsInit();
    BumpSensorsInit();
    MotorsInit();
    ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / 100);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();
    SoundInit();
    // WaveOpen((unsigned long *) sWaveClips[ulWaveIndex].pucWav, &sWaveHeader);
    //mozliwe ze trzeba przed kazdym odtworzeniem ;/
   // while(WaveOpen((unsigned long *)
     //                            sWaveClips[ulWaveIndex].pucWav,
       //                          &sWaveHeader) != WAVE_OK);//do zablokowania w razie bledu
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
                //       WavePlayStart(&sWaveHeader); mozliwe ze tu
                	losL =10+ g_ulTickCount % 20;//i dać los zamiast 15,mamy losowe skrecanie(10-30)
                     	losH =40+ g_ulTickCount % 30;//i dać los zamiast 60,mamy losowe skrecanie(40-70)
                         sterowanie(1,losL,losH);
                	 sMotorState = STATE_TYL;
                    }

                    else if(bBumperIsPressed[1]){
                          MotorStop((tSide)0);
                          MotorStop((tSide)1);
                      	  losL =10+ g_ulTickCount % 20;//i dać los zamiast 15,mamy losowe skrecanie(10-30)
                     	  losH =40+ g_ulTickCount % 30;//i dać los zamiast 60,mamy losowe skrecanie(40-70)
                          sterowanie(1,losH,losL);
                //       WavePlayStart(&sWaveHeader); mozliwe ze tu
                          sMotorState = STATE_TYL;
                          }
                    break;
                }

               case STATE_TYL:
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

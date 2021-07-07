#ifndef FUNCTIONS
#define FUNCTIONS

#include "matrix.h"

int FanActualSpeed = 0,
    ActualVolume = 0, 
    lastCommand = -1;
    
time_t lastCommandTime = 0;

void submitFunction (int val, int check = 0, bool feedback = false)
{
    if(check and lastCommand == val and lastCommandTime + check >= millis())
        return ;
  
    const int type = val / 1000, 
              functionID = val % 1000;

    switch(type)
    {
        case 1:
            switch(functionID)
            {
                case 2: //Switch Roof Light
                    __RoofLightON__.state ^= 1;
                    digitalWrite(ROOF_LIGHT_PIN, __RoofLightON__.state ? HIGH : LOW);
                    break;

                case 5:  //Fan Speed
                    cleanMatrix();
                    __FanVelocity__[FanActualSpeed].state = false;
                    FanActualSpeed = FanActualSpeed % 3 + 1;
                    __FanVelocity__[FanActualSpeed].state = true;
                    delay(300);
                    digitalWrite(MATRIX_PIN_LATCH, LOW);
                    shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b00000011);
                    digitalWrite(MATRIX_PIN_LATCH, HIGH);
                    delay(40); 
                    digitalWrite(MATRIX_PIN_LATCH, LOW);
                    shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b00000000);
                    digitalWrite(MATRIX_PIN_LATCH, HIGH);
                    break;
  
                case 9:  //Fan OFF
                    cleanMatrix();
                    __FanVelocity__[FanActualSpeed].state = false;
                    FanActualSpeed = 0;
                    __FanVelocity__[FanActualSpeed].state = true;
                    delay(300);
                    digitalWrite(MATRIX_PIN_LATCH, LOW);
                    shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b00001100);
                    digitalWrite(MATRIX_PIN_LATCH, HIGH);
                    delay(40); 
                    digitalWrite(MATRIX_PIN_LATCH, LOW);
                    shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b00000000);
                    digitalWrite(MATRIX_PIN_LATCH, HIGH);
                    break;
  
                case 21: //Switch Amplificator
                    __AmpliON__.state ^= 1;
                    digitalWrite(AMPLI_PIN, __AmpliON__.state ? HIGH : LOW);
                    break;
                   
            
                case 25: //Switch Desktop Light
                    __DesktopLightON__.state ^= 1;
                    digitalWrite(DESKTOP_LIGHT_PIN, __DesktopLightON__.state ? HIGH : LOW);
                    break;
            }
            break;
         case 2:
            switch(functionID){
                case 4: //Change Matrix Mode
                    matrixMode = matrixMode % 2 + 1;
                    break;
                   
                case 2: //Switch PC
                    if(__PcON__.state)
                        submitFunction(3003);
                    else
                    {
                        digitalWrite(PC_ON_PIN, HIGH);
                        delay(100);
                        digitalWrite(PC_ON_PIN, LOW);
                    }
                    break;

                case 20:
                    Serial.print("enter#");
                    break;

                case 45:
                    Serial.print("upArrow#");
                    break;

                case 46:
                    Serial.print("rightArrow#");
                    break;

                case 47:
                    Serial.print("downArrow#");
                    break;

                case 48:
                    Serial.print("leftArrow#");
                    break;

                case 21:
                    Serial.print("volumeMute#");
                    break;

                case 13:
                    Serial.print("volumeUp#");
                    break;

                case 17:
                    Serial.print("volumeDown#");
                    break;

                case 44:
                    Serial.print("browserBack#");
                    break;

                case 40:
                    Serial.print("mediaStop#");
                    break;

                case 38:
                    Serial.print("mediaPlayPause#");
                    break;
                    
                case 36:
                    Serial.print("mediaPrevTrack#");
                    break;

                case 37:
                    Serial.print("mediaNextTrack#");
                    break;
                    
                case 32:
                    Serial.print("LJ#");
                    break;

                case 33:
                    Serial.print("LL#");
                    break;

                case 27:
                    Serial.print("LS#");
                    break;

                case 30:
                    Serial.print("LQ#");
                    break;

                case 31:
                    Serial.print("LW#");
                    break;

                case 5:
                    Serial.print("nextDesk#");
                    break;

                case 9:
                    Serial.print("prevDesk#");
                    break;

                case 1:
                    Serial.print("closeApp#");
                    break;

                case 43:
                    Serial.print("changeApp#");
                    break;
            }
            break;
         case 3:
            switch(functionID)
            {
                case 1:
                    Serial.print("ConnectionUpdate#");
                    break;
                case 2:
                    Serial.print("VolumeUpdate#");
                    break;
                case 3:
                    Serial.print("Shutdown#");
                    break;
            }
    }

    lastCommand = val;
    lastCommandTime = millis();
}

int Temperature ()
{
  return (int)((float)analogRead(TERMOMETER_PIN) * 500 / 1023);
}

#endif // FUNCTIONS

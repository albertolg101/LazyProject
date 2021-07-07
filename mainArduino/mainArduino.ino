#include <TimeLib.h>
#include <IRremote.h>

#define RECV_PIN 14
#define PC_ON_PIN 15
#define AMPLI_PIN 16
#define DESKTOP_LIGHT_PIN 17
#define ROOF_LIGHT_PIN 18
#define TERMOMETER_PIN A5

#include "matrix.h"
#include "functions.h"

int ActualTemperature;
time_t lastTemperatureTime = 0, 
       lastConnectionUpdate = 0,
       lastVolumeUpdate = 0;

bool  PC_feedback,
      PC_feedbackCheck = false;

IRrecv irrecv(RECV_PIN);
decode_results IRresults;

void setup() {
    Serial.begin(9600);
    pinMode(13, OUTPUT);

    {
      int _row[8] = {2, 3, 4, 5, 6, 7, 8, 9};
      initMatrix(12, 11, 10, _row);
    }

    pinMode(PC_ON_PIN, OUTPUT);
    pinMode(AMPLI_PIN, OUTPUT);
    pinMode(DESKTOP_LIGHT_PIN, OUTPUT);
    pinMode(ROOF_LIGHT_PIN, OUTPUT);

    submitFunction(1009); //Apagar Ventilador

    setTime(20,25,0,23,4,2021);

    irrecv.enableIRIn();

    ActualTemperature = Temperature();
}

void loop() {
  
    if(irrecv.decode(&IRresults) and IRresults.decode_type == SONY)
    {        
        switch(IRresults.value)
        {
            case 0xA90:   //Switch Roof Light
                submitFunction(1002, 500);
                break;
                
            case 0xA50:   //Switch Desktop Light
                submitFunction(1025, 500);
                break;
  
            case 0x290:   //Switch Amplificator
                submitFunction(1021, 500);
                break;
                
            case 0x90:    //Fan Speed
                submitFunction(1005);
                break;
  
            case 0x890:   //Fan OFF
                submitFunction(1009);
                break;

            case 0x96BCA: //Change Matrix Mode
                submitFunction(2004, 500);
                break;

            case 0xA8BCA: //Switch PC
                submitFunction(2002, 3000);
                break;
        
            case 0xD0BCA: //Enter
                submitFunction(2020, 300);
                break;

            case 0x42BCA: //Up Arrow
                submitFunction(2045, 100);
                break;

            case 0x86BCA: //Right Arrow
                submitFunction(2046, 100);
                break;

            case 0xC2BCA: //Down Arrow
                submitFunction(2047, 100);
                break;

            case 0x46BCA: //Right Arrow
                submitFunction(2048, 100);
                break;

            case 0x9EBCA: //Volume Mute              
                submitFunction(2021, 300);
                break;

            case 0x490:   //Volume Up
                submitFunction(2013, 100);
                break;

            case 0xC90:   //Volume Down
                submitFunction(2017, 100);
                break;

            case 0x24BCA: //Return 
                submitFunction(2044, 300);
                break;

            case 0x18BCA: //Stop
                submitFunction(2040, 300);
                break;

            case 0x58BCA: // Play
            case 0x98BCA: // Pause
                submitFunction(2038, 300);
                break;

            case 0xEABCA: // Prev Track
                submitFunction(2036, 300);
                break;

            case 0x6ABCA: // Next Track
                submitFunction(2037, 300);
                break;

            case 0xD8BCA: // <<
                submitFunction(2032, 100);
                break;

            case 0x38BCA: // >>
                submitFunction(2033, 100);
                break;

            case 0x6BCA:  // Subtitle\Timer
                submitFunction(2027, 300);
                break;

            case 0xDABCA: // Reducir retardo de subtitulos
                submitFunction(2030, 200);
                break;

            case 0xBABCA: // Aumentar retardo de subtitulos
                submitFunction(2031, 200);
                break;

            case 0x8BCA:  // Siguiente escritorio
                submitFunction(2005, 300);
                break;

            case 0x88BCA: // Anterior escritorio
                submitFunction(2009, 300);
                break;

            case 0x68BCA: // Cerrar Aplicacion
                submitFunction(2001, 500);
                break;

            case 0xC4BCA: // Cambiar de aplicacion
                submitFunction(2043, 300);
                break;
        }
    }

    irrecv.resume(); // empezamos una nueva recepción
    
    byte len = 0;
    char commandFromSerial[31];

    if(Serial.available() > 0)
    {
        len = Serial.readBytesUntil('#', (char *)commandFromSerial, 30) ;
        commandFromSerial[len] = '\0';

        PC_feedback = true;
        PC_feedbackCheck = true;

        if(!strcmp(commandFromSerial, "PC_ON")) //Computadora Encendida
        {
            __PcON__.state = true;
        }
        
        else if(commandFromSerial[0] == 'c' and commandFromSerial[1] == 'u') //Connection Update
        {
            __TPLinkConection__.state = (commandFromSerial[2] == '1');
            __ETECSAConection__.state = (commandFromSerial[3] == '1');
            __IntranetConection__.state = (commandFromSerial[4] == '1');
            __InternetConection__.state = (commandFromSerial[5] == '1');
            __Person1Conection__.state = (commandFromSerial[6] == '1');
            __Person2Conection__.state = (commandFromSerial[7] == '1');
        }

        else if(commandFromSerial[0] == 'v' and commandFromSerial[1] == 'u') // Volume Update
        {
            int number = 0;
            for(int i = 0 ; i < 3 ; i++)
                number = number * 10 + commandFromSerial[i+3] - '0';

            __PcMasterMute__.state = (commandFromSerial[2] == '-');
        
            for(int i = 0 ; i < 10 ; i++)
                __PcMasterVolume__[i].state = (number != 0 and number >= i * 10);
        }

        commandFromSerial[0] = Serial.read();
        commandFromSerial[0] = '\n';
    }
    
    if(__PcON__.state)
    {
        if(now() - lastConnectionUpdate >= 60)
        {
            submitFunction(3001); // Connection Update
            lastConnectionUpdate = now();
        }

        if(now() - lastVolumeUpdate >= 15)
        {
            if(PC_feedbackCheck == false)
                PC_feedback = false;
          
            PC_feedbackCheck = false;          
            submitFunction(3002); // Volume Update
            lastVolumeUpdate = now();
        }
    }
    
    if(now() - lastTemperatureTime >= 5)
    {
        ActualTemperature = Temperature();
        lastTemperatureTime = now();
    }
    
    switch(matrixMode)
    {
        case 1:
            setToInfoMode(ActualTemperature, PC_feedback);
            break;

        case 2:
            setToClockMode(hour(now()), minute(now()), second(now()));
            break;
    }
    
    printMatrix();
}

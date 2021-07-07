#ifndef MATRIX
#define MATRIX

bool mainMatrix[8][8];
int matrixMode = 1;
/*
Matrix mode:
1: Info Mode
2: Clock Mode
3: Timer
4: Setting Time
5: Setting Alarm
*/

struct pixel
{
	int x, y;
	bool state;

	pixel(int _x = 0, int _y = 0, int _state = false): x(_x), y(_y), state(_state){}
};

//Info state constants

int MATRIX_PIN_LATCH, 
  	MATRIX_PIN_CLOCK,
   	MATRIX_PIN_DATA, 
	  row[8];

pixel __ArduinoON__ 		= {0, 0, true},  //La arduino esta funcinando 
	  __IR__ 				= {0, 1, false}, //El sensor IR recibe datos
	  __AlarmON__			= {0, 6, false},
	  __Sec__ 				= {0, 7, false}, //Transcurrio un segundo
	  __PcON__				= {1, 0, false}, //La arduino recibe informacion del driver de la PC para la arduino
	  __RoofLightON__ 		= {1, 1, false}, //La luz del techo esta encendida
	  __DesktopLightON__	= {1, 2, false}, //La luz de escritorio esta encendida
	  __AmpliON__			= {1, 7, false}, //El amplificador esta encendido
	  __PcMasterMute__  	= {2, 7, false},
	  __TPLinkConection__	= {6, 0, false}, //192.168.1.106 (Mi direccion IP repartida por TP-LINK)
	  __ETECSAConection__ 	= {6, 1, false}, //dmoj.uclv.edu.cu (Sitio gratuito)
	  __IntranetConection__ = {6, 2, false}, //cubadebate.cu (Sitio accesible a travez de Intranet)
	  __InternetConection__ = {6, 3, false}, //google.com (Sitio accesible a travez de internet)
	  __Person1Conection__ 	= {6, 4, false}, //192.168.1.111 (Mama esta conectada)
	  __Person2Conection__ 	= {6, 5, false}, //192.168.1.102 (Papa esta conectado)

	  __FanVelocity__[4] 	  = {{1, 3, true}, {1, 4, false}, {1, 5, false}, {1, 6, false}},
	  __PcMasterVolume__[10]  = {{7, 6, false}, {6, 6, false}, {5, 6, false}, {4, 6, false}, {3, 6, false},
							   	   {7, 7, false}, {6, 7, false}, {5, 7, false}, {4, 7, false}, {3, 7, false}},
	  __DekstopNumber__[3]    = {{7, 0, false}, {7, 1, false}, {7, 2, false}};

//Time State constants

pixel __Timer__ 		= {3, 3, false},
	  __SettingTime__	= {3, 4, false},
	  __SettingAlarm__  = {4, 3, false},
	  __cAlarmON__		= {4, 4, false},
	  
	  __Hours__[12] 	= {{2, 3}, {2, 4}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {5, 4}, {5, 4}, {5, 2}, {4, 2}, {3, 2}, {2, 2}},
	  __Minutes__[20]	= {{1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {1, 2}},
	  __Seconds__[30]	= {{0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}, {7, 6}, {7, 5}, {7, 4}, {7, 3}, {7, 2}, {7, 1}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}, {0, 1}, {0, 2}, {0, 2}, {0, 2}};

void initMatrix (int _LATCH, int _CLOCK, int _DATA, int _row[])
{
	for(int i = 0 ; i < 8 ; i++)
	{
		row[i] = _row[i];
		pinMode(row[i], OUTPUT);
		digitalWrite(row[i], HIGH);
	}

	MATRIX_PIN_LATCH = _LATCH;
	MATRIX_PIN_CLOCK = _CLOCK;
	MATRIX_PIN_DATA = _DATA;

	pinMode(MATRIX_PIN_LATCH, OUTPUT);
	pinMode(MATRIX_PIN_CLOCK, OUTPUT);
	pinMode(MATRIX_PIN_DATA, OUTPUT);
}

void mainMatrixUpdate (pixel &p)
{
	mainMatrix[p.x][p.y] = p.state;
}

void mainMatrixUpdate (pixel &p, bool sol)
{
  mainMatrix[p.x][p.y] = sol;
}

void setToInfoMode (int temperature = 0, bool PC_feedback = false)
{
	for(int i = 0 ; i < 8 ; i++)
	{
		for(int j = 0 ; j < 8 ; j++)
		{
			mainMatrix[i][j] = false;
		}
	}

	mainMatrixUpdate(__ArduinoON__);
	mainMatrixUpdate(__IR__);
	mainMatrixUpdate(__AlarmON__);
	mainMatrixUpdate(__Sec__);
	mainMatrixUpdate(__PcON__);
	mainMatrixUpdate(__RoofLightON__);
	mainMatrixUpdate(__DesktopLightON__);
	mainMatrixUpdate(__AmpliON__);
	mainMatrixUpdate(__TPLinkConection__);
	mainMatrixUpdate(__ETECSAConection__);
	mainMatrixUpdate(__IntranetConection__);
	mainMatrixUpdate(__InternetConection__);
	mainMatrixUpdate(__Person1Conection__);
	mainMatrixUpdate(__Person2Conection__);
	mainMatrixUpdate(__PcMasterMute__);

	for(int i = 0 ; i < 4 ; i++)
		mainMatrixUpdate(__FanVelocity__[i]);

	for(int i = 0 ; i < 10 ; i++)
		mainMatrixUpdate(__PcMasterVolume__[i]);

	for(int i = 0 ; i < 3 ; i++)
		mainMatrixUpdate(__DekstopNumber__[i]);

  for(int i = 0 ; i < 6 ; i++)
    mainMatrix[5][5-i] = ((temperature & (1<<i)) > 0);

  if(!PC_feedback)
  {
    __PcON__.state = false;
    mainMatrixUpdate(__PcON__);
    mainMatrixUpdate(__TPLinkConection__, false);
    mainMatrixUpdate(__ETECSAConection__, false);
    mainMatrixUpdate(__IntranetConection__, false);
    mainMatrixUpdate(__InternetConection__, false);
    mainMatrixUpdate(__Person1Conection__, false);
    mainMatrixUpdate(__Person2Conection__, false);
    mainMatrixUpdate(__PcMasterMute__, false);

    for(int i = 0 ; i < 10 ; i++)
      mainMatrixUpdate(__PcMasterVolume__[i], false);

    for(int i = 0 ; i < 3 ; i++)
      mainMatrixUpdate(__DekstopNumber__[i], false);
  }
}

void setToClockMode (int hh, int mm, int ss)
{
	for(int i = 0 ; i < 8 ; i++)
	{
		for(int j = 0 ; j < 8 ; j++)
		{
			mainMatrix[i][j] = false;
		}
	}

	hh = hh % 12;
	mm = (mm % 60) / 3;
	ss = (ss % 60) / 2;

	mainMatrix[__Hours__[hh].x][__Hours__[hh].y] = true;
	mainMatrix[__Minutes__[mm].x][__Minutes__[mm].y] = true;
	mainMatrix[__Seconds__[ss].x][__Seconds__[ss].y] = true;
}

void printMatrix (bool invMode = false)
{
  if(invMode)
  {
    for(int i = 0 ; i < 8 ; i++)
    {
      for(int j = 0 ; j < 8 ; j++)
      {
        digitalWrite(row[j], mainMatrix[i][j] ? HIGH : LOW);
      }
  
      digitalWrite(MATRIX_PIN_LATCH, LOW);
      shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b11111111 - (1<<i));
      digitalWrite(MATRIX_PIN_LATCH, HIGH);
  
      delay(300);
  
      digitalWrite(MATRIX_PIN_LATCH, LOW);
      shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b11111111);
      digitalWrite(MATRIX_PIN_LATCH, HIGH);
    }
  }
  else
  {
    for(int i = 0 ; i < 8 ; i++)
    {
      for(int j = 0 ; j < 8 ; j++)
      {
        digitalWrite(row[j], mainMatrix[i][j] ? LOW : HIGH);
      }
  
      digitalWrite(MATRIX_PIN_LATCH, LOW);
      shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, (1<<i));
      digitalWrite(MATRIX_PIN_LATCH, HIGH);
  
      //delay(100);
  
      digitalWrite(MATRIX_PIN_LATCH, LOW);
      shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0);
      digitalWrite(MATRIX_PIN_LATCH, HIGH);
    }
  }
}

void cleanMatrix ()
{
  for(int i = 0 ; i < 8 ; i++)
      digitalWrite(row[i], HIGH);
  digitalWrite(MATRIX_PIN_LATCH, LOW);
  shiftOut(MATRIX_PIN_DATA, MATRIX_PIN_CLOCK, MSBFIRST, 0b00000000);
  digitalWrite(MATRIX_PIN_LATCH, HIGH);
}

#endif //MATRIX

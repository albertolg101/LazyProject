#include <iostream>
#include <windows.h>
#include "functions.h"
#include "PressKeys.h"
#include "ArduSerial/ArduSerial.cpp"
#include "ArduSerial/pch.cpp"

using namespace std;

string buff;

void setup ()
{
	Serial3.begin(9600);
	while (Serial27.available())
		Serial27.read();
	Serial3.print("PC_ON#");
}

void loop ()
{
	char temp = Serial3.read();

	while(temp != '#')
	{
		while(!Serial3.available());
		temp = Serial3.read();

		if(temp == '#')
			break;

		buff += temp;
	}

	if(buff == "ConnectionUpdate")
		ipTest();

	else if(buff == "VolumeUpdate")
		volUpd();

	else if(buff == "enter")
	{
		enter(true);
		enter(false);
	}

	else if(buff == "leftArrow")
	{
		leftArrow(true);
		leftArrow(false);
	}

	else if(buff == "upArrow")
	{
		upArrow(true);
		upArrow(false);
	}

	else if(buff == "rightArrow")
	{
		rightArrow(true);
		rightArrow(false);
	}

	else if(buff == "downArrow")
	{
		downArrow(true);
		downArrow(false);
	}

	else if(buff == "volumeMute")
	{
		volumeMute(true);
		volumeMute(false);
	}

	else if(buff == "volumeUp")
	{
		volumeUp(true);
		volumeUp(false);
	}

	else if(buff == "volumeDown")
	{
		volumeDown(true);
		volumeDown(false);
	}

	else if(buff == "browserBack")
	{
		browserBack(true);
		browserBack(false);
	}

	else if(buff == "mediaStop")
	{
		mediaStop(true);
		mediaStop(false);
	}

	else if(buff == "mediaPlayPause")
	{
		mediaPlayPause(true);
		mediaPlayPause(false);
	}

	else if(buff == "mediaNextTrack")
	{
		mediaNextTrack(true);
		mediaNextTrack(false);
	}

	else if(buff == "mediaPrevTrack")
	{
		mediaPrevTrack(true);
		mediaPrevTrack(false);
	}

	else if(buff[0] == 'L')
	{
		letterKey(buff[1], true);
		letterKey(buff[1], false);
	}

	else if(buff == "prevDesk" or buff == "nextDesk")
	{
		winKey(true);
		ctrlKey(true);
		buff == "prevDesk" ? leftArrow(true) : rightArrow(true);
		buff == "prevDesk" ? leftArrow(false) : rightArrow(false);
		ctrlKey(false);
		winKey(false);
	}

	else if(buff == "closeApp")
	{
		altKey(true);
		F4Key(true);
		F4Key(false);
		altKey(false);
	}

	else if(buff == "changeApp")
	{
		winKey(true);
		tabKey(true);
		tabKey(false);
		winKey(false);
	}

	else if(buff == "Shutdown")
		system("start /B /ABOVENORMAL shut_down");

	buff.clear();
}

int main()
{
	setup();
	while(true)
		loop();

	return 0;
}

/*
time_t tim = time(nullptr);
tm* temp = localtime(&tim);
	
cout << temp->tm_hour << ' ' << temp->tm_min << ' ' << temp->tm_sec ; 
*/
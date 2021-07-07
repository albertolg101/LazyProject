#ifndef PressKeys
#define PressKeys

#include <windows.h>

void enter (bool sol)
{
	keybd_event(VK_RETURN, 0x0D, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void leftArrow (bool sol)
{
	keybd_event(VK_LEFT, 0x25, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void upArrow (bool sol)
{
	keybd_event(VK_UP, 0x26, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void rightArrow (bool sol)
{
	keybd_event(VK_RIGHT, 0x27, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void downArrow (bool sol)
{
	keybd_event(VK_DOWN, 0x28, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void volumeMute (bool sol)
{
	keybd_event(VK_VOLUME_MUTE, 0xAD, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void volumeUp (bool sol)
{	
	keybd_event(VK_VOLUME_UP, 0xAF, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void volumeDown (bool sol)
{
	keybd_event(VK_VOLUME_DOWN, 0xAE, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void browserBack (bool sol)
{
	keybd_event(VK_BROWSER_BACK, 0xA6, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void mediaStop (bool sol)
{
	keybd_event(VK_MEDIA_STOP, 0xB2, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void mediaPlayPause (bool sol)
{
	keybd_event(VK_MEDIA_PLAY_PAUSE, 0xB3, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void mediaNextTrack (bool sol)
{
	keybd_event(VK_MEDIA_NEXT_TRACK, 0xB0, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void mediaPrevTrack (bool sol)
{
	keybd_event(VK_MEDIA_PREV_TRACK, 0xB1, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void letterKey (char letter, bool sol)
{
	keybd_event(VkKeyScan(letter), 0x41 + letter - 'A', sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void winKey (bool sol)
{
	keybd_event(VK_LWIN, 0x5B, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void ctrlKey (bool sol)
{
	keybd_event(VK_CONTROL, 0x11, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void altKey (bool sol)
{
	keybd_event(VK_MENU, 0x12, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void tabKey (bool sol)
{
	keybd_event(VK_TAB, 0x09, sol ? 0 : KEYEVENTF_KEYUP, 0);
}

void F4Key (bool sol)
{
	keybd_event(VK_F4, 0x73, sol ? 0 : KEYEVENTF_KEYUP, 0);	
}

#endif // PressKeys
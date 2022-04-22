#ifndef _MainLoop_H_
#define _MainLoop_H_

#include "SDLQuickLoad.h"
#include "TextureLayer.h"
#include "Button.h"
#include "Scenery.h"
#include "Props.h"
#include "Character.h"
#include "LoadMap.h"

#include <vector>
#include <iostream>
#include <sstream>

const int FPS = 60;

void MainLoop();
void Delay(int& preTime, int& postTime);

#endif 

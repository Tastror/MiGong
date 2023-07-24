#ifndef _LoadMap_H_
#define _LoadMap_H_

#include "Scenery.h"
#include "Character.h"
#include <cstring>
#include <ctime>
#include <cstdio>

struct Archive {
	int year = 0;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int x;
	int y;
	int begin_x;
	int begin_y;
	int end_x;
	int end_y;
	char map[Radix * Radix2];
};

void LoadMap(Scenery* Sce);
void LoadMap(Scenery* Sce, Archive* archi);
void LoadMap(Scenery* Sce, Character* chara, Archive* archi);
void SaveMap(Scenery* Sce, Character* chara, Archive* archi);
void SaveMap(Scenery* Sce, Archive* archi);
std::string GetTime(Archive* archi);
std::string GetTimeNoColon(Archive* archi);

#endif

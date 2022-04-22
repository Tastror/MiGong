#include "LoadMap.h"

void LoadMap(Scenery* Sce)
{
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
		{
			Sce->material[i * Radix + j] = 0;
		}
	srand(SDL_GetTicks());
	int rep = 1500;
	while (rep--)
	{
		int i = rand() % (Width / ScenCell);
		int j = rand() % (Height / ScenCell);
		while (Sce->material[i * Radix + j])
		{
			i = rand() % (Width / ScenCell);
			j = rand() % (Height / ScenCell);
		}
		Sce->material[i * Radix + j] = 1;
	}
	{
		int i = rand() % (Width / ScenCell);
		int j = rand() % (Height / ScenCell);
		while (Sce->material[i * Radix + j])
		{
			i = rand() % (Width / ScenCell);
			j = rand() % (Height / ScenCell);
		}
		Sce->material[i * Radix + j] = 3;
	}
	Sce->FindBE();
	return;
}

void LoadMap(Scenery* Sce, Archive* archi)
{
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			Sce->material[i * Radix + j] = archi->map[i * Radix + j];
	Sce->begin_mx = archi->begin_x / ScenCell;
	Sce->begin_my = archi->begin_y / ScenCell;
	Sce->end_mx = archi->end_x / ScenCell;
	Sce->end_my = archi->end_y / ScenCell;
	// std::cout << chara->cx << ", " << chara->cy << std::endl;
	return;
}

void LoadMap(Scenery* Sce, Character* chara, Archive* archi)
{
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			Sce->material[i * Radix + j] = archi->map[i * Radix + j];
	chara->cx = chara->home_cx = archi->x;
	chara->cy = chara->home_cy = archi->y;
	Sce->begin_mx = archi->begin_x / ScenCell;
	Sce->begin_my = archi->begin_y / ScenCell;
	Sce->end_mx = archi->end_x / ScenCell;
	Sce->end_my = archi->end_y / ScenCell;
	// std::cout << chara->cx << ", " << chara->cy << std::endl;
	return;
}

void SaveMap(Scenery* Sce, Archive* archi)
{
	time_t pret = time(NULL);
	tm* nowtime = localtime(&pret);
	archi->year = nowtime->tm_year + 1900,
	archi->month = nowtime->tm_mon + 1,
	archi->day = nowtime->tm_mday,
	archi->hour = nowtime->tm_hour,
	archi->minute = nowtime->tm_min;
	archi->second = nowtime->tm_sec;
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			archi->map[i * Radix + j] = Sce->material[i * Radix + j];
	archi->x = Sce->begin_mx * ScenCell;
	archi->y = Sce->begin_my * ScenCell;
	archi->begin_x = Sce->begin_mx * ScenCell;
	archi->begin_y = Sce->begin_my * ScenCell;
	archi->end_x = Sce->end_mx * ScenCell;
	archi->end_y = Sce->end_my * ScenCell;
	// std::cout << Sce->begin_mx << ", " << Sce->begin_my << std::endl;
	return;
}

void SaveMap(Scenery* Sce, Character* chara, Archive* archi)
{
	time_t pret = time(NULL);
	tm* nowtime = localtime(&pret);
	archi->year = nowtime->tm_year + 1900,
	archi->month = nowtime->tm_mon + 1,
	archi->day = nowtime->tm_mday,
	archi->hour = nowtime->tm_hour,
	archi->minute = nowtime->tm_min;
	archi->second = nowtime->tm_sec;
	for (int i = 0; i < Radix; ++i)
		for (int j = 0; j < Radix2; ++j)
			archi->map[i * Radix + j] = Sce->material[i * Radix + j];
	archi->x = chara->cx;
	archi->y = chara->cy;
	archi->begin_x = Sce->begin_mx * ScenCell;
	archi->begin_y = Sce->begin_my * ScenCell;
	archi->end_x = Sce->end_mx * ScenCell;
	archi->end_y = Sce->end_my * ScenCell;
	return;
}

std::string GetTime(Archive* archi)
{
	return std::to_string(archi->year) + "." + std::to_string(archi->month) + "." + std::to_string(archi->day) + " "
	+ std::to_string(archi->hour) + ":" + std::to_string(archi->minute) + ":" + std::to_string(archi->second);
}

std::string GetTimeNoColon(Archive* archi)
{
	return std::to_string(archi->year) + "." + std::to_string(archi->month) + "." + std::to_string(archi->day) + "_"
	+ std::to_string(archi->hour) + "." + std::to_string(archi->minute) + "." + std::to_string(archi->second);
}

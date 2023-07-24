#include "MainLoop.h"

void MainLoop()
{
	// Pre_Definitions:
	bool Quit = false;
	SDL_Event event = { 0 };
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int preTime = SDL_GetTicks();
	int postTime = SDL_GetTicks();
	std::vector<char> selectionVec;
	int Root = -1;
	int SightMode = -1;
	int premouse_x = 0, premouse_y = 0;
	int nowmouse_x = 100, nowmouse_y = 100;
	
	Archive sysmap[3];
	for (int rep = 1; rep <= 3; ++rep)
	{
		std::string name = "../map/sysmap" + std::to_string(rep);
		FILE* fmap = fopen(name.c_str(), "rb+");
		fread(&sysmap[rep - 1], sizeof(sysmap[rep - 1]), 1, fmap);
		fflush(fmap);
		fclose(fmap);
	}
	
	FILE* flog = fopen("../log/log", "rb+");
	Archive arch[5];
	selectionVec.push_back(Root);
	fread(arch, sizeof(arch), 5, flog);
	
	// Window:
	Window w("Programming Tales", 900, 600);
	
	// Texture:
	Texture tGround(w.gr()), tGround2(w.gr()), tRole1(w.gr()), tRole2(w.gr()), tRole3(w.gr()), tRole4(w.gr()), tPM(w.gr()), tSM(w.gr()), tMM(w.gr()), 
	tTree(w.gr()), tGG(w.gr()), tEG(w.gr()), tSky(w.gr()), tSV(w.gr()), tGB(w.gr()), tSI(w.gr()), tLI(w.gr()), tWin(w.gr());
	WordTexture tDT[4] { WordTexture(w.gr()), WordTexture(w.gr(), GetTime(&arch[1])), WordTexture(w.gr(), GetTime(&arch[2])), WordTexture(w.gr(), GetTime(&arch[3])) };
	tGround.LoadParent("../image/background.bmp", {255, 0, 0, 0});
	tGround2.Load("../image/background2.bmp");
	tRole1.LoadParent("../image/role1.bmp");
	tRole2.LoadParent("../image/role2.bmp");
	tRole3.LoadParent("../image/role3.bmp");
	tRole4.LoadParent("../image/role4.bmp");
	tPM.LoadParent("../image/PauseMenu.bmp", {255, 0, 0, 0});
	tSM.Load("../image/StartMenu.bmp");
	tMM.Load("../image/MapMenu.bmp");
	tTree.LoadParent("../image/tree.bmp");
	tGG.Load("../image/greenground.bmp");
	tEG.Load("../image/endground.bmp");
	tSky.Load("../image/sky.bmp");
	tSV.Load("../image/saving.bmp");
	tGB.LoadParent("../image/goback.bmp", {255, 0, 0, 0});
	tSI.LoadParent("../image/saveit.bmp", {255, 0, 0, 0});
	tLI.LoadParent("../image/loadin.bmp", {255, 0, 0, 0});
	tWin.LoadParent("../image/win.bmp", {255, 0, 0, 0});
	
	// Animation
	Animation aGround, aGround2, aRole, aPauMen, aStaMen, aMapMen, aTree, aGrGr, aEnGr, aSky, aSave, aDate[4], aGoba, aSait, aLoin, aWin;
	aGround.Compose(&tGround);
	aGround2.Compose(&tGround2);
	aRole.Compose(&tRole1);
	aRole.Compose(&tRole2);
	aRole.Compose(&tRole3);
	aRole.Compose(&tRole4);
	aPauMen.Compose(&tPM);
	aStaMen.Compose(&tSM);
	aMapMen.Compose(&tMM);
	aTree.Compose(&tTree);
	aGrGr.Compose(&tGG);
	aEnGr.Compose(&tEG);
	aSky.Compose(&tSky);
	aSave.Compose(&tSV);
	aDate[1].Compose(&tDT[1]);
	aDate[2].Compose(&tDT[2]);
	aDate[3].Compose(&tDT[3]);
	aGoba.Compose(&tGB);
	aSait.Compose(&tSI);
	aLoin.Compose(&tLI);
	aWin.Compose(&tWin);
	
	// TextureLayer
	MapTextureLayer GamePicture(w.gr());
	GamePicture.Push(&aSky, 0, 0);
	GamePicture.Push(&aGround, 0, 0);
	const int backNum = GamePicture.PreNumber();
	GamePicture.Push(&aGrGr, 0, 0);
	const int testNum = GamePicture.PreNumber();
	GamePicture.Push(&aEnGr, 0, 0), GamePicture.LayerElement[GamePicture.PreNumber()].use = false;
	const int endNum = GamePicture.PreNumber();
	GamePicture.Push(&aRole, 0, 0);
	const int roleNum = GamePicture.PreNumber();
	// 5000 trees to provide "Props: Tree" with
	const int treeNum = GamePicture.layerNum;
	for (int i = 0; i < 6500; ++i)
	GamePicture.Push(&aTree, 0, 0), GamePicture.LayerElement[GamePicture.PreNumber()].use = false;
	
	TextureLayer WinMenu(w.gr());
	WinMenu.Push(&aWin, 100, 100);
	
	TextureLayer PauseMenu(w.gr());
	PauseMenu.Push(&aPauMen, 100, 100); 
	
	TextureLayer StartMenu(w.gr());
	StartMenu.Push(&aStaMen, 0, 0); 
	
	TextureLayer MapMenu(w.gr());
	MapMenu.Push(&aMapMen, 0, 0);
	
	TextureLayer Saving(w.gr());
	Saving.Push(&aSave, 0, 0);
	const int dateNum = Saving.layerNum;
	Saving.Push(&aDate[1], 350, 216 - 30);
	Saving.Push(&aDate[2], 350, 342 - 30);
	Saving.Push(&aDate[3], 350, 468 - 30);
	
	MapTextureLayer MapMaking(w.gr());
	MapMaking.Push(&aSky, 0, 0);
	MapMaking.Push(&aGround2, 0, 0);
	const int mapNum = MapMaking.PreNumber();
	const int mapgreenNum = MapMaking.layerNum;
	for (int i = 0; i < 6500; ++i)
	MapMaking.Push(&aGrGr, 0, 0), MapMaking.LayerElement[MapMaking.PreNumber()].use = false;
	const int maptreesNum = MapMaking.layerNum;
	for (int i = 0; i < 100; ++i)
	MapMaking.Push(&aTree, 0, 0), MapMaking.LayerElement[MapMaking.PreNumber()].use = false;
	const int mapEndNum = MapMaking.layerNum;
	for (int i = 0; i < 100; ++i)
	MapMaking.Push(&aEnGr, 0, 0), MapMaking.LayerElement[MapMaking.PreNumber()].use = false;
	MapMaking.Push(&aSait, 10, 10);
	MapMaking.Push(&aGoba, 770, 10);
	MapMaking.Push(&aLoin, 400, 10);
	
	
	// Scenery:
	Scenery Background;
	Background.Push(&GamePicture, backNum);
	
	Scenery Newmap;
	Newmap.Push(&MapMaking, mapNum);
	
	
	// Character:
	Character Player(&Background);
	Player.Push(&GamePicture, roleNum);
	
	
	// Props:
	Props Trees(&Background, &GamePicture, treeNum);
	Props Ends(&Background, &GamePicture, endNum);
	LoadMap(&Background, &Player, &arch[0]);
	Trees.LoadInScen(1);
	Ends.LoadInScen2(3);
	
	Props Greens(&Newmap, &MapMaking, mapgreenNum);
	Greens.LoadInScen2(1);
	Props MTrees(&Newmap, &MapMaking, maptreesNum);
	MTrees.LoadInScen(2);
	Props MEnds(&Newmap, &MapMaking, mapEndNum);
	MTrees.LoadInScen2(3);
	
	// Button:
	Button pausebuttons;
	pausebuttons.Add(100, 100, 700, 400);
	pausebuttons.Add(394, 220, 493 - 394, 252 - 220);
	pausebuttons.Add(394, 260, 493 - 394, 292 - 260);
	pausebuttons.Add(394, 300, 493 - 394, 332 - 300);
	pausebuttons.Add(394, 340, 493 - 394, 372 - 340);
	pausebuttons.Add(336, 380, 552 - 336, 412 - 380);
	
	Button menubuttons;
	menubuttons.Add(85, 210, 392 - 85, 255 - 210);
	menubuttons.Add(85, 270, 257 - 85, 318 - 270);
	menubuttons.Add(85, 332, 257 - 85, 377 - 332);
	menubuttons.Add(85, 390, 257 - 85, 439 - 390);
	menubuttons.Add(85, 450, 168 - 85, 496 - 450);
	
	Button savingbuttons;
	savingbuttons.Add2(715, 49, 802, 88);
	savingbuttons.Add2(197, 172, 718, 227);
	savingbuttons.Add2(195, 294, 703, 349);
	savingbuttons.Add2(192, 425, 715, 481);
	
	Button mapmenubuttons;
	mapmenubuttons.Add2(708, 72, 784, 117);
	mapmenubuttons.Add2(406, 225, 468, 288);
	mapmenubuttons.Add2(540, 226, 604, 284);
	mapmenubuttons.Add2(669, 218, 732, 278);
	mapmenubuttons.Add2(403, 409, 455, 463);
	mapmenubuttons.Add2(530, 402, 719, 462);
	
	Button mapmakingbuttons;
	mapmakingbuttons.Add(10, 10, 120, 60);
	mapmakingbuttons.Add(770, 10, 120, 60);
	mapmakingbuttons.Add(400, 10, 120, 60);
	
	Button winmenubuttons;
	// winmenubuttons.Add();
	// winmenubuttons.Add();
	
	// Loop:
	while (!Quit)
	{
		
		for(std::vector<char>::iterator iter = selectionVec.begin(); iter != selectionVec.end(); iter++)
			std::cout << (int)*iter << ' ';
		std::cout << std::endl;
		
		
		switch (Root)
		{
		case -1:
			{
				StartMenu.Update();
				w.Present();
				
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_MOUSEMOTION:
					{
						menubuttons.In(event.motion.x, event.motion.y);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						menubuttons.Click(event.motion.x, event.motion.y);
						switch (menubuttons.click)
						{
						case 0:
							{
								Root = 1;
								selectionVec.push_back(Root);
							}
							break;
						case 1:
							{
								Root = 3;
								selectionVec.push_back(Root);
							}
							break;
						case 2:
							{
								LoadMap(&Background);
								Trees.LoadInScen(1);
								Ends.LoadInScen2(3);
								// std::cout << Background.end_mx << ", " << Background.end_my << std::endl;
								Player.RandomReborn();
								SightMode = -1;
								Root = 1;
								selectionVec.push_back(Root);
							}
							break;
						case 3:
							{
								Root = 2;
								selectionVec.push_back(Root);
							}
							break;
						case 4:
							{
								Quit = true;
							}
							break;
						}
					}
					break;
				}
			}
			break; // Root case -1: Start Menu
		
		case 0:
			{
				GamePicture.Update();
				PauseMenu.Update();
				w.Present();
				
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_MOUSEMOTION:
					{
						pausebuttons.In(event.motion.x, event.motion.y);
						switch (pausebuttons.nowIn)
						{
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						pausebuttons.Click(event.motion.x, event.motion.y);
						// std::cout << event.motion.x << ", " << event.motion.y << std::endl;
						switch (pausebuttons.click)
						{
						case -1:
							break;
						case 0:
							break;
						case 1:
							{
								Root = 1;
								selectionVec.pop_back();
							}
							break;
						case 2:
							{
								while (selectionVec.back() != -1)
									selectionVec.pop_back();
								Root = 3;
								selectionVec.push_back(Root);
							}
							break;
						case 3:
							{
								selectionVec.pop_back();
								selectionVec.pop_back();
								Root = selectionVec.back();
							}
							break;
						case 4:
							{
								Root = 2;
								selectionVec.push_back(Root);
							}
							break;
						case 5:
							{
								SightMode *= -1;
								Root = 1;
								selectionVec.pop_back();
							}
							break;
						}
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_c:
						{
							Root = 1;
							selectionVec.pop_back();
						}
						break;
					case SDLK_l:
						{
							while (selectionVec.back() != -1)
								selectionVec.pop_back();
							Root = 3;
							selectionVec.push_back(Root);
						}
						break;
					case SDLK_q:
						{
							selectionVec.pop_back();
							selectionVec.pop_back();
							Root = selectionVec.back();
						}
						break;
					case SDLK_s:
						{
							Root = 2;
							selectionVec.push_back(Root);
						}
						break;
					case SDLK_y:
						{
							SightMode *= -1;
							Root = 1;
							selectionVec.pop_back();
						}
						break;
					case SDLK_ESCAPE:
						{
							Root = 1;
							selectionVec.pop_back();
						}
						break;
					}
					break;
				}
			}
			break; // Root case 0: Pause Menu
		
		case 1:
			{
				// Print:
				GamePicture.LayerElement[testNum].tx = Player.cmx * ScenCell - Background.sx;
				GamePicture.LayerElement[testNum].ty = Player.cmy * ScenCell - Background.sy;
				// std::cout << GamePicture.LayerElement[testNum].tx << ' ' << GamePicture.LayerElement[testNum].ty << std::endl;
				Background.SlowSynXY();
				Player.SynXY();
				Trees.SynXY();
				Ends.SynXY();
				GamePicture.Update();
				// Win
				{
					if (Player.win == 1)
					{
						WinMenu.Update();
						
					}
				}
				
				w.Present();
				
				// Press:
				{
					if (state[ SDL_SCANCODE_A ])
						Player.Move(-1, 0);
					if (state[ SDL_SCANCODE_D ])
						Player.Move(1, 0);
					if (state[ SDL_SCANCODE_W ])
						Player.Move(0, -1);
					if (state[ SDL_SCANCODE_S ])
						Player.Move(0, 1);
					
					if (SightMode == 1 && !state[ SDL_SCANCODE_SPACE ])
					{
						if (state[ SDL_SCANCODE_LEFT ])
							Background.Move(-1, 0);
						if (state[ SDL_SCANCODE_RIGHT ])
							Background.Move(1, 0);
						if (state[ SDL_SCANCODE_UP ])
							Background.Move(0, -1);
						if (state[ SDL_SCANCODE_DOWN ])
							Background.Move(0, 1);
					}
					else
					{
						Player.LockSight();
					}
				}
				
				// Event:
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_c:
					case SDLK_ESCAPE:
						{
							Root = 0;
							selectionVec.push_back(Root);
						}
						break;
					case SDLK_r:
						{
							Player.cx = Player.home_cx;
							Player.cy = Player.home_cy;
						}
						break;
					case SDLK_y:
						{
							SightMode *= -1;
						}
						break;
					}
					break;
				}
			}
			break; // Root case 1: Game Playing
		
		case 2:
			{
				for (int i = 1; i <= 3; ++i)
				{
					if (arch[i].year == 0)
						Saving.LayerElement[dateNum + i - 1].use = false;
					else
						Saving.LayerElement[dateNum + i - 1].use = true;
				}
				Saving.Update();
				w.Present();
				
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						savingbuttons.Click(event.motion.x, event.motion.y);
						// std::cout << event.motion.x << ", " << event.motion.y << std::endl;
						switch (savingbuttons.click)
						{
						case 0:
							{
								selectionVec.pop_back();
								Root = selectionVec.back();
							}
							break;
						case 1:
						case 2:
						case 3:
							{
								std::vector<char>::iterator iter = selectionVec.end() - 2;
								// std::cout << (int)*iter << std::endl;
								if (*iter == 0)
								{
									// std::cout << arch[savingbuttons.click].year << ", " << arch[savingbuttons.click].month << std::endl;
									SaveMap(&Background, &Player, &arch[savingbuttons.click]);
									tDT[savingbuttons.click].UpdateWord(GetTime(&arch[savingbuttons.click]));
									aDate[savingbuttons.click].Pop();
									aDate[savingbuttons.click].Compose(&tDT[savingbuttons.click]);
									FILE* ftmp = fopen("../log/tmp", "wb+");
									fwrite(arch, sizeof(arch), 5, ftmp);
									fclose(ftmp);
									fclose(flog);
									remove("../log/log");
									rename("../log/tmp", "../log/log");
									flog = fopen("../log/log", "rb+");
									
									Player.home_cx = Player.cx;
									Player.home_cy = Player.cy;
								}
								else
								{
									if (arch[savingbuttons.click].year == 0)
										break;
									LoadMap(&Background, &Player, &arch[savingbuttons.click]);
									Trees.LoadInScen(1);
									Ends.LoadInScen2(3);
									SightMode = -1;
									Root = 1;
									selectionVec.pop_back();
									selectionVec.push_back(Root);
								}
							}
							break;
						}
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						{
							selectionVec.pop_back();
							Root = selectionVec.back();
						}
						break;
					}
					break;
				}
			}
			break; // Root case 2: Archives
		
		case 3:
			{
				MapMenu.Update();
				w.Present();
				
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						mapmenubuttons.Click(event.motion.x, event.motion.y);
						// std::cout << event.motion.x << ", " << event.motion.y << ": " << mapmenubuttons.click << std::endl;
						switch (mapmenubuttons.click)
						{
						case 0:
							{
								selectionVec.pop_back();
								Root = selectionVec.back();
							}
							break;
						case 1:
						case 2:
						case 3:
							{
								LoadMap(&Background, &Player, &sysmap[mapmenubuttons.click - 1]);
								Trees.LoadInScen(1);
								Ends.LoadInScen2(3);
								SightMode = -1;
								Player.win = false;
								Root = 1;
								selectionVec.push_back(Root);
							}
							break;
						case 5:
							{
								Root = 4;
								selectionVec.push_back(Root);
							}
						}
					}
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						{
							selectionVec.pop_back();
							Root = selectionVec.back();
						}
						break;
					}
					break;
				}
			}
			break; // Root case 3: Map Loading
		
		case 4:
			{
				Greens.LoadInScen2(1);
				MTrees.LoadInScen(2);
				MEnds.LoadInScen2(3);
				Newmap.SlowSynXY();
				Greens.SynXY();
				MTrees.SynXY();
				MEnds.SynXY();
				MapMaking.Update();
				w.Present();
				
				int premouse_mx = (premouse_x + Newmap.sx) / ScenCell;
				int premouse_my = (premouse_y + Newmap.sy) / ScenCell;
				// int nowmouse_mx = (nowmouse_x + Newmap.sx) / ScenCell;
				// int nowmouse_my = (nowmouse_y + Newmap.sy) / ScenCell;
				bool lock = false;
				bool lock2 = false;
				
				{
					if (state[ SDL_SCANCODE_LEFT ] || state[ SDL_SCANCODE_A ])
						Newmap.Move(-1, 0);
					if (state[ SDL_SCANCODE_RIGHT ] || state[ SDL_SCANCODE_D ])
						Newmap.Move(1, 0);
					if (state[ SDL_SCANCODE_UP ] || state[ SDL_SCANCODE_W ])
						Newmap.Move(0, -1);
					if (state[ SDL_SCANCODE_DOWN ] || state[ SDL_SCANCODE_S ])
						Newmap.Move(0, 1);
				}
				
				{
					if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						SDL_GetMouseState(&nowmouse_x, &nowmouse_y);
						int nowmouse_mx = (nowmouse_x + Newmap.sx) / ScenCell;
						int nowmouse_my = (nowmouse_y + Newmap.sy) / ScenCell;
						if (lock2 == false && premouse_mx == nowmouse_mx && premouse_my == nowmouse_my)
						{
							;
						}
						else
						{
							Newmap.material[nowmouse_mx * Radix + nowmouse_my] = 1;
							lock2 = true;
						}
					}
				}
				
				{
					if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
					{
						SDL_GetMouseState(&nowmouse_x, &nowmouse_y);
						int nowmouse_mx = (nowmouse_x + Newmap.sx) / ScenCell;
						int nowmouse_my = (nowmouse_y + Newmap.sy) / ScenCell;
						Newmap.material[nowmouse_mx * Radix + nowmouse_my] = 0;
					}
				}
				
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						mapmakingbuttons.Click(event.motion.x, event.motion.y);
						// std::cout << event.motion.x << ", " << event.motion.y << std::endl;
						switch (mapmakingbuttons.click)
						{
						case 0:
							{
								Newmap.FindBE();
								Archive newmapArch;
								SaveMap(&Newmap, &newmapArch);
								std::string name = "../map/newmap_" + GetTimeNoColon(&newmapArch);
								FILE* fnew = fopen(name.c_str(), "wb+");
								fwrite(&newmapArch, sizeof(newmapArch), 1, fnew);
								fclose(fnew);
							}
							break;
						case 1:
							{
								selectionVec.pop_back();
								Root = selectionVec.back();
							}
							break;
						case 2:
							{
								Archive newmapArch;
								FILE* fnew = fopen("../map/save", "rb+");
								fread(&newmapArch, sizeof(newmapArch), 1, fnew);
								fclose(fnew);
								LoadMap(&Newmap, &newmapArch);
							}
							break;
						default:
							{
								if (lock) break;
								premouse_x = event.motion.x;
								premouse_y = event.motion.y;
								Newmap.AddMaterial(event.motion.x, event.motion.y);
								lock = true;
								lock2 = false;
							}
							break;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					{
						lock = false;
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						{
							selectionVec.pop_back();
							Root = selectionVec.back();
						}
						break;
					}
					break;
				}
			}
			break; // Root case 4: Map Making
		
		/*
		case 5:
			{
				WinMenu.Update();
				w.Present();
				
				if (SDL_PollEvent(&event))
				switch (event.type)
				{
				case SDL_QUIT:
					Quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					{
						winmenubuttons.Click(event.motion.x, event.motion.y);
						// std::cout << event.motion.x << ", " << event.motion.y << std::endl;
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						{
							selectionVec.pop_back();
							Root = selectionVec.back();
						}
						break;
					}
					break;
				}
			}
			break; // Root case 5: Winner
		*/
		default:
			{
				Root = -1;
			}
			break; // Root case others: Wrong Root
		
		} // end of switch Root
		
		Delay(preTime, postTime);
	
	} // end of while
	
	
	// automaticly save (OvO)
	SaveMap(&Background, &Player, &arch[0]);
	FILE* ftmp = fopen("../log/tmp", "wb+");
	fwrite(arch, sizeof(arch), 5, ftmp);
	fclose(ftmp);
	fclose(flog);
	remove("../log/log");
	rename("../log/tmp", "../log/log");
	
	return;
}

void Delay(int& preTime, int& postTime)
{
	postTime = SDL_GetTicks();
	if (postTime - preTime <= 1000 / FPS)
		SDL_Delay(1000 / FPS - postTime + preTime);
	preTime = SDL_GetTicks();
	return;
}

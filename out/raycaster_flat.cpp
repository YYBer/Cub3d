//TODO: convert to c not cpp
//TODO: convert to use cc not g++
//TODO: use MLX42 not quickcg
//TODO: include world map in main struct
//TODO: where do w and h come from?
//TODO: how to handle RGB colours?
// covert below to use .c, and cc?
// g++ raycaster_flat.cpp quickcg/quickcg.cpp -Iquickcg -lSDL -O3 -W -Wall -ansi -pedantic

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define MAPWIDTH 24
#define MAPHEIGHT 24
#define SQRS_PER_SEC 5.0
#define RADS_PER_SEC 3.0

struct Point2Dd {
	double x;
	double y;
};

struct Point2Di {
	int x;
	int y;
};

struct Main {
	Point2Dd pos; // start position:	
	Point2Dd dir; // initial direction vector:
	Point2Dd plane; // 2d raycaster version of camera plane:
	Point2Dd raydr;
	Point2Dd sideDist;
	Point2Dd deltaDist;
	Point2Di map;
	Point2Di step; //what direction to step in x or y-direction (either +1 or -1)
	double moveSpeed;
	double rotSpeed;
};

int worldMap[MAPWIDTH][MAPHEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	init_m(Main *m)
{
	m->pos.x = 22;
	m->pos.y = 12;
	m->dir.x = -1;
	m->dir.y = 0;
	m->plane.x = 0;
	m->plane.y = 0.66;
}

Point2Dd	calcRaydr(int x, int w, Point2Dd raydr, Point2Dd dir, Point2Dd plane)
{
	double cameraX; //x-coordinate in camera space

	cameraX = 2 * x / (double)w - 1;
	raydr.x = dir.x + plane.x * cameraX;
	raydr.y = dir.y + plane.y * cameraX;
	return (raydr);
}

Point2Dd calcDeltaDist(Point2Dd deltaDist, Point2Dd raydr)
{
	if (raydr.x == 0)
		deltaDist.x = 1e30;
	else
		deltaDist.x = std::abs(1 / raydr.x);
	if (raydr.y == 0)
		deltaDist.y = 1e30;
	else
		deltaDist.y = std::abs(1 / raydr.y);
	return (deltaDist);
}

//calculate step and initial sideDist
void	calcStepAndSideDist(Main *m)
{
	if(m->raydr.x < 0)
	{
		m->step.x = -1;
		m->sideDist.x = (m->pos.x - m->map.x) * m->deltaDist.x;
	}
	else
	{
		m->step.x = 1;
		m->sideDist.x = (m->map.x + 1.0 - m->pos.x) * m->deltaDist.x;
	}
	if(m->raydr.y < 0)
	{
		m->step.y = -1;
		m->sideDist.y = (m->pos.y - m->map.y) * m->deltaDist.y;
	}
	else
	{
		m->step.y = 1;
		m->sideDist.y = (m->map.y + 1.0 - m->pos.y) * m->deltaDist.y;
	}
}

int	performDDA(Main *m, int worldMap[MAPWIDTH][MAPHEIGHT])
{
	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	hit = 0;
	while(hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if(m->sideDist.x < m->sideDist.y)
		{
			m->sideDist.x += m->deltaDist.x;
			m->map.x += m->step.x;
			side = 0;
		}
		else
		{
			m->sideDist.y += m->deltaDist.y;
			m->map.y += m->step.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if(worldMap[m->map.x][m->map.y] > 0)
			hit = 1;
	}
	return (side);
}

ColorRGB	getWallColor(int worldMap[MAPWIDTH][MAPHEIGHT], Point2Di map)
{
	ColorRGB color;
	int mapValue;
	
	mapValue = worldMap[map.x][map.y];
	if (mapValue == 1)
		color = RGB_Red;
	else if (mapValue == 2)
		color = RGB_Green;
	else if (mapValue == 3)
		color = RGB_Blue;
	else if (mapValue == 4)
		color = RGB_White;
	else
		color = RGB_Yellow;
	return (color);
}

void drawVerLine(int h, int x, int side, double perpWallDist, int worldMap[MAPWIDTH][MAPHEIGHT], Point2Di map)
{
	//Calculate height of line to draw on screen
	int lineHeight;
	int drawStart;
	int drawEnd;
	ColorRGB color;

	printf("%f\n", perpWallDist);
	lineHeight = (int)(SCREENHEIGHT / perpWallDist);
	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
	if(drawStart < 0) drawStart = 0;
	drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
	if(drawEnd >= SCREENHEIGHT) drawEnd = SCREENHEIGHT - 1;
	// get wall colour
	color = getWallColor(worldMap, map);
	//give x and y sides different brightness
	if(side == 1) {color = color / 2;}
	//draw the pixels of the stripe as a vertical line
	verLine(x, drawStart, drawEnd, color);
}

double getPerpWallDist(int side, Point2Dd sideDist, Point2Dd deltaDist)
{
	if(side == 0)
	  	return(sideDist.x - deltaDist.x);
	return(sideDist.y - deltaDist.y);
}

void	castRays(Main *m)
{
	for(int x = 0; x < w; x++)
	{
		int side;
		//calculate ray position and direction
		//length of ray from current position to next x or y-side:
		m->raydr = calcRaydr(x, w, m->raydr, m->dir, m->plane);
		m->map.x = int(m->pos.x);
		m->map.y = int(m->pos.y);
		m->deltaDist = calcDeltaDist(m->deltaDist, m->raydr);
		calcStepAndSideDist(m);
		side = performDDA(m, worldMap);
		drawVerLine(h, x, side, getPerpWallDist(side, m->sideDist, m->deltaDist), worldMap, m->map);
	}
}

//move forward if no wall in front of you
void	keyDownUp(Main *m)
{
	if(keyDown(SDLK_UP))
	{
		if(worldMap[int(m->pos.x + m->dir.x * m->moveSpeed)][int(m->pos.y)] == false) m->pos.x += m->dir.x * m->moveSpeed;
		if(worldMap[int(m->pos.x)][int(m->pos.y + m->dir.y * m->moveSpeed)] == false) m->pos.y += m->dir.y * m->moveSpeed;
	}
}

//move backwards if no wall behind you
void	keyDownDown(Main *m)
{
	if(keyDown(SDLK_DOWN))
	{
		if(worldMap[int(m->pos.x - m->dir.x * m->moveSpeed)][int(m->pos.y)] == false) m->pos.x -= m->dir.x * m->moveSpeed;
		if(worldMap[int(m->pos.x)][int(m->pos.y - m->dir.y * m->moveSpeed)] == false) m->pos.y -= m->dir.y * m->moveSpeed;
	}
}

//rotate to the right
void	keyDownRight(Main *m)
{
	if(keyDown(SDLK_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		double olddirX = m->dir.x;
		m->dir.x = m->dir.x * cos(-m->rotSpeed) - m->dir.y * sin(-m->rotSpeed);
		m->dir.y = olddirX * sin(-m->rotSpeed) + m->dir.y * cos(-m->rotSpeed);
		double oldplaneX = m->plane.x;
		m->plane.x = m->plane.x * cos(-m->rotSpeed) - m->plane.y * sin(-m->rotSpeed);
		m->plane.y = oldplaneX * sin(-m->rotSpeed) + m->plane.y * cos(-m->rotSpeed);
	}
}

//rotate to the left
void	keyDownLeft(Main *m)
{
	if(keyDown(SDLK_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double olddirX = m->dir.x;
		m->dir.x = m->dir.x * cos(m->rotSpeed) - m->dir.y * sin(m->rotSpeed);
		m->dir.y = olddirX * sin(m->rotSpeed) + m->dir.y * cos(m->rotSpeed);
		double oldplaneX = m->plane.x;
		m->plane.x = m->plane.x * cos(m->rotSpeed) - m->plane.y * sin(m->rotSpeed);
		m->plane.y = oldplaneX * sin(m->rotSpeed) + m->plane.y * cos(m->rotSpeed);
	}
}


int main()
{
	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	Main m;
	init_m(&m);
	screen(SCREENWIDTH, SCREENHEIGHT, 0, "Raycaster");
	while(!done())
	{
		double frameTime;
		castRays(&m);
		//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / frameTime); //FPS counter
		redraw();
		cls();
		m.moveSpeed = frameTime * SQRS_PER_SEC; 
		m.rotSpeed = frameTime * RADS_PER_SEC;	
		readKeys();
		keyDownUp(&m);
		keyDownDown(&m);
		keyDownRight(&m);
		keyDownLeft(&m);
	}
}

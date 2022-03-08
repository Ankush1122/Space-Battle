//#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>

struct spaceship
{
	double x;
	double y;
	double speed;
	double speed2;
} redshipdown = {-0.5, -0.7, 0, 0}, redshipup = {0.45, -0.074, 0, 0},
  greenshipdown = {0.45, -0.7, 0, 0}, greenshipup = {-0.5, -0.074, 0, 0};

struct explosion
{
	double x;
	double y;
	int unity;
	double bomb;
	int time;
	int number;
} exploredup = {-1.5, -1.5, 0, 0.02, 0, 0}, exploreddown = {-1.5, -1.5, 0, 0.02, 0, 0}, explogreenup = {1.5, 1.5, 0, 0.02, 0, 0},
  explogreendown = {1.5, 1.5, 0, 0.02, 0, 0};

struct Asteroid
{
	double x;
	double y;
	char xdire;
	char ydire;
	double xspeed;
	double yspeed;
	int astromove;
} Astro1 = {-0.89, 0.88, 'r', 'u', 0.0008, 0.0007, 0}, Astro2 = {0.89, -0.88,
																 'l', 'u', 0.0008, 0.0007, 0};

#define firespeed 0.06
#define AMMO 1000
#define AMMO2 1000

long int showpower1 = 100, showpower2 = 100, i, j, k, numoffire = 0,
		 numoffire2 = 0, visibility[AMMO], visibility2[AMMO2], page = 0,
		 button1 = 0, button2 = 0, var = 100, Strike1 = 0, Strike2 = 0;
double x1fire[AMMO], y1fire[AMMO], x2fire[AMMO], y2fire[AMMO], xup[AMMO2],
	yup[AMMO2], xdown[AMMO2], ydown[AMMO2], translatepower = 0.12, power1 = 0.4, power2 = 0.4, r1 = 1.0, r2 = 0.0, r3 = 0.0, g1 = 0.0, g2 = 1.0, g3 = 0.0;

void printstring(char string[], int stringlen, double stringx, double stringy,
				 int size)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(stringx, stringy, 0);
	glScaled(0.00001 * size, 0.00001 * size, 0.00001 * size);
	for (i = 0; i < stringlen; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, string[i]);
	}
}

void Display()
{
	if (Astro1.x <= 0.008)
	{
		Astro1.xspeed = Astro1.xspeed + 0.000001;
		Astro1.yspeed = Astro1.yspeed + 0.000001;
		Astro2.xspeed = Astro2.xspeed + 0.000001;
		Astro2.yspeed = Astro2.yspeed + 0.000001;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (page == 0)
	{
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex2d(-1.0, 0.5);
		glVertex2d(1.0, 0.5);
		glEnd();
		glColor3d(0.0, 1.0, 0.0);
		printstring("SPACE BATTLE DELUXE", 19, -0.95, 0.8, 120);
		glColor3d(1.0, 0.0, 0.0);
		printstring("Two Player", 10, -0.45, 0.55, 150);
		glColor3d(0.0, 1.0, 1.0);
		printstring(" Developer : Ankush Deshmukh", strlen(" Developer : Ankush Deshmukh"), -1.0, 0.4, 60);
		printstring(" Producer : Ankush Deshmukh", strlen(" Producer : Ankush Deshmukh"), -1.0, 0.2, 60);
		printstring("Version : 1.2", 13, -0.93, 0.0, 60);
		printstring("Special Things : 1)Two Player", 29, -0.93, -0.2, 60);
		printstring("2)Hideable Spaceships", 21, -0.25, -0.4, 60);
		printstring("3)Asteroids", 11, -0.25, -0.6, 60);
		printstring("Now Press Enter to skip page.", 24, -0.93, -0.8, 60);
	}
	if (page == 1)
	{
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex2d(-1.0, 0.7);
		glVertex2d(1.0, 0.7);
		glEnd();
		glBegin(GL_LINES);
		glVertex2d(0.0, 0.7);
		glVertex2d(0.0, -1.0);
		glEnd();
		glBegin(GL_LINES);
		glVertex2d(-1.0, 0.5);
		glVertex2d(1.0, 0.5);
		glEnd();
		glColor3d(0.0, 1.0, 0.0);
		printstring("Controls", 8, -0.47, 0.75, 200);
		glColor3d(0.0, 1.0, 1.0);
		printstring("One Player", 10, -0.95, 0.55, 130);
		printstring("Two Player", 10, 0.05, 0.55, 130);
		printstring("1)W:Front", 9, -0.8, 0.35, 80);
		printstring("2)S:Back", 8, -0.8, 0.15, 80);
		printstring("3)A:Left", 8, -0.8, -0.05, 80);
		printstring("4)D:Right", 9, -0.8, -0.25, 80);
		printstring("5)Space:Fire", 12, -0.8, -0.45, 80);
		printstring("6)Z:Hide Mode", 13, -0.8, -0.65, 80);
		printstring("(On/Off)", 8, -0.65, -0.8, 80);
		printstring("[Only work when you in Hide Zone]", 33, -0.96, -0.95, 40);
		printstring("1)Up Arrow:Front", 16, 0.03, 0.35, 80);
		printstring("2)Down Arrow:Back", 17, 0.03, 0.15, 80);
		printstring("3)Left Arrow:Left", 17, 0.03, -0.05, 80);
		printstring("4)Right Arrow:Back", 18, 0.03, -0.25, 80);
		printstring("5)Enter:Fire", 12, 0.03, -0.45, 80);
		printstring("6)5(Numpad):Hide Mode", 17, 0.03, -0.65, 80);
		printstring("(On/Off)", 8, 0.3, -0.8, 80);
		printstring("[Only work when you in Hide Zone]", 33, 0.04, -0.95, 40);
	}
	if (page == 2)
	{
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(4.0);
		glBegin(GL_LINES);
		glVertex2d(-1.0, 0.7);
		glVertex2d(1.0, 0.7);
		glEnd();
		glColor3d(0.0, 1.0, 0.0);
		printstring("Help", 4, -0.3, 0.78, 200);
		glColor3d(0.0, 1.0, 1.0);
		printstring("1)Using controls defeat the another player.", 43, -1.0,
					0.5, 70);
		printstring("2)Their is hide zone in battle area.", 36, -1.0, 0.3, 70);
		printstring("3)Using this hide zone you can beat your", 40, -1.0, 0.1,
					70);
		printstring("opponent.", 9, -0.91, -0.1, 70);
		printstring("4)After some time this zone will be invisible.", 46, -1.0,
					-0.3, 60);
		printstring("5)If Asteroid may strike you,your spaceship will be", 52,
					-1.0, -0.5, 60);
		printstring("destroy.", 8, -0.91, -0.7, 70);
		glColor3d(1.0, 0.0, 0.0);
		printstring("Now Press Enter to play game.", 29, -0.91, -0.9, 70);
	}
	if (page == 3)
	{
		if (power1 <= -0.6 || Strike1 == 1)
		{
			if (exploredup.unity == 0)
			{
				exploredup.x = redshipup.x;
				exploredup.y = redshipup.y;
				exploredup.unity = 1;
			}
			glLoadIdentity();
			glTranslated(exploredup.x, exploredup.y + 0.7, 0);
			glColor3d(1.0, 0.0, 0.0);
			if (exploredup.bomb <= 0.2 && exploredup.time < 10)
			{
				exploredup.bomb = exploredup.bomb + 0.007;
			}
			if (exploredup.bomb >= 0.19 || exploredup.number == 1)
			{
				exploredup.bomb = exploredup.bomb - 0.14;
				exploredup.time++;
				exploredup.number = 1;
			}
			redshipup.x = 100;
			glutSolidSphere(exploredup.bomb, 100, 100);
			glLoadIdentity();
			glColor3d(0.0, 1.0, 0.0);
			if (exploreddown.unity == 0)
			{
				exploreddown.x = redshipdown.x;
				exploreddown.y = redshipdown.y;
				exploreddown.unity = 1;
			}
			glLoadIdentity();
			glTranslated(exploreddown.x, exploreddown.y + 0.1, 0);
			glColor3d(1.0, 0.0, 0.0);
			if (exploreddown.bomb <= 0.2 && exploreddown.time < 10)
			{
				exploreddown.bomb = exploreddown.bomb + 0.007;
			}
			if (exploreddown.bomb >= 0.19 || exploreddown.number == 1)
			{
				exploreddown.bomb = exploreddown.bomb - 0.14;
				exploreddown.time++;
				exploreddown.number = 1;
			}
			redshipdown.x = 100;
			glutSolidSphere(exploreddown.bomb, 100, 100);
			glLoadIdentity();
			glColor3d(0.0, 1.0, 0.0);
			printstring("Green Spaceship Win", 19, -0.7, 0.0, 100);
			Astro1.astromove = 0;
			Astro2.astromove = 0;
		}
		if (power2 <= -0.6 || Strike2 == 1)
		{
			glColor3d(0.0, 1.0, 0.0);
			if (explogreenup.unity == 0)
			{
				explogreenup.x = greenshipup.x;
				explogreenup.y = greenshipup.y;
				explogreenup.unity = 1;
			}
			glLoadIdentity();
			glTranslated(explogreenup.x, explogreenup.y + 0.7, 0);
			glColor3d(0.0, 1.0, 0.0);
			if (explogreenup.bomb <= 0.2 && explogreenup.time < 10)
			{
				explogreenup.bomb = explogreenup.bomb + 0.007;
			}
			if (explogreenup.bomb >= 0.19 || explogreenup.number == 1)
			{
				explogreenup.bomb = explogreenup.bomb - 0.14;
				explogreenup.time++;
				explogreenup.number = 1;
			}
			greenshipup.x = 100;
			glutSolidSphere(explogreenup.bomb, 100, 100);
			glLoadIdentity();
			glColor3d(0.0, 1.0, 0.0);
			if (explogreendown.unity == 0)
			{
				explogreendown.x = greenshipdown.x;
				explogreendown.y = greenshipdown.y;
				explogreendown.unity = 1;
			}
			glLoadIdentity();
			glTranslated(explogreendown.x, explogreendown.y + 0.1, 0);
			glColor3d(0.0, 1.0, 0.0);
			if (explogreendown.bomb <= 0.2 && explogreendown.time < 10)
			{
				explogreendown.bomb = explogreendown.bomb + 0.007;
			}
			if (explogreendown.bomb >= 0.19 || explogreendown.number == 1)
			{
				explogreendown.bomb = explogreendown.bomb - 0.14;
				explogreendown.time++;
				explogreendown.number = 1;
			}
			greenshipdown.x = 100;
			glutSolidSphere(explogreendown.bomb, 100, 100);
			glLoadIdentity();
			glColor3d(1.0, 0.0, 0.0);
			printstring("Red Spaceship Win", 17, -0.6, 0.0, 100);
			Astro1.astromove = 0;
			Astro2.astromove = 0;
		}
		for (i = 0; i < AMMO; i++)
		{
			if (visibility[i] == 1)
			{
				if (greenshipup.x + 0.08 >= x1fire[i] && greenshipup.x - 0.08 <= x1fire[i] && greenshipup.y + 0.2 >= y1fire[i] && greenshipup.y - 0.0001 <= y1fire[i])
				{
					if (power2 >= -0.6)
					{
						power2 = power2 - 0.001;
					}
				}
				glLoadIdentity();
				glColor3d((double)236 / 255, (double)10 / 255,
						  (double)10 / 255);
				glTranslated(x1fire[i] + 0.02, y1fire[i] + 0.09, 0);
				glutSolidSphere(0.01, 10, 10);
			}
		}
		for (i = 0; i < AMMO; i++)
		{
			if (visibility[i] == 1)
			{
				glLoadIdentity();
				glColor3d((double)236 / 255, (double)10 / 255,
						  (double)10 / 255);
				glTranslated(x2fire[i] + 0.02, y2fire[i] + 0.67, 0);
				glutSolidSphere(0.01, 10, 10);
			}
		}
		for (i = 0; i < AMMO2; i++)
		{
			if (visibility2[i] == 1)
			{
				if (redshipup.x + 0.08 >= xdown[i] && redshipup.x - 0.08 <= xdown[i] && redshipup.y + 0.2 >= ydown[i] && redshipup.y - 0.0001 <= ydown[i])
					if (power1 >= -0.6)
					{
						power1 = power1 - 0.001;
					}
				glLoadIdentity();
				glColor3d((double)68 / 255, (double)235 / 255,
						  (double)119 / 255);
				glTranslated(xdown[i] + 0.02, ydown[i] + 0.09, 0);
				glutSolidSphere(0.01, 10, 10);
			}
		}
		for (i = 0; i < AMMO2; i++)
		{
			if (visibility2[i] == 1)
			{
				glLoadIdentity();
				glColor3d((double)68 / 255, (double)235 / 255,
						  (double)119 / 255);
				glTranslated(xup[i] + 0.02, yup[i] + 0.67, 0);
				glutSolidSphere(0.01, 10, 10);
			}
		};
		var--;
		if (var > 0)
		{
			// hidered1
			glLoadIdentity();
			glColor3d(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex2d(-1.0, -0.73);
			glVertex2d(0.0, -0.73);
			glVertex2d(0.0, -1.1);
			glVertex2d(-1.0, -1.1);
			glEnd();
			// hidered2
			glLoadIdentity();
			glColor3d(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex2d(1.0, 0.73);
			glVertex2d(0.0, 0.73);
			glVertex2d(0.0, 1.1);
			glVertex2d(1.0, 1.1);
			glEnd();
			// hidegreen1
			glLoadIdentity();
			glColor3d(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex2d(1.0, -0.73);
			glVertex2d(0.0, -0.73);
			glVertex2d(0.0, -1.1);
			glVertex2d(1.0, -1.1);
			glEnd();
			// hidegreen2
			glLoadIdentity();
			glColor3d(0.0, 1.0, 0.0);
			glBegin(GL_POLYGON);
			glVertex2d(-1.0, 0.73);
			glVertex2d(0.0, 0.73);
			glVertex2d(0.0, 1.1);
			glVertex2d(-1.0, 1.1);
			glEnd();
		}
		// 1power
		glLoadIdentity();
		glTranslated(-0.9, translatepower, 0.0);
		glBegin(GL_POLYGON);
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(-0.1, power1);
		glVertex2d(0.1, power1);
		glColor3d(0.274509804, 0.08627451, 0.08627451);
		glVertex2d(0.1, -0.6);
		glVertex2d(-0.1, -0.6);
		glEnd();
		// 2power
		glLoadIdentity();
		glTranslated(0.9, translatepower, 0.0);
		glBegin(GL_POLYGON);
		glColor3d(0.0, 1.0, 0.0);
		glVertex2d(-0.1, power2);
		glVertex2d(0.1, power2);
		glColor3d(0.117647059, 0.274509804, 0.08627451);
		glVertex2d(0.1, -0.6);
		glVertex2d(-0.1, -0.6);
		glEnd();
		// border1
		glLoadIdentity();
		glTranslated(-0.9, 0.12, 0.0);
		glBegin(GL_LINES);
		glColor3d(0.0, 1.0, 0.0);
		glVertex2d(-0.1, 0.4);
		glVertex2d(0.1, 0.4);
		glVertex2d(0.1, 0.4);
		glVertex2d(0.1, -0.6);
		glVertex2d(0.1, -0.6);
		glVertex2d(-0.1, -0.6);
		glVertex2d(-0.096, -0.6);
		glVertex2d(-0.096, 0.4);
		glEnd();
		// border2
		glLoadIdentity();
		glTranslated(0.9, 0.12, 0.0);
		glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(-0.1, 0.4);
		glVertex2d(0.1, 0.4);
		glVertex2d(0.096, 0.4);
		glVertex2d(0.096, -0.6);
		glVertex2d(0.1, -0.6);
		glVertex2d(-0.1, -0.6);
		glVertex2d(-0.1, -0.6);
		glVertex2d(-0.1, 0.4);
		glEnd();
		// midline
		glLoadIdentity();
		glLineWidth(5.0);
		glBegin(GL_LINES);
		glColor3d(1.0, 1.0, 1.0);
		glVertex2d(0.0, 1.0);
		glColor3d(0.0, 0.0, 0.0);
		glVertex2d(0.0, -1.0);
		glEnd();
		// redshipdown
		glLoadIdentity();
		glTranslated(redshipdown.x, redshipdown.y, 0.0);
		glColor3d(r1, r2, r3);
		glBegin(GL_POLYGON);
		glVertex2d(-0.04, 0.025);
		glVertex2d(-0.04, -0.025);
		glVertex2d(0.09, -0.025);
		glVertex2d(0.09, 0.025);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2d(0.02, 0.20);
		glVertex2d(-0.01, 0.0);
		glVertex2d(0.06, 0.0);
		glEnd();
		// greenshipdown
		glLoadIdentity();
		glTranslated(greenshipdown.x, greenshipdown.y, 0.0);
		glColor3d(g1, g2, g3);
		glBegin(GL_POLYGON);
		glVertex2d(-0.04, 0.025);
		glVertex2d(-0.04, -0.025);
		glVertex2d(0.09, -0.025);
		glVertex2d(0.09, 0.025);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2d(0.02, 0.20);
		glVertex2d(-0.01, 0.0);
		glVertex2d(0.06, 0.0);
		glEnd();
		// redshipup
		glLoadIdentity();
		glTranslated(redshipup.x, redshipup.y, 0.0);
		glBegin(GL_POLYGON);
		glColor3d(1.0f, 0.0f, 0.0f);
		glVertex2d(-0.04, 0.8);
		glVertex2d(-0.04, 0.75);
		glVertex2d(0.09, 0.75);
		glVertex2d(0.09, 0.8);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2d(0.02, 0.55);
		glVertex2d(-0.01, 0.8);
		glVertex2d(0.06, 0.8);
		glEnd();
		// greenshipup
		glLoadIdentity();
		glTranslated(greenshipup.x, greenshipup.y, 0.0);
		glBegin(GL_POLYGON);
		glColor3d(0.0f, 1.0f, 0.0f);
		glVertex2d(-0.04, 0.8);
		glVertex2d(-0.04, 0.75);
		glVertex2d(0.09, 0.75);
		glVertex2d(0.09, 0.8);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2d(0.02, 0.55);
		glVertex2d(-0.01, 0.8);
		glVertex2d(0.06, 0.8);
		glEnd();
		// print
		glColor3d(1.0, 0.0, 0.0);
		printstring("RED", 3, -0.999, 0.6, 80);
		glColor3d(0.0, 1.0, 0.0);
		printstring("GREEN", 5, 0.783, 0.6, 50);
		// astro1
		glLoadIdentity();
		glTranslated(Astro1.x, Astro1.y, 0.0);
		glColor3d(1.0, 0.0, 0.0);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glLoadIdentity();
		glTranslated(Astro2.x, Astro2.y, 0.0);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		glutWireSphere(0.1, 12, 12);
		if (var == 0)
		{
			Astro1.astromove = 1;
		}
		if (var == 0)
		{
			Astro2.astromove = 1;
		}
		// r-right, l-left, u-up, d-down
		if (Astro1.astromove == 1)
		{
			if (Astro1.xdire == 'r')
				Astro1.x = Astro1.x + Astro1.xspeed;
			else if (Astro1.xdire == 'l')
				Astro1.x = Astro1.x - Astro1.xspeed;
			if (Astro1.ydire == 'd')
				Astro1.y = Astro1.y - Astro1.yspeed;
			else if (Astro1.ydire == 'u')
				Astro1.y = Astro1.y + Astro1.yspeed;
			if (Astro1.x < -0.9)
				Astro1.xdire = 'r';
			else if (Astro1.x > -0.1)
				Astro1.xdire = 'l';
			if (Astro1.y > 0.9)
				Astro1.ydire = 'd';
			else if (Astro1.y < -0.9)
				Astro1.ydire = 'u';
		}
		if (Astro2.astromove == 1)
		{
			if (Astro2.xdire == 'r')
				Astro2.x = Astro2.x + Astro2.xspeed;
			else if (Astro2.xdire == 'l')
				Astro2.x = Astro2.x - Astro2.xspeed;
			if (Astro2.ydire == 'd')
				Astro2.y = Astro2.y - Astro2.yspeed;
			else if (Astro2.ydire == 'u')
				Astro2.y = Astro2.y + Astro2.yspeed;
			if (Astro2.x < 0.1)
				Astro2.xdire = 'r';
			else if (Astro2.x > 0.9)
				Astro2.xdire = 'l';
			if (Astro2.y > 0.9)
				Astro2.ydire = 'd';
			else if (Astro2.y < -0.9)
				Astro2.ydire = 'u';
		}
		if (redshipdown.x + 0.15 >= Astro1.x && redshipdown.x - 0.15 <= Astro1.x && redshipdown.y + 0.26 >= Astro1.y && redshipdown.y - 0.1 <= Astro1.y)
		{
			Strike1 = 1;
		}
		if (greenshipdown.x + 0.15 >= Astro2.x && greenshipdown.x - 0.15 <= Astro2.x && greenshipdown.y + 0.26 >= Astro2.y && greenshipdown.y - 0.1 <= Astro2.y)
		{
			Strike2 = 1;
		}
	}
	glutSwapBuffers();
}

void Timer(int Value)
{
	for (i = 0; i < AMMO; i++)
	{
		y1fire[i] += firespeed;
	}
	for (i = 0; i < AMMO; i++)
	{
		y2fire[i] -= firespeed;
	}
	for (i = 0; i < AMMO2; i++)
	{
		ydown[i] += firespeed;
	}
	for (i = 0; i < AMMO; i++)
	{
		yup[i] -= firespeed;
	}
	// redshipdown
	if (redshipdown.x < -0.96)
	{
		redshipdown.x = -0.96;
		redshipdown.speed = 0;
	}
	if (redshipdown.x > -0.1)
	{
		redshipdown.x = -0.1;
		redshipdown.speed = 0;
	}
	if (redshipdown.y > 0.8)
	{
		redshipdown.y = 0.8;
		redshipdown.speed2 = 0;
	}
	if (redshipdown.y < -0.98)
	{
		redshipdown.y = -0.98;
		redshipdown.speed2 = 0;
	}
	redshipdown.x = redshipdown.x + redshipdown.speed;
	redshipdown.y = redshipdown.y + redshipdown.speed2;
	if (redshipdown.speed >= 0.0004)
	{
		redshipdown.speed = redshipdown.speed - 0.002;
	}
	else if (redshipdown.speed <= (-0.0004))
	{
		redshipdown.speed = redshipdown.speed + 0.002;
	}
	else
		redshipdown.speed = 0;
	if (redshipdown.speed2 >= 0.0004)
	{
		redshipdown.speed2 = redshipdown.speed2 - 0.002;
	}
	else if (redshipdown.speed2 <= (-0.0004))
	{
		redshipdown.speed2 = redshipdown.speed2 + 0.002;
	}
	else
		redshipdown.speed2 = 0;
	// redshipup
	if (redshipup.x < 0.05)
	{
		redshipup.x = 0.05;
		redshipup.speed = 0;
	}
	if (redshipup.x > 0.91)
	{
		redshipup.x = 0.91;
		redshipup.speed = 0;
	}
	if (redshipup.y > 0.2)
	{
		redshipup.y = 0.2;
		redshipup.speed2 = 0;
	}
	if (redshipup.y < -1.55)
	{
		redshipup.y = -1.55;
		redshipup.speed2 = 0;
	}
	redshipup.x = redshipup.x + redshipup.speed;
	redshipup.y = redshipup.y + redshipup.speed2;
	if (redshipup.speed >= 0.0004)
	{
		redshipup.speed = redshipup.speed - 0.002;
	}
	else if (redshipup.speed <= (-0.0004))
	{
		redshipup.speed = redshipup.speed + 0.002;
	}
	else
		redshipup.speed = 0;
	if (redshipup.speed2 >= 0.0004)
	{
		redshipup.speed2 = redshipup.speed2 - 0.002;
	}
	else if (redshipup.speed2 <= (-0.0004))
	{
		redshipup.speed2 = redshipup.speed2 + 0.002;
	}
	else
		redshipup.speed2 = 0;
	// greenshipdown
	if (greenshipdown.x > 0.91)
	{
		greenshipdown.x = 0.91;
		greenshipdown.speed = 0;
	}
	if (greenshipdown.x < 0.05)
	{
		greenshipdown.x = 0.05;
		greenshipdown.speed = 0;
	}
	if (greenshipdown.y > 0.8)
	{
		greenshipdown.y = 0.8;
		greenshipdown.speed2 = 0;
	}
	if (greenshipdown.y < -0.98)
	{
		greenshipdown.y = -0.98;
		greenshipdown.speed2 = 0;
	}
	greenshipdown.x = greenshipdown.x + greenshipdown.speed;
	greenshipdown.y = greenshipdown.y + greenshipdown.speed2;
	if (greenshipdown.speed >= 0.0004)
	{
		greenshipdown.speed = greenshipdown.speed - 0.002;
	}
	else if (greenshipdown.speed <= (-0.0004))
	{
		greenshipdown.speed = greenshipdown.speed + 0.002;
	}
	else
		greenshipdown.speed = 0;
	if (greenshipdown.speed2 >= 0.0004)
	{
		greenshipdown.speed2 = greenshipdown.speed2 - 0.002;
	}
	else if (greenshipdown.speed2 <= (-0.0004))
	{
		greenshipdown.speed2 = greenshipdown.speed2 + 0.002;
	}
	else
		greenshipdown.speed2 = 0;
	// greenshipup
	if (greenshipup.x > -0.1)
	{
		greenshipup.x = -0.1;
		greenshipup.speed = 0;
	}
	if (greenshipup.x < -0.96)
	{
		greenshipup.x = -0.96;
		greenshipup.speed = 0;
	}
	if (greenshipup.y > 0.2)
	{
		greenshipup.y = 0.2;
		greenshipup.speed2 = 0;
	}
	if (greenshipup.y < -1.55)
	{
		greenshipup.y = -1.55;
		greenshipup.speed2 = 0;
	}
	greenshipup.x = greenshipup.x + greenshipup.speed;
	greenshipup.y = greenshipup.y + greenshipup.speed2;
	if (greenshipup.speed >= 0.0004)
	{
		greenshipup.speed = greenshipup.speed - 0.002;
	}
	else if (greenshipup.speed <= (-0.0004))
	{
		greenshipup.speed = greenshipup.speed + 0.002;
	}
	else
		greenshipup.speed = 0;
	if (greenshipup.speed2 >= 0.0004)
	{
		greenshipup.speed2 = greenshipup.speed2 - 0.002;
	}
	else if (greenshipup.speed2 <= (-0.0004))
	{
		greenshipup.speed2 = greenshipup.speed2 + 0.002;
	}
	else
		greenshipup.speed2 = 0;

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}

void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		greenshipdown.speed2 = greenshipdown.speed2 + 0.02;
		greenshipup.speed2 = greenshipup.speed2 - 0.02;
		break;
	case GLUT_KEY_DOWN:
		greenshipdown.speed2 = greenshipdown.speed2 - 0.02;
		greenshipup.speed2 = greenshipup.speed2 + 0.02;
		break;
	case GLUT_KEY_RIGHT:
		greenshipdown.speed = greenshipdown.speed + 0.02;
		greenshipup.speed = greenshipup.speed - 0.02;
		break;
	case GLUT_KEY_LEFT:
		greenshipdown.speed = greenshipdown.speed - 0.02;
		greenshipup.speed = greenshipup.speed + 0.02;
		break;
	}
}

void Keyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'z':
		if (button1 % 2 == 0)
		{
			r1 = 1.0;
			r2 = 1.0;
			r3 = 1.0;
			button1++;
			break;
		}
		if (button1 % 2 == 1)
		{
			r1 = 1.0;
			r2 = 0.0;
			r3 = 0.0;
			button1++;
			break;
		}
		break;
	case 53:
		if (button2 % 2 == 0)
		{
			g1 = 1.0;
			g2 = 1.0;
			g3 = 1.0;
			button2++;
			break;
		}
		if (button2 % 2 == 1)
		{
			g1 = 0.0;
			g2 = 1.0;
			g3 = 0.0;
			button2++;
			break;
		}
		break;
	case 32:
		x1fire[numoffire % AMMO] = redshipdown.x;
		y1fire[numoffire % AMMO] = redshipdown.y;
		x2fire[numoffire % AMMO] = redshipup.x;
		y2fire[numoffire % AMMO] = redshipup.y;
		visibility[numoffire % AMMO] = 1;
		numoffire++;
		break;
	case 27:
		exit(0);
	case 'w':
		redshipdown.speed2 = redshipdown.speed2 + 0.02;
		redshipup.speed2 = redshipup.speed2 - 0.02;
		break;
	case 's':
		redshipdown.speed2 = redshipdown.speed2 - 0.02;
		redshipup.speed2 = redshipup.speed2 + 0.02;
		break;
	case 'a':
		redshipdown.speed = redshipdown.speed - 0.02;
		redshipup.speed = redshipup.speed + 0.02;
		break;
	case 'd':
		redshipdown.speed = redshipdown.speed + 0.02;
		redshipup.speed = redshipup.speed - 0.02;
		break;
	case 13:
		if (page == 3)
		{
			xdown[numoffire2 % AMMO2] = greenshipdown.x;
			ydown[numoffire2 % AMMO2] = greenshipdown.y;
			xup[numoffire2 % AMMO2] = greenshipup.x;
			yup[numoffire2 % AMMO2] = greenshipup.y;
			visibility2[numoffire2 % AMMO2] = 1;
			numoffire2++;
		}
		if (page == 0)
		{
			page = 1;
			break;
		}
		if (page == 1)
		{
			page = 2;
			break;
		}
		if (page == 2)
		{
			page = 3;
		}
		break;
	}
}

int main(int argc, char **argv)
{
	for (j = 0; j < AMMO; j++)
	{
		visibility[j] = 0;
	}
	for (j = 0; j < AMMO; j++)
	{
		visibility[j] = 0;
	}
	for (k = 0; k < AMMO2; k++)
	{
		visibility2[k] = 0;
	}
	for (k = 0; k < AMMO2; k++)
	{
		visibility2[k] = 0;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(450, 150);
	glutCreateWindow("Space Battle Deluxe");
	glutFullScreen();
	glutDisplayFunc(Display);
	glutTimerFunc(0, Timer, 0);
	glutSpecialFunc(SpecialInput);
	glutKeyboardFunc(Keyboard);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glutMainLoop();
	return 0;
}

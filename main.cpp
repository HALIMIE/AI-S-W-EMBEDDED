#include "device_driver.h"

/*---------- DEFINE START ----------*/

#define LCDW (320)
#define LCDH (240)
#define X_MIN (0)
#define X_MAX (LCDW - 1)
#define Y_MIN (0)
#define Y_MAX (LCDH - 1)

#define TIMER_PERIOD (10)
#define RIGHT (1)
#define LEFT (-1)

#define CAR_STEP (5)
#define CAR_SIZE_X (20)
#define CAR_SIZE_Y (20)
#define FROG_STEP (10)
#define FROG_SIZE_X (20)
#define FROG_SIZE_Y (20)

#define BACK_COLOR (6)
#define FROG_COLOR (0)

#define GAME_OVER (1)

#define MAX_CAR 5

/*---------- DEFINE END ----------*/

/*---------- ENUM START ----------*/

enum BORDER
{
	LEFT_BORDER = 0,
	RIGHT_BORDER = 1,
	TOP_BORDER = 2,
	BOTTOM_BORDER = 3,
	NO_BORDER = -1
};

enum FROG_GOAL
{
	HOME,
	SCHOOL
};

/*---------- ENUM END ----------*/

/*---------- CLASS DECLARATION START ----------*/

class square;
class frog;
class car;

/*---------- CLASS DECLARATION END ----------*/

/*---------- FUNCTION DECLARATION START ----------*/

void lcdDrawChar(int x, int y, int num, unsigned short color, int scale);
void lcdDrawNumber(int x, int y, int number, unsigned short color, int scale);
int checkCollisionWithCars(frog *FUCKINGFROG, car *cars, int curCar);
void addCar();
static void Game_Init();
static int jogKeyHandler();
static int timerHandler();
static void Game_Over();

/*---------- FUNCTION DECLARATION END ----------*/

/*---------- GLOBAL VAR START ----------*/

static int score;
static unsigned short color[] = {RED, YELLOW, GREEN, BLUE, WHITE, VIOLET, BLACK};
static int curCar = 1;
volatile int i = 0;

extern volatile int TIM4_expired;
extern volatile int USART1_rx_ready;
extern volatile int USART1_rx_data;
extern volatile int Jog_key_in;
extern volatile int Jog_key;

const unsigned char font[10][5] = {
	{0b111, 0b101, 0b101, 0b101, 0b111}, // 0
	{0b010, 0b010, 0b010, 0b010, 0b010}, // 1
	{0b111, 0b001, 0b111, 0b100, 0b111}, // 2
	{0b111, 0b001, 0b111, 0b001, 0b111}, // 3
	{0b101, 0b101, 0b111, 0b001, 0b001}, // 4
	{0b111, 0b100, 0b111, 0b001, 0b111}, // 5
	{0b111, 0b100, 0b111, 0b101, 0b111}, // 6
	{0b111, 0b001, 0b001, 0b001, 0b001}, // 7
	{0b111, 0b101, 0b111, 0b101, 0b111}, // 8
	{0b111, 0b101, 0b111, 0b001, 0b111}	 // 9
};

/*---------- GLOBAL VAR END ----------*/

/*---------- CLASS START ----------*/

class square
{
protected:
	int x, y;
	int w, h;
	int ci;
	int dir;

public:
	square() {}
	void drawSquare();
	int checkCollision(square *obj);
	BORDER checkCollisionBorder();
};

class frog : public square
{
private:
	int goal;

public:
	frog() {}
	frog(int x, int y, int w, int h, int ci, int dir)
	{
		this->goal = SCHOOL;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->ci = ci;
		this->dir = dir;
	}
	void moveFrog(int Jog_key);
	void checkBorder();
};

class car : public square
{
public:
	car() {}
	car(int x, int y, int w, int h, int ci, int dir)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->ci = ci;
		this->dir = dir;
	}
	void moveCar();
};

// This should be here because it uses the class definition
frog FUCKINGFROG;
car cars[MAX_CAR];

/*---------- CLASS END ----------*/

/*---------- CLASS FUNCTION DEFINITION START ----------*/

// draw a square
void square::drawSquare()
{
	Lcd_Draw_Box(x, y, w, h, color[ci]);
}

// if two squares collide, return 1
int square::checkCollision(square *obj)
{
	if (x > obj->x + obj->w || obj->x > x + w)
		return 0;
	if (y > obj->y + obj->h || obj->y > y + h)
		return 0;
	return 1;
}

// if the square collides with the border, return BORDER
// otherwise, return -1
BORDER square::checkCollisionBorder()
{
	if (this->x <= X_MIN)
		return LEFT_BORDER;
	if (this->x + this->w >= X_MAX)
		return RIGHT_BORDER;
	if (this->y <= Y_MIN)
		return TOP_BORDER;
	if (this->y + this->h >= Y_MAX)
		return BOTTOM_BORDER;
	return NO_BORDER;
}

// move the frog according to the Jog_key
void frog::moveFrog(int Jog_key)
{
	int temp = this->ci;
	this->ci = BACK_COLOR;
	this->drawSquare();
	switch (Jog_key)
	{
	case 0:
		if (this->y > Y_MIN)
			this->y -= FROG_STEP;
		break;
	case 1:
		if (this->y + this->h < Y_MAX)
			this->y += FROG_STEP;
		break;
	case 2:
		if (this->x > X_MIN)
			this->x -= FROG_STEP;
		break;
	case 3:
		if (this->x + this->w < X_MAX)
			this->x += FROG_STEP;
		break;
	}
	this->ci = temp;
	this->drawSquare();
}

// check the border and change the goal if necessary
void frog::checkBorder()
{
	static int collidedBorder = NO_BORDER;
	collidedBorder = this->checkCollisionBorder();
	switch (collidedBorder)
	{
	// Nothing happens if the frog collides with the left or right border
	case NO_BORDER:
	case LEFT_BORDER:
	case RIGHT_BORDER:
		break;
	// If the frog collides with the top border and goal is SCHOOL, change the goal to HOME
	case TOP_BORDER:
		if (this->goal == SCHOOL)
		{
			Uart1_Printf("SCHOOL\n");
			this->goal = HOME;
		}
		break;
	// If the frog collides with the bottom border and goal is HOME, add a car and increase the score
	case BOTTOM_BORDER:
		if (this->goal == HOME)
		{
			addCar();
			score++;
			Uart1_Printf("HOME, SCORE: %d\n", score);
			this->goal = SCHOOL;
		}
		break;
	}
}

// move the car
void car::moveCar()
{
	int temp = this->ci;
	this->ci = BACK_COLOR;
	this->drawSquare();
	this->x += CAR_STEP * this->dir;
	if ((this->x + this->w >= X_MAX) || (this->x <= X_MIN))
		this->dir = -this->dir;
	this->ci = temp;
	this->drawSquare();
}

/*---------- CLASS FUNCTION DEFINITION END ----------*/

/*---------- SYSTEM RELATED FUNCTION START ----------*/

extern "C" void abort(void)
{
	while (1)
		;
}

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 7 << 16;
}

/*---------- SYSTEM RELATED FUNCTION END ----------*/

/*---------- LCD RELATED FUNCTION START ----------*/

void lcdDrawChar(int x, int y, int num, unsigned short color, int scale)
{
	if (num < 0 || num > 9)
		return;

	const unsigned char *bitmap = font[num];
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (bitmap[row] & (1 << (2 - col)))
			{
				Lcd_Draw_Box(x + col * scale, y + row * scale, scale, scale, color);
			}
		}
	}
}

void lcdDrawNumber(int x, int y, int number, unsigned short color, int scale)
{
	if (number < 0 || number > 99)
		return;

	lcdDrawChar(x, y, number / 10, color, scale);
	// Char width + spaceing added to x
	lcdDrawChar(x + 3 * scale + scale, y, number % 10, color, scale);
}

/*---------- LCD RELATED FUNCTION END ----------*/

/*---------- GAME RELATED FUNCTION START ----------*/

// check collision with cars
int checkCollisionWithCars(frog *FUCKINGFROG, car cars[], int curCar)
{
	for (int i = 0; i < curCar; i++)
		if (FUCKINGFROG->checkCollision(&cars[i]))
			return 1;
	return 0;
}

// add a car
void addCar()
{
	if (curCar < MAX_CAR)
	{
		cars[curCar] = car(10, 40 + 30 * curCar, CAR_SIZE_X, CAR_SIZE_Y, curCar + 1, RIGHT);
		cars[curCar].drawSquare();
		curCar++;
	}
}

// initialize the game
static void Game_Init()
{
	score = 0;
	curCar = 0;
	Lcd_Clr_Screen();
	FUCKINGFROG = frog(150, 220, FROG_SIZE_X, FROG_SIZE_Y, FROG_COLOR, SCHOOL);
	FUCKINGFROG.drawSquare();
	addCar();
	Uart_Printf("Game Start\n");
}

// return -1 if game over
// else return 0
static int jogKeyHandler()
{
	FUCKINGFROG.moveFrog(Jog_key);
	// check collision with cars
	if (checkCollisionWithCars(&FUCKINGFROG, cars, curCar))
	{
		return GAME_OVER;
	}
	// check border
	FUCKINGFROG.checkBorder();
	Jog_key_in = 0;
	return 0;
}

// return -1 if game over
// else return 0
static int timerHandler()
{
	for (i = 0; i < curCar; i++)
	{
		cars[i].moveCar();
	}
	// check collision with frog
	if (checkCollisionWithCars(&FUCKINGFROG, cars, curCar))
	{
		return GAME_OVER;
	}
	TIM4_expired = 0;
	return 0;
}

// game is over game is over
static void Game_Over()
{
	TIM4_Repeat_Interrupt_Enable(0, 0);
	Uart_Printf("Game Over, your score is %d.\nPress Push Button to continue.\n", score);
	Lcd_Clr_Screen();
	lcdDrawNumber(80, 50, score % 100, WHITE, 20);
	static int k = 0;
	while(1)
	{
		if (Jog_key == 4 || Jog_key == 5)
		{
			Jog_key_in = 0;
			break;
		}
	}
}

/*---------- GAME RELATED FUNCTION END ----------*/

/*---------- MAIN START ----------*/

extern "C" void Main()
{
	Sys_Init();
	Uart_Printf("Game Example\n\n");

	Lcd_Init();
	Jog_Poll_Init();
	Jog_ISR_Enable(1);
	Uart1_RX_Interrupt_Enable(1);

	for (;;)
	{
		Game_Init();
		TIM4_Repeat_Interrupt_Enable(1, TIMER_PERIOD * 10);
		int gameOver = 0;

		for (;;)
		{
			// jog key input
			if (Jog_key_in)
			{
				gameOver = jogKeyHandler();
			}
			// timer interrupt
			if (TIM4_expired)
			{
				gameOver = timerHandler();
			}
			// game over
			if (gameOver)
			{
				Game_Over();
				break;
			}
		}
	}
}

/*---------- MAIN END ----------*/

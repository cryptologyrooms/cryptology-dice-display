#include <Adafruit_NeoPixel.h>
#include <TaskAction.h>

#include "dice.h"
#include "display-config.h"

static const int NEOPIXEL_DATA_PIN = 3;

static const int COLOUR_R = 0;
static const int COLOUR_G = 0;
static const int COLOUR_B = 255;

static Adafruit_NeoPixel s_strip = Adafruit_NeoPixel(9, NEOPIXEL_DATA_PIN, NEO_GRB + NEO_KHZ800);

static int s_state = 0;

static const int NUMBER_OF_STATES = sizeof(s_numbers) / sizeof(int);
static const int s_delays[NUMBER_OF_STATES] = {SHORT_DELAY_MS, SHORT_DELAY_MS, SHORT_DELAY_MS, LONG_DELAY_MS};

static void set_dice_face(Adafruit_NeoPixel& strip, int number)
{
	int px;
	int r = 0; int g = 0; int b = 0;

	for (px = 0; px < 9; px++)
	{
		if (pixel_is_on(number, px))
		{
			r = COLOUR_R; g = COLOUR_G; b = COLOUR_B;
		}

		strip.setPixelColor(px, r, g, b);
	}

	strip.show();
}

void set_number_task_fn(TaskAction * this_task)
{
	set_dice_face(s_strip, s_numbers[s_state]);
	this_task->SetInterval(s_delays[s_state]);
	s_state  = (s_state < NUMBER_OF_STATES) ? s_state+1 : 0;
}
static TaskAction s_set_number_task(set_number_task_fn, 500, INFINITE_TICKS);

void setup()
{
	s_strip.begin();
	s_strip.show();
}

void loop()
{
	s_set_number_task.tick();
}

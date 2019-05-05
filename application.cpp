#include <Adafruit_NeoPixel.h>

#include "raat.hpp"

#include "adafruit-neopixel-raat.hpp"

#include "raat-oneshot-timer.hpp"
#include "raat-oneshot-task.hpp"
#include "raat-task.hpp"

#include "dice.h"

static AdafruitNeoPixelRAAT * s_pStrip;
static EightBitRGBParam * s_pRGBParam;

static uint8_t s_number_of_states = 0;
static uint8_t s_state = 0;
static int32_t s_longdelay = 0;
static int32_t s_shortdelay = 0;

static char s_combination[16] = "";
static uint8_t s_numbers[16] = {0};

static void set_dice_face(int number)
{
	int px;
	uint8_t rgb[3];

	for (px = 0; px < 9; px++)
	{
		if (pixel_is_on(number, px))
		{
			s_pRGBParam->get(rgb);
		}
		else
		{
			rgb[0] = 0; rgb[1] = 0; rgb[2] = 0;
		}

		s_pStrip->setPixelColor(px, rgb[0], rgb[1], rgb[2]);
	}

	s_pStrip->show();
}

static void set_number_task_fn(RAATTask& ThisTask, void * pTaskData)
{
	(void)pTaskData;
	Serial.print(s_state);
	Serial.print(" :");

	if (s_state == s_number_of_states-1)
	{
		ThisTask.set_period(s_longdelay);	
		Serial.println("0");
		set_dice_face(0);
	}
	else
	{
		ThisTask.set_period(s_shortdelay);
		Serial.println(s_numbers[s_state]);
		set_dice_face(s_numbers[s_state]);		
	}
	incrementwithrollover(s_state, s_number_of_states-1);
}
static RAATTask set_number_task(0, set_number_task_fn);

void raat_custom_setup(const raat_devices_struct& devices, const raat_params_struct& params)
{
	s_pStrip = devices.pNeoPixels;
	s_pRGBParam = params.pColour;

	params.pCombination->get(s_combination);
	s_number_of_states = strlen(s_combination) + 1;

	{
		uint8_t i = 0;
		while (s_combination[i] != '\0')
		{
			s_numbers[i] = s_combination[i] - '0';
			i++;
		}
	}
}

void raat_custom_loop(const raat_devices_struct& devices, const raat_params_struct& params)
{
	s_longdelay = params.pLong_Delay->get();
	s_shortdelay = params.pShort_Delay->get();
	set_number_task.run();
}


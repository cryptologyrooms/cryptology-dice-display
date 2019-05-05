#include <stdint.h>

static const bool NUMBERS_TO_PIXEL_MAP[10][9] = {
	{
		false, false, false,
		false, false, false,
		false, false, false
	}, //0

	{
		false, false, false,
		false, true,  false,
		false, false, false
	}, //1
	{
		true,  false, false,
		false, false, false,
		false, false, true 
	}, //2
	{
		false, false, true,
		false, true,  false,
		true,  false, false
	}, //3
	{
		true,  false, true,
		false, false, false,
		true,  false, true 
	}, //4
	{
		true,  false, true,
		false, true,  false,
		true,  false, true 
	}, //5
	{
		true, false, true,
		true, false, true,
		true, false, true
	}, //6
	{
		true, false, true,
		true, true,  true,
		true, false, true
	}, //7
	{
		true, true,  true,
		true, false, true,
		true, true,  true
	}, //8
	{
		true, true, true,
		true, true, true,
		true, true, true
	}, //9
};

bool pixel_is_on(uint8_t number, uint8_t px)
{
	if ((number > 9) || (px >= 9)) { return false; }

	return NUMBERS_TO_PIXEL_MAP[number][px];
}
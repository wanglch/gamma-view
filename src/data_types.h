/**
 * @file	data_types.h
 * @brief	gives data types for gamma-view
 * @author	Mateusz Plociennik
 * @data	2012-07-15
 */

#ifndef _GAMMA_VIEW_DATA_TYPES_H_
#define _GAMMA_VIEW_DATA_TYPES_H_

enum GammaColormap_e
{
	GAMMA_COLORMAP_AUTUMN = 0,
	GAMMA_COLORMAP_BONE,
	GAMMA_COLORMAP_COOL,
	GAMMA_COLORMAP_COPPER,
	GAMMA_COLORMAP_GRAY,
	GAMMA_COLORMAP_GRAY_INV,
	GAMMA_COLORMAP_HOT,
	GAMMA_COLORMAP_HSV,
	GAMMA_COLORMAP_JET,
	GAMMA_COLORMAP_OCEAN,
	GAMMA_COLORMAP_PINK,
	GAMMA_COLORMAP_RAINBOW,
	GAMMA_COLORMAP_SPRING,
	GAMMA_COLORMAP_SUMMER,
	GAMMA_COLORMAP_WINTER,
};

enum GammaSetting_e
{
	GAMMA_SET_RESERVED = 0x00,
	GAMMA_SET_DISPLAY = 0x01, //deprecated
	GAMMA_SET_ZOOM,
	GAMMA_SET_SHIFT_X,
	GAMMA_SET_SHIFT_Y,
	GAMMA_SET_TMARKER,
	GAMMA_SET_GATE,
	GAMMA_SET_END, //end
};

enum GammaSettingTmarker_e
{
	GAMMA_TMARKER_OFF = 0x00,
	GAMMA_TMARKER_1MS,
	GAMMA_TMARKER_10MS,
	GAMMA_TMARKER_100MS,
	GAMMA_TMARKER_1000MS,
};

enum GammaBlockDataItemType_e
{
	GAMMA_ITEM_POINT = 'P',
	GAMMA_ITEM_TMARKER = 'T', 
	GAMMA_ITEM_TRIGGER = 'G',
};

enum GammaBlockDataType_e
{
	GAMMA_DATA_USB_RAW = 'U',
	GAMMA_DATA_POINTS = 'S',
	GAMMA_DATA_WXIMAGE = 'I',
};

enum GammaBlockMode_e
{
	GAMMA_MODE_USB_2_FILE = 0,
	GAMMA_MODE_USB_2_IMAGE,
	GAMMA_MODE_FAKE_2_FILE,
	GAMMA_MODE_FAKE_2_IMAGE,
	GAMMA_MODE_FILE_2_IMAGE,
	GAMMA_MODE_USB_FULL,
	GAMMA_MODE_PLAYBACK,
	GAMMA_MODE_VIRTUAL,
	GAMMA_MODE_NONE,
};

struct GammaPoint 		// 6 bytes
{
	unsigned char x;	// 1 byte
	unsigned char y; 	// 1 byte
	float z;			// 4 bytes
};

struct GammaItem				// 7 bytes
{
	unsigned char type;			// 1 byte
	union
	{
		unsigned long int time;		// 4 bytes
		GammaPoint point;		// 6 bytes
	} data;
};

#endif //_GAMMA_VIEW_DATA_TYPES_H_

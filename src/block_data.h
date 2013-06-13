/**
 * @file	block_data.h
 * @brief	GammaBlockDataBase class declaration.
 * @author	Mateusz Plociennik
 * @data	2012-07-20
 */

#ifndef _GAMMA_VIEW_BLOCK_DATA_H_
#define _GAMMA_VIEW_BLOCK_DATA_H_

#include <vector>
#include <stdint.h>

#include <wx/datetime.h>
#include <wx/thread.h>
#include <list>
#include "data_types.h"

/**
 * Base class to make GammaBlock able to send pointers without cast.
 */
class GammaData
{
public:
	/**
	 * Default constructor.
	 */
	GammaData()
	{
	}

	virtual ~GammaData()
	{
	}
};

/**
 * GammaDataUSB class.
 */
class GammaDataUSB :
	public GammaData
{
public:
	GammaDataUSB()
	{
	}

	~GammaDataUSB()
	{
	}

	wxUint8 data[256 * 256];
};

/**
 * GammaItems class.
 */
class GammaItems :
	public GammaData
{
public:
	GammaItems()
		: items(256)
	{
	}

	~GammaItems()
	{
	}

	std::vector<GammaItem> items;
};

/**
 * GammaImage class.
 */
class GammaMatrix :
	public GammaData
{
public:
	GammaMatrix()
		: eventMax(1)
		, eventSum(0)
		, time(0)
		, span(0)
		, trig(GAMMA_TRIG_NONE)
	{
	}

	~GammaMatrix()
	{
	}

	wxUint32 matrix[256 * 256];
	wxUint32 eventMax;
	wxUint64 eventSum;

	wxTimeSpan time;
	wxTimeSpan span;

	GammaTrig_e trig;
};

/**
 * GammaImage class.
 */
class GammaImage :
	public GammaData
{
public:
	GammaImage()
		: image(256, 256, true)
	{
	}

	~GammaImage()
	{
	}

	wxImage image;
};

#endif //_GAMMA_VIEW_BLOCK_DATA_H_

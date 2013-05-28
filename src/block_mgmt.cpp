/**
 * @file	block_mgmt.cpp
 * @brief	blocks manager
 * @author	Mateusz Plociennik
 * @data	2012-07-25
 */

#include "block_mgmt.h"

#include "block_fread.h"
#include "block_fwrite.h"
#include "block_tr_us.h"
#include "block_tr_sm.h"
#include "block_tr_mi.h"
#include "block_usb.h"
#include "block_usb_fake.h"
#include "b_nemacalc.h"
#include "b_uniform.h"

void GammaManager::setMode(GammaMode_e mode)
{
	switch(mode)
	{
	case GAMMA_MODE_USB_2_FILE:
		{
			GammaPipeSegment* usb = new GammaBlockUSB(this);
			GammaPipeSegment* trans = new GammaBlockTransUS(this);
			GammaPipeSegment* file = new GammaBlockFileWrite(this);
			m_blockList.push_back(usb);
			m_blockList.push_back(trans);
			m_blockList.push_back(file);

			trans->connectSegment(file);
			usb->connectSegment(trans);
			
			//file->Run();
			//trans->Run();
			//usb->Run();
			break;
		}
	case GAMMA_MODE_FAKE_2_FILE:
		{
			GammaPipeSegment* usb = new GammaBlockUSBFake(this);
			GammaPipeSegment* trans = new GammaBlockTransUS(this);
			GammaPipeSegment* file = new GammaBlockFileWrite(this);
			m_blockList.push_back(usb);
			m_blockList.push_back(trans);
			m_blockList.push_back(file);

			trans->connectSegment(file);
			usb->connectSegment(trans);
			
			//file->Run();
			//trans->Run();
			//usb->Run();
			break;
		}
	case GAMMA_MODE_FAKE_2_IMAGE:
		{
			GammaPipeHead* usb = new GammaBlockUSBFake(this);
			GammaPipeSegment* tr_us = new GammaBlockTransUS(this);
			GammaPipeSegment* unif = new GammaUniformity(this);
			GammaPipeSegment* tr_sm = new GammaBlockTransSM(this);
			GammaPipeSegment* tr_mi = new GammaTransMI(this);
			
			m_blockList.push_back(usb);
			
			m_blockList.push_back(tr_us);
			m_blockList.push_back(unif);
			m_blockList.push_back(tr_sm);
			m_blockList.push_back(tr_mi);

			tr_sm->connectSegment(tr_mi);
			tr_us->connectSegment(tr_sm);
			usb->connectSegment(tr_us);

			*usb += *tr_us += *unif += *tr_sm += /*nema += */*tr_mi;

			usb->start();
			break;
		}
	case GAMMA_MODE_USB_2_IMAGE:
		{
			GammaPipeSegment* usb = new GammaBlockUSB(this);
			GammaPipeSegment* tr_us = new GammaBlockTransUS(this);
			GammaPipeSegment* tr_sm = new GammaBlockTransSM(this);
			GammaPipeSegment* tr_mi = new GammaTransMI(this);
			m_blockList.push_back(usb);
			m_blockList.push_back(tr_us);
			m_blockList.push_back(tr_sm);
			m_blockList.push_back(tr_mi);

			tr_sm->connectSegment(tr_mi);
			tr_us->connectSegment(tr_sm);
			usb->connectSegment(tr_us);

			//tr_mi->Run();
			//tr_sm->Run();
			//tr_us->Run();
			//usb->Run();
			break;
		}
	case GAMMA_MODE_USB_FULL:
		{
			GammaPipeSegment* usb = new GammaBlockUSB(this);
			GammaPipeSegment* tr_us = new GammaBlockTransUS(this);
			GammaPipeSegment* write = new GammaBlockFileWrite(this);
			GammaPipeSegment* tr_sm1 = new GammaBlockTransSM(this);
			GammaPipeSegment* tr_mi1 = new GammaTransMI(this);
			GammaPipeSegment* tr_sm2 = new GammaBlockTransSM(this);
			GammaPipeSegment* tr_mi2 = new GammaTransMI(this);


			m_blockList.push_back(usb);
			m_blockList.push_back(tr_us);
			m_blockList.push_back(write);
			m_blockList.push_back(tr_sm1);
			m_blockList.push_back(tr_mi1);
			m_blockList.push_back(tr_sm2);
			m_blockList.push_back(tr_mi2);

			tr_sm1->connectSegment(tr_mi1);
			tr_us->connectSegment(tr_sm1);
			tr_sm2->connectSegment(tr_mi2);
			tr_us->connectSegment(tr_sm2);
			tr_us->connectSegment(write);
			usb->connectSegment(tr_us);

			break;
		}
	case GAMMA_MODE_FILE_2_IMAGE:
		{
			GammaPipeHead* file = new GammaBlockFileRead(this);
			GammaPipeSegment* unif = new GammaUniformity(this);
			GammaPipeSegment* tr_sm = new GammaBlockTransSM(this);
			GammaPipeSegment* nema = new GammaNemaCalc(this);
			GammaPipeSegment* tr_mi = new GammaTransMI(this);
			
			m_blockList.push_back(file);
			m_blockList.push_back(unif);
			m_blockList.push_back(tr_sm);
			m_blockList.push_back(nema);
			m_blockList.push_back(tr_mi);

			*file += *unif += *tr_sm += /*nema += */*tr_mi;

			file->start();
			break;
		}
	case GAMMA_MODE_NONE:
	default:
		{
			dynamic_cast<GammaPipeHead*>(m_blockList.front())->stop();
			while(!m_blockList.empty())
			{
				//m_blockList.front()->Stop();
				delete m_blockList.front();
				m_blockList.pop_front();
			}

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

int GammaManager::DataTierSetParam(GammaParam_e param, void* value)
{
	int ret = 0;

	for(std::list<GammaPipeSegment*>::iterator iBlock = m_blockList.begin();
		iBlock != m_blockList.end(); iBlock++ )
	{
		if((*iBlock)->setParam(param, value))
		{
			ret++;
		}
	}

	return ret;
}
	
////////////////////////////////////////////////////////////////////////////////

bool GammaManager::PresentationTierSetParam(GammaParam_e param, void* value)
{
	return m_pFrame->SetParam(param, value);
}

GammaConfig* GammaManager::getConfig()
{
	return &m_config;
}

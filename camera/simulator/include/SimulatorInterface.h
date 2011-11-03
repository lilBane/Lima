//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2011
// European Synchrotron Radiation Facility
// BP 220, Grenoble 38043
// FRANCE
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################
#ifndef SIMUHWINTERFACE_H
#define SIMUHWINTERFACE_H

#include "SimulatorCompatibility.h"
#include "HwInterface.h"
#include "SimulatorCamera.h"

namespace lima
{

class HwInterface;

namespace Simulator
{


/*******************************************************************
 * \class DetInfoCtrlObj
 * \brief Control object providing simulator detector info interface
 *******************************************************************/

class LIBSIMULATOR_API DetInfoCtrlObj : public HwDetInfoCtrlObj
{
 public:
	DetInfoCtrlObj(Camera& simu);
	virtual ~DetInfoCtrlObj();

	virtual void getMaxImageSize(Size& max_image_size);
	virtual void getDetectorImageSize(Size& det_image_size);

	virtual void getDefImageType(ImageType& def_image_type);
	virtual void getCurrImageType(ImageType& curr_image_type);
	virtual void setCurrImageType(ImageType  curr_image_type);

	virtual void getPixelSize(double& pixel_size);
	virtual void getDetectorType(std::string& det_type);
	virtual void getDetectorModel(std::string& det_model);

	virtual void registerMaxImageSizeCallback(
					HwMaxImageSizeCallback& cb);
	virtual void unregisterMaxImageSizeCallback(
					HwMaxImageSizeCallback& cb);

 private:
	class MaxImageSizeCallbackGen: public HwMaxImageSizeCallbackGen
	{
	protected:
		virtual void setMaxImageSizeCallbackActive(bool cb_active);
	};

	Camera& 		m_simu;
	MaxImageSizeCallbackGen m_mis_cb_gen;
};

/*******************************************************************
 * \class SyncCtrlObj
 * \brief Control object providing simulator synchronization interface
 *******************************************************************/

class LIBSIMULATOR_API SyncCtrlObj : public HwSyncCtrlObj
{
 public:
	SyncCtrlObj(Camera& simu);
	virtual ~SyncCtrlObj();

	virtual bool checkTrigMode(TrigMode trig_mode);
	virtual void setTrigMode(TrigMode  trig_mode);
	virtual void getTrigMode(TrigMode& trig_mode);

	virtual void setExpTime(double  exp_time);
	virtual void getExpTime(double& exp_time);

	virtual void setLatTime(double  lat_time);
	virtual void getLatTime(double& lat_time);

	virtual void setNbHwFrames(int  nb_frames);
	virtual void getNbHwFrames(int& nb_frames);

	virtual void getValidRanges(ValidRangesType& valid_ranges);

 private:
	Camera& m_simu;
};


/*******************************************************************
 * \class BinCtrlObj
 * \brief Control object providing simulator binning interface
 *******************************************************************/

class LIBSIMULATOR_API BinCtrlObj : public HwBinCtrlObj
{
 public:
	BinCtrlObj(Camera& simu);
	virtual ~BinCtrlObj();

	virtual void setBin(const Bin& bin);
	virtual void getBin(Bin& bin);
	virtual void checkBin(Bin& bin);

 private:
	Camera& m_simu;
};


/*******************************************************************
 * \class HwInterface
 * \brief Simulator hardware interface
 *******************************************************************/

class LIBSIMULATOR_API Interface : public HwInterface
{
 public:
	Interface(Camera& simu);
	virtual ~Interface();

	virtual void getCapList(CapList&) const;

	virtual void reset(ResetLevel reset_level);
	virtual void prepareAcq();
	virtual void startAcq();
	virtual void stopAcq();
	virtual void getStatus(StatusType& status);
	virtual int getNbHwAcquiredFrames();

 private:
	Camera& 	m_simu;
	CapList 	m_cap_list;
	DetInfoCtrlObj 	m_det_info;
	SyncCtrlObj    	m_sync;
	BinCtrlObj     	m_bin;
};

}
}

#endif // SIMUHWINTERFACE_H
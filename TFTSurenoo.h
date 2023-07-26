/*
 *   Copyright (C) 2019 by SASANO Takayoshi JG1UAA
 *   Copyright (C) 2015,2016,2018,2020,2023 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined(TFTSURENOO_H)
#define TFTSURENOO_H

#include "Display.h"
#include "Defines.h"
#include "SerialPort.h"

#include <string>

class CTFTSurenoo : public CDisplay
{
public:
	CTFTSurenoo(const std::string& callsign, unsigned int id, bool duplex, ISerialPort* serial, unsigned int brightness);
	virtual ~CTFTSurenoo();

	virtual bool open();

	virtual void close();

protected:
	virtual void setIdleInt();
	virtual void setErrorInt();
	virtual void setLockoutInt();
	virtual void setQuitInt();
	virtual void setFMInt();

	virtual void writeDStarInt(const std::string& my1, const std::string& my2, const std::string& your, const std::string& type, const std::string& reflector);
	virtual void clearDStarInt();

	virtual void writeDMRInt(unsigned int slotNo, const std::string& src, bool group, unsigned int dst, const std::string& type);
	virtual void clearDMRInt(unsigned int slotNo);

	virtual void writeFusionInt(const std::string& source, const std::string& dest, unsigned char dgid, const std::string& type, const std::string& origin);
	virtual void clearFusionInt();

	virtual void writeP25Int(const std::string& source, bool group, unsigned int dest, const std::string& type);
	virtual void clearP25Int();

	virtual void writeNXDNInt(const std::string& source, bool group, unsigned int dest, const std::string& type);
	virtual void clearNXDNInt();

	virtual void writeM17Int(const std::string& source, const std::string& dest, const std::string& type);
	virtual void clearM17Int();

	virtual void writePOCSAGInt(uint32_t ric, const std::string& message);
	virtual void clearPOCSAGInt();

	virtual void writeCWInt();
	virtual void clearCWInt();

	virtual void clockInt(unsigned int ms);

private:
	std::string   m_callsign;
	unsigned int  m_id;
	bool          m_duplex;
	ISerialPort*  m_serial;
	unsigned int  m_brightness;
	unsigned char m_mode;
	bool          m_refresh;
	CTimer        m_refreshTimer;
	char*         m_lineBuf;
	char          m_temp[128];

	void setLineBuffer(char *buf, const char *text, int maxchar);
	void setModeLine(const char *text);
	void setStatusLine(unsigned int line, const char *text);
	void refreshDisplay();

	void lcdReset();
	void clearScreen(unsigned char colour);
	void setBackground(unsigned char colour);
	void setRotation(unsigned char rotation);
	void setBrightness(unsigned char brightness);
};

#endif

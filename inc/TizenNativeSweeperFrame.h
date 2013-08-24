#ifndef _TIZENNATIVESWEEPERFRAME_H_
#define _TIZENNATIVESWEEPERFRAME_H_

#include "tizenx.h"

class TizenNativeSweeperFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	TizenNativeSweeperFrame(void);
	virtual ~TizenNativeSweeperFrame(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif	//_TIZENNATIVESWEEPERFRAME_H_

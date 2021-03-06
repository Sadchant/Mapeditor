#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include "Singleton.h"

#define g_pTimer CTimer::Get ()
class CTimer : public TSingleton<CTimer>
{
public:
	CTimer();
	void	Update();
	float	GetElapsed(){ return m_fElapsed; }
	float	GetLastTime(){ return m_fLastTime; }

private:
	float	m_fElapsed;			// Vergangene Zeit seit dem letzten Frame
	float	m_fCurTime;			// Aktuelle Zeit
	float	m_fLastTime;		// Zeit des letzten Frames


};

#endif

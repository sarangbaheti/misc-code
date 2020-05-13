#ifndef NOTIFY_H__
#define NOTIFY_H__

#include "ansi.h"
//----------------------------------------------------------------------
class Notifiable
{
public:
	virtual void notify( class Notifier *sender ) = 0;
	virtual ~Notifiable(){}
};
//----------------------------------------------------------------------
class Notifier
{
	bool	am_silent;
public:
	virtual ~Notifier(){};

	Notifier( void ): am_silent( false ) {}

	void	notify_on	( void ){ am_silent = false;}
	void	notify_off	( void ){ am_silent = true; }
	
	void notify(Notifiable *observer)
	{
		if( !am_silent )
			observer->notify(this);
	}
};
//----------------------------------------------------------------------
static class Notify_nobody: public Notifiable
{
public:
	virtual void notify( Notifier * ){}
}
Nobody;
//----------------------------------------------------------------------
#endif // NOTIFY_H__

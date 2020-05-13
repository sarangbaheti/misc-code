// ChangeValueFrame.cpp

#include "stdeos.hpp" // this header file must be first for precompiled headers to work

#ifndef CHANGEVALUEFRAME_HPP
#include <ChangeValueFrame.hpp>
#endif

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//ChangeValueFrame
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

ChangeValueFrame::ChangeValueFrame() : EosFramework(),
	value()
{
	CONNECT_ChangeValueFrame()
}

ChangeValueFrame::ChangeValueFrame(const ChangeValueFrame& src) : EosFramework(src),
	value(src.value)
{
	CONNECT_ChangeValueFrame()
}

ChangeValueFrame::~ChangeValueFrame()
{
	disconnect();
}

ChangeValueFrame& ChangeValueFrame::operator =(const ChangeValueFrame& src)
{
	EOS_PROBE_LOCK(*this);
	if (this != &src)
	{
		EosFramework::operator=(src);
		value = src.value;
	}
	return *this;
}

void ChangeValueFrame::add()
{
	value += 15;
}

void ChangeValueFrame::subtract()
{
	value -= 15;
}




//BEGIN EOS BIND >>>>>> Don't edit this comment //////////////////////////////////////////////////
// This part Copyright (c) 1992-1996 ViewSoft, Inc. All Rights Reserved.

EOS_IMPLEMENT_REF(ChangeValueFrame,EosFramework)

extern void EOS_NVNV_prim(EosObject&,EosProbeMemberPointer&,EosParameterList&);



EOS_BND()
EOS_FNOFT_H(ChangeValueFrame)
EOS_FNOFT_V(ChangeValueFrame,void,(),0)
EOS_FNOFT_V(ChangeValueFrame,void,(),1)
EOS_FNOFT_T(ChangeValueFrame)
EOS_FNOFT_E(ChangeValueFrame,add,EOS_NVNV_prim)
EOS_FNOFT_E(ChangeValueFrame,subtract,EOS_NVNV_prim)
EOS_FNOFT_ET(ChangeValueFrame)
EOS_FNOPT_H(ChangeValueFrame,EosFramework,2)
EOS_FNOPT_E(ChangeValueFrame,0)
EOS_FNOPT_E(ChangeValueFrame,1)
EOS_FNOPT_T(ChangeValueFrame)
EOS_FIOFT_H(ChangeValueFrame)
EOS_FIOFT_V(ChangeValueFrame,EosInt,0)
EOS_FIOFT_T(ChangeValueFrame)
EOS_FIOFT_E(ChangeValueFrame,value)
EOS_FIOFT_ET(ChangeValueFrame)
EOS_FIOPT_H(ChangeValueFrame,EosFramework,1)
EOS_FIOPT_E(ChangeValueFrame,0,0)
EOS_FIOPT_T(ChangeValueFrame)
EOS_CTC(ChangeValueFrame,0,CHANGEVALUE)
EOS_CREATE(ChangeValueFrame)
EOS_GET_MO(ChangeValueFrame)

//END EOS BIND >>>>>> Don't edit this comment //////////////////////////////////////////////////

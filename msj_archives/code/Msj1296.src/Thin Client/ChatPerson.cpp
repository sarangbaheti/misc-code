// ChatPerson.cpp

#include "stdeos.hpp" // this header file must be first for precompiled headers to work

#ifndef CHATPERSON_HPP
#include <ChatPerson.hpp>
#endif

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//ChatPerson
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// Perform the send which adds the client string to the chat list
void ChatPerson::send()
{
	// Prepare the client string and add it to the chat list
	EosString theString("(" + fName + ") " + fSendString);
	int index = fChatList->add(theString);
	fChatList->selectAt(index);

	// Now clear the send string field on the client
	fSendString = "";
}

// The constructor that takes a pointer to the global chat list
ChatPerson::ChatPerson(EosPrimitiveArray<EosString> *chatList) : EosObject(),
	fChatList(chatList),
	fName(),
	fSendString()
{
	CONNECT_ChatPerson()
}


ChatPerson::ChatPerson() : EosObject(),
	fChatList(),
	fName(),
	fSendString()
{
	CONNECT_ChatPerson()
}

ChatPerson::ChatPerson(const ChatPerson& src) : EosObject(src),
	fChatList(src.fChatList),
	fName(src.fName),
	fSendString(src.fSendString)
{
	CONNECT_ChatPerson()
}

ChatPerson::~ChatPerson()
{
	disconnect();
}

ChatPerson& ChatPerson::operator =(const ChatPerson& src)
{
	EOS_PROBE_LOCK(*this);
	if (this != &src)
	{
		EosObject::operator=(src);
		fChatList = src.fChatList;
		fName = src.fName;
		fSendString = src.fSendString;
	}
	return *this;
}




//BEGIN EOS BIND >>>>>> Don't edit this comment //////////////////////////////////////////////////
// This part Copyright (c) 1992-1996 ViewSoft, Inc. All Rights Reserved.

EOS_IMPLEMENT_REF(ChatPerson,EosObject)

extern void EOS_NVNV_prim(EosObject&,EosProbeMemberPointer&,EosParameterList&);



EOS_BND()
EOS_FNOFT_H(ChatPerson)
EOS_FNOFT_V(ChatPerson,void,(),0)
EOS_FNOFT_T(ChatPerson)
EOS_FNOFT_E(ChatPerson,send,EOS_NVNV_prim)
EOS_FNOFT_ET(ChatPerson)
EOS_FNOPT_H(ChatPerson,EosObject,1)
EOS_FNOPT_E(ChatPerson,0)
EOS_FNOPT_T(ChatPerson)
EOS_FIOFT_H(ChatPerson)
EOS_FIOFT_V(ChatPerson,EosPrimitiveArrayRef<EosString>,0)
EOS_FIOFT_V(ChatPerson,EosString,1)
EOS_FIOFT_V(ChatPerson,EosString,2)
EOS_FIOFT_T(ChatPerson)
EOS_FIOFT_E(ChatPerson,fChatList)
EOS_FIOFT_E(ChatPerson,fName)
EOS_FIOFT_E(ChatPerson,fSendString)
EOS_FIOFT_ET(ChatPerson)
EOS_FIOPT_H(ChatPerson,EosObject,3)
EOS_FIOPT_E(ChatPerson,0,0)
EOS_FIOPT_E(ChatPerson,1,0)
EOS_FIOPT_E(ChatPerson,2,0)
EOS_FIOPT_T(ChatPerson)
EOS_CTC(ChatPerson,0,CHAT)
EOS_CREATE(ChatPerson)
EOS_GET_MO(ChatPerson)

//END EOS BIND >>>>>> Don't edit this comment //////////////////////////////////////////////////

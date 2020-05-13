// ChatApp.cpp

#include "stdeos.hpp" // this header file must be first for precompiled headers to work

#ifndef CHATAPP_HPP
#include <ChatApp.hpp>
#endif

#ifndef CHATPERSON_HPP
#include <ChatPerson.hpp>
#endif

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//ChatApp
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

// Retrieves a chat person object for each client that attaches to the server .exe
EosObject *ChatApp::getFirstObject()
{
  return (EosObject *)new ChatPerson(&fChatList);
}

// Allows the server app to control how the chat person object will be represented on the client
void ChatApp::initDialogArg(EosClient *client, EosDialogArg &dialogArg)
{
  dialogArg.fDialogName = EosAtom("Chat");
}

ChatApp::ChatApp() : EosFramework(),
	fChatList()
{
	CONNECT_ChatApp()
}

ChatApp::ChatApp(const ChatApp& src) : EosFramework(src),
	fChatList(src.fChatList)
{
	CONNECT_ChatApp()
}

ChatApp::~ChatApp()
{
	disconnect();
}

ChatApp& ChatApp::operator =(const ChatApp& src)
{
	EOS_PROBE_LOCK(*this);
	if (this != &src)
	{
		EosFramework::operator=(src);
		fChatList = src.fChatList;
	}
	return *this;
}





//BEGIN EOS BIND >>>>>> Don't edit this comment //////////////////////////////////////////////////
// This part Copyright (c) 1992-1996 ViewSoft, Inc. All Rights Reserved.

EOS_IMPLEMENT_REF(ChatApp,EosFramework)




EOS_BND()
EOS_FNOFT_H(ChatApp)
EOS_FNOFT_T(ChatApp)
EOS_FNOFT_ET(ChatApp)
EOS_FNOPT_H(ChatApp,EosFramework,0)
EOS_FNOPT_T(ChatApp)
EOS_FIOFT_H(ChatApp)
EOS_FIOFT_V(ChatApp,EosPrimitiveArray<EosString>,0)
EOS_FIOFT_T(ChatApp)
EOS_FIOFT_E(ChatApp,fChatList)
EOS_FIOFT_ET(ChatApp)
EOS_FIOPT_H(ChatApp,EosFramework,1)
EOS_FIOPT_E(ChatApp,0,0)
EOS_FIOPT_T(ChatApp)
EOS_CTC(ChatApp,0,CHAT)
EOS_CREATE(ChatApp)
EOS_GET_MO(ChatApp)

//END EOS BIND >>>>>> Don't edit this comment //////////////////////////////////////////////////

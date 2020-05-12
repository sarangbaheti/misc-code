/*
The MIT License (MIT)
Copyright (c) 2012 Thibaud Comte
Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR 
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define ARG_IS_SWITCH(arg) (arg[0]=='-')
#define FORMAT_SPACE "    "


class CmdLineParserParameter;
class CmdLineParserArgument;
class CmdLineParserExample;


class CmdLineParserEngine
{
public:
	CmdLineParserEngine(string description);
	~CmdLineParserEngine(void);
	void AddParameter(const CmdLineParserParameter&);
	void AddExample(const CmdLineParserExample&);
	void PrintHelp(void);
	bool ProcessCommandLine(int argc, char* argv[]);
	bool TryGetParameter(const string name, CmdLineParserParameter& outParameter);
	int GetParsedParametersCount(void);
	bool IsHelpRequested(void);
private:
	bool GetParameterEx(const string paramNameWithDash, CmdLineParserParameter& outParam);
	bool SetParameter(const string paramName, const CmdLineParserParameter& outParam);
private:
	string m_sNameOfExecutable;
	string m_sDescription;
	vector<CmdLineParserExample> m_vExamples;
	vector<CmdLineParserParameter> m_vParameters;
	bool m_bHelpRequested;
};

class CmdLineParserParameter
{
public:
	CmdLineParserParameter();
	CmdLineParserParameter(string name, string alias, string desc);
	~CmdLineParserParameter(void);
	void AddArgument(const CmdLineParserArgument&);
	void SetArgumentContent(int pos, string content);
	int GetArgumentCount(void);
	bool GetArgumentAt(int pos, CmdLineParserArgument& outArgument);
	bool TryGetArgument(const string name, CmdLineParserArgument& outArgument);
public:
	string m_sName;
	string m_sAlias;
	string m_sDescription;
	vector<CmdLineParserArgument> m_vArguments;
	bool m_bExists; // read from command-line ??
};


class CmdLineParserArgument
{
public:
	CmdLineParserArgument();
	CmdLineParserArgument(string name); // this has no defaults. we expect a value on the cmdline.
	CmdLineParserArgument(string name, string default); // this has a default. if no value is passed along on the cmdline, we'll set the value to the default.
	~CmdLineParserArgument(void);
	void SetContent(string content);

public:
	string m_sName;
	string m_sContent;
	string m_sDefault;
	bool m_bRequired;
};

class CmdLineParserExample
{
public:
	CmdLineParserExample();
	CmdLineParserExample(string command, string desc);
	~CmdLineParserExample();

public:
	string m_sCommand;
	string m_sDescription;
};
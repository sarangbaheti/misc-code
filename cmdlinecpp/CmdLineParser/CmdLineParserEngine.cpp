#include "CmdLineParserEngine.h"

/* CmdLineParserEngine */
CmdLineParserEngine::CmdLineParserEngine(string description) : m_sDescription(description)
{
	AddExample(CmdLineParserExample("-help", "print the help page relative to this program"));
}

CmdLineParserEngine::~CmdLineParserEngine(void)
{
}

bool CmdLineParserEngine::ProcessCommandLine(int argc, char* argv[])
{
	// name of exe
	size_t found;
	m_sNameOfExecutable = argv[0];
	found=m_sNameOfExecutable.find_last_of("/\\");
	m_sNameOfExecutable = m_sNameOfExecutable.substr(found+1);

	// check if help requested
	if(argc == 2)
	{
		if(strcmp(argv[1], "-help") == 0)
		{
			PrintHelp();
			return true;
		}
	}

	// feed arguments
	int argi;						// to iterate on the cmdline
	CmdLineParserParameter param;	// the current parameter object matching the current name from the cmdline
	CmdLineParserArgument argument;	// the current argument object
	for (argi=1; argi < argc; argi++)
	{
		if(ARG_IS_SWITCH(argv[argi]))
		{
			if(GetParameterEx(argv[argi], param))
			{
				param.m_bExists = true;
				int argIndex;
				for(argIndex=0; argIndex<param.GetArgumentCount(); argIndex++)
				{
					if(ARG_IS_SWITCH(argv[argi+argIndex+1]))
					{
						// if the argument needs a specified value (here we don't have such value on the cmdline), we fail.
						if( param.GetArgumentAt(argIndex, argument) )
						{
							if( argument.m_bRequired )
							{
								cerr << "Syntax error." << endl;
								return false;
							}
						}
					}
					else
					{
						param.SetArgumentContent(argIndex, argv[argi+argIndex+1]);
					}
				}
				SetParameter(param.m_sName, param); // replace old param
			}
			else
			{
				cerr << argv[argi] << ": unknown parameter." << endl;
				return false;
			}
		}

	}
	
	return true;
}

void CmdLineParserEngine::AddParameter(const CmdLineParserParameter& param)
{
	m_vParameters.push_back(param); // stores a copy of param
}

void CmdLineParserEngine::AddExample(const CmdLineParserExample& ex)
{
	m_vExamples.push_back(ex);
}

void CmdLineParserEngine::PrintHelp(void)
{
	vector<CmdLineParserParameter>::iterator paramIter;
	vector<CmdLineParserArgument>::iterator argIter;
	vector<CmdLineParserExample>::iterator exIter;
	CmdLineParserParameter param;
	CmdLineParserArgument arg;
	CmdLineParserExample ex;
	
	// NAME
	cout << "NAME" << endl;
	cout << FORMAT_SPACE << m_sNameOfExecutable << endl;
	cout << endl;

	// SYNOPSIS
	cout << "SYNOPSIS" << endl;
	cout << FORMAT_SPACE << m_sDescription << endl;
	cout << endl;

	// SYNTAX
	cout << "SYNTAX" << endl;
	cout << FORMAT_SPACE << m_sNameOfExecutable;
	for( paramIter = m_vParameters.begin(); paramIter != m_vParameters.end(); paramIter++)
	{
		param = (CmdLineParserParameter) *paramIter;
		cout << " [-" << param.m_sName;

		for( argIter = param.m_vArguments.begin(); argIter != param.m_vArguments.end(); argIter++)
		{
			arg = (CmdLineParserArgument) *argIter;
			if( arg.m_bRequired)
			{
				cout << "<" << arg.m_sName << ">";
			}
			else // optional
			{
				cout << "[<" << arg.m_sName << ">]";
			}
		}

		cout << "]";
	}
	cout << endl;
	cout << endl;
	
	// PARAMETERS
	cout << "PARAMETERS" << endl;
	for( paramIter = m_vParameters.begin(); paramIter != m_vParameters.end(); paramIter++)
	{
		param = (CmdLineParserParameter) *paramIter;
		cout << FORMAT_SPACE << "-" << param.m_sName << " | -" << param.m_sAlias;

		for( argIter = param.m_vArguments.begin(); argIter != param.m_vArguments.end(); argIter++)
		{
			arg = (CmdLineParserArgument) *argIter;
			cout << " <" << arg.m_sName << ">";
		}

		cout << endl;
		cout << FORMAT_SPACE << FORMAT_SPACE << param.m_sDescription << endl;
		cout << FORMAT_SPACE << FORMAT_SPACE;

		bool bAlreadyPrintDefaultValueMessage = false;

		for( argIter = param.m_vArguments.begin(); argIter != param.m_vArguments.end(); argIter++)
		{
			arg = (CmdLineParserArgument) *argIter;

			// not required means we have a default
			if(!arg.m_bRequired)
			{
				// need to print out "default value(s)" message
				if(!bAlreadyPrintDefaultValueMessage)
				{
					cout << "default value(s): ";
					bAlreadyPrintDefaultValueMessage = true;
				}

				cout << " <" << arg.m_sName << ">=" << arg.m_sDefault;
			}
		}
		cout << endl;
	}
	cout << endl;

	// EXAMPLES
	cout << "EXAMPLES" << endl;
	for( exIter = m_vExamples.begin(); exIter != m_vExamples.end(); exIter++ )
	{
		ex = (CmdLineParserExample) *exIter;
		cout << FORMAT_SPACE << m_sNameOfExecutable << " " << ex.m_sCommand << endl;
		cout << FORMAT_SPACE << ex.m_sDescription << endl;
		cout << endl;
	}

}

bool CmdLineParserEngine::GetParameterEx(const string paramNameWithDash, CmdLineParserParameter& outParam)
{
	vector<CmdLineParserParameter>::iterator paramIter;
	string paramName;

	// remove dash '-'
	paramName = paramNameWithDash.substr(1);

	for( paramIter=m_vParameters.begin(); paramIter != m_vParameters.end(); paramIter++ )
	{
		if( (paramIter->m_sName == paramName) || (paramIter->m_sAlias == paramName) )
		{
			outParam = *paramIter;
			return true;
		}
	}

	return false;
}

bool CmdLineParserEngine::SetParameter(const string paramName, const CmdLineParserParameter& outParam)
{
	vector<CmdLineParserParameter>::iterator paramIter;

	for( paramIter=m_vParameters.begin(); paramIter != m_vParameters.end(); paramIter++ )
	{
		if( paramIter->m_sName == paramName )
		{
			*paramIter = outParam;
			return true;
		}
	}

	return false;
}

bool CmdLineParserEngine::TryGetParameter(const string name, CmdLineParserParameter& outParameter)
{
	bool paramDefined = GetParameterEx("-"+name, outParameter);
	return paramDefined && outParameter.m_bExists;
}

int CmdLineParserEngine::GetParsedParametersCount(void)
{
	int count = 0;
	vector<CmdLineParserParameter>::iterator paramIter;

	for( paramIter=m_vParameters.begin(); paramIter != m_vParameters.end(); paramIter++ )
	{
		if( paramIter->m_bExists )
		{
			count++;
		}
	}

	return count;
}

bool CmdLineParserEngine::IsHelpRequested(void)
{
	return m_bHelpRequested;
}

/* CmdLineParserParameter */
CmdLineParserParameter::CmdLineParserParameter()
{
}

CmdLineParserParameter::CmdLineParserParameter(string name, string alias, string desc) : m_sName(name), m_sAlias(alias), m_sDescription(desc)
{
	m_bExists = false;
}

CmdLineParserParameter::~CmdLineParserParameter(void)
{
}

void CmdLineParserParameter::AddArgument(const CmdLineParserArgument& arg)
{
	m_vArguments.push_back(arg);
}

void CmdLineParserParameter::SetArgumentContent(int pos, string content)
{
	m_vArguments[pos].m_sContent = content;
}

int CmdLineParserParameter::GetArgumentCount(void)
{
	return m_vArguments.size();
}

bool CmdLineParserParameter::GetArgumentAt(int pos, CmdLineParserArgument& outArgument)
{
	if(pos < GetArgumentCount())
	{
		outArgument = m_vArguments[pos];
		return true;
	}

	return false;
}

/*
 * Get the argument object whose name is the one specified. If the argument is not given on the command-line, set its value to its default if any, otherwise, return false.
 *
*/
bool CmdLineParserParameter::TryGetArgument(const string name, CmdLineParserArgument& outArgument)
{
	vector<CmdLineParserArgument>::iterator argIter;
	CmdLineParserArgument tempArgument;

	for( argIter=m_vArguments.begin(); argIter != m_vArguments.end(); argIter++ )
	{
		if( argIter->m_sName == name )
		{
			tempArgument = *argIter;

			if( (tempArgument.m_sContent == "") && (!tempArgument.m_bRequired) && (tempArgument.m_sDefault != "") )
				tempArgument.m_sContent = tempArgument.m_sDefault;

			outArgument = tempArgument;
			return true;
		}
	}

	return false;
}

/* CmdLineParserArgument */
CmdLineParserArgument::CmdLineParserArgument()
{

}

CmdLineParserArgument::CmdLineParserArgument(string name) : m_sName(name)
{
	m_bRequired = true;
}

CmdLineParserArgument::CmdLineParserArgument(string name, string defaultContent) : m_sName(name), m_sDefault(defaultContent)
{
	m_bRequired = false;
}

CmdLineParserArgument::~CmdLineParserArgument(void)
{

}

void CmdLineParserArgument::SetContent(string content)
{
	m_sContent = content;
}

/* CmdLineParserExample */
CmdLineParserExample::CmdLineParserExample()
{

}

CmdLineParserExample::CmdLineParserExample(string command, string desc) : m_sCommand(command), m_sDescription(desc)
{

}

CmdLineParserExample::~CmdLineParserExample()
{

}
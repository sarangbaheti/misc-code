// CmdLineParser.cpp : Defines the entry point for the console application.
//

#include "CmdLineParserEngine.h"

int main(int argc, char* argv[])
{
	CmdLineParserEngine parser("This program sets up the rules to access the ftp, telnet and web-access capabilities on an Icon camera.");

	CmdLineParserParameter ftp("ftp", "f", "sets the ftp access login");
	ftp.AddArgument(CmdLineParserArgument("login", "LOGIN"));
	parser.AddParameter(ftp);

	CmdLineParserParameter telnet("telnet", "t", "sets the telnet access login and password");
	telnet.AddArgument(CmdLineParserArgument("login", "LOGIN"));
	telnet.AddArgument(CmdLineParserArgument("password", "PASS"));
	parser.AddParameter(telnet);

	CmdLineParserParameter web("web", "w", "sets the web access login and password");
	web.AddArgument(CmdLineParserArgument("login", "LOGIN"));
	web.AddArgument(CmdLineParserArgument("password", "PASS"));
	parser.AddParameter(web);

	parser.AddExample(CmdLineParserExample("", "print current logins and passwords"));
	parser.AddExample(CmdLineParserExample("-web", "set default web login and password unless they are already set"));
	parser.AddExample(CmdLineParserExample("-web john smith", "set web login to 'john' and password to 'smith' and erase existing values, if any"));
	parser.AddExample(CmdLineParserExample("-w john smith", "exact same than above"));
	parser.AddExample(CmdLineParserExample("-f jack -t -w john smith", "set ftp login to 'jack'. telnet used defaults. web to 'john':'smith'. erase existing values, if any"));

	// command line is: "-f abc -t qwe 123 -w toto 789"
	if( parser.ProcessCommandLine(argc, argv) == false )
	{
		cerr << "Failed to parse the command line." << endl;
		goto end_block;
	}

	// logic is here under
	if( (parser.GetParsedParametersCount() == 0) && (!parser.IsHelpRequested()) )
	{
		// no parameters specified by user on the command-line, print current logins and passwords
		cout << "Current logins and passwords are TOP SECRET." << endl;
	}
	else
	{
		CmdLineParserParameter param;
		CmdLineParserArgument argument;
		if( parser.TryGetParameter("ftp", param) )
		{
			if( param.TryGetArgument("login", argument) )
			{
				cout << "set ftp login to " << argument.m_sContent << endl;
			}
		}

		if( parser.TryGetParameter("telnet", param) )
		{
			if( param.TryGetArgument("login", argument) )
			{
				cout << "set telnet login to " << argument.m_sContent << endl;
			}

			if( param.TryGetArgument("password", argument) )
			{
				cout << "set telnet password to " << argument.m_sContent << endl;
			}
		}

		if( parser.TryGetParameter("web", param) )
		{
			if( param.TryGetArgument("login", argument) )
			{
				cout << "set web login to " << argument.m_sContent << endl;
			}

			if( param.TryGetArgument("password", argument) )
			{
				cout << "set web password to " << argument.m_sContent << endl;
			}
		}
	}

end_block:

	cout << endl << "Press <Enter> to exit this demo... ";
	cin.get();

	return 0;
}


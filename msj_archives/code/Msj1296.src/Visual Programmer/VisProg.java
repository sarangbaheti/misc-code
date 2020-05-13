//******************************************************************************
// VisProg.java: 
//
// Demo applet that reads in the HTML source from an URL,
// and replaces tag brackets with &lt; symbols.
//
// Written by Joshua Trupin, 9/96
// (c) Microsoft Systems Journal
//
//******************************************************************************

import java.applet.*;
import java.awt.*;
import java.net.*;
import java.io.*;
import java.util.StringTokenizer;

//==============================================================================
// Main Class for applet VisProg
//==============================================================================

public class VisProg extends Applet
{
	public String HTMLline = "";

//==========================================================================

	public void start() 
	{

	}

//==========================================================================

    public void paint(Graphics g) 
	{
		g.drawString(HTMLline, 10, 10);
	}

//==========================================================================
	
	public String goGet(String theURL)
	{
        String inputLine;
		String outputLine;

        try 
		{
			// Open the URL called for when this class was invoked

            URL msft = new URL(theURL);
            URLConnection msftConnection = msft.openConnection();

			// Get a data input stream from this URL connection
            DataInputStream dis = new DataInputStream(msftConnection.getInputStream());

			HTMLline = "";
			outputLine = "";

			// Keep reading a line of data until exhausted

            while ((inputLine = dis.readLine()) != null) 
			{
				HTMLline = HTMLline + inputLine;
			}

			
			// All finished, so close the data input stream

            dis.close();

			// HTMLline now has the full HTML text of the chosen URL. We
			// now need to change < to &lt; and > to &gt; to make the 
			// code displayable in a browser without having it accidentally
			// interpreted. In practice, however, if a > doesn't close a tag,
			// it can be left as is. Therefore, we only tokenize and
			// replace tag opening brackets.

			StringTokenizer st = new StringTokenizer(HTMLline, "<");
			while  (st.hasMoreTokens())
			{
				outputLine = outputLine + "&lt;" + st.nextToken();
			}

			return outputLine;
        }
		catch (MalformedURLException me) 
		{
            System.out.println("MalformedURLException: " + me);
        }
		catch (IOException ioe) 
		{
            System.out.println("IOException: " + ioe);
        }
		return "";  // If there's an error, return a blank string instead.
	}
}

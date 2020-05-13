ReadMe for December '97 Bugslayer code.

If you have any questions (or debugging tips -- keep'em rollin' in!)
drop me an email at john@jprobbins.com.

Directories under this one:

.\TraceSrv      - The actual TraceSrv DCOM service.
.\Test          - A VB test program for TraceSrv.
.\DCOMTest      - A C console program to call TraceSrv.
.\TraceView     - The VB TraceView to view output sent TraceSrv.
.\VBA           - A Word97 document that uses VBA to talk to TraceSrv.
.\VBScript      - A HTML page that uses VBScript to talk to TraceSrv.
.\Lib           - The INTEL and ALPHA versions of the Memory Dumper and
                  Validator libraries from Bugslayer Oct. '97.

To build:

Since VC5 keeps full paths in the .MAK files, you cannot build directly
from the command line unless you put everything in the following
directory: \Dev\Column\Dec97\SourceCode.  Bummer.  You will need to open
up each .DSW with MSDEV and build from there.

The TraceSrv project must be built first.



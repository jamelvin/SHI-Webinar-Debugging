# SHI-Webinar-Debugging
Content (Instructions/Slides/Examples) for the Sustainable Horizons Institute Webinar on Debugging

I will be using GDB (GNU Project Debugger) for all examples.  To prevent the need for everyone to have GDB installed on their computers and be familiar with unix, I will do the examples using the web based gdb found at https://www.onlinegdb.com/.  There are instructions in the repository for how to take an example and get yourself to a gdb command prompt so that you can follow along interactively.

Below are some brief "instructions" for installing GDB (if necessary) for various OS.  For Mac and Windows this can be difficult and I apologize for the instructions possibly not being very helpful for those.  Googling for your particular OS and coding environment will yield the best results for trying to install for your particular setup.

Linux:
  GDB should come installed as a standard package on your system.  If you don't already have it, you should be able to install it using your package manager or from https://www.gnu.org/software/gdb/download/.
  
Mac:
  GDB may already be there or it can be complicated to install.  It is usually dependent on which OS version you are running.  You may also be able to use LLDB instead.  See https://www.quora.com/How-can-I-install-GDB-on-a-Mac for one possible set of instructions or google "Installing GDB with OS ________" for your particular operating system.
  
Windows:
  This will again be dependent on what coding environment you use and possibly can be difficult.  If you use MinGW, the following may help: https://rpg.hamsterrepublic.com/ohrrpgce/GDB_on_Windows.

d3_tooltips
===========

Utility to export d3 items stats to a more user-friendly format

YouTube Demo : http://youtu.be/kqZ0Jgw7tOo

Install
-------

<a href="http://www.microsoft.com/en-us/download/details.aspx?id=5555">Microsoft Visual C++ Redistributable Package</a> is needed to run compiled binaries (release/D3_ToolTips.exe)

D3_ToolTips also uses QT and SQLite, but dynamics libraries are embedded.

Compile
----------

In order to compile it smoothly you will need :
 - QT (4.1.8 desktop) : http://qt.nokia.com/downloads
 - MSVC++ 2010 (Express Edition will do the job) : http://www.microsoft.com/visualstudio/en-us/products/2010-editions/express-iso

You can use MinGW if you want. (with a few fairly minor technical adjustments).

Changelog
---------
 - v0.2
  - Memory scan improvements, taking care of segmentation
  - New ToolTips support : D3_SOCKET_0, D3_SOCKET_1, D3_SOCKET_2, D3_SOCKET_COST, D3_ITEM_LEVEL, D3_FLAVOR, D3_SET_ITEM, D3_ENHANCEMENT, D3_INSTRUCTION
  - Export improvements (threaded and loop based)
  - Minor corrections
 - v0.1
  - Initial commit, projet started
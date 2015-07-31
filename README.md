
Amazon Game Circle wrapper for Marmalade Quick
==============================================

This is a 1:1 wrapper for the s3eGaemCircle C extension so that you
can use it from Marmalade Quick Lua code. Functionality and usage is the
same as the C++ version.

It's supported on Android.

Notes:

- All the paths here are relative to the root folder of your installed
  Marmalade SDK.

NB: With Marmalade 7.8.0, this extension requires you to mod a file in the
Quick engine as well. Copy the contents of engine_mods over the root Marmalade
SDK (e.g. C:/Marmalade/7.8) This will be built into the engine when you run
build_quick_prebuilt.bat (see "Setup..." below) This should no longer be needed
in 7.8.1 (TBC whether it makes that release)


Prerequisites
-------------

1. Marmalade SDK 7.7 or newer for:
   
   - The latest C Game Circle extension
   - Quick tooling upgrades (in 7.7)

2. Put this project on Marmalade search paths:

  Easiest option is to keep the project in you main github folder. Then, if you
  haven't already, add your github root to the global search by putting the
  following in < Marmalade >/s3e/s3e-default.mkf:

        options { module_path="path/to/my/github/projects/root" }

  Multiple Marmalade installs can pick up your project then.
  
  If you dont have a main github folder, you can add just this project:
  
        options { module_path="path/to/QGameCircle" }


Setup: Add and build this wrapper into Quick
--------------------------------------------

1. Edit quick/quickuser_tolua.pkg and add this new line:

        $cfile "path/to/QGameCircle/QGameCircle.h"

2. Edit quick/quickuser.mkf and add QGameCircle to the 'subprojects'
   block:

        subprojects
        {
            QGameCircle
        }
   
3. Run quick/quickuser_tolua.bat to generate Lua bindings.

4. Rebuild the Quick binaries by running the script(s):
   quick/build_quick_prebuilt.bat etc.

   
Using Game Circle in your app
--------------------------------------

1. Add the C++ extension to your app's .mkb file:

        subproject s3eGameCircle

   This bundles platform specific extension libraries (jar, lib etc) in your app
   at deploy time. Forgetting this means all calls will quietly fail!

2. Use the Lua APIs in your app!
   
   The Lua functions largely match the C++ ones in s3eGameCircle.h.
   
   Make sure you use gameCircle.xxx() and not gameCircle:xxx()!

The functions are all pretty simple. They either submit score/achievements,
load data asynchronously, or display a GUI.

Typically you would sign in, make a call to load a leaderboard/achievements,
then show the relevant GUI once loaded.
   
## Events

Quick events are provided to match the C callbacks from s3eGameCircle.
Quick Game Circle uses a single event, also called "gameCircle", which
is registered with the usual system:addEventListener function. The "type" value
of the table passed to your listener indicates which of the callbacks is being.

The types are:

TODO: Fill out event info. These will be very similar to Google Game Services.

------------------------------------------------------------------------------------------
(C) 2015 Nick Smith.

All code is provided under the MIT license unless stated otherwise:

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

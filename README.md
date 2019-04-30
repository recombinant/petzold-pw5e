### Work in progress. 

- Examples up to and including Chapter 18 are compiling and "running". 
- Some examples in *"Chapter 16 The Palette Manager"* expect 256 bit color 
  displays - hardware that was ubiquitous in the Window98 era. 

-------------------------------------------------------------------------------

# petzold-pw5e
Revisited C source code for Charles Petzold's Programming Windows 5th Edition ISBN-10 157231995X

The 5th edition Programming Windows was published in 1998 in the era of Windows 98,
 Windows NT and Internet Explorer 4. There is a 6th edition, but this deals with
 later Windows technologies - the 5th edition was the last to deal with purely C
 programming. Many programmers learnt and many are learning Windows Programming
 from this huge tome and its various editions. An excellent work.

Contents of this repository
---------------------------

This projects is being tweaked to use CMake. This works with both
- Microsoft Visual Studio 2019 
- JetBrains CLion with MinGW


Updating C source code
----------------------

**As of 2019 Visual Studio 2019 Community Edition is being used.**

- Rename the chapter folder and project folder to improve lexicographical
   sorting and order the projects within a chapter as per *the book*.
- Reformat code with *Ctrl-K Ctrl-D*
- Windows 98 is no longer supported - remove any `#define WINVER` and
   `GetVersion()`
- Apply any errata as per various errata references on the interweb. Jason Doucette's
   errata are referred to on Charles Petzold's own website and are well explained.
   There is another set of errata at *Computer Science Lab*.
- Replace `WinMain` with `_tWinMain` using `PTSTR` for `szCommand`
- There are no long pointers. 16 bit Windows is dead. Replace `LPTSTR` with `PTSTR` usw.
- Use safe versions of functions susceptible to buffer overrun e.g. Replace
   `_vsntprintf()` with `_vsntprintf_s()`
- Annotate functions with Microsoft source-code annotation language (SAL)
- (void)fn for functions where return value is ignored.
- Apply `#define STRICT` and `#define WIN32_LEAN_AND_MEAN`
- `#include <windows.x>` and use its macros where suitable. `Edit_GetSel()`
   being an example of one to avoid.

Notes
-----

There are limited links to websites or internet sources on this page. Links can
 go stale. A search engine is your friend.
# petzold-pw5e
Revisited C source code for Charles Petzold's Programming Windows 5th Edition ISBN-10 157231995X

The 5th edition Programming Windows was published in 1998 in the era of Windows 98,
 Windows NT and Internet Explorer 4. There is a 6th edition, but this deals with
 later Windows technologies - the 5th edition was the last to deal with purely C
 programming. Many programmers learnt and many are learning Windows Programming
 from this huge tome and its various editions. An excellent work.

Purpose of this repository
--------------------------

This repository was created to give the author working code to transliterate into
 the rust language - the rusty fruit of this exercise being placed in the
 petzold-pw5e-rs repository.

Contents of this repository
---------------------------

The initial commit was the source code roughly "as is" from the original
 distribution from the book's website.

- The Microsoft *.dep* *.dsp* *.dsw* & *.mak* files and the *Debug* and *Release*
  folders were omitted.
- Some of the files were renamed to
  - improve lexicographical sorting
  - avoid duplicate names
- Duplicate files were eliminated. Using the C compiler and the development
  environment allows files to be used across multiple projects.

Updating C source code
----------------------

Using Visual Studio 2015 Community Edition.

- Rename the chapter folder and project folder to improve lexicographical
   sorting and order the projects within a chapter as per *the book*.
- Reformat code with *Ctrl-K Ctrl-D*
- Windows 98 is no longer supported - remove any `#define WINVER` and
   `GetVersion()`
- Apply any errata as per various errata refernces on the interweb. Jason Doucette's
   errata are referred to on Charles Petzold's own website and are well explained.
   There is another set of errata at *Computer Science Lab*.
- Replace `WinMain` with `_tWinMain` using `PTSTR` for `szCommand`
- There are no long pointers. 16 bit Windows is dead. Replace `LPTSTR` with `PTSTR` usw.
- Use safe versions of functions susceptible to buffer overrun e.g. Replace
   `_vsntprintf()` with `_vsntprintf_s()`
- Annote Function Parameters and Return Values (a Microsoft thing)
- (void)fn for functions where return value is ignored.
- Apply `#define STRICT` and `#define WIN32_LEAN_AND_MEAN`
- `#include <windows.x>` and use its macros where suitable. `Edit_GetSel()`
   being an example of one to avoid.

Notes
-----

There are no links to any websites or internet sources on this page. Links can
 go stale. A search engine is your friend.
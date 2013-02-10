// Copyright (c) 2000 Mike Morearty
// Original code and docs: http://www.morearty.com/code/strprintf

#ifndef _STRPRINTF_H_
#define _STRPRINTF_H_

#include <afx.h>

//
// This function makes it easy to elegantly create a temporary string
// and pass it as an argument, without having to explicitly create a
// temporary variable.  For example, you can combine these three lines...
//		CString s;
//		s.Format(format_string, args ...);
//		AfxMessageBox(s);
// ... into this one line:
//		AfxMessageBox( StrPrintf(format_string, args ...) );
//
CString StrPrintf(LPCTSTR lpszFormat, ...)
{
	CString s;

	va_list argList;
	va_start(argList, lpszFormat);
	s.FormatV(lpszFormat, argList);
	return s;
}

#endif // _STRPRINTF_H_

/*  minIni - Multi-Platform INI file parser, suitable for embedded systems
 *
 *  Copyright (c) CompuPhase, 2008-2012
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 *
 *  Version: $Id: minIni.h 44 2012-01-04 15:52:56Z thiadmer.riemersma@gmail.com $
 */
#ifndef _MININI_H_
#define _MININI_H_

//#include "minGlue.h"

/*
#if (defined _UNICODE || defined __UNICODE__ || defined UNICODE) && !defined MININI_ANSI
  #include <tchar.h>
  #define MINICHAR TCHAR
#else
  // force TCHAR to be "char", but only for minIni
  #define MINICHAR char
#endif
*/


typedef char MINICHAR;


#if !defined INI_BUFFERSIZE
  #define INI_BUFFERSIZE  1024
#endif

#if defined __cplusplus
  extern "C" {
#endif

int   ini_getbool(const MINICHAR *Section, const MINICHAR *Key, int DefValue, const MINICHAR *Filename);
long  ini_getl(const MINICHAR *Section, const MINICHAR *Key, long DefValue, const MINICHAR *Filename);
int   ini_gets(const MINICHAR *Section, const MINICHAR *Key, const MINICHAR *DefValue, MINICHAR *Buffer, int BufferSize, const MINICHAR *Filename);
int   ini_getsection(int idx, MINICHAR *Buffer, int BufferSize, const MINICHAR *Filename);
int   ini_getkey(const MINICHAR *Section, int idx, MINICHAR *Buffer, int BufferSize, const MINICHAR *Filename);

#if defined INI_REAL
INI_REAL ini_getf(const MINICHAR *Section, const MINICHAR *Key, INI_REAL DefValue, const MINICHAR *Filename);
#endif

#if !defined INI_READONLY
int   ini_putl(const MINICHAR *Section, const MINICHAR *Key, long Value, const MINICHAR *Filename);
int   ini_puts(const MINICHAR *Section, const MINICHAR *Key, const MINICHAR *Value, const MINICHAR *Filename);
#if defined INI_REAL
int   ini_putf(const MINICHAR *Section, const MINICHAR *Key, INI_REAL Value, const MINICHAR *Filename);
#endif
#endif /* INI_READONLY */

#if !defined INI_NOBROWSE
typedef int (*INI_CALLBACK)(const MINICHAR *Section, const MINICHAR *Key, const MINICHAR *Value, const void *UserData);
int  ini_browse(INI_CALLBACK Callback, const void *UserData, const MINICHAR *Filename);
#endif /* INI_NOBROWSE */

#if defined __cplusplus
  }
#endif


#if defined __cplusplus

#if defined __WXWINDOWS__
	#include "wxMinIni.h"
#else
  #include <string>

  /* The C++ class in minIni.h was contributed by Steven Van Ingelgem. */
  class minIni
  {
  public:
    minIni(const std::string& filename) : iniFilename(filename)
      { }

    bool getbool(const std::string& Section, const std::string& Key, bool DefValue=false) const
      { return ini_getbool(Section.c_str(), Key.c_str(), int(DefValue), iniFilename.c_str()) != 0; }

    long getl(const std::string& Section, const std::string& Key, long DefValue=0) const
      { return ini_getl(Section.c_str(), Key.c_str(), DefValue, iniFilename.c_str()); }

    int geti(const std::string& Section, const std::string& Key, int DefValue=0) const
      { return static_cast<int>(this->getl(Section, Key, long(DefValue))); }

    std::string gets(const std::string& Section, const std::string& Key, const std::string& DefValue="") const
      {
        char buffer[INI_BUFFERSIZE];
        ini_gets(Section.c_str(), Key.c_str(), DefValue.c_str(), buffer, INI_BUFFERSIZE, iniFilename.c_str());
        return buffer;
      }

    std::string getsection(int idx) const
      {
        char buffer[INI_BUFFERSIZE];
        ini_getsection(idx, buffer, INI_BUFFERSIZE, iniFilename.c_str());
        return buffer;
      }

    std::string getkey(const std::string& Section, int idx) const
      {
        char buffer[INI_BUFFERSIZE];
        ini_getkey(Section.c_str(), idx, buffer, INI_BUFFERSIZE, iniFilename.c_str());
        return buffer;
      }

#if defined INI_REAL
    INI_REAL getf(const std::string& Section, const std::string& Key, INI_REAL DefValue=0) const
      { return ini_getf(Section.c_str(), Key.c_str(), DefValue, iniFilename.c_str()); }
#endif

#if ! defined INI_READONLY
    bool put(const std::string& Section, const std::string& Key, long Value) const
      { return ini_putl(Section.c_str(), Key.c_str(), Value, iniFilename.c_str()) != 0; }

    bool put(const std::string& Section, const std::string& Key, int Value) const
      { return ini_putl(Section.c_str(), Key.c_str(), (long)Value, iniFilename.c_str()) != 0; }

    bool put(const std::string& Section, const std::string& Key, bool Value) const
      { return ini_putl(Section.c_str(), Key.c_str(), (long)Value, iniFilename.c_str()) != 0; }

    bool put(const std::string& Section, const std::string& Key, const std::string& Value) const
      { return ini_puts(Section.c_str(), Key.c_str(), Value.c_str(), iniFilename.c_str()) != 0; }

    bool put(const std::string& Section, const std::string& Key, const char* Value) const
      { return ini_puts(Section.c_str(), Key.c_str(), Value, iniFilename.c_str()) != 0; }

#if defined INI_REAL
    bool put(const std::string& Section, const std::string& Key, INI_REAL Value) const
      { return ini_putf(Section.c_str(), Key.c_str(), Value, iniFilename.c_str()) != 0; }
#endif

    bool del(const std::string& Section, const std::string& Key) const
      { return ini_puts(Section.c_str(), Key.c_str(), 0, iniFilename.c_str()) != 0; }

    bool del(const std::string& Section) const
      { return ini_puts(Section.c_str(), 0, 0, iniFilename.c_str()) != 0; }
#endif

  private:
    std::string iniFilename;
  };

#endif /* __WXWINDOWS__ */
#endif /* __cplusplus */

#endif /* _MININI_H_ */

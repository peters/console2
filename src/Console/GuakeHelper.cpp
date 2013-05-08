#include "stdafx.h"
#include <boost/filesystem.hpp>
#include "GuakeHelper.h"

using Console2::TerminalType;
using Console2::GuakeHelper;

namespace fs = boost::filesystem;

std::string GuakeHelper::GetFullPath(const std::string& filename, const std::string& environmentVariable)
{
  
  fs::path path(filename);
  if(!fs::exists(filename)) 
  {
    return fs::canonical(path).string();
  }

  char * env = std::getenv(environmentVariable.c_str());
  if(env != nullptr) {
    char *pch;
    pch = strtok(env, ";");
    while(pch != nullptr) {
       fs::path search(pch);
       fs::path fullpath = search / path;
       if(fs::exists(fullpath)) {
         return fullpath.string();
       }
    }
    return nullptr;
  }
};

std::string GuakeHelper::GetShellPath(TerminalType terminalType) 
{
  switch(terminalType) 
  {
  case TerminalType::WindowsShell:
    return GetFullPath("cmd.exe", "PATH");
  case TerminalType::PowerShell:
    return GetFullPath("powershell.exe", "PATH");
  case TerminalType::Bash:
    return GetFullPath("sh.exe", "PATH");
  case TerminalType::Mingw:
    return GetFullPath("msys.bat", "PATH");
  case TerminalType::Github:
    TCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPath(NULL, 
                                 CSIDL_LOCAL_APPDATA, 
                                 NULL, 
                                 0, 
                                 szPath))) 
    {
       fs::path location(szPath);
       fs::path github("github");
       fs::path fullpath = location / github;
       if(fs::is_directory(fullpath)) 
       {
         return fullpath.string();
       }
    }
    return nullptr;
  default:
    return nullptr;
  }
};
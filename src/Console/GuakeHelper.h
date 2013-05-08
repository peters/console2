#pragma once

namespace Console2 {

  enum TerminalType {
    WindowsShell,
    PowerShell,
    Bash,
    Mingw,
    Github
  };

	class GuakeHelper {
	public:
		static std::string GetFullPath(const std::string& filename, const std::string& environmentVariable);
    static std::string GetShellPath(TerminalType terminalType);
	};
};
#include <iostream>
#include <GitVersion.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Open|Phantasy Server" << std::endl;
	std::cout << "BUILD INFORMATION" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "* Build version: " << GIT_BUILD_VERSION << std::endl;
	std::cout << "* Hash: " << GIT_COMMITHASH << std::endl;
	std::cout << "* Commit date: " << GIT_COMMITTERDATE << std::endl;
	std::cout << "* Branch: " << GIT_BRANCH << std::endl;
	std::cout << "* Tag: " << GIT_TAG_NAME << std::endl;

	return 0;
}


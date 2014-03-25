#include <Daemon.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	OPS::Daemon Server;

	if( Server.Initialise( "openphantasy" ) != 0 )
	{
		return 1;
	}

	return Server.Execute( );
}


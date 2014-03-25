#include <Daemon.hpp>
#include <Error.hpp>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <cstdlib>

namespace OPS
{
	Daemon::Daemon( )
	{
	}

	Daemon::~Daemon( )
	{
		if( m_pLogPrefix )
		{
			delete [ ] m_pLogPrefix;
			m_pLogPrefix = nullptr;
		}
	}

	int Daemon::Initialise( const char *p_pLogPrefix )
	{
		size_t PrefixLength = strlen( p_pLogPrefix ) + 1;
		m_pLogPrefix = new char[ PrefixLength ];
		strncpy( m_pLogPrefix, p_pLogPrefix, PrefixLength - 1 );
		m_pLogPrefix[ PrefixLength ] = '\0';
		
		umask( 0 );

		struct rlimit FileLimit;

		if( getrlimit( RLIMIT_NOFILE, &FileLimit ) < 0 )
		{
			Error::Quit( "Can't get file limit\n" );

			return 1;
		}

		pid_t PID;

		if( ( PID = fork( ) ) < 0 )
		{
			Error::Quit( "Can't fork\n" );
		}
		else if( PID != 0 )
		{
			exit( 0 );
		}

		setsid( );

		struct sigaction Signals;

		Signals.sa_handler = SIG_IGN;
		sigemptyset( &Signals.sa_mask );
		Signals.sa_flags = 0;

		if( sigaction( SIGHUP, &Signals, NULL ) < 0 )
		{
			Error::Quit( "Can't ignore SIGHUP\n" );
		}
		if( ( PID = fork( ) ) < 0 )
		{
			Error::Quit( "Can't fork\n" );
		}
		else if( PID != 0 )
		{
			exit( 0 );
		}

		if( chdir( "/" ) < 0 )
		{
			Error::Quit( "Can't change directory to \"/\"\n" );
		}

		if( FileLimit.rlim_max == RLIM_INFINITY )
		{
			FileLimit.rlim_max = 1024;
		}

		for( unsigned int i = 0; i < FileLimit.rlim_max; ++i )
		{
			close( i );
		}

		int FileDescriptor[ 3 ];

		FileDescriptor[ 0 ] = open( "/dev/null", O_RDWR );
		FileDescriptor[ 1 ] = dup( 0 );
		FileDescriptor[ 2 ] = dup( 0 );

		openlog( m_pLogPrefix, LOG_CONS, LOG_DAEMON );

		if( FileDescriptor[ 0 ] != 0 ||
			FileDescriptor[ 1 ] != 1 ||
			FileDescriptor[ 2 ] != 2 )
		{
			syslog( LOG_ERR, "Unexpected file descriptors %d %d %d",
				FileDescriptor[ 0 ], FileDescriptor[ 1 ],
				FileDescriptor[ 2 ] );
			exit( 1 );
		}

		syslog( LOG_INFO, "Server initialised" );

		return 0;
	}

	int Daemon::Execute( )
	{
		sleep( 10 );

		syslog( LOG_INFO, "Server exiting..." );

		return 0;
	}
}


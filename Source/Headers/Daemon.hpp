#ifndef __OPS_DAEMON_HPP__
#define __OPS_DAEMON_HPP__

namespace OPS
{
	class Daemon
	{
	public:
		Daemon( );
		~Daemon( );

		int Initialise( const char *p_pLogPrefix );

		int Execute( );

		bool AlreadyRunning( );

	private:
		Daemon( const Daemon & );
		Daemon &operator=( const Daemon & );

		int LockFile( int p_FileDescriptor );

		char *m_pLogPrefix;
		char *m_pLockFileName;
	};
}

#endif // __OPS_DAEMON_HPP__


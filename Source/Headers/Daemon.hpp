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

	private:
		Daemon( const Daemon & );
		Daemon &operator=( const Daemon & );

		char *m_pLogPrefix;
	};
}

#endif // __OPS_DAEMON_HPP__


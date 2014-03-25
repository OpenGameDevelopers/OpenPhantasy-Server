#include <Error.hpp>
#include <Common.hpp>
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace OPS
{
	namespace Error
	{
		void Quit( const char *p_pFormat, ... )
		{
			va_list Args;

			va_start( Args, p_pFormat );
			OPS::Error::Print( 0, 0, p_pFormat, Args );
			va_end( Args );
			exit( 1 );
		}

		void Print( int p_ErrorFlag, int p_Error, const char *p_pFormat,
			va_list p_Args )
		{
			char Buffer[ OPS::MaximumLineSize ];

			vsnprintf( Buffer, OPS::MaximumLineSize, p_pFormat, p_Args );

			if( p_ErrorFlag )
			{
				snprintf( Buffer + strlen( Buffer ),
					OPS::MaximumLineSize - strlen( Buffer ), ": %s",
					strerror( p_Error ) );
			}

			strcat( Buffer, "\n" );
			fflush( stdout );
			fputs( Buffer, stderr );
			fflush( NULL );
		}
	}
}


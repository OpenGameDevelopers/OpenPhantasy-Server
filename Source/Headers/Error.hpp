#ifndef __OPS_ERROR_HPP__
#define __OPS_ERROR_HPP__

#include <cstdarg>

namespace OPS
{
	namespace Error
	{
		void Quit( const char *p_pFormat, ... );

		void Print( int p_ErrorFlag, int p_Error, const char *p_pFormat,
			va_list p_Args );
	}
}

#endif // __OPS_ERROR_HPP__


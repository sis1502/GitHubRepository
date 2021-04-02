#pragma once

#include "PubUtil/BaseDef.h"

namespace Sis_
{
	inline string CheckIP(const char *ip)
	{
		if (ip == nullptr || strlen(ip) == 0)
		{
			return string("null string");
		}

		struct in_addr addr;
		if (inet_pton(AF_INET, ip, &addr) > 0)
		{
			return string("ipv4");
		}
		else
		{
			struct in6_addr addr;
			if (inet_pton(AF_INET6, ip, &addr) > 0)
			{
				return string("ipv6");
			}
			else
			{
				return string("error srting");
			}
		}
	}
}
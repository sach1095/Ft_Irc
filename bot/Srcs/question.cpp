#include "../Includes/lib.hpp"

bool	quest_1(std::string buf)
{
	if (buf.find("salut") != std::string::npos || 
		buf.find("bonjour") != std::string::npos || 
		buf.find("coucou") != std::string::npos ||
		buf.find("Hello") != std::string::npos)
		return SUCCESS;
	return FAIL;
}

bool	quest_2(std::string buf)
{
	if (buf.find("salut") != std::string::npos || 
			buf.find("salut") != std::string::npos || 
			buf.find("salut") != std::string::npos)
		return SUCCESS;
	return FAIL;
}

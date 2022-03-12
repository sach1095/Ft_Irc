#include "../Includes/lib.hpp"

bool	quest_1(std::string buf)
{
	if (buf.find("salut") != std::string::npos || 
		buf.find("bonjour") != std::string::npos || 
		buf.find("coucou") != std::string::npos ||
		buf.find("Hello") != std::string::npos)
		return true;
	return false;
}

bool	quest_2(std::string buf)
{
	if (buf.find("ca va") != std::string::npos || 
		buf.find("comment va tu") != std::string::npos || 
		buf.find("bien ou bien") != std::string::npos)
		return true;
	return false;
}

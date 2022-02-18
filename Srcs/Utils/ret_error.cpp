#include "../../Includes/lib.hpp"

/*
* Fonction qui print le message d'erreur et quitte le programme.
*/
bool	ret_error(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}
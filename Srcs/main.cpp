#include "../Includes/lib.hpp"

/***************************************************************************************/
/***** Fonction qui a sert à écrire le message d'erreur et à quitter le programme. *****/
/***************************************************************************************/
static bool	ret_error(std::string str)
{
	std::cerr << str << std::endl;
	return 1;
}

/*****************/
/***** Main. *****/
/*****************/
int		main(int ac, char **av)
{
	if (ac != 3)
		return (ret_error("Number of arguments incorrect.\nPlease follow the rules ./ircserv <port> <password>."));

	t_data data;

	if (init_and_pars_data(&data ,av))
		return (FAIL);

	std::cout << "parseur :\n\nport = " << data.port << "\npassword = " << data.password << std::endl;
	return (SUCCESS);
}

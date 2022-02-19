#include "../../Includes/lib.hpp"

/*****************************************************************************************************/
/***** Initialisation de la structure qui a sert à stoker les données a vérifié leur format. *********/
/*****************************************************************************************************/
bool	pars_data(data<user *> &data, char **av)
{
	int	i = 0;

	while (av[1][i])
	{
		if (!isdigit(av[1][i]))
			return (ret_error("Port incorrect.\nPlease check your port again."));
		i++;
	}
	data.port = atoi(av[1]);
	if (av[2])
		data.password.assign(av[2], strlen(av[2]));
	else
		return (ret_error("Password cant be NULL.\nPlease try again witch another password."));
	return (SUCCESS);
}

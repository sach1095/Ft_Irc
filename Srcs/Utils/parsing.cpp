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

std::vector<std::string>	parse_cmd(std::string buf)
{
	char delimiter = ' ';
	std::vector<std::string> cmd;
	std::stringstream ss(buf);
	std::string line;
	while (std::getline(ss, line, delimiter))
	{
		while (line.back() == '\n' || line.back() == '\r')
			line.pop_back();
		cmd.push_back(line);
	}
	while (cmd.back() == "\n" || cmd.back() == "\r" || cmd.back() == " " || cmd.back().size() == 0)
		cmd.pop_back();
	if (cmd.size() > 2 && cmd[2][0] == ':')
		cmd[2] = &cmd[2][1];
	return cmd;
}

std::vector<std::string>	parse_msg(std::string buf)
{
	char delimiter = ' ';
	std::vector<std::string> cmd;
	std::stringstream ss(buf);
	std::string line;
	while (std::getline(ss, line, delimiter))
	{
		while (line.back() == '\n' || line.back() == '\r')
			line.pop_back();
		cmd.push_back(line);
	}
	while (cmd.back() == "\n" || cmd.back() == "\r" || cmd.back() == " " || cmd.back() == "#" || cmd.back().size() == 0)
		cmd.pop_back();
	if (cmd.size() > 2 && cmd[2][0] == ':')
	{
		cmd[2] = &cmd[2][1];
		for (size_t i = 3; i < cmd.size(); i++)
			cmd[2] = cmd[2] + " " + cmd[i];
	}
	return cmd;
}

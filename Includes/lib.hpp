# ifndef __LIB_HPP__
#define __LIB_HPP__

#pragma once

# define SUCCESS 0
# define FAIL 1

# include <iostream>
# include <memory>
# include <algorithm>
# include <array>
# include <iterator>
# include <ios>
# include <istream>
# include <iomanip>
# include <cstring>
# include <sstream>
# include <string>
# include <cctype>
# include <cstdlib>

typedef struct s_data
{
	int port;
	std::string password;
}t_data;

/* parsing.cpp */
bool	init_and_pars_data(t_data *data, char **av);


#endif

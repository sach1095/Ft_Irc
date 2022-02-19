#pragma once

# include <iostream>

class servException
{

public:

	class socket_failure : public std::exception
	{
		const char *what() const throw()
		{
			return "socket failed";
		}
	};

	class setsockopt_failure : public std::exception
	{
		const char *what() const throw()
		{
			return "setsockopt(SO_REUSEADDR) failed";
		}
	};

	class bind_failure : public std::exception
	{
		const char *what() const throw()
		{
			return "bind failed";
		}
	};

	class listen_failure : public std::exception
	{
		const char *what() const throw()
		{
			return "listen failed";
		}
	};

	class accept_failure : public std::exception
	{
		const char *what() const throw()
		{
			return "accept failed";
		}
	};

	class pass_mismatch : public std::exception
	{
		const char *what() const throw()
		{
			return ":server 464 pass :Password incorrect\r\n";
		}
	};

	class pass_param : public std::exception
	{
		const char *what() const throw()
		{
			return ":server 461 pass :Not enough parameters\r\n";
		}
	};
};

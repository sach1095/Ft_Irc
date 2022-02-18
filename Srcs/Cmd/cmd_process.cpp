#include "../../Includes/lib.hpp"

void	check_Password(data<user *> &data , user *cursor, std::string buf)
{
	std::string command = buf.substr(0, buf.find(' '));

	if (command == "/pass")
	{
		command = "PASS";
		buf = buf.substr(1, buf.length() - 1);
	}

	if (command == "PASS" || command == "/pass")
	{
		std::string pass = buf.substr(5, buf.length() - 6);
		if (buf.find('\r') != buf.npos)
			pass = buf.substr(5, buf.length() - 7);

		if (pass == data.password)
		{
			cursor->setAccept("true");
			return ;
		}
		else
			throw servException::pass_mismatch();
	}
	else
		throw servException::pass_param();

}

void	cmd_process(data<user *> &data)
{
	int sd;
	int ret_read;
	int size_adress = sizeof(data.address);
	char	buffer[1024];

	for (std::vector<user *>::iterator it = data.users.begin(); it != data.users.end(); it++)
	{
		user *cursor = *it;
		sd = cursor->getSd();

		if (FD_ISSET(sd, &data.readfds))
		{
			if ((ret_read = read(sd, buffer, 1024)) == 0)
			{
				/*
				* if someone is disconnected, get his details and print hem.
				*/
				getpeername(sd, (struct sockaddr*)&data.address, (socklen_t*)&data.address);
				std::cout << "User disconnected, ip " << inet_ntoa(data.address.sin_addr) << " port " << ntohs(data.address.sin_port) << std::endl;
				/*
				* close the socket and set is as 0 in list.
				*/
				close(sd);
				sd = 0;
				/*
				* delete the user from the list.
				*/
				delete_user(data, cursor);
				return ;
			}
			else
			{
				buffer[ret_read] = '\0';
				if (buffer[ret_read - 1] != '\n')
				{
					cursor->setBuffer(cursor->getBuffer() + buffer);
					return;
				}
				if (cursor->getBuffer().empty())
					cursor->setBuffer(buffer);
				else
					cursor->setBuffer(cursor->getBuffer() + buffer);
				std::cout << "===BUFFER===\n|" << cursor->getBuffer() << "|\n";
				std::string command = cursor->getBuffer().substr(0, cursor->getBuffer().find(' '));
				if (cursor->getAccept() == true)
				{
					// pars.parse(cursor->getBuffer(), cursor);
					std::cout << "need do pars" << std::endl;
				}
				else
				{
					try
					{
						check_Password(data, cursor, cursor->getBuffer());
					}
					catch(const std::exception& e)
					{
						send(cursor->getSd(), e.what(), std::strlen(e.what()), 0);
						close(sd);
						sd = 0;
						delete_user(data, cursor);
						return ;
					}
				}
				cursor->cleanBuffer();
			}
		}
	}
}

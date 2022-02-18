#include "../../Includes/lib.hpp"

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
				std::cout << "test buffer 0 : " << buffer << std::endl;
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
				std::cout << "test buffer 1 : " << buffer << std::endl;
				cursor->cleanBuffer();
			}
		}
	}
}

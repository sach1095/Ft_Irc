#include "../Includes/lib.hpp"

static std::vector<std::string>	copy_parse_cmd(std::string buf)
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

bool	quest_3(std::string buf)
{
	if (buf.find("waza") != std::string::npos ||
			buf.find("WAZA") != std::string::npos ||
			buf.find("waaza") != std::string::npos ||
			buf.find("WAAZA") != std::string::npos)
		return true;
	return false;
}

bool	quest_4(std::string buf)
{
	if (buf.find("quoi de neuf") != std::string::npos ||
			buf.find("quoi de beau") != std::string::npos ||
			buf.find("que fait tu") != std::string::npos)
		return true;
	return false;
}

bool	quest_5(std::string buf)
{
	if (buf.find("vim ou vscode") != std::string::npos ||
			buf.find("vscode ou vim") != std::string::npos)
		return true;
	return false;
}

bool	quest_6(std::string buf)
{
	if (buf.find("quelle heure est-il") != std::string::npos ||
			buf.find("ta l'heure") != std::string::npos ||
			buf.find("il est quelle heure") != std::string::npos)
		return true;
	return false;
}

bool	quest_7(std::string buf)
{
	if (buf.find("quelle est la date") != std::string::npos ||
			buf.find("et la date") != std::string::npos ||
			buf.find("la date") != std::string::npos ||
			buf.find("il est quelle heure") != std::string::npos)
		return true;
	return false;
}

bool	quest_8(Bot &bot, std::string buf)
{
	std::vector<std::string> cmd = copy_parse_cmd(buf);
	if (buf.find("merde") != std::string::npos ||
		buf.find("connard") != std::string::npos ||
		buf.find("conard") != std::string::npos ||
		buf.find("salo") != std::string::npos ||
		buf.find("encule") != std::string::npos)
		{
			bot.to_ban = &cmd[0][1];
			return true;
		}
	return false;
}

bool	quest_9(std::string buf)
{
	if (buf.find("non c'est trop") != std::string::npos ||
			buf.find("trop") != std::string::npos)
		return true;
	return false;
}

bool	quest_10(std::string buf)
{
	if (buf.find("ou sont tes lunette") != std::string::npos)
		return true;
	return false;
}

bool	quest_11(std::string buf)
{
	if (buf.find("prepare moi mon cafe") != std::string::npos)
		return true;
	return false;
}

bool	quest_12(std::string buf)
{
	if (buf.find("pas de bra") != std::string::npos)
		return true;
	return false;
}

bool	quest_13(std::string buf)
{
	if (buf.find("ya du soleil") != std::string::npos)
		return true;
	return false;
}

bool	quest_14(Bot &bot, std::string buf)
{
	std::vector<std::string> cmd = copy_parse_cmd(buf);
	if (buf.find("fada") != std::string::npos ||
		buf.find("je suis marseillais") != std::string::npos ||
		buf.find("peut cher") != std::string::npos ||
		buf.find("ofan") != std::string::npos ||
		buf.find("tarpin") != std::string::npos ||
		buf.find("allez l'OM") != std::string::npos)
	{
		bot.to_ban = &cmd[0][1];
		return true;
	}
	return false;
}

bool	quest_15(std::string buf)
{
	if (buf.find("chou rabibi") != std::string::npos)
		return true;
	return false;
}


bool	quest_16(std::string buf)
{
	if (buf.find("tu vote qui") != std::string::npos ||
		buf.find("tu va vote qui") != std::string::npos)
		return true;
	return false;
}

bool	quest_17(std::string buf)
{
	if (buf.find("votera-tu ?") != std::string::npos ||
		buf.find("tu vote ?") != std::string::npos)
		return true;
	return false;
}

bool	quest_18(std::string buf)
{
	if (buf.find("colise") != std::string::npos ||
		buf.find("esti") != std::string::npos)
		return true;
	return false;
}

bool	quest_19(std::string buf)
{
	if (buf.find("il on des tete de") != std::string::npos)
		return true;
	return false;
}
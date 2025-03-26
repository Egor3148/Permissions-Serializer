// 

#include "../inc/perms_serializer.h"

#include "perms_manip.h"
#include "encrypter.h"

#include <fstream>
#include <string>


int serialize(std::string* inputPath, std::string* password)
{
	UniversalPermissions perms = getPermissions(*inputPath);

	std::ifstream in(*inputPath, std::ios::binary);
	std::ofstream out(*inputPath + ".dat", std::ios::binary);

	if (!in || !out) 
	{
		return 1;
	}
	
	out << perms.code();
	char buf;
	while (in.read(&buf, sizeof(buf)))
	{
		out.write(&buf, sizeof(buf));
	}

	in.close();
	out.close();

	return encryptFile(*inputPath + ".dat", *inputPath + ".dat" + "enc", *password);
	// return 0;
}


int deserialize(std::string* inputPath, std::string* password)
{
	int retCode = 0;

	std::string decryptPath = (*inputPath).substr(0, (*inputPath).length() - 3);
	std::string outputPath = decryptPath.substr(0, decryptPath.length() - 4);

	retCode = decryptFile(*inputPath, decryptPath, *password);
	if (retCode != 0) return retCode;

	std::ifstream in(decryptPath, std::ios::binary);
	std::ofstream out(outputPath, std::ios::binary);
	if (!in || !out) return 1;

	

	char buf;
	if (in >> buf)
	{
		UniversalPermissions perms;
		perms.parse(buf);
		setPermissions(outputPath, perms);
	}
	else return 0;

	while (in.read(&buf, sizeof(buf)))
	{
		out.write(&buf, sizeof(buf));
	}

	in.close();
	out.close();

	return 0;
}
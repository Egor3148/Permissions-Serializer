#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include <string>
#include<vector>

int encryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& password);

int decryptFile(const std::string& inputFilePath, const std::string& outputFilePath, const std::string& password);


#endif // ENCRYPTER_H

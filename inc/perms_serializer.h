#ifndef PERMS_SERIALIZER_H
#define PERMS_SERIALIZER_H


#include <string>

/**
* @brief Serializes file with permissions for current user
* @details Gets permissions, encrypts file, sets checksum, puts it all to .dat file
* @param inputPath [in]: input file path
* @param outputPath [in]: output file path
* @param password [in]: password for encryption, passed by pointer
* 
* @return [0] if OK
*		  [1] if invalid path
*         [2] if encrypting failed 
*/
int serialize(std::string* inputPath, std::string* password);

/**
* @brief Deserializes file with permissions for current user
* @details Decrypts .dat file, checks checksum, writes to file and sets permissions
* @param inputPath [in]: input file path
* @param outputPath [in]: output file path
* @param password [in]: password for encryption, passed by pointer
*
* @return [0] if OK
*		  [1] if invalid path
*         [2] if decrypting failed
*/
int deserialize(std::string* inputPath, std::string* password);

#endif // PERMS_SERIALIZER_H


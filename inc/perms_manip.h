#ifndef PERMS_MANIP_H
#define PERMS_MANIP_H


#include <string>


struct UniversalPermissions {

    const char READ_MASK = 1;
    const char WRITE_MASK = 1 << 1;
    const char EXEC_MASK = 1 << 2;

    bool read;
    bool write;
    bool execute;

    // Returns permissions compressed to 1 byte:
    // Read = code
    // Write = code << 1
    // Execute = code << 2 
    //
    char code();

    void parse(char code);
};


/*
* @brief Converts file permissions to universal structure for further serialization
*/
UniversalPermissions getPermissions(std::string filePath);


/*
* @brief Applies permissions from structure to file
*/
void setPermissions(std::string filePath, UniversalPermissions permissions);

#endif // PERMS_MANIP_H

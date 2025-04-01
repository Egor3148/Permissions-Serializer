// 
#include "../inc/perms_manip.h"

#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <aclapi.h>
#else
#include <sys/stat.h>
#endif
#include <iostream>

namespace fs = std::filesystem;


UniversalPermissions getPermissions(std::string filePath) {

    UniversalPermissions result;

#ifdef _WIN32
    PSID pOwnerSid = nullptr;
    PSECURITY_DESCRIPTOR pSD = nullptr;

    if (GetNamedSecurityInfo(filePath.c_str(), SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
        &pOwnerSid, nullptr, nullptr, nullptr, &pSD) != ERROR_SUCCESS) {
        std::cerr << "Failed to get security info\n";
        return result;
    }

    PACL pDacl = nullptr;
    BOOL daclPresent = FALSE;
    BOOL daclDefaulted = FALSE;
    if (!GetSecurityDescriptorDacl(pSD, &daclPresent, &pDacl, &daclDefaulted) || !daclPresent) {
        LocalFree(pSD);
        std::cerr << "Failed to get DACL\n";
        return result;
    }

    for (DWORD i = 0; i < pDacl->AceCount; ++i) {
        ACCESS_ALLOWED_ACE* pAce;
        if (!GetAce(pDacl, i, (LPVOID*)&pAce)) continue;

        if (EqualSid(&pAce->SidStart, pOwnerSid)) {
            result.read = (pAce->Mask & GENERIC_READ) || (pAce->Mask & FILE_GENERIC_READ);
            result.write = (pAce->Mask & GENERIC_WRITE) || (pAce->Mask & FILE_GENERIC_WRITE);
            result.execute = (pAce->Mask & GENERIC_EXECUTE) || (pAce->Mask & FILE_GENERIC_EXECUTE);
            break;
        }
    }

    LocalFree(pSD);
#else
    fs::perms permissions = std::filesystem::status(filePath).permissions();
    result.read = (permissions & fs::perms::owner_read) != fs::perms::none;
    result.write = (permissions & fs::perms::owner_write) != fs::perms::none;
    result.execute = (permissions & fs::perms::owner_exec) != fs::perms::none;
#endif
    return result;
}

void setPermissions(std::string filePath, UniversalPermissions permissions)
{
    fs::perms prms = fs::perms::none;
#ifdef _WIN32

    PSID pOwnerSid = nullptr;
    PSECURITY_DESCRIPTOR pSD = nullptr;

    if (GetNamedSecurityInfo(filePath.c_str(), SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION,
        &pOwnerSid, nullptr, nullptr, nullptr, &pSD) != ERROR_SUCCESS) {
        std::cerr << "Failed to get owner info\n";
        return;
    }

    DWORD dwAccessMask = 0;
    if (permissions.read) dwAccessMask |= GENERIC_READ | FILE_GENERIC_READ;
    if (permissions.write) dwAccessMask |= GENERIC_WRITE | FILE_GENERIC_WRITE;
    if (permissions.execute) dwAccessMask |= GENERIC_EXECUTE | FILE_GENERIC_EXECUTE;

    EXPLICIT_ACCESS ea;
    ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
    ea.grfAccessPermissions = dwAccessMask;
    ea.grfAccessMode = SET_ACCESS;
    ea.grfInheritance = NO_INHERITANCE;
    ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    ea.Trustee.TrusteeType = TRUSTEE_IS_USER;
    ea.Trustee.ptstrName = (LPTSTR)pOwnerSid;

    PACL pNewDacl = nullptr;
    if (SetEntriesInAcl(1, &ea, nullptr, &pNewDacl) != ERROR_SUCCESS) {
        LocalFree(pSD);
        std::cerr << "Failed to create new ACL\n";
        return;
    }

    DWORD dwResult = SetNamedSecurityInfo(
        filePath.data(),
        SE_FILE_OBJECT,
        DACL_SECURITY_INFORMATION,
        nullptr, nullptr, pNewDacl, nullptr);

    LocalFree(pNewDacl);
    LocalFree(pSD);

#else
    if (permissions.read) prms |= fs::perms::owner_read;
    if (permissions.write) prms |= fs::perms::owner_write;
    if (permissions.execute) prms |= fs::perms::owner_exec;

    fs::path path(filePath);
    fs::permissions(path, prms);
#endif
}

char UniversalPermissions::code()
{
    char result = 0;
    result = (read) ? result | 1 : result;
    result = (write) ? result | (1<<1) : result;
    result = (execute) ? result | (1<<2) : result;

    return result;
}

void UniversalPermissions::parse(char code)
{
    read = (code & READ_MASK) && READ_MASK;
    write = (code & WRITE_MASK) && WRITE_MASK;
    execute = (code & EXEC_MASK) && EXEC_MASK;
}

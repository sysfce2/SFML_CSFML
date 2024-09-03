////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2023 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <CSFML/Char32.hpp>
#include <CSFML/Network/Ftp.h>
#include <CSFML/Network/FtpStruct.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/System/String.hpp>

#include <cstring>


////////////////////////////////////////////////////////////
void sfFtpListingResponse_destroy(sfFtpListingResponse* ftpListingResponse)
{
    delete ftpListingResponse;
}


////////////////////////////////////////////////////////////
bool sfFtpListingResponse_isOk(const sfFtpListingResponse* ftpListingResponse)
{
    assert(ftpListingResponse);
    return ftpListingResponse->This.isOk();
}


////////////////////////////////////////////////////////////
sfFtpStatus sfFtpListingResponse_getStatus(const sfFtpListingResponse* ftpListingResponse)
{
    assert(ftpListingResponse);
    return static_cast<sfFtpStatus>(ftpListingResponse->This.getStatus());
}


////////////////////////////////////////////////////////////
const char* sfFtpListingResponse_getMessage(const sfFtpListingResponse* ftpListingResponse)
{
    assert(ftpListingResponse);
    return ftpListingResponse->This.getMessage().c_str();
}


////////////////////////////////////////////////////////////
size_t sfFtpListingResponse_getCount(const sfFtpListingResponse* ftpListingResponse)
{
    assert(ftpListingResponse);
    return ftpListingResponse->This.getListing().size();
}


////////////////////////////////////////////////////////////
const char* sfFtpListingResponse_getName(const sfFtpListingResponse* ftpListingResponse, size_t index)
{
    assert(ftpListingResponse);
    return ftpListingResponse->This.getListing()[index].c_str();
}


////////////////////////////////////////////////////////////
void sfFtpDirectoryResponse_destroy(sfFtpDirectoryResponse* ftpDirectoryResponse)
{
    delete ftpDirectoryResponse;
}


////////////////////////////////////////////////////////////
bool sfFtpDirectoryResponse_isOk(const sfFtpDirectoryResponse* ftpDirectoryResponse)
{
    assert(ftpDirectoryResponse);
    return ftpDirectoryResponse->This.isOk();
}


////////////////////////////////////////////////////////////
sfFtpStatus sfFtpDirectoryResponse_getStatus(const sfFtpDirectoryResponse* ftpDirectoryResponse)
{
    assert(ftpDirectoryResponse);
    return static_cast<sfFtpStatus>(ftpDirectoryResponse->This.getStatus());
}


////////////////////////////////////////////////////////////
const char* sfFtpDirectoryResponse_getMessage(const sfFtpDirectoryResponse* ftpDirectoryResponse)
{
    assert(ftpDirectoryResponse);
    return ftpDirectoryResponse->This.getMessage().c_str();
}


////////////////////////////////////////////////////////////
const char* sfFtpDirectoryResponse_getDirectory(const sfFtpDirectoryResponse* ftpDirectoryResponse)
{
    assert(ftpDirectoryResponse);
    return strdup(ftpDirectoryResponse->This.getDirectory().string().c_str());
}


////////////////////////////////////////////////////////////
const sfChar32* sfFtpDirectoryResponse_getDirectoryUnicode(const sfFtpDirectoryResponse* ftpDirectoryResponse)
{
    assert(ftpDirectoryResponse);
    sf::String str = sf::String(ftpDirectoryResponse->This.getDirectory().c_str());
    return copyToChar32(str);
}


////////////////////////////////////////////////////////////
void sfFtpResponse_destroy(sfFtpResponse* ftpResponse)
{
    delete ftpResponse;
}


////////////////////////////////////////////////////////////
bool sfFtpResponse_isOk(const sfFtpResponse* ftpResponse)
{
    assert(ftpResponse);
    return ftpResponse->This.isOk();
}


////////////////////////////////////////////////////////////
sfFtpStatus sfFtpResponse_getStatus(const sfFtpResponse* ftpResponse)
{
    assert(ftpResponse);
    return static_cast<sfFtpStatus>(ftpResponse->This.getStatus());
}


////////////////////////////////////////////////////////////
const char* sfFtpResponse_getMessage(const sfFtpResponse* ftpResponse)
{
    assert(ftpResponse);
    return ftpResponse->This.getMessage().c_str();
}


////////////////////////////////////////////////////////////
sfFtp* sfFtp_create()
{
    return new sfFtp;
}


////////////////////////////////////////////////////////////
void sfFtp_destroy(sfFtp* ftp)
{
    delete ftp;
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_connect(sfFtp* ftp, sfIpAddress server, unsigned short port, sfTime timeout)
{
    assert(ftp);

    std::optional<sf::IpAddress> SFMLServer = sf::IpAddress::resolve(server.address);

    if (!SFMLServer)
        return nullptr;

    return new sfFtpResponse(ftp->This.connect(*SFMLServer, port, sf::microseconds(timeout.microseconds)));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_loginAnonymous(sfFtp* ftp)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.login());
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_login(sfFtp* ftp, const char* name, const char* password)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.login(name ? name : "", password ? password : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_disconnect(sfFtp* ftp)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.disconnect());
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_keepAlive(sfFtp* ftp)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.keepAlive());
}


////////////////////////////////////////////////////////////
sfFtpDirectoryResponse* sfFtp_getWorkingDirectory(sfFtp* ftp)
{
    assert(ftp);
    return new sfFtpDirectoryResponse(ftp->This.getWorkingDirectory());
}


////////////////////////////////////////////////////////////
sfFtpListingResponse* sfFtp_getDirectoryListing(sfFtp* ftp, const char* directory)
{
    assert(ftp);
    return new sfFtpListingResponse(ftp->This.getDirectoryListing(directory ? directory : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_changeDirectory(sfFtp* ftp, const char* directory)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.changeDirectory(directory ? directory : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_parentDirectory(sfFtp* ftp)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.parentDirectory());
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_createDirectory(sfFtp* ftp, const char* name)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.createDirectory(name ? name : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_deleteDirectory(sfFtp* ftp, const char* name)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.deleteDirectory(name ? name : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_renameFile(sfFtp* ftp, const char* file, const char* newName)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.renameFile(file ? file : "", newName ? newName : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_deleteFile(sfFtp* ftp, const char* name)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.deleteFile(name ? name : ""));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_download(sfFtp* ftp, const char* remoteFile, const char* localPath, sfFtpTransferMode mode)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.download(remoteFile ? remoteFile : "",
                                                localPath ? localPath : "",
                                                static_cast<sf::Ftp::TransferMode>(mode)));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_upload(sfFtp* ftp, const char* localFile, const char* remotePath, sfFtpTransferMode mode, bool append)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.upload(localFile ? localFile : "",
                                              remotePath ? remotePath : "",
                                              static_cast<sf::Ftp::TransferMode>(mode),
                                              append));
}


////////////////////////////////////////////////////////////
sfFtpResponse* sfFtp_sendCommand(sfFtp* ftp, const char* command, const char* parameter)
{
    assert(ftp);
    return new sfFtpResponse(ftp->This.sendCommand(command ? command : "", parameter ? parameter : ""));
}
/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** LibHandle
*/

#include "LibLoader.hpp"
#include <dlfcn.h>

Arcade::LibLoader::LibHandle::LibHandle(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_NOW);
}

Arcade::LibLoader::LibHandle::~LibHandle()
{
    if (_handle)
        dlclose(_handle);
}

Arcade::LibLoader::LibHandle::operator bool() const
{
    return isSet();
}

bool Arcade::LibLoader::LibHandle::isSet() const
{
    return _handle != nullptr;
}

bool Arcade::LibLoader::LibHandle::symbolExists(const std::string &symbolName) const
{
    return (dlsym(_handle, symbolName.c_str()) != nullptr);
}

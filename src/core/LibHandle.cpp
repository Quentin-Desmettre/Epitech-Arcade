/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** LibHandle
*/

#include "LibHandle.hpp"
#include <dlfcn.h>

Arcade::Core::LibHandle::LibHandle(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE);
}

Arcade::Core::LibHandle::~LibHandle()
{
    if (_handle)
        dlclose(_handle);
}

Arcade::Core::LibHandle::operator bool() const
{
    return isSet();
}

bool Arcade::Core::LibHandle::isSet() const
{
    return _handle != nullptr;
}

bool Arcade::Core::LibHandle::symbolExists(const std::string &symbolName) const
{
    return (dlsym(_handle, symbolName.c_str()) != nullptr);
}

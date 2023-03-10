/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** LibLoader
*/

#include "LibLoader.hpp"
#include <stdexcept>

Arcade::LibLoader::LibType Arcade::LibLoader::getLibType(const std::string &path) const
{
    LibHandle handle(path);

    if (!handle)
        return (ERROR);
    if (handle.symbolExists(_createDisplaySymbol) && handle.symbolExists(_deleteDisplaySymbol))
        return (GRAPHICAL);
    if (handle.symbolExists(_createGameSymbol) && handle.symbolExists(_deleteGameSymbol))
        return (GAME);
    return (ERROR);
}

std::string Arcade::LibLoader::getLastError() const
{
    return (dlerror());
}

Arcade::IDisplay *Arcade::LibLoader::loadGraphicalLib(const std::string &path)
{
    return loadLib<IDisplay>(path, _createDisplaySymbol, _deleteDisplaySymbol);
}

void Arcade::LibLoader::unloadGraphicalLib(Arcade::IDisplay *lib)
{
    return unloadLib(static_cast<void *>(lib), _deleteDisplaySymbol);
}

Arcade::IGame *Arcade::LibLoader::loadGameLib(const std::string &path)
{
    return loadLib<IGame>(path, _createGameSymbol, _deleteGameSymbol);
}

void Arcade::LibLoader::unloadGameLib(Arcade::IGame *lib)
{
    return unloadLib(static_cast<void *>(lib), _deleteGameSymbol);
}

void Arcade::LibLoader::unloadLib(void *lib, const std::string &deleteSymbol)
{
    delete_t dtor;

    if (_handles.find(lib) == _handles.end()
    || !(dtor = _handles[lib]->fetchSymbol<delete_t>(deleteSymbol)))
        return;
    dtor(lib);
    _handles.erase(lib);
}

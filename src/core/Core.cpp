/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Core
*/

#include "Core.hpp"
#include "DirectoryLister.hpp"
#include <iostream>

Arcade::Core::LibraryNotLoadedException::LibraryNotLoadedException(const LibLoader &loader)
{
    _message = "Error: " + loader.getLastError();
}

const char *Arcade::Core::LibraryNotLoadedException::what() const noexcept
{
    return _message.c_str();
}

Arcade::Core::NoLibraryException::NoLibraryException(LibLoader::LibType type)
{
    if (type == LibLoader::GRAPHICAL)
        _message = "Error: No graphical library could be loaded.";
    else if (type == LibLoader::GAME)
        _message = "Error: No game library could be loaded.";
}

const char *Arcade::Core::NoLibraryException::what() const noexcept
{
    return _message.c_str();
}

Arcade::Core::Core(int ac, char **av):
    _libLoader(LibLoader::getInstance())
{
    LibLoader::LibType libType;
    DirectoryLister dirLister;
    std::string tmpFile;

    if (ac != 2)
        throw std::invalid_argument("Usage: ./arcade displayLib.so");

    try {
        dirLister.open("./lib", true);
    } catch (DirectoryLister::OpenFailureException &e) {
        std::cerr << "Error: ./lib: " << e.what() << std::endl;
        exit(84);
    }

    while (1) {
        try {
            tmpFile = dirLister.get();
        } catch (DirectoryLister::NoMoreFileException &e) {
            break;
        }

        if (tmpFile.size() < 3 || tmpFile.substr(tmpFile.size() - 3) != ".so")
            continue;
        libType = _libLoader.getLibType("./lib/" + tmpFile);
        if (libType == LibLoader::GRAPHICAL)
            _graphicalLibs.push_back(tmpFile);
        else if (libType == LibLoader::GAME)
            _gameLibs.push_back(tmpFile);
    }

    if (_graphicalLibs.empty())
        throw NoLibraryException(LibLoader::GRAPHICAL);
    if (_gameLibs.empty())
        throw NoLibraryException(LibLoader::GAME);
    if (!(_display = _libLoader.loadGraphicalLib(av[1])))
        throw LibraryNotLoadedException(_libLoader);
}

Arcade::Core::~Core()
{
    _libLoader.unloadGraphicalLib(_display);
    _libLoader.unloadGameLib(_game);
}

int Arcade::Core::run()
{
    return 0;
}

/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** DirectoryLister
*/

#include "DirectoryLister.hpp"
#include <string.h>

const char *DirectoryLister::OpenFailureException::what() const noexcept
{
    return strerror(errno);
}

const char *DirectoryLister::NoMoreFileException::what() const noexcept
{
    return "End of stream";
}

DirectoryLister::DirectoryLister() :
    _dir(nullptr),
    _streamValid(false),
    _hidden(false)
{
}

DirectoryLister::DirectoryLister(const std::string &folder, bool hidden) :
    DirectoryLister()
{
    open(folder, hidden);
}

DirectoryLister::~DirectoryLister()
{
    if (_dir)
        closedir(_dir);
}

bool DirectoryLister::open(std::string const& folder, bool hidden)
{
    // Close old dir
    if (_dir)
        closedir(_dir);

    // Open new dir
    _dir = opendir(folder.c_str());
    if (_dir == nullptr) {
        _streamValid = false;
        throw OpenFailureException();
    }
    _streamValid = true;
    _hidden = hidden;
    return true;
}

std::string DirectoryLister::get()
{
    if (!_streamValid)
        return "";
    while (true) {
        struct dirent *entry = readdir(_dir);
        if (entry == nullptr) { // End of stream
            throw NoMoreFileException();
        }
        if (entry->d_name[0] == '.' && !_hidden) // Hidden files, but not allowed
            continue;
        return entry->d_name;
    }
}

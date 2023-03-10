/*
** EPITECH PROJECT, 2022
** B-PDG-300-LIL-3-1-PDGD11-quentin.desmettre
** File description:
** DirectoryLister.hpp
*/

#pragma once
#include <dirent.h>
#include <exception>
#include <string>

class DirectoryLister {
public:
    class OpenFailureException: public std::exception
    {
    public:
        OpenFailureException() = default;
        ~OpenFailureException() = default;
        const char *what() const noexcept override;
    };
    class NoMoreFileException: public std::exception
    {
    public:
        NoMoreFileException() = default;
        ~NoMoreFileException() = default;
        const char *what() const noexcept override;
    };

    DirectoryLister();
    DirectoryLister(const std::string &folder, bool hidden);
    DirectoryLister(DirectoryLister &&other) = delete;
    DirectoryLister(const DirectoryLister &other) = delete;
    DirectoryLister &operator=(const DirectoryLister &other) = delete;

    ~DirectoryLister();

    bool open(std::string const& folder, bool hidden);
    std::string get();

private:
    DIR *_dir;
    bool _streamValid;
    bool _hidden;
};

/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Test_DirectoryLister
*/

#include "../../include/core/DirectoryLister.hpp"
#include "../doctest.h"
#include <vector>

#define check_hidden_files(dirLister) \
    dirLister.open("../../.github", true); \
    std::vector<std::string> files = { \
        dirLister.get(), \
        dirLister.get(), \
        dirLister.get(), \
        dirLister.get(), \
        dirLister.get() \
    }; \
    CHECK(std::find(files.begin(), files.end(), "workflows") != files.end());  \
    CHECK(std::find(files.begin(), files.end(), "commit_msg.sh") != files.end()); \
    CHECK(std::find(files.begin(), files.end(), "cpp_checker.py") != files.end()); \
    CHECK(std::find(files.begin(), files.end(), ".") != files.end()); \
    CHECK(std::find(files.begin(), files.end(), "..") != files.end()); \
    CHECK_THROWS_AS(dirLister.get(), DirectoryLister::NoMoreFileException);


#define check_normal_files(dirLister) \
    dirLister.open("../../.github", false); \
    std::vector<std::string> files = { \
        dirLister.get(), \
        dirLister.get(), \
        dirLister.get() \
    }; \
    CHECK(std::find(files.begin(), files.end(), "workflows") != files.end()); \
    CHECK(std::find(files.begin(), files.end(), "commit_msg.sh") != files.end()); \
    CHECK(std::find(files.begin(), files.end(), "cpp_checker.py") != files.end()); \
    CHECK_THROWS_AS(dirLister.get(), DirectoryLister::NoMoreFileException);


TEST_CASE("DirectoryLister")
{
    DirectoryLister dirLister;

    SUBCASE("OpenFailureException")
    {
        CHECK_THROWS_AS(dirLister.open("randombullshit", false), DirectoryLister::OpenFailureException);
    }
    SUBCASE("Reading files")
    {
        check_normal_files(dirLister);
    }
    SUBCASE("Reading hidden files")
    {
        check_hidden_files(dirLister);
    }

    SUBCASE("Open failure, open with constructor")
    {
        CHECK_THROWS_AS(DirectoryLister("randombullshit", false), DirectoryLister::OpenFailureException);
    }
    SUBCASE("Reading files, open with constructor")
    {
        DirectoryLister dirLister2("../../.github", false);
        check_normal_files(dirLister2);
    }
    SUBCASE("Reading hidden files, open with constructor")
    {
        DirectoryLister dirLister2("../../.github", true);
        check_hidden_files(dirLister2);
    }
    SUBCASE("Invalid stream")
    {
        CHECK_THROWS_AS(dirLister.open("randombullshit", false), DirectoryLister::OpenFailureException);
        CHECK(dirLister.get() == "");
    }
}

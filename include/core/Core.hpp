/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <vector>
#include <string>
#include <exception>
#include "LibLoader.hpp"
#include "IDisplay.hpp"
#include "test.hpp"

/**
 * @brief Namespace for the core of the arcade.
 * It contains classes that are used to load, manage, and communicate between libraries.
 */
namespace Arcade::Core {

    /**
     * @brief Class that handles the communication between the graphical and game libraries.
     */
    class Core {
        public:
            /**
             * @brief Exception thrown when no library is found.
             */
            class NoLibraryException: public std::exception {
                public:
                    explicit NoLibraryException(LibLoader::LibType type);
                    ~NoLibraryException() override = default;
                    const char *what() const noexcept override;
                private:
                    std::string _message;
            };

            /**
             * @brief Exception thrown when a library could not be loaded.
             */
            class LibraryNotLoadedException: public std::exception {
                public:
                    LibraryNotLoadedException();
                    ~LibraryNotLoadedException() override = default;
                    const char *what() const noexcept override;
                private:
                    std::string _message;
            };

            /**
             * @brief Constructor for the Core class.
             *
             * It will pre-load the available libraries.
             * Throws:
             *  - Arcade::Core::NoLibraryException if no game / graphics library is found.
             *  - Arcade::Core::LibraryNotLoadedException If the given library (av[1]) could not be loaded.
             * @param ac The number of arguments.
             * @param av The arguments.
             */
            Core(int ac, char **av);
            ~Core();

            /**
             * @brief Runs the arcade.
             *
             * This function will select (via a menu) the graphic/game lib to play with, and run the main loop.
             * @param libName
             * @return
             */
            int run(const std::string &libName);

        private:
            std::vector<std::string> _graphicalLibs, _gameLibs;
            LibLoader &_libLoader;
            IDisplay *_display;
            IGame *_game;
            bool _run, _isInMenu;
            int _selectedGraph, _selectedGame;
            ControlMap _controls;
            IDisplay *_testInterface;
            bool _testOnly;
            std::string _username;
            std::string _bestScoreUser;
            int _bestScore;

            void handleEvents(const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys);
            void exitGame();
            bool isKeyPressed(Key key, const std::vector<Key> &pressedKeys) const ;
            bool isKeyPressed(Key key, const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys) const;
            void loadSelectedLibrary();
            void loadGameLibrary(const std::string &name);
            void loadGraphicLibrary(const std::string &name);
            static void incrementIndex(int &index, std::size_t len, int dir);
            void fetchAvailableLibs();
            std::vector<Key> fetchPressedKeys();
            void changeUsername(const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys);
            void updateBestScore();
    };
};

#endif /* !CORE_HPP_ */

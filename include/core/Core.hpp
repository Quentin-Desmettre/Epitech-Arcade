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

namespace Arcade {
    class Core {
        public:
            class NoLibraryException: public std::exception {
                public:
                    NoLibraryException(LibLoader::LibType type);
                    ~NoLibraryException() = default;
                    const char *what() const noexcept override;
                private:
                    std::string _message;
            };
            class LibraryNotLoadedException: public std::exception {
                public:
                    LibraryNotLoadedException();
                    ~LibraryNotLoadedException() = default;
                    const char *what() const noexcept override;
                private:
                    std::string _message;
            };

            Core(int ac, char **av);
            ~Core();

            int run();

        private:
            std::vector<std::string> _graphicalLibs, _gameLibs;
            LibLoader &_libLoader;
            IDisplay *_display;
            IGame *_game;
            bool _run, _isInMenu;
            bool _isSelectingGame;
            std::size_t _selectedIndex;

            void handleMenuEvents(const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys);
            void exitGame();
            bool isKeyPressed(Key key, const std::vector<Key> &pressedKeys) const ;
            bool isKeyPressed(Key key, const std::vector<Key> &oldKeys, const std::vector<Key> &newKeys) const;
            void loadSelectedLibrary();
            void loadGameLibrary(const std::string &name);
            void loadGraphicLibrary(const std::string &name);
    };
};

#endif /* !CORE_HPP_ */

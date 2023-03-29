/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** LibLoader
*/

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_
#include <string>
#include "IDisplay.hpp"
#include "GameInterfaces.hpp"
#include "LibHandle.hpp"
#include <vector>
#include <memory>

typedef void *(*create_t)();
typedef void (*delete_t)(void *);

namespace Arcade::Core {
    /**
     * @brief The LibLoader for arcade-like libraries.
     * @note This class is a singleton, and may be accessed using the getInstance() method.
     */
    class LibLoader {
        public:
            /**
             * @brief The type of the library
             */
            enum LibType {
                GRAPHICAL,
                GAME,
                ERROR
            };

            /**
             * @brief Gets the library loader.
             * @note This handle is unique, and will be destroyed when the program is exited.
             * @return The library loader.
             */
            static LibLoader &getInstance() {
                static LibLoader instance;
                return instance;
            }
            ~LibLoader() = default;

            /**
             * @brief Gets the type of the dynamic library.
             * @param path The path to the dynamic library.
             * @return The type of the dynamic library.
             */
            LibType getLibType(const std::string &path) const;

            /**
             * @brief Gets the last error that occurred.
             * @return The last error that occurred.
             */
            std::string getLastError() const;

            /**
             * @brief Loads a graphical library.
             * @param path The path to the library.
             * @return The graphical library, nullptr is not loadable (see getLastError).
             */
            IDisplay *loadGraphicalLib(const std::string &path);

            /**
             * @brief Unloads a graphical library.
             * @param lib The library to unload.
             */
            void unloadGraphicalLib(IDisplay *lib);

            /**
             * @brief Loads a game library.
             * @param path The path to the library.
             * @return The game library, nullptr is not loadable (see getLastError).
             */
            IGame *loadGameLib(const std::string &path);

            /**
             * @brief Unloads a game library.
             * @param lib The library to unload.
             */
            void unloadGameLib(IGame *lib);

        private:
            LibLoader() = default;
            DELETE_COPY_MOVE(LibLoader);

            template <typename T>
            T *loadLib(const std::string &path, const std::string &createSymbol, const std::string &deleteSymbol) {
                UniqueLibHandle handle = std::make_unique<LibHandle>(path);
                create_t createLibrary;
                void *lib;

                if (!(*handle.get())
                || !(createLibrary = handle->fetchSymbol<create_t>(createSymbol))
                || !handle->fetchSymbol<delete_t>(deleteSymbol))
                    return nullptr;
                lib = createLibrary();
                _handles[lib] = std::move(handle);
                return static_cast<T *>(lib);
            }
            void unloadLib(void *lib, const std::string &deleteSymbol);

            const std::string _createDisplaySymbol = "createDisplay";
            const std::string _deleteDisplaySymbol = "deleteDisplay";
            const std::string _createGameSymbol = "createGame";
            const std::string _deleteGameSymbol = "deleteGame";

            using UniqueLibHandle = std::unique_ptr<LibHandle>;
            std::map<void *, UniqueLibHandle> _handles;
    };
}

#endif /* !LIBLOADER_HPP_ */

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
#include <vector>
#include <memory>
#include <dlfcn.h>

#define DELETE_COPY_MOVE(class_name) \
    class_name(const class_name &other) = delete; \
    class_name &operator=(const class_name &other) = delete; \
    class_name(const class_name &&other) = delete; \
    class_name &operator=(const class_name &&other) = delete;

typedef void *(*create_t)(void);
typedef void (*delete_t)(void *);

namespace Arcade {
    class LibLoader {
        public:
            enum LibType {
                GRAPHICAL,
                GAME,
                ERROR
            };

            static LibLoader &getInstance() {
                static LibLoader instance;
                return instance;
            }
            ~LibLoader() = default;

            LibType getLibType(const std::string &path) const;
            std::string getLastError() const;

            IDisplay *loadGraphicalLib(const std::string &path);
            void unloadGraphicalLib(IDisplay *lib);

            IGame *loadGameLib(const std::string &path);
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

            class LibHandle {
                public:
                    explicit LibHandle(const std::string &path);
                    ~LibHandle();
                    DELETE_COPY_MOVE(LibHandle);

                    operator bool() const;
                    bool isSet() const;
                    bool symbolExists(const std::string &symbolName) const;
                    template <typename T>
                    T fetchSymbol(const std::string &symbolName) const {
                        return reinterpret_cast<T>(dlsym(_handle, symbolName.c_str()));
                    }

                private:
                    void *_handle;
            };

            const std::string _createDisplaySymbol = "createDisplay";
            const std::string _deleteDisplaySymbol = "deleteDisplay";
            const std::string _createGameSymbol = "createGame";
            const std::string _deleteGameSymbol = "deleteGame";

            using UniqueLibHandle = std::unique_ptr<LibHandle>;
            std::map<void *, UniqueLibHandle> _handles;
    };
}

#endif /* !LIBLOADER_HPP_ */

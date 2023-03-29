/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** LibHandle
*/

#ifndef EPITECH_ARCADE_LIBHANDLE_HPP
#define EPITECH_ARCADE_LIBHANDLE_HPP
#include <string>
#include <dlfcn.h>

#define DELETE_COPY_MOVE(class_name) \
    class_name(const class_name &other) = delete; \
    class_name &operator=(const class_name &other) = delete; \
    class_name(const class_name &&other) = delete; \
    class_name &operator=(const class_name &&other) = delete;

namespace Arcade::Core {
    class LibHandle;
}

/**
 * @brief A wrapper around a dynamic library handle.
 */
class Arcade::Core::LibHandle {
public:
    /**
     * @brief Construct a new Library Handle.
     * @param path The path to the dynamic library.
     */
    explicit LibHandle(const std::string &path);
    ~LibHandle();
    DELETE_COPY_MOVE(LibHandle);

    /**
     * @brief see LibHandle::isSet()
     */
    operator bool() const;

    /**
     * @brief Check if the handle is valid.
     * @return True if the handle is valid, false otherwise.
     */
    bool isSet() const;

    /**
     * @brief Check if a symbol exists in the library.
     * @param symbolName The name of the symbol.
     * @return True if the symbol exists, false otherwise.
     */
    bool symbolExists(const std::string &symbolName) const;

    /**
     * @brief Fetch a symbol from the library.
     * @tparam T The type of the symbol.
     * @param symbolName The name of the symbol.
     * @return The symbol, null if can not be loaded.
     */
    template <typename T>
    T fetchSymbol(const std::string &symbolName) const {
        return reinterpret_cast<T>(dlsym(_handle, symbolName.c_str()));
    }

private:
    void *_handle;
};

#endif //EPITECH_ARCADE_LIBHANDLE_HPP

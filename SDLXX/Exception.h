#ifndef SDLXX_EXCEPTION_H
#define SDLXX_EXCEPTION_H

#include <exception>
#include <string>

namespace SDL {
    class Exception : public std::exception {
    public:
        Exception();

        Exception(const std::string &);

        Exception(const std::string &, const std::string &);

        Exception(const Exception &other);

        virtual ~Exception();

        virtual const char *what() const noexcept;

    private:
        std::string msg;
    };
}
#endif // SDLXX_EXCEPTION_H

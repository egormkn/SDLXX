#ifndef SDL2XX_EXCEPTION_H
#define SDL2XX_EXCEPTION_H

#include <exception>
#include <sstream>

namespace SDL {

    class Exception : public std::exception {
    public:
        Exception();

        Exception(const std::string &);

        Exception(const std::string &, const std::string &);

        Exception(const Exception& other);

        virtual ~Exception();

        virtual const char *what() const noexcept;

    private:
        std::string msg;
    };
}
#endif // SDL2XX_EXCEPTION_H

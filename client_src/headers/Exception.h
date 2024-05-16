/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */
#ifndef __Exception_H__
#define __Exception_H__

#include <exception>
#include <string>
/**
 * Clase que se inspira de las filminas de la catedra de exception.
 * recibe en su constructor un string con el formato (al estilo del formato
 * que recibe printf), y una cantidad indefinida de parámetros adicionales,
 * para agregarselos al esqueleto de fmt.
 */
class Exception: public std::exception {
private:
    std::string msg_error;

public:
    explicit Exception(const char* fmt, ...) noexcept;
    Exception() = delete;
    virtual const char* what() const noexcept;
    virtual ~Exception() noexcept = default;
};

#endif  //__Exception_H__

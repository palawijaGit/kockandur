#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

class FileException : public exception {

  virtual const char* what() const throw()
    {
        return "Some Fileexception happened";
    }
};


#endif // EXCEPTIONS_H

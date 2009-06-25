#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

class FileException : public exception {

  private:
    char * error_description;

  public:
    FileException();

  virtual const char* what() const throw()
    {
        return "Some Fileexception happened";
    }
};


#endif // EXCEPTIONS_H

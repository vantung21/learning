#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class DuplicateIDException : public exception {
        string msg;
    public:
        DuplicateIDException(const string& id)
            : msg("Error: Duplicate ID '" + id + "'") {}
        const char* what() const noexcept override { return msg.c_str(); }
};

class InvalidYearException : public exception {
        string msg;
    public:
        InvalidYearException(int y)
            : msg("Error: Invalid year " + to_string(y) + ". Must be 2000-2025") {}
        const char* what() const noexcept override { return msg.c_str(); }
    };

class InvalidValueException : public exception {
        string msg;
    public:
        InvalidValueException(const string& field)
            : msg("Error: Invalid value for " + field) {}
        const char* what() const noexcept override { return msg.c_str(); }
};

#endif // EXCEPTION_H
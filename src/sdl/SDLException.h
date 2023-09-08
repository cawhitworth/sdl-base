#pragma once
#include <exception>
#include <string>

class SDLException : public std::exception
{
    std::string m_message;
public:
    SDLException(std::string message) : m_message(message) {}
    virtual ~SDLException() {}

    const std::string& Message() const { return m_message; }
};


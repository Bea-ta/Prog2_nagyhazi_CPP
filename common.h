#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include <string>

/// Saját kivételosztály a teszthez.
class BajVan {
private:
    std::string message;
public:
    /// @param msg - a hiba leirasa
    explicit BajVan(const std::string& msg):message(msg) {}
    const char* uzenet(){
        return message.c_str();
    }
};
#endif // COMMON_H_INCLUDED

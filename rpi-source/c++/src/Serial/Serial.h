#pragma once
#include <string>

class Serial {
    public:
        Serial(std::string sertty, unsigned baud);

        int Write(int input);
        int Write(std::string input);
    private:
    private:
        int m_handle;
};
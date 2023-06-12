#pragma once

#include <fstream>

namespace TapeModule
{
    enum class Mode
    {
        Write,
        Read
    };

    class Tape
    {   
    public:
        Tape(const char *fPath, Mode mode);

        inline Mode getMode() const { return m_mode; }

        ~Tape() = default;
        Tape(const Tape&) = default;
        Tape& operator=(const Tape&) = default;

        Tape(Tape&&) = delete;
        Tape& operator=(Tape&&) = delete;

    private:
        Mode m_mode;
        std::fstream m_file;
        unsigned int m_tapePointer = 0;
    };
}
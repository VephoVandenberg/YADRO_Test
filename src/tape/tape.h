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
        Tape(const char *fPath, Mode mode = Mode::Read);

        int read();
        void write(int data);
        void moveForward();
        void moveBack();

        inline Mode getMode() const { return m_mode; }

        ~Tape() = default;
        Tape(const Tape&) = default;
        Tape& operator=(const Tape&) = default;

        Tape(Tape&&) = delete;
        Tape& operator=(Tape&&) = delete;

    private:
        Mode m_mode;
        std::string fPath;
        std::fstream m_file;
        unsigned int m_tapePointer = 0;
    };
}

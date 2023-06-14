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
        Tape(std::string path, Mode mode = Mode::Read);
        ~Tape();

        void read(int& data);
        void write(int data);
        void moveForward();
        void moveBackward();
        void reload();
        void toRead();
        void toWrite();

        inline bool isOpen() const { return m_writer.is_open() || m_reader.is_open(); }
        inline std::string getPath() const  { return m_path; } 
        inline Mode getMode() const { return m_mode; }
        inline bool isEOF() { return m_tapePointer > m_fileLength; }

        inline int getTapeLength() const { return m_fileLength; }
        inline int getTapePtr() const { return m_tapePointer; }

        Tape(const Tape&) = default;
        Tape& operator=(const Tape&) = default;
        Tape(Tape&&) = default;
        Tape& operator=(Tape&&) = default;

    private:
        Mode m_mode;
        std::string m_path;
        std::ifstream m_reader;
        std::ofstream m_writer;
        int m_tapePointer = 0;
        int m_fileLength = 0;
    };
}

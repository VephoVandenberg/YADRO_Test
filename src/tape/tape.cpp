#include <iostream>

#include "tape.h"

using namespace TapeModule;

constexpr int g_cellSize = sizeof(int);

Tape::Tape(std::string path, Mode mode)
    : m_mode(mode) 
    , m_path(path)
    , m_tapePointer(0)
    , m_fileLength(0)
{
    switch(m_mode)
    {
        case Mode::Read:
            m_reader.open(m_path, std::ios::binary);
            m_reader.seekg(m_tapePointer, std::ios::end);
            m_fileLength = m_reader.tellg();
            std::cout << m_fileLength <<std::endl;
            m_reader.seekg(m_tapePointer, std::ios::beg);
            break;
        
        case Mode::Write:
            m_writer.open(m_path, std::ios::binary);
            m_writer.seekp(m_tapePointer, std::ios::beg);
            break;
    }
}

Tape::~Tape()
{
    reload();
    m_writer.close();
    m_reader.close();
}

void Tape::read(int& data)
{
    m_reader.read(reinterpret_cast<char*>(&data), g_cellSize);
    m_tapePointer += g_cellSize;
}

void Tape::write(int data)
{
    m_writer.write(reinterpret_cast<char*>(&data), g_cellSize);
    m_tapePointer += g_cellSize;
}

void Tape::moveForward()
{
    m_tapePointer += g_cellSize;
    if (m_mode == Mode::Write)
    {
        m_writer.seekp(m_tapePointer, std::ios::beg);
    }
    else
    {
        m_reader.seekg(m_tapePointer, std::ios::beg);
    }
}

void Tape::moveBackward()
{
    m_tapePointer -= g_cellSize;
    if (m_mode == Mode::Write)
    {
        m_writer.seekp(m_tapePointer, std::ios::beg);
    }
    else
    {
        m_reader.seekg(m_tapePointer, std::ios::beg);
    }
}

void Tape::reload()
{
    for (;m_tapePointer > 0; m_tapePointer -= g_cellSize);
}

void Tape::toRead()
{
    m_mode = Mode::Read;
    m_writer.close();
    m_reader.open(m_path, std::ios::binary);
    m_reader.seekg(m_tapePointer, std::ios::end);
    m_fileLength = m_reader.tellg();
    m_reader.seekg(m_tapePointer, std::ios::beg);
}

void Tape::toWrite()
{
    m_mode = Mode::Write;
    m_reader.close();
    m_writer.open(m_path, std::ios::binary);
    m_writer.seekp(m_tapePointer, std::ios::beg);
}

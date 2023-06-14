#include <iostream>
#include <chrono>
#include <thread>

#include "tape.h"

using namespace TapeModule;

constexpr int g_cellSize = sizeof(int);

Tape::Tape(std::string path, std::string config, Mode mode)
    : m_mode(mode) 
    , m_path(path)
    , m_tapePointer(0)
    , m_fileLength(0)
    , m_readAndWriteDelay(1)
    , m_reloadDelay(1)
    , m_moveDelay(1)
{
    readConfig(config);
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

void Tape::readConfig(std::string path)
{
    std::ifstream config(path);

    if (!config.is_open())
    {
        std::cout << "ERROR::Failed to open config file!" << std::endl;
    }

    std::string param;
    while (!config.eof())
    {
        config >> param;

        if (param == "RW_DELAY")
        {
            config >> m_readAndWriteDelay;
        }
        else if (param == "MOV_DELAY")
        {
            config >> m_moveDelay;
        }
        else if (param == "RELOAD_DELAY")
        {
            config >> m_reloadDelay;
        }
    }
}

void Tape::read(int& data)
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(m_readAndWriteDelay));
    m_reader.read(reinterpret_cast<char*>(&data), g_cellSize);
    m_tapePointer += g_cellSize;
}

void Tape::write(int data)
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(m_readAndWriteDelay));
    m_writer.write(reinterpret_cast<char*>(&data), g_cellSize);
    m_tapePointer += g_cellSize;
}

void Tape::moveForward()
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(m_moveDelay));
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
    std::this_thread::sleep_for(std::chrono::nanoseconds(m_moveDelay));
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
    std::this_thread::sleep_for(std::chrono::nanoseconds(m_reloadDelay));
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

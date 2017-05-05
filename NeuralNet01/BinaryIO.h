#pragma once
#include <type_traits>
#include <iostream>
#include <fstream>
#include <string>

	class BinaryIO {
	private:
		std::string m_FileName;
		std::ifstream m_fileReadStream;
		std::ofstream m_fileWriteStream;
	public:

		BinaryIO(const std::string& fileName) :m_FileName(fileName) {}
		virtual ~BinaryIO() {}

		void openwrite()
		{
			m_fileWriteStream.open(m_FileName, std::ios::binary );
		}

		void openread()
		{
			m_fileReadStream.open(m_FileName, std::ios::binary);
		}

		void close()
		{
			m_fileReadStream.close();
			m_fileWriteStream.close();
		}

		template <typename t>void write(t data)
		{
			if (m_fileWriteStream.is_open())
			{
				m_fileWriteStream.write((const char*)&data, sizeof(data));
			}
			else
			{
				std::cout << "failed to open file\n";
			}
		}

		template <typename t> void read(t& data)
		{
			if (m_fileReadStream.is_open())
			{
				m_fileReadStream.read((char*)&data, sizeof(data));
			}
			else
			{
				std::cout << "failed to open file\n";
			}
		}

		void write(std::string data)
		{
			if (m_fileWriteStream.is_open())
			{
				m_fileWriteStream.write(data.c_str(), data.size());
			}
			else
			{
				std::cout << "file not open\n";
			}
		}

		void read(std::string& data, int len)
		{
			if (m_fileReadStream.is_open())
			{
				char* buffer = new char[len + 1]{};
				m_fileReadStream.read(buffer, len);
				data = buffer;
				delete[] buffer;
			}
			else
			{
				std::cout << "file not open\n";
			}
		}

		int getEndPos()
		{
			m_fileReadStream.seekg(0, std::ios::end);
			int length = int(m_fileReadStream.tellg());
			m_fileReadStream.seekg(0, std::ios::beg);
			return length;
		}

		int getCurrentPos()
		{
			return int(m_fileReadStream.tellg());
		}
	};



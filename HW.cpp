
#include <Windows.h>
#include <iostream>
#include <string>


bool WriteTextAfter(std::string const& i_file_name, std::string const& i_what_to_find, std::string const& i_what_to_write);


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

struct Handle
{
	Handle(const HANDLE& handle);
	HANDLE& get();
	const HANDLE& get() const;
	~Handle();
private:
	HANDLE m_handle;
};

Handle::Handle(const HANDLE& handle)
	: m_handle(handle)
{}

HANDLE& Handle::get()
{
	return m_handle;
}

const HANDLE& Handle::get() const
{
	return m_handle;
}

Handle::~Handle()
{
	::CloseHandle(m_handle);
}

int main()
{
	try
	{
		WriteTextAfter("temp.txt", "Test:", "passed");
		WriteTextAfter("t.txt", "Test:", "passed");
		WriteTextAfter("", "Test:", "passed");
	}
	catch (std::runtime_error& r_e)
	{
		std::cout << r_e.what();
	}

	system("pause");
	return 0;
}


//-----------------------------------------------------------------------------------
HANDLE GetOrCreateFile(std::string const& i_file_name, bool i_create_if_no_exists, bool i_read_only)
{
	/*auto handle = ::CreateFileA(i_file_name.c_str(), i_read_only ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE,
		0, NULL, i_create_if_no_exists ? OPEN_ALWAYS : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);*/
	Handle handle(::CreateFileA(i_file_name.c_str(), i_read_only ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE,
		0, NULL, i_create_if_no_exists ? OPEN_ALWAYS : OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL));

	if (handle.get() == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Cannot open file. Error code is: " + ::GetLastError() + '\n');

	return handle.get();
}

//-----------------------------------------------------------------------------------
bool WriteTextAfter(std::string const& i_file_name, std::string const& i_what_to_find, std::string const& i_what_to_write)
{
	if (i_what_to_write.empty())
	{
		std::cout << "Nothing to write, returning\n";
		return true;
	}

	Handle handle = GetOrCreateFile(i_file_name.c_str(), !i_what_to_find.empty(), false);
	if (handle.get() == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Cannot open the specifield file\n");

	LARGE_INTEGER file_size = {};
	if (!::GetFileSizeEx(handle.get(), &file_size))
		throw std::runtime_error("The function failed: file size cannot be calculated.\n");

	// If file is empty or new
	if (file_size.QuadPart == 0)
	{
		if (!i_what_to_find.empty())
			throw std::runtime_error("Cannot find the specified text in the file\n");
		else
		{
			DWORD bytes_written = 0;
			auto res = ::WriteFile(handle.get(), i_what_to_write.c_str(), i_what_to_write.size(), &bytes_written, NULL);
			if (res == FALSE || bytes_written != i_what_to_write.size())
				throw std::runtime_error("The function failed: cannot write to the file.\n");
			return true;
		}
	}

	// try to find a substring
	auto p_buffer = new char[file_size.QuadPart];

	DWORD bytes_read = 0;
	if (!::ReadFile(handle.get(), p_buffer, file_size.QuadPart, &bytes_read, NULL))
	{
		delete p_buffer;
		::CloseHandle(handle.get());
		throw std::runtime_error("The function failed: cannot read file.\n");
	}

	auto p_pos = strstr(p_buffer, i_what_to_find.c_str());


	// write to the file
	LARGE_INTEGER pos_move = { p_pos - p_buffer + strlen(i_what_to_find.c_str()) };
	::SetFilePointerEx(handle.get(), pos_move, NULL, FILE_BEGIN);

	DWORD bytes_written = 0;
	auto res = ::WriteFile(handle.get(), i_what_to_write.c_str(), i_what_to_write.size(), &bytes_written, NULL);
	if (res == FALSE || bytes_written != i_what_to_write.size())
	{
		delete p_buffer;
		throw std::runtime_error("The function failed: cannot write to the file.\n");
	}

	delete p_buffer;
	return true;
}
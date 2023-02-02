#include <boost/asio.hpp>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#define PORT "1212"

using namespace std;
using namespace std::filesystem;
using namespace boost::asio;
using ip::tcp;

void
panic(string msg)
{
    cout << msg << endl;
    exit(1);
}

int
main(int argc, char* argv[])
{
    try {
        if (argc < 2) {
            cerr << "No file was specified!" << endl;
            return EXIT_FAILURE;
        }

        string path = argv[1];

        cout << "Selected file: '" << path << "'" << endl;

        string msg;

        if (!exists(path)) {
            panic("Specified path not found!");
        } else if (!is_regular_file(path)) {
            panic("Specified path is not a file!");
        } else {
            ifstream file(path);
            msg = string(istreambuf_iterator<char>(file),
                         istreambuf_iterator<char>());
            file.close();

            if (msg.length() == 0)
                panic("File is empty");
        }

        // cout << "Message: '" << msg << "'" << endl;

        int repeat = 1;

        if (argc >= 3) {
            repeat = stoi(argv[2]);
        }

        io_context context;
        tcp::socket socket(context);
        connect(socket, tcp::resolver(context).resolve("127.0.0.1", PORT));
        int port = socket.local_endpoint().port();

        for (int i = 0; i < repeat; i++) {
            cout << "[p:" << port << "] Sending repeat #" << i + 1 << endl;
            socket.send(buffer(msg));
            socket.send(buffer({ '\xff' })); // Message delimiter
            cout << "[p:" << port << "] Message sent" << endl;
        }
    } catch (exception& e) {
        cerr << "Got error while sending message: " << e.what() << endl;
    }

    return EXIT_SUCCESS;
}

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <csignal>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#define PORT 1212

using namespace std;
using namespace boost::asio;
using ip::tcp;

static bool quiet = false;

class Connection : public boost::enable_shared_from_this<Connection>
{
    bool reading_msg = false;

    boost::asio::streambuf _buf;
    ofstream log;
    tcp::socket _socket;

    Connection(io_context& context)
      : _socket(context)
    {
    }

  public:
    typedef boost::shared_ptr<Connection> pointer;

    static pointer create(io_context& context)
    {
        return pointer(new Connection(context));
    }

    tcp::socket& socket() { return _socket; }

    tuple<string, int> identity()
    {
        tcp::endpoint client = _socket.remote_endpoint();
        return { client.address().to_string(), client.port() };
    }

    void print_identity(const tuple<string, int>& client)
    {
        auto [addr, port] = client;
        cout << "Client[" << addr << ":" << port << "]";
    }

    void start()
    {
        auto client = identity();
        // Announce client
        cout << "Got connection from new ";
        print_identity(client);
        cout << endl;

        // Open log file
        auto [addr, port] = client;
        log.open(addr + "_" + to_string(port) + ".log", ios_base::app);
        msg_begin();

        read(0);
    }

    // Append message begin decorator to log
    void msg_begin()
    {
        reading_msg = true;
        time_t now = time(0);
        log << "> Message at " << ctime(&now) << "========" << endl;
    }

    // Append message end decorator to log
    void msg_end()
    {
        log << endl << (reading_msg ? "=======!" : "========") << endl;
        log.flush();
        reading_msg = false;
    }

    void msg_part(const tuple<string, int>& client,
                  size_t chunk,
                  const string& msg)
    {
        cout << "Got message part from ";
        print_identity(client);
        cout << "[c:" << chunk;

        if (!quiet)
            cout << "]: "
                 << "\"" << msg << "\"" << endl;
        else
            cout << "]" << endl;
    }

    // Start/Restart async reader
    void read(size_t chunk)
    {
        async_read_until(
          _socket,
          _buf,
          '\xff',
          boost::bind(&Connection::handle_read,
                      shared_from_this(),
                      chunk,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(size_t chunk,
                     const boost::system::error_code& err,
                     size_t transferred)
    {
        auto client = identity();
        if (!err || err == error::eof) {
            bool finished = false;
            auto process = [&, this](bool last) {
                istream in(addressof(_buf));
                string msg;
                getline(in, msg, '\xff'); // Parse buffer

                // Process message delimiter
                if (int delim = msg.find('\xff'); delim != 1) {
                    finished = true;
                    msg = msg.substr(0, delim); // Cut delimiter
                }

                msg_part(client, chunk, msg); // Show part in console
                log << msg;                   // Write new part to log

                if (finished) { // Write end decorator
                    reading_msg = false;
                    msg_end();
                }

                if (finished && !last) // Write decorator for the next message
                    msg_begin();
                if (!last)
                    read(++chunk); // Continue reading stream
            };

            if (err == error::eof && transferred == 0) { // Finish connection
                // Process buffer, when client hasn't sent delimiter
                if (_buf.size() != 0) {
                    process(true);
                }

                // if (reading_msg)
                msg_end();
                print_identity(client);
                cout << " disconnected" << endl;
            } else {
                process(false);
            }
        } else {
            throw boost::system::system_error(err);
        }
    }
};

class Server
{
    io_context& _context;
    tcp::acceptor _acceptor;

    void accept()
    {
        Connection::pointer conn = Connection::create(_context);

        _acceptor.async_accept(
          conn->socket(),
          boost::bind(
            &Server::handle, this, conn, boost::asio::placeholders::error));
    }

    void handle(Connection::pointer conn, const boost::system::error_code& err)
    {
        if (!err) {
            conn->start();
        } else {

            cerr << "Error occurred while accepting new client" << endl;
        }

        accept();
    }

  public:
    Server(io_context& context)
      : _context(context)
      , _acceptor(context, tcp::endpoint(tcp::v4(), PORT))
    {
        accept();
    }
};

void
signal_handler(int signum)
{
    cout << "Got signal (" << signum << ") closing server";
    exit(signum);
}

int
main(int argc, char* argv[])
{
    signal(SIGHUP, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    quiet = argc >= 2;

    try {
        io_context context;
        Server server(context);
        context.run();
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    return EXIT_SUCCESS;
}

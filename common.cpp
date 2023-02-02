#include <string>
#include <boost/asio.hpp>


using namespace std;
using namespace boost::asio;
using ip::tcp;

string read(tcp::socket &socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    return boost::asio::buffer_cast<const char *>(buf.data());
}

void send(tcp::socket &socket, const string &message)
{
    const string msg = message + "\n";
    boost::asio::write(socket, boost::asio::buffer(message));
}
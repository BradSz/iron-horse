#define BOOST_TEST_MODULE streamsocket
#include <boost/test/included/unit_test.hpp>

#include <iron/core/socket/StreamSocket.hpp>

BOOST_AUTO_TEST_SUITE(StreamSocket)

BOOST_AUTO_TEST_CASE(ServerListenTest)
{
  iron::socket::StreamSocket server;

  server.listen(42095);
}

BOOST_AUTO_TEST_CASE(ClientToServerTest)
{
  iron::socket::StreamSocket server, client;

  server.listen(42095);
  client.connect(42095);

  std::string textWritten = "Test Text";
  std::string textRead;

  client.write(textWritten);
  textRead = server.readSome();

  BOOST_CHECK_EQUAL(textWritten, textRead);
}

BOOST_AUTO_TEST_SUITE_END()


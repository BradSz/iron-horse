#pragma once

#include <iron/core.h>

class TcpServer
{
  public:
    TcpServer(boost::asio::io_service& io_service, short port)
  : io_service_(io_service),
    acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  {
      start_accept();
  }

  private:
    void start_accept()
    {
      session* new_session = new session(io_service_);
      acceptor_.async_accept(new_session->socket(),
                             boost::bind(&server::handle_accept, this, new_session,
                                         boost::asio::placeholders::error));
    }

    void handle_accept(session* new_session,
                       const boost::system::error_code& error)
    {
      if (!error)
        {
          new_session->start();
        }
      else
        {
          delete new_session;
        }

      start_accept();
    }

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};
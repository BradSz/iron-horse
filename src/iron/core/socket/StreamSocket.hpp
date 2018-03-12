#pragma once

#include <iron/core.h>

namespace iron {
namespace socket {

  struct StreamSocket {

      void write(const std::string& inData)
      {
        ss << inData;
      }

      std::string readSome() {
        return ss.str();
      }

      void listen(uint16_t inPort) {
      }

      void connect(uint16_t inPort, std::string inHost = "localhost") {
      }

    private:
      std::stringstream ss;
  };

} /* socket */
} /* iron */


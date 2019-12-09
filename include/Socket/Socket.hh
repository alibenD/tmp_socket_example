#ifndef __SOCKET_HH__
#define __SOCKET_HH__
/**-----------------------------------------------
  * @Copyright (C) 2019 All rights reserved.
  * @date: 2019
  * @file: Socket.hh
  * @version: v0.0.1
  * @author: aliben.develop@gmail.com
  * @create_date: 2019-08-26 18:28:19
  * @last_modified_date: 2019-09-03 16:37:18
  * @brief: TODO
  * @details: TODO
  *-----------------------------------------------*/

// Header include
#include <sys/un.h>
#include <sys/socket.h>
#include <string>

// Declaration
namespace ak
{
  class Socket;
  class StreamSocket;
  class DatagramSocket;

  class Socket
  {
    public:
      Socket() = default;
      explicit Socket(const std::string& sock_addr);
      virtual ~Socket() = default;
    public:
      virtual void Connect() = 0;
      virtual void Close() = 0;
      virtual void DebugPrint() = 0;
    protected:
      int socket_fd_;
  };

  class StreamSocket : public Socket
  {
    public:
      StreamSocket() = default;
      virtual ~StreamSocket() = default;
    public:
      virtual void Connect() override;
      virtual void Close() override;
      virtual void DebugPrint() override;
  };

  class DatagramSocket : public Socket
  {
    public:
      DatagramSocket() = default;
      virtual ~DatagramSocket() = default;
  };
}
#endif // __SOCKET_HH__

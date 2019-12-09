/**
  * @Copyright (C) 2019 All rights reserved.
  * @date: 2019
  * @file: example_unix_domain_datagram_socket_server.cc
  * @version: v0.0.1
  * @author: aliben.develop@gmail.com
  * @create_date: 2019-09-03 16:29:57
  * @last_modified_date: 2019-09-03 16:34:59
  * @brief: TODO
  * @details: TODO
  */

//INCLUDE
#include <sys/un.h>
#include <sys/socket.h>

#define BUF_SIZE 10
#define SV_SOCK_PATH "/tmp/unix_dgram"
//CODE

int main(int argc, char** argv)
{
  struct sockaddr_un server_addr, client_addr;
  int server_fd, tmp_fd;
  ssize_t num_bytes;
  socklen_t len;
  return 0;
}

/**
  * @Copyright (C) 2019 All rights reserved.
  * @date: 2019
  * @file: example_unix_domain_socket_client.cc
  * @version: v0.0.1
  * @author: aliben.develop@gmail.com
  * @create_date: 2019-08-27 12:13:14
  * @last_modified_date: 2019-11-30 16:58:37
  * @brief: TODO
  * @details: TODO
  */

//INCLUDE
#include <sys/un.h>
#include <sys/socket.h>

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fcntl.h>

#define SV_SOCK_PATH "/tmp/ak_us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

//CODE
int main(int argc, char** argv)
{
  struct sockaddr_un addr;
  int socket_fd;
  ssize_t num_read;
  char buf[BUF_SIZE];
  socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

  std::cout << "BACKLOG: " << BACKLOG << std::endl;

  if(socket_fd == -1)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "Error creating new client socket:\n" << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

  if(connect(socket_fd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) == -1)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "Connect" << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }

  while((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
  {
    if(write(socket_fd, buf, num_read) != num_read)
    {
      std::cout << "Partial/Failed write" << std::endl;
      exit(1);
    }
  }

  if(num_read == -1)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "Read" << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }

  exit(EXIT_SUCCESS);
}

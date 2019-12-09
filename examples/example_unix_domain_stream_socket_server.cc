/**
  * @Copyright (C) 2019 All rights reserved.
  * @date: 2019
  * @file: example_unix_domain_socket_service.cc
  * @version: v0.0.1
  * @author: aliben.develop@gmail.com
  * @create_date: 2019-08-27 10:10:23
  * @last_modified_date: 2019-11-30 19:32:29
  * @brief: TODO
  * @details: TODO
  */

//INCLUDE
#include <sys/un.h>
#include <sys/socket.h>
#include <fcntl.h>

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

#define SV_SOCK_PATH "/tmp/ak_us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

//CODE
int main(int argc, char** argv)
{
  struct sockaddr_un addr;
  int socket_fd, connect_fd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if(socket_fd == -1)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "Error creating new client socket:\n" << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }

  if(remove(SV_SOCK_PATH) == -1 && errno!= ENOENT)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "remove " << SV_SOCK_PATH << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  int flags = fcntl(socket_fd, F_GETFL, 0);
  fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK);

  if(bind(socket_fd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) == -1)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "Bind" << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }

  if(listen(socket_fd, BACKLOG) == -1)
  {
    std::ostringstream aux_comp_str;
    aux_comp_str << "Listen" << std::endl;
    throw std::logic_error(aux_comp_str.str());
  }

  for(;;)
  {
    connect_fd = accept(socket_fd, nullptr, nullptr);
    if(connect_fd == -1)
    {
      std::ostringstream aux_comp_str;
      aux_comp_str << "Accept" << std::endl;
      throw std::logic_error(aux_comp_str.str());
    }

    while((num_read = read(connect_fd, buf, BUF_SIZE)) > 0)
    {
      //if(num_read == 0) break;
      std::cout << "In Loop" << std::endl;
      if(write(STDOUT_FILENO, buf, num_read) != num_read)
      {
        //fatal("Partial/Failed write");
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
    if(close(connect_fd) == -1)
    {
      std::ostringstream aux_comp_str;
      aux_comp_str << "Close" << std::endl;
      throw std::logic_error(aux_comp_str.str());
    }
  }

  return 0;
}

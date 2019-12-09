/**
  * @Copyright (C) 2019 All rights reserved.
  * @date: 2019
  * @file: example_unix_domain_socket_service.cc
  * @version: v0.0.1
  * @author: aliben.develop@gmail.com
  * @create_date: 2019-08-27 10:10:23
  * @last_modified_date: 2019-12-01 15:33:44
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
#include <vector>

#define SV_SOCK_PATH "/tmp/ak_us_xfr"
#define BUF_SIZE 100
#define BACKLOG 2

size_t read_async(int socket_handle_, void* buffer, const size_t count, const int timeout_start_ms, const int timeout_between);
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

  std::vector<int> socket_fd_vector;
  for(;;)
  {
    connect_fd = accept(socket_fd, nullptr, nullptr);
    if(connect_fd == -1)
    {
      //std::ostringstream aux_comp_str;
      //aux_comp_str << "Accept" << std::endl;
      //throw std::logic_error(aux_comp_str.str());
      //std::cout << "Listening: "<< connect_fd << std::endl;
    }

    if(connect_fd != -1)
    {
      std::cout << "Connect: "<< connect_fd << std::endl;
      socket_fd_vector.emplace_back(connect_fd);
    }

    //while((num_read = read(connect_fd, buf, BUF_SIZE)) > 0)
    //{
    //  //if(num_read == 0) break;
    //  std::cout << "In Loop" << std::endl;
    //  if(write(STDOUT_FILENO, buf, num_read) != num_read)
    //  {
    //    //fatal("Partial/Failed write");
    //    std::cout << "Partial/Failed write" << std::endl;
    //    exit(1);
    //  }
    //}
    num_read = read_async(connect_fd, buf, BUF_SIZE, 200, 20);
    if(num_read > 0)
    {
      std::cout << "Msg: " << buf << std::endl;
    }
    if(num_read == -1)
    {
      std::ostringstream aux_comp_str;
      aux_comp_str << "Read" << std::endl;
      throw std::logic_error(aux_comp_str.str());
    }
  }

  return 0;
}

size_t read_async(int socket_handle_, void* buffer, const size_t count, const int timeout_start_ms, const int timeout_between)
{
    if( socket_handle_ == -1 )
    {
      return 0;
    }

    size_t remain_to_read, already_read = 0;
    int read_now;
    bool timeout_expired = false;

    struct timeval timeout_select;
    struct timeval* ptr_timeout;
    fd_set sock_arr;

    FD_ZERO(&sock_arr);
    FD_SET(socket_handle_, &sock_arr);

    // Loop until timeout expires or the socket closed
    while( already_read < count && !timeout_expired )
    {
      int cur_timeout = already_read == 0 ? timeout_start_ms : timeout_between;
      if (cur_timeout < 0)
      {
        ptr_timeout = nullptr;
      }
      else
      {
        timeout_select.tv_sec = cur_timeout / 1000;
        timeout_select.tv_usec = 1000 * (cur_timeout % 1000);
        ptr_timeout = &timeout_select;
      }

      int sel_ret = ::select(socket_handle_ + 1,
            &sock_arr,
            nullptr,
            nullptr,
            ptr_timeout);

      if( sel_ret == -1 )
      {
        std::ostringstream aux_comp_str;
        aux_comp_str << "\n\n========DR EXCEPTION========\n";
        //aux_comp_str << "Error reading from socket: " << get_last_error_str().c_str() <<"\n" << std::endl;
        throw std::logic_error(aux_comp_str.str());
      }

      if ( sel_ret == 0 )
      {
        timeout_expired = true;
      }
      else
      {
        remain_to_read = count - already_read;
        read_now = ::recv(socket_handle_,
                          ((char*)buffer) + already_read,
                          (int)remain_to_read,
                          0);
        if ( read_now != -1 )
        {
          already_read += read_now;
        }
        else
        {
          // If error, then close socket
          //close();
          return already_read;
        }

        if ( read_now == 0 && remain_to_read != 0 )
        {
          timeout_expired = true;
          //close();
        }
      }

    }   // END while
    return already_read;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int fun1() {
  char buf[1024] = {0};

  int pipefd[2];

  // create pipe
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }

  // 管道写入
  if (write(pipefd[1], "this is a fun1 test msg",
            strlen("this is a fun1 test msg")) < 0) {
    perror("write()");
    exit(1);
  }

  // 管道读取
  if (read(pipefd[0], buf, 1024) < 0) {
    perror("read()");
    exit(1);
  }

  cout << buf << endl;
  return 0;
}

int fun2() {
  char buf[1024] = {0};
  int pipefd[2];
  // 先保存标准输出端句柄，用于恢复cout
  int out_fd = dup(STDOUT_FILENO);

  // 创建管道
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }
  // 重定向stdout 到 管道输入端
  dup2(pipefd[1], 1);

  // 重定向stdin 到 管道输出端
  dup2(pipefd[0], 0);
  // 写入信息到管道
  cout << "this is a fun2 test msg" << endl;
  // 管道信息写入到buf
  cin.getline(buf, 1024);

  // 恢复标准输出
  dup2(out_fd, 1);
  cout << buf << endl;
  return 0;
}

int main() {
  fun1();
  fun2();
  return 0;
}
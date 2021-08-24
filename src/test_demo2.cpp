#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main() {
  char buf[1024] = {0};

  int pipefd[2];

  // 管道创建
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork()");
    exit(1);
  }

  if(pid == 0) {
    // 子进程
    // 关闭 pipefd 输出端
    close(pipefd[0]);
    // stdout 重定向到 pipefd 输入端
    dup2(pipefd[1], 1);
    cout << "msg from child process" << endl;
  } else {
    // 父进程
    // 关闭 pipefd 输入端
    close(pipefd[1]);
    // stdin 重定向到 pipefd 输出端
    dup2(pipefd[0], 0);
    cin.getline(buf, 1024);
    cout << "parent get from child:" << buf << endl;
    wait(pid);
  }
  exit(0);
}
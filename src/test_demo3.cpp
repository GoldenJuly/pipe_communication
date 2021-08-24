#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main() {
  char bufC[1024] = {0};
  char bufP[1024] = {0};

  // 实现子进程->父进程通信
  int pipeC2P[2];
  // 实现父进程->子进程通信
  int pipeP2C[2];

  // create pipe
  if (pipe(pipeC2P) == -1) {
    perror("pipeC2P");
    exit(1);
  }
  if (pipe(pipeP2C) == -1) {
    perror("pipeP2C");
    exit(1);
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("fork()");
    exit(1);
  }

  if (pid == 0) {
    // 子进程
    int out_fd = dup(STDOUT_FILENO);
    // 关闭 pipeC2P 输出端
    close(pipeC2P[0]);
    // stdout 重定向到 pipefd 输入端
    dup2(pipeC2P[1], 1);
    cout << "msg from child process" << endl;

    // 关闭 pipeP2C 输入端
    close(pipeP2C[1]);
    // stdin 重定向到 pipefd 输出端
    dup2(pipeP2C[0], 0);
    cin.getline(bufC, 1024);
    dup2(out_fd, 1);
    cout << "child get from parent:" << bufC << endl;
  } else {
    // 父进程
    int out_fd = dup(STDOUT_FILENO);
    // 关闭 pipeC2P 输出端
    close(pipeP2C[0]);
    // stdout 重定向到 pipefd 输入端
    dup2(pipeP2C[1], 1);
    cout << "msg from parent process" << endl;

    // 关闭 pipeC2P 输入端
    close(pipeC2P[1]);
    // stdin 重定向到 pipefd 输出端
    dup2(pipeC2P[0], 0);
    cin.getline(bufP, 1024);
    dup2(out_fd, 1);
    cout << "parent get from child:" << bufP << endl;
    wait(pid);
  }
  exit(0);
}
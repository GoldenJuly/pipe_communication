# pipe_communication
进程间通信演示

### test_demo1.cpp
单进程中使用单个管道进行读写
  
![image](https://user-images.githubusercontent.com/11610236/130611299-51ce0b07-8588-42c9-b751-d3c9e1c0f281.png)

### test_demo2.cpp
父子进程使用单个管道进行半双工通信  
child进程通过红色线路写入管道，parent通过蓝色线路从管道读取信息  
因为只有一个管道，在一个时刻，要么child ——> parent 传递信息，要么parent ——>  child传递信息  
图中和代码只展示了  parent <—— pipe <—— child  
  
![image](https://user-images.githubusercontent.com/11610236/130611334-01e99e96-d56d-4e4e-8437-177c61b82b03.png)

### test_demo3.cpp
父子进程使用两个管道进行全双工通信  
child进程通过Fd[1]红色线路写入信息到pipe1，parent通过Fd[0]从蓝色线路通过pipe1读取子进程信息  
parent进程通过Fd[1]蓝色线路写入信息到pipe2，child通过Fd[0]从红色线路通过pipe2读取子进程信息  
图中和代码只展示了  parent <—— pipe1 <—— child 以及 parent ——> pipe2 ——> child  
  
![image](https://user-images.githubusercontent.com/11610236/130611360-3517c071-6bff-4236-b6b0-15435a84db70.png)

# make
  cd src && make

# make clean
  cd src && make clean

# run
  cd src && make run

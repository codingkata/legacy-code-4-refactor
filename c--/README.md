[TOC]

## 运行准备说明

1. 本用例使用gtest作为单元测试框架，并且已包含在本项目源代码中，不必下载，版本为`googletest-release-1.8.1`。
2. 本机有C++编译环境
3. 可以运行make命令

## 如何编译

在命令控制台下，在项目根目录运行命令 `make`，将生成两个可执行文件，其中，`marsrover`为程序文件，`gtest`为单元测试文件。

```
./output/bin/marsrover
./output/ut/gtest
```

## 如何运行

### 运行程序文件

在项目根目录执行下面命令

`./output/bin/marsrover`

### 运行单元测试

在项目根目录执行下面命令

`./output/ut/gtest`


## 程序各步骤的输入说明

#### 第一步：获取用户输入参数
>1. 用户的最大边界范围（第一行）
2. 起始坐标位置及方向（除第一行外的每个偶数行都为起始位置组）
3. 移动操作序列（除第一行外的每个奇数行都是操作序列）
4. 控制行数的关键是，该行输入正确，才进行下一行的输出，

#### 第二步：mar操作逻辑处理
>1. 规定方向数据
a。 Y轴正方向为N,X轴正方向为E,用数组表示方向位置，E方向为0位置，顺时针一次递增
b. E方向的移动为X+1,N方向的移动为Y+1
c. 左转操作为方向位置-1 [表达式：(N+4-1)%4]，右转操作为方向位置+1 [表达式：（N-1)%4]
d. 规定操作范围集合为[L/M/R]
e。 以上过程需要做边界检查，比如：移动操作时，需要判定范围大小
2. 按照操作序列的基本操作，根据1.b和1.c中的做相应的逻辑处理

#### 第三步：遍历所有组数据，输出处理结果

## 编译与运行
>1. 编译方式： g++ -o demo demo.cpp
2. 编译与测试运行环境：Linux version 3.10.107-1-tlinux2_kvm_guest-0046

## 数据使用证明
```
//程序要求输入
-bash-4.2$ ./demo 
5 5
1 2 N
LMLMLMLMM
3 3 E
MMM

1 3 N
5 3 E RIP
```

```
//输入错误提示
-bash-4.2$ ./demo 
5 5
66 66 S
start location input err, input again:
2 3 S
1 2 N
operation input err, input again:
LMLMLM
1 3 N
5
operation input err, input again:

2 4 W
1 3 N
```


```
//多组输入结果
-bash-4.2$ ./demo 
5 5 
1 2 N
LMLMLMLMM
1 3 N
MMM
2 4 S
LMLMLMMMML

1 3 N
1 5 N RIP
0 5 S RIP
```
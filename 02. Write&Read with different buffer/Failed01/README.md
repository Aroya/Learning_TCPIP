# Requirement

1. Linux/Ubuntu
2. c/c++ complier

# Complie

```shell
make
```

# Usage

Terminal 1

```shell
./server <server_port>
```

Terminal 2

```shell
./client <server_addr> <server_port>
```

# Function

这里尝试多次发送msg，结果client只能收到1次的msg

> socket
> connect
> read time: 0
> recv msg: Hello! msg_time: 0
>
> read time: 1
> recv msg:
> read time: 2
> recv msg:

这是因为，accept为条件触发循环，只有client调用connect时会触发

且client调用read，是直接从stream buffer中读数据，没有数据返回空字符串
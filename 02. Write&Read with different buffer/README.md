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

测试双方buffer不一致时处理bug

## 1

```
#define TEST_WLTB
//#define TEST_WLTB_SLEEP_TO_READ
```

可以看到因为超过了buffer，server RW 6次，client只读了3次未能读到所有数据

当双方buffer设置不一致时，需要特殊的处理`TODO`

## 2.

```cpp
#define TEST_WLTB
#define TEST_WLTB_SLEEP_TO_READ
```

可以看到因为超过了buffer，server RW 6次，client只读了3次，但是已经读到了第4次的数据
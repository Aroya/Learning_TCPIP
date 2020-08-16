### Introduction

本章进行进程间通信的基本实验

### Experiment

#### Pipe

read会阻塞，在child添加sleep，parent read时会阻塞

> main send: child send to pipe
> main recv: child send to pipe

#### TODO

有没有不会阻塞的方法呢？
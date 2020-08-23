### Theme

IO复用 - select

### Server

standard output

> select - doing select
> select - select done
> serv_skt 3: connection comein
> serv_skt 3: connection comein at 4
> select - doing select
> select - select done
> select - doing select
> select - select done
> clnt_skt 4: readable
> clnt_skt 4: recv: 111111111 111111111 00000
> select - doing select
> select - select done
> select - doing select
> select - select done
> clnt_skt 4: readable
> clnt_skt 4: recv: 111111111 111111111 00000
> select - doing select
> select - select done
> select - doing select
> select - select done
> clnt_skt 4: readable
> clnt_skt 4: recv: 111111111 111111111 00000
> select - doing select
> select - select done
> clnt_skt 4: readable
> clnt_skt 4: size 0
> select - doing select

### Client

复用Chapter2的client，加了sleep使select更直观

standard output

> socket
> connect
> sleep 3 s
> sleep 3 s done
> read time: 0
> Sending: 111111111 111111111 00000
> recv msg: writeBack from server
>  00 
> sleep 3 s
> sleep 3 s done
> read time: 1
> Sending: 111111111 111111111 00000
> recv msg: writeBack from server
>  00 
> sleep 3 s
> sleep 3 s done
> read time: 2
> Sending: 111111111 111111111 00000
> recv msg: writeBack from server
>  00


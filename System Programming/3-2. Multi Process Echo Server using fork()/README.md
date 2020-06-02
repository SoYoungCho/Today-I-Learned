# Multi Process Server using fork()
### Implemented example : Echo Server

- This is an implementation of Multi Process Echo Server using fork() to support multi clients per server.

## Server
- Server takes Port number as an argument.
- When connected with a client, makes new process using fork().
- Parent server process prints information (IP, Port number) of connected client and waits for another client to be connected.  
- Child server process takes a command line from the client, sends and receives the echoed command from the server. (repeat)

## Flowchart

![](https://postfiles.pstatic.net/MjAyMDA2MDJfMTY0/MDAxNTkxMTA0Njc4NTI3.tgcRvk3v0aHu5i9QNYk7NoaJxZzE8wm8lEPLDRX2mbYg.FFxxhztoc6L7ZWK3YB1lgKMBQaa1X4MkzIKiVC_loEog.PNG.wazoskee/image.png?type=w773)

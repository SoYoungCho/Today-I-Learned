# ls Command Implementation using socket

- This is an implementation of 'ls command' using socket to communicate with server and client.  
- Client socket uses socket(), connect(), write(), read(), etc.  
- Server socket uses socket(), connect(), write(), read(), etc to receive command from client and processes the command and returns(sends) the result to the client. 
- Client displays the command (ls) result. Also, client uses inet_ntoa() and ntohs() to print connected client's IP address and Port number.
---
- fork() is not used in this code. Check 3-2 to find codes with fork() implemented.
- ls options are not implemented.

## Flowchart

![](https://postfiles.pstatic.net/MjAyMDA2MDJfMjQy/MDAxNTkxMTA0NjYyNDkw.CWaQapeVeIHX2JK48UBi2vklILEOWZfzeHS8x-1anfwg.e-AgLo73RsF86YDIRJAIy2XHocU-EJh_oNDfie7virQg.PNG.wazoskee/image.png?type=w773)

# Build
Build with Qt (https://www.qt.io/ide/)

# Examples
Go to `./scripts`


### Binary add plus 1
returns: T1000
```bash
echo T111 | ./tm_bplus1
```

### IF
input: Tiu  
if i=1 run: ./tm_bplus1 with u as input  
if i=0 run: ./tm_bminus1 with u as input  
returns: T011
```bash
echo T0100 | ./IF | ./THEN | ./tm_bplus1 | ./ELSE | ./tm_bminus1 | ./ENDIF
```

# Build
Build with Qt (https://www.qt.io/ide/)

# Examples
Go to `./scripts`


### Binary add plus 1 (or not)
```bash
echo T111 | ./tm_bplus1
```
returns: R1000

```bash
echo R111 | ./tm_bplus1
```
returns: R111

### IF
input: Tiu  
if i=1 runs: ./tm_bplus1 with u as input  
if i=0 runs: ./tm_bminus1 with u as input
```bash
echo T0100 | ./IF | ./THEN | ./tm_bplus1 | ./ELSE | ./tm_bminus1 | ./ENDIF
```
returns: T011

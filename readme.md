# building
This started life on linux, but you can compile it on windows too, just use `gcc main.c -omain` it dosnt really use much else. oh yeah, i use miniGw to get the compiler and stuff

# repel
| command | use              |
| ------- | ---------------- |
| !stack  | prints the stack |
| !exit   | exits repl       |

# commands
| sym   | Effects         |
| ----- | --------------- |
| add   | [1] +  [0]=>top |
| sub   | [1] -  [0]=>top |
| div   | [1] /  [0]=>top |
| mul   | [1] *  [0]=>top |
| bsl   | [1] << [0]=>top | shift [1] left  by [0] |
| bsr   | [1] >> [0]=>top | shift [1] right by [0] |
| pop   | [0]             |
| print | [0]             |
| push  | arg => top      |

```
>push 10
>push 5
>add
>print
15
```


# motivation
I was watching tsoding's videos on [PORTH](https://gitlab.com/tsoding/porth) and kinda stopped half way though, and thought it would fun to impliment something like that, so this is that. 
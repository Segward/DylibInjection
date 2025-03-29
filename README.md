## Dylib Injection

The dylib is injected using the `DYLD_INSERT_LIBRARIES` environment variable. It uses lua version 5.4.7.

### Usage

```shell
$ gcc -dynamiclib -o payload.dylib payload.c -I./lua-5.4.7/src -L./lua-5.4.7/src -llua -lm -ldl -lpthread 
$ DYLD_INSERT_LIBRARIES=./payload.dylib ./target
```

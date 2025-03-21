## Dylib Injection

This is a simple dylib injection tool that injects a dylib into a target process. The dylib is injected using the `DYLD_INSERT_LIBRARIES` environment variable.

### Usage

```shell
$ gcc -dynamiclib -o payload.dylib payload.c -lpthread -ldl
$ DYLD_INSERT_LIBRARIES=./payload.dylib ./target
```

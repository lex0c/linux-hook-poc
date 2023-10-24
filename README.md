# POC - Hooking `readdir` to Hide Files

Hooking is an advanced technique that allows the interception and modification of function calls.

## Compilation

```sh
gcc -shared -fPIC -o hook.so hook.c -ldl
```

This command compiles the code into a shared library named `hook.so`.

## Testing

Create some files to be hidden:
```sh
touch hidden_file1.txt
touch hidden_file2.txt
touch hidden_file3.txt
touch foobar.txt
```

Run:
```sh
LD_PRELOAD=./hook.so ls
```

The library is preloaded using the `LD_PRELOAD` environment variable, which causes the system readdir function to be replaced by the one defined in the code.

This command will execute `ls` with the hooked `readdir`, hiding the specified files from the listing.


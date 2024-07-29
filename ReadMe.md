## Building
```
git submodule update --recursive --init
mkdir build
cd build
cmake3 ..
cmake3 --build .
```

## Command line options

- `name/n [name]`- ALFIPbus server name
- `log_file/f [filename]` (`f`)- Log file name (if not specified, logs will be sent to std::cout)
- `link/l [IP address]:[remote port]` (`l`) - set the IP address and port for consecutive links (can be used multiple times)


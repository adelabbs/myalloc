# MyAlloc

Illustration of memory allocation / deallocation mechanisms inspired 
by the malloc() / free() functions of the standard unix library.

The memory allocation algorithm is based on the First Fit method [[1]](#1).

## Running

Make sure the gtk library is installed before running the gui. You can install gtk with :

```bash
sudo apt-get install build-essential libgtk-3-dev
```

Build the entire project with :
```bash
make

#Or only the modules you want

make demo test gui
```

Then you can choose to run 1 of 3 programs : demo, test or gui
```bash
./demo

./test

./gui
```

## References

<a id="1">[1]</a> 
Robson, J. (1977). Worst Case Fragmentation of First Fit and Best Fit Storage Allocation Strategies. Comput. J., 20, 242-244.

<a id="2">[2]</a> 
Johnstone, M.S., & Wilson, P.R. (1998). The memory fragmentation problem: solved? ISMM '98.

## Contributors

- Geoffroy Keime - [@GeoffroyK](https://github.com/GeoffroyK)
- Lucas Olivieri - [@Lucas-Olivieri](https://github.com/Lucas-Olivieri)
- Adel Abbas - [@dedely](https://github.com/dedely)

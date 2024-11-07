cd ..

mkdir build && cd build

cmake -DFIZZY_WASI=ON -DFIZZY_TESTING=ON ..

cmake --build .

bin/fizzy-wasi ../test/smoketests/wasi/helloworld.wasm

bin/fizzy-unittests

bin/fizzy-bench ../test/benchmarks/

```
$ bin/fizzy-bench ../test01/
2024-11-07T07:22:24+00:00
Running bin/fizzy-bench
Run on (2 X 3241.1 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x1)
  L1 Instruction 32 KiB (x1)
  L2 Unified 512 KiB (x1)
  L3 Unified 32768 KiB (x1)
Load Average: 1.27, 1.04, 0.79
---------------------------------------------------------------------------------------
Benchmark                             Time             CPU   Iterations UserCounters...
---------------------------------------------------------------------------------------
fizzy/parse/fibonacci              1.35 us         1.35 us       563888 rate=56.4208M/s size=76
fizzyc/parse/fibonacci             1.24 us         1.24 us       529543 rate=61.4287M/s size=76
 wabt/parse/fibonacci              2.98 us         2.97 us       232669 rate=25.5817M/s size=76
wasm3/parse/fibonacci             0.319 us        0.314 us      2324816 rate=242.393M/s size=76
fizzy/instantiate/fibonacci        1.64 us         1.64 us       486588
fizzyc/instantiate/fibonacci       1.55 us         1.55 us       453472
 wabt/instantiate/fibonacci        5.54 us         5.44 us       139716
wasm3/instantiate/fibonacci        1.35 us         1.35 us       507458

fizzy/execute/fibonacci/24         6880 us         6633 us          114
fizzyc/execute/fibonacci/24        6228 us         6227 us          106
 wabt/execute/fibonacci/24        22301 us        22293 us           30
wasm3/execute/fibonacci/24         3166 us         3166 us          225

fizzy/execute/fibonacci/40     14929578 us     14708901 us            1
fizzyc/execute/fibonacci/40    14636962 us     14437357 us            1
 wabt/execute/fibonacci/40     49374439 us     49159368 us            1
wasm3/execute/fibonacci/40      7122312 us      7063483 us            1
```
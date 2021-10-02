# libmcc

Generic collections for C.

## Build

`libmcc` is built using [meson](https://mesonbuild.com/):

```sh
meson setup build
cd build
ninja
```

## Usage [![codedocs](https://codedocs.xyz/elementbound/mcc.svg)](https://codedocs.xyz/elementbound/mcc/index.html)

Docs are generated during build via [Doxygen](https://www.doxygen.nl/). They are placed under `build/docs`.

For examples on usage, see [src/samples](src/samples).

## Why

There are multiple collection libraries for C out there, all with different approaches and pros/cons.
`libmcc` is an experiment at an approach that's easy to maintain ( i.e. no specializations generated via. preprocessor ) and use.

## How

The core of `libmcc` is the `vector`, an array that resizes itself as more elements are added. 
This is done using a fat pointer - the data is prepended with a header struct, and the client code only receives a pointer to the actual data.

Consider the following:

```c
int* vector = mcc_vector_create();
```

```
+--------+------+------+------+------+------+
| header | item | item | item | item | ...  |
+--------+------+------+------+------+------+
           ^
           int* vector
```

All other implemented collections are either directly or indirectly backed by vectors:

* `treeset.h` - A vector with elements ordered based on comparator; looking up items is done via binary search
* `hashset.h` - A vector segmented into logical buckets; addition and search is done by hashing and looking up appropriate bucket
* `treemap.h` - Keys are stored in a treeset, values are stored in a vector, in the same order as keys
* `hashmap.h` - Keys are stored in a hashset, values are stored in a vector, in the same order as keys

This leads to a neat feature - easy iteration and item access. No matter what kind of collection:

* it can be treated as a simple array
* it can be iterated as a simple array

## License

`libmcc` is licensed under the MIT license.

See [LICENSE](./LICENSE).

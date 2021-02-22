# Tuya Embedded Gateway Testing SDK

[English version](README.md) | [中文版](README_cn.md)

## Introduction

### Directory

```shell
.
├── CHANGE_LOG.md  
├── Makefile
├── README.md
├── demo
│   └── demo.c
└── sdk
    ├── include
    │   ├── tuya_prod_test.h
    │   └── tuya_testframe_handle.h
    └── lib
        ├── shared
        │   ├── libtuya_prodtest.so
        │   └── libtuya_prodtest.so.stripped
        └── static
            ├── libtuya_prodtest.a
            └── libtuya_prodtest.a.stripped
```

### Library

This SDK provides the dynamic library, static library, strip library. And the static library is selected by default.

## Getting started

* Command for local compilation:

    ```
    make
    ```
* Command for local clear:

    ```
    make clean
    ```
* The path of the executable file:

    `output/bin`

## Demo reference

Please see the `demo` directory for details.

## Technical support

- [Tuya Developer](https://developer.tuya.com/en/)
- [Tuya Smart Documentation](https://developer.tuya.com/en/docs/iot)
- [Technical ticket](https://service.console.tuya.com)

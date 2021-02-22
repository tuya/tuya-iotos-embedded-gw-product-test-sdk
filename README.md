# Tuya Embedded Gateway Product Test SDK

[English](README.md) | [中文版](README_cn.md)

## Introduction

### directory structure
<pre>.
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
</pre>

### lib
Support dynamic library, static library, strip library, static library is selected by default

## Get Started
### local compilation
`make`

### local clear
`make clean`

### executable file
stored in the `output/bin` directory

## Demo Reference
See the `demo` directory for details

## Support
- Tuya Developer Webiste:https://developer.tuya.com/en/
- Tuya Smart Help Center: https://support.tuya.com/en/help
- Technical Support Council: https://service.console.tuya.com





# Tuya 嵌入式网关产测 SDK

[English version](README.md) | [中文版](README_cn.md)

## 介绍

### 目录结构
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
支持动态库，静态库，strip库，默认选择静态库

## 快速开始
* 本地编译

```
make
```

* 本地清除

```
make clean
```

* 可执行文件路径

    `output/bin`

## 案例参考
详见 `demo` 示例

## 如何获得技术支持

- [开发者中心](https://developer.tuya.com/cn/)
- [IoT平台文档中心](https://developer.tuya.com/cn/docs/iot)
- [技术支持工单中心](https://service.console.tuya.com)


#目录结构
.
├── CHANGE_LOG.md
├── demo
│   └── demo.c
├── Makefile
├── README.md
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

#lib
支持动态库，静态库，strip库，默认选择静态库

# 本地编译
make

#本地清除
make clean

#可执行文件
存放在output/bin目录下

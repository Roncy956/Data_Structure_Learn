# 数据结构学习代码 (Data Structures Learning)

本仓库是个人在学习《数据结构》过程中的代码实践，主要使用 C 语言手写实现各种经典的数据结构。

## ⚠️ 重要声明 (Disclaimer)

1. **仅供学习交流**：本仓库代码主要为了练习和验证基础数据结构的概念与逻辑。
2. **不严谨之处**：代码在内存管理（如某些情况下的内存泄漏、野指针防御）、边界条件处理、错误处理机制（如 malloc 失败的情况）等方面可能存在不严谨的地方。
3. **请勿用于工程/生产环境**：这里的代码**绝对不能**作为工业级工程项目（Production-ready）的参考。实际工程中请使用标准库或经过严格测试的开源库。

## 目录结构

```
Learn/
├── CMakeLists.txt
├── README.md
└── src/
    ├── 00/                     # 零基础 / 指针练习
    │   └── pointer.c
    ├── 00utils/                # 公共头文件
    │   ├── boolean.h           # boolean / true / false 定义
    │   └── total.h             # 汇总头（stdio + malloc + boolean）
    ├── chapter01/              # 线性表
    │   ├── 01_static_linear_list.c
    │   ├── 02_dynamic_linear_list.c
    │   ├── 03_linked_list_bok_style.c
    │   └── 04_linked_list_industrial_lnode.c
    └── chapter02/              # 栈与队列
        ├── 01_stack_sequential.c
        ├── 02_stack_linked.c
        ├── 03_queue_null1.c        # 循环队列：牺牲一个空槽
        ├── 04_queue_tag_flag.c     # 循环队列：标志位 isOut
        ├── 05_queue_len.c          # 循环队列：计数器 len
        └── 06_queue_linkNode.c     # 链式队列
```

## 环境要求

- CMake >= 3.28
- 支持 C17 的编译器（MinGW-w64 GCC / clang / MSVC 均可）

## 构建

项目采用「**一个 .c = 一个可执行文件**」的结构。因为每个 .c 都是带 `main()` 的独立练习程序，且存在同名函数（`push` / `pop` / `createQueue` 等），所以**不能**编进同一个 target，否则链接期会报 `multiple definition`。

### 方式一：CLion（推荐）

1. 用 CLion 打开项目根目录，它会自动识别 `CMakeLists.txt` 并生成构建目录 `cmake-build-default/`。
2. 右下角状态栏选择要运行的 target（列表里就是每一节课的名字，如 `chapter02_04_queue_tag_flag`）。
3. 点运行 / 调试图标即可，CLion 会自动编译。

> 如果新建了 .c 文件但在 target 下拉框里看不到，点 CMake 面板的 **Reload CMake Project**（刷新图标）重新加载一次。

### 方式二：命令行

```bash
# 1. 配置（只需一次，之后改源码不用重复）
cmake -S . -B build -G "MinGW Makefiles"

# 2. 编译全部
cmake --build build

# 3. 只编译某一个
cmake --build build --target chapter02_04_queue_tag_flag

# 4. 运行
./build/chapter02_04_queue_tag_flag.exe      # Windows
# ./build/chapter02_04_queue_tag_flag        # Linux / macOS

# 5. 清空重来
rm -rf build
```

## 添加新的源文件

**只需要把 .c 文件放进 `src/` 下的任意子目录，不要修改 `CMakeLists.txt`。**

`CMakeLists.txt` 用 `file(GLOB_RECURSE ... CONFIGURE_DEPENDS)` 自动扫描 `src/` 下所有 `.c`，为每个文件生成一个独立可执行文件。

以新增 `src/chapter03/01_string.c` 为例：

1. 创建文件，写好 `main()`：

   ```c
   #include "total.h"     // 直接引公共头，不需要写 ../00utils/total.h

   int main(void) {
       printf("hello\n");
       return 0;
   }
   ```

2. 先跑一次**全量构建**，让它重新扫描目录并生成新 target：

   ```bash
   cmake --build build      # 会自动触发重新配置，日志里能看到新 target
   ```

   自动多出的 target 名字规则是 **`目录名_文件名`**：

   ```
   chapter03_01_string.exe
   ```

   > 注意：新增文件后**不要**直接 `cmake --build build --target chapter03_01_string`，
   > 会报 `No rule to make target` —— 此时 CMake 还没重新配置，target 尚不存在。
   > 先跑一次全量构建（或 `cmake -S . -B build`）就正常了。

3. 若在 CLion 里，target 下拉框没刷新出来，Reload CMake Project 一次。

### 规则说明

| 规则 | 说明 |
|---|---|
| target 命名 | `<所在目录名>_<文件名不含扩展名>`，如 `src/chapter02/04_queue_tag_flag.c` → `chapter02_04_queue_tag_flag`；`src/00/pointer.c` → `00_pointer` |
| 头文件引用 | 公共头目录 `src/00utils` 已加入 include path，任意层级的文件都可以直接 `#include "total.h"` 或 `#include "boolean.h"` |
| 没有 `main()` 的文件 | 自动跳过，不生成 target（配置阶段会打印 `跳过（无 main，不生成可执行文件）: ...`） |
| 分隔符 | 文件名建议用下划线，不要用空格或中文，否则 target 名和命令行调用都会很别扭 |

### 千万不要做的事

不要往 `add_executable()` 里手写文件路径：

```cmake
# ❌ 错误：foreach 每循环一次都会执行这句，
#    等于把 06_queue_linkNode.c 塞进了所有 target
add_executable(${_dirname}_${_name} ${src}
        src/chapter02/06_queue_linkNode.c)
```

后果是一个可执行文件里出现两个 `main()`，链接报 `multiple definition of 'main'`。

## 常见问题

**Q：报 `multiple definition of 'main'` / `'push'` / `'createQueue'`**
A：有文件被重复加进了同一个 target。检查 `CMakeLists.txt` 的 `add_executable()` 里有没有手写路径（见上一节），删掉即可。

**Q：报 `undefined reference to 'WinMain'`**
A：该 `.c` 文件没有 `main()`，却被当成了可执行程序。正常情况会自动跳过；若仍报错，检查 `main` 是否写成了宏或拼写有误（如 `mian`）。

**Q：报 `No such file or directory: total.h`**
A：`#include` 写法没问题的话，多半是 CMake 配置没生效。删掉 `build/`（或 `cmake-build-default/`）重新配置一次。

**Q：`error: 'nullptr' undeclared`**
A：`nullptr` 是 C++ 关键字，C 语言里要用 `NULL`。

**Q：新增 .c 后报 `No rule to make target 'xxx'`**
A：CMake 还没重新配置，新 target 还不存在。先跑一次全量构建 `cmake --build build`，或手动 `cmake -S . -B build`。

**Q：CLion 里找不到新加的 target**
A：点 CMake 面板的 Reload CMake Project 刷新一次。

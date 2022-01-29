# 内容物

## PrimitiveDataType.hpp

プリミティブなデータ型（ size_t, int 等 ） を宣言したファイル。

### インクルード

```cpp
#include <cstddef> // size_t 用
#include <cstdint> // intXX_t 用
```

### マクロと using

```cpp
// size_t
using IndexUint = CRAFTERRA_SIZE_T;
using SizeUint = CRAFTERRA_SIZE_T;
// int, uint
using Int64 = CRAFTERRA_INT64_T;
using Uint64 = CRAFTERRA_UINT64_T;
using Int32 = CRAFTERRA_INT32_T;
using Uint32 = CRAFTERRA_UINT32_T;
using Int16 = CRAFTERRA_INT16_T;
using Uint16 = CRAFTERRA_UINT16_T;
using Int8 = CRAFTERRA_INT8_T;
using Uint8 = CRAFTERRA_UINT8_T;
```

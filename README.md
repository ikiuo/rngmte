# RngMTE

C++ の std::mersenne\_twister\_engine に内部の処理方法を追加したテンプレート クラスです。

C++ 言語仕様 C++14 で記述してあります。

```
namespace RngMTE {
  template <typename UIntType, size_t W, size_t N, size_t M,
            size_t R, UIntType A, size_t U, UIntType D,
            size_t S, UIntType B, size_t T, UIntType C,
            size_t L, UIntType F,
            int P /* 処理方法(追加) */>
  class RngMTE;
}
```

include ディレクトリのヘッダ ファイル rngmte.hpp を <code>#include</code> して使用します。

標準の std::mt19937 と std::mt19937_64 に対応する型を既に定義しています。

| std::mt19937       | std::mt19937_64    |
|:-------------------|:-------------------|
| RngMT19937SeqB32   | RngMT19937SeqB64   |
| RngMT19937SeqC32   | RngMT19937SeqC64   |
| RngMT19937SeqBP32  | RngMT19937SeqBP64  |
| RngMT19937SeqCP32  | RngMT19937SeqCP64  |
| RngMT19937SeqSB32  | RngMT19937SeqSB64  |
| RngMT19937SeqSC32  | RngMT19937SeqSC64  |
| RngMT19937BlkB32   | RngMT19937BlkB64   |
| RngMT19937BlkC32   | RngMT19937BlkC64   |
| RngMT19937BlkBV32  | RngMT19937BlkBV64  |
| RngMT19937BlkCV32  | RngMT19937BlkCV64  |
| RngMT19937BlkBT32  | RngMT19937BlkBT64  |
| RngMT19937BlkCT32  | RngMT19937BlkCT64  |
| RngMT19937BlkSB32  | RngMT19937BlkSB64  |
| RngMT19937BlkSC32  | RngMT19937BlkSC64  |
| RngMT19937BlkSBV32 | RngMT19937BlkSBV64 |
| RngMT19937BlkSCV32 | RngMT19937BlkSCV64 |
| RngMT19937BlkSBT32 | RngMT19937BlkSBT64 |
| RngMT19937BlkSCT32 | RngMT19937BlkSCT64 |


## 処理の種類

上記 <code>RngMT19937</code> の後続表記で処理の種類を説明します。

■ <code>RngMT19937</code> 直後の <code>Seq</code> と <code>Blk</code>

| 表記 | 内容 |
|:--|:--|
| <code>Seq</code> | 生成毎に内部要素(N個)を１つ更新<br>生成負荷は安定的 |
| <code>Blk</code> | 内部要素を一括で更新<br>N 回生成毎に突出した高負荷が発生 |

■ <code>Seq / Blk</code> の後続

- <code>S</code>
  - あり : SIMD を明示的に使用
  - なし : SIMD 使用はコンパイラの最適化次第
- <code>B / C</code>
  - <code>B</code> : 条件分岐を積極的に使用
  - <code>C</code> : 条件代入へのコンパイラ最適化を期待

■ <code>Seq {S}[BC]</code> の後続

- <code>P</code>
  - なし : 要素更新→抽出(生成) の処理順で依存関係あり
  - あり : {更新済み要素}から抽出(生成)と次要素の事前更新 で依存関係を分離

■ <code>Blk {S}[BC]</code> の後続

- <code>V</code>
  - 要素を一括更新した後に抽出(生成)も一括で実行
    - 要素と抽出は別ループ
- <code>T</code>
  - 「要素→抽出」のループで一括処理

## ストリーム入出力

<code>operator&lt;&lt;</code> で使用した型と <code>operator&gt;&gt;</code> で取り込む型が違うと正常動作しません。

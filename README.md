# so_long
## 概要
42Tokyoの課題の一つ。2Dゲーム。

## ゲーム詳細
イルカが魚を食べて地球を脱出する小さな2Dゲーム。

## マップ
### 構成
- 0 : 何もない空間
- 1 : 壁
- C : 収集物
- E : マップの出口
- P : プレイヤーのスタート位置

### ルール
- マップは壁で囲まれていなければならない
- マップには少なくとも
  - 1つの出口
  - 1つのお宝
  - 1つのスタート地点
  が必要
- 地図は長方形

#### Example
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

※ ファイルに何らかの設定ミスがあった場合、プログラムは適切に終了し、"Error\n"を出力する

## 使用関数
- open, close, read, write, printf, malloc, free, perror, strerror, exit
- MinilibX

## 実行
```
$ git clone https://github.com/RIshimoto/so_long
$ cd so_long
$ make all
$ ./so_long
```

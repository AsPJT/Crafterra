# CrafterraTest-Linux

OpenSiv3Dを用いたLinux系OSへのセットアップ方法。

## 動作確認済み環境

- Ubuntu 20.04.3 LTS 64bit
- cmake 3.16.3 

## 導入方法

### 1. OpenSiv3Dのインストール


 [公式リファレンス](https://zenn.dev/reputeless/books/siv3d-documentation/viewer/setup#3.-linux-%E3%81%A7-siv3d-%E3%82%92%E5%A7%8B%E3%82%81%E3%82%8B) <br>

上リンクの手順を参考に、`libSiv3D.a`の生成までを行います。

### 2. ビルド環境の構築

2-1. ターミナルにて、カレントディレクトリを`CrafterraTest-Linux/CrafterraTest-Linux`に移動します。

2-2. ビルド用のディレクトリを作成します。
```
$ mkdir build ; cd build
```
<br>

2-3. ビルドファイルを生成します。(ビルドシステムにはninjaを利用します。)<br>
処理が完了したら、前のディレクトリに戻ります。
```
$ cmake -G "Ninja" ..
$ cd ..
```
<br>

2-4. CMakeLists.txtの'custom'項目を編集します。<br>
以下の山括弧<>内を適切な形に書き換えてください : 

```
# ----- custom -----
set(OPENSIV3D_SOURCE_DIRECTORY "<OpenSiv3D全体のソースへのパス(末尾は /OpenSiv3D)>")
set(CRAFTERRA_SOURCE_DIRECTORY "<Crafterra全体のソースへのパス(末尾は /Crafterra)>")
# ------------------
```
<br>
これで、ビルド環境が整いました。


### 3. Resourcesの流用

3-1. resourcesディレクトリ `OpenSiv3D/Linux/App/resources` を探します。

3-2. resourcesディレクトリを `CrafterraTest-Linux/CrafterraTest-Linux/App` にコピー&ペーストします。

### 4. 実行

4-1. ファイルの位置関係が以下のようになっていることを確認してください。

``` 
(CrafterraTest-Linux/CrafterraTest-Linux) --|- CMakeLists.txt
                                            |- Source.cpp    
                                            |- build - (各種ファイル)
                                            |- App  ----------------|- resources/engine - (各種ファイル)
                                                                    |- Setting.tsv
```

4-2. ターミナルにて、カレントディレクトリを`CrafterraTest-Linux/CrafterraTest-Linux/App`に移動します。

4-3. 以下を実行し、実行可能ファイルを生成します。

```
$ cmake --build ../build
```
<br>

4-4. プログラムを実行します。

```
$ ./Source
```
<br>

無事に実行できたら、作業は終了です。

4-3と4-4 を行うことで、ビルド内容が更新されます。

## その他

Linux環境でのセットアップでお困りの際は、ぺるき までお願いします。<br>
<GitHub: https://github.com/TadaTeruki ><br>
<Twitter: https://twitter.com/PerukiFUN ><br>

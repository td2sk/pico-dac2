Language: [English](README.md) | [日本語](README.ja.md)

# Raspberry Pi Pico USB DAC

Raspberry Pi Pico を USB DAC（Digital-to-Analog Converter）として機能させるためのファームウェアです。USB Audio Class 2.0（UAC2）に対応しており、PC やスマートフォンなどのホストに接続するだけで、高品質なオーディオ出力デバイスとして利用できます。

## 主な特徴

- **USB Audio Class 2.0 対応:**
  - ドライバーのインストールなしで多くの OS（Windows, macOS, Linux）で動作します。
  - Feedback Endpoint によるフロー制御に対応
- **ハイレゾ対応:**
  - **サンプリング周波数:** 44.1kHz, 48kHz, 88.2kHz, 96kHz
  - **量子化ビット数:** 16bit, 24bit, 32bit
- **HID コントロール:**
  - ファームウェアのカスタム制御用に HID（Human Interface Device）エンドポイントを実装しています。(現状はダミーデータ送受信のみ。将来機能追加予定)
- **独自 USB スタックの利用**
  - 必要最小限の機能を備えた Raspberry Pi Pico 用の USB スタックを独自実装しています。
    - 将来的には USB プロトコルスタックのみを独立したライブラリにする予定です

## 必要なハードウェア

- Raspberry Pi Pico
- I2S 対応の DAC モジュール（PCM5102A 想定）
- USB ケーブル

## ビルド方法

### 1. 開発環境のセットアップ

Raspberry Pi Pico の C/C++開発環境をセットアップする必要があります。公式ドキュメントを参考に、Pico SDK とツールチェーンをインストールしてください。

- [Getting started with Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

### 2. ソースコードの取得

```bash
git clone https://github.com/td2sk/pico-dac2
cd pico-dac2
```

### 3. ビルド

標準的な CMake のビルド手順でファームウェアをビルドします。

```bash
mkdir build
cd build
cmake ..
make
```

ビルドが成功すると、`build`ディレクトリ内に`mdac_adc2.uf2`という名前のファイルが生成されます。

### GPIO ピンの変更

I2S に使用する GPIO ピンは`CMakeLists.txt`で変更できます。デフォルト設定は以下の通りです。

- **I2S DATA:** GPIO 22
- **I2S BCLK:** GPIO 20
- **I2S LRCLK:** GPIO 21

```cmake
# CMakeLists.txt

# user configurations
set (PICODAC_I2S_DATA_PIN 22 CACHE STRING "I2S Data Pin")
set (PICODAC_I2S_BASE_CLOCK_PIN 20 CACHE STRING "I2S Base Clock Pin. LRCLK is BASE + 1")
```

## インストール

1. Raspberry Pi Pico の`BOOTSEL`ボタンを押しながら、PC に USB ケーブルで接続します。
2. PC に`RPI-RP2`という名前のマスストレージデバイスとして認識されます。
3. ビルドして生成された`mdac_adc2.uf2`ファイルを、その`RPI-RP2`ドライブにドラッグ＆ドロップします。
4. コピーが完了すると、Pico は自動的に再起動し、ファームウェアの実行が開始されます。

## 使い方

1. I2S DAC モジュールを、`CMakeLists.txt`で設定した GPIO ピンに正しく接続します。
2. ファームウェアを書き込んだ Pico をホスト（PC など）に USB で接続します。
3. ホストの OS は、`mdac_adc2`（または同様の名前）という新しいオーディオ出力デバイスを自動的に認識します。
4. OS のサウンド設定で、このデバイスを出力先に選択し、音楽などを再生してください。

## HID 通信

このファームウェアは、カスタムコマンドを送受信するための HID インターフェースを備えています。`tools/comm.py` は、Python の `hid` ライブラリを使用してデバイスと通信する簡単なサンプルスクリプトです。

ベンダー ID と プロダクト ID は `CMakeLists.txt` で設定できます。

- **ベンダー ID:** `PICODAC_VENDOR_ID` (デフォルト値: `0xcafe`)
- **プロダクト ID:** `PICODAC_PRODUCT_ID` (デフォルト値: `0xbabe`)

## TODO

- [ ] ドキュメントの整備
- [ ] HID によるカスタム制御
- [ ] HID によるデバッグ/統計情報の取得
- [ ] USB プロトコルスタックを独立したライブラリ化

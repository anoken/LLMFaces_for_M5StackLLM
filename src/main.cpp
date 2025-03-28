/**
 * Copyright (c) 2025 aNoken
 * @file main.cpp
 *
 * @Hardwares: M5Stack with M5Module-LLM and FacesKeyboard
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5Module-LLM: https://github.com/m5stack/M5Module-LLM
 */

//======================================================================
// インクルード
//======================================================================
#include <M5GFX.h>
#include <M5ModuleLLM.h>
#include <M5Unified.h>
#include <gob_unifiedButton.hpp>
#include "config.h"
#include "convertHiraganaTable.h"
#include "sound.h"

//======================================================================
// 定数定義
//======================================================================
/** @brief シリアル通信ポート */
#define CommSerialPort Serial
/** @brief キーボード割り込みピン */
#define FACESKEYBOARD_INTPIN 1

// バッファサイズの定義
#define SERIAL_RX_BUFFER_SIZE 2048  // 受信バッファサイズ（デフォルトは256バイト）
#define SERIAL_TX_BUFFER_SIZE 2048  // 送信バッファサイズ（デフォルトは256バイト）

//======================================================================
// クラス定義
//======================================================================
/**
 * @brief FacesKeyboard クラスの実装
 * I2C通信を使用してキーボードモジュールと通信するクラス
 */
namespace m5 {
class I2C_Device;  // 前方宣言
class I2C_Class;   // 前方宣言

class FacesKeyboard_Class : public I2C_Device {
 public:
  static constexpr std::uint8_t DEFAULT_ADDRESS = 0X08;

  FacesKeyboard_Class(std::uint8_t i2c_addr = DEFAULT_ADDRESS,
                      std::uint32_t freq = 400000, I2C_Class *i2c = &In_I2C)
      : I2C_Device(i2c_addr, freq, i2c) {}

  uint8_t GetKey() {
    uint8_t res = 0;
    res = readRegister8(0x00);
    return res;
  }

 private:
};
}  // namespace m5

//======================================================================
// グローバル変数
//======================================================================
using namespace m5;
goblib::UnifiedButton unifiedButton;

// LLM関連
static M5ModuleLLM module_llm;
static String llm_work_id;
static String question;
static String answer = "";
static bool task_llm_ready = false;
static bool end_flag = false;

// UI関連
static M5Canvas canvas(&M5.Display);
static portMUX_TYPE display_mutex = portMUX_INITIALIZER_UNLOCKED;
static bool input_mode = true;
static String input_buffer = "";
static bool question_ok = false;

// キーボード
static FacesKeyboard_Class kbd;

//======================================================================
// ユーティリティ関数
//======================================================================
/**
 * @brief ビープ音を鳴らす
 */
static void beep() { 
  sound_play(SOUND_SQUARE, 440, 50); 
}

/**
 * @brief エラーメッセージを表示
 * @param msg 表示するメッセージ
 */
static void error_message(String msg) {
  portENTER_CRITICAL_ISR(&display_mutex);
  canvas.setTextColor(WHITE, RED);
  canvas.println(msg);
  canvas.setTextColor(WHITE, BLACK);
  canvas.pushSprite(4, 4);
  portEXIT_CRITICAL_ISR(&display_mutex);

  M5.Speaker.tone(440, 800);  // Error
  delay(1000);
}

/**
 * @brief システムメッセージを表示
 * @param msg 表示するメッセージ
 * @param lf 改行の有無
 */
static void system_message(String msg, bool lf = true) {
  portENTER_CRITICAL_ISR(&display_mutex);
  M5.Display.fillRect(0, M5.Display.height() - 28, M5.Display.width(), 28,
                      BLACK);

  M5.Display.setTextColor(CYAN);
  M5.Display.drawString(msg, 4, M5.Display.height() - 24);

  portEXIT_CRITICAL_ISR(&display_mutex);
}

/**
 * @brief 画面をクリア
 */
void clear() {
  portENTER_CRITICAL_ISR(&display_mutex);
  canvas.setCursor(0, 0);
  canvas.clear();
  canvas.pushSprite(4, 4);
  portEXIT_CRITICAL_ISR(&display_mutex);
}

//======================================================================
// LLM関連関数
//======================================================================
/**
 * @brief LLMの初期化
 * @param lang 使用する言語 ("en":英語, "jp":日本語)
 */
static void LLM_setup(String lang) {
  // Reset LLM
  int err = module_llm.sys.reset();
  if (err != MODULE_LLM_OK) {
    error_message("Error: Reset LLM failed");
  }

  // Setup LLM
  while (1) {
    system_message("Setup LLM");

    m5_module_llm::ApiLlmSetupConfig_t llm_config;
    llm_config.model = MODEL;
    llm_config.max_token_len = 1023;

    if (lang == "en") {
      llm_config.prompt = "You are StackChan, a super cute robot.";
    } else if (lang == "jp") {
      llm_config.prompt =
          "あなたはなまえはスタックチャンです。スーパーカワイイロボットです。";
    }

    llm_work_id = module_llm.llm.setup(llm_config);
    if (llm_work_id == "") {
      error_message("Error: Setup LLM failed");
      delay(500);
      continue;
    }
    system_message("LLM Work ID:" + llm_work_id);
    break;
  }

  beep();
}

/**
 * @brief LLMに質問を送信
 * @param question 質問文
 */
void talk(String question) {
  // Push question to LLM module and wait inference result
  module_llm.llm.inferenceAndWaitResult(
      llm_work_id, question.c_str(),
      [](String &result) {
        answer += result;
      },
      5000, "llm_inference");
  end_flag = true;
}

//======================================================================
// UI関連関数
//======================================================================
/**
 * @brief 入力モードを表示
 */
void show_input_mode() {
  M5.Display.fillRect(0, M5.Display.height() - 28, M5.Display.width(), 28,
                      BLACK);
  M5.Display.setTextColor(WHITE);

  String display_text = ">" + input_buffer;
  M5.Display.drawString(display_text, 4, M5.Display.height() - 24);
}

/**
 * @brief 起動アニメーションを表示
 */
static void startup_animation() {
  const int W = M5.Display.width();
  const int H = M5.Display.height();
  const int STEP = 20;
  const uint16_t COLOR[] = {
      BLACK,
      M5.Display.color565(175, 66, 47),
      M5.Display.color565(139, 227, 77),
      M5.Display.color565(19, 17, 169),
  };
  while (!task_llm_ready) {
    // ボタン状態を更新
    M5.update();
    unifiedButton.update();

    // ボリューム調整処理を追加
    if (M5.BtnA.wasPressed()) {
      SOUND_VOLUME += 10;
      if (SOUND_VOLUME > SOUND_VOLUME_MAX) {
        SOUND_VOLUME = 0;
      }
      M5.Speaker.setVolume(SOUND_VOLUME);
    }

    if (M5.BtnC.wasPressed()) {
      if (SOUND_VOLUME >= 10) {
        SOUND_VOLUME -= 10;
      } else {
        SOUND_VOLUME = 0;
      }
      M5.Speaker.setVolume(SOUND_VOLUME);
    }

    portENTER_CRITICAL_ISR(&display_mutex);
    M5.Display.startWrite();
    for (int x = 0; x < W; x += STEP) {
      for (int y = 0; y < H; y += STEP) {
        int r = rand() % 4;

        uint16_t color = COLOR[r];
        canvas.fillRect(x, y, STEP, STEP, color);
      }
    }
    canvas.pushSprite(4, 4);
    M5.Display.endWrite();

    // ボリューム表示を追加
    M5.Display.fillRect(M5.Display.width() - 80, M5.Display.height() - 28, 80,
                        28, BLACK);
    M5.Display.setTextColor(YELLOW);
    M5.Display.drawString("Vol:" + String(SOUND_VOLUME),
                          M5.Display.width() - 75, M5.Display.height() - 24);
    portEXIT_CRITICAL_ISR(&display_mutex);

    // ランダムに S&H 風の音を鳴らす
    int freq = 400 + rand() % 800;
    sound_play(SOUND_TRIANGLE, (float)freq, 80);

    vTaskDelay(100);
  }
  clear();
}

//======================================================================
// 入力処理関数
//======================================================================
/**
 * @brief シリアル入力を処理
 */
void handle_serial_input() {
  if (CommSerialPort.available()) {
    while (CommSerialPort.available()) {
      char in_char = (char)CommSerialPort.read();

      // 入力文字の処理
      if (in_char == '\b') {  // バックスペース
        if (input_buffer.length() > 0) {
          input_buffer.remove(input_buffer.length() - 1);
        }
      } else if (in_char == '\r' || in_char == '\n') {
        // 改行コードの組み合わせチェック
        if (in_char == '\r' && CommSerialPort.peek() == '\n') {
          CommSerialPort.read();  // '\n'を消費
        }
        if (input_buffer.length() > 0) {
          question_ok = true;
        }
        break;
      } else {
        input_buffer += in_char;
      }
      vTaskDelay(20);
    }
  }
}

/**
 * @brief キーボード入力を処理
 */
void handle_keyboard_input() {
  if (digitalRead(FACESKEYBOARD_INTPIN) == LOW) {
    uint8_t key = kbd.GetKey();

    if (key != 0) {
      // キーボード入力の処理
      if (key == '\b') {  // バックスペース
        if (input_buffer.length() > 0) {
          M5.Speaker.tone(440, 100);
          input_buffer.remove(input_buffer.length() - 1);

          // シリアルポートにエコー
          CommSerialPort.write('\b');
          CommSerialPort.write(' ');
          CommSerialPort.write('\b');
        }
      } else if (key == '\r' || key == '\n') {  // Enter
        sound_play_SE(SOUND_SE_START);
        CommSerialPort.write('\r');
        CommSerialPort.write('\n');
        if (input_buffer.length() > 0) {
          question_ok = true;
        }
      } else {
        input_buffer += (char)key;
        input_buffer = convertRomajiToHiragana(input_buffer);
        M5.Speaker.tone(880, 100);
        // シリアルポートにエコー
        CommSerialPort.write(key);
      }
      show_input_mode();
      vTaskDelay(20);
    }
  }
}

//======================================================================
// タスク関数
//======================================================================
/**
 * @brief LLM制御タスク
 * @param pvParameters タスクパラメータ(未使用)
 */
void task_llm(void *pvParameters) {
  // モジュールの初期化
  module_llm.begin(&Serial2);

  // モジュールの接続確認
  system_message("ModuleLLM connecting", false);

  while (1) {
    if (module_llm.checkConnection()) {
      break;
    }
  }

  LLM_setup("jp");
  task_llm_ready = true;

  while (1) {
    module_llm.update();
    vTaskDelay(100);
  }
}

/**
 * @brief 回答表示タスク
 * @param pvParameters タスクパラメータ(未使用)
 */
void task_print(void *pvParameters) {
  while (1) {
    int len = answer.length();
    String buffer = answer;
    answer = "";

    int count = 0;
    for (int i = 0; i < len; i++) {
      // 1文字づつ表示
      String str = buffer.substring(i, i + 1);
      if (str == ".") {
        // スペースや疑問符の場合は効果音なし
      } else {
        count++;
        if (count % 2 == 1) {
          // 喋ってる風のSE
          sound_play(SOUND_SQUARE, 888, 33);  // 888Hz(A5)
          vTaskDelay(33);
        }
      }
      portENTER_CRITICAL_ISR(&display_mutex);
      canvas.setTextColor(GREEN);
      canvas.printf("%s", str.c_str());
      canvas.pushSprite(4, 4);

      portEXIT_CRITICAL_ISR(&display_mutex);
      vTaskDelay(50);  // 短い遅延を入れてwatchdogのリセット機会を与える
    }

    if (end_flag && (len == 0)) {
      sound_play_SE(SOUND_SE_END);
      end_flag = false;
    }
    vTaskDelay(50);
  }
}

//======================================================================
// Arduino メイン関数
//======================================================================
/**
 * @brief セットアップ
 */
void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  unifiedButton.begin(&M5.Display);

  // キーボード割り込みピンの設定
  pinMode(FACESKEYBOARD_INTPIN, INPUT_PULLUP);

  // USBシリアルの初期化
  CommSerialPort.begin(115200);
  CommSerialPort.print("SetUp Start\n");

  // LLMモジュール用シリアルの初期化
  int rxd = M5.getPin(m5::pin_name_t::port_c_rxd);
  int txd = M5.getPin(m5::pin_name_t::port_c_txd);
  Serial2.setRxBufferSize(SERIAL_RX_BUFFER_SIZE);
  Serial2.setTxBufferSize(SERIAL_TX_BUFFER_SIZE);

  Serial2.begin(115200, SERIAL_8N1, rxd, txd);

  // スピーカーの初期化
  M5.Speaker.setVolume(SOUND_VOLUME);

  // ディスプレイの初期化
  portENTER_CRITICAL_ISR(&display_mutex);
  M5.Display.startWrite();
  M5.Display.setRotation(1);
  M5.Display.setTextSize(1.0f);

  // ディスプレイの外枠を描画
  M5.Display.drawRect(0, 0, M5.Display.width(), M5.Display.height() - 28,
                      WHITE);
  M5.Display.drawRect(1, 1, M5.Display.width() - 1, M5.Display.height() - 29,
                      WHITE);
  M5.Display.setFont(&FONTNAME);

  // キャンバスの設定
  canvas.setFont(&FONTNAME);
  canvas.setTextSize(1.0);
  canvas.createSprite(M5.Display.width() - 8, M5.Display.height() - 36);
  canvas.setTextScroll(true);  // テキストスクロールを有効に
  canvas.pushSprite(4, 4);

  M5.Display.endWrite();
  portEXIT_CRITICAL_ISR(&display_mutex);

  CommSerialPort.print("task_llm start\n");

  // タスクの作成
  xTaskCreate(task_llm, "task_llm", 4096, NULL, 1, NULL);

  // 画面クリア
  clear();

  // 起動アニメーション
  startup_animation();

  // 表示色の設定
  canvas.setTextColor(GREEN);
  canvas.pushSprite(4, 4);

  // 入力モードの表示
  show_input_mode();
  xTaskCreate(task_print, "task_print", 4096, NULL, 1, NULL);

  CommSerialPort.print("SetUp End\n");

  // 初期の指示
  talk("あなたのなまえはなんですか？");
}

/**
 * @brief メインループ
 */
void loop() {
  M5.update();             // ボタン状態の更新
  unifiedButton.update();  // Must be call after M5.update.

  // シリアル入力の処理
  handle_serial_input();

  // キーボード入力の処理
  handle_keyboard_input();

  // 質問が準備できた場合の処理
  if (question_ok) {
    sound_play_SE(SOUND_SE_START);

    question = input_buffer;

    portENTER_CRITICAL_ISR(&display_mutex);
    canvas.setTextColor(WHITE);
    canvas.println("\n[You]:" + question);
    canvas.pushSprite(4, 4);

    canvas.setTextColor(GREEN);
    canvas.print("[AI]:");
    portEXIT_CRITICAL_ISR(&display_mutex);

    CommSerialPort.printf("<< \"%s\"\n", question.c_str());

    CommSerialPort.print(">> ");

    input_buffer = "";
    question_ok = false;
    talk(question);
  }

  // ボリューム増加処理 (A ボタン)
  if (M5.BtnA.wasPressed()) {
    SOUND_VOLUME += 10;
    if (SOUND_VOLUME > SOUND_VOLUME_MAX) {
      SOUND_VOLUME = SOUND_VOLUME_MAX;
    }
    M5.Speaker.setVolume(SOUND_VOLUME);

    // 画面の右下にボリューム値を表示
    portENTER_CRITICAL_ISR(&display_mutex);
    M5.Display.fillRect(M5.Display.width() - 80, M5.Display.height() - 28, 80,
                        28, BLACK);
    M5.Display.setTextColor(YELLOW);
    M5.Display.drawString("Vol:" + String(SOUND_VOLUME),
                          M5.Display.width() - 75, M5.Display.height() - 24);
    portEXIT_CRITICAL_ISR(&display_mutex);

    // 確認用のメッセージ表示（任意）
    CommSerialPort.printf("Volume: %d\n", SOUND_VOLUME);
    // ボリューム変更の確認音（任意）
    sound_play(SOUND_SQUARE, 440, 100);
  }

  // ボリューム減少処理 (C ボタン)
  if (M5.BtnC.wasPressed()) {
    if (SOUND_VOLUME >= 10) {
      SOUND_VOLUME -= 10;
    } else {
      SOUND_VOLUME = 0;
    }
    M5.Speaker.setVolume(SOUND_VOLUME);

    // 画面の右下にボリューム値を表示
    portENTER_CRITICAL_ISR(&display_mutex);
    M5.Display.fillRect(M5.Display.width() - 80, M5.Display.height() - 28, 80,
                        28, BLACK);
    M5.Display.setTextColor(YELLOW);
    M5.Display.drawString("Vol:" + String(SOUND_VOLUME),
                          M5.Display.width() - 75, M5.Display.height() - 24);
    portEXIT_CRITICAL_ISR(&display_mutex);

    // 確認用のメッセージ表示
    CommSerialPort.printf("Volume: %d\n", SOUND_VOLUME);
    // ボリューム変更の確認音
    sound_play(SOUND_SQUARE, 440, 100);
  }

  vTaskDelay(20);  // CPUの負荷軽減のための遅延
}

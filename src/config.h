/**
 *
 * This source code is taken from
 * Original code by GOROman
 * https://github.com/GOROman/LLMCardputer
 *
 * @file config.h
 * @brief M5Cardputer LLM Assistant の設定ファイル
 * @version 0.1
 * @date 2024-02-08
 *
 * @details
 * アプリケーションの動作に関する各種設定パラメータを定義します。
 * フォント、通信設定、音量、使用するLLMモデルなどの設定が含まれます。
 */

#pragma once
#include <stddef.h>  // for NULL

/**
 * @brief 表示に使用するフォント
 * @details 日本語表示に対応したLGFXJapanGothicフォントを使用
 */
#define FONTNAME fonts::lgfxJapanGothic_24

/**
 * @brief M5Module-LLM との通信用UARTピン設定
 * @note M5Cardputer の Serial2 を使用
 */

/**
 * @brief スピーカーの音量設定
 * @details 0-255の範囲で指定 (0: 無音, 255: 最大音量)
 */
int SOUND_VOLUME = 10;
int SOUND_VOLUME_MAX = 200;
/**
 * @brief 使用するLLMモデルの設定
 * @details
 * - NULL: デフォルトモデルを使用
 * - 以下のモデルが利用可能:
 *   - qwen2.5-0.5B-prefill-20e: 小規模な高速モデル
 *   - qwen2.5-1.5b-ax630c: 中規模な汎用モデル
 *   - deepseek-r1-1.5B-ax630c: DeepSeekベースの高性能モデル
 */
// const char *MODEL = NULL;  // NULL: Default model

const char *MODEL = "qwen2.5-0.5B-prefill-20e";
// const char *MODEL = "qwen2.5-1.5b-ax630c";
// const char *MODEL = "deepseek-r1-1.5B-ax630c";

// const char *MODEL = "TinySwallow-1.5B";
// const char *MODEL = "llm-jp-3-150m";
// const char *MODEL = "llm-jp-3-440m";
//  const char *MODEL = "llm-jp-3-980m";

# LLMFaces_for_M5StackLLM

![image](https://github.com/user-attachments/assets/15309c27-53c9-4f46-a31a-ceca4d5adf76)

手のひらサイズローカルLLMマシン"LLMFaces_for_M5StackLLM"は、<br>
@GOROman氏のLLMCardputer をベースにFaceKITキーボードと日本語入力に対応しました。<br>
はんだ付け不要で、ドッキングするだけで使えます。

https://x.com/anoken2017/status/1905433935699738652

# 用意するもの

 - M5Stack CoreS3
https://docs.m5stack.com/en/core/CoreS3
 - Faces Kit
https://docs.m5stack.com/en/core/face_kit
 - Module-LLM
https://docs.m5stack.com/en/module/Module-LLM

# 使用方法
![image](https://github.com/user-attachments/assets/cec0b112-5075-4787-ac0a-dbc00a271705)

 - M5Stack CoreS3、face_kit、Module-LLMをドッキングします。
 - 電源を入れると起動アニメーションが表示され、ピロピロ音が鳴ります。AボタンとCボタンで音量調整できます。
 - 起動したら、キーボードから質問を入力します。ローマ字は自動的にひらがなに変換されます。エンターキーで送信します。LLMが回答を生成し、テキストで応答します。

# 注意
 - Face_kitは現在、EOL(生産終了)になっています。
 - 所定の確率で、Module-LLMからの文字列が処理しきれず、表示から漏れるする不具合が残っています。

# 参考
https://github.com/GOROman/LLMCardputer<br>
LLMCardputer のつくりかた:<br>
https://www.docswell.com/s/GOROman/5YDG9E-LLMCardputer<br>
ローカルLLMを手のひらサイズで動かしてみよう！ M5 Cardputer + ModuleLLM<br>
https://qiita.com/GOROman/items/769bf17589d5661f7a70<br>

# ライセンス
MIT License



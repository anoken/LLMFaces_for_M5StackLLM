# LLMFaces_for_M5StackLLM

![image](https://github.com/user-attachments/assets/15309c27-53c9-4f46-a31a-ceca4d5adf76)

手のひらサイズローカルLLMマシン"LLMFaces_for_M5StackLLM"は、<br>
@GOROman氏のLLMCardputer をベースにFaceKITキーボードと日本語入力に対応しました。<br>

https://x.com/anoken2017/status/1905433935699738652

# 用意するもの

![image](https://github.com/user-attachments/assets/cec0b112-5075-4787-ac0a-dbc00a271705)

 - M5Stack CoreS3
https://docs.m5stack.com/en/core/CoreS3
 - face_kit(EOL)
https://docs.m5stack.com/en/core/face_kit
 - Module-LLM
https://docs.m5stack.com/en/module/Module-LLM

# 使用方法
 - M5Stack CoreS3、face_kit、Module-LLMを合体します。
 - 電源を入れると起動アニメーションが表示され、ピロピロ音が鳴ります。AボタンとCボタンで音量調整できます。
 - 起動したら、キーボードから質問を入力します。ローマ字は自動的にひらがなに変換されます。エンターキーで送信します。LLMが回答を生成し、テキストで応答します。
　

# 注意
M5Stackのface_kitは現在、EOLになっています。

# 参考
https://github.com/GOROman/LLMCardputer<br>
LLMCardputer のつくりかた:<br>
https://www.docswell.com/s/GOROman/5YDG9E-LLMCardputer<br>
ローカルLLMを手のひらサイズで動かしてみよう！ M5 Cardputer + ModuleLLM<br>
https://qiita.com/GOROman/items/769bf17589d5661f7a70<br>

# ライセンス
MIT License



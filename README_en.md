# LLMFaces_for_M5StackLLM

![image](https://github.com/user-attachments/assets/15309c27-53c9-4f46-a31a-ceca4d5adf76)

The palm-sized local LLM machine "LLMFaces_for_M5StackLLM" is based on @GOROman's LLMCardputer with added support for FaceKIT keyboard and Japanese input.
No soldering required! Just dock the components and it's ready to use. It's a compact palm-sized local LLM machine.
You can enjoy conversations with the local LLM accompanied by LLMCardputer's cool beeping sounds. <br>
https://x.com/anoken2017/status/1905433935699738652 <br>

## Required Components
- M5Stack CoreS3 <br>
https://docs.m5stack.com/en/core/CoreS3 <br>
- Faces Kit <br>
https://docs.m5stack.com/en/core/face_kit <br>
- Module-LLM <br>
https://docs.m5stack.com/en/module/Module-LLM <br>

## How to Use
![image](https://github.com/user-attachments/assets/cec0b112-5075-4787-ac0a-dbc00a271705)
- Dock the M5Stack CoreS3, face_kit, and Module-LLM together. <br>
- When powered on, a startup animation will display with beeping sounds. You can adjust the volume using buttons A and C.
- Once started, input your questions using the keyboard. Romaji is automatically converted to hiragana. Press the Enter key to send. The LLM will generate an answer and respond with text.

## Notes
- The Face_kit is currently EOL (End of Life) and no longer in production.
- There is a remaining issue where, at a certain probability, the response string from Module-LLM cannot be fully processed, causing some response text to be missing from the screen display.

## References
@GOROman LLMCardputer https://github.com/GOROman/LLMCardputer <br>
@GOROman@How to build LLMCardputer: <br>
https://www.docswell.com/s/GOROman/5YDG9E-LLMCardputer <br>
@GOROman/Run local LLM in palm-size! M5 Cardputer + ModuleLLM <br>
https://qiita.com/GOROman/items/769bf17589d5661f7a70 <br>
@shikarunochi/Input from M5Faces keyboard to M5Stack LLM Module <br>
https://gist.github.com/shikarunochi/a871ccf8ebf8f4c8601c8f6250640451 <br>
@devemin/LLM-Keyboard-M5Stack <br>
https://gist.github.com/devemin/b798d606e9be8680673b89177269175e <br>
@anoken/ModuleLLM_MAniaX <br>
https://github.com/anoken/modulellm_maniax <br>

## License
MIT License

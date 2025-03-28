#ifndef _CONVERT_HIRAGANA_TABLE_H_
#define _CONVERT_HIRAGANA_TABLE_H_

// ローマ字からひらがなへの変換マップ構造体
struct RomajiToHiragana {
  const char* romaji;
  const char* hiragana;
};

// 基本的なローマ字からひらがなへのマッピングテーブル
const RomajiToHiragana romaji_map[] = {
    {"a", "あ"},        {"i", "い"},        {"u", "う"},
    {"e", "え"},        {"o", "お"},        {"ka", "か"},
    {"ki", "き"},       {"ku", "く"},       {"ke", "け"},
    {"ko", "こ"},       {"ga", "が"},       {"gi", "ぎ"},
    {"gu", "ぐ"},       {"ge", "げ"},       {"go", "ご"},
    {"sa", "さ"},       {"si", "し"},       {"su", "す"},
    {"se", "せ"},       {"so", "そ"},       {"shi", "し"},
    {"za", "ざ"},       {"zi", "じ"},       {"zu", "ず"},
    {"ze", "ぜ"},       {"zo", "ぞ"},       {"ji", "じ"},
    {"ta", "た"},       {"chi", "ち"},      {"tsu", "つ"},
    {"te", "て"},       {"to", "と"},       {"ti", "ち"},
    {"tu", "つ"},       {"da", "だ"},       {"di", "ぢ"},
    {"du", "づ"},       {"de", "で"},       {"do", "ど"},
    {"na", "な"},       {"ni", "に"},       {"nu", "ぬ"},
    {"ne", "ね"},       {"no", "の"},       {"ha", "は"},
    {"hi", "ひ"},       {"fu", "ふ"},       {"he", "へ"},
    {"ho", "ほ"},       {"ba", "ば"},       {"bi", "び"},
    {"bu", "ぶ"},       {"be", "べ"},       {"bo", "ぼ"},
    {"pa", "ぱ"},       {"pi", "ぴ"},       {"pu", "ぷ"},
    {"pe", "ぺ"},       {"po", "ぽ"},       {"ma", "ま"},
    {"mi", "み"},       {"mu", "む"},       {"me", "め"},
    {"mo", "も"},       {"ya", "や"},       {"yu", "ゆ"},
    {"yo", "よ"},       {"ra", "ら"},       {"ri", "り"},
    {"ru", "る"},       {"re", "れ"},       {"ro", "ろ"},
    {"wa", "わ"},       {"wo", "を"},       {"nn", "ん"},
    {"xya", "ょ"},      {"xyu", "ゅ"},      {"xyo", "ょ"},
    {"xtu", "っ"},      {"kya", "きゃ"},    {"kyu", "きゅ"},
    {"kyo", "きょ"},    {"gya", "ぎゃ"},    {"gyu", "ぎゅ"},
    {"gyo", "ぎょ"},    {"sha", "しゃ"},    {"shu", "しゅ"},
    {"sho", "しょ"},    {"ja", "じゃ"},     {"ju", "じゅ"},
    {"jo", "じょ"},     {"cha", "ちゃ"},    {"chu", "ちゅ"},
    {"cho", "ちょ"},    {"dya", "ぢゃ"},    {"dyu", "ぢゅ"},
    {"dyo", "ぢょ"},    {"nya", "にゃ"},    {"nyu", "にゅ"},
    {"nyo", "にょ"},    {"hya", "ひゃ"},    {"hyu", "ひゅ"},
    {"hyo", "ひょ"},    {"bya", "びゃ"},    {"byu", "びゅ"},
    {"byo", "びょ"},    {"pya", "ぴゃ"},    {"pyu", "ぴゅ"},
    {"pyo", "ぴょ"},    {"mya", "みゃ"},    {"myu", "みゅ"},
    {"myo", "みょ"},    {"rya", "りゃ"},    {"ryu", "りゅ"},
    {"ryo", "りょ"},    {"kka", "っか"},    {"kki", "っき"},
    {"kku", "っく"},    {"kke", "っけ"},    {"kko", "っこ"},
    {"gga", "っが"},    {"ggi", "っぎ"},    {"ggu", "っぐ"},
    {"gge", "っげ"},    {"ggo", "っご"},    {"ssa", "っさ"},
    {"sshi", "っし"},   {"ssu", "っす"},    {"sse", "っせ"},
    {"sso", "っそ"},    {"zza", "っざ"},    {"zzi", "っじ"},
    {"zzu", "っず"},    {"zze", "っぜ"},    {"zzo", "っぞ"},
    {"tta", "った"},    {"cchi", "っち"},   {"ttsu", "っつ"},
    {"tte", "って"},    {"tto", "っと"},    {"dda", "っだ"},
    {"ddi", "っぢ"},    {"ddu", "っづ"},    {"dde", "っで"},
    {"ddo", "っど"},    {"nna", "っな"},    {"nni", "っに"},
    {"nnu", "っぬ"},    {"nne", "っね"},    {"nno", "っの"},
    {"hha", "っは"},    {"hhi", "っひ"},    {"ffu", "っふ"},
    {"hhe", "っへ"},    {"hho", "っほ"},    {"bba", "っば"},
    {"bbi", "っび"},    {"bbu", "っぶ"},    {"bbe", "っべ"},
    {"bbo", "っぼ"},    {"ppa", "っぱ"},    {"ppi", "っぴ"},
    {"ppu", "っぷ"},    {"ppe", "っぺ"},    {"ppo", "っぽ"},
    {"mma", "っま"},    {"mmi", "っみ"},    {"mmu", "っむ"},
    {"mme", "っめ"},    {"mmo", "っも"},    {"yya", "っや"},
    {"yyu", "っゆ"},    {"yyo", "っよ"},    {"rra", "っら"},
    {"rri", "っり"},    {"rru", "る"},      {"rre", "れ"},
    {"rro", "ろ"},      {"wwa", "っわ"},    {"wwo", "っを"},
    {"kkya", "っきゃ"}, {"kkyu", "っきゅ"}, {"kkyo", "っきょ"},
    {"ggya", "っぎゃ"}, {"ggyu", "っぎゅ"}, {"ggyo", "っぎょ"},
    {"ssha", "っしゃ"}, {"sshu", "っしゅ"}, {"ssho", "っしょ"},
    {"jja", "っじゃ"},  {"jju", "っじゅ"},  {"jjo", "っじょ"},
    {"ccha", "っちゃ"}, {"cchu", "っちゅ"}, {"ccho", "っちょ"},
    {"ddya", "っぢゃ"}, {"ddyu", "っぢゅ"}, {"ddyo", "っぢょ"},
    {"nnya", "っにゃ"}, {"nnyu", "っにゅ"}, {"nnyo", "っにょ"},
    {"hhya", "っひゃ"}, {"hhyu", "っひゅ"}, {"hhyo", "っひょ"},
    {"bbya", "っびゃ"}, {"bbyu", "っびゅ"}, {"bbyo", "っびょ"},
    {"ppya", "っぴゃ"}, {"ppyu", "っぴゅ"}, {"ppyo", "っぴょ"},
    {"mmya", "っみゃ"}, {"mmyu", "っみゅ"}, {"mmyo", "っみょ"},
    {"rrya", "っりゃ"}, {"rryu", "っりゅ"}, {"rryo", "っりょ"},
    {"-", "ー"},        {".", "。"},        {",", "、"},
};

#define TABLE_SIZE (sizeof(table) / sizeof(table[0]))

// ローマ字からひらがなへの変換関数
String convertRomajiToHiragana(const String& romaji) {
  String hiragana = "";
  String temp = romaji;
  temp.toLowerCase();  // 小文字に変換

  // 特殊なケース: 小さい「っ」の処理（子音の連続）
  for (int i = 0; i < temp.length() - 1; i++) {
    if (isalpha(temp[i]) && temp[i] == temp[i + 1] && temp[i] != 'n') {
      hiragana += "っ";
      temp.remove(i, 1);
    }
  }

  // ローマ字をひらがなに変換
  int i = 0;
  while (i < temp.length()) {
    bool found = false;

    // 長い一致から試す (最大3文字)
    for (int len = 3; len > 0 && !found; len--) {
      if (i + len <= temp.length()) {
        String substr = temp.substring(i, i + len);

        for (const auto& entry : romaji_map) {
          if (strcmp(substr.c_str(), entry.romaji) == 0) {
            hiragana += entry.hiragana;
            i += len;
            found = true;
            break;
          }
        }
      }
    }

    // 一致するものが見つからなかった場合、そのまま追加
    if (!found) {
      hiragana += temp[i];
      i++;
    }
  }

  return hiragana;
}

#endif _CONVERT_HIRAGANA_TABLE_H_
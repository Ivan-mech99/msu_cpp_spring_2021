#ifndef H_MY_PARSER
#define H_MY_PARSER
#include <string>

typedef void (*StartCallbackType)();
typedef std::string (*DigitTokenCallbackType)(uint64_t);
typedef std::string (*WordTokenCallbackType)(std::string);
typedef void (*EndCallbackType)(const std::string &);
class TokenParser {
  StartCallbackType StartCallback;
  DigitTokenCallbackType DigitTokenCallback;
  WordTokenCallbackType WordTokenCallback;
  EndCallbackType EndCallback;

 public:
  std::string result;
  TokenParser();
  bool IsSpaceTabEnd(char symbol);
  bool Uint_checker(std::string token);
  int IsTokenInteger(std::string token);
  void Basic_parser(const std::string &text_par);
  void SetStartCallback(StartCallbackType Startfunc) {
    StartCallback = Startfunc;
  }
  void SetEndCallback(EndCallbackType Endfunc) { EndCallback = Endfunc; }
  void SetDigitTokenCallback(DigitTokenCallbackType Digitfunc) {
    DigitTokenCallback = Digitfunc;
  }
  void SetWordTokenCallback(WordTokenCallbackType Wordfunc) {
    WordTokenCallback = Wordfunc;
  }
};

#endif

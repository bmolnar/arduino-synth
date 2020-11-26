#ifndef SYNTH__COMMAND_PARSER_H_
#define SYNTH__COMMAND_PARSER_H_

#include <Arduino.h>

namespace synth {

struct CommandParserRequest {
  uint8_t datalen;
  const char* data;
};

struct CommandParserResponse {
  typedef uint8_t Status;

  HardwareSerial& printer;

  void ReplyStatus(Status status) {
    if (status == 0) {
      printer.println("OK");
    } else {
      printer.print("E"); printer.println(status);
    }
  }
};


typedef void (*CommandParserCallback)(const CommandParserRequest& request, CommandParserResponse& response);

class CommandParser
{
public:
  static const uint8_t kBufSize = 16;
  CommandParser(HardwareSerial& serial, CommandParserCallback callback);
  void Step(uint32_t delta_t);

private:
  void PushChar(char c);

  HardwareSerial& serial_;
  CommandParserCallback callback_;
  uint8_t pos_ = 0;
  char cmdbuf_[kBufSize];
  bool error_ = false;
};

} // namespace synth

#endif // SYNTH__COMMAND_PARSER_H_

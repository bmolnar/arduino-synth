#include "command_parser.h"

namespace synth {

CommandParser::CommandParser(HardwareSerial& serial, CommandParserCallback callback)
  : serial_(serial), callback_(callback), pos_(0), error_(false)
{
}

void CommandParser::Step(uint32_t delta_t)
{
  if (serial_.available() > 0) {
    int rval = serial_.read();
    if (rval >= 0) {
      PushChar(static_cast<char>(rval));
    }
  }
}
void CommandParser::PushChar(char c)
{
  if (c == '\r') {
  } else if (c == '\n') {
    if (pos_ < kBufSize) {
      cmdbuf_[pos_] = '\0';

      CommandParserRequest request{pos_, cmdbuf_};
      CommandParserResponse response{serial_};
      (*callback_)(request, response);

      pos_ = 0;
      error_ = false;
    }
  } else if (pos_ < kBufSize) {
    cmdbuf_[pos_++] = c;
  } else {
    error_ = true;
  }
}

} // namespace synth

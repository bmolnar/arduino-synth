#ifndef SYNTH__COMMAND_PARSER_H_
#define SYNTH__COMMAND_PARSER_H_

#include "types.h"
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

  /**
   * Initializes command parser
   *
   * @param serial The HardwareSerial object acting as input
   * @param callback Function to be called on successful decoding of command
   */
  CommandParser(HardwareSerial& serial, CommandParserCallback callback);

  /**
   * Advances state machine
   *
   * @param delta_t Duration of time
   */
  void Step(uint32_t delta_t);

  /**
   * Advances graph object to given time
   *
   * @param timestamp Time to advance graph object to
   */
  void StepTo(timestamp_t timestamp);

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

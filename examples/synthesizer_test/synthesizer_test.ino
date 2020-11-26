#include "synth.h"

namespace note = synth::notes::voltage;

synth::Oscillator osc0(synth::WaveformSquare, synth::milliseconds(10000), synth::millivolts(1000), synth::millivolts(1000));
synth::Oscillator osc1(synth::WaveformSine, synth::milliseconds(5000), synth::millivolts(100), synth::millivolts(100));
synth::Oscillator osc2(synth::WaveformSine, synth::milliseconds(2000), synth::millivolts(10), synth::millivolts(10));
synth::Oscillator osc3(synth::WaveformSine, synth::milliseconds(1000), synth::millivolts(1000), synth::millivolts(0));

synth::voltage_t slots0[] = {note::Note_E2, note::Note_G2, note::Note_A2, note::Note_G2, note::Note_D3, note::Note_C3, note::Note_D3, note::Note_E3};
synth::Sequencer seq0(synth::milliseconds(125), synth::kDutyHalf, slots0, 8);
synth::voltage_t slots1[] = {synth::millivolts(0), synth::millivolts(500), synth::millivolts(1000), synth::millivolts(2000)};
synth::Sequencer seq1(synth::milliseconds(1000), synth::kDutyHalf, slots1, 4);

synth::Mixer mixer0(osc0.Output(), osc1.Output(), osc2.Output(), osc3.Output(), seq0.Output(), seq1.Output());

synth::OscillatorPtr osc_list[] = {&osc0, &osc1, &osc2, &osc3};
synth::SequencerPtr seq_list[] = {&seq0, &seq1};
synth::MixerPtr mixer_list[] = {&mixer0};

synth::SignalSourcePtr source_list[] = {
 osc0.Output(), osc1.Output(), osc2.Output(), osc3.Output(),
 seq0.Output(), seq1.Output(),
 mixer0.Output()
};

synth::DacMcp4725 dac;
synth::Timer timer;

static synth::voltage_t g_value = synth::millivolts(0);
static bool g_trace = false;
static Print& g_logger = Serial;
static synth::SignalSourcePtr g_source = mixer0.Output();
static uint32_t g_loopcnt = 0;


static const synth::CommandParserResponse::Status kResultOk = 0;
static const synth::CommandParserResponse::Status kErrorInvalidCommand = 1;
static const synth::CommandParserResponse::Status kErrorInvalidFunction = 2;
static const synth::CommandParserResponse::Status kErrorTraceInvalidArg = 3;
static const synth::CommandParserResponse::Status kErrorSelectionInvalidArg = 4;

static synth::NormalizedWaveform GetWaveformByIndex(uint8_t index)
{
  switch (index) {
    case 0: return synth::WaveformZero;
    case 1: return synth::WaveformSine;
    case 2: return synth::WaveformTriangle;
    case 3: return synth::WaveformSawtooth;
    case 4: return synth::WaveformSquare;
    default: return synth::WaveformZero;
  }
}

static synth::CommandParserResponse::Status OnCommand(const char* cmd)
{
  switch (cmd[0]) {
    case 'A':
      {
        uint8_t index = 0;
        char* argp = &cmd[1];
        char* commap = synth::find_char(argp, ',');
        if (commap != nullptr) {
          String indexstr(&cmd[1]);
          index = static_cast<uint8_t>(indexstr.toInt());
          argp = commap + 1;
        }
        String valstr(argp);
        osc_list[index]->SetAmplitude(synth::millivolts(valstr.toInt()));
        return kResultOk;
      }
    case 'G':
      {
        uint8_t index = 0;
        uint8_t channel = 0;
        char* argp = &cmd[1];
        char* commap = synth::find_char(argp, ',');
        if (commap != nullptr) {
          String indexstr(argp);
          index = static_cast<uint8_t>(indexstr.toInt());
          argp = commap + 1;
        }
        char* colonp = synth::find_char(argp, ':');
        if (colonp != nullptr) {
          String channelstr(argp);
          channel = static_cast<uint8_t>(channelstr.toInt());
          argp = colonp + 1;
        }
        String valstr(argp);
        mixer_list[index]->SetChannelGain(channel, static_cast<synth::gain_t>(valstr.toInt()));
        return kResultOk;
      }
    case 'I':
      {
        g_logger.print("graph.objcnt="); g_logger.println(synth::Graph::Instance().ObjectCount());
      }
      break;
    case 'O':
      {
        uint8_t index = 0;
        char* argp = &cmd[1];
        char* commap = synth::find_char(argp, ',');
        if (commap != nullptr) {
          String indexstr(argp);
          index = static_cast<uint8_t>(indexstr.toInt());
          argp = commap + 1;
        }
        String valstr(argp);
        osc_list[index]->SetOffset(synth::millivolts(valstr.toInt()));
        return kResultOk;
      }
    case 'P':
      {
        uint8_t index = 0;
        char* argp = &cmd[1];
        char* commap = synth::find_char(argp, ',');
        if (commap != nullptr) {
          String indexstr(argp);
          index = static_cast<uint8_t>(indexstr.toInt());
          argp = commap + 1;
        }
        String valstr(argp);
        osc_list[index]->SetPeriod(synth::milliseconds(valstr.toInt()));
        return kResultOk;
      }
    case 'S':
      {
        if (cmd[1] == '\0') {
          g_source = synth::SignalSourcePtrNull;
          return kResultOk;
        }
        String valstr(cmd[1]);
        int val = valstr.toInt();
        if (val >= 0 && val < (sizeof(source_list)/sizeof(synth::SignalSourcePtr))) {
          g_source = source_list[val];
          return kResultOk;
        } else {
          return kErrorSelectionInvalidArg;
        }
      }
    case 'T': 
      switch (cmd[1]) {
        case '0': g_trace = false; return kResultOk;
        case '1': g_trace = true; return kResultOk;
        case '\0': g_trace = !g_trace; return kResultOk;
        default: return kErrorTraceInvalidArg;
      }
    case 'V':
      {
        String argstr(cmd[1]);
        g_value = synth::millivolts(argstr.toInt());
        return kResultOk;
      }
    case 'W':
      {
        uint8_t index = 0;
        char* argp = &cmd[1];
        char* commap = synth::find_char(argp, ',');
        if (commap != nullptr) {
          String indexstr(argp);
          index = static_cast<uint8_t>(indexstr.toInt());
          argp = commap + 1;
        }
        osc_list[index]->SetWaveform(GetWaveformByIndex(static_cast<uint8_t>(argp[0] - '0')));
        return kResultOk;
      }
    default:
      return kErrorInvalidCommand;
  }
}
static void CommandCallback(const synth::CommandParserRequest& request, synth::CommandParserResponse& response)
{
  synth::CommandParserResponse::Status status = OnCommand(request.data);
  response.ReplyStatus(status);
}

synth::CommandParser cmd(Serial, &CommandCallback);

void setup() {
  Serial.begin(9600);
  //dac.begin(0x60);
  dac.Begin();
  timer.Start();
}

void loop() {
  synth::duration_t delta_t = timer.ElapsedSinceLast();

  cmd.Step(delta_t);

  synth::Graph::Instance().Step(delta_t);

  synth::voltage_t value = (g_source != synth::SignalSourcePtrNull) ? g_source->Value() : g_value;
  
  if (g_trace) {
    Serial.print("T value="); Serial.println(value);
  }
  dac.SetVoltage(value);

  g_loopcnt++;
}

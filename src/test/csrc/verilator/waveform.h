/***************************************************************************************
* Copyright (c) 2020-2025 Institute of Computing Technology, Chinese Academy of Sciences
*
* DiffTest is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __WAVEFORM_H
#define __WAVEFORM_H

#include "verilated.h"
#ifdef ENABLE_FST
#include <verilated_fst_c.h>
#else
#include <verilated_vcd_c.h>
#endif // ENABLE_FST

using TraceBindFunc = std::function<void(VerilatedTraceBaseC *, int)>;

class EmuWaveform {
private:
#ifdef ENABLE_FST
  VerilatedFstC *tfp;
#else
  VerilatedVcdC *tfp;
#endif

  // waveform clock: this may differ from the CPU clock
  uint64_t waveform_clock;

  const char *default_filename(uint64_t cycles);

public:
  EmuWaveform(TraceBindFunc trace, uint64_t cycles);
  EmuWaveform(TraceBindFunc trace, uint64_t cycles, const char *filename);

  ~EmuWaveform() {
    if (tfp) {
      tfp->close();
      delete tfp;
    }
  }

  void tick();
};

#endif

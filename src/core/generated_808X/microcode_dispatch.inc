// Generated from Intel microcode. Do not edit.
switch (pending_) {
// 000: 0100010??.00
// Opcodes: 88-8B
// ------------------------------------------------------------
// R     -> tmpb      4   none  WB,NX     
// ------------------------------------------------------------
case 56:
{
    tmpb() = mc_read_r();
    if (!m_is_m_ || !use_memory_ || alu_ == AluOp::CMP) {
        nx_ = true;
    }
    break;
}

// 001:
// ------------------------------------------------------------
// tmpb  -> M         4   none  RNI       
// ------------------------------------------------------------
case 57:
{
    mc_write_m(tmpb());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 002:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 58:
{
    startWriteRniDDP0();
    break;
}

// 003:
// ------------------------------------------------------------
// IJ    -> tmpa      5   UNC   EAOFFSET  
// ------------------------------------------------------------
case 59:
{
    tmpa() = rw(6);
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? ((mod_rm_ & 0xc0) == 0 ? 0x140d : 0x140a) : ((mod_rm_ & 0xc0) == 0 ? 0x140f : 0x140a)); // EAOFFSET
    state_ = stateSingleCycleWait;
    break;
}

// 004: 010001101.00
// Opcodes: 8D
// ------------------------------------------------------------
// IND   -> R         4   none  RNI       
// ------------------------------------------------------------
case 60:
{
    mc_write_r(ind());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 008: 000???0??.00
// Opcodes: 00-03, 08-0B, 10-13, 18-1B, 20-23, 28-2B, 30-33, 38-3B
// ------------------------------------------------------------
// M     -> tmpa      1   XI    tmpa      
// ------------------------------------------------------------
case 61:
{
    tmpa() = mc_read_m();
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 009:
// ------------------------------------------------------------
// R     -> tmpb      4   none  WB,NX     
// ------------------------------------------------------------
case 62:
{
    tmpb() = mc_read_r();
    if (!m_is_m_ || !use_memory_ || alu_ == AluOp::CMP) {
        nx_ = true;
    }
    break;
}

// 00a:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 63:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 00b:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 64:
{
    startWriteRniDDP0();
    break;
}

// 00c: 0100000??.00
// Opcodes: 80-83
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 65:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 00d:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 66:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 00e:
// ------------------------------------------------------------
// M     -> tmpa      1   XI    tmpa, NX  
// ------------------------------------------------------------
case 67:
{
    tmpa() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpA;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 00f:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 68:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 010: 0?00000??.01
// Opcodes: none
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 69:
{
    startWriteRniDDP0();
    break;
}

// 014: 01100011?.00
// Opcodes: C6-C7
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 70:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 015:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 71:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 016:
// ------------------------------------------------------------
// tmpb  -> M         4   none  RNI       
// ------------------------------------------------------------
case 72:
{
    mc_write_m(tmpb());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 017:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 73:
{
    startWriteRniDDP0();
    break;
}

// 018: 000???10?.00
// Opcodes: 04-05, 0C-0D, 14-15, 1C-1D, 24-25, 2C-2D, 34-35, 3C-3D
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 74:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 019:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 75:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 01a:
// ------------------------------------------------------------
// M     -> tmpa      1   XI    tmpa, NX  
// ------------------------------------------------------------
case 76:
{
    tmpa() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpA;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 01b:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 77:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 01c: 01011????.00
// Opcodes: B0-BF
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 78:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 01d:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 79:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 01e:
// ------------------------------------------------------------
// tmpb  -> M         4   none  RNI       
// ------------------------------------------------------------
case 80:
{
    mc_write_m(tmpb());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 01f:
// ------------------------------------------------------------
// IK    -> tmpa      5   UNC   EAOFFSET  
// ------------------------------------------------------------
case 81:
{
    tmpa() = rw(7);
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? ((mod_rm_ & 0xc0) == 0 ? 0x140d : 0x140a) : ((mod_rm_ & 0xc0) == 0 ? 0x140f : 0x140a)); // EAOFFSET
    state_ = stateSingleCycleWait;
    break;
}

// 020: ?1111100?.00
// Opcodes: FE-FF /0, FE-FF /1
// ------------------------------------------------------------
// M     -> tmpb      1   XI    tmpb, NX  
// ------------------------------------------------------------
case 82:
{
    tmpb() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpB;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 021:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 83:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 022:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 84:
{
    startWriteRniDDP0();
    break;
}

// 023:
// ------------------------------------------------------------
// MP    -> tmpa      5   UNC   EAOFFSET  
// ------------------------------------------------------------
case 85:
{
    tmpa() = rw(5);
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? ((mod_rm_ & 0xc0) == 0 ? 0x140d : 0x140a) : ((mod_rm_ & 0xc0) == 0 ? 0x140f : 0x140a)); // EAOFFSET
    state_ = stateSingleCycleWait;
    break;
}

// 024: ?1111111?.00
// Opcodes: FE-FF /6, FE-FF /7
// ------------------------------------------------------------
// SP    -> tmpa      1   DEC2  tmpa      
// ------------------------------------------------------------
case 0:
{
    tmpa() = rw(4);
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 025:
// ------------------------------------------------------------
// SIGMA -> IND                           
// ------------------------------------------------------------
case 86:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    ind() = sigma;
    break;
}

// 026:
// ------------------------------------------------------------
// SIGMA -> SP                            
// ------------------------------------------------------------
case 87:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    rw(4) = sigma;
    break;
}

// 027:
// ------------------------------------------------------------
// M     -> OPR       6   W,RNI DS,P0     
// ------------------------------------------------------------
case 88:
{
    opr() = mc_read_m();
    mc_bus(true, false, true, 2, 3);
    break;
}

// 028: 001010???.00
// Opcodes: 50-57
// ------------------------------------------------------------
// SP    -> tmpa      1   DEC2  tmpa      
// ------------------------------------------------------------
case 1:
{
    tmpa() = rw(4);
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 029:
// ------------------------------------------------------------
// SIGMA -> IND                           
// ------------------------------------------------------------
case 89:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    ind() = sigma;
    break;
}

// 02a:
// ------------------------------------------------------------
// SIGMA -> SP                            
// ------------------------------------------------------------
case 90:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    rw(4) = sigma;
    break;
}

// 02b:
// ------------------------------------------------------------
// M     -> OPR       6   W,RNI DS,P0     
// ------------------------------------------------------------
case 91:
{
    opr() = mc_read_m();
    mc_bus(true, false, true, 2, 3);
    break;
}

// 02c: 0000??110.00
// Opcodes: 06, 0E, 16, 1E
// ------------------------------------------------------------
// SP    -> tmpa      1   DEC2  tmpa      
// ------------------------------------------------------------
case 2:
{
    tmpa() = rw(4);
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 02d:
// ------------------------------------------------------------
// SIGMA -> IND                           
// ------------------------------------------------------------
case 92:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    ind() = sigma;
    break;
}

// 02e:
// ------------------------------------------------------------
// SIGMA -> SP                            
// ------------------------------------------------------------
case 93:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    rw(4) = sigma;
    break;
}

// 02f:
// ------------------------------------------------------------
// R     -> OPR       6   W,RNI DS,P0     
// ------------------------------------------------------------
case 94:
{
    opr() = mc_read_r();
    mc_bus(true, false, true, 2, 3);
    break;
}

// 030: 010011100.00
// Opcodes: 9C
// ------------------------------------------------------------
// SP    -> tmpa      1   DEC2  tmpa      
// ------------------------------------------------------------
case 3:
{
    tmpa() = rw(4);
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 031:
// ------------------------------------------------------------
// SIGMA -> IND                           
// ------------------------------------------------------------
case 95:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    ind() = sigma;
    break;
}

// 032:
// ------------------------------------------------------------
// SIGMA -> SP                            
// ------------------------------------------------------------
case 96:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpA>();
    rw(4) = sigma;
    break;
}

// 033:
// ------------------------------------------------------------
// F     -> OPR       6   W,RNI DS,P0     
// ------------------------------------------------------------
case 97:
{
    opr() = flags();
    mc_bus(true, false, true, 2, 3);
    break;
}

// 034: 001011???.00
// Opcodes: 58-5F
// ------------------------------------------------------------
// SP    -> IND       6   R     DS,P2     
// ------------------------------------------------------------
case 98:
{
    ind() = rw(4);
    mc_bus(false, false, false, 2, 0);
    break;
}

// 035:
// ------------------------------------------------------------
// IND   -> SP        4   none  NX        
// ------------------------------------------------------------
case 99:
{
    rw(4) = ind();
    nx_ = true;
    break;
}

// 036:
// ------------------------------------------------------------
// OPR   -> M         4   none  RNI       
// ------------------------------------------------------------
case 100:
{
    mc_write_m(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 037:
// ------------------------------------------------------------
// HL    -> tmpa      5   UNC   EAOFFSET  
// ------------------------------------------------------------
case 101:
{
    tmpa() = rw(3);
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? ((mod_rm_ & 0xc0) == 0 ? 0x140d : 0x140a) : ((mod_rm_ & 0xc0) == 0 ? 0x140f : 0x140a)); // EAOFFSET
    state_ = stateSingleCycleWait;
    break;
}

// 038: 0000??111.00
// Opcodes: 07, 0F, 17, 1F
// ------------------------------------------------------------
// SP    -> IND       6   R     DS,P2     
// ------------------------------------------------------------
case 102:
{
    ind() = rw(4);
    mc_bus(false, false, false, 2, 0);
    break;
}

// 039:
// ------------------------------------------------------------
// IND   -> SP        4   none  NX        
// ------------------------------------------------------------
case 103:
{
    rw(4) = ind();
    nx_ = true;
    break;
}

// 03a:
// ------------------------------------------------------------
// OPR   -> R         4   none  RNI       
// ------------------------------------------------------------
case 104:
{
    mc_write_r(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 03c: 010011101.00
// Opcodes: 9D
// ------------------------------------------------------------
// SP    -> IND       6   R     DS,P2     
// ------------------------------------------------------------
case 105:
{
    ind() = rw(4);
    mc_bus(false, false, false, 2, 0);
    break;
}

// 03d:
// ------------------------------------------------------------
// IND   -> SP        4   none  NX        
// ------------------------------------------------------------
case 106:
{
    rw(4) = ind();
    nx_ = true;
    break;
}

// 03e:
// ------------------------------------------------------------
// OPR   -> F         4   none  RNI       
// ------------------------------------------------------------
case 107:
{
    flags() = (opr() & 0xffd5) | 0xf002;
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 040: 010001111.00
// Opcodes: 8F
// ------------------------------------------------------------
// IND   -> tmpa                          
// ------------------------------------------------------------
case 108:
{
    tmpa() = ind();
    break;
}

// 041:
// ------------------------------------------------------------
// SP    -> IND       6   R     DS,P2     
// ------------------------------------------------------------
case 109:
{
    ind() = rw(4);
    mc_bus(false, false, false, 2, 0);
    break;
}

// 042:
// ------------------------------------------------------------
// IND   -> SP                            
// ------------------------------------------------------------
case 110:
{
    rw(4) = ind();
    break;
}

// 043:
// ------------------------------------------------------------
// tmpa  -> IND       4   none  WB,NX     
// ------------------------------------------------------------
case 111:
{
    ind() = tmpa();
    if (!m_is_m_ || !use_memory_ || alu_ == AluOp::CMP) {
        nx_ = true;
    }
    break;
}

// 044: 010001111.01
// Opcodes: none
// ------------------------------------------------------------
// OPR   -> M         4   none  RNI       
// ------------------------------------------------------------
case 112:
{
    mc_write_m(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 045:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 113:
{
    startWriteRniDDP0();
    break;
}

// 04c: ?11110010.00
// Opcodes: F6-F7 /2
// ------------------------------------------------------------
// M     -> tmpb      1   XI    tmpb, NX  
// ------------------------------------------------------------
case 114:
{
    tmpb() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpB;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 04d:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI       
// ------------------------------------------------------------
case 115:
{
    const uint32_t sigma = doALU();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 04e:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 116:
{
    startWriteRniDDP0();
    break;
}

// 050: ?11110011.00
// Opcodes: F6-F7 /3
// ------------------------------------------------------------
// M     -> tmpb      1   XI    tmpb, NX  
// ------------------------------------------------------------
case 117:
{
    tmpb() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpB;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 051:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 118:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 052:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 119:
{
    startWriteRniDDP0();
    break;
}

// 054: 010011000.00
// Opcodes: 98
// ------------------------------------------------------------
// XA    -> tmpbL     4   none  NX        
// ------------------------------------------------------------
case 120:
{
    const uint32_t value = rw(0);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    nx_ = true;
    break;
}

// 055:
// ------------------------------------------------------------
// tmpb  -> XA        4   none  RNI       
// ------------------------------------------------------------
case 121:
{
    rw(0) = tmpb();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 058: 010011001.00
// Opcodes: 99
// ------------------------------------------------------------
// XA    -> tmpb      1   LRCY  tmpb      
// ------------------------------------------------------------
case 4:
{
    tmpb() = rw(0);
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 059:
// ------------------------------------------------------------
// SIGMA -> tmpb      1   RRCY  tmpb      
// ------------------------------------------------------------
case 122:
{
    const uint32_t sigma = doALUFixed<AluOp::LRCY, AluInput::TmpB>();
    tmpb() = sigma;
    alu_ = AluOp::RRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 05a:
// ------------------------------------------------------------
//                    0   CY       5      
// ------------------------------------------------------------
case 123:
{
    if (getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 05b:
// ------------------------------------------------------------
// ZERO  -> DE        4   none  NX        
// ------------------------------------------------------------
case 124:
{
    rw(2) = 0;
    nx_ = true;
    break;
}

// 05c: 010011001.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> tmpb      4   none  RNI       
// ------------------------------------------------------------
case 125:
{
    const uint32_t sigma = doALUFixed<AluOp::RRCY, AluInput::TmpB>();
    tmpb() = sigma;
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 05d:
// ------------------------------------------------------------
// ONES  -> DE        4   none  NX        
// ------------------------------------------------------------
case 126:
{
    rw(2) = 0xffff;
    nx_ = true;
    break;
}

// 05e:
// ------------------------------------------------------------
// SIGMA -> tmpb      4   none  RNI       
// ------------------------------------------------------------
case 127:
{
    const uint32_t sigma = doALU();
    tmpb() = sigma;
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 060: 01010000?.00
// Opcodes: A0-A1
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 128:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 061:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 129:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 062:
// ------------------------------------------------------------
// tmpb  -> IND       6   R     DD,P0     
// ------------------------------------------------------------
case 130:
{
    ind() = tmpb();
    mc_bus(false, false, false, 3, 3);
    break;
}

// 063:
// ------------------------------------------------------------
// OPR   -> M         4   none  RNI       
// ------------------------------------------------------------
case 131:
{
    mc_write_m(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 064: 01010001?.00
// Opcodes: A2-A3
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 132:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 065:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 133:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 066:
// ------------------------------------------------------------
// tmpb  -> IND                           
// ------------------------------------------------------------
case 134:
{
    ind() = tmpb();
    break;
}

// 067:
// ------------------------------------------------------------
// M     -> OPR       6   W,RNI DD,P0     
// ------------------------------------------------------------
case 135:
{
    opr() = mc_read_m();
    startWriteRniDDP0();
    break;
}

// 068: ?11111011.00
// Opcodes: FE-FF /3
// ------------------------------------------------------------
// IND   -> tmpc      1   INC2  tmpc      
// ------------------------------------------------------------
case 136:
{
    registers_[14] = ind();
    alu_ = AluOp::INC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 069:
// ------------------------------------------------------------
// SIGMA -> IND       6   R     DD,P0     
// ------------------------------------------------------------
case 137:
{
    const uint32_t sigma = doALUFixed<AluOp::INC2, AluInput::TmpC>();
    ind() = sigma;
    mc_bus(false, false, false, 3, 3);
    break;
}

// 06a:
// ------------------------------------------------------------
// OPR   -> tmpa      1   DEC2  tmpc      
// ------------------------------------------------------------
case 138:
{
    tmpa() = opr();
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 06b:
// ------------------------------------------------------------
// SP    -> tmpc      4   none  SUSP      
// ------------------------------------------------------------
case 139:
{
    registers_[14] = rw(4);
    suspendPrefetch();
    break;
}

// 06c: ?11111011.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> IND       4   none  CORR      
// ------------------------------------------------------------
case 140:
{
    const uint32_t sigma = doALU();
    ind() = sigma;
    correctPC();
    break;
}

// 06d:
// ------------------------------------------------------------
// RC    -> OPR       6   w     DS,M2     
// ------------------------------------------------------------
case 141:
{
    opr() = sr(1);
    mc_bus(true, false, false, 2, 2);
    break;
}

// 06e:
// ------------------------------------------------------------
// tmpa  -> RC        1   PASS  tmpc      
// ------------------------------------------------------------
case 5:
{
    sr(1) = tmpa();
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 06f:
// ------------------------------------------------------------
// PC    -> OPR       5   UNC   NEARCALL  
// ------------------------------------------------------------
case 142:
{
    opr() = pc();
    skip_rni_ = false;
    microcode_pointer_ = 0x1fa3; // NEARCALL
    state_ = stateSingleCycleWait;
    break;
}

// 070: 010011010.00
// Opcodes: 9A
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 143:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 071:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 144:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 072:
// ------------------------------------------------------------
// Q     -> tmpaL     1   DEC2  tmpc      
// ------------------------------------------------------------
case 145:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff00) | (queueRead(QueueReadState::SubsequentByte) & 0xff);
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 073:
// ------------------------------------------------------------
// Q     -> tmpaH     5   UNC   FARCALL   
// ------------------------------------------------------------
case 146:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    skip_rni_ = false;
    microcode_pointer_ = 0x1fb3; // FARCALL
    state_ = stateSingleCycleWait;
    break;
}

// 074: ?11111010.00
// Opcodes: FE-FF /2
// ------------------------------------------------------------
// M     -> tmpb      4   none  SUSP      
// ------------------------------------------------------------
case 147:
{
    tmpb() = mc_read_m();
    suspendPrefetch();
    break;
}

// 075:
// ------------------------------------------------------------
// SP    -> IND       4   none  CORR      
// ------------------------------------------------------------
case 148:
{
    ind() = rw(4);
    correctPC();
    break;
}

// 076:
// ------------------------------------------------------------
// PC    -> OPR       1   DEC2  tmpc      
// ------------------------------------------------------------
case 149:
{
    opr() = pc();
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 077:
// ------------------------------------------------------------
// tmpb  -> PC        4   FLUSH none      
// ------------------------------------------------------------
case 150:
{
    pc() = tmpb();
    flushQueue();
    break;
}

// 078: ?11111010.01
// Opcodes: none
// ------------------------------------------------------------
// IND   -> tmpc                          
// ------------------------------------------------------------
case 6:
{
    registers_[14] = ind();
    break;
}

// 079:
// ------------------------------------------------------------
// SIGMA -> IND                           
// ------------------------------------------------------------
case 151:
{
    const uint32_t sigma = doALU();
    ind() = sigma;
    break;
}

// 07a:
// ------------------------------------------------------------
// SIGMA -> SP        6   W,RNI DS,P0     
// ------------------------------------------------------------
case 152:
{
    const uint32_t sigma = doALU();
    rw(4) = sigma;
    mc_bus(true, false, true, 2, 3);
    break;
}

// 07c: 011101000.00
// Opcodes: E8
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 153:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 07d:
// ------------------------------------------------------------
// Q     -> tmpbH     1   DEC2  tmpc      
// ------------------------------------------------------------
case 154:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 07e:
// ------------------------------------------------------------
// SP    -> tmpc      4   none  SUSP      
// ------------------------------------------------------------
case 155:
{
    registers_[14] = rw(4);
    suspendPrefetch();
    break;
}

// 07f:
// ------------------------------------------------------------
// SIGMA -> IND       4   none  CORR      
// ------------------------------------------------------------
case 156:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpC>();
    ind() = sigma;
    correctPC();
    break;
}

// 080: 011101000.01
// Opcodes: none
// ------------------------------------------------------------
// PC    -> tmpa      1   ADD   tmpa      
// ------------------------------------------------------------
case 157:
{
    tmpa() = pc();
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 081:
// ------------------------------------------------------------
// SIGMA -> PC        4   FLUSH none      
// ------------------------------------------------------------
case 158:
{
    const uint32_t sigma = doALUFixed<AluOp::ADD, AluInput::TmpA>();
    pc() = sigma;
    flushQueue();
    break;
}

// 082:
// ------------------------------------------------------------
// IND   -> SP        0   UNC      7      
// ------------------------------------------------------------
case 159:
{
    rw(4) = ind();
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
    state_ = stateSingleCycleWait;
    break;
}

// 083:
// ------------------------------------------------------------
// tmpa  -> OPR       6   W,RNI DS,P0     
// ------------------------------------------------------------
case 160:
{
    opr() = tmpa();
    mc_bus(true, false, true, 2, 3);
    break;
}

// 084: 010010???.00
// Opcodes: 90-97
// ------------------------------------------------------------
// M     -> tmpb                          
// ------------------------------------------------------------
case 161:
{
    tmpb() = mc_read_m();
    break;
}

// 085:
// ------------------------------------------------------------
// XA    -> M         4   none  NX        
// ------------------------------------------------------------
case 162:
{
    mc_write_m(rw(0));
    nx_ = true;
    break;
}

// 086:
// ------------------------------------------------------------
// tmpb  -> XA        4   none  RNI       
// ------------------------------------------------------------
case 163:
{
    rw(0) = tmpb();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 088: 01101000?.00
// Opcodes: D0-D1
// ------------------------------------------------------------
// M     -> tmpb      1   XI    tmpb, NX  
// ------------------------------------------------------------
case 164:
{
    tmpb() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpB;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 089:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 165:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 08a:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 166:
{
    startWriteRniDDP0();
    break;
}

// 08c: 01101001?.00
// Opcodes: D2-D3
// ------------------------------------------------------------
// ZERO  -> tmpa                          
// ------------------------------------------------------------
case 7:
{
    tmpa() = 0;
    break;
}

// 08d:
// ------------------------------------------------------------
// BC    -> tmpaL     1   PASS  tmpa      
// ------------------------------------------------------------
case 167:
{
    tmpa() = (tmpa() & 0xff00) | (rw(1) & 0xff);
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 08e:
// ------------------------------------------------------------
// M     -> tmpb      0   UNC      4      
// ------------------------------------------------------------
case 168:
{
    tmpb() = mc_read_m();
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x4;
    state_ = stateSingleCycleWait;
    break;
}

// 08f:
// ------------------------------------------------------------
// SIGMA -> tmpb      1   DEC   tmpa     F
// ------------------------------------------------------------
case 169:
{
    const uint32_t sigma = doALU();
    updateFlags();
    tmpb() = sigma;
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 090: 01101001?.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> tmpa      1   XI    tmpb      
// ------------------------------------------------------------
case 8:
{
    const uint32_t sigma = doALU();
    tmpa() = sigma;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 091:
// ------------------------------------------------------------
//                    0   NZ       3      
// ------------------------------------------------------------
case 170:
{
    if (!super_zero_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x3;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 092:
// ------------------------------------------------------------
// tmpb  -> M         4   none  RNI       
// ------------------------------------------------------------
case 171:
{
    mc_write_m(tmpb());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 093:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 172:
{
    startWriteRniDDP0();
    break;
}

// 094: 01000010?.00
// Opcodes: 84-85
// ------------------------------------------------------------
// M     -> tmpa      1   AND   tmpa      
// ------------------------------------------------------------
case 173:
{
    tmpa() = mc_read_m();
    alu_ = AluOp::AND;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 095:
// ------------------------------------------------------------
// R     -> tmpb      4   none  NX        
// ------------------------------------------------------------
case 174:
{
    tmpb() = mc_read_r();
    nx_ = true;
    break;
}

// 096:
// ------------------------------------------------------------
// SIGMA -> no dest   4   none  RNI      F
// ------------------------------------------------------------
case 175:
{
    doALUFixed<AluOp::AND, AluInput::TmpA>();
    updateFlags();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 098: ?1111000?.00
// Opcodes: F6-F7 /0, F6-F7 /1
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 176:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 099:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 177:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 09a:
// ------------------------------------------------------------
// M     -> tmpa      1   AND   tmpa, NX  
// ------------------------------------------------------------
case 178:
{
    tmpa() = mc_read_m();
    alu_ = AluOp::AND;
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpA;
    break;
}

// 09b:
// ------------------------------------------------------------
// SIGMA -> no dest   4   none  RNI      F
// ------------------------------------------------------------
case 179:
{
    doALUFixed<AluOp::AND, AluInput::TmpA>();
    updateFlags();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 09c: 01010100?.00
// Opcodes: A8-A9
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 180:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 09d:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 181:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 09e:
// ------------------------------------------------------------
// XA    -> tmpa      1   AND   tmpa, NX  
// ------------------------------------------------------------
case 182:
{
    tmpa() = rw(0);
    alu_ = AluOp::AND;
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpA;
    break;
}

// 09f:
// ------------------------------------------------------------
// SIGMA -> no dest   4   none  RNI      F
// ------------------------------------------------------------
case 183:
{
    doALUFixed<AluOp::AND, AluInput::TmpA>();
    updateFlags();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0a0: 011010110.00
// Opcodes: D6
// ------------------------------------------------------------
//                    0   CY       2      
// ------------------------------------------------------------
case 184:
{
    if (getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 0a1:
// ------------------------------------------------------------
// ZERO  -> A         4   none  RNI       
// ------------------------------------------------------------
case 185:
{
    rb(0) = static_cast<uint8_t>(0);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0a2:
// ------------------------------------------------------------
// ONES  -> A         4   none  RNI       
// ------------------------------------------------------------
case 186:
{
    rb(0) = static_cast<uint8_t>(0xffff);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0a4: 01000011?.00
// Opcodes: 86-87
// ------------------------------------------------------------
// R     -> tmpa                          
// ------------------------------------------------------------
case 9:
{
    tmpa() = mc_read_r();
    break;
}

// 0a5:
// ------------------------------------------------------------
// M     -> tmpb                          
// ------------------------------------------------------------
case 187:
{
    tmpb() = mc_read_m();
    break;
}

// 0a6:
// ------------------------------------------------------------
// tmpb  -> R         4   none  WB,NX     
// ------------------------------------------------------------
case 188:
{
    mc_write_r(tmpb());
    if (!m_is_m_ || !use_memory_ || alu_ == AluOp::CMP) {
        nx_ = true;
    }
    break;
}

// 0a7:
// ------------------------------------------------------------
// tmpa  -> M         4   none  RNI       
// ------------------------------------------------------------
case 189:
{
    mc_write_m(tmpa());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0a8: 01000011?.01
// Opcodes: none
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 190:
{
    startWriteRniDDP0();
    break;
}

// 0ac: 01110010?.00
// Opcodes: E4-E5
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 191:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 0ad:
// ------------------------------------------------------------
// ZERO  -> tmpbH     1   PASS  tmpb      
// ------------------------------------------------------------
case 192:
{
    tmpb() = (tmpb() & 0xff) | (0 << 8);
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 0ae:
// ------------------------------------------------------------
// SIGMA -> IND       6   R     D0,P0     
// ------------------------------------------------------------
case 193:
{
    const uint32_t sigma = doALUFixed<AluOp::PASS, AluInput::TmpB>();
    ind() = sigma;
    mc_bus(false, false, false, 1, 3);
    break;
}

// 0af:
// ------------------------------------------------------------
// OPR   -> M         4   none  RNI       
// ------------------------------------------------------------
case 194:
{
    mc_write_m(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0b0: 01110011?.00
// Opcodes: E6-E7
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 195:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 0b1:
// ------------------------------------------------------------
// ZERO  -> tmpbH     1   PASS  tmpb      
// ------------------------------------------------------------
case 10:
{
    tmpb() = (tmpb() & 0xff) | (0 << 8);
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 0b2:
// ------------------------------------------------------------
// SIGMA -> IND                           
// ------------------------------------------------------------
case 196:
{
    const uint32_t sigma = doALUFixed<AluOp::PASS, AluInput::TmpB>();
    ind() = sigma;
    break;
}

// 0b3:
// ------------------------------------------------------------
// XA    -> OPR       6   W,RNI D0,P0     
// ------------------------------------------------------------
case 197:
{
    opr() = rw(0);
    mc_bus(true, false, true, 1, 3);
    break;
}

// 0b4: 01110110?.00
// Opcodes: EC-ED
// ------------------------------------------------------------
// DE    -> IND       6   R     D0,P0     
// ------------------------------------------------------------
case 198:
{
    ind() = rw(2);
    mc_bus(false, false, false, 1, 3);
    break;
}

// 0b5:
// ------------------------------------------------------------
// OPR   -> M         4   none  RNI       
// ------------------------------------------------------------
case 199:
{
    mc_write_m(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0b8: 01110111?.00
// Opcodes: EE-EF
// ------------------------------------------------------------
// DE    -> IND                           
// ------------------------------------------------------------
case 200:
{
    ind() = rw(2);
    break;
}

// 0b9:
// ------------------------------------------------------------
// XA    -> OPR       6   W,RNI D0,P0     
// ------------------------------------------------------------
case 201:
{
    opr() = rw(0);
    mc_bus(true, false, true, 1, 3);
    break;
}

// 0bc: 0110000?1.00
// Opcodes: C1, C3
// ------------------------------------------------------------
// SP    -> IND       6   R     DS,P2     
// ------------------------------------------------------------
case 202:
{
    ind() = rw(4);
    mc_bus(false, false, false, 2, 0);
    break;
}

// 0bd:
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 203:
{
    suspendPrefetch();
    break;
}

// 0be:
// ------------------------------------------------------------
// OPR   -> PC        4   FLUSH none      
// ------------------------------------------------------------
case 204:
{
    pc() = opr();
    flushQueue();
    break;
}

// 0bf:
// ------------------------------------------------------------
// IND   -> SP        4   none  RNI       
// ------------------------------------------------------------
case 205:
{
    rw(4) = ind();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0c0: 0110010?1.00
// Opcodes: C9, CB
// ------------------------------------------------------------
//                    7   UNC   FARRET    
// ------------------------------------------------------------
case 206:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x0cb2; // FARRET
    state_ = stateSingleCycleWait;
    break;
}

// 0c1:
// ------------------------------------------------------------
// IND   -> SP        4   none  RNI       
// ------------------------------------------------------------
case 207:
{
    rw(4) = ind();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0c2:
// ------------------------------------------------------------
// SP    -> IND       6   R     DS,P2     
// ------------------------------------------------------------
case 208:
{
    ind() = rw(4);
    mc_bus(false, false, false, 2, 0);
    break;
}

// 0c3:
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 209:
{
    suspendPrefetch();
    break;
}

// 0c4: 0110010?1.01
// Opcodes: none
// ------------------------------------------------------------
// OPR   -> PC        0   X0       6      
// ------------------------------------------------------------
case 210:
{
    pc() = opr();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x6;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 0c5:
// ------------------------------------------------------------
//                    4   FLUSH RTN       
// ------------------------------------------------------------
case 211:
{
    flushQueue();
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 0c6:
// ------------------------------------------------------------
//                    6   R     DS,P2     
// ------------------------------------------------------------
case 212:
{
    mc_bus(false, false, false, 2, 0);
    break;
}

// 0c7:
// ------------------------------------------------------------
// OPR   -> RC        4   FLUSH RTN       
// ------------------------------------------------------------
case 213:
{
    sr(1) = opr();
    flushQueue();
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 0c8: 011001111.00
// Opcodes: CF
// ------------------------------------------------------------
//                    7   UNC   FARRET    
// ------------------------------------------------------------
case 214:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x0cb2; // FARRET
    state_ = stateSingleCycleWait;
    break;
}

// 0c9:
// ------------------------------------------------------------
//                    6   R     DS,P2     
// ------------------------------------------------------------
case 215:
{
    mc_bus(false, false, false, 2, 0);
    break;
}

// 0ca:
// ------------------------------------------------------------
// OPR   -> F                             
// ------------------------------------------------------------
case 11:
{
    flags() = (opr() & 0xffd5) | 0xf002;
    break;
}

// 0cb:
// ------------------------------------------------------------
// IND   -> SP        4   none  RNI       
// ------------------------------------------------------------
case 216:
{
    rw(4) = ind();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0cc: 01100?0?0.00
// Opcodes: C0, C2, C8, CA
// ------------------------------------------------------------
// Q     -> tmpaL     1   ADD   tmpa      
// ------------------------------------------------------------
case 217:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff00) | (queueRead(QueueReadState::SubsequentByte) & 0xff);
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 0cd:
// ------------------------------------------------------------
// Q     -> tmpaH     7   UNC   FARRET    
// ------------------------------------------------------------
case 218:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x0cb2; // FARRET
    state_ = stateSingleCycleWait;
    break;
}

// 0ce:
// ------------------------------------------------------------
// IND   -> tmpb                          
// ------------------------------------------------------------
case 12:
{
    tmpb() = ind();
    break;
}

// 0cf:
// ------------------------------------------------------------
// SIGMA -> SP        4   none  RNI       
// ------------------------------------------------------------
case 219:
{
    const uint32_t sigma = doALU();
    rw(4) = sigma;
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0d0: 0111010?1.00
// Opcodes: E9, EB
// ------------------------------------------------------------
// Q     -> tmpbL     0   L8       2      
// ------------------------------------------------------------
case 220:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupLoadRegisterImmediate) != 0 ? (opcode_ & 8) == 0 : ((opcode_ & 1) == 0 || (opcode_ & 6) == 2))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 0d1:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 221:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 0d2:
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 222:
{
    suspendPrefetch();
    break;
}

// 0d3:
// ------------------------------------------------------------
//                    4   none  CORR      
// ------------------------------------------------------------
case 223:
{
    correctPC();
    break;
}

// 0d4: 0111010?1.01
// Opcodes: none
// ------------------------------------------------------------
// PC    -> tmpa      1   ADD   tmpa      
// ------------------------------------------------------------
case 224:
{
    tmpa() = pc();
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 0d5:
// ------------------------------------------------------------
// SIGMA -> PC        4   FLUSH RNI       
// ------------------------------------------------------------
case 225:
{
    const uint32_t sigma = doALUFixed<AluOp::ADD, AluInput::TmpA>();
    pc() = sigma;
    flushQueue();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0d8: ?11111100.00
// Opcodes: FE-FF /4
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 226:
{
    suspendPrefetch();
    break;
}

// 0d9:
// ------------------------------------------------------------
// M     -> PC        4   FLUSH RNI       
// ------------------------------------------------------------
case 227:
{
    pc() = mc_read_m();
    flushQueue();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0dc: ?11111101.00
// Opcodes: FE-FF /5
// ------------------------------------------------------------
// IND   -> tmpc      1   INC2  tmpc      
// ------------------------------------------------------------
case 228:
{
    registers_[14] = ind();
    alu_ = AluOp::INC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 0dd:
// ------------------------------------------------------------
// SIGMA -> IND       4   none  SUSP      
// ------------------------------------------------------------
case 229:
{
    const uint32_t sigma = doALUFixed<AluOp::INC2, AluInput::TmpC>();
    ind() = sigma;
    suspendPrefetch();
    break;
}

// 0de:
// ------------------------------------------------------------
// tmpb  -> PC        6   R     DD,P0     
// ------------------------------------------------------------
case 230:
{
    pc() = tmpb();
    mc_bus(false, false, false, 3, 3);
    break;
}

// 0df:
// ------------------------------------------------------------
// OPR   -> RC        4   FLUSH RNI       
// ------------------------------------------------------------
case 231:
{
    sr(1) = opr();
    flushQueue();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0e0: 011101010.00
// Opcodes: EA
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 232:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 0e1:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 233:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 0e2:
// ------------------------------------------------------------
// Q     -> tmpaL                         
// ------------------------------------------------------------
case 234:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff00) | (queueRead(QueueReadState::SubsequentByte) & 0xff);
    break;
}

// 0e3:
// ------------------------------------------------------------
// Q     -> tmpaH                         
// ------------------------------------------------------------
case 235:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 0e4: 011101010.01
// Opcodes: none
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 236:
{
    suspendPrefetch();
    break;
}

// 0e5:
// ------------------------------------------------------------
// tmpb  -> PC                            
// ------------------------------------------------------------
case 237:
{
    pc() = tmpb();
    break;
}

// 0e6:
// ------------------------------------------------------------
// tmpa  -> RC        4   FLUSH RNI       
// ------------------------------------------------------------
case 238:
{
    sr(1) = tmpa();
    flushQueue();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0e8: 0011?????.00
// Opcodes: 60-7F
// ------------------------------------------------------------
// Q     -> tmpbL                         
// ------------------------------------------------------------
case 239:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 0e9:
// ------------------------------------------------------------
//                    5   XC    RELJMP    
// ------------------------------------------------------------
case 240:
{
    const bool overflow = (flags() & 0x800) != 0;
    const bool carry = (flags() & 1) != 0;
    const bool zero = (flags() & 0x40) != 0;
    const bool sign = (flags() & 0x80) != 0;
    const bool conditions[] = {overflow, carry, zero, carry || zero, sign, (flags() & 4) != 0, sign != overflow, (sign != overflow) || zero};
    if (conditions[(opcode_ >> 1) & 7] != ((opcode_ & 1) != 0)) {
        skip_rni_ = false;
        microcode_pointer_ = 0x0eb2; // RELJMP
        state_ = stateSingleCycleWait;
    }
    break;
}

// 0ea:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 241:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0ec: 0100011?0.00
// Opcodes: 8C, 8E
// ------------------------------------------------------------
// R     -> M         4   none  RNI       
// ------------------------------------------------------------
case 242:
{
    mc_write_m(mc_read_r());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0ed:
// ------------------------------------------------------------
//                    6   W,RNI DD,P0     
// ------------------------------------------------------------
case 243:
{
    startWriteRniDDP0();
    break;
}

// 0f0: 011000100.00
// Opcodes: C4
// ------------------------------------------------------------
// OPR   -> R                             
// ------------------------------------------------------------
case 13:
{
    mc_write_r(opr());
    break;
}

// 0f1:
// ------------------------------------------------------------
// IND   -> tmpc      1   INC2  tmpc      
// ------------------------------------------------------------
case 244:
{
    registers_[14] = ind();
    alu_ = AluOp::INC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 0f2:
// ------------------------------------------------------------
// SIGMA -> IND       6   R     DD,P0     
// ------------------------------------------------------------
case 245:
{
    const uint32_t sigma = doALUFixed<AluOp::INC2, AluInput::TmpC>();
    ind() = sigma;
    mc_bus(false, false, false, 3, 3);
    break;
}

// 0f3:
// ------------------------------------------------------------
// OPR   -> RA        4   none  RNI       
// ------------------------------------------------------------
case 246:
{
    sr(0) = opr();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0f4: 011000101.00
// Opcodes: C5
// ------------------------------------------------------------
// OPR   -> R                             
// ------------------------------------------------------------
case 14:
{
    mc_write_r(opr());
    break;
}

// 0f5:
// ------------------------------------------------------------
// IND   -> tmpc      1   INC2  tmpc      
// ------------------------------------------------------------
case 247:
{
    registers_[14] = ind();
    alu_ = AluOp::INC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 0f6:
// ------------------------------------------------------------
// SIGMA -> IND       6   R     DD,P0     
// ------------------------------------------------------------
case 248:
{
    const uint32_t sigma = doALUFixed<AluOp::INC2, AluInput::TmpC>();
    ind() = sigma;
    mc_bus(false, false, false, 3, 3);
    break;
}

// 0f7:
// ------------------------------------------------------------
// OPR   -> RD        4   none  RNI       
// ------------------------------------------------------------
case 249:
{
    sr(3) = opr();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0f8: 010011011.00
// Opcodes: 9B
// ------------------------------------------------------------
//                    0   TEST     3      
// ------------------------------------------------------------
case 250:
{
    if (test_pin_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x3;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 0f9:
// ------------------------------------------------------------
//                    4   WAIT  none      
// ------------------------------------------------------------
case 15:
{
    break;
}

// 0fa:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 251:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 0fb:
// ------------------------------------------------------------
//                    0   INT      5      
// ------------------------------------------------------------
case 252:
{
    if (interrupt_pending_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 0fc: 010011011.01
// Opcodes: none
// ------------------------------------------------------------
//                    0   UNC      0      
// ------------------------------------------------------------
case 253:
{
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x0;
    state_ = stateSingleCycleWait;
    break;
}

// 0fd:
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 254:
{
    suspendPrefetch();
    break;
}

// 0fe:
// ------------------------------------------------------------
//                    4   none  CORR      
// ------------------------------------------------------------
case 255:
{
    correctPC();
    break;
}

// 0ff:
// ------------------------------------------------------------
// PC    -> tmpc      1   DEC   tmpc      
// ------------------------------------------------------------
case 256:
{
    registers_[14] = pc();
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 100: 010011110.00
// Opcodes: 9E
// ------------------------------------------------------------
//                                        
// ------------------------------------------------------------
case 16:
{
    break;
}

// 101:
// ------------------------------------------------------------
// F     -> tmpa                          
// ------------------------------------------------------------
case 257:
{
    tmpa() = flags();
    break;
}

// 102:
// ------------------------------------------------------------
// X     -> tmpaL     4   none  NX        
// ------------------------------------------------------------
case 258:
{
    tmpa() = (tmpa() & 0xff00) | (rb(4) & 0xff);
    nx_ = true;
    break;
}

// 103:
// ------------------------------------------------------------
// tmpa  -> F         4   none  RNI       
// ------------------------------------------------------------
case 259:
{
    flags() = (tmpa() & 0xffd5) | 0xf002;
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 104: 010011111.00
// Opcodes: 9F
// ------------------------------------------------------------
//                    4   none  NX        
// ------------------------------------------------------------
case 260:
{
    nx_ = true;
    break;
}

// 105:
// ------------------------------------------------------------
// F     -> X         4   none  RNI       
// ------------------------------------------------------------
case 261:
{
    rb(4) = static_cast<uint8_t>(flags());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 108: 011011???.00
// Opcodes: D8-DF
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 262:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 10c: 011010111.00
// Opcodes: D7
// ------------------------------------------------------------
// ZERO  -> tmpa                          
// ------------------------------------------------------------
case 17:
{
    tmpa() = 0;
    break;
}

// 10d:
// ------------------------------------------------------------
// XA    -> tmpaL                         
// ------------------------------------------------------------
case 263:
{
    tmpa() = (tmpa() & 0xff00) | (rw(0) & 0xff);
    break;
}

// 10e:
// ------------------------------------------------------------
// HL    -> tmpb      1   ADD   tmpa      
// ------------------------------------------------------------
case 264:
{
    tmpb() = rw(3);
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 10f:
// ------------------------------------------------------------
// SIGMA -> IND       6   R     DD,P0     
// ------------------------------------------------------------
case 265:
{
    const uint32_t sigma = doALUFixed<AluOp::ADD, AluInput::TmpA>();
    ind() = sigma;
    mc_bus(false, false, false, 3, 3);
    break;
}

// 110: 011010111.01
// Opcodes: none
// ------------------------------------------------------------
// OPR   -> A         4   none  RNI       
// ------------------------------------------------------------
case 266:
{
    rb(0) = static_cast<uint8_t>(opr());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 111:
// ------------------------------------------------------------
//                                        
// ------------------------------------------------------------
case 267:
{
    break;
}

// 112:
// ------------------------------------------------------------
// BC    -> tmpc      1   PASS  tmpc      
// ------------------------------------------------------------
case 18:
{
    registers_[14] = rw(1);
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 113:
// ------------------------------------------------------------
// SIGMA -> no dest   1   DEC   tmpc      
// ------------------------------------------------------------
case 268:
{
    doALUFixed<AluOp::PASS, AluInput::TmpC>();
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 114: 011010111.10
// Opcodes: none
// ------------------------------------------------------------
//                    0   NZ      10      
// ------------------------------------------------------------
case 269:
{
    if (!super_zero_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xa;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 115:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 270:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 116:
// ------------------------------------------------------------
//                    4   none  RTN       
// ------------------------------------------------------------
case 271:
{
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 117:
// ------------------------------------------------------------
//                                        
// ------------------------------------------------------------
case 272:
{
    break;
}

// 118: 011010111.11
// Opcodes: none
// ------------------------------------------------------------
// tmpc  -> BC        4   none  SUSP      
// ------------------------------------------------------------
case 273:
{
    rw(1) = registers_[14];
    suspendPrefetch();
    break;
}

// 119:
// ------------------------------------------------------------
//                    4   none  CORR      
// ------------------------------------------------------------
case 274:
{
    correctPC();
    break;
}

// 11a:
// ------------------------------------------------------------
// PC    -> tmpb      1   DEC2  tmpb      
// ------------------------------------------------------------
case 275:
{
    tmpb() = pc();
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 11b:
// ------------------------------------------------------------
// SIGMA -> PC        4   FLUSH RNI       
// ------------------------------------------------------------
case 276:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpB>();
    pc() = sigma;
    flushQueue();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 11c: 01010101?.00
// Opcodes: AA-AB
// ------------------------------------------------------------
// IK    -> IND       7   F1    RPTS      
// ------------------------------------------------------------
case 277:
{
    ind() = rw(7);
    if (f1_) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x0d76; // RPTS
        state_ = stateSingleCycleWait;
    }
    break;
}

// 11d:
// ------------------------------------------------------------
// M     -> OPR       6   w     DA,BL     
// ------------------------------------------------------------
case 278:
{
    opr() = mc_read_m();
    mc_bus(true, false, false, 0, 1);
    break;
}

// 11e:
// ------------------------------------------------------------
// IND   -> IK        0   NF1      5      
// ------------------------------------------------------------
case 279:
{
    rw(7) = ind();
    if (!f1_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 11f:
// ------------------------------------------------------------
// SIGMA -> tmpc      5   INT   RPTI      
// ------------------------------------------------------------
case 280:
{
    const uint32_t sigma = doALU();
    registers_[14] = sigma;
    if (interrupt_pending_) {
        skip_rni_ = false;
        microcode_pointer_ = 0x0d7c; // RPTI
        state_ = stateSingleCycleWait;
    }
    break;
}

// 120: 01010?11?.00
// Opcodes: A6-A7, AE-AF
// ------------------------------------------------------------
//                    7   F1    RPTS      
// ------------------------------------------------------------
case 281:
{
    if (f1_) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x0d76; // RPTS
        state_ = stateSingleCycleWait;
    }
    break;
}

// 121:
// ------------------------------------------------------------
// M     -> tmpa      0   X0       5      
// ------------------------------------------------------------
case 282:
{
    tmpa() = mc_read_m();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 122:
// ------------------------------------------------------------
// IJ    -> IND       6   R     DD,BL     
// ------------------------------------------------------------
case 283:
{
    ind() = rw(6);
    mc_bus(false, false, false, 3, 1);
    break;
}

// 123:
// ------------------------------------------------------------
// IND   -> IJ                            
// ------------------------------------------------------------
case 19:
{
    rw(6) = ind();
    break;
}

// 124: 01010?11?.01
// Opcodes: none
// ------------------------------------------------------------
// OPR   -> tmpa                          
// ------------------------------------------------------------
case 284:
{
    tmpa() = opr();
    break;
}

// 125:
// ------------------------------------------------------------
// IK    -> IND       6   R     DA,BL     
// ------------------------------------------------------------
case 285:
{
    ind() = rw(7);
    mc_bus(false, false, false, 0, 1);
    break;
}

// 126:
// ------------------------------------------------------------
// OPR   -> tmpb      1   SUBT  tmpa      
// ------------------------------------------------------------
case 20:
{
    tmpb() = opr();
    alu_ = AluOp::SUBT;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 127:
// ------------------------------------------------------------
// SIGMA -> no dest   1   DEC   tmpc     F
// ------------------------------------------------------------
case 286:
{
    doALUFixed<AluOp::SUBT, AluInput::TmpA>();
    updateFlags();
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 128: 01010?11?.10
// Opcodes: none
// ------------------------------------------------------------
// IND   -> IK        0   NF1     12      
// ------------------------------------------------------------
case 287:
{
    rw(7) = ind();
    if (!f1_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xc;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 129:
// ------------------------------------------------------------
// SIGMA -> BC        0   F1ZZ    12      
// ------------------------------------------------------------
case 288:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC, AluInput::TmpC>();
    rw(1) = sigma;
    if (((group_ & groupF1ZZFromPrefix) != 0 ? ((flags() & 0x40) != 0) == (f1_ && repne_) : ((flags() & 0x40) != 0) != ((opcode_ & 1) != 0))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xc;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 12a:
// ------------------------------------------------------------
// SIGMA -> tmpc      5   INT   RPTI      
// ------------------------------------------------------------
case 289:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC, AluInput::TmpC>();
    registers_[14] = sigma;
    if (interrupt_pending_) {
        skip_rni_ = false;
        microcode_pointer_ = 0x0d7c; // RPTI
        state_ = stateSingleCycleWait;
    }
    break;
}

// 12b:
// ------------------------------------------------------------
//                    0   NZ       1      
// ------------------------------------------------------------
case 290:
{
    if (!super_zero_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x1;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 12c: 01010?10?.00
// Opcodes: A4-A5, AC-AD
// ------------------------------------------------------------
//                    7   F1    RPTS      
// ------------------------------------------------------------
case 291:
{
    if (f1_) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x0d76; // RPTS
        state_ = stateSingleCycleWait;
    }
    break;
}

// 12d:
// ------------------------------------------------------------
// IJ    -> IND       6   R     DD,BL     
// ------------------------------------------------------------
case 292:
{
    ind() = rw(6);
    mc_bus(false, false, false, 3, 1);
    break;
}

// 12e:
// ------------------------------------------------------------
// IND   -> IJ        0   X0       8      
// ------------------------------------------------------------
case 293:
{
    rw(6) = ind();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x8;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 12f:
// ------------------------------------------------------------
// IK    -> IND       6   w     DA,BL     
// ------------------------------------------------------------
case 294:
{
    ind() = rw(7);
    mc_bus(true, false, false, 0, 1);
    break;
}

// 130: 01010?10?.01
// Opcodes: none
// ------------------------------------------------------------
// IND   -> IK        0   NF1      7      
// ------------------------------------------------------------
case 295:
{
    rw(7) = ind();
    if (!f1_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 131:
// ------------------------------------------------------------
// SIGMA -> tmpc      5   INT   RPTI      
// ------------------------------------------------------------
case 296:
{
    const uint32_t sigma = doALU();
    registers_[14] = sigma;
    if (interrupt_pending_) {
        skip_rni_ = false;
        microcode_pointer_ = 0x0d7c; // RPTI
        state_ = stateSingleCycleWait;
    }
    break;
}

// 132:
// ------------------------------------------------------------
// tmpc  -> BC        0   NZ       1      
// ------------------------------------------------------------
case 297:
{
    rw(1) = registers_[14];
    if (!super_zero_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x1;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 133:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 298:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 134: 011100011.00
// Opcodes: E3
// ------------------------------------------------------------
// BC    -> tmpc      1   PASS  tmpc      
// ------------------------------------------------------------
case 21:
{
    registers_[14] = rw(1);
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 135:
// ------------------------------------------------------------
// SIGMA -> no dest                       
// ------------------------------------------------------------
case 299:
{
    doALUFixed<AluOp::PASS, AluInput::TmpC>();
    break;
}

// 136:
// ------------------------------------------------------------
// Q     -> tmpbL     0   NZ       4      
// ------------------------------------------------------------
case 300:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (!super_zero_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x4;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 137:
// ------------------------------------------------------------
//                    5   UNC   RELJMP    
// ------------------------------------------------------------
case 301:
{
    skip_rni_ = false;
    microcode_pointer_ = 0x0eb2; // RELJMP
    state_ = stateSingleCycleWait;
    break;
}

// 138: 01110000?.00
// Opcodes: E0-E1
// ------------------------------------------------------------
// BC    -> tmpc      1   DEC   tmpc      
// ------------------------------------------------------------
case 22:
{
    registers_[14] = rw(1);
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 139:
// ------------------------------------------------------------
// SIGMA -> BC                            
// ------------------------------------------------------------
case 302:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC, AluInput::TmpC>();
    rw(1) = sigma;
    break;
}

// 13a:
// ------------------------------------------------------------
// Q     -> tmpbL     0   F1ZZ     4      
// ------------------------------------------------------------
case 303:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (((group_ & groupF1ZZFromPrefix) != 0 ? ((flags() & 0x40) != 0) == (f1_ && repne_) : ((flags() & 0x40) != 0) != ((opcode_ & 1) != 0))) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x4;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 13b:
// ------------------------------------------------------------
//                    5   NZ    RELJMP    
// ------------------------------------------------------------
case 304:
{
    if (!super_zero_) {
        skip_rni_ = false;
        microcode_pointer_ = 0x0eb2; // RELJMP
        state_ = stateSingleCycleWait;
    }
    break;
}

// 13c: 01110000?.01
// Opcodes: none
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 305:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 140: 011100010.00
// Opcodes: E2
// ------------------------------------------------------------
// BC    -> tmpc      1   DEC   tmpc      
// ------------------------------------------------------------
case 23:
{
    registers_[14] = rw(1);
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 141:
// ------------------------------------------------------------
// SIGMA -> BC                            
// ------------------------------------------------------------
case 306:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC, AluInput::TmpC>();
    rw(1) = sigma;
    break;
}

// 142:
// ------------------------------------------------------------
// Q     -> tmpbL     5   NZ    RELJMP    
// ------------------------------------------------------------
case 307:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if (!super_zero_) {
        skip_rni_ = false;
        microcode_pointer_ = 0x0eb2; // RELJMP
        state_ = stateSingleCycleWait;
    }
    break;
}

// 143:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 308:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 144: 00010?111.00
// Opcodes: 27, 2F
// ------------------------------------------------------------
// A     -> tmpaL     1   XI    tmpa      
// ------------------------------------------------------------
case 24:
{
    tmpa() = (tmpa() & 0xff00) | (rb(0) & 0xff);
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 145:
// ------------------------------------------------------------
// ONES  -> tmpb                          
// ------------------------------------------------------------
case 309:
{
    tmpb() = 0xffff;
    break;
}

// 146:
// ------------------------------------------------------------
// SIGMA -> A         1   ADD   tmpa, NX F
// ------------------------------------------------------------
case 310:
{
    const uint32_t sigma = doALU();
    updateFlags();
    rb(0) = static_cast<uint8_t>(sigma);
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpA;
    break;
}

// 147:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 311:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 148: 00011?111.00
// Opcodes: 37, 3F
// ------------------------------------------------------------
// A     -> tmpaL     1   XI    tmpa      
// ------------------------------------------------------------
case 25:
{
    tmpa() = (tmpa() & 0xff00) | (rb(0) & 0xff);
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 149:
// ------------------------------------------------------------
// ONES  -> tmpb                          
// ------------------------------------------------------------
case 312:
{
    tmpb() = 0xffff;
    break;
}

// 14a:
// ------------------------------------------------------------
// SIGMA -> A         1   DEC   tmpb     F
// ------------------------------------------------------------
case 313:
{
    const uint32_t sigma = doALU();
    updateFlags();
    rb(0) = static_cast<uint8_t>(sigma);
    alu_ = AluOp::DEC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 14b:
// ------------------------------------------------------------
//                    0   X0       5      
// ------------------------------------------------------------
case 314:
{
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 14c: 00011?111.01
// Opcodes: none
// ------------------------------------------------------------
//                    1   INC   tmpb      
// ------------------------------------------------------------
case 315:
{
    alu_ = AluOp::INC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 14d:
// ------------------------------------------------------------
// X     -> tmpb      0   NCY      7      
// ------------------------------------------------------------
case 316:
{
    tmpb() = rb(4);
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 14e:
// ------------------------------------------------------------
// SIGMA -> X         4   none  RNI       
// ------------------------------------------------------------
case 317:
{
    const uint32_t sigma = doALU();
    rb(4) = static_cast<uint8_t>(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 14f:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 318:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 150: 01111010?.00
// Opcodes: F6 /4, F6 /5
// ------------------------------------------------------------
// A     -> tmpc      1   LRCY  tmpc      
// ------------------------------------------------------------
case 26:
{
    registers_[14] = rb(0);
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 151:
// ------------------------------------------------------------
// M     -> tmpb      7   X0    PREIMUL   
// ------------------------------------------------------------
case 319:
{
    tmpb() = mc_read_m();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x123c; // PREIMUL
        state_ = stateSingleCycleWait;
    }
    break;
}

// 152:
// ------------------------------------------------------------
//                    7   UNC   CORX      
// ------------------------------------------------------------
case 320:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x04f3; // CORX
    state_ = stateSingleCycleWait;
    break;
}

// 153:
// ------------------------------------------------------------
//                    7   F1    NEGATE    
// ------------------------------------------------------------
case 321:
{
    if (f1_) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1232; // NEGATE
        state_ = stateSingleCycleWait;
    }
    break;
}

// 154: 01111010?.01
// Opcodes: none
// ------------------------------------------------------------
//                    7   X0    IMULCOF   
// ------------------------------------------------------------
case 322:
{
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1249; // IMULCOF
        state_ = stateSingleCycleWait;
    }
    break;
}

// 155:
// ------------------------------------------------------------
// tmpc  -> A         0   X0       7      
// ------------------------------------------------------------
case 323:
{
    rb(0) = static_cast<uint8_t>(registers_[14]);
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 156:
// ------------------------------------------------------------
//                    7   UNC   MULCOF    
// ------------------------------------------------------------
case 324:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x124e; // MULCOF
    state_ = stateSingleCycleWait;
    break;
}

// 157:
// ------------------------------------------------------------
// tmpa  -> X         4   none  RNI       
// ------------------------------------------------------------
case 325:
{
    rb(4) = static_cast<uint8_t>(tmpa());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 158: 11111010?.00
// Opcodes: F7 /4, F7 /5
// ------------------------------------------------------------
// XA    -> tmpc      1   LRCY  tmpc      
// ------------------------------------------------------------
case 27:
{
    registers_[14] = rw(0);
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 159:
// ------------------------------------------------------------
// M     -> tmpb      7   X0    PREIMUL   
// ------------------------------------------------------------
case 326:
{
    tmpb() = mc_read_m();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x123c; // PREIMUL
        state_ = stateSingleCycleWait;
    }
    break;
}

// 15a:
// ------------------------------------------------------------
//                    7   UNC   CORX      
// ------------------------------------------------------------
case 327:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x04f3; // CORX
    state_ = stateSingleCycleWait;
    break;
}

// 15b:
// ------------------------------------------------------------
//                    7   F1    NEGATE    
// ------------------------------------------------------------
case 328:
{
    if (f1_) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1232; // NEGATE
        state_ = stateSingleCycleWait;
    }
    break;
}

// 15c: 11111010?.01
// Opcodes: none
// ------------------------------------------------------------
//                    7   X0    IMULCOF   
// ------------------------------------------------------------
case 329:
{
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1249; // IMULCOF
        state_ = stateSingleCycleWait;
    }
    break;
}

// 15d:
// ------------------------------------------------------------
// tmpc  -> XA        0   X0       7      
// ------------------------------------------------------------
case 330:
{
    rw(0) = registers_[14];
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 15e:
// ------------------------------------------------------------
//                    7   UNC   MULCOF    
// ------------------------------------------------------------
case 331:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x124e; // MULCOF
    state_ = stateSingleCycleWait;
    break;
}

// 15f:
// ------------------------------------------------------------
// tmpa  -> DE        4   none  RNI       
// ------------------------------------------------------------
case 332:
{
    rw(2) = tmpa();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 160: 01111011?.00
// Opcodes: F6 /6, F6 /7
// ------------------------------------------------------------
// X     -> tmpa                          
// ------------------------------------------------------------
case 28:
{
    tmpa() = rb(4);
    break;
}

// 161:
// ------------------------------------------------------------
// A     -> tmpc      1   LRCY  tmpa      
// ------------------------------------------------------------
case 333:
{
    registers_[14] = rb(0);
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 162:
// ------------------------------------------------------------
// M     -> tmpb      7   X0    PREIDIV   
// ------------------------------------------------------------
case 334:
{
    tmpb() = mc_read_m();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1230; // PREIDIV
        state_ = stateSingleCycleWait;
    }
    break;
}

// 163:
// ------------------------------------------------------------
//                    7   UNC   CORD      
// ------------------------------------------------------------
case 335:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x1220; // CORD
    state_ = stateSingleCycleWait;
    break;
}

// 164: 01111011?.01
// Opcodes: none
// ------------------------------------------------------------
//                    1   COM1  tmpc      
// ------------------------------------------------------------
case 29:
{
    alu_ = AluOp::COM1;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 165:
// ------------------------------------------------------------
// X     -> tmpb      7   X0    POSTIDIV  
// ------------------------------------------------------------
case 336:
{
    tmpb() = rb(4);
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1240; // POSTIDIV
        state_ = stateSingleCycleWait;
    }
    break;
}

// 166:
// ------------------------------------------------------------
// SIGMA -> A         4   none  NX        
// ------------------------------------------------------------
case 337:
{
    const uint32_t sigma = doALU();
    rb(0) = static_cast<uint8_t>(sigma);
    nx_ = true;
    break;
}

// 167:
// ------------------------------------------------------------
// tmpa  -> X         4   none  RNI       
// ------------------------------------------------------------
case 338:
{
    rb(4) = static_cast<uint8_t>(tmpa());
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 168: 11111011?.00
// Opcodes: F7 /6, F7 /7
// ------------------------------------------------------------
// DE    -> tmpa                          
// ------------------------------------------------------------
case 30:
{
    tmpa() = rw(2);
    break;
}

// 169:
// ------------------------------------------------------------
// XA    -> tmpc      1   LRCY  tmpa      
// ------------------------------------------------------------
case 339:
{
    registers_[14] = rw(0);
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 16a:
// ------------------------------------------------------------
// M     -> tmpb      7   X0    PREIDIV   
// ------------------------------------------------------------
case 340:
{
    tmpb() = mc_read_m();
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1230; // PREIDIV
        state_ = stateSingleCycleWait;
    }
    break;
}

// 16b:
// ------------------------------------------------------------
//                    7   UNC   CORD      
// ------------------------------------------------------------
case 341:
{
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x1220; // CORD
    state_ = stateSingleCycleWait;
    break;
}

// 16c: 11111011?.01
// Opcodes: none
// ------------------------------------------------------------
//                    1   COM1  tmpc      
// ------------------------------------------------------------
case 31:
{
    alu_ = AluOp::COM1;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 16d:
// ------------------------------------------------------------
// DE    -> tmpb      7   X0    POSTIDIV  
// ------------------------------------------------------------
case 342:
{
    tmpb() = rw(2);
    if ((((group_ & groupMicrocodePointerFromOpcode) != 0 ? opcode_ : mod_rm_) & 8) != 0) {
        skip_rni_ = false;
        microcode_return_ = microcode_pointer_;
        microcode_pointer_ = 0x1240; // POSTIDIV
        state_ = stateSingleCycleWait;
    }
    break;
}

// 16e:
// ------------------------------------------------------------
// SIGMA -> XA        4   none  NX        
// ------------------------------------------------------------
case 343:
{
    const uint32_t sigma = doALU();
    rw(0) = sigma;
    nx_ = true;
    break;
}

// 16f:
// ------------------------------------------------------------
// tmpa  -> DE        4   none  RNI       
// ------------------------------------------------------------
case 344:
{
    rw(2) = tmpa();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 170: 011010101.00
// Opcodes: D5
// ------------------------------------------------------------
// Q     -> tmpc                          
// ------------------------------------------------------------
case 345:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    registers_[14] = queueRead(QueueReadState::SubsequentByte);
    break;
}

// 171:
// ------------------------------------------------------------
// X     -> tmpb      7   UNC   CORX      
// ------------------------------------------------------------
case 346:
{
    tmpb() = rb(4);
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x04f3; // CORX
    state_ = stateSingleCycleWait;
    break;
}

// 172:
// ------------------------------------------------------------
// A     -> tmpb      1   ADD   tmpc      
// ------------------------------------------------------------
case 32:
{
    tmpb() = rb(0);
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 173:
// ------------------------------------------------------------
// ZERO  -> X         5   UNC   AAEND     
// ------------------------------------------------------------
case 347:
{
    rb(4) = static_cast<uint8_t>(0);
    skip_rni_ = false;
    microcode_pointer_ = 0x0d45; // AAEND
    state_ = stateSingleCycleWait;
    break;
}

// 174: 011010100.00
// Opcodes: D4
// ------------------------------------------------------------
// Q     -> tmpb                          
// ------------------------------------------------------------
case 348:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = queueRead(QueueReadState::SubsequentByte);
    break;
}

// 175:
// ------------------------------------------------------------
// ZERO  -> tmpa                          
// ------------------------------------------------------------
case 33:
{
    tmpa() = 0;
    break;
}

// 176:
// ------------------------------------------------------------
// A     -> tmpc      7   UNC   CORD      
// ------------------------------------------------------------
case 349:
{
    registers_[14] = rb(0);
    skip_rni_ = false;
    microcode_return_ = microcode_pointer_;
    microcode_pointer_ = 0x1220; // CORD
    state_ = stateSingleCycleWait;
    break;
}

// 177:
// ------------------------------------------------------------
//                    1   COM1  tmpc      
// ------------------------------------------------------------
case 350:
{
    alu_ = AluOp::COM1;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 178: 011010100.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> X         1   PASS  tmpa, NX  
// ------------------------------------------------------------
case 351:
{
    const uint32_t sigma = doALUFixed<AluOp::COM1, AluInput::TmpC>();
    rb(4) = static_cast<uint8_t>(sigma);
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpA;
    break;
}

// 179:
// ------------------------------------------------------------
// SIGMA -> A         4   none  RNI      F
// ------------------------------------------------------------
case 352:
{
    const uint32_t sigma = doALU();
    updateFlags();
    rb(0) = static_cast<uint8_t>(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 17c: 00100????.00
// Opcodes: 40-4F
// ------------------------------------------------------------
// M     -> tmpb      1   XI    tmpb, NX  
// ------------------------------------------------------------
case 353:
{
    tmpb() = mc_read_m();
    carry_latch_ = true;
    nx_ = true;
    if (m_is_m_ && use_memory_ && (group_ & groupEffectiveAddress) != 0) {
        nx_ = false;
    }
    alu_input_ = AluInput::TmpB;
    readFlags();
    alu_ = static_cast<AluOp>(((((opcode_ & 0x80) != 0 ? mod_rm_ : opcode_) >> 3) & 7) | ((opcode_ >> 3) & 8) | ((group_ & groupAddSubBooleanRotate) != 0 ? 0 : 0x10));
    break;
}

// 17d:
// ------------------------------------------------------------
// SIGMA -> M         4   none  RNI      F
// ------------------------------------------------------------
case 354:
{
    const uint32_t sigma = doALU();
    updateFlags();
    mc_write_m(sigma);
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 17e:
// ------------------------------------------------------------
//                                        
// ------------------------------------------------------------
case 355:
{
    break;
}

// 17f:
// ------------------------------------------------------------
// ZERO  -> tmpa      1   RRCY  tmpc      
// ------------------------------------------------------------
case 34:
{
    tmpa() = 0;
    alu_ = AluOp::RRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 180: 00100????.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> tmpc      4   MAXC  none      
// ------------------------------------------------------------
case 356:
{
    const uint32_t sigma = doALUFixed<AluOp::RRCY, AluInput::TmpC>();
    registers_[14] = sigma;
    counter_ = word_size_ ? 15 : 7;
    break;
}

// 181:
// ------------------------------------------------------------
//                    0   NCY      8      
// ------------------------------------------------------------
case 357:
{
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x8;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 182:
// ------------------------------------------------------------
//                    1   ADD   tmpa      
// ------------------------------------------------------------
case 35:
{
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 183:
// ------------------------------------------------------------
// SIGMA -> tmpa                         F
// ------------------------------------------------------------
case 358:
{
    const uint32_t sigma = doALUFixed<AluOp::ADD, AluInput::TmpA>();
    updateFlags();
    tmpa() = sigma;
    break;
}

// 184: 00100????.10
// Opcodes: none
// ------------------------------------------------------------
//                    1   RRCY  tmpa      
// ------------------------------------------------------------
case 36:
{
    alu_ = AluOp::RRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 185:
// ------------------------------------------------------------
// SIGMA -> tmpa      1   RRCY  tmpc      
// ------------------------------------------------------------
case 359:
{
    const uint32_t sigma = doALUFixed<AluOp::RRCY, AluInput::TmpA>();
    tmpa() = sigma;
    alu_ = AluOp::RRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 186:
// ------------------------------------------------------------
// SIGMA -> tmpc      0   NCZ      5      
// ------------------------------------------------------------
case 360:
{
    const uint32_t sigma = doALUFixed<AluOp::RRCY, AluInput::TmpC>();
    registers_[14] = sigma;
    if (--counter_ != -1) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 187:
// ------------------------------------------------------------
//                    4   none  RTN       
// ------------------------------------------------------------
case 361:
{
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 188: 100100010.00
// Opcodes: none
// ------------------------------------------------------------
//                    1   SUBT  tmpa      
// ------------------------------------------------------------
case 37:
{
    alu_ = AluOp::SUBT;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 189:
// ------------------------------------------------------------
// SIGMA -> no dest   4   MAXC  none     F
// ------------------------------------------------------------
case 362:
{
    doALUFixed<AluOp::SUBT, AluInput::TmpA>();
    updateFlags();
    counter_ = word_size_ ? 15 : 7;
    break;
}

// 18a:
// ------------------------------------------------------------
//                    5   NCY   INT0      
// ------------------------------------------------------------
case 363:
{
    if (!getAluCF()) {
        skip_rni_ = false;
        microcode_pointer_ = 0x100f; // INT0
        state_ = stateSingleCycleWait;
    }
    break;
}

// 18b:
// ------------------------------------------------------------
//                    1   LRCY  tmpc      
// ------------------------------------------------------------
case 38:
{
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 18c: 100100010.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> tmpc      1   LRCY  tmpa      
// ------------------------------------------------------------
case 364:
{
    const uint32_t sigma = doALUFixed<AluOp::LRCY, AluInput::TmpC>();
    registers_[14] = sigma;
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 18d:
// ------------------------------------------------------------
// SIGMA -> tmpa      1   SUBT  tmpa      
// ------------------------------------------------------------
case 365:
{
    const uint32_t sigma = doALUFixed<AluOp::LRCY, AluInput::TmpA>();
    tmpa() = sigma;
    alu_ = AluOp::SUBT;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 18e:
// ------------------------------------------------------------
//                    0   CY      13      
// ------------------------------------------------------------
case 366:
{
    if (getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xd;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 18f:
// ------------------------------------------------------------
// SIGMA -> no dest                      F
// ------------------------------------------------------------
case 39:
{
    doALUFixed<AluOp::SUBT, AluInput::TmpA>();
    updateFlags();
    break;
}

// 190: 100100010.10
// Opcodes: none
// ------------------------------------------------------------
//                    0   NCY     14      
// ------------------------------------------------------------
case 367:
{
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xe;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 191:
// ------------------------------------------------------------
//                    0   NCZ      3      
// ------------------------------------------------------------
case 368:
{
    if (--counter_ != -1) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x3;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 192:
// ------------------------------------------------------------
//                    1   LRCY  tmpc      
// ------------------------------------------------------------
case 40:
{
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 193:
// ------------------------------------------------------------
// SIGMA -> tmpc                          
// ------------------------------------------------------------
case 369:
{
    const uint32_t sigma = doALUFixed<AluOp::LRCY, AluInput::TmpC>();
    registers_[14] = sigma;
    break;
}

// 194: 100100010.11
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> no dest   4   none  RTN       
// ------------------------------------------------------------
case 370:
{
    doALUFixed<AluOp::LRCY, AluInput::TmpC>();
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 195:
// ------------------------------------------------------------
//                    4   RCY   none      
// ------------------------------------------------------------
case 371:
{
    setInternalCarry(false);
    carry_latch_ = false;
    break;
}

// 196:
// ------------------------------------------------------------
// SIGMA -> tmpa      0   NCZ      3      
// ------------------------------------------------------------
case 372:
{
    const uint32_t sigma = doALU();
    tmpa() = sigma;
    if (--counter_ != -1) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x3;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 197:
// ------------------------------------------------------------
//                    0   UNC     10      
// ------------------------------------------------------------
case 373:
{
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xa;
    state_ = stateSingleCycleWait;
    break;
}

// 198: 100000000.00
// Opcodes: none
// ------------------------------------------------------------
// CR    -> OPR       0   UNC      5      
// ------------------------------------------------------------
case 374:
{
    word_size_ = true;
    opr() = (microcode_pointer_ & 0xf);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
    state_ = stateSingleCycleWait;
    break;
}

// 199:
// ------------------------------------------------------------
// CR    -> OPR       0   UNC      5      
// ------------------------------------------------------------
case 375:
{
    word_size_ = true;
    opr() = (microcode_pointer_ & 0xf);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
    state_ = stateSingleCycleWait;
    break;
}

// 19a:
// ------------------------------------------------------------
// ZERO  -> IND       6   IRQ   D0,P0     
// ------------------------------------------------------------
case 376:
{
    ind() = 0;
    mc_bus(false, true, false, 1, 3);
    break;
}

// 19b:
// ------------------------------------------------------------
//                    4   none  SUSP      
// ------------------------------------------------------------
case 377:
{
    suspendPrefetch();
    break;
}

// 19c: 100000000.01
// Opcodes: none
// ------------------------------------------------------------
//                    6   IRQ   D0,P0     
// ------------------------------------------------------------
case 378:
{
    mc_bus(false, true, false, 1, 3);
    break;
}

// 19d:
// ------------------------------------------------------------
// OPR   -> tmpbL     4   none  SUSP      
// ------------------------------------------------------------
case 379:
{
    const uint32_t value = opr();
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    suspendPrefetch();
    break;
}

// 19e:
// ------------------------------------------------------------
// ZERO  -> tmpbH     1   ADD   tmpb      
// ------------------------------------------------------------
case 41:
{
    tmpb() = (tmpb() & 0xff) | (0 << 8);
    alu_ = AluOp::ADD;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 19f:
// ------------------------------------------------------------
// SIGMA -> tmpb                          
// ------------------------------------------------------------
case 380:
{
    const uint32_t sigma = doALUFixed<AluOp::ADD, AluInput::TmpB>();
    tmpb() = sigma;
    break;
}

// 1a0: 100000000.10
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> IND       6   R     D0,P2     
// ------------------------------------------------------------
case 381:
{
    const uint32_t sigma = doALUFixed<AluOp::ADD, AluInput::TmpB>();
    ind() = sigma;
    mc_bus(false, false, false, 1, 0);
    break;
}

// 1a1:
// ------------------------------------------------------------
// OPR   -> tmpb      1   DEC2  tmpc      
// ------------------------------------------------------------
case 382:
{
    tmpb() = opr();
    alu_ = AluOp::DEC2;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1a2:
// ------------------------------------------------------------
// SP    -> tmpc      6   R     D0,P0     
// ------------------------------------------------------------
case 383:
{
    registers_[14] = rw(4);
    mc_bus(false, false, false, 1, 3);
    break;
}

// 1a3:
// ------------------------------------------------------------
// OPR   -> tmpa                          
// ------------------------------------------------------------
case 384:
{
    tmpa() = opr();
    break;
}

// 1a4: 100000000.11
// Opcodes: none
// ------------------------------------------------------------
// F     -> OPR       4   CITF  none      
// ------------------------------------------------------------
case 385:
{
    opr() = flags();
    flags() &= ~0x300;
    break;
}

// 1a5:
// ------------------------------------------------------------
// SIGMA -> IND       6   w     DS,P0     
// ------------------------------------------------------------
case 386:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC2, AluInput::TmpC>();
    ind() = sigma;
    mc_bus(true, false, false, 2, 3);
    break;
}

// 1a6:
// ------------------------------------------------------------
// IND   -> tmpc      5   UNC   FARCALL2  
// ------------------------------------------------------------
case 387:
{
    registers_[14] = ind();
    skip_rni_ = false;
    microcode_pointer_ = 0x1fb4; // FARCALL2
    state_ = stateSingleCycleWait;
    break;
}

// 1a7:
// ------------------------------------------------------------
// CR    -> OPR       0   UNC      5      
// ------------------------------------------------------------
case 388:
{
    word_size_ = true;
    opr() = (microcode_pointer_ & 0xf);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
    state_ = stateSingleCycleWait;
    break;
}

// 1a8: 011001101.00
// Opcodes: CD
// ------------------------------------------------------------
// Q     -> tmpb                          
// ------------------------------------------------------------
case 389:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = queueRead(QueueReadState::SubsequentByte);
    break;
}

// 1a9:
// ------------------------------------------------------------
// tmpb  -> OPR       5   UNC   INTR      
// ------------------------------------------------------------
case 390:
{
    opr() = tmpb();
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

// 1ac: 011001110.00
// Opcodes: CE
// ------------------------------------------------------------
//                                        
// ------------------------------------------------------------
case 42:
{
    break;
}

// 1ad:
// ------------------------------------------------------------
//                    0   OF       3      
// ------------------------------------------------------------
case 391:
{
    if ((flags() & 0x800) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x3;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1ae:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 392:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1af:
// ------------------------------------------------------------
// CR    -> OPR       5   UNC   INTR      
// ------------------------------------------------------------
case 393:
{
    word_size_ = true;
    opr() = (microcode_pointer_ & 0xf);
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

// 1b0: 011001100.00
// Opcodes: CC
// ------------------------------------------------------------
//                    0   UNC      2      
// ------------------------------------------------------------
case 394:
{
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x2;
    state_ = stateSingleCycleWait;
    break;
}

// 1b1:
// ------------------------------------------------------------
//                                        
// ------------------------------------------------------------
case 395:
{
    break;
}

// 1b2:
// ------------------------------------------------------------
// CR    -> OPR       5   UNC   INTR      
// ------------------------------------------------------------
case 396:
{
    word_size_ = true;
    opr() = (microcode_pointer_ & 0xf);
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

// 1b4: 100100011.00
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> no dest                       
// ------------------------------------------------------------
case 43:
{
    doALU();
    break;
}

// 1b5:
// ------------------------------------------------------------
//                    0   NCY      7      
// ------------------------------------------------------------
case 397:
{
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1b6:
// ------------------------------------------------------------
//                    1   NEG   tmpc      
// ------------------------------------------------------------
case 44:
{
    alu_ = AluOp::NEG;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1b7:
// ------------------------------------------------------------
// SIGMA -> tmpc      1   COM1  tmpa     F
// ------------------------------------------------------------
case 398:
{
    const uint32_t sigma = doALUFixed<AluOp::NEG, AluInput::TmpC>();
    updateFlags();
    registers_[14] = sigma;
    alu_ = AluOp::COM1;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 1b8: 100100011.01
// Opcodes: none
// ------------------------------------------------------------
//                    0   CY       6      
// ------------------------------------------------------------
case 399:
{
    if (getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x6;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1b9:
// ------------------------------------------------------------
//                    1   NEG   tmpa      
// ------------------------------------------------------------
case 400:
{
    alu_ = AluOp::NEG;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 1ba:
// ------------------------------------------------------------
// SIGMA -> tmpa      4   CF1   none      
// ------------------------------------------------------------
case 401:
{
    const uint32_t sigma = doALU();
    tmpa() = sigma;
    f1_ = !f1_;
    break;
}

// 1bb:
// ------------------------------------------------------------
//                    1   LRCY  tmpb      
// ------------------------------------------------------------
case 45:
{
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 1bc: 100100011.10
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> no dest   1   NEG   tmpb      
// ------------------------------------------------------------
case 402:
{
    doALUFixed<AluOp::LRCY, AluInput::TmpB>();
    alu_ = AluOp::NEG;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 1bd:
// ------------------------------------------------------------
//                    0   NCY     11      
// ------------------------------------------------------------
case 403:
{
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xb;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1be:
// ------------------------------------------------------------
// SIGMA -> tmpb      4   CF1   RTN       
// ------------------------------------------------------------
case 404:
{
    const uint32_t sigma = doALUFixed<AluOp::NEG, AluInput::TmpB>();
    tmpb() = sigma;
    f1_ = !f1_;
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 1bf:
// ------------------------------------------------------------
//                    4   none  RTN       
// ------------------------------------------------------------
case 405:
{
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 1c0: 100100011.11
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> no dest   1   NEG   tmpc      
// ------------------------------------------------------------
case 46:
{
    doALU();
    alu_ = AluOp::NEG;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1c1:
// ------------------------------------------------------------
//                    0   NCY      7      
// ------------------------------------------------------------
case 406:
{
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1c2:
// ------------------------------------------------------------
// SIGMA -> tmpc      4   CF1   none      
// ------------------------------------------------------------
case 47:
{
    const uint32_t sigma = doALUFixed<AluOp::NEG, AluInput::TmpC>();
    registers_[14] = sigma;
    f1_ = !f1_;
    break;
}

// 1c3:
// ------------------------------------------------------------
//                    0   UNC      7      
// ------------------------------------------------------------
case 407:
{
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x7;
    state_ = stateSingleCycleWait;
    break;
}

// 1c4: 100100100.00
// Opcodes: none
// ------------------------------------------------------------
//                    5   NCY   INT0      
// ------------------------------------------------------------
case 408:
{
    if (!getAluCF()) {
        skip_rni_ = false;
        microcode_pointer_ = 0x100f; // INT0
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1c5:
// ------------------------------------------------------------
//                    1   LRCY  tmpb      
// ------------------------------------------------------------
case 48:
{
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpB;
    break;
}

// 1c6:
// ------------------------------------------------------------
// SIGMA -> no dest   1   NEG   tmpa      
// ------------------------------------------------------------
case 409:
{
    doALUFixed<AluOp::LRCY, AluInput::TmpB>();
    alu_ = AluOp::NEG;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 1c7:
// ------------------------------------------------------------
//                    0   NCY      5      
// ------------------------------------------------------------
case 410:
{
    if (!getAluCF()) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1c8: 100100100.01
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> tmpa                          
// ------------------------------------------------------------
case 411:
{
    const uint32_t sigma = doALUFixed<AluOp::NEG, AluInput::TmpA>();
    tmpa() = sigma;
    break;
}

// 1c9:
// ------------------------------------------------------------
//                    1   INC   tmpc      
// ------------------------------------------------------------
case 49:
{
    alu_ = AluOp::INC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1ca:
// ------------------------------------------------------------
//                    0   F1       8      
// ------------------------------------------------------------
case 412:
{
    if (f1_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x8;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1cb:
// ------------------------------------------------------------
//                    1   COM1  tmpc      
// ------------------------------------------------------------
case 413:
{
    alu_ = AluOp::COM1;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1cc: 100100100.10
// Opcodes: none
// ------------------------------------------------------------
//                    4   CCOF  RTN       
// ------------------------------------------------------------
case 414:
{
    setInternalCarry(false);
    flags() &= ~0x801;
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 1cd:
// ------------------------------------------------------------
// ZERO  -> tmpb      1   LRCY  tmpc      
// ------------------------------------------------------------
case 50:
{
    tmpb() = 0;
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1ce:
// ------------------------------------------------------------
// SIGMA -> no dest   1   ADC   tmpa      
// ------------------------------------------------------------
case 415:
{
    doALUFixed<AluOp::LRCY, AluInput::TmpC>();
    alu_ = AluOp::ADC;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 1cf:
// ------------------------------------------------------------
// SIGMA -> no dest                      F
// ------------------------------------------------------------
case 416:
{
    doALUFixed<AluOp::ADC, AluInput::TmpA>();
    updateFlags();
    break;
}

// 1d0: 100100100.11
// Opcodes: none
// ------------------------------------------------------------
//                    0   Z        8      
// ------------------------------------------------------------
case 417:
{
    if ((flags() & 0x40) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x8;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1d1:
// ------------------------------------------------------------
//                    4   SCOF  RTN       
// ------------------------------------------------------------
case 418:
{
    setInternalCarry(true);
    flags() |= 0x801;
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 1d2:
// ------------------------------------------------------------
//                    1   PASS  tmpa      
// ------------------------------------------------------------
case 51:
{
    alu_ = AluOp::PASS;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpA;
    break;
}

// 1d3:
// ------------------------------------------------------------
// SIGMA -> no dest   0   UNC     12     F
// ------------------------------------------------------------
case 419:
{
    doALUFixed<AluOp::PASS, AluInput::TmpA>();
    updateFlags();
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xc;
    state_ = stateSingleCycleWait;
    break;
}

// 1d4: 101000000.00
// Opcodes: none
// ------------------------------------------------------------
// HL    -> tmpa                          
// ------------------------------------------------------------
case 420:
{
    tmpa() = rw(3);
    break;
}

// 1d5:
// ------------------------------------------------------------
// IJ    -> tmpb                          
// ------------------------------------------------------------
case 52:
{
    tmpb() = rw(6);
    break;
}

// 1d6:
// ------------------------------------------------------------
// SIGMA -> tmpa      5   UNC   EAOFFSET  
// ------------------------------------------------------------
case 421:
{
    const uint32_t sigma = doALU();
    tmpa() = sigma;
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? ((mod_rm_ & 0xc0) == 0 ? 0x140d : 0x140a) : ((mod_rm_ & 0xc0) == 0 ? 0x140f : 0x140a)); // EAOFFSET
    state_ = stateSingleCycleWait;
    break;
}

// 1d7:
// ------------------------------------------------------------
// MP    -> tmpa                          
// ------------------------------------------------------------
case 422:
{
    tmpa() = rw(5);
    break;
}

// 1d8: 101000000.01
// Opcodes: none
// ------------------------------------------------------------
// IK    -> tmpb                          
// ------------------------------------------------------------
case 53:
{
    tmpb() = rw(7);
    break;
}

// 1d9:
// ------------------------------------------------------------
// SIGMA -> tmpa      5   UNC   EAOFFSET  
// ------------------------------------------------------------
case 423:
{
    const uint32_t sigma = doALU();
    tmpa() = sigma;
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? ((mod_rm_ & 0xc0) == 0 ? 0x140d : 0x140a) : ((mod_rm_ & 0xc0) == 0 ? 0x140f : 0x140a)); // EAOFFSET
    state_ = stateSingleCycleWait;
    break;
}

// 1da:
// ------------------------------------------------------------
// HL    -> tmpa      0   UNC      4      
// ------------------------------------------------------------
case 424:
{
    tmpa() = rw(3);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x4;
    state_ = stateSingleCycleWait;
    break;
}

// 1db:
// ------------------------------------------------------------
// MP    -> tmpa      0   UNC      1      
// ------------------------------------------------------------
case 425:
{
    tmpa() = rw(5);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x1;
    state_ = stateSingleCycleWait;
    break;
}

// 1dc: 101000000.10
// Opcodes: none
// ------------------------------------------------------------
// Q     -> tmpaL                         
// ------------------------------------------------------------
case 426:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff00) | (queueRead(QueueReadState::SubsequentByte) & 0xff);
    break;
}

// 1dd:
// ------------------------------------------------------------
// Q     -> tmpaH     5   UNC   EAFINISH  
// ------------------------------------------------------------
case 427:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpa() = (tmpa() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? 0x140d : 0x140f); // EAFINISH
    state_ = stateSingleCycleWait;
    break;
}

// 1de:
// ------------------------------------------------------------
// Q     -> tmpbL     0   MOD1    12      
// ------------------------------------------------------------
case 428:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    if ((mod_rm_ & 0x40) != 0) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0xc;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1df:
// ------------------------------------------------------------
// Q     -> tmpbH                         
// ------------------------------------------------------------
case 429:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    tmpb() = (tmpb() & 0xff) | (queueRead(QueueReadState::SubsequentByte) << 8);
    break;
}

// 1e0: 101000000.11
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> tmpa      5   UNC   EAFINISH  
// ------------------------------------------------------------
case 430:
{
    const uint32_t sigma = doALU();
    tmpa() = sigma;
    skip_rni_ = false;
    microcode_pointer_ = ((group_ & groupInitialEARead) != 0 ? 0x140d : 0x140f); // EAFINISH
    state_ = stateSingleCycleWait;
    break;
}

// 1e1:
// ------------------------------------------------------------
// tmpa  -> IND       6   R     DD,P0     
// ------------------------------------------------------------
case 431:
{
    ind() = tmpa();
    mc_bus(false, false, false, 3, 3);
    break;
}

// 1e2:
// ------------------------------------------------------------
// OPR   -> tmpb      4   none  RTN       
// ------------------------------------------------------------
case 432:
{
    tmpb() = opr();
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 1e3:
// ------------------------------------------------------------
// tmpa  -> IND       4   none  RTN       
// ------------------------------------------------------------
case 433:
{
    ind() = tmpa();
    flags() = (flags() & ~1) | unsigned(getAluCF());
    microcode_pointer_ = microcode_return_;
    state_ = stateSingleCycleWait;
    break;
}

// 1e4: 110000000.00
// Opcodes: none
// ------------------------------------------------------------
// ZERO  -> RD        4   none  SUSP      
// ------------------------------------------------------------
case 434:
{
    sr(3) = 0;
    suspendPrefetch();
    break;
}

// 1e5:
// ------------------------------------------------------------
// ONES  -> RC                            
// ------------------------------------------------------------
case 435:
{
    sr(1) = 0xffff;
    break;
}

// 1e6:
// ------------------------------------------------------------
// ZERO  -> PC        4   FLUSH none      
// ------------------------------------------------------------
case 436:
{
    pc() = 0;
    flushQueue();
    break;
}

// 1e7:
// ------------------------------------------------------------
// ZERO  -> F                             
// ------------------------------------------------------------
case 54:
{
    flags() = (0 & 0xffd5) | 0xf002;
    break;
}

// 1e8: 110000000.01
// Opcodes: none
// ------------------------------------------------------------
// ZERO  -> RA                            
// ------------------------------------------------------------
case 437:
{
    sr(0) = 0;
    break;
}

// 1e9:
// ------------------------------------------------------------
// ZERO  -> RS        4   none  RNI       
// ------------------------------------------------------------
case 438:
{
    sr(2) = 0;
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1ec: 010011011.10
// Opcodes: none
// ------------------------------------------------------------
// SIGMA -> PC        4   FLUSH RNI       
// ------------------------------------------------------------
case 439:
{
    const uint32_t sigma = doALUFixed<AluOp::DEC, AluInput::TmpC>();
    pc() = sigma;
    flushQueue();
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1f0: 01010101?.01
// Opcodes: none
// ------------------------------------------------------------
// tmpc  -> BC        0   NZ       1      
// ------------------------------------------------------------
case 440:
{
    rw(1) = registers_[14];
    if (!super_zero_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x1;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1f1:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 441:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1f4: 01010?11?.11
// Opcodes: none
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 442:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1f8: 01010?10?.10
// Opcodes: none
// ------------------------------------------------------------
// OPR   -> M         0   F1       5      
// ------------------------------------------------------------
case 443:
{
    mc_write_m(opr());
    if (f1_) {
        microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x5;
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1f9:
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 444:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1fa:
// ------------------------------------------------------------
// IND   -> tmpaL     1   LRCY  tmpc     F
// ------------------------------------------------------------
case 445:
{
    tmpa() = (tmpa() & 0xff00) | (ind() & 0xff);
    alu_ = AluOp::LRCY;
    carry_latch_ = true;
    nx_ = false;
    alu_input_ = AluInput::TmpC;
    break;
}

// 1fc: 011100011.01
// Opcodes: none
// ------------------------------------------------------------
//                    4   none  RNI       
// ------------------------------------------------------------
case 446:
{
    if (!skip_rni_) {
        rni_ = true;
        in_instruction_ = false;
    }
    break;
}

// 1fe:
// ------------------------------------------------------------
// A     -> tmpa      5   INT   FARCALL2  
// ------------------------------------------------------------
case 447:
{
    tmpa() = rb(0);
    if (interrupt_pending_) {
        skip_rni_ = false;
        microcode_pointer_ = 0x1fb4; // FARCALL2
        state_ = stateSingleCycleWait;
    }
    break;
}

// 1ff:
// ------------------------------------------------------------
// B     -> E         5   UNC   INTR     F
// ------------------------------------------------------------
case 448:
{
    rb(2) = static_cast<uint8_t>(rb(5));
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

// 198: 100000000.00
// Opcodes: none
// ------------------------------------------------------------
// CR    -> tmpbL     0   UNC      6      
// ------------------------------------------------------------
case 449:
{
    word_size_ = true;
    const uint32_t value = (microcode_pointer_ & 0xf);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x6;
    state_ = stateSingleCycleWait;
    break;
}

// 199:
// ------------------------------------------------------------
// CR    -> tmpbL     0   UNC      6      
// ------------------------------------------------------------
case 450:
{
    word_size_ = true;
    const uint32_t value = (microcode_pointer_ & 0xf);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x6;
    state_ = stateSingleCycleWait;
    break;
}

// 19a:
// ------------------------------------------------------------
// XA    -> tmpc      6   IRQ   D0,P0     
// ------------------------------------------------------------
case 451:
{
    registers_[14] = rw(0);
    mc_bus(false, true, false, 1, 3);
    break;
}

// 19b:
// ------------------------------------------------------------
// OPR   -> XA        4   none  SUSP      
// ------------------------------------------------------------
case 452:
{
    rw(0) = opr();
    suspendPrefetch();
    break;
}

// 19c: 100000000.01
// Opcodes: none
// ------------------------------------------------------------
// X     -> tmpbL                         
// ------------------------------------------------------------
case 55:
{
    const uint32_t value = rb(4);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    break;
}

// 19d:
// ------------------------------------------------------------
// tmpc  -> XA                            
// ------------------------------------------------------------
case 453:
{
    rw(0) = registers_[14];
    break;
}

// 1a3:
// ------------------------------------------------------------
// OPR   -> tmpa      4   none  SUSP      
// ------------------------------------------------------------
case 454:
{
    tmpa() = opr();
    suspendPrefetch();
    break;
}

// 1a7:
// ------------------------------------------------------------
// CR    -> tmpbL     0   UNC      6      
// ------------------------------------------------------------
case 455:
{
    word_size_ = true;
    const uint32_t value = (microcode_pointer_ & 0xf);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    microcode_pointer_ = (microcode_pointer_ & 0x1ff0) | 0x6;
    state_ = stateSingleCycleWait;
    break;
}

// 1a8: 011001101.00
// Opcodes: CD
// ------------------------------------------------------------
// Q     -> tmpbL     5   UNC   INTR      
// ------------------------------------------------------------
case 456:
{
    if (queue_bytes_ == 0) {
        state_ = stateWaitingForQueueData;
        goto microcodeDone;
    }
    const uint32_t value = queueRead(QueueReadState::SubsequentByte);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

// 1af:
// ------------------------------------------------------------
// CR    -> tmpbL     5   UNC   INTR      
// ------------------------------------------------------------
case 457:
{
    word_size_ = true;
    const uint32_t value = (microcode_pointer_ & 0xf);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

// 1b2:
// ------------------------------------------------------------
// CR    -> tmpbL     5   UNC   INTR      
// ------------------------------------------------------------
case 458:
{
    word_size_ = true;
    const uint32_t value = (microcode_pointer_ & 0xf);
    tmpb() = ((value & 0x80) != 0 ? 0xff00 : 0) | (value & 0xff);
    skip_rni_ = false;
    microcode_pointer_ = intr_entry_; // INTR
    state_ = stateSingleCycleWait;
    break;
}

default: assert(false && "invalid generated microcode word"); break;
}
microcodeDone:;

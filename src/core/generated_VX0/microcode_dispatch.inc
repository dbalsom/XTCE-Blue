// Generated from NEC microcode. Do not edit.

// Word: 000 (ROM line 000)
// Match: 00?.00???0??.0000
// Native Opcodes: 00-03, 08-0B, 10-13, 18-1B, 20-23, 28-2B, 30-33, 38-3B
// -------------------------------------------------------------------------
// OP1 -> tmpB     OP2 -> tmpA    ---  ALU XI, tmpA
// -------------------------------------------------------------------------
case 0x0000:
case 0x0010:
case 0x0020:
case 0x0030:
case 0x0080:
case 0x0090:
case 0x00a0:
case 0x00b0:
case 0x0100:
case 0x0110:
case 0x0120:
case 0x0130:
case 0x0180:
case 0x0190:
case 0x01a0:
case 0x01b0:
case 0x0200:
case 0x0210:
case 0x0220:
case 0x0230:
case 0x0280:
case 0x0290:
case 0x02a0:
case 0x02b0:
case 0x0300:
case 0x0310:
case 0x0320:
case 0x0330:
case 0x0380:
case 0x0390:
case 0x03a0:
case 0x03b0:
case 0x1000:
case 0x1010:
case 0x1020:
case 0x1030:
case 0x1080:
case 0x1090:
case 0x10a0:
case 0x10b0:
case 0x1100:
case 0x1110:
case 0x1120:
case 0x1130:
case 0x1180:
case 0x1190:
case 0x11a0:
case 0x11b0:
case 0x1200:
case 0x1210:
case 0x1220:
case 0x1230:
case 0x1280:
case 0x1290:
case 0x12a0:
case 0x12b0:
case 0x1300:
case 0x1310:
case 0x1320:
case 0x1330:
case 0x1380:
case 0x1390:
case 0x13a0:
case 0x13b0:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = readOperand(op2);
    r[TB] = a;
    r[TA] = b;
    setupDecodedAlu<false, false>(TA);
    break;
}

// Word: 001 (ROM line 001)
// Match: 00?.00???0??.0001
// Native Opcodes: 00-03, 08-0B, 10-13, 18-1B, 20-23, 28-2B, 30-33, 38-3B
// -------------------------------------------------------------------------
// SIGMA -> OP1                   -WE  EC=COMMIT
// -------------------------------------------------------------------------
case 0x0001:
case 0x0011:
case 0x0021:
case 0x0031:
case 0x0081:
case 0x0091:
case 0x00a1:
case 0x00b1:
case 0x0101:
case 0x0111:
case 0x0121:
case 0x0131:
case 0x0181:
case 0x0191:
case 0x01a1:
case 0x01b1:
case 0x0201:
case 0x0211:
case 0x0221:
case 0x0231:
case 0x0281:
case 0x0291:
case 0x02a1:
case 0x02b1:
case 0x0301:
case 0x0311:
case 0x0321:
case 0x0331:
case 0x0381:
case 0x0391:
case 0x03a1:
case 0x03b1:
case 0x1001:
case 0x1011:
case 0x1021:
case 0x1031:
case 0x1081:
case 0x1091:
case 0x10a1:
case 0x10b1:
case 0x1101:
case 0x1111:
case 0x1121:
case 0x1131:
case 0x1181:
case 0x1191:
case 0x11a1:
case 0x11b1:
case 0x1201:
case 0x1211:
case 0x1221:
case 0x1231:
case 0x1281:
case 0x1291:
case 0x12a1:
case 0x12b1:
case 0x1301:
case 0x1311:
case 0x1321:
case 0x1331:
case 0x1381:
case 0x1391:
case 0x13a1:
case 0x13b1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitAluFlags();
    commitOperand();
    endRequested = true;
    break;
}

// Word: 004 (ROM line 004)
// Match: 00?.00???10?.0000
// Native Opcodes: 04-05, 0C-0D, 14-15, 1C-1D, 24-25, 2C-2D, 34-35, 3C-3D
// -------------------------------------------------------------------------
// OP1 -> tmpB     Q -> tmpA      ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x0040:
case 0x0050:
case 0x00c0:
case 0x00d0:
case 0x0140:
case 0x0150:
case 0x01c0:
case 0x01d0:
case 0x0240:
case 0x0250:
case 0x02c0:
case 0x02d0:
case 0x0340:
case 0x0350:
case 0x03c0:
case 0x03d0:
case 0x1040:
case 0x1050:
case 0x10c0:
case 0x10d0:
case 0x1140:
case 0x1150:
case 0x11c0:
case 0x11d0:
case 0x1240:
case 0x1250:
case 0x12c0:
case 0x12d0:
case 0x1340:
case 0x1350:
case 0x13c0:
case 0x13d0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readOperand(op1);
    const uint16_t b = readPrefetchForMicrocode();
    r[TB] = a;
    r[TA] = b;
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 005 (ROM line 005)
// Match: 00?.00???10?.0001
// Native Opcodes: 04-05, 0C-0D, 14-15, 1C-1D, 24-25, 2C-2D, 34-35, 3C-3D
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x0041:
case 0x0051:
case 0x00c1:
case 0x00d1:
case 0x0141:
case 0x0151:
case 0x01c1:
case 0x01d1:
case 0x0241:
case 0x0251:
case 0x02c1:
case 0x02d1:
case 0x0341:
case 0x0351:
case 0x03c1:
case 0x03d1:
case 0x1041:
case 0x1051:
case 0x10c1:
case 0x10d1:
case 0x1141:
case 0x1151:
case 0x11c1:
case 0x11d1:
case 0x1241:
case 0x1251:
case 0x12c1:
case 0x12d1:
case 0x1341:
case 0x1351:
case 0x13c1:
case 0x13d1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 006 (ROM line 006)
// Match: 00?.00???10?.0010
// Native Opcodes: 04-05, 0C-0D, 14-15, 1C-1D, 24-25, 2C-2D, 34-35, 3C-3D
// -------------------------------------------------------------------------
//                                --E  ALU XI, tmpA
// -------------------------------------------------------------------------
case 0x0042:
case 0x0052:
case 0x00c2:
case 0x00d2:
case 0x0142:
case 0x0152:
case 0x01c2:
case 0x01d2:
case 0x0242:
case 0x0252:
case 0x02c2:
case 0x02d2:
case 0x0342:
case 0x0352:
case 0x03c2:
case 0x03d2:
case 0x1042:
case 0x1052:
case 0x10c2:
case 0x10d2:
case 0x1142:
case 0x1152:
case 0x11c2:
case 0x11d2:
case 0x1242:
case 0x1252:
case 0x12c2:
case 0x12d2:
case 0x1342:
case 0x1352:
case 0x13c2:
case 0x13d2:
{
    setupDecodedAlu<false, false>(TA);
    endRequested = true;
    break;
}

// Word: 007 (ROM line 007)
// Match: 00?.00???10?.0011
// Native Opcodes: 04-05, 0C-0D, 14-15, 1C-1D, 24-25, 2C-2D, 34-35, 3C-3D
// -------------------------------------------------------------------------
// SIGMA -> OP1                   -W-  --
// -------------------------------------------------------------------------
case 0x0043:
case 0x0053:
case 0x00c3:
case 0x00d3:
case 0x0143:
case 0x0153:
case 0x01c3:
case 0x01d3:
case 0x0243:
case 0x0253:
case 0x02c3:
case 0x02d3:
case 0x0343:
case 0x0353:
case 0x03c3:
case 0x03d3:
case 0x1043:
case 0x1053:
case 0x10c3:
case 0x10d3:
case 0x1143:
case 0x1153:
case 0x11c3:
case 0x11d3:
case 0x1243:
case 0x1253:
case 0x12c3:
case 0x12d3:
case 0x1343:
case 0x1353:
case 0x13c3:
case 0x13d3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitAluFlags();
    break;
}

// Word: 00C (ROM line 00C)
// Match: 00?.000??110.0000
// Native Opcodes: 06, 0E, 16, 1E
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x0060:
case 0x00e0:
case 0x0160:
case 0x01e0:
case 0x1060:
case 0x10e0:
case 0x1160:
case 0x11e0:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 00D (ROM line 00D)
// Match: 00?.000??110.0001
// Native Opcodes: 06, 0E, 16, 1E
// -------------------------------------------------------------------------
// OP2 -> OPR      SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x0061:
case 0x00e1:
case 0x0161:
case 0x01e1:
case 0x1061:
case 0x10e1:
case 0x1161:
case 0x11e1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOperand(op2);
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 00E (ROM line 00E)
// Match: 00?.000??110.0010
// Native Opcodes: 06, 0E, 16, 1E
// -------------------------------------------------------------------------
// SIGMA -> SP                    --E  --
// -------------------------------------------------------------------------
case 0x0062:
case 0x00e2:
case 0x0162:
case 0x01e2:
case 0x1062:
case 0x10e2:
case 0x1162:
case 0x11e2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    endRequested = true;
    break;
}

// Word: 008 (ROM line 008)
// Match: 00?.000??111.0000
// Native Opcodes: 07, 17, 1F
// -------------------------------------------------------------------------
// SP -> DP                       ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0070:
case 0x00f0:
case 0x0170:
case 0x01f0:
case 0x1070:
case 0x10f0:
case 0x1170:
case 0x11f0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    writeIndex(a);
    requestRead(Segment::SS);
    break;
}

// Word: 009 (ROM line 009)
// Match: 00?.000??111.0001
// Native Opcodes: 07, 17, 1F
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x0071:
case 0x00f1:
case 0x0171:
case 0x01f1:
case 0x1071:
case 0x10f1:
case 0x1171:
case 0x11f1:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 00A (ROM line 00A)
// Match: 00?.000??111.0010
// Native Opcodes: 07, 17, 1F
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x0072:
case 0x00f2:
case 0x0172:
case 0x01f2:
case 0x1072:
case 0x10f2:
case 0x1172:
case 0x11f2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 00B (ROM line 00B)
// Match: 00?.000??111.0011
// Native Opcodes: 07, 17, 1F
// -------------------------------------------------------------------------
// OPR -> OP2                     F-E  --
// -------------------------------------------------------------------------
case 0x0073:
case 0x00f3:
case 0x0173:
case 0x01f3:
case 0x1073:
case 0x10f3:
case 0x1173:
case 0x11f3:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op2, a);
    endRequested = true;
    break;
}

// Word: 010 (ROM line 010)
// Match: 00?.00100111.0000
// Native Opcodes: 27
// -------------------------------------------------------------------------
// A -> tmpBL                     ---  ALU ADJD, tmpB
// -------------------------------------------------------------------------
case 0x0270:
case 0x1270:
{
    const uint16_t a = r[AX];
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::AdjustDecimal, TB);
    break;
}

// Word: 011 (ROM line 011)
// Match: 00?.00100111.0001
// Native Opcodes: 27
// -------------------------------------------------------------------------
// K -> tmpA                      --E  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0271:
case 0x1271:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Add, TA);
    endRequested = true;
    break;
}

// Word: 012 (ROM line 012)
// Match: 00?.00100111.0010
// Native Opcodes: 27
// -------------------------------------------------------------------------
// SIGMA -> AL     SIGMA -> NULL  -W-  --
// -------------------------------------------------------------------------
case 0x0272:
case 0x1272:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeByteReg(0, a);
    (void)b;
    commitAluFlags();
    break;
}

// Word: 014 (ROM line 014)
// Match: 00?.00101111.0000
// Native Opcodes: 2F
// -------------------------------------------------------------------------
// A -> tmpBL                     ---  ALU ADJD, tmpB
// -------------------------------------------------------------------------
case 0x02f0:
case 0x12f0:
{
    const uint16_t a = r[AX];
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::AdjustDecimal, TB);
    break;
}

// Word: 015 (ROM line 015)
// Match: 00?.00101111.0001
// Native Opcodes: 2F
// -------------------------------------------------------------------------
// K -> tmpA                      --E  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x02f1:
case 0x12f1:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    endRequested = true;
    break;
}

// Word: 016 (ROM line 016)
// Match: 00?.00101111.0010
// Native Opcodes: 2F
// -------------------------------------------------------------------------
// SIGMA -> AL     SIGMA -> NULL  -W-  --
// -------------------------------------------------------------------------
case 0x02f2:
case 0x12f2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeByteReg(0, a);
    (void)b;
    commitAluFlags();
    break;
}

// Word: 018 (ROM line 018)
// Match: 00?.00110111.0000
// Native Opcodes: 37
// -------------------------------------------------------------------------
// A -> tmpBL                     ---  ALU ADJA, tmpB
// -------------------------------------------------------------------------
case 0x0370:
case 0x1370:
{
    const uint16_t a = r[AX];
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::AdjustAscii, TB);
    break;
}

// Word: 019 (ROM line 019)
// Match: 00?.00110111.0001
// Native Opcodes: 37
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0371:
case 0x1371:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 01A (ROM line 01A)
// Match: 00?.00110111.0010
// Native Opcodes: 37
// -------------------------------------------------------------------------
// SIGMA -> AL     SIGMA -> NULL  -W-  ALU INC, tmpB
// -------------------------------------------------------------------------
case 0x0372:
case 0x1372:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeByteReg(0, a);
    (void)b;
    commitAluFlags();
    setupAlu<false, true>(Alu::Inc, TB);
    break;
}

// Word: 01B (ROM line 01B)
// Match: 00?.00110111.0011
// Native Opcodes: 37
// -------------------------------------------------------------------------
// AL:AH -> tmpB                  ---  JUMP JNC, 05
// -------------------------------------------------------------------------
case 0x0373:
case 0x1373:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = a;
    if (!aluCarry()) {
        jumpLocal(5);
    }
    break;
}

// Word: 01C (ROM line 01C)
// Match: 00?.0011?111.0100
// Native Opcodes: 37, 3F
// -------------------------------------------------------------------------
// SIGMA -> AH                    ---  --
// -------------------------------------------------------------------------
case 0x0374:
case 0x03f4:
case 0x1374:
case 0x13f4:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(4, a);
    break;
}

// Word: 01D (ROM line 01D)
// Match: 00?.0011?111.0101
// Native Opcodes: 37, 3F
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0375:
case 0x03f5:
case 0x1375:
case 0x13f5:
{
    endRequested = true;
    break;
}

// Word: 020 (ROM line 020)
// Match: 00?.00111111.0000
// Native Opcodes: 3F
// -------------------------------------------------------------------------
// A -> tmpBL                     ---  ALU ADJA, tmpB
// -------------------------------------------------------------------------
case 0x03f0:
case 0x13f0:
{
    const uint16_t a = r[AX];
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::AdjustAscii, TB);
    break;
}

// Word: 021 (ROM line 021)
// Match: 00?.00111111.0001
// Native Opcodes: 3F
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x03f1:
case 0x13f1:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 022 (ROM line 022)
// Match: 00?.00111111.0010
// Native Opcodes: 3F
// -------------------------------------------------------------------------
// SIGMA -> AL     SIGMA -> NULL  -W-  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x03f2:
case 0x13f2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeByteReg(0, a);
    (void)b;
    commitAluFlags();
    setupAlu<false, true>(Alu::Dec, TB);
    break;
}

// Word: 023 (ROM line 023)
// Match: 00?.00111111.0011
// Native Opcodes: 3F
// -------------------------------------------------------------------------
// AL:AH -> tmpB                  ---  JUMP JNC, 05
// -------------------------------------------------------------------------
case 0x03f3:
case 0x13f3:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = a;
    if (!aluCarry()) {
        jumpLocal(5);
    }
    break;
}

// Word: 024 (ROM line 024)
// Match: 00?.0100????.0000
// Native Opcodes: 40-4F
// -------------------------------------------------------------------------
// OP1 -> tmpB                    --E  ALU XI, tmpB
// -------------------------------------------------------------------------
case 0x0400:
case 0x0410:
case 0x0420:
case 0x0430:
case 0x0440:
case 0x0450:
case 0x0460:
case 0x0470:
case 0x0480:
case 0x0490:
case 0x04a0:
case 0x04b0:
case 0x04c0:
case 0x04d0:
case 0x04e0:
case 0x04f0:
case 0x1400:
case 0x1410:
case 0x1420:
case 0x1430:
case 0x1440:
case 0x1450:
case 0x1460:
case 0x1470:
case 0x1480:
case 0x1490:
case 0x14a0:
case 0x14b0:
case 0x14c0:
case 0x14d0:
case 0x14e0:
case 0x14f0:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupDecodedAlu<false, false>(TB);
    endRequested = true;
    break;
}

// Word: 025 (ROM line 025)
// Match: 00?.0100????.0001
// Native Opcodes: 40-4F
// -------------------------------------------------------------------------
// SIGMA -> OP1                   -W-  --
// -------------------------------------------------------------------------
case 0x0401:
case 0x0411:
case 0x0421:
case 0x0431:
case 0x0441:
case 0x0451:
case 0x0461:
case 0x0471:
case 0x0481:
case 0x0491:
case 0x04a1:
case 0x04b1:
case 0x04c1:
case 0x04d1:
case 0x04e1:
case 0x04f1:
case 0x1401:
case 0x1411:
case 0x1421:
case 0x1431:
case 0x1441:
case 0x1451:
case 0x1461:
case 0x1471:
case 0x1481:
case 0x1491:
case 0x14a1:
case 0x14b1:
case 0x14c1:
case 0x14d1:
case 0x14e1:
case 0x14f1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitAluFlags();
    break;
}

// Word: 028 (ROM line 028)
// Match: 00?.01010???.0000
// Native Opcodes: 50-57
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x0500:
case 0x0510:
case 0x0520:
case 0x0530:
case 0x0540:
case 0x0550:
case 0x0560:
case 0x0570:
case 0x1500:
case 0x1510:
case 0x1520:
case 0x1530:
case 0x1540:
case 0x1550:
case 0x1560:
case 0x1570:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 029 (ROM line 029)
// Match: 00?.01010???.0001
// Native Opcodes: 50-57
// -------------------------------------------------------------------------
// SIGMA -> SP     SIGMA -> IND   --E  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x0501:
case 0x0511:
case 0x0521:
case 0x0531:
case 0x0541:
case 0x0551:
case 0x0561:
case 0x0571:
case 0x1501:
case 0x1511:
case 0x1521:
case 0x1531:
case 0x1541:
case 0x1551:
case 0x1561:
case 0x1571:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SP] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    endRequested = true;
    break;
}

// Word: 02A (ROM line 02A)
// Match: 00?.01010???.0010
// Native Opcodes: 50-57
// -------------------------------------------------------------------------
// OP1 -> OPR                     ---  --
// -------------------------------------------------------------------------
case 0x0502:
case 0x0512:
case 0x0522:
case 0x0532:
case 0x0542:
case 0x0552:
case 0x0562:
case 0x0572:
case 0x1502:
case 0x1512:
case 0x1522:
case 0x1532:
case 0x1542:
case 0x1552:
case 0x1562:
case 0x1572:
{
    const uint16_t a = readOperand(op1);
    writeOpr(a);
    break;
}

// Word: 02C (ROM line 02C)
// Match: 00?.01011???.0000
// Native Opcodes: 58-5F
// -------------------------------------------------------------------------
// SP -> DP                       ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0580:
case 0x0590:
case 0x05a0:
case 0x05b0:
case 0x05c0:
case 0x05d0:
case 0x05e0:
case 0x05f0:
case 0x1580:
case 0x1590:
case 0x15a0:
case 0x15b0:
case 0x15c0:
case 0x15d0:
case 0x15e0:
case 0x15f0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    writeIndex(a);
    requestRead(Segment::SS);
    break;
}

// Word: 02D (ROM line 02D)
// Match: 00?.01011???.0001
// Native Opcodes: 58-5F
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x0581:
case 0x0591:
case 0x05a1:
case 0x05b1:
case 0x05c1:
case 0x05d1:
case 0x05e1:
case 0x05f1:
case 0x1581:
case 0x1591:
case 0x15a1:
case 0x15b1:
case 0x15c1:
case 0x15d1:
case 0x15e1:
case 0x15f1:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 02E (ROM line 02E)
// Match: 00?.01011???.0010
// Native Opcodes: 58-5F
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x0582:
case 0x0592:
case 0x05a2:
case 0x05b2:
case 0x05c2:
case 0x05d2:
case 0x05e2:
case 0x05f2:
case 0x1582:
case 0x1592:
case 0x15a2:
case 0x15b2:
case 0x15c2:
case 0x15d2:
case 0x15e2:
case 0x15f2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 02F (ROM line 02F)
// Match: 00?.01011???.0011
// Native Opcodes: 58-5F
// -------------------------------------------------------------------------
// OPR -> OP1                     F-E  --
// -------------------------------------------------------------------------
case 0x0583:
case 0x0593:
case 0x05a3:
case 0x05b3:
case 0x05c3:
case 0x05d3:
case 0x05e3:
case 0x05f3:
case 0x1583:
case 0x1593:
case 0x15a3:
case 0x15b3:
case 0x15c3:
case 0x15d3:
case 0x15e3:
case 0x15f3:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 234 (ROM line 238)
// Match: 00?.01100000.0000
// Native Opcodes: 60
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x0600:
case 0x1600:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 235 (ROM line 239)
// Match: 00?.01100000.0001
// Native Opcodes: 60
// -------------------------------------------------------------------------
// A -> OPR        SIGMA -> IND   F--  --
// -------------------------------------------------------------------------
case 0x0601:
case 0x1601:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[AX];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    break;
}

// Word: 236 (ROM line 23A)
// Match: 00?.01100000.0010
// Native Opcodes: 60
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x0602:
case 0x1602:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    requestWrite(Segment::SS);
    break;
}

// Word: 237 (ROM line 23B)
// Match: 00?.01100000.0011
// Native Opcodes: 60
// -------------------------------------------------------------------------
// C -> OPR                       F--  CALL PUSHA (0B) -> 7580 [Line 238]
// -------------------------------------------------------------------------
case 0x0603:
case 0x1603:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[CX];
    writeOpr(a);
    jumpFar(0x7580);
    break;
}

// Word: 248 (ROM line 24C)
// Match: 00?.01100001.0000
// Native Opcodes: 61
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpB     ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0610:
case 0x1610:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::SS);
    break;
}

// Word: 249 (ROM line 24D)
// Match: 00?.01100001.0001
// Native Opcodes: 61
// -------------------------------------------------------------------------
//                                ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x0611:
case 0x1611:
{
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 24A (ROM line 24E)
// Match: 00?.01100001.0010
// Native Opcodes: 61
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0612:
case 0x1612:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 24B (ROM line 24F)
// Match: 00?.01100001.0011
// Native Opcodes: 61
// -------------------------------------------------------------------------
// OPR -> DI                      F--  CALL POPA (0C) -> 7600 [Line 24C]
// -------------------------------------------------------------------------
case 0x0613:
case 0x1613:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[DI] = a;
    jumpFar(0x7600);
    break;
}

// Word: 274 (ROM line 278)
// Match: 00?.01100010.0000
// Native Opcodes: 62
// -------------------------------------------------------------------------
// OPR -> tmpC     SIGMA -> tmpA  F--  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x0620:
case 0x1620:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOpr();
    const uint16_t b = sigma;
    r[TC] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 275 (ROM line 279)
// Match: 00?.01100010.0001
// Native Opcodes: 62
// -------------------------------------------------------------------------
// FLAGS -> LC     SIGMA -> IND   ---  EC=MR
// -------------------------------------------------------------------------
case 0x0621:
case 0x1621:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[FLAGS];
    const uint16_t b = sigma;
    r[LC] = a;
    writeIndex(b);
    requestRead(Segment::Default);
    break;
}

// Word: 276 (ROM line 27A)
// Match: 00?.01100010.0010
// Native Opcodes: 62
// -------------------------------------------------------------------------
// OP2 -> tmpB                    ---  ALU SUB, tmpC
// -------------------------------------------------------------------------
case 0x0622:
case 0x1622:
{
    const uint16_t a = readOperand(op2);
    r[TB] = a;
    setupAlu<false, false>(Alu::Sub, TC);
    break;
}

// Word: 277 (ROM line 27B)
// Match: 00?.01100010.0011
// Native Opcodes: 62
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x0623:
case 0x1623:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 278 (ROM line 27C)
// Match: 00?.01100010.0100
// Native Opcodes: 62
// -------------------------------------------------------------------------
// LC -> FLAGS     OP2 -> tmpA    ---  JUMP JL, 0A
// -------------------------------------------------------------------------
case 0x0624:
case 0x1624:
{
    const uint16_t a = r[LC];
    const uint16_t b = readOperand(op2);
    writeFlags(a);
    r[TA] = b;
    if (aluLess()) {
        jumpLocal(10);
    }
    break;
}

// Word: 279 (ROM line 27D)
// Match: 00?.01100010.0101
// Native Opcodes: 62
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x0625:
case 0x1625:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 27A (ROM line 27E)
// Match: 00?.01100010.0110
// Native Opcodes: 62
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x0626:
case 0x1626:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 27B (ROM line 27F)
// Match: 00?.01100010.0111
// Native Opcodes: 62
// -------------------------------------------------------------------------
// LC -> FLAGS                    ---  JUMP JL, 0B
// -------------------------------------------------------------------------
case 0x0627:
case 0x1627:
{
    const uint16_t a = r[LC];
    writeFlags(a);
    if (aluLess()) {
        jumpLocal(11);
    }
    break;
}

// Word: 27C (ROM line 280)
// Match: 00?.01100010.1000
// Native Opcodes: 62
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0628:
case 0x1628:
{
    endRequested = true;
    break;
}

// Word: 27E (ROM line 282)
// Match: 00?.01100010.1010
// Native Opcodes: 62
// -------------------------------------------------------------------------
// OPR -> tmpA                    F--  --
// -------------------------------------------------------------------------
case 0x062a:
case 0x162a:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    break;
}

// Word: 27F (ROM line 283)
// Match: 00?.01100010.1011
// Native Opcodes: 62
// -------------------------------------------------------------------------
// 5 -> tmpBL                     ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x062b:
case 0x162b:
{
    const uint16_t a = 5;
    r[TB] = extendByte(a);
    jumpFar(0x7100);
    break;
}

// Word: 030 (ROM line 030)
// Match: 00?.0110011?.0000
// Native Opcodes: 66-67
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0660:
case 0x0670:
case 0x1660:
case 0x1670:
{
    endRequested = true;
    break;
}

// Word: 284 (ROM line 288)
// Match: 00?.01101000.0000
// Native Opcodes: 68
// -------------------------------------------------------------------------
// Q -> tmpAL      SP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x0680:
case 0x1680:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[SP];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 285 (ROM line 289)
// Match: 00?.01101000.0001
// Native Opcodes: 68
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x0681:
case 0x1681:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 286 (ROM line 28A)
// Match: 00?.01101000.0010
// Native Opcodes: 68
// -------------------------------------------------------------------------
// tmpA -> OPR     SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x0682:
case 0x1682:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 287 (ROM line 28B)
// Match: 00?.01101000.0011
// Native Opcodes: 68
// -------------------------------------------------------------------------
// SIGMA -> SP                    --E  --
// -------------------------------------------------------------------------
case 0x0683:
case 0x1683:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    endRequested = true;
    break;
}

// Word: 28C (ROM line 290)
// Match: 00?.011010?1.0000
// Native Opcodes: 69, 6B
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x0690:
case 0x06b0:
case 0x1690:
case 0x16b0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 28D (ROM line 291)
// Match: 00?.011010?1.0001
// Native Opcodes: 69, 6B
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0691:
case 0x06b1:
case 0x1691:
case 0x16b1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 28E (ROM line 292)
// Match: 00?.011010?1.0010
// Native Opcodes: 69, 6B
// -------------------------------------------------------------------------
// OP1 -> tmpA                    ---  ALU MULDIV, tmpB
// -------------------------------------------------------------------------
case 0x0692:
case 0x06b2:
case 0x1692:
case 0x16b2:
{
    const uint16_t a = readOperand(op1);
    r[TA] = a;
    setupAlu<false, false>(Alu::MulDiv, TB);
    break;
}

// Word: 28F (ROM line 293)
// Match: 00?.011010?1.0011
// Native Opcodes: 69, 6B
// -------------------------------------------------------------------------
//                                ---  CALL IMUL2 (07) -> 7380 [Line 208]
// -------------------------------------------------------------------------
case 0x0693:
case 0x06b3:
case 0x1693:
case 0x16b3:
{
    jumpFar(0x7380);
    break;
}

// Word: 280 (ROM line 284)
// Match: 00?.01101010.0000
// Native Opcodes: 6A
// -------------------------------------------------------------------------
// Q -> tmpA       SP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x06a0:
case 0x16a0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[SP];
    r[TA] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 281 (ROM line 285)
// Match: 00?.01101010.0001
// Native Opcodes: 6A
// -------------------------------------------------------------------------
// SIGMA -> SP     SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x06a1:
case 0x16a1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SP] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 282 (ROM line 286)
// Match: 00?.01101010.0010
// Native Opcodes: 6A
// -------------------------------------------------------------------------
// tmpA -> tmpBL                  --E  --
// -------------------------------------------------------------------------
case 0x06a2:
case 0x16a2:
{
    const uint16_t a = r[TA];
    r[TB] = extendByte(a);
    endRequested = true;
    break;
}

// Word: 283 (ROM line 287)
// Match: 00?.01101010.0011
// Native Opcodes: 6A
// -------------------------------------------------------------------------
// tmpB -> OPR                    ---  --
// -------------------------------------------------------------------------
case 0x06a3:
case 0x16a3:
{
    const uint16_t a = r[TB];
    writeOpr(a);
    break;
}

// Word: 290 (ROM line 294)
// Match: 000.0110110?.0000
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// D -> DP                        ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x06c0:
case 0x06d0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DX];
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 291 (ROM line 295)
// Match: 000.0110110?.0001
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// DIRSZ -> tmpA   DI -> tmpB     ---  --
// -------------------------------------------------------------------------
case 0x06c1:
case 0x06d1:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[DI];
    r[TA] = a;
    r[TB] = b;
    break;
}

// Word: 292 (ROM line 296)
// Match: 000.0110110?.0010
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// DI -> DP                       --E  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x06c2:
case 0x06d2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestWrite(Segment::ES);
    endRequested = true;
    break;
}

// Word: 293 (ROM line 297)
// Match: 000.0110110?.0011
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  --
// -------------------------------------------------------------------------
case 0x06c3:
case 0x06d3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    break;
}

// Word: 29C (ROM line 2A0)
// Match: 000.0110111?.0000
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// SI -> DP                       ---  EC=MR
// -------------------------------------------------------------------------
case 0x06e0:
case 0x06f0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 29D (ROM line 2A1)
// Match: 000.0110111?.0001
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// DIRSZ -> tmpA   SI -> tmpB     ---  --
// -------------------------------------------------------------------------
case 0x06e1:
case 0x06f1:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[SI];
    r[TA] = a;
    r[TB] = b;
    break;
}

// Word: 29E (ROM line 2A2)
// Match: 000.0110111?.0010
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// D -> DP                        --E  EC=MW, SR=None
// -------------------------------------------------------------------------
case 0x06e2:
case 0x06f2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DX];
    writeIndex(a);
    requestWrite(Segment::Io);
    endRequested = true;
    break;
}

// Word: 29F (ROM line 2A3)
// Match: 000.0110111?.0011
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  --
// -------------------------------------------------------------------------
case 0x06e3:
case 0x06f3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    break;
}

// Word: 034 (ROM line 034)
// Match: 00?.0111????.0000
// Native Opcodes: 70-7F
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0700:
case 0x0710:
case 0x0720:
case 0x0730:
case 0x0740:
case 0x0750:
case 0x0760:
case 0x0770:
case 0x0780:
case 0x0790:
case 0x07a0:
case 0x07b0:
case 0x07c0:
case 0x07d0:
case 0x07e0:
case 0x07f0:
case 0x1700:
case 0x1710:
case 0x1720:
case 0x1730:
case 0x1740:
case 0x1750:
case 0x1760:
case 0x1770:
case 0x1780:
case 0x1790:
case 0x17a0:
case 0x17b0:
case 0x17c0:
case 0x17d0:
case 0x17e0:
case 0x17f0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 035 (ROM line 035)
// Match: 00?.0111????.0001
// Native Opcodes: 70-7F
// -------------------------------------------------------------------------
//                                ---  JUMP OPC, 04
// -------------------------------------------------------------------------
case 0x0701:
case 0x0711:
case 0x0721:
case 0x0731:
case 0x0741:
case 0x0751:
case 0x0761:
case 0x0771:
case 0x0781:
case 0x0791:
case 0x07a1:
case 0x07b1:
case 0x07c1:
case 0x07d1:
case 0x07e1:
case 0x07f1:
case 0x1701:
case 0x1711:
case 0x1721:
case 0x1731:
case 0x1741:
case 0x1751:
case 0x1761:
case 0x1771:
case 0x1781:
case 0x1791:
case 0x17a1:
case 0x17b1:
case 0x17c1:
case 0x17d1:
case 0x17e1:
case 0x17f1:
{
    if (opcodeCondition()) {
        jumpLocal(4);
    }
    break;
}

// Word: 036 (ROM line 036)
// Match: 00?.0111????.0010
// Native Opcodes: 70-7F
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0702:
case 0x0712:
case 0x0722:
case 0x0732:
case 0x0742:
case 0x0752:
case 0x0762:
case 0x0772:
case 0x0782:
case 0x0792:
case 0x07a2:
case 0x07b2:
case 0x07c2:
case 0x07d2:
case 0x07e2:
case 0x07f2:
case 0x1702:
case 0x1712:
case 0x1722:
case 0x1732:
case 0x1742:
case 0x1752:
case 0x1762:
case 0x1772:
case 0x1782:
case 0x1792:
case 0x17a2:
case 0x17b2:
case 0x17c2:
case 0x17d2:
case 0x17e2:
case 0x17f2:
{
    endRequested = true;
    break;
}

// Word: 038 (ROM line 038)
// Match: 00?.0111????.0100
// Native Opcodes: 70-7F
// -------------------------------------------------------------------------
// PC -> tmpA                     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0704:
case 0x0714:
case 0x0724:
case 0x0734:
case 0x0744:
case 0x0754:
case 0x0764:
case 0x0774:
case 0x0784:
case 0x0794:
case 0x07a4:
case 0x07b4:
case 0x07c4:
case 0x07d4:
case 0x07e4:
case 0x07f4:
case 0x1704:
case 0x1714:
case 0x1724:
case 0x1734:
case 0x1744:
case 0x1754:
case 0x1764:
case 0x1774:
case 0x1784:
case 0x1794:
case 0x17a4:
case 0x17b4:
case 0x17c4:
case 0x17d4:
case 0x17e4:
case 0x17f4:
{
    const uint16_t a = readPc();
    r[TA] = a;
    suspendPrefetch();
    break;
}

// Word: 039 (ROM line 039)
// Match: 00?.0111????.0101
// Native Opcodes: 70-7F
// -------------------------------------------------------------------------
// SIGMA -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0705:
case 0x0715:
case 0x0725:
case 0x0735:
case 0x0745:
case 0x0755:
case 0x0765:
case 0x0775:
case 0x0785:
case 0x0795:
case 0x07a5:
case 0x07b5:
case 0x07c5:
case 0x07d5:
case 0x07e5:
case 0x07f5:
case 0x1705:
case 0x1715:
case 0x1725:
case 0x1735:
case 0x1745:
case 0x1755:
case 0x1765:
case 0x1775:
case 0x1785:
case 0x1795:
case 0x17a5:
case 0x17b5:
case 0x17c5:
case 0x17d5:
case 0x17e5:
case 0x17f5:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, true);
    endRequested = true;
    break;
}

// Word: 03C (ROM line 03C)
// Match: 00?.100000??.0000
// Native Opcodes: 80-83
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x0800:
case 0x0810:
case 0x0820:
case 0x0830:
case 0x1800:
case 0x1810:
case 0x1820:
case 0x1830:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 03D (ROM line 03D)
// Match: 00?.100000??.0001
// Native Opcodes: 80-83
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0801:
case 0x0811:
case 0x0821:
case 0x0831:
case 0x1801:
case 0x1811:
case 0x1821:
case 0x1831:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 03E (ROM line 03E)
// Match: 00?.100000??.0010
// Native Opcodes: 80-83
// -------------------------------------------------------------------------
// tmpB -> tmpA                   ---  ALU XI, tmpA
// -------------------------------------------------------------------------
case 0x0802:
case 0x0812:
case 0x0822:
case 0x0832:
case 0x1802:
case 0x1812:
case 0x1822:
case 0x1832:
{
    const uint16_t a = r[TB];
    r[TA] = a;
    setupDecodedAlu<false, false>(TA);
    break;
}

// Word: 03F (ROM line 03F)
// Match: 00?.100000??.0011
// Native Opcodes: 80-83
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  --
// -------------------------------------------------------------------------
case 0x0803:
case 0x0813:
case 0x0823:
case 0x0833:
case 0x1803:
case 0x1813:
case 0x1823:
case 0x1833:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    break;
}

// Word: 040 (ROM line 040)
// Match: 00?.100000??.0100
// Native Opcodes: 80-83
// -------------------------------------------------------------------------
// SIGMA -> OP1                   -WE  EC=COMMIT
// -------------------------------------------------------------------------
case 0x0804:
case 0x0814:
case 0x0824:
case 0x0834:
case 0x1804:
case 0x1814:
case 0x1824:
case 0x1834:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitAluFlags();
    commitOperand();
    endRequested = true;
    break;
}

// Word: 044 (ROM line 044)
// Match: 00?.1000010?.0000
// Native Opcodes: 84-85
// -------------------------------------------------------------------------
// OP1 -> tmpA     OP2 -> tmpB    --E  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x0840:
case 0x0850:
case 0x1840:
case 0x1850:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = readOperand(op2);
    r[TA] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::And, TA);
    endRequested = true;
    break;
}

// Word: 045 (ROM line 045)
// Match: 00?.1000010?.0001
// Native Opcodes: 84-85
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x0841:
case 0x0851:
case 0x1841:
case 0x1851:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 048 (ROM line 048)
// Match: 00?.1000011?.0000
// Native Opcodes: 86-87
// -------------------------------------------------------------------------
// OP1 -> tmpA     OP2 -> tmpB    ---  --
// -------------------------------------------------------------------------
case 0x0860:
case 0x0870:
case 0x1860:
case 0x1870:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = readOperand(op2);
    r[TA] = a;
    r[TB] = b;
    break;
}

// Word: 049 (ROM line 049)
// Match: 00?.1000011?.0001
// Native Opcodes: 86-87
// -------------------------------------------------------------------------
// tmpA -> OP2                    --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x0861:
case 0x0871:
case 0x1861:
case 0x1871:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeOperand(op2, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 04A (ROM line 04A)
// Match: 00?.1000011?.0010
// Native Opcodes: 86-87
// -------------------------------------------------------------------------
// tmpB -> OP1                    ---  --
// -------------------------------------------------------------------------
case 0x0862:
case 0x0872:
case 0x1862:
case 0x1872:
{
    const uint16_t a = r[TB];
    writeOperand(op1, a);
    break;
}

// Word: 04C (ROM line 04C)
// Match: 00?.100010??.0000
// Native Opcodes: 88-8B
// -------------------------------------------------------------------------
// OP2 -> tmpA                    ---  --
// -------------------------------------------------------------------------
case 0x0880:
case 0x0890:
case 0x08a0:
case 0x08b0:
case 0x1880:
case 0x1890:
case 0x18a0:
case 0x18b0:
{
    const uint16_t a = readOperand(op2);
    r[TA] = a;
    break;
}

// Word: 04D (ROM line 04D)
// Match: 00?.100010??.0001
// Native Opcodes: 88-8B
// -------------------------------------------------------------------------
// tmpA -> OP1                    --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x0881:
case 0x0891:
case 0x08a1:
case 0x08b1:
case 0x1881:
case 0x1891:
case 0x18a1:
case 0x18b1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 050 (ROM line 050)
// Match: 00?.100011?0.0000
// Native Opcodes: 8C, 8E
// -------------------------------------------------------------------------
// OP2 -> OP1                     --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x08c0:
case 0x08e0:
case 0x18c0:
case 0x18e0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readOperand(op2);
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 054 (ROM line 054)
// Match: 00?.10001101.0000
// Native Opcodes: 8D
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x08d0:
case 0x18d0:
{
    endRequested = true;
    break;
}

// Word: 055 (ROM line 055)
// Match: 00?.10001101.0001
// Native Opcodes: 8D
// -------------------------------------------------------------------------
// SIGMA -> OP2                   ---  --
// -------------------------------------------------------------------------
case 0x08d1:
case 0x18d1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op2, a);
    break;
}

// Word: 058 (ROM line 058)
// Match: 00?.10001111.0000
// Native Opcodes: 8F
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x08f0:
case 0x18f0:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 059 (ROM line 059)
// Match: 00?.10001111.0001
// Native Opcodes: 8F
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpB     ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x08f1:
case 0x18f1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::SS);
    break;
}

// Word: 05A (ROM line 05A)
// Match: 00?.10001111.0010
// Native Opcodes: 8F
// -------------------------------------------------------------------------
// SIGMA -> SP                    F--  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x08f2:
case 0x18f2:
{
    requestOprLatch();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 05B (ROM line 05B)
// Match: 00?.10001111.0011
// Native Opcodes: 8F
// -------------------------------------------------------------------------
// SIGMA -> DP                    --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x08f3:
case 0x18f3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 05C (ROM line 05C)
// Match: 00?.10010???.0000
// Native Opcodes: 90-97
// -------------------------------------------------------------------------
// OP1 -> tmpB     A -> tmpA      ---  --
// -------------------------------------------------------------------------
case 0x0900:
case 0x0910:
case 0x0920:
case 0x0930:
case 0x0940:
case 0x0950:
case 0x0960:
case 0x0970:
case 0x1900:
case 0x1910:
case 0x1920:
case 0x1930:
case 0x1940:
case 0x1950:
case 0x1960:
case 0x1970:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[AX];
    r[TB] = a;
    r[TA] = b;
    break;
}

// Word: 05D (ROM line 05D)
// Match: 00?.10010???.0001
// Native Opcodes: 90-97
// -------------------------------------------------------------------------
// tmpA -> OP1                    --E  --
// -------------------------------------------------------------------------
case 0x0901:
case 0x0911:
case 0x0921:
case 0x0931:
case 0x0941:
case 0x0951:
case 0x0961:
case 0x0971:
case 0x1901:
case 0x1911:
case 0x1921:
case 0x1931:
case 0x1941:
case 0x1951:
case 0x1961:
case 0x1971:
{
    const uint16_t a = r[TA];
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 05E (ROM line 05E)
// Match: 00?.10010???.0010
// Native Opcodes: 90-97
// -------------------------------------------------------------------------
// tmpB -> A                      ---  --
// -------------------------------------------------------------------------
case 0x0902:
case 0x0912:
case 0x0922:
case 0x0932:
case 0x0942:
case 0x0952:
case 0x0962:
case 0x0972:
case 0x1902:
case 0x1912:
case 0x1922:
case 0x1932:
case 0x1942:
case 0x1952:
case 0x1962:
case 0x1972:
{
    const uint16_t a = r[TB];
    r[AX] = a;
    break;
}

// Word: 060 (ROM line 060)
// Match: 00?.10011000.0000
// Native Opcodes: 98
// -------------------------------------------------------------------------
// A -> tmpBL                     --E  --
// -------------------------------------------------------------------------
case 0x0980:
case 0x1980:
{
    const uint16_t a = r[AX];
    r[TB] = extendByte(a);
    endRequested = true;
    break;
}

// Word: 061 (ROM line 061)
// Match: 00?.10011000.0001
// Native Opcodes: 98
// -------------------------------------------------------------------------
// tmpB -> A                      ---  --
// -------------------------------------------------------------------------
case 0x0981:
case 0x1981:
{
    const uint16_t a = r[TB];
    r[AX] = a;
    break;
}

// Word: 064 (ROM line 064)
// Match: 00?.10011001.0000
// Native Opcodes: 99
// -------------------------------------------------------------------------
// ZERO -> D       A -> tmpB      ---  --
// -------------------------------------------------------------------------
case 0x0990:
case 0x1990:
{
    const uint16_t a = 0;
    const uint16_t b = r[AX];
    r[DX] = a;
    r[TB] = b;
    break;
}

// Word: 065 (ROM line 065)
// Match: 00?.10011001.0001
// Native Opcodes: 99
// -------------------------------------------------------------------------
//                                ---  JUMP JNS, 03
// -------------------------------------------------------------------------
case 0x0991:
case 0x1991:
{
    if ((r[TB] & (wordSize ? 0x8000 : 0x80)) == 0) {
        jumpLocal(3);
    }
    break;
}

// Word: 066 (ROM line 066)
// Match: 00?.10011001.0010
// Native Opcodes: 99
// -------------------------------------------------------------------------
// K -> D                         ---  --
// -------------------------------------------------------------------------
case 0x0992:
case 0x1992:
{
    const uint16_t a = readK();
    r[DX] = a;
    break;
}

// Word: 067 (ROM line 067)
// Match: 00?.10011001.0011
// Native Opcodes: 99
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0993:
case 0x1993:
{
    endRequested = true;
    break;
}

// Word: 068 (ROM line 068)
// Match: 00?.10011010.0000
// Native Opcodes: 9A
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x09a0:
case 0x19a0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 069 (ROM line 069)
// Match: 00?.10011010.0001
// Native Opcodes: 9A
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x09a1:
case 0x19a1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 06A (ROM line 06A)
// Match: 00?.10011010.0010
// Native Opcodes: 9A
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x09a2:
case 0x19a2:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 06B (ROM line 06B)
// Match: 00?.10011010.0011
// Native Opcodes: 9A
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  CALL FARCALL (0D) -> 7680 [Line 228]
// -------------------------------------------------------------------------
case 0x09a3:
case 0x19a3:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    jumpFar(0x7680);
    break;
}

// Word: 06C (ROM line 06C)
// Match: 00?.10011011.0000
// Native Opcodes: 9B
// -------------------------------------------------------------------------
//                                ---  JUMP BUSY, 03
// -------------------------------------------------------------------------
case 0x09b0:
case 0x19b0:
{
    if (busyPin) {
        jumpLocal(3);
    }
    break;
}

// Word: 06D (ROM line 06D)
// Match: 00?.10011011.0001
// Native Opcodes: 9B
// -------------------------------------------------------------------------
//                                --E  IC=WAIT
// -------------------------------------------------------------------------
case 0x09b1:
case 0x19b1:
{
    deferInterrupt();
    endRequested = true;
    break;
}

// Word: 06F (ROM line 06F)
// Match: 00?.10011011.0011
// Native Opcodes: 9B
// -------------------------------------------------------------------------
//                                ---  JUMP INT, 05
// -------------------------------------------------------------------------
case 0x09b3:
case 0x19b3:
{
    const bool interrupt_pending = interruptPending();
    if (interrupt_pending) {
        jumpLocal(5);
    }
    break;
}

// Word: 070 (ROM line 070)
// Match: 00?.10011011.0100
// Native Opcodes: 9B
// -------------------------------------------------------------------------
//                                ---  JUMP UNC, 00
// -------------------------------------------------------------------------
case 0x09b4:
case 0x19b4:
{
    if (true) {
        jumpLocal(0);
    }
    break;
}

// Word: 071 (ROM line 071)
// Match: 00?.10011011.0101
// Native Opcodes: 9B
// -------------------------------------------------------------------------
//                                ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x09b5:
case 0x19b5:
{
    suspendPrefetch();
    break;
}

// Word: 072 (ROM line 072)
// Match: 00?.10011011.0110
// Native Opcodes: 9B
// -------------------------------------------------------------------------
// PC -> tmpB                     ---  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x09b6:
case 0x19b6:
{
    const uint16_t a = readPc();
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec, TB);
    break;
}

// Word: 073 (ROM line 073)
// Match: 00?.10011011.0111
// Native Opcodes: 9B
// -------------------------------------------------------------------------
// SIGMA -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x09b7:
case 0x19b7:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, true);
    endRequested = true;
    break;
}

// Word: 074 (ROM line 074)
// Match: 00?.10011100.0000
// Native Opcodes: 9C
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x09c0:
case 0x19c0:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 075 (ROM line 075)
// Match: 00?.10011100.0001
// Native Opcodes: 9C
// -------------------------------------------------------------------------
// FLAGS -> OPR    SIGMA -> IND   --E  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x09c1:
case 0x19c1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[FLAGS];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::SS);
    endRequested = true;
    break;
}

// Word: 076 (ROM line 076)
// Match: 00?.10011100.0010
// Native Opcodes: 9C
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x09c2:
case 0x19c2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 078 (ROM line 078)
// Match: 00?.10011101.0000
// Native Opcodes: 9D
// -------------------------------------------------------------------------
// SP -> DP                       ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x09d0:
case 0x19d0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    writeIndex(a);
    requestRead(Segment::SS);
    break;
}

// Word: 079 (ROM line 079)
// Match: 00?.10011101.0001
// Native Opcodes: 9D
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x09d1:
case 0x19d1:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 07A (ROM line 07A)
// Match: 00?.10011101.0010
// Native Opcodes: 9D
// -------------------------------------------------------------------------
// OPR -> FLAGS                   F-E  --
// -------------------------------------------------------------------------
case 0x09d2:
case 0x19d2:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeFlags(a);
    endRequested = true;
    break;
}

// Word: 07B (ROM line 07B)
// Match: 00?.10011101.0011
// Native Opcodes: 9D
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x09d3:
case 0x19d3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 07C (ROM line 07C)
// Match: 00?.10011110.0000
// Native Opcodes: 9E
// -------------------------------------------------------------------------
// AL:AH -> tmpAL                 ---  --
// -------------------------------------------------------------------------
case 0x09e0:
case 0x19e0:
{
    const uint16_t a = swappedAccumulator();
    r[TA] = uint8_t(a);
    break;
}

// Word: 07D (ROM line 07D)
// Match: 00?.10011110.0001
// Native Opcodes: 9E
// -------------------------------------------------------------------------
// FLAGS -> tmpAH                 --E  --
// -------------------------------------------------------------------------
case 0x09e1:
case 0x19e1:
{
    const uint16_t a = r[FLAGS];
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    endRequested = true;
    break;
}

// Word: 07E (ROM line 07E)
// Match: 00?.10011110.0010
// Native Opcodes: 9E
// -------------------------------------------------------------------------
// tmpA -> FLAGS                  ---  --
// -------------------------------------------------------------------------
case 0x09e2:
case 0x19e2:
{
    const uint16_t a = r[TA];
    writeFlags(a);
    break;
}

// Word: 080 (ROM line 080)
// Match: 00?.10011111.0000
// Native Opcodes: 9F
// -------------------------------------------------------------------------
// FLAGS -> AH                    --E  --
// -------------------------------------------------------------------------
case 0x09f0:
case 0x19f0:
{
    const uint16_t a = r[FLAGS];
    writeByteReg(4, a);
    endRequested = true;
    break;
}

// Word: 084 (ROM line 084)
// Match: 00?.1010000?.0000
// Native Opcodes: A0-A1
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x0a00:
case 0x0a10:
case 0x1a00:
case 0x1a10:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 085 (ROM line 085)
// Match: 00?.1010000?.0001
// Native Opcodes: A0-A1
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0a01:
case 0x0a11:
case 0x1a01:
case 0x1a11:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 086 (ROM line 086)
// Match: 00?.1010000?.0010
// Native Opcodes: A0-A1
// -------------------------------------------------------------------------
// tmpB -> DP                     ---  EC=MR
// -------------------------------------------------------------------------
case 0x0a02:
case 0x0a12:
case 0x1a02:
case 0x1a12:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TB];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 087 (ROM line 087)
// Match: 00?.1010000?.0011
// Native Opcodes: A0-A1
// -------------------------------------------------------------------------
// OPR -> OP1                     F-E  --
// -------------------------------------------------------------------------
case 0x0a03:
case 0x0a13:
case 0x1a03:
case 0x1a13:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 088 (ROM line 088)
// Match: 00?.1010001?.0000
// Native Opcodes: A2-A3
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x0a20:
case 0x0a30:
case 0x1a20:
case 0x1a30:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 089 (ROM line 089)
// Match: 00?.1010001?.0001
// Native Opcodes: A2-A3
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0a21:
case 0x0a31:
case 0x1a21:
case 0x1a31:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 08A (ROM line 08A)
// Match: 00?.1010001?.0010
// Native Opcodes: A2-A3
// -------------------------------------------------------------------------
// tmpB -> DP                     --E  EC=MW
// -------------------------------------------------------------------------
case 0x0a22:
case 0x0a32:
case 0x1a22:
case 0x1a32:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TB];
    writeIndex(a);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 08B (ROM line 08B)
// Match: 00?.1010001?.0011
// Native Opcodes: A2-A3
// -------------------------------------------------------------------------
// OP1 -> OPR                     ---  --
// -------------------------------------------------------------------------
case 0x0a23:
case 0x0a33:
case 0x1a23:
case 0x1a33:
{
    const uint16_t a = readOperand(op1);
    writeOpr(a);
    break;
}

// Word: 08C (ROM line 08C)
// Match: 000.1010010?.0000
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   SI -> tmpB     ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x0a40:
case 0x0a50:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[SI];
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 08D (ROM line 08D)
// Match: 000.1010010?.0001
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// SI -> DP                       ---  EC=MR
// -------------------------------------------------------------------------
case 0x0a41:
case 0x0a51:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 08E (ROM line 08E)
// Match: 000.1010010?.0010
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// SIGMA -> SI     DI -> tmpB     ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x0a42:
case 0x0a52:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = r[DI];
    r[SI] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 08F (ROM line 08F)
// Match: 000.1010010?.0011
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// DI -> DP                       --E  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x0a43:
case 0x0a53:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestWrite(Segment::ES);
    endRequested = true;
    break;
}

// Word: 098 (ROM line 098)
// Match: 00?.1010010?.0100
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  --
// -------------------------------------------------------------------------
case 0x0a44:
case 0x0a54:
case 0x1a44:
case 0x1a54:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    break;
}

// Word: 099 (ROM line 099)
// Match: 00?.1010010?.0101
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// tmpB -> DP      SI -> tmpB     ---  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x0a45:
case 0x0a55:
case 0x1a45:
case 0x1a55:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TB];
    const uint16_t b = r[SI];
    writeIndex(a);
    r[TB] = b;
    requestWrite(Segment::ES);
    break;
}

// Word: 09A (ROM line 09A)
// Match: 00?.1010010?.0110
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x0a46:
case 0x0a56:
case 0x1a46:
case 0x1a56:
{
    const bool interrupt_pending = interruptPending();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 09B (ROM line 09B)
// Match: 00?.1010010?.0111
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x0a47:
case 0x0a57:
case 0x1a47:
case 0x1a57:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 09C (ROM line 09C)
// Match: 000.1010011?.0000
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   SI -> tmpB     ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x0a60:
case 0x0a70:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[SI];
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 09D (ROM line 09D)
// Match: 000.1010011?.0001
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// SI -> DP                       ---  EC=MR
// -------------------------------------------------------------------------
case 0x0a61:
case 0x0a71:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 09E (ROM line 09E)
// Match: 000.1010011?.0010
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// SIGMA -> SI     DI -> tmpB     ---  --
// -------------------------------------------------------------------------
case 0x0a62:
case 0x0a72:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = r[DI];
    r[SI] = a;
    r[TB] = b;
    break;
}

// Word: 09F (ROM line 09F)
// Match: 000.1010011?.0011
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// DI -> DP        SIGMA -> tmpA  ---  EC=MR, SR=ES
// -------------------------------------------------------------------------
case 0x0a63:
case 0x0a73:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DI];
    const uint16_t b = sigma;
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::ES);
    break;
}

// Word: 0A0 (ROM line 0A0)
// Match: 000.1010011?.0100
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  --
// -------------------------------------------------------------------------
case 0x0a64:
case 0x0a74:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    break;
}

// Word: 0A1 (ROM line 0A1)
// Match: 000.1010011?.0101
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// tmpA -> DI                     ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x0a65:
case 0x0a75:
{
    const uint16_t a = r[TA];
    r[DI] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 0A2 (ROM line 0A2)
// Match: 000.1010011?.0110
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// OPR -> tmpA                    F-E  --
// -------------------------------------------------------------------------
case 0x0a66:
case 0x0a76:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    endRequested = true;
    break;
}

// Word: 0A3 (ROM line 0A3)
// Match: 000.1010011?.0111
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x0a67:
case 0x0a77:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 0B4 (ROM line 0B4)
// Match: 00?.1010100?.0000
// Native Opcodes: A8-A9
// -------------------------------------------------------------------------
// A -> tmpB       Q -> tmpA      ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x0a80:
case 0x0a90:
case 0x1a80:
case 0x1a90:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = r[AX];
    const uint16_t b = readPrefetchForMicrocode();
    r[TB] = a;
    r[TA] = b;
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 0B5 (ROM line 0B5)
// Match: 00?.1010100?.0001
// Native Opcodes: A8-A9
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x0a81:
case 0x0a91:
case 0x1a81:
case 0x1a91:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 0B6 (ROM line 0B6)
// Match: 00?.1010100?.0010
// Native Opcodes: A8-A9
// -------------------------------------------------------------------------
//                                --E  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x0a82:
case 0x0a92:
case 0x1a82:
case 0x1a92:
{
    setupAlu<false, false>(Alu::And, TA);
    endRequested = true;
    break;
}

// Word: 0B7 (ROM line 0B7)
// Match: 00?.1010100?.0011
// Native Opcodes: A8-A9
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x0a83:
case 0x0a93:
case 0x1a83:
case 0x1a93:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 0B8 (ROM line 0B8)
// Match: 000.1010101?.0000
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   DI -> tmpB     ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x0aa0:
case 0x0ab0:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[DI];
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 0B9 (ROM line 0B9)
// Match: 000.1010101?.0001
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// DI -> DP                       ---  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x0aa1:
case 0x0ab1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestWrite(Segment::ES);
    break;
}

// Word: 0BA (ROM line 0BA)
// Match: 000.1010101?.0010
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// OP1 -> OPR                     --E  --
// -------------------------------------------------------------------------
case 0x0aa2:
case 0x0ab2:
{
    const uint16_t a = readOperand(op1);
    writeOpr(a);
    endRequested = true;
    break;
}

// Word: 0BB (ROM line 0BB)
// Match: 000.1010101?.0011
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  --
// -------------------------------------------------------------------------
case 0x0aa3:
case 0x0ab3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    break;
}

// Word: 0C4 (ROM line 0C4)
// Match: 000.1010110?.0000
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   SI -> tmpB     ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x0ac0:
case 0x0ad0:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[SI];
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 0C5 (ROM line 0C5)
// Match: 000.1010110?.0001
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// SI -> DP                       ---  EC=MR
// -------------------------------------------------------------------------
case 0x0ac1:
case 0x0ad1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 0C6 (ROM line 0C6)
// Match: 000.1010110?.0010
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  --
// -------------------------------------------------------------------------
case 0x0ac2:
case 0x0ad2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    break;
}

// Word: 0C7 (ROM line 0C7)
// Match: 000.1010110?.0011
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// OPR -> OP1                     F-E  --
// -------------------------------------------------------------------------
case 0x0ac3:
case 0x0ad3:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 0D0 (ROM line 0D0)
// Match: 000.1010111?.0000
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   DI -> tmpB     ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x0ae0:
case 0x0af0:
{
    const uint16_t a = directionStep();
    const uint16_t b = r[DI];
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 0D1 (ROM line 0D1)
// Match: 000.1010111?.0001
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// DI -> DP                       ---  EC=MR, SR=ES
// -------------------------------------------------------------------------
case 0x0ae1:
case 0x0af1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestRead(Segment::ES);
    break;
}

// Word: 0D2 (ROM line 0D2)
// Match: 000.1010111?.0010
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x0ae2:
case 0x0af2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 0D3 (ROM line 0D3)
// Match: 000.1010111?.0011
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  --
// -------------------------------------------------------------------------
case 0x0ae3:
case 0x0af3:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    break;
}

// Word: 0D4 (ROM line 0D4)
// Match: 000.1010111?.0100
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// OPR -> tmpA                    F--  --
// -------------------------------------------------------------------------
case 0x0ae4:
case 0x0af4:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    break;
}

// Word: 0D5 (ROM line 0D5)
// Match: 000.1010111?.0101
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -WE  --
// -------------------------------------------------------------------------
case 0x0ae5:
case 0x0af5:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    endRequested = true;
    break;
}

// Word: 0E0 (ROM line 0E0)
// Match: 00?.1011????.0000
// Native Opcodes: B0-BF
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x0b00:
case 0x0b10:
case 0x0b20:
case 0x0b30:
case 0x0b40:
case 0x0b50:
case 0x0b60:
case 0x0b70:
case 0x0b80:
case 0x0b90:
case 0x0ba0:
case 0x0bb0:
case 0x0bc0:
case 0x0bd0:
case 0x0be0:
case 0x0bf0:
case 0x1b00:
case 0x1b10:
case 0x1b20:
case 0x1b30:
case 0x1b40:
case 0x1b50:
case 0x1b60:
case 0x1b70:
case 0x1b80:
case 0x1b90:
case 0x1ba0:
case 0x1bb0:
case 0x1bc0:
case 0x1bd0:
case 0x1be0:
case 0x1bf0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 0E1 (ROM line 0E1)
// Match: 00?.1011????.0001
// Native Opcodes: B0-BF
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0b01:
case 0x0b11:
case 0x0b21:
case 0x0b31:
case 0x0b41:
case 0x0b51:
case 0x0b61:
case 0x0b71:
case 0x0b81:
case 0x0b91:
case 0x0ba1:
case 0x0bb1:
case 0x0bc1:
case 0x0bd1:
case 0x0be1:
case 0x0bf1:
case 0x1b01:
case 0x1b11:
case 0x1b21:
case 0x1b31:
case 0x1b41:
case 0x1b51:
case 0x1b61:
case 0x1b71:
case 0x1b81:
case 0x1b91:
case 0x1ba1:
case 0x1bb1:
case 0x1bc1:
case 0x1bd1:
case 0x1be1:
case 0x1bf1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 0E2 (ROM line 0E2)
// Match: 00?.1011????.0010
// Native Opcodes: B0-BF
// -------------------------------------------------------------------------
// tmpB -> OP1                    --E  --
// -------------------------------------------------------------------------
case 0x0b02:
case 0x0b12:
case 0x0b22:
case 0x0b32:
case 0x0b42:
case 0x0b52:
case 0x0b62:
case 0x0b72:
case 0x0b82:
case 0x0b92:
case 0x0ba2:
case 0x0bb2:
case 0x0bc2:
case 0x0bd2:
case 0x0be2:
case 0x0bf2:
case 0x1b02:
case 0x1b12:
case 0x1b22:
case 0x1b32:
case 0x1b42:
case 0x1b52:
case 0x1b62:
case 0x1b72:
case 0x1b82:
case 0x1b92:
case 0x1ba2:
case 0x1bb2:
case 0x1bc2:
case 0x1bd2:
case 0x1be2:
case 0x1bf2:
{
    const uint16_t a = r[TB];
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 288 (ROM line 28C)
// Match: 00?.1100000?.0000
// Native Opcodes: C0-C1
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x0c00:
case 0x0c10:
case 0x1c00:
case 0x1c10:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 289 (ROM line 28D)
// Match: 00?.1100000?.0001
// Native Opcodes: C0-C1
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  --
// -------------------------------------------------------------------------
case 0x0c01:
case 0x0c11:
case 0x1c01:
case 0x1c11:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    break;
}

// Word: 28A (ROM line 28E)
// Match: 00?.1100000?.0010
// Native Opcodes: C0-C1
// -------------------------------------------------------------------------
// tmpA -> LC      SIGMA -> NULL  ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x0c02:
case 0x0c12:
case 0x1c02:
case 0x1c12:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    r[LC] = a;
    (void)b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 28B (ROM line 28F)
// Match: 00?.1100000?.0011
// Native Opcodes: C0-C1
// -------------------------------------------------------------------------
//                                ---  CALL ROT (09) -> 7480 [Line 224]
// -------------------------------------------------------------------------
case 0x0c03:
case 0x0c13:
case 0x1c03:
case 0x1c13:
{
    jumpFar(0x7480);
    break;
}

// Word: 0E4 (ROM line 0E4)
// Match: 00?.1100?010.0000
// Native Opcodes: C2, CA
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x0c20:
case 0x0ca0:
case 0x1c20:
case 0x1ca0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 0E5 (ROM line 0E5)
// Match: 00?.1100?010.0001
// Native Opcodes: C2, CA
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x0c21:
case 0x0ca1:
case 0x1c21:
case 0x1ca1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 0E6 (ROM line 0E6)
// Match: 00?.1100?010.0010
// Native Opcodes: C2, CA
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0c22:
case 0x0ca2:
case 0x1c22:
case 0x1ca2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TA] = b;
    suspendPrefetch();
    requestRead(Segment::SS);
    break;
}

// Word: 0E8 (ROM line 0E8)
// Match: 00?.11000010.0100
// Native Opcodes: C2
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0c24:
case 0x1c24:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 0E9 (ROM line 0E9)
// Match: 00?.11000010.0101
// Native Opcodes: C2
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x0c25:
case 0x1c25:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 0EA (ROM line 0EA)
// Match: 00?.11000010.0110
// Native Opcodes: C2
// -------------------------------------------------------------------------
// OPR -> PC                      F-E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0c26:
case 0x1c26:
{
    if (!prefetchFlushReady(true)) { return; }
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[IP] = a;
    flushPrefetch(true, false, true);
    endRequested = true;
    break;
}

// Word: 0F0 (ROM line 0F0)
// Match: 00?.11000011.0000
// Native Opcodes: C3
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0c30:
case 0x1c30:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TA] = b;
    suspendPrefetch();
    requestRead(Segment::SS);
    break;
}

// Word: 0F1 (ROM line 0F1)
// Match: 00?.11000011.0001
// Native Opcodes: C3
// -------------------------------------------------------------------------
//                                ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x0c31:
case 0x1c31:
{
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 0F2 (ROM line 0F2)
// Match: 00?.11000011.0010
// Native Opcodes: C3
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x0c32:
case 0x1c32:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 0F3 (ROM line 0F3)
// Match: 00?.11000011.0011
// Native Opcodes: C3
// -------------------------------------------------------------------------
// OPR -> PC                      F-E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0c33:
case 0x1c33:
{
    if (!prefetchFlushReady(true)) { return; }
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[IP] = a;
    flushPrefetch(true, false, true);
    endRequested = true;
    break;
}

// Word: 0F8 (ROM line 0F8)
// Match: 00?.11000100.0000
// Native Opcodes: C4
// -------------------------------------------------------------------------
// OPR -> OP2      SIGMA -> tmpB  F--  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x0c40:
case 0x1c40:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOpr();
    const uint16_t b = sigma;
    writeOperand(op2, a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 0F9 (ROM line 0F9)
// Match: 00?.11000100.0001
// Native Opcodes: C4
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MR
// -------------------------------------------------------------------------
case 0x0c41:
case 0x1c41:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 0FA (ROM line 0FA)
// Match: 00?.11000100.0010
// Native Opcodes: C4
// -------------------------------------------------------------------------
// OPR -> ES                      F-E  --
// -------------------------------------------------------------------------
case 0x0c42:
case 0x1c42:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeSegment(ES, a);
    endRequested = true;
    break;
}

// Word: 0FC (ROM line 0FC)
// Match: 00?.11000101.0000
// Native Opcodes: C5
// -------------------------------------------------------------------------
// OPR -> OP2      SIGMA -> tmpB  F--  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x0c50:
case 0x1c50:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOpr();
    const uint16_t b = sigma;
    writeOperand(op2, a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 0FD (ROM line 0FD)
// Match: 00?.11000101.0001
// Native Opcodes: C5
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MR
// -------------------------------------------------------------------------
case 0x0c51:
case 0x1c51:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 0FE (ROM line 0FE)
// Match: 00?.11000101.0010
// Native Opcodes: C5
// -------------------------------------------------------------------------
// OPR -> DS                      F-E  --
// -------------------------------------------------------------------------
case 0x0c52:
case 0x1c52:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeSegment(DS, a);
    endRequested = true;
    break;
}

// Word: 100 (ROM line 100)
// Match: 00?.1100011?.0000
// Native Opcodes: C6-C7
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x0c60:
case 0x0c70:
case 0x1c60:
case 0x1c70:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 101 (ROM line 101)
// Match: 00?.1100011?.0001
// Native Opcodes: C6-C7
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0c61:
case 0x0c71:
case 0x1c61:
case 0x1c71:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 102 (ROM line 102)
// Match: 00?.1100011?.0010
// Native Opcodes: C6-C7
// -------------------------------------------------------------------------
// tmpB -> OP1                    --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x0c62:
case 0x0c72:
case 0x1c62:
case 0x1c72:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TB];
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 25C (ROM line 260)
// Match: 00?.11001000.0000
// Native Opcodes: C8
// -------------------------------------------------------------------------
// Q -> tmpAL      SP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x0c80:
case 0x1c80:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[SP];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 25D (ROM line 261)
// Match: 00?.11001000.0001
// Native Opcodes: C8
// -------------------------------------------------------------------------
// Q -> tmpAH      SIGMA -> IND   ---  --
// -------------------------------------------------------------------------
case 0x0c81:
case 0x1c81:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t sigma = evaluateAlu();
    const uint16_t a = (readPrefetchForMicrocode() << 8);
    const uint16_t b = sigma;
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    writeIndex(b);
    break;
}

// Word: 25E (ROM line 262)
// Match: 00?.11001000.0010
// Native Opcodes: C8
// -------------------------------------------------------------------------
//                                ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x0c82:
case 0x1c82:
{
    if (!requestSlotReady()) { return; }
    requestWrite(Segment::SS);
    break;
}

// Word: 25F (ROM line 263)
// Match: 00?.11001000.0011
// Native Opcodes: C8
// -------------------------------------------------------------------------
// BP -> OPR                      F--  CALL ENTER (0A) -> 7500 [Line 260]
// -------------------------------------------------------------------------
case 0x0c83:
case 0x1c83:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[BP];
    writeOpr(a);
    jumpFar(0x7500);
    break;
}

// Word: 270 (ROM line 274)
// Match: 00?.11001001.0000
// Native Opcodes: C9
// -------------------------------------------------------------------------
// BP -> DP        BP -> tmpB     ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0c90:
case 0x1c90:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    const uint16_t b = r[BP];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::SS);
    break;
}

// Word: 271 (ROM line 275)
// Match: 00?.11001001.0001
// Native Opcodes: C9
// -------------------------------------------------------------------------
// 2 -> tmpA                      ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0c91:
case 0x1c91:
{
    const uint16_t a = 2;
    r[TA] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 272 (ROM line 276)
// Match: 00?.11001001.0010
// Native Opcodes: C9
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x0c92:
case 0x1c92:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 273 (ROM line 277)
// Match: 00?.11001001.0011
// Native Opcodes: C9
// -------------------------------------------------------------------------
// OPR -> BP                      F-E  --
// -------------------------------------------------------------------------
case 0x0c93:
case 0x1c93:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[BP] = a;
    endRequested = true;
    break;
}

// Word: 0EC (ROM line 0EC)
// Match: 00?.11001010.0100
// Native Opcodes: CA
// -------------------------------------------------------------------------
// SIGMA -> DP     SIGMA -> tmpA  ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0ca4:
case 0x1ca4:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::SS);
    break;
}

// Word: 0ED (ROM line 0ED)
// Match: 00?.11001010.0101
// Native Opcodes: CA
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  CALL FARRET (10) -> 7800 [Line 230]
// -------------------------------------------------------------------------
case 0x0ca5:
case 0x1ca5:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    jumpFar(0x7800);
    break;
}

// Word: 0F4 (ROM line 0F4)
// Match: 00?.11001011.0000
// Native Opcodes: CB
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0cb0:
case 0x1cb0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TA] = b;
    suspendPrefetch();
    requestRead(Segment::SS);
    break;
}

// Word: 0F5 (ROM line 0F5)
// Match: 00?.11001011.0001
// Native Opcodes: CB
// -------------------------------------------------------------------------
// ZERO -> tmpB                   ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x0cb1:
case 0x1cb1:
{
    const uint16_t a = 0;
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 0F6 (ROM line 0F6)
// Match: 00?.11001011.0010
// Native Opcodes: CB
// -------------------------------------------------------------------------
// SIGMA -> DP     SIGMA -> tmpA  ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0cb2:
case 0x1cb2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::SS);
    break;
}

// Word: 0F7 (ROM line 0F7)
// Match: 00?.11001011.0011
// Native Opcodes: CB
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  CALL FARRET (10) -> 7800 [Line 230]
// -------------------------------------------------------------------------
case 0x0cb3:
case 0x1cb3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    jumpFar(0x7800);
    break;
}

// Word: 104 (ROM line 104)
// Match: 00?.11001100.0000
// Native Opcodes: CC
// -------------------------------------------------------------------------
// 3 -> tmpBL                     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0cc0:
case 0x1cc0:
{
    const uint16_t a = 3;
    r[TB] = extendByte(a);
    suspendPrefetch();
    break;
}

// Word: 105 (ROM line 105)
// Match: 00?.11001100.0001
// Native Opcodes: CC
// -------------------------------------------------------------------------
//                                ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x0cc1:
case 0x1cc1:
{
    jumpFar(0x7100);
    break;
}

// Word: 108 (ROM line 108)
// Match: 00?.11001101.0000
// Native Opcodes: CD
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x0cd0:
case 0x1cd0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    jumpFar(0x7100);
    break;
}

// Word: 10C (ROM line 10C)
// Match: 00?.11001110.0000
// Native Opcodes: CE
// -------------------------------------------------------------------------
// 4 -> tmpBL                     ---  JUMP JO, 03
// -------------------------------------------------------------------------
case 0x0ce0:
case 0x1ce0:
{
    const uint16_t a = 4;
    r[TB] = extendByte(a);
    if ((r[FLAGS] & OF) != 0) {
        jumpLocal(3);
    }
    break;
}

// Word: 10D (ROM line 10D)
// Match: 00?.11001110.0001
// Native Opcodes: CE
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0ce1:
case 0x1ce1:
{
    endRequested = true;
    break;
}

// Word: 10F (ROM line 10F)
// Match: 00?.11001110.0011
// Native Opcodes: CE
// -------------------------------------------------------------------------
//                                ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x0ce3:
case 0x1ce3:
{
    jumpFar(0x7100);
    break;
}

// Word: 110 (ROM line 110)
// Match: 00?.11001111.0000
// Native Opcodes: CF
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x0cf0:
case 0x1cf0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TA] = b;
    suspendPrefetch();
    requestRead(Segment::SS);
    break;
}

// Word: 111 (ROM line 111)
// Match: 00?.11001111.0001
// Native Opcodes: CF
// -------------------------------------------------------------------------
//                                ---  CALL IRET (01) -> 7080 [Line 1E0]
// -------------------------------------------------------------------------
case 0x0cf1:
case 0x1cf1:
{
    jumpFar(0x7080);
    break;
}

// Word: 114 (ROM line 114)
// Match: 00?.1101000?.0000
// Native Opcodes: D0-D1
// -------------------------------------------------------------------------
// 1 -> LC                        ---  --
// -------------------------------------------------------------------------
case 0x0d00:
case 0x0d10:
case 0x1d00:
case 0x1d10:
{
    const uint16_t a = 1;
    r[LC] = a;
    break;
}

// Word: 115 (ROM line 115)
// Match: 00?.1101000?.0001
// Native Opcodes: D0-D1
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x0d01:
case 0x0d11:
case 0x1d01:
case 0x1d11:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 116 (ROM line 116)
// Match: 00?.1101000?.0010
// Native Opcodes: D0-D1
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  -W-  ALU XI, tmpB, R
// -------------------------------------------------------------------------
case 0x0d02:
case 0x0d12:
case 0x1d02:
case 0x1d12:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDecodedAlu<true, true>(TB);
    break;
}

// Word: 117 (ROM line 117)
// Match: 00?.1101000?.0011
// Native Opcodes: D0-D1
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x0d03:
case 0x0d13:
case 0x1d03:
case 0x1d13:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 118 (ROM line 118)
// Match: 00?.1101001?.0000
// Native Opcodes: D2-D3
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x0d20:
case 0x0d30:
case 0x1d20:
case 0x1d30:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 119 (ROM line 119)
// Match: 00?.1101001?.0001
// Native Opcodes: D2-D3
// -------------------------------------------------------------------------
// C -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x0d21:
case 0x0d31:
case 0x1d21:
case 0x1d31:
{
    const uint16_t a = r[CX];
    r[TA] = uint8_t(a);
    break;
}

// Word: 11A (ROM line 11A)
// Match: 00?.1101001?.0010
// Native Opcodes: D2-D3
// -------------------------------------------------------------------------
// tmpA -> LC      SIGMA -> NULL  ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x0d22:
case 0x0d32:
case 0x1d22:
case 0x1d32:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    r[LC] = a;
    (void)b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 11B (ROM line 11B)
// Match: 00?.1101001?.0011
// Native Opcodes: D2-D3
// -------------------------------------------------------------------------
//                                ---  CALL ROT (09) -> 7480 [Line 224]
// -------------------------------------------------------------------------
case 0x0d23:
case 0x0d33:
case 0x1d23:
case 0x1d33:
{
    jumpFar(0x7480);
    break;
}

// Word: 11C (ROM line 11C)
// Match: 00?.11010100.0000
// Native Opcodes: D4
// -------------------------------------------------------------------------
// Q -> tmpC       A -> tmpA      ---  --
// -------------------------------------------------------------------------
case 0x0d40:
case 0x1d40:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[AX];
    r[TC] = a;
    r[TA] = b;
    break;
}

// Word: 11D (ROM line 11D)
// Match: 00?.11010100.0001
// Native Opcodes: D4
// -------------------------------------------------------------------------
// ZERO -> tmpB                   ---  --
// -------------------------------------------------------------------------
case 0x0d41:
case 0x1d41:
{
    const uint16_t a = 0;
    r[TB] = a;
    break;
}

// Word: 11E (ROM line 11E)
// Match: 00?.11010100.0010
// Native Opcodes: D4
// -------------------------------------------------------------------------
// 8 -> LC                        ---  ALU SUB, tmpC
// -------------------------------------------------------------------------
case 0x0d42:
case 0x1d42:
{
    const uint16_t a = 8;
    r[LC] = a;
    setupAlu<false, false>(Alu::Sub, TC);
    break;
}

// Word: 11F (ROM line 11F)
// Match: 00?.11010100.0011
// Native Opcodes: D4
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU DIV, tmpC, R
// -------------------------------------------------------------------------
case 0x0d43:
case 0x1d43:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDiv<true, false>(TC);
    break;
}

// Word: 120 (ROM line 120)
// Match: 00?.11010100.0100
// Native Opcodes: D4
// -------------------------------------------------------------------------
// SIGMA -> NULL   SIGMA -> tmpB  ---  ALU DIV, tmpC
// -------------------------------------------------------------------------
case 0x0d44:
case 0x1d44:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    (void)a;
    r[TB] = b;
    setupDiv<false, false>(TC);
    break;
}

// Word: 121 (ROM line 121)
// Match: 00?.11010100.0101
// Native Opcodes: D4
// -------------------------------------------------------------------------
// tmpA -> AH                     --E  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x0d45:
case 0x1d45:
{
    const uint16_t a = r[TA];
    writeByteReg(4, a);
    setupAlu<false, false>(Alu::Pass, TB);
    endRequested = true;
    break;
}

// Word: 122 (ROM line 122)
// Match: 00?.11010100.0110
// Native Opcodes: D4
// -------------------------------------------------------------------------
// SIGMA -> AL                    -W-  --
// -------------------------------------------------------------------------
case 0x0d46:
case 0x1d46:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(0, a);
    commitAluFlags();
    break;
}

// Word: 124 (ROM line 124)
// Match: 00?.11010101.0000
// Native Opcodes: D5
// -------------------------------------------------------------------------
// AL:AH -> tmpA   Q -> tmpB      ---  --
// -------------------------------------------------------------------------
case 0x0d50:
case 0x1d50:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = swappedAccumulator();
    const uint16_t b = readPrefetchForMicrocode();
    r[TA] = a;
    r[TB] = b;
    break;
}

// Word: 125 (ROM line 125)
// Match: 00?.11010101.0001
// Native Opcodes: D5
// -------------------------------------------------------------------------
// AL:AH -> tmpB                  ---  ALU ADD, tmpB
// -------------------------------------------------------------------------
case 0x0d51:
case 0x1d51:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = a;
    setupAlu<false, false>(Alu::Add, TB);
    break;
}

// Word: 126 (ROM line 126)
// Match: 00?.11010101.0010
// Native Opcodes: D5
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x0d52:
case 0x1d52:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    break;
}

// Word: 127 (ROM line 127)
// Match: 00?.11010101.0011
// Native Opcodes: D5
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0d53:
case 0x1d53:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 128 (ROM line 128)
// Match: 00?.11010101.0100
// Native Opcodes: D5
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU ADD, tmpB
// -------------------------------------------------------------------------
case 0x0d54:
case 0x1d54:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<false, false>(Alu::Add, TB);
    break;
}

// Word: 129 (ROM line 129)
// Match: 00?.11010101.0101
// Native Opcodes: D5
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x0d55:
case 0x1d55:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    break;
}

// Word: 12A (ROM line 12A)
// Match: 00?.11010101.0110
// Native Opcodes: D5
// -------------------------------------------------------------------------
// ZERO -> AH      A -> tmpA      --E  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0d56:
case 0x1d56:
{
    const uint16_t a = 0;
    const uint16_t b = r[AX];
    writeByteReg(4, a);
    r[TA] = b;
    setupAlu<false, false>(Alu::Add, TA);
    endRequested = true;
    break;
}

// Word: 12B (ROM line 12B)
// Match: 00?.11010101.0111
// Native Opcodes: D5
// -------------------------------------------------------------------------
// SIGMA -> AL                    -W-  --
// -------------------------------------------------------------------------
case 0x0d57:
case 0x1d57:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(0, a);
    commitAluFlags();
    break;
}

// Word: 12C (ROM line 12C)
// Match: 00?.11010111.0000
// Native Opcodes: D7
// -------------------------------------------------------------------------
// A -> tmpAL      B -> tmpB      ---  --
// -------------------------------------------------------------------------
case 0x0d70:
case 0x1d70:
{
    const uint16_t a = r[AX];
    const uint16_t b = r[BX];
    r[TA] = uint8_t(a);
    r[TB] = b;
    break;
}

// Word: 12D (ROM line 12D)
// Match: 00?.11010111.0001
// Native Opcodes: D7
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MR
// -------------------------------------------------------------------------
case 0x0d71:
case 0x1d71:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 12E (ROM line 12E)
// Match: 00?.11010111.0010
// Native Opcodes: D7
// -------------------------------------------------------------------------
// OPR -> AL                      F-E  --
// -------------------------------------------------------------------------
case 0x0d72:
case 0x1d72:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeByteReg(0, a);
    endRequested = true;
    break;
}

// Word: 130 (ROM line 130)
// Match: 00?.11011???.0000
// Native Opcodes: D8-DF
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0d80:
case 0x0d90:
case 0x0da0:
case 0x0db0:
case 0x0dc0:
case 0x0dd0:
case 0x0de0:
case 0x0df0:
case 0x1d80:
case 0x1d90:
case 0x1da0:
case 0x1db0:
case 0x1dc0:
case 0x1dd0:
case 0x1de0:
case 0x1df0:
{
    endRequested = true;
    break;
}

// Word: 134 (ROM line 134)
// Match: 00?.1110000?.0000
// Native Opcodes: E0-E1
// -------------------------------------------------------------------------
// C -> LC                        ---  --
// -------------------------------------------------------------------------
case 0x0e00:
case 0x0e10:
case 0x1e00:
case 0x1e10:
{
    const uint16_t a = r[CX];
    r[LC] = a;
    break;
}

// Word: 136 (ROM line 136)
// Match: 00?.1110000?.0010
// Native Opcodes: E0-E1
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  JUMP REP, 04
// -------------------------------------------------------------------------
case 0x0e02:
case 0x0e12:
case 0x1e02:
case 0x1e12:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const bool interrupt_pending = interruptPending();
    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(4);
    }
    break;
}

// Word: 137 (ROM line 137)
// Match: 00?.1110000?.0011
// Native Opcodes: E0-E1
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0e03:
case 0x0e13:
case 0x1e03:
case 0x1e13:
{
    endRequested = true;
    break;
}

// Word: 138 (ROM line 138)
// Match: 00?.111000??.0100
// Native Opcodes: E0-E3
// -------------------------------------------------------------------------
// LC -> C                        ---  --
// -------------------------------------------------------------------------
case 0x0e04:
case 0x0e14:
case 0x0e24:
case 0x0e34:
case 0x1e04:
case 0x1e14:
case 0x1e24:
case 0x1e34:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    break;
}

// Word: 139 (ROM line 139)
// Match: 00?.111000??.0101
// Native Opcodes: E0-E3
// -------------------------------------------------------------------------
// tmpA -> tmpBL                  ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0e05:
case 0x0e15:
case 0x0e25:
case 0x0e35:
case 0x1e05:
case 0x1e15:
case 0x1e25:
case 0x1e35:
{
    const uint16_t a = r[TA];
    r[TB] = extendByte(a);
    suspendPrefetch();
    break;
}

// Word: 13A (ROM line 13A)
// Match: 00?.111000??.0110
// Native Opcodes: E0-E3
// -------------------------------------------------------------------------
// PC -> tmpA                     ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0e06:
case 0x0e16:
case 0x0e26:
case 0x0e36:
case 0x1e06:
case 0x1e16:
case 0x1e26:
case 0x1e36:
{
    const uint16_t a = readPc();
    r[TA] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 13B (ROM line 13B)
// Match: 00?.111000??.0111
// Native Opcodes: E0-E3
// -------------------------------------------------------------------------
// SIGMA -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0e07:
case 0x0e17:
case 0x0e27:
case 0x0e37:
case 0x1e07:
case 0x1e17:
case 0x1e27:
case 0x1e37:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, true);
    endRequested = true;
    break;
}

// Word: 13C (ROM line 13C)
// Match: 00?.11100010.0000
// Native Opcodes: E2
// -------------------------------------------------------------------------
// Q -> tmpAL      C -> tmpB      ---  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x0e20:
case 0x1e20:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[CX];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec, TB);
    break;
}

// Word: 13D (ROM line 13D)
// Match: 00?.11100010.0001
// Native Opcodes: E2
// -------------------------------------------------------------------------
// SIGMA -> C                     ---  --
// -------------------------------------------------------------------------
case 0x0e21:
case 0x1e21:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[CX] = a;
    break;
}

// Word: 13E (ROM line 13E)
// Match: 00?.11100010.0010
// Native Opcodes: E2
// -------------------------------------------------------------------------
// C -> LC                        ---  JUMP JNZ, 05
// -------------------------------------------------------------------------
case 0x0e22:
case 0x1e22:
{
    const uint16_t a = r[CX];
    r[LC] = a;
    if (!aluZero()) {
        jumpLocal(5);
    }
    break;
}

// Word: 13F (ROM line 13F)
// Match: 00?.11100010.0011
// Native Opcodes: E2
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x0e23:
case 0x1e23:
{
    endRequested = true;
    break;
}

// Word: 140 (ROM line 140)
// Match: 00?.11100011.0000
// Native Opcodes: E3
// -------------------------------------------------------------------------
// Q -> tmpAL      C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x0e30:
case 0x1e30:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[CX];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 141 (ROM line 141)
// Match: 00?.11100011.0001
// Native Opcodes: E3
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  --
// -------------------------------------------------------------------------
case 0x0e31:
case 0x1e31:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    break;
}

// Word: 142 (ROM line 142)
// Match: 00?.11100011.0010
// Native Opcodes: E3
// -------------------------------------------------------------------------
//                                ---  JUMP JZ, 05
// -------------------------------------------------------------------------
case 0x0e32:
case 0x1e32:
{
    if (aluZero()) {
        jumpLocal(5);
    }
    break;
}

// Word: 143 (ROM line 143)
// Match: 00?.11100011.0011
// Native Opcodes: E3
// -------------------------------------------------------------------------
// C -> LC                        --E  --
// -------------------------------------------------------------------------
case 0x0e33:
case 0x1e33:
{
    const uint16_t a = r[CX];
    r[LC] = a;
    endRequested = true;
    break;
}

// Word: 144 (ROM line 144)
// Match: 00?.1110010?.0000
// Native Opcodes: E4-E5
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x0e40:
case 0x0e50:
case 0x1e40:
case 0x1e50:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 145 (ROM line 145)
// Match: 00?.1110010?.0001
// Native Opcodes: E4-E5
// -------------------------------------------------------------------------
// tmpA -> DP                     ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x0e41:
case 0x0e51:
case 0x1e41:
case 0x1e51:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 146 (ROM line 146)
// Match: 00?.1110010?.0010
// Native Opcodes: E4-E5
// -------------------------------------------------------------------------
// OPR -> OP1                     F-E  --
// -------------------------------------------------------------------------
case 0x0e42:
case 0x0e52:
case 0x1e42:
case 0x1e52:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 148 (ROM line 148)
// Match: 00?.1110011?.0000
// Native Opcodes: E6-E7
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x0e60:
case 0x0e70:
case 0x1e60:
case 0x1e70:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 149 (ROM line 149)
// Match: 00?.1110011?.0001
// Native Opcodes: E6-E7
// -------------------------------------------------------------------------
// OP1 -> OPR      SIGMA -> IND   --E  EC=MW, SR=None
// -------------------------------------------------------------------------
case 0x0e61:
case 0x0e71:
case 0x1e61:
case 0x1e71:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOperand(op1);
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::Io);
    endRequested = true;
    break;
}

// Word: 14C (ROM line 14C)
// Match: 00?.11101000.0000
// Native Opcodes: E8
// -------------------------------------------------------------------------
// Q -> tmpAL      SP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x0e80:
case 0x1e80:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[SP];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 14D (ROM line 14D)
// Match: 00?.11101000.0001
// Native Opcodes: E8
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x0e81:
case 0x1e81:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 14E (ROM line 14E)
// Match: 00?.11101000.0010
// Native Opcodes: E8
// -------------------------------------------------------------------------
// SIGMA -> SP     SIGMA -> IND   ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0e82:
case 0x1e82:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SP] = a;
    writeIndex(b);
    suspendPrefetch();
    break;
}

// Word: 14F (ROM line 14F)
// Match: 00?.11101000.0011
// Native Opcodes: E8
// -------------------------------------------------------------------------
// PC -> tmpB                     ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0e83:
case 0x1e83:
{
    const uint16_t a = readPc();
    r[TB] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 150 (ROM line 150)
// Match: 00?.11101000.0100
// Native Opcodes: E8
// -------------------------------------------------------------------------
// SIGMA -> PC                    ---  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0e84:
case 0x1e84:
{
    if (!prefetchFlushReady(false)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, false);
    break;
}

// Word: 151 (ROM line 151)
// Match: 00?.11101000.0101
// Native Opcodes: E8
// -------------------------------------------------------------------------
// tmpB -> OPR                    --E  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x0e85:
case 0x1e85:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TB];
    writeOpr(a);
    requestWrite(Segment::SS);
    endRequested = true;
    break;
}

// Word: 154 (ROM line 154)
// Match: 00?.11101001.0000
// Native Opcodes: E9
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0e90:
case 0x1e90:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 155 (ROM line 155)
// Match: 00?.11101001.0001
// Native Opcodes: E9
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  JUMP UNC, 02
// -------------------------------------------------------------------------
case 0x0e91:
case 0x1e91:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    if (true) {
        jumpLocal(2);
    }
    break;
}

// Word: 156 (ROM line 156)
// Match: 00?.11101001.0010
// Native Opcodes: E9
// -------------------------------------------------------------------------
// PC -> tmpA                     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0e92:
case 0x1e92:
{
    const uint16_t a = readPc();
    r[TA] = a;
    suspendPrefetch();
    break;
}

// Word: 157 (ROM line 157)
// Match: 00?.11101001.0011
// Native Opcodes: E9
// -------------------------------------------------------------------------
// SIGMA -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0e93:
case 0x1e93:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, true);
    endRequested = true;
    break;
}

// Word: 15C (ROM line 15C)
// Match: 00?.11101010.0000
// Native Opcodes: EA
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x0ea0:
case 0x1ea0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 15D (ROM line 15D)
// Match: 00?.11101010.0001
// Native Opcodes: EA
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x0ea1:
case 0x1ea1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 15E (ROM line 15E)
// Match: 00?.11101010.0010
// Native Opcodes: EA
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x0ea2:
case 0x1ea2:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 15F (ROM line 15F)
// Match: 00?.11101010.0011
// Native Opcodes: EA
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x0ea3:
case 0x1ea3:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 160 (ROM line 160)
// Match: 00?.11101010.0100
// Native Opcodes: EA
// -------------------------------------------------------------------------
// tmpA -> CS                     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0ea4:
case 0x1ea4:
{
    const uint16_t a = r[TA];
    writeSegment(CS, a);
    suspendPrefetch();
    break;
}

// Word: 161 (ROM line 161)
// Match: 00?.11101010.0101
// Native Opcodes: EA
// -------------------------------------------------------------------------
// tmpB -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0ea5:
case 0x1ea5:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TB];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 158 (ROM line 158)
// Match: 00?.11101011.0000
// Native Opcodes: EB
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x0eb0:
case 0x1eb0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 159 (ROM line 159)
// Match: 00?.11101011.0001
// Native Opcodes: EB
// -------------------------------------------------------------------------
//                                ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x0eb1:
case 0x1eb1:
{
    suspendPrefetch();
    break;
}

// Word: 15A (ROM line 15A)
// Match: 00?.11101011.0010
// Native Opcodes: EB
// -------------------------------------------------------------------------
// PC -> tmpA                     ---  --
// -------------------------------------------------------------------------
case 0x0eb2:
case 0x1eb2:
{
    const uint16_t a = readPc();
    r[TA] = a;
    break;
}

// Word: 15B (ROM line 15B)
// Match: 00?.11101011.0011
// Native Opcodes: EB
// -------------------------------------------------------------------------
// SIGMA -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x0eb3:
case 0x1eb3:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, true);
    endRequested = true;
    break;
}

// Word: 164 (ROM line 164)
// Match: 00?.1110110?.0000
// Native Opcodes: EC-ED
// -------------------------------------------------------------------------
// D -> DP                        ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x0ec0:
case 0x0ed0:
case 0x1ec0:
case 0x1ed0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DX];
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 165 (ROM line 165)
// Match: 00?.1110110?.0001
// Native Opcodes: EC-ED
// -------------------------------------------------------------------------
// OPR -> OP1                     F-E  --
// -------------------------------------------------------------------------
case 0x0ec1:
case 0x0ed1:
case 0x1ec1:
case 0x1ed1:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 168 (ROM line 168)
// Match: 00?.1110111?.0000
// Native Opcodes: EE-EF
// -------------------------------------------------------------------------
// D -> DP                        --E  EC=MW, SR=None
// -------------------------------------------------------------------------
case 0x0ee0:
case 0x0ef0:
case 0x1ee0:
case 0x1ef0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DX];
    writeIndex(a);
    requestWrite(Segment::Io);
    endRequested = true;
    break;
}

// Word: 169 (ROM line 169)
// Match: 00?.1110111?.0001
// Native Opcodes: EE-EF
// -------------------------------------------------------------------------
// OP1 -> OPR                     ---  --
// -------------------------------------------------------------------------
case 0x0ee1:
case 0x0ef1:
case 0x1ee1:
case 0x1ef1:
{
    const uint16_t a = readOperand(op1);
    writeOpr(a);
    break;
}

// Word: 294 (ROM line 298)
// Match: 001.0110110?.0000
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// C -> LC         C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x16c0:
case 0x16d0:
{
    const uint16_t a = r[CX];
    const uint16_t b = r[CX];
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 295 (ROM line 299)
// Match: 001.0110110?.0001
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x16c1:
case 0x16d1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 296 (ROM line 29A)
// Match: 001.0110110?.0010
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// DIRSZ -> tmpC                  ---  JUMP JZ, 07
// -------------------------------------------------------------------------
case 0x16c2:
case 0x16d2:
{
    const uint16_t a = directionStep();
    r[TC] = a;
    if (aluZero()) {
        jumpLocal(7);
    }
    break;
}

// Word: 297 (ROM line 29B)
// Match: 001.0110110?.0011
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// D -> DP                        ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x16c3:
case 0x16d3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DX];
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 299 (ROM line 29D)
// Match: 001.0110110?.0101
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// DI -> DP        DI -> tmpB     ---  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x16c5:
case 0x16d5:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    const uint16_t b = r[DI];
    writeIndex(a);
    r[TB] = b;
    requestWrite(Segment::ES);
    break;
}

// Word: 29A (ROM line 29E)
// Match: 001.0110110?.0110
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x16c6:
case 0x16d6:
{
    const bool interrupt_pending = interruptPending();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 29B (ROM line 29F)
// Match: 001.0110110?.0111
// Native Opcodes: 6C-6D
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x16c7:
case 0x16d7:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 2A0 (ROM line 2A4)
// Match: 001.0110111?.0000
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// C -> LC         C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x16e0:
case 0x16f0:
{
    const uint16_t a = r[CX];
    const uint16_t b = r[CX];
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 2A1 (ROM line 2A5)
// Match: 001.0110111?.0001
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x16e1:
case 0x16f1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 2A2 (ROM line 2A6)
// Match: 001.0110111?.0010
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// DIRSZ -> tmpC                  ---  JUMP JZ, 07
// -------------------------------------------------------------------------
case 0x16e2:
case 0x16f2:
{
    const uint16_t a = directionStep();
    r[TC] = a;
    if (aluZero()) {
        jumpLocal(7);
    }
    break;
}

// Word: 2A3 (ROM line 2A7)
// Match: 001.0110111?.0011
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// SI -> DP        SI -> tmpB     ---  EC=MR
// -------------------------------------------------------------------------
case 0x16e3:
case 0x16f3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    const uint16_t b = r[SI];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 2A4 (ROM line 2A8)
// Match: 001.0110111?.0100
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  --
// -------------------------------------------------------------------------
case 0x16e4:
case 0x16f4:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    break;
}

// Word: 2A5 (ROM line 2A9)
// Match: 001.0110111?.0101
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// D -> DP                        ---  EC=MW, SR=None
// -------------------------------------------------------------------------
case 0x16e5:
case 0x16f5:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DX];
    writeIndex(a);
    requestWrite(Segment::Io);
    break;
}

// Word: 2A6 (ROM line 2AA)
// Match: 001.0110111?.0110
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
//                                ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x16e6:
case 0x16f6:
{
    const bool interrupt_pending = interruptPending();
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 2A7 (ROM line 2AB)
// Match: 001.0110111?.0111
// Native Opcodes: 6E-6F
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x16e7:
case 0x16f7:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 094 (ROM line 094)
// Match: 001.1010010?.0000
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// C -> LC         C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x1a40:
case 0x1a50:
{
    const uint16_t a = r[CX];
    const uint16_t b = r[CX];
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 095 (ROM line 095)
// Match: 001.1010010?.0001
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x1a41:
case 0x1a51:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 096 (ROM line 096)
// Match: 001.1010010?.0010
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// DIRSZ -> tmpC                  ---  JUMP JZ, 07
// -------------------------------------------------------------------------
case 0x1a42:
case 0x1a52:
{
    const uint16_t a = directionStep();
    r[TC] = a;
    if (aluZero()) {
        jumpLocal(7);
    }
    break;
}

// Word: 097 (ROM line 097)
// Match: 001.1010010?.0011
// Native Opcodes: A4-A5
// -------------------------------------------------------------------------
// SI -> DP        DI -> tmpB     ---  EC=MR
// -------------------------------------------------------------------------
case 0x1a43:
case 0x1a53:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    const uint16_t b = r[DI];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 0A4 (ROM line 0A4)
// Match: 001.1010?11?.0000
// Native Opcodes: A6-A7, AE-AF
// -------------------------------------------------------------------------
// C -> LC         C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x1a60:
case 0x1a70:
case 0x1ae0:
case 0x1af0:
{
    const uint16_t a = r[CX];
    const uint16_t b = r[CX];
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 0A5 (ROM line 0A5)
// Match: 001.1010?11?.0001
// Native Opcodes: A6-A7, AE-AF
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   SIGMA -> NULL  ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x1a61:
case 0x1a71:
case 0x1ae1:
case 0x1af1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = directionStep();
    const uint16_t b = sigma;
    r[TC] = a;
    (void)b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 0A6 (ROM line 0A6)
// Match: 001.1010?11?.0010
// Native Opcodes: A6-A7, AE-AF
// -------------------------------------------------------------------------
//                                ---  JUMP JZ, 0B
// -------------------------------------------------------------------------
case 0x1a62:
case 0x1a72:
case 0x1ae2:
case 0x1af2:
{
    if (aluZero()) {
        jumpLocal(11);
    }
    break;
}

// Word: 0A7 (ROM line 0A7)
// Match: 001.1010?11?.0011
// Native Opcodes: A6-A7, AE-AF
// -------------------------------------------------------------------------
// DI -> DP        DI -> tmpB     ---  EC=MR, SR=ES
// -------------------------------------------------------------------------
case 0x1a63:
case 0x1a73:
case 0x1ae3:
case 0x1af3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    const uint16_t b = r[DI];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::ES);
    break;
}

// Word: 0A8 (ROM line 0A8)
// Match: 001.1010011?.0100
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// SIGMA -> DI     SI -> tmpB     ---  --
// -------------------------------------------------------------------------
case 0x1a64:
case 0x1a74:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = r[SI];
    r[DI] = a;
    r[TB] = b;
    break;
}

// Word: 0A9 (ROM line 0A9)
// Match: 001.1010011?.0101
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// SI -> DP        SIGMA -> tmpB  ---  EC=MR
// -------------------------------------------------------------------------
case 0x1a65:
case 0x1a75:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[SI];
    const uint16_t b = sigma;
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 0AA (ROM line 0AA)
// Match: 001.1010011?.0110
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// OPR -> tmpA                    F--  --
// -------------------------------------------------------------------------
case 0x1a66:
case 0x1a76:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    break;
}

// Word: 0AB (ROM line 0AB)
// Match: 001.1010011?.0111
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// tmpB -> SI                     ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x1a67:
case 0x1a77:
{
    const uint16_t a = r[TB];
    r[SI] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 0AC (ROM line 0AC)
// Match: 001.1010011?.1000
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  --
// -------------------------------------------------------------------------
case 0x1a68:
case 0x1a78:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    break;
}

// Word: 0AD (ROM line 0AD)
// Match: 001.1010011?.1001
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x1a69:
case 0x1a79:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    setupAlu<false, true>(Alu::Add, TC);
    break;
}

// Word: 0AE (ROM line 0AE)
// Match: 001.1010011?.1010
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
//                                ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x1a6a:
case 0x1a7a:
{
    const bool interrupt_pending = interruptPending();
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 0AF (ROM line 0AF)
// Match: 001.1010011?.1011
// Native Opcodes: A6-A7
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x1a6b:
case 0x1a7b:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 0BC (ROM line 0BC)
// Match: 001.1010101?.0000
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// C -> LC         C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x1aa0:
case 0x1ab0:
{
    const uint16_t a = r[CX];
    const uint16_t b = r[CX];
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 0BD (ROM line 0BD)
// Match: 001.1010101?.0001
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   SIGMA -> NULL  ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x1aa1:
case 0x1ab1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = directionStep();
    const uint16_t b = sigma;
    r[TC] = a;
    (void)b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 0BE (ROM line 0BE)
// Match: 001.1010101?.0010
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// OP1 -> OPR                     ---  JUMP JZ, 05
// -------------------------------------------------------------------------
case 0x1aa2:
case 0x1ab2:
{
    const uint16_t a = readOperand(op1);
    writeOpr(a);
    if (aluZero()) {
        jumpLocal(5);
    }
    break;
}

// Word: 0BF (ROM line 0BF)
// Match: 001.1010101?.0011
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// DI -> DP        DI -> tmpB     ---  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x1aa3:
case 0x1ab3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    const uint16_t b = r[DI];
    writeIndex(a);
    r[TB] = b;
    requestWrite(Segment::ES);
    break;
}

// Word: 0C0 (ROM line 0C0)
// Match: 001.1010101?.0100
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x1aa4:
case 0x1ab4:
{
    const bool interrupt_pending = interruptPending();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 0C1 (ROM line 0C1)
// Match: 001.1010101?.0101
// Native Opcodes: AA-AB
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x1aa5:
case 0x1ab5:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 0C8 (ROM line 0C8)
// Match: 001.1010110?.0000
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// C -> LC         C -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x1ac0:
case 0x1ad0:
{
    const uint16_t a = r[CX];
    const uint16_t b = r[CX];
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 0C9 (ROM line 0C9)
// Match: 001.1010110?.0001
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// DIRSZ -> tmpC   SIGMA -> NULL  ---  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x1ac1:
case 0x1ad1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = directionStep();
    const uint16_t b = sigma;
    r[TC] = a;
    (void)b;
    setupAlu<false, false>(Alu::Add, TC);
    break;
}

// Word: 0CA (ROM line 0CA)
// Match: 001.1010110?.0010
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
//                                ---  JUMP JZ, 07
// -------------------------------------------------------------------------
case 0x1ac2:
case 0x1ad2:
{
    if (aluZero()) {
        jumpLocal(7);
    }
    break;
}

// Word: 0CB (ROM line 0CB)
// Match: 001.1010110?.0011
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// SI -> DP        SI -> tmpB     ---  EC=MR
// -------------------------------------------------------------------------
case 0x1ac3:
case 0x1ad3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    const uint16_t b = r[SI];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 0CC (ROM line 0CC)
// Match: 001.1010110?.0100
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  --
// -------------------------------------------------------------------------
case 0x1ac4:
case 0x1ad4:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    break;
}

// Word: 0CD (ROM line 0CD)
// Match: 001.1010110?.0101
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// OPR -> OP1                     F--  --
// -------------------------------------------------------------------------
case 0x1ac5:
case 0x1ad5:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op1, a);
    break;
}

// Word: 0CE (ROM line 0CE)
// Match: 001.1010110?.0110
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
//                                ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x1ac6:
case 0x1ad6:
{
    const bool interrupt_pending = interruptPending();
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 0CF (ROM line 0CF)
// Match: 001.1010110?.0111
// Native Opcodes: AC-AD
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x1ac7:
case 0x1ad7:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 0D8 (ROM line 0D8)
// Match: 001.1010111?.0100
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x1ae4:
case 0x1af4:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 0D9 (ROM line 0D9)
// Match: 001.1010111?.0101
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  --
// -------------------------------------------------------------------------
case 0x1ae5:
case 0x1af5:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    break;
}

// Word: 0DA (ROM line 0DA)
// Match: 001.1010111?.0110
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// OPR -> tmpA                    F--  --
// -------------------------------------------------------------------------
case 0x1ae6:
case 0x1af6:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    break;
}

// Word: 0DB (ROM line 0DB)
// Match: 001.1010111?.0111
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  ALU ADD, tmpC
// -------------------------------------------------------------------------
case 0x1ae7:
case 0x1af7:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    setupAlu<false, true>(Alu::Add, TC);
    break;
}

// Word: 0DC (ROM line 0DC)
// Match: 001.1010111?.1000
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
//                                ---  JUMP REP, 03
// -------------------------------------------------------------------------
case 0x1ae8:
case 0x1af8:
{
    const bool interrupt_pending = interruptPending();
    if (repeatCondition(interrupt_pending)) {
        jumpLocal(3);
    }
    break;
}

// Word: 0DF (ROM line 0DF)
// Match: 001.1010111?.1011
// Native Opcodes: AE-AF
// -------------------------------------------------------------------------
// LC -> C                        ---  CALL REP (08) -> 7400 [Line 21C]
// -------------------------------------------------------------------------
case 0x1aeb:
case 0x1afb:
{
    const uint16_t a = r[LC];
    r[CX] = a;
    jumpFar(0x7400);
    break;
}

// Word: 16C (ROM line 16C)
// Match: 010.??00????.0000
// Native Opcodes: F6-F7 /0, F6-F7 /1
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  JUMP JNW, 02
// -------------------------------------------------------------------------
case 0x2000:
case 0x2010:
case 0x2020:
case 0x2030:
case 0x2040:
case 0x2050:
case 0x2060:
case 0x2070:
case 0x2080:
case 0x2090:
case 0x20a0:
case 0x20b0:
case 0x20c0:
case 0x20d0:
case 0x20e0:
case 0x20f0:
case 0x2400:
case 0x2410:
case 0x2420:
case 0x2430:
case 0x2440:
case 0x2450:
case 0x2460:
case 0x2470:
case 0x2480:
case 0x2490:
case 0x24a0:
case 0x24b0:
case 0x24c0:
case 0x24d0:
case 0x24e0:
case 0x24f0:
case 0x2800:
case 0x2810:
case 0x2820:
case 0x2830:
case 0x2840:
case 0x2850:
case 0x2860:
case 0x2870:
case 0x2880:
case 0x2890:
case 0x28a0:
case 0x28b0:
case 0x28c0:
case 0x28d0:
case 0x28e0:
case 0x28f0:
case 0x2c00:
case 0x2c10:
case 0x2c20:
case 0x2c30:
case 0x2c40:
case 0x2c50:
case 0x2c60:
case 0x2c70:
case 0x2c80:
case 0x2c90:
case 0x2ca0:
case 0x2cb0:
case 0x2cc0:
case 0x2cd0:
case 0x2ce0:
case 0x2cf0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    if (shortImmediate()) {
        jumpLocal(2);
    }
    break;
}

// Word: 16D (ROM line 16D)
// Match: 010.??00????.0001
// Native Opcodes: F6-F7 /0, F6-F7 /1
// -------------------------------------------------------------------------
// Q -> tmpBH                     ---  --
// -------------------------------------------------------------------------
case 0x2001:
case 0x2011:
case 0x2021:
case 0x2031:
case 0x2041:
case 0x2051:
case 0x2061:
case 0x2071:
case 0x2081:
case 0x2091:
case 0x20a1:
case 0x20b1:
case 0x20c1:
case 0x20d1:
case 0x20e1:
case 0x20f1:
case 0x2401:
case 0x2411:
case 0x2421:
case 0x2431:
case 0x2441:
case 0x2451:
case 0x2461:
case 0x2471:
case 0x2481:
case 0x2491:
case 0x24a1:
case 0x24b1:
case 0x24c1:
case 0x24d1:
case 0x24e1:
case 0x24f1:
case 0x2801:
case 0x2811:
case 0x2821:
case 0x2831:
case 0x2841:
case 0x2851:
case 0x2861:
case 0x2871:
case 0x2881:
case 0x2891:
case 0x28a1:
case 0x28b1:
case 0x28c1:
case 0x28d1:
case 0x28e1:
case 0x28f1:
case 0x2c01:
case 0x2c11:
case 0x2c21:
case 0x2c31:
case 0x2c41:
case 0x2c51:
case 0x2c61:
case 0x2c71:
case 0x2c81:
case 0x2c91:
case 0x2ca1:
case 0x2cb1:
case 0x2cc1:
case 0x2cd1:
case 0x2ce1:
case 0x2cf1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    break;
}

// Word: 16E (ROM line 16E)
// Match: 010.??00????.0010
// Native Opcodes: F6-F7 /0, F6-F7 /1
// -------------------------------------------------------------------------
// OP1 -> tmpA                    --E  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x2002:
case 0x2012:
case 0x2022:
case 0x2032:
case 0x2042:
case 0x2052:
case 0x2062:
case 0x2072:
case 0x2082:
case 0x2092:
case 0x20a2:
case 0x20b2:
case 0x20c2:
case 0x20d2:
case 0x20e2:
case 0x20f2:
case 0x2402:
case 0x2412:
case 0x2422:
case 0x2432:
case 0x2442:
case 0x2452:
case 0x2462:
case 0x2472:
case 0x2482:
case 0x2492:
case 0x24a2:
case 0x24b2:
case 0x24c2:
case 0x24d2:
case 0x24e2:
case 0x24f2:
case 0x2802:
case 0x2812:
case 0x2822:
case 0x2832:
case 0x2842:
case 0x2852:
case 0x2862:
case 0x2872:
case 0x2882:
case 0x2892:
case 0x28a2:
case 0x28b2:
case 0x28c2:
case 0x28d2:
case 0x28e2:
case 0x28f2:
case 0x2c02:
case 0x2c12:
case 0x2c22:
case 0x2c32:
case 0x2c42:
case 0x2c52:
case 0x2c62:
case 0x2c72:
case 0x2c82:
case 0x2c92:
case 0x2ca2:
case 0x2cb2:
case 0x2cc2:
case 0x2cd2:
case 0x2ce2:
case 0x2cf2:
{
    const uint16_t a = readOperand(op1);
    r[TA] = a;
    setupAlu<false, false>(Alu::And, TA);
    endRequested = true;
    break;
}

// Word: 16F (ROM line 16F)
// Match: 010.??00????.0011
// Native Opcodes: F6-F7 /0, F6-F7 /1
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x2003:
case 0x2013:
case 0x2023:
case 0x2033:
case 0x2043:
case 0x2053:
case 0x2063:
case 0x2073:
case 0x2083:
case 0x2093:
case 0x20a3:
case 0x20b3:
case 0x20c3:
case 0x20d3:
case 0x20e3:
case 0x20f3:
case 0x2403:
case 0x2413:
case 0x2423:
case 0x2433:
case 0x2443:
case 0x2453:
case 0x2463:
case 0x2473:
case 0x2483:
case 0x2493:
case 0x24a3:
case 0x24b3:
case 0x24c3:
case 0x24d3:
case 0x24e3:
case 0x24f3:
case 0x2803:
case 0x2813:
case 0x2823:
case 0x2833:
case 0x2843:
case 0x2853:
case 0x2863:
case 0x2873:
case 0x2883:
case 0x2893:
case 0x28a3:
case 0x28b3:
case 0x28c3:
case 0x28d3:
case 0x28e3:
case 0x28f3:
case 0x2c03:
case 0x2c13:
case 0x2c23:
case 0x2c33:
case 0x2c43:
case 0x2c53:
case 0x2c63:
case 0x2c73:
case 0x2c83:
case 0x2c93:
case 0x2ca3:
case 0x2cb3:
case 0x2cc3:
case 0x2cd3:
case 0x2ce3:
case 0x2cf3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 174 (ROM line 174)
// Match: 010.??010???.0000
// Native Opcodes: F6-F7 /2
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  ALU XI, tmpB
// -------------------------------------------------------------------------
case 0x2100:
case 0x2110:
case 0x2120:
case 0x2130:
case 0x2140:
case 0x2150:
case 0x2160:
case 0x2170:
case 0x2500:
case 0x2510:
case 0x2520:
case 0x2530:
case 0x2540:
case 0x2550:
case 0x2560:
case 0x2570:
case 0x2900:
case 0x2910:
case 0x2920:
case 0x2930:
case 0x2940:
case 0x2950:
case 0x2960:
case 0x2970:
case 0x2d00:
case 0x2d10:
case 0x2d20:
case 0x2d30:
case 0x2d40:
case 0x2d50:
case 0x2d60:
case 0x2d70:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupDecodedAlu<false, false>(TB);
    break;
}

// Word: 175 (ROM line 175)
// Match: 010.??010???.0001
// Native Opcodes: F6-F7 /2
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x2101:
case 0x2111:
case 0x2121:
case 0x2131:
case 0x2141:
case 0x2151:
case 0x2161:
case 0x2171:
case 0x2501:
case 0x2511:
case 0x2521:
case 0x2531:
case 0x2541:
case 0x2551:
case 0x2561:
case 0x2571:
case 0x2901:
case 0x2911:
case 0x2921:
case 0x2931:
case 0x2941:
case 0x2951:
case 0x2961:
case 0x2971:
case 0x2d01:
case 0x2d11:
case 0x2d21:
case 0x2d31:
case 0x2d41:
case 0x2d51:
case 0x2d61:
case 0x2d71:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 170 (ROM line 170)
// Match: 010.??011???.0000
// Native Opcodes: F6-F7 /3
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  ALU XI, tmpB
// -------------------------------------------------------------------------
case 0x2180:
case 0x2190:
case 0x21a0:
case 0x21b0:
case 0x21c0:
case 0x21d0:
case 0x21e0:
case 0x21f0:
case 0x2580:
case 0x2590:
case 0x25a0:
case 0x25b0:
case 0x25c0:
case 0x25d0:
case 0x25e0:
case 0x25f0:
case 0x2980:
case 0x2990:
case 0x29a0:
case 0x29b0:
case 0x29c0:
case 0x29d0:
case 0x29e0:
case 0x29f0:
case 0x2d80:
case 0x2d90:
case 0x2da0:
case 0x2db0:
case 0x2dc0:
case 0x2dd0:
case 0x2de0:
case 0x2df0:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupDecodedAlu<false, false>(TB);
    break;
}

// Word: 171 (ROM line 171)
// Match: 010.??011???.0001
// Native Opcodes: F6-F7 /3
// -------------------------------------------------------------------------
// SIGMA -> OP1                   -WE  EC=COMMIT
// -------------------------------------------------------------------------
case 0x2181:
case 0x2191:
case 0x21a1:
case 0x21b1:
case 0x21c1:
case 0x21d1:
case 0x21e1:
case 0x21f1:
case 0x2581:
case 0x2591:
case 0x25a1:
case 0x25b1:
case 0x25c1:
case 0x25d1:
case 0x25e1:
case 0x25f1:
case 0x2981:
case 0x2991:
case 0x29a1:
case 0x29b1:
case 0x29c1:
case 0x29d1:
case 0x29e1:
case 0x29f1:
case 0x2d81:
case 0x2d91:
case 0x2da1:
case 0x2db1:
case 0x2dc1:
case 0x2dd1:
case 0x2de1:
case 0x2df1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitAluFlags();
    commitOperand();
    endRequested = true;
    break;
}

// Word: 178 (ROM line 178)
// Match: 010.??100???.0000
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// OP1 -> tmpC     ZERO -> tmpB   ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x2200:
case 0x2210:
case 0x2220:
case 0x2230:
case 0x2240:
case 0x2250:
case 0x2260:
case 0x2270:
case 0x2600:
case 0x2610:
case 0x2620:
case 0x2630:
case 0x2640:
case 0x2650:
case 0x2660:
case 0x2670:
case 0x2a00:
case 0x2a10:
case 0x2a20:
case 0x2a30:
case 0x2a40:
case 0x2a50:
case 0x2a60:
case 0x2a70:
case 0x2e00:
case 0x2e10:
case 0x2e20:
case 0x2e30:
case 0x2e40:
case 0x2e50:
case 0x2e60:
case 0x2e70:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = 0;
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 179 (ROM line 179)
// Match: 010.??100???.0001
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// A -> tmpA                      ---  --
// -------------------------------------------------------------------------
case 0x2201:
case 0x2211:
case 0x2221:
case 0x2231:
case 0x2241:
case 0x2251:
case 0x2261:
case 0x2271:
case 0x2601:
case 0x2611:
case 0x2621:
case 0x2631:
case 0x2641:
case 0x2651:
case 0x2661:
case 0x2671:
case 0x2a01:
case 0x2a11:
case 0x2a21:
case 0x2a31:
case 0x2a41:
case 0x2a51:
case 0x2a61:
case 0x2a71:
case 0x2e01:
case 0x2e11:
case 0x2e21:
case 0x2e31:
case 0x2e41:
case 0x2e51:
case 0x2e61:
case 0x2e71:
{
    const uint16_t a = r[AX];
    r[TA] = a;
    break;
}

// Word: 17A (ROM line 17A)
// Match: 010.??100???.0010
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// 8 -> LC                        ---  JUMP JNW, 04
// -------------------------------------------------------------------------
case 0x2202:
case 0x2212:
case 0x2222:
case 0x2232:
case 0x2242:
case 0x2252:
case 0x2262:
case 0x2272:
case 0x2602:
case 0x2612:
case 0x2622:
case 0x2632:
case 0x2642:
case 0x2652:
case 0x2662:
case 0x2672:
case 0x2a02:
case 0x2a12:
case 0x2a22:
case 0x2a32:
case 0x2a42:
case 0x2a52:
case 0x2a62:
case 0x2a72:
case 0x2e02:
case 0x2e12:
case 0x2e22:
case 0x2e32:
case 0x2e42:
case 0x2e52:
case 0x2e62:
case 0x2e72:
{
    const uint16_t a = 8;
    r[LC] = a;
    if (shortImmediate()) {
        jumpLocal(4);
    }
    break;
}

// Word: 17B (ROM line 17B)
// Match: 010.??100???.0011
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// 16 -> LC                       ---  --
// -------------------------------------------------------------------------
case 0x2203:
case 0x2213:
case 0x2223:
case 0x2233:
case 0x2243:
case 0x2253:
case 0x2263:
case 0x2273:
case 0x2603:
case 0x2613:
case 0x2623:
case 0x2633:
case 0x2643:
case 0x2653:
case 0x2663:
case 0x2673:
case 0x2a03:
case 0x2a13:
case 0x2a23:
case 0x2a33:
case 0x2a43:
case 0x2a53:
case 0x2a63:
case 0x2a73:
case 0x2e03:
case 0x2e13:
case 0x2e23:
case 0x2e33:
case 0x2e43:
case 0x2e53:
case 0x2e63:
case 0x2e73:
{
    const uint16_t a = 16;
    r[LC] = a;
    break;
}

// Word: 17C (ROM line 17C)
// Match: 010.??100???.0100
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x2204:
case 0x2214:
case 0x2224:
case 0x2234:
case 0x2244:
case 0x2254:
case 0x2264:
case 0x2274:
case 0x2604:
case 0x2614:
case 0x2624:
case 0x2634:
case 0x2644:
case 0x2654:
case 0x2664:
case 0x2674:
case 0x2a04:
case 0x2a14:
case 0x2a24:
case 0x2a34:
case 0x2a44:
case 0x2a54:
case 0x2a64:
case 0x2a74:
case 0x2e04:
case 0x2e14:
case 0x2e24:
case 0x2e34:
case 0x2e44:
case 0x2e54:
case 0x2e64:
case 0x2e74:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 17D (ROM line 17D)
// Match: 010.??100???.0101
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
//                                ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x2205:
case 0x2215:
case 0x2225:
case 0x2235:
case 0x2245:
case 0x2255:
case 0x2265:
case 0x2275:
case 0x2605:
case 0x2615:
case 0x2625:
case 0x2635:
case 0x2645:
case 0x2655:
case 0x2665:
case 0x2675:
case 0x2a05:
case 0x2a15:
case 0x2a25:
case 0x2a35:
case 0x2a45:
case 0x2a55:
case 0x2a65:
case 0x2a75:
case 0x2e05:
case 0x2e15:
case 0x2e25:
case 0x2e35:
case 0x2e45:
case 0x2e55:
case 0x2e65:
case 0x2e75:
{
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 17E (ROM line 17E)
// Match: 010.??100???.0110
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// tmpA -> A                      ---  JUMP JNW, 08
// -------------------------------------------------------------------------
case 0x2206:
case 0x2216:
case 0x2226:
case 0x2236:
case 0x2246:
case 0x2256:
case 0x2266:
case 0x2276:
case 0x2606:
case 0x2616:
case 0x2626:
case 0x2636:
case 0x2646:
case 0x2656:
case 0x2666:
case 0x2676:
case 0x2a06:
case 0x2a16:
case 0x2a26:
case 0x2a36:
case 0x2a46:
case 0x2a56:
case 0x2a66:
case 0x2a76:
case 0x2e06:
case 0x2e16:
case 0x2e26:
case 0x2e36:
case 0x2e46:
case 0x2e56:
case 0x2e66:
case 0x2e76:
{
    const uint16_t a = r[TA];
    r[AX] = a;
    if (shortImmediate()) {
        jumpLocal(8);
    }
    break;
}

// Word: 17F (ROM line 17F)
// Match: 010.??100???.0111
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// tmpB -> D       SIGMA -> NULL  ---  CALL MUL2 (05) -> 7280 [Line 204]
// -------------------------------------------------------------------------
case 0x2207:
case 0x2217:
case 0x2227:
case 0x2237:
case 0x2247:
case 0x2257:
case 0x2267:
case 0x2277:
case 0x2607:
case 0x2617:
case 0x2627:
case 0x2637:
case 0x2647:
case 0x2657:
case 0x2667:
case 0x2677:
case 0x2a07:
case 0x2a17:
case 0x2a27:
case 0x2a37:
case 0x2a47:
case 0x2a57:
case 0x2a67:
case 0x2a77:
case 0x2e07:
case 0x2e17:
case 0x2e27:
case 0x2e37:
case 0x2e47:
case 0x2e57:
case 0x2e67:
case 0x2e77:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TB];
    const uint16_t b = sigma;
    r[DX] = a;
    (void)b;
    jumpFar(0x7280);
    break;
}

// Word: 180 (ROM line 180)
// Match: 010.??100???.1000
// Native Opcodes: F6-F7 /4
// -------------------------------------------------------------------------
// tmpB -> AH      SIGMA -> NULL  ---  CALL MUL2 (05) -> 7280 [Line 204]
// -------------------------------------------------------------------------
case 0x2208:
case 0x2218:
case 0x2228:
case 0x2238:
case 0x2248:
case 0x2258:
case 0x2268:
case 0x2278:
case 0x2608:
case 0x2618:
case 0x2628:
case 0x2638:
case 0x2648:
case 0x2658:
case 0x2668:
case 0x2678:
case 0x2a08:
case 0x2a18:
case 0x2a28:
case 0x2a38:
case 0x2a48:
case 0x2a58:
case 0x2a68:
case 0x2a78:
case 0x2e08:
case 0x2e18:
case 0x2e28:
case 0x2e38:
case 0x2e48:
case 0x2e58:
case 0x2e68:
case 0x2e78:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TB];
    const uint16_t b = sigma;
    writeByteReg(4, a);
    (void)b;
    jumpFar(0x7280);
    break;
}

// Word: 184 (ROM line 184)
// Match: 010.??101???.0000
// Native Opcodes: F6-F7 /5
// -------------------------------------------------------------------------
// OP1 -> tmpA     A -> tmpB      ---  ALU MULDIV, tmpB
// -------------------------------------------------------------------------
case 0x2280:
case 0x2290:
case 0x22a0:
case 0x22b0:
case 0x22c0:
case 0x22d0:
case 0x22e0:
case 0x22f0:
case 0x2680:
case 0x2690:
case 0x26a0:
case 0x26b0:
case 0x26c0:
case 0x26d0:
case 0x26e0:
case 0x26f0:
case 0x2a80:
case 0x2a90:
case 0x2aa0:
case 0x2ab0:
case 0x2ac0:
case 0x2ad0:
case 0x2ae0:
case 0x2af0:
case 0x2e80:
case 0x2e90:
case 0x2ea0:
case 0x2eb0:
case 0x2ec0:
case 0x2ed0:
case 0x2ee0:
case 0x2ef0:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[AX];
    r[TA] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::MulDiv, TB);
    break;
}

// Word: 185 (ROM line 185)
// Match: 010.??101???.0001
// Native Opcodes: F6-F7 /5
// -------------------------------------------------------------------------
//                                ---  CALL IMUL (06) -> 7300 [Line 208]
// -------------------------------------------------------------------------
case 0x2281:
case 0x2291:
case 0x22a1:
case 0x22b1:
case 0x22c1:
case 0x22d1:
case 0x22e1:
case 0x22f1:
case 0x2681:
case 0x2691:
case 0x26a1:
case 0x26b1:
case 0x26c1:
case 0x26d1:
case 0x26e1:
case 0x26f1:
case 0x2a81:
case 0x2a91:
case 0x2aa1:
case 0x2ab1:
case 0x2ac1:
case 0x2ad1:
case 0x2ae1:
case 0x2af1:
case 0x2e81:
case 0x2e91:
case 0x2ea1:
case 0x2eb1:
case 0x2ec1:
case 0x2ed1:
case 0x2ee1:
case 0x2ef1:
{
    jumpFar(0x7300);
    break;
}

// Word: 188 (ROM line 188)
// Match: 010.??110???.0000
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// OP1 -> tmpC     A -> tmpA      ---  ALU SUB, tmpC
// -------------------------------------------------------------------------
case 0x2300:
case 0x2310:
case 0x2320:
case 0x2330:
case 0x2340:
case 0x2350:
case 0x2360:
case 0x2370:
case 0x2700:
case 0x2710:
case 0x2720:
case 0x2730:
case 0x2740:
case 0x2750:
case 0x2760:
case 0x2770:
case 0x2b00:
case 0x2b10:
case 0x2b20:
case 0x2b30:
case 0x2b40:
case 0x2b50:
case 0x2b60:
case 0x2b70:
case 0x2f00:
case 0x2f10:
case 0x2f20:
case 0x2f30:
case 0x2f40:
case 0x2f50:
case 0x2f60:
case 0x2f70:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[AX];
    r[TC] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::Sub, TC);
    break;
}

// Word: 189 (ROM line 189)
// Match: 010.??110???.0001
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// D -> tmpB                      ---  JUMP JNW, 04
// -------------------------------------------------------------------------
case 0x2301:
case 0x2311:
case 0x2321:
case 0x2331:
case 0x2341:
case 0x2351:
case 0x2361:
case 0x2371:
case 0x2701:
case 0x2711:
case 0x2721:
case 0x2731:
case 0x2741:
case 0x2751:
case 0x2761:
case 0x2771:
case 0x2b01:
case 0x2b11:
case 0x2b21:
case 0x2b31:
case 0x2b41:
case 0x2b51:
case 0x2b61:
case 0x2b71:
case 0x2f01:
case 0x2f11:
case 0x2f21:
case 0x2f31:
case 0x2f41:
case 0x2f51:
case 0x2f61:
case 0x2f71:
{
    const uint16_t a = r[DX];
    r[TB] = a;
    if (shortImmediate()) {
        jumpLocal(4);
    }
    break;
}

// Word: 18A (ROM line 18A)
// Match: 010.??110???.0010
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// 16 -> LC                       ---  --
// -------------------------------------------------------------------------
case 0x2302:
case 0x2312:
case 0x2322:
case 0x2332:
case 0x2342:
case 0x2352:
case 0x2362:
case 0x2372:
case 0x2702:
case 0x2712:
case 0x2722:
case 0x2732:
case 0x2742:
case 0x2752:
case 0x2762:
case 0x2772:
case 0x2b02:
case 0x2b12:
case 0x2b22:
case 0x2b32:
case 0x2b42:
case 0x2b52:
case 0x2b62:
case 0x2b72:
case 0x2f02:
case 0x2f12:
case 0x2f22:
case 0x2f32:
case 0x2f42:
case 0x2f52:
case 0x2f62:
case 0x2f72:
{
    const uint16_t a = 16;
    r[LC] = a;
    break;
}

// Word: 18B (ROM line 18B)
// Match: 010.??110???.0011
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  JUMP UNC, 07
// -------------------------------------------------------------------------
case 0x2303:
case 0x2313:
case 0x2323:
case 0x2333:
case 0x2343:
case 0x2353:
case 0x2363:
case 0x2373:
case 0x2703:
case 0x2713:
case 0x2723:
case 0x2733:
case 0x2743:
case 0x2753:
case 0x2763:
case 0x2773:
case 0x2b03:
case 0x2b13:
case 0x2b23:
case 0x2b33:
case 0x2b43:
case 0x2b53:
case 0x2b63:
case 0x2b73:
case 0x2f03:
case 0x2f13:
case 0x2f23:
case 0x2f33:
case 0x2f43:
case 0x2f53:
case 0x2f63:
case 0x2f73:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    if (true) {
        jumpLocal(7);
    }
    break;
}

// Word: 18C (ROM line 18C)
// Match: 010.??110???.0100
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// AL:AH -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x2304:
case 0x2314:
case 0x2324:
case 0x2334:
case 0x2344:
case 0x2354:
case 0x2364:
case 0x2374:
case 0x2704:
case 0x2714:
case 0x2724:
case 0x2734:
case 0x2744:
case 0x2754:
case 0x2764:
case 0x2774:
case 0x2b04:
case 0x2b14:
case 0x2b24:
case 0x2b34:
case 0x2b44:
case 0x2b54:
case 0x2b64:
case 0x2b74:
case 0x2f04:
case 0x2f14:
case 0x2f24:
case 0x2f34:
case 0x2f44:
case 0x2f54:
case 0x2f64:
case 0x2f74:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = a;
    break;
}

// Word: 18D (ROM line 18D)
// Match: 010.??110???.0101
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// 8 -> LC                        ---  --
// -------------------------------------------------------------------------
case 0x2305:
case 0x2315:
case 0x2325:
case 0x2335:
case 0x2345:
case 0x2355:
case 0x2365:
case 0x2375:
case 0x2705:
case 0x2715:
case 0x2725:
case 0x2735:
case 0x2745:
case 0x2755:
case 0x2765:
case 0x2775:
case 0x2b05:
case 0x2b15:
case 0x2b25:
case 0x2b35:
case 0x2b45:
case 0x2b55:
case 0x2b65:
case 0x2b75:
case 0x2f05:
case 0x2f15:
case 0x2f25:
case 0x2f35:
case 0x2f45:
case 0x2f55:
case 0x2f65:
case 0x2f75:
{
    const uint16_t a = 8;
    r[LC] = a;
    break;
}

// Word: 18E (ROM line 18E)
// Match: 010.??110???.0110
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  --
// -------------------------------------------------------------------------
case 0x2306:
case 0x2316:
case 0x2326:
case 0x2336:
case 0x2346:
case 0x2356:
case 0x2366:
case 0x2376:
case 0x2706:
case 0x2716:
case 0x2726:
case 0x2736:
case 0x2746:
case 0x2756:
case 0x2766:
case 0x2776:
case 0x2b06:
case 0x2b16:
case 0x2b26:
case 0x2b36:
case 0x2b46:
case 0x2b56:
case 0x2b66:
case 0x2b76:
case 0x2f06:
case 0x2f16:
case 0x2f26:
case 0x2f36:
case 0x2f46:
case 0x2f56:
case 0x2f66:
case 0x2f76:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    break;
}

// Word: 18F (ROM line 18F)
// Match: 010.??110???.0111
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
//                                ---  JUMP JNC, 0D
// -------------------------------------------------------------------------
case 0x2307:
case 0x2317:
case 0x2327:
case 0x2337:
case 0x2347:
case 0x2357:
case 0x2367:
case 0x2377:
case 0x2707:
case 0x2717:
case 0x2727:
case 0x2737:
case 0x2747:
case 0x2757:
case 0x2767:
case 0x2777:
case 0x2b07:
case 0x2b17:
case 0x2b27:
case 0x2b37:
case 0x2b47:
case 0x2b57:
case 0x2b67:
case 0x2b77:
case 0x2f07:
case 0x2f17:
case 0x2f27:
case 0x2f37:
case 0x2f47:
case 0x2f57:
case 0x2f67:
case 0x2f77:
{
    if (!aluCarry()) {
        jumpLocal(13);
    }
    break;
}

// Word: 190 (ROM line 190)
// Match: 010.??110???.1000
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU DIV, tmpC, R
// -------------------------------------------------------------------------
case 0x2308:
case 0x2318:
case 0x2328:
case 0x2338:
case 0x2348:
case 0x2358:
case 0x2368:
case 0x2378:
case 0x2708:
case 0x2718:
case 0x2728:
case 0x2738:
case 0x2748:
case 0x2758:
case 0x2768:
case 0x2778:
case 0x2b08:
case 0x2b18:
case 0x2b28:
case 0x2b38:
case 0x2b48:
case 0x2b58:
case 0x2b68:
case 0x2b78:
case 0x2f08:
case 0x2f18:
case 0x2f28:
case 0x2f38:
case 0x2f48:
case 0x2f58:
case 0x2f68:
case 0x2f78:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDiv<true, false>(TC);
    break;
}

// Word: 191 (ROM line 191)
// Match: 010.??110???.1001
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// SIGMA -> NULL   SIGMA -> tmpB  ---  ALU DIV, tmpC
// -------------------------------------------------------------------------
case 0x2309:
case 0x2319:
case 0x2329:
case 0x2339:
case 0x2349:
case 0x2359:
case 0x2369:
case 0x2379:
case 0x2709:
case 0x2719:
case 0x2729:
case 0x2739:
case 0x2749:
case 0x2759:
case 0x2769:
case 0x2779:
case 0x2b09:
case 0x2b19:
case 0x2b29:
case 0x2b39:
case 0x2b49:
case 0x2b59:
case 0x2b69:
case 0x2b79:
case 0x2f09:
case 0x2f19:
case 0x2f29:
case 0x2f39:
case 0x2f49:
case 0x2f59:
case 0x2f69:
case 0x2f79:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    (void)a;
    r[TB] = b;
    setupDiv<false, false>(TC);
    break;
}

// Word: 192 (ROM line 192)
// Match: 010.??110???.1010
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// tmpA -> A                      ---  JUMP JNW, 0E
// -------------------------------------------------------------------------
case 0x230a:
case 0x231a:
case 0x232a:
case 0x233a:
case 0x234a:
case 0x235a:
case 0x236a:
case 0x237a:
case 0x270a:
case 0x271a:
case 0x272a:
case 0x273a:
case 0x274a:
case 0x275a:
case 0x276a:
case 0x277a:
case 0x2b0a:
case 0x2b1a:
case 0x2b2a:
case 0x2b3a:
case 0x2b4a:
case 0x2b5a:
case 0x2b6a:
case 0x2b7a:
case 0x2f0a:
case 0x2f1a:
case 0x2f2a:
case 0x2f3a:
case 0x2f4a:
case 0x2f5a:
case 0x2f6a:
case 0x2f7a:
{
    const uint16_t a = r[TA];
    r[AX] = a;
    if (shortImmediate()) {
        jumpLocal(14);
    }
    break;
}

// Word: 193 (ROM line 193)
// Match: 010.??110???.1011
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// tmpB -> D                      --E  --
// -------------------------------------------------------------------------
case 0x230b:
case 0x231b:
case 0x232b:
case 0x233b:
case 0x234b:
case 0x235b:
case 0x236b:
case 0x237b:
case 0x270b:
case 0x271b:
case 0x272b:
case 0x273b:
case 0x274b:
case 0x275b:
case 0x276b:
case 0x277b:
case 0x2b0b:
case 0x2b1b:
case 0x2b2b:
case 0x2b3b:
case 0x2b4b:
case 0x2b5b:
case 0x2b6b:
case 0x2b7b:
case 0x2f0b:
case 0x2f1b:
case 0x2f2b:
case 0x2f3b:
case 0x2f4b:
case 0x2f5b:
case 0x2f6b:
case 0x2f7b:
{
    const uint16_t a = r[TB];
    r[DX] = a;
    endRequested = true;
    break;
}

// Word: 195 (ROM line 195)
// Match: 010.??110???.1101
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// ZERO -> tmpBL                  ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x230d:
case 0x231d:
case 0x232d:
case 0x233d:
case 0x234d:
case 0x235d:
case 0x236d:
case 0x237d:
case 0x270d:
case 0x271d:
case 0x272d:
case 0x273d:
case 0x274d:
case 0x275d:
case 0x276d:
case 0x277d:
case 0x2b0d:
case 0x2b1d:
case 0x2b2d:
case 0x2b3d:
case 0x2b4d:
case 0x2b5d:
case 0x2b6d:
case 0x2b7d:
case 0x2f0d:
case 0x2f1d:
case 0x2f2d:
case 0x2f3d:
case 0x2f4d:
case 0x2f5d:
case 0x2f6d:
case 0x2f7d:
{
    const uint16_t a = 0;
    r[TB] = extendByte(a);
    jumpFar(0x7100);
    break;
}

// Word: 196 (ROM line 196)
// Match: 010.??110???.1110
// Native Opcodes: F6-F7 /6
// -------------------------------------------------------------------------
// tmpB -> AH                     --E  --
// -------------------------------------------------------------------------
case 0x230e:
case 0x231e:
case 0x232e:
case 0x233e:
case 0x234e:
case 0x235e:
case 0x236e:
case 0x237e:
case 0x270e:
case 0x271e:
case 0x272e:
case 0x273e:
case 0x274e:
case 0x275e:
case 0x276e:
case 0x277e:
case 0x2b0e:
case 0x2b1e:
case 0x2b2e:
case 0x2b3e:
case 0x2b4e:
case 0x2b5e:
case 0x2b6e:
case 0x2b7e:
case 0x2f0e:
case 0x2f1e:
case 0x2f2e:
case 0x2f3e:
case 0x2f4e:
case 0x2f5e:
case 0x2f6e:
case 0x2f7e:
{
    const uint16_t a = r[TB];
    writeByteReg(4, a);
    endRequested = true;
    break;
}

// Word: 198 (ROM line 198)
// Match: 010.??111???.0000
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  ALU MULDIV, tmpB
// -------------------------------------------------------------------------
case 0x2380:
case 0x2390:
case 0x23a0:
case 0x23b0:
case 0x23c0:
case 0x23d0:
case 0x23e0:
case 0x23f0:
case 0x2780:
case 0x2790:
case 0x27a0:
case 0x27b0:
case 0x27c0:
case 0x27d0:
case 0x27e0:
case 0x27f0:
case 0x2b80:
case 0x2b90:
case 0x2ba0:
case 0x2bb0:
case 0x2bc0:
case 0x2bd0:
case 0x2be0:
case 0x2bf0:
case 0x2f80:
case 0x2f90:
case 0x2fa0:
case 0x2fb0:
case 0x2fc0:
case 0x2fd0:
case 0x2fe0:
case 0x2ff0:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupAlu<false, false>(Alu::MulDiv, TB);
    break;
}

// Word: 199 (ROM line 199)
// Match: 010.??111???.0001
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
// 8 -> LC                        ---  IC=SCOF
// -------------------------------------------------------------------------
case 0x2381:
case 0x2391:
case 0x23a1:
case 0x23b1:
case 0x23c1:
case 0x23d1:
case 0x23e1:
case 0x23f1:
case 0x2781:
case 0x2791:
case 0x27a1:
case 0x27b1:
case 0x27c1:
case 0x27d1:
case 0x27e1:
case 0x27f1:
case 0x2b81:
case 0x2b91:
case 0x2ba1:
case 0x2bb1:
case 0x2bc1:
case 0x2bd1:
case 0x2be1:
case 0x2bf1:
case 0x2f81:
case 0x2f91:
case 0x2fa1:
case 0x2fb1:
case 0x2fc1:
case 0x2fd1:
case 0x2fe1:
case 0x2ff1:
{
    const uint16_t a = 8;
    r[LC] = a;
    r[FLAGS] |= (CF | OF);
    break;
}

// Word: 19A (ROM line 19A)
// Match: 010.??111???.0010
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
// SIGMA -> tmpC                  ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x2382:
case 0x2392:
case 0x23a2:
case 0x23b2:
case 0x23c2:
case 0x23d2:
case 0x23e2:
case 0x23f2:
case 0x2782:
case 0x2792:
case 0x27a2:
case 0x27b2:
case 0x27c2:
case 0x27d2:
case 0x27e2:
case 0x27f2:
case 0x2b82:
case 0x2b92:
case 0x2ba2:
case 0x2bb2:
case 0x2bc2:
case 0x2bd2:
case 0x2be2:
case 0x2bf2:
case 0x2f82:
case 0x2f92:
case 0x2fa2:
case 0x2fb2:
case 0x2fc2:
case 0x2fd2:
case 0x2fe2:
case 0x2ff2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TC] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 19B (ROM line 19B)
// Match: 010.??111???.0011
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
// D -> tmpB       SIGMA -> tmpA  ---  JUMP JNW, 05
// -------------------------------------------------------------------------
case 0x2383:
case 0x2393:
case 0x23a3:
case 0x23b3:
case 0x23c3:
case 0x23d3:
case 0x23e3:
case 0x23f3:
case 0x2783:
case 0x2793:
case 0x27a3:
case 0x27b3:
case 0x27c3:
case 0x27d3:
case 0x27e3:
case 0x27f3:
case 0x2b83:
case 0x2b93:
case 0x2ba3:
case 0x2bb3:
case 0x2bc3:
case 0x2bd3:
case 0x2be3:
case 0x2bf3:
case 0x2f83:
case 0x2f93:
case 0x2fa3:
case 0x2fb3:
case 0x2fc3:
case 0x2fd3:
case 0x2fe3:
case 0x2ff3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DX];
    const uint16_t b = sigma;
    r[TB] = a;
    r[TA] = b;
    if (shortImmediate()) {
        jumpLocal(5);
    }
    break;
}

// Word: 19C (ROM line 19C)
// Match: 010.??111???.0100
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
// 16 -> LC                       ---  JUMP UNC, 06
// -------------------------------------------------------------------------
case 0x2384:
case 0x2394:
case 0x23a4:
case 0x23b4:
case 0x23c4:
case 0x23d4:
case 0x23e4:
case 0x23f4:
case 0x2784:
case 0x2794:
case 0x27a4:
case 0x27b4:
case 0x27c4:
case 0x27d4:
case 0x27e4:
case 0x27f4:
case 0x2b84:
case 0x2b94:
case 0x2ba4:
case 0x2bb4:
case 0x2bc4:
case 0x2bd4:
case 0x2be4:
case 0x2bf4:
case 0x2f84:
case 0x2f94:
case 0x2fa4:
case 0x2fb4:
case 0x2fc4:
case 0x2fd4:
case 0x2fe4:
case 0x2ff4:
{
    const uint16_t a = 16;
    r[LC] = a;
    if (true) {
        jumpLocal(6);
    }
    break;
}

// Word: 19D (ROM line 19D)
// Match: 010.??111???.0101
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
// AL:AH -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x2385:
case 0x2395:
case 0x23a5:
case 0x23b5:
case 0x23c5:
case 0x23d5:
case 0x23e5:
case 0x23f5:
case 0x2785:
case 0x2795:
case 0x27a5:
case 0x27b5:
case 0x27c5:
case 0x27d5:
case 0x27e5:
case 0x27f5:
case 0x2b85:
case 0x2b95:
case 0x2ba5:
case 0x2bb5:
case 0x2bc5:
case 0x2bd5:
case 0x2be5:
case 0x2bf5:
case 0x2f85:
case 0x2f95:
case 0x2fa5:
case 0x2fb5:
case 0x2fc5:
case 0x2fd5:
case 0x2fe5:
case 0x2ff5:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = a;
    break;
}

// Word: 19E (ROM line 19E)
// Match: 010.??111???.0110
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
//                                ---  IC=SIGN
// -------------------------------------------------------------------------
case 0x2386:
case 0x2396:
case 0x23a6:
case 0x23b6:
case 0x23c6:
case 0x23d6:
case 0x23e6:
case 0x23f6:
case 0x2786:
case 0x2796:
case 0x27a6:
case 0x27b6:
case 0x27c6:
case 0x27d6:
case 0x27e6:
case 0x27f6:
case 0x2b86:
case 0x2b96:
case 0x2ba6:
case 0x2bb6:
case 0x2bc6:
case 0x2bd6:
case 0x2be6:
case 0x2bf6:
case 0x2f86:
case 0x2f96:
case 0x2fa6:
case 0x2fb6:
case 0x2fc6:
case 0x2fd6:
case 0x2fe6:
case 0x2ff6:
{
    captureArithmeticSign();
    break;
}

// Word: 19F (ROM line 19F)
// Match: 010.??111???.0111
// Native Opcodes: F6-F7 /7
// -------------------------------------------------------------------------
//                                ---  CALL IDIV (0F) -> 7780 [Line 1A0]
// -------------------------------------------------------------------------
case 0x2387:
case 0x2397:
case 0x23a7:
case 0x23b7:
case 0x23c7:
case 0x23d7:
case 0x23e7:
case 0x23f7:
case 0x2787:
case 0x2797:
case 0x27a7:
case 0x27b7:
case 0x27c7:
case 0x27d7:
case 0x27e7:
case 0x27f7:
case 0x2b87:
case 0x2b97:
case 0x2ba7:
case 0x2bb7:
case 0x2bc7:
case 0x2bd7:
case 0x2be7:
case 0x2bf7:
case 0x2f87:
case 0x2f97:
case 0x2fa7:
case 0x2fb7:
case 0x2fc7:
case 0x2fd7:
case 0x2fe7:
case 0x2ff7:
{
    jumpFar(0x7780);
    break;
}

// Word: 1B8 (ROM line 1B8)
// Match: 011.??00????.0000
// Native Opcodes: FE-FF /0, FE-FF /1
// -------------------------------------------------------------------------
// OP1 -> tmpB                    ---  ALU XI, tmpB
// -------------------------------------------------------------------------
case 0x3000:
case 0x3010:
case 0x3020:
case 0x3030:
case 0x3040:
case 0x3050:
case 0x3060:
case 0x3070:
case 0x3080:
case 0x3090:
case 0x30a0:
case 0x30b0:
case 0x30c0:
case 0x30d0:
case 0x30e0:
case 0x30f0:
case 0x3400:
case 0x3410:
case 0x3420:
case 0x3430:
case 0x3440:
case 0x3450:
case 0x3460:
case 0x3470:
case 0x3480:
case 0x3490:
case 0x34a0:
case 0x34b0:
case 0x34c0:
case 0x34d0:
case 0x34e0:
case 0x34f0:
case 0x3800:
case 0x3810:
case 0x3820:
case 0x3830:
case 0x3840:
case 0x3850:
case 0x3860:
case 0x3870:
case 0x3880:
case 0x3890:
case 0x38a0:
case 0x38b0:
case 0x38c0:
case 0x38d0:
case 0x38e0:
case 0x38f0:
case 0x3c00:
case 0x3c10:
case 0x3c20:
case 0x3c30:
case 0x3c40:
case 0x3c50:
case 0x3c60:
case 0x3c70:
case 0x3c80:
case 0x3c90:
case 0x3ca0:
case 0x3cb0:
case 0x3cc0:
case 0x3cd0:
case 0x3ce0:
case 0x3cf0:
{
    const uint16_t a = readOperand(op1);
    r[TB] = a;
    setupDecodedAlu<false, false>(TB);
    break;
}

// Word: 1B9 (ROM line 1B9)
// Match: 011.??00????.0001
// Native Opcodes: FE-FF /0, FE-FF /1
// -------------------------------------------------------------------------
// SIGMA -> OP1                   -WE  EC=COMMIT
// -------------------------------------------------------------------------
case 0x3001:
case 0x3011:
case 0x3021:
case 0x3031:
case 0x3041:
case 0x3051:
case 0x3061:
case 0x3071:
case 0x3081:
case 0x3091:
case 0x30a1:
case 0x30b1:
case 0x30c1:
case 0x30d1:
case 0x30e1:
case 0x30f1:
case 0x3401:
case 0x3411:
case 0x3421:
case 0x3431:
case 0x3441:
case 0x3451:
case 0x3461:
case 0x3471:
case 0x3481:
case 0x3491:
case 0x34a1:
case 0x34b1:
case 0x34c1:
case 0x34d1:
case 0x34e1:
case 0x34f1:
case 0x3801:
case 0x3811:
case 0x3821:
case 0x3831:
case 0x3841:
case 0x3851:
case 0x3861:
case 0x3871:
case 0x3881:
case 0x3891:
case 0x38a1:
case 0x38b1:
case 0x38c1:
case 0x38d1:
case 0x38e1:
case 0x38f1:
case 0x3c01:
case 0x3c11:
case 0x3c21:
case 0x3c31:
case 0x3c41:
case 0x3c51:
case 0x3c61:
case 0x3c71:
case 0x3c81:
case 0x3c91:
case 0x3ca1:
case 0x3cb1:
case 0x3cc1:
case 0x3cd1:
case 0x3ce1:
case 0x3cf1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitAluFlags();
    commitOperand();
    endRequested = true;
    break;
}

// Word: 1BC (ROM line 1BC)
// Match: 011.??010???.0000
// Native Opcodes: FE-FF /2
// -------------------------------------------------------------------------
// PC -> tmpA      SP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x3100:
case 0x3110:
case 0x3120:
case 0x3130:
case 0x3140:
case 0x3150:
case 0x3160:
case 0x3170:
case 0x3500:
case 0x3510:
case 0x3520:
case 0x3530:
case 0x3540:
case 0x3550:
case 0x3560:
case 0x3570:
case 0x3900:
case 0x3910:
case 0x3920:
case 0x3930:
case 0x3940:
case 0x3950:
case 0x3960:
case 0x3970:
case 0x3d00:
case 0x3d10:
case 0x3d20:
case 0x3d30:
case 0x3d40:
case 0x3d50:
case 0x3d60:
case 0x3d70:
{
    const uint16_t a = readPc();
    const uint16_t b = r[SP];
    r[TA] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 1BD (ROM line 1BD)
// Match: 011.??010???.0001
// Native Opcodes: FE-FF /2
// -------------------------------------------------------------------------
// OP1 -> PC       SIGMA -> IND   ---  IC=FLUSH
// -------------------------------------------------------------------------
case 0x3101:
case 0x3111:
case 0x3121:
case 0x3131:
case 0x3141:
case 0x3151:
case 0x3161:
case 0x3171:
case 0x3501:
case 0x3511:
case 0x3521:
case 0x3531:
case 0x3541:
case 0x3551:
case 0x3561:
case 0x3571:
case 0x3901:
case 0x3911:
case 0x3921:
case 0x3931:
case 0x3941:
case 0x3951:
case 0x3961:
case 0x3971:
case 0x3d01:
case 0x3d11:
case 0x3d21:
case 0x3d31:
case 0x3d41:
case 0x3d51:
case 0x3d61:
case 0x3d71:
{
    if (!prefetchFlushReady(false)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOperand(op1);
    const uint16_t b = sigma;
    r[IP] = a;
    writeIndex(b);
    flushPrefetch(false, false, false);
    break;
}

// Word: 1BE (ROM line 1BE)
// Match: 011.??010???.0010
// Native Opcodes: FE-FF /2
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x3102:
case 0x3112:
case 0x3122:
case 0x3132:
case 0x3142:
case 0x3152:
case 0x3162:
case 0x3172:
case 0x3502:
case 0x3512:
case 0x3522:
case 0x3532:
case 0x3542:
case 0x3552:
case 0x3562:
case 0x3572:
case 0x3902:
case 0x3912:
case 0x3922:
case 0x3932:
case 0x3942:
case 0x3952:
case 0x3962:
case 0x3972:
case 0x3d02:
case 0x3d12:
case 0x3d22:
case 0x3d32:
case 0x3d42:
case 0x3d52:
case 0x3d62:
case 0x3d72:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    requestWrite(Segment::SS);
    break;
}

// Word: 1BF (ROM line 1BF)
// Match: 011.??010???.0011
// Native Opcodes: FE-FF /2
// -------------------------------------------------------------------------
// tmpA -> OPR                    --E  --
// -------------------------------------------------------------------------
case 0x3103:
case 0x3113:
case 0x3123:
case 0x3133:
case 0x3143:
case 0x3153:
case 0x3163:
case 0x3173:
case 0x3503:
case 0x3513:
case 0x3523:
case 0x3533:
case 0x3543:
case 0x3553:
case 0x3563:
case 0x3573:
case 0x3903:
case 0x3913:
case 0x3923:
case 0x3933:
case 0x3943:
case 0x3953:
case 0x3963:
case 0x3973:
case 0x3d03:
case 0x3d13:
case 0x3d23:
case 0x3d33:
case 0x3d43:
case 0x3d53:
case 0x3d63:
case 0x3d73:
{
    const uint16_t a = r[TA];
    writeOpr(a);
    endRequested = true;
    break;
}

// Word: 1C0 (ROM line 1C0)
// Match: 011.??011???.0000
// Native Opcodes: FE-FF /3
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x3180:
case 0x3190:
case 0x31a0:
case 0x31b0:
case 0x31c0:
case 0x31d0:
case 0x31e0:
case 0x31f0:
case 0x3580:
case 0x3590:
case 0x35a0:
case 0x35b0:
case 0x35c0:
case 0x35d0:
case 0x35e0:
case 0x35f0:
case 0x3980:
case 0x3990:
case 0x39a0:
case 0x39b0:
case 0x39c0:
case 0x39d0:
case 0x39e0:
case 0x39f0:
case 0x3d80:
case 0x3d90:
case 0x3da0:
case 0x3db0:
case 0x3dc0:
case 0x3dd0:
case 0x3de0:
case 0x3df0:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    suspendPrefetch();
    break;
}

// Word: 1C1 (ROM line 1C1)
// Match: 011.??011???.0001
// Native Opcodes: FE-FF /3
// -------------------------------------------------------------------------
// OPR -> tmpA                    F--  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x3181:
case 0x3191:
case 0x31a1:
case 0x31b1:
case 0x31c1:
case 0x31d1:
case 0x31e1:
case 0x31f1:
case 0x3581:
case 0x3591:
case 0x35a1:
case 0x35b1:
case 0x35c1:
case 0x35d1:
case 0x35e1:
case 0x35f1:
case 0x3981:
case 0x3991:
case 0x39a1:
case 0x39b1:
case 0x39c1:
case 0x39d1:
case 0x39e1:
case 0x39f1:
case 0x3d81:
case 0x3d91:
case 0x3da1:
case 0x3db1:
case 0x3dc1:
case 0x3dd1:
case 0x3de1:
case 0x3df1:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 1C2 (ROM line 1C2)
// Match: 011.??011???.0010
// Native Opcodes: FE-FF /3
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MR
// -------------------------------------------------------------------------
case 0x3182:
case 0x3192:
case 0x31a2:
case 0x31b2:
case 0x31c2:
case 0x31d2:
case 0x31e2:
case 0x31f2:
case 0x3582:
case 0x3592:
case 0x35a2:
case 0x35b2:
case 0x35c2:
case 0x35d2:
case 0x35e2:
case 0x35f2:
case 0x3982:
case 0x3992:
case 0x39a2:
case 0x39b2:
case 0x39c2:
case 0x39d2:
case 0x39e2:
case 0x39f2:
case 0x3d82:
case 0x3d92:
case 0x3da2:
case 0x3db2:
case 0x3dc2:
case 0x3dd2:
case 0x3de2:
case 0x3df2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 1C3 (ROM line 1C3)
// Match: 011.??011???.0011
// Native Opcodes: FE-FF /3
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  CALL FARCALL (0D) -> 7680 [Line 228]
// -------------------------------------------------------------------------
case 0x3183:
case 0x3193:
case 0x31a3:
case 0x31b3:
case 0x31c3:
case 0x31d3:
case 0x31e3:
case 0x31f3:
case 0x3583:
case 0x3593:
case 0x35a3:
case 0x35b3:
case 0x35c3:
case 0x35d3:
case 0x35e3:
case 0x35f3:
case 0x3983:
case 0x3993:
case 0x39a3:
case 0x39b3:
case 0x39c3:
case 0x39d3:
case 0x39e3:
case 0x39f3:
case 0x3d83:
case 0x3d93:
case 0x3da3:
case 0x3db3:
case 0x3dc3:
case 0x3dd3:
case 0x3de3:
case 0x3df3:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    jumpFar(0x7680);
    break;
}

// Word: 1C4 (ROM line 1C4)
// Match: 011.??100???.0000
// Native Opcodes: FE-FF /4
// -------------------------------------------------------------------------
// OP1 -> PC                      --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x3200:
case 0x3210:
case 0x3220:
case 0x3230:
case 0x3240:
case 0x3250:
case 0x3260:
case 0x3270:
case 0x3600:
case 0x3610:
case 0x3620:
case 0x3630:
case 0x3640:
case 0x3650:
case 0x3660:
case 0x3670:
case 0x3a00:
case 0x3a10:
case 0x3a20:
case 0x3a30:
case 0x3a40:
case 0x3a50:
case 0x3a60:
case 0x3a70:
case 0x3e00:
case 0x3e10:
case 0x3e20:
case 0x3e30:
case 0x3e40:
case 0x3e50:
case 0x3e60:
case 0x3e70:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = readOperand(op1);
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 1C8 (ROM line 1C8)
// Match: 011.??101???.0000
// Native Opcodes: FE-FF /5
// -------------------------------------------------------------------------
// OPR -> tmpB     SIGMA -> tmpA  F--  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x3280:
case 0x3290:
case 0x32a0:
case 0x32b0:
case 0x32c0:
case 0x32d0:
case 0x32e0:
case 0x32f0:
case 0x3680:
case 0x3690:
case 0x36a0:
case 0x36b0:
case 0x36c0:
case 0x36d0:
case 0x36e0:
case 0x36f0:
case 0x3a80:
case 0x3a90:
case 0x3aa0:
case 0x3ab0:
case 0x3ac0:
case 0x3ad0:
case 0x3ae0:
case 0x3af0:
case 0x3e80:
case 0x3e90:
case 0x3ea0:
case 0x3eb0:
case 0x3ec0:
case 0x3ed0:
case 0x3ee0:
case 0x3ef0:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOpr();
    const uint16_t b = sigma;
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 1C9 (ROM line 1C9)
// Match: 011.??101???.0001
// Native Opcodes: FE-FF /5
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  IC=SUSP, EC=MR
// -------------------------------------------------------------------------
case 0x3281:
case 0x3291:
case 0x32a1:
case 0x32b1:
case 0x32c1:
case 0x32d1:
case 0x32e1:
case 0x32f1:
case 0x3681:
case 0x3691:
case 0x36a1:
case 0x36b1:
case 0x36c1:
case 0x36d1:
case 0x36e1:
case 0x36f1:
case 0x3a81:
case 0x3a91:
case 0x3aa1:
case 0x3ab1:
case 0x3ac1:
case 0x3ad1:
case 0x3ae1:
case 0x3af1:
case 0x3e81:
case 0x3e91:
case 0x3ea1:
case 0x3eb1:
case 0x3ec1:
case 0x3ed1:
case 0x3ee1:
case 0x3ef1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    suspendPrefetch();
    requestRead(Segment::Default);
    break;
}

// Word: 1CA (ROM line 1CA)
// Match: 011.??101???.0010
// Native Opcodes: FE-FF /5
// -------------------------------------------------------------------------
// OPR -> CS                      F--  --
// -------------------------------------------------------------------------
case 0x3282:
case 0x3292:
case 0x32a2:
case 0x32b2:
case 0x32c2:
case 0x32d2:
case 0x32e2:
case 0x32f2:
case 0x3682:
case 0x3692:
case 0x36a2:
case 0x36b2:
case 0x36c2:
case 0x36d2:
case 0x36e2:
case 0x36f2:
case 0x3a82:
case 0x3a92:
case 0x3aa2:
case 0x3ab2:
case 0x3ac2:
case 0x3ad2:
case 0x3ae2:
case 0x3af2:
case 0x3e82:
case 0x3e92:
case 0x3ea2:
case 0x3eb2:
case 0x3ec2:
case 0x3ed2:
case 0x3ee2:
case 0x3ef2:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeSegment(CS, a, true);
    break;
}

// Word: 1CB (ROM line 1CB)
// Match: 011.??101???.0011
// Native Opcodes: FE-FF /5
// -------------------------------------------------------------------------
// tmpB -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x3283:
case 0x3293:
case 0x32a3:
case 0x32b3:
case 0x32c3:
case 0x32d3:
case 0x32e3:
case 0x32f3:
case 0x3683:
case 0x3693:
case 0x36a3:
case 0x36b3:
case 0x36c3:
case 0x36d3:
case 0x36e3:
case 0x36f3:
case 0x3a83:
case 0x3a93:
case 0x3aa3:
case 0x3ab3:
case 0x3ac3:
case 0x3ad3:
case 0x3ae3:
case 0x3af3:
case 0x3e83:
case 0x3e93:
case 0x3ea3:
case 0x3eb3:
case 0x3ec3:
case 0x3ed3:
case 0x3ee3:
case 0x3ef3:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TB];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 1CC (ROM line 1CC)
// Match: 011.??11????.0000
// Native Opcodes: FE-FF /6, FE-FF /7
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x3300:
case 0x3310:
case 0x3320:
case 0x3330:
case 0x3340:
case 0x3350:
case 0x3360:
case 0x3370:
case 0x3380:
case 0x3390:
case 0x33a0:
case 0x33b0:
case 0x33c0:
case 0x33d0:
case 0x33e0:
case 0x33f0:
case 0x3700:
case 0x3710:
case 0x3720:
case 0x3730:
case 0x3740:
case 0x3750:
case 0x3760:
case 0x3770:
case 0x3780:
case 0x3790:
case 0x37a0:
case 0x37b0:
case 0x37c0:
case 0x37d0:
case 0x37e0:
case 0x37f0:
case 0x3b00:
case 0x3b10:
case 0x3b20:
case 0x3b30:
case 0x3b40:
case 0x3b50:
case 0x3b60:
case 0x3b70:
case 0x3b80:
case 0x3b90:
case 0x3ba0:
case 0x3bb0:
case 0x3bc0:
case 0x3bd0:
case 0x3be0:
case 0x3bf0:
case 0x3f00:
case 0x3f10:
case 0x3f20:
case 0x3f30:
case 0x3f40:
case 0x3f50:
case 0x3f60:
case 0x3f70:
case 0x3f80:
case 0x3f90:
case 0x3fa0:
case 0x3fb0:
case 0x3fc0:
case 0x3fd0:
case 0x3fe0:
case 0x3ff0:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 1CD (ROM line 1CD)
// Match: 011.??11????.0001
// Native Opcodes: FE-FF /6, FE-FF /7
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x3301:
case 0x3311:
case 0x3321:
case 0x3331:
case 0x3341:
case 0x3351:
case 0x3361:
case 0x3371:
case 0x3381:
case 0x3391:
case 0x33a1:
case 0x33b1:
case 0x33c1:
case 0x33d1:
case 0x33e1:
case 0x33f1:
case 0x3701:
case 0x3711:
case 0x3721:
case 0x3731:
case 0x3741:
case 0x3751:
case 0x3761:
case 0x3771:
case 0x3781:
case 0x3791:
case 0x37a1:
case 0x37b1:
case 0x37c1:
case 0x37d1:
case 0x37e1:
case 0x37f1:
case 0x3b01:
case 0x3b11:
case 0x3b21:
case 0x3b31:
case 0x3b41:
case 0x3b51:
case 0x3b61:
case 0x3b71:
case 0x3b81:
case 0x3b91:
case 0x3ba1:
case 0x3bb1:
case 0x3bc1:
case 0x3bd1:
case 0x3be1:
case 0x3bf1:
case 0x3f01:
case 0x3f11:
case 0x3f21:
case 0x3f31:
case 0x3f41:
case 0x3f51:
case 0x3f61:
case 0x3f71:
case 0x3f81:
case 0x3f91:
case 0x3fa1:
case 0x3fb1:
case 0x3fc1:
case 0x3fd1:
case 0x3fe1:
case 0x3ff1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 1CE (ROM line 1CE)
// Match: 011.??11????.0010
// Native Opcodes: FE-FF /6, FE-FF /7
// -------------------------------------------------------------------------
// OP1 -> OPR      SIGMA -> IND   --E  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x3302:
case 0x3312:
case 0x3322:
case 0x3332:
case 0x3342:
case 0x3352:
case 0x3362:
case 0x3372:
case 0x3382:
case 0x3392:
case 0x33a2:
case 0x33b2:
case 0x33c2:
case 0x33d2:
case 0x33e2:
case 0x33f2:
case 0x3702:
case 0x3712:
case 0x3722:
case 0x3732:
case 0x3742:
case 0x3752:
case 0x3762:
case 0x3772:
case 0x3782:
case 0x3792:
case 0x37a2:
case 0x37b2:
case 0x37c2:
case 0x37d2:
case 0x37e2:
case 0x37f2:
case 0x3b02:
case 0x3b12:
case 0x3b22:
case 0x3b32:
case 0x3b42:
case 0x3b52:
case 0x3b62:
case 0x3b72:
case 0x3b82:
case 0x3b92:
case 0x3ba2:
case 0x3bb2:
case 0x3bc2:
case 0x3bd2:
case 0x3be2:
case 0x3bf2:
case 0x3f02:
case 0x3f12:
case 0x3f22:
case 0x3f32:
case 0x3f42:
case 0x3f52:
case 0x3f62:
case 0x3f72:
case 0x3f82:
case 0x3f92:
case 0x3fa2:
case 0x3fb2:
case 0x3fc2:
case 0x3fd2:
case 0x3fe2:
case 0x3ff2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOperand(op1);
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::SS);
    endRequested = true;
    break;
}

// Word: 2A8 (ROM line 2AC)
// Match: 100.0001000?.0000
// 0F Opcodes: 10-11
// -------------------------------------------------------------------------
// OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x4100:
case 0x4110:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[CX];
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2A9 (ROM line 2AD)
// Match: 100.0001000?.0001
// 0F Opcodes: 10-11
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x4101:
case 0x4111:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::And, TA);
    break;
}

// Word: 2AA (ROM line 2AE)
// Match: 100.0001000?.0010
// 0F Opcodes: 10-11
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -WE  --
// -------------------------------------------------------------------------
case 0x4102:
case 0x4112:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    endRequested = true;
    break;
}

// Word: 2B8 (ROM line 2BC)
// Match: 100.0001001?.0000
// 0F Opcodes: 12-13
// -------------------------------------------------------------------------
// OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x4120:
case 0x4130:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[CX];
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2B9 (ROM line 2BD)
// Match: 100.0001001?.0001
// 0F Opcodes: 12-13
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU NOT, tmpA
// -------------------------------------------------------------------------
case 0x4121:
case 0x4131:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Not, TA);
    break;
}

// Word: 2BA (ROM line 2BE)
// Match: 100.0001001?.0010
// 0F Opcodes: 12-13
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x4122:
case 0x4132:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    setupAlu<false, false>(Alu::And, TA);
    break;
}

// Word: 2BB (ROM line 2BF)
// Match: 100.0001001?.0011
// 0F Opcodes: 12-13
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x4123:
case 0x4133:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 2B0 (ROM line 2B4)
// Match: 100.0001010?.0000
// 0F Opcodes: 14-15
// -------------------------------------------------------------------------
// OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x4140:
case 0x4150:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[CX];
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2B1 (ROM line 2B5)
// Match: 100.0001010?.0001
// 0F Opcodes: 14-15
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU OR, tmpA
// -------------------------------------------------------------------------
case 0x4141:
case 0x4151:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Or, TA);
    break;
}

// Word: 2B2 (ROM line 2B6)
// Match: 100.0001010?.0010
// 0F Opcodes: 14-15
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x4142:
case 0x4152:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 2C0 (ROM line 2C4)
// Match: 100.0001011?.0000
// 0F Opcodes: 16-17
// -------------------------------------------------------------------------
// OP1 -> tmpB     C -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x4160:
case 0x4170:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[CX];
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2C1 (ROM line 2C5)
// Match: 100.0001011?.0001
// 0F Opcodes: 16-17
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU XOR, tmpA
// -------------------------------------------------------------------------
case 0x4161:
case 0x4171:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Xor, TA);
    break;
}

// Word: 2C2 (ROM line 2C6)
// Match: 100.0001011?.0010
// 0F Opcodes: 16-17
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x4162:
case 0x4172:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 2AC (ROM line 2B0)
// Match: 100.0001100?.0000
// 0F Opcodes: 18-19
// -------------------------------------------------------------------------
// OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x4180:
case 0x4190:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readOperand(op1);
    const uint16_t b = readPrefetchForMicrocode();
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2AD (ROM line 2B1)
// Match: 100.0001100?.0001
// 0F Opcodes: 18-19
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x4181:
case 0x4191:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::And, TA);
    break;
}

// Word: 2AE (ROM line 2B2)
// Match: 100.0001100?.0010
// 0F Opcodes: 18-19
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -WE  --
// -------------------------------------------------------------------------
case 0x4182:
case 0x4192:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    endRequested = true;
    break;
}

// Word: 2BC (ROM line 2C0)
// Match: 100.0001101?.0000
// 0F Opcodes: 1A-1B
// -------------------------------------------------------------------------
// OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x41a0:
case 0x41b0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readOperand(op1);
    const uint16_t b = readPrefetchForMicrocode();
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2BD (ROM line 2C1)
// Match: 100.0001101?.0001
// 0F Opcodes: 1A-1B
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU NOT, tmpA
// -------------------------------------------------------------------------
case 0x41a1:
case 0x41b1:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Not, TA);
    break;
}

// Word: 2BE (ROM line 2C2)
// Match: 100.0001101?.0010
// 0F Opcodes: 1A-1B
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x41a2:
case 0x41b2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    setupAlu<false, false>(Alu::And, TA);
    break;
}

// Word: 2BF (ROM line 2C3)
// Match: 100.0001101?.0011
// 0F Opcodes: 1A-1B
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x41a3:
case 0x41b3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 2B4 (ROM line 2B8)
// Match: 100.0001110?.0000
// 0F Opcodes: 1C-1D
// -------------------------------------------------------------------------
// OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x41c0:
case 0x41d0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readOperand(op1);
    const uint16_t b = readPrefetchForMicrocode();
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2B5 (ROM line 2B9)
// Match: 100.0001110?.0001
// 0F Opcodes: 1C-1D
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU OR, tmpA
// -------------------------------------------------------------------------
case 0x41c1:
case 0x41d1:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Or, TA);
    break;
}

// Word: 2B6 (ROM line 2BA)
// Match: 100.0001110?.0010
// 0F Opcodes: 1C-1D
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x41c2:
case 0x41d2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 2C4 (ROM line 2C8)
// Match: 100.0001111?.0000
// 0F Opcodes: 1E-1F
// -------------------------------------------------------------------------
// OP1 -> tmpB     Q -> tmpA      ---  ALU BITM, tmpA
// -------------------------------------------------------------------------
case 0x41e0:
case 0x41f0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readOperand(op1);
    const uint16_t b = readPrefetchForMicrocode();
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::BitMask, TA);
    break;
}

// Word: 2C5 (ROM line 2C9)
// Match: 100.0001111?.0001
// 0F Opcodes: 1E-1F
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU XOR, tmpA
// -------------------------------------------------------------------------
case 0x41e1:
case 0x41f1:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Xor, TA);
    break;
}

// Word: 2C6 (ROM line 2CA)
// Match: 100.0001111?.0010
// 0F Opcodes: 1E-1F
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x41e2:
case 0x41f2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 2C8 (ROM line 2CC)
// Match: 100.00100??0.0000
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// C -> tmpAL                     ---  ALU INC, tmpA
// -------------------------------------------------------------------------
case 0x4200:
case 0x4220:
case 0x4240:
case 0x4260:
{
    const uint16_t a = r[CX];
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Inc, TA);
    break;
}

// Word: 2C9 (ROM line 2CD)
// Match: 100.00100??0.0001
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU SHR, tmpB
// -------------------------------------------------------------------------
case 0x4201:
case 0x4221:
case 0x4241:
case 0x4261:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<false, false>(Alu::Shr, TB);
    break;
}

// Word: 2CA (ROM line 2CE)
// Match: 100.00100??0.0010
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// SIGMA -> LC                    ---  IC=BCD_INIT
// -------------------------------------------------------------------------
case 0x4202:
case 0x4222:
case 0x4242:
case 0x4262:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[LC] = a;
    beginDecimalString();
    break;
}

// Word: 2CB (ROM line 2CF)
// Match: 100.00100??0.0011
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// SI -> DP        SI -> tmpA     ---  EC=MR
// -------------------------------------------------------------------------
case 0x4203:
case 0x4223:
case 0x4243:
case 0x4263:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SI];
    const uint16_t b = r[SI];
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 2CC (ROM line 2D0)
// Match: 100.00100??0.0100
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
//                                ---  ALU INC, tmpA
// -------------------------------------------------------------------------
case 0x4204:
case 0x4224:
case 0x4244:
case 0x4264:
{
    setupAlu<false, false>(Alu::Inc, TA);
    break;
}

// Word: 2CD (ROM line 2D1)
// Match: 100.00100??0.0101
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  --
// -------------------------------------------------------------------------
case 0x4205:
case 0x4225:
case 0x4245:
case 0x4265:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    break;
}

// Word: 2CE (ROM line 2D2)
// Match: 100.00100??0.0110
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// OPR -> tmpC                    F--  --
// -------------------------------------------------------------------------
case 0x4206:
case 0x4226:
case 0x4246:
case 0x4266:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TC] = a;
    break;
}

// Word: 2CF (ROM line 2D3)
// Match: 100.00100??0.0111
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// DI -> DP                       ---  EC=MR, SR=ES
// -------------------------------------------------------------------------
case 0x4207:
case 0x4227:
case 0x4247:
case 0x4267:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestRead(Segment::ES);
    break;
}

// Word: 2D0 (ROM line 2D4)
// Match: 100.00100000.1000
// 0F Opcodes: 20
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU ADC, tmpC
// -------------------------------------------------------------------------
case 0x4208:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Adc, TC);
    break;
}

// Word: 2D1 (ROM line 2D5)
// Match: 100.00100000.1001
// 0F Opcodes: 20
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  -W-  ALU ADJD, tmpB
// -------------------------------------------------------------------------
case 0x4209:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    commitAluFlags();
    setupAlu<false, true>(Alu::AdjustDecimal, TB);
    break;
}

// Word: 2D2 (ROM line 2D6)
// Match: 100.00100000.1010
// 0F Opcodes: 20
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x420a:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 2D3 (ROM line 2D7)
// Match: 100.00100000.1011
// 0F Opcodes: 20
// -------------------------------------------------------------------------
// DI -> DP        SIGMA -> NULL  -W-  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x420b:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DI];
    const uint16_t b = sigma;
    writeIndex(a);
    (void)b;
    commitAluFlags();
    requestWrite(Segment::ES);
    break;
}

// Word: 2D4 (ROM line 2D8)
// Match: 100.00100??0.1100
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
//                                ---  IC=BCD_ZERO
// -------------------------------------------------------------------------
case 0x420c:
case 0x422c:
case 0x424c:
case 0x426c:
{
    accumulateDecimalZero();
    break;
}

// Word: 2D5 (ROM line 2D9)
// Match: 100.00100??0.1101
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// SIGMA -> OPR    DI -> tmpA     ---  ALU INC, tmpA
// -------------------------------------------------------------------------
case 0x420d:
case 0x422d:
case 0x424d:
case 0x426d:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = r[DI];
    writeOpr(a);
    r[TA] = b;
    setupAlu<false, false>(Alu::Inc, TA);
    break;
}

// Word: 2D6 (ROM line 2DA)
// Match: 100.00100??0.1110
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// SIGMA -> DI     ONES -> tmpB   ---  JUMP JLCNZ, 03
// -------------------------------------------------------------------------
case 0x420e:
case 0x422e:
case 0x424e:
case 0x426e:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = 0xffff;
    r[DI] = a;
    r[TB] = b;
    if (decrementLoopCounter()) {
        jumpLocal(3);
    }
    break;
}

// Word: 2D7 (ROM line 2DB)
// Match: 100.00100??0.1111
// 0F Opcodes: 20, 22, 24, 26
// -------------------------------------------------------------------------
// C -> tmpAL                     ---  ALU ADD, tmpB
// -------------------------------------------------------------------------
case 0x420f:
case 0x422f:
case 0x424f:
case 0x426f:
{
    const uint16_t a = r[CX];
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Add, TB);
    break;
}

// Word: 2D8 (ROM line 2DC)
// Match: 100.00100??1.0000
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
//                                ---  JUMP JC, 03
// -------------------------------------------------------------------------
case 0x4210:
case 0x4230:
case 0x4250:
case 0x4270:
{
    if ((r[FLAGS] & CF) != 0) {
        jumpLocal(3);
    }
    break;
}

// Word: 2D9 (ROM line 2DD)
// Match: 100.00100??1.0001
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// 1 -> tmpB                      ---  JUMP JPOS/NZ4S, 03
// -------------------------------------------------------------------------
case 0x4211:
case 0x4231:
case 0x4251:
case 0x4271:
{
    const uint16_t a = 1;
    r[TB] = a;
    if (nonnegativeResult()) {
        jumpLocal(3);
    }
    break;
}

// Word: 2DA (ROM line 2DE)
// Match: 100.00100??1.0010
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// ZERO -> tmpB                   ---  --
// -------------------------------------------------------------------------
case 0x4212:
case 0x4232:
case 0x4252:
case 0x4272:
{
    const uint16_t a = 0;
    r[TB] = a;
    break;
}

// Word: 2DB (ROM line 2DF)
// Match: 100.00100??1.0011
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  ALU INC, tmpA
// -------------------------------------------------------------------------
case 0x4213:
case 0x4233:
case 0x4253:
case 0x4273:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    setupAlu<false, true>(Alu::Inc, TA);
    break;
}

// Word: 2DC (ROM line 2E0)
// Match: 100.00100??1.0100
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU SHR, tmpB
// -------------------------------------------------------------------------
case 0x4214:
case 0x4234:
case 0x4254:
case 0x4274:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<false, false>(Alu::Shr, TB);
    break;
}

// Word: 2DD (ROM line 2E1)
// Match: 100.00100??1.0101
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// DI -> tmpB      SIGMA -> tmpA  ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x4215:
case 0x4235:
case 0x4255:
case 0x4275:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DI];
    const uint16_t b = sigma;
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 2DE (ROM line 2E2)
// Match: 100.00100??1.0110
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// SIGMA -> DI     SI -> tmpB     --E  --
// -------------------------------------------------------------------------
case 0x4216:
case 0x4236:
case 0x4256:
case 0x4276:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = r[SI];
    r[DI] = a;
    r[TB] = b;
    endRequested = true;
    break;
}

// Word: 2DF (ROM line 2E3)
// Match: 100.00100??1.0111
// 0F Opcodes: 21, 23, 25, 27
// -------------------------------------------------------------------------
// SIGMA -> SI                    ---  --
// -------------------------------------------------------------------------
case 0x4217:
case 0x4237:
case 0x4257:
case 0x4277:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SI] = a;
    break;
}

// Word: 2E0 (ROM line 2E4)
// Match: 100.00100010.1000
// 0F Opcodes: 22
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU SBB, tmpC
// -------------------------------------------------------------------------
case 0x4228:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Sbb, TC);
    break;
}

// Word: 2E1 (ROM line 2E5)
// Match: 100.00100010.1001
// 0F Opcodes: 22
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  -W-  ALU ADJD, tmpB
// -------------------------------------------------------------------------
case 0x4229:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    commitAluFlags();
    setupAlu<false, true>(Alu::AdjustDecimal, TB);
    break;
}

// Word: 2E2 (ROM line 2E6)
// Match: 100.00100010.1010
// 0F Opcodes: 22
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x422a:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 2E3 (ROM line 2E7)
// Match: 100.00100010.1011
// 0F Opcodes: 22
// -------------------------------------------------------------------------
// DI -> DP        SIGMA -> NULL  -W-  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x422b:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DI];
    const uint16_t b = sigma;
    writeIndex(a);
    (void)b;
    commitAluFlags();
    requestWrite(Segment::ES);
    break;
}

// Word: 2E4 (ROM line 2E8)
// Match: 100.00100110.1000
// 0F Opcodes: 26
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU SBB, tmpC
// -------------------------------------------------------------------------
case 0x4268:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Sbb, TC);
    break;
}

// Word: 2E5 (ROM line 2E9)
// Match: 100.00100110.1001
// 0F Opcodes: 26
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  -W-  ALU ADJD, tmpB
// -------------------------------------------------------------------------
case 0x4269:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    commitAluFlags();
    setupAlu<false, true>(Alu::AdjustDecimal, TB);
    break;
}

// Word: 2E6 (ROM line 2EA)
// Match: 100.00100110.1010
// 0F Opcodes: 26
// -------------------------------------------------------------------------
// K -> tmpA                      ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x426a:
{
    const uint16_t a = readK();
    r[TA] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 2E7 (ROM line 2EB)
// Match: 100.00100110.1011
// 0F Opcodes: 26
// -------------------------------------------------------------------------
// DI -> DP        SIGMA -> NULL  -W-  --
// -------------------------------------------------------------------------
case 0x426b:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DI];
    const uint16_t b = sigma;
    writeIndex(a);
    (void)b;
    commitAluFlags();
    break;
}

// Word: 2E8 (ROM line 2EC)
// Match: 100.00101000.0000
// 0F Opcodes: 28
// -------------------------------------------------------------------------
// 4 -> LC                        ---  --
// -------------------------------------------------------------------------
case 0x4280:
{
    const uint16_t a = 4;
    r[LC] = a;
    break;
}

// Word: 2E9 (ROM line 2ED)
// Match: 100.00101000.0001
// 0F Opcodes: 28
// -------------------------------------------------------------------------
// OP1 -> tmpBL                   ---  --
// -------------------------------------------------------------------------
case 0x4281:
{
    const uint16_t a = readOperand(op1);
    r[TB] = extendByte(a);
    break;
}

// Word: 2EA (ROM line 2EE)
// Match: 100.00101000.0010
// 0F Opcodes: 28
// -------------------------------------------------------------------------
// AL:AH -> tmpBH                 ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x4282:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 2EB (ROM line 2EF)
// Match: 100.00101000.0011
// 0F Opcodes: 28
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU ROL12, tmpB, R
// -------------------------------------------------------------------------
case 0x4283:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<true, false>(Alu::Rol12, TB);
    break;
}

// Word: 2EC (ROM line 2F0)
// Match: 100.001010?0.0100
// 0F Opcodes: 28, 2A
// -------------------------------------------------------------------------
// tmpB -> OP1                    ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x4284:
case 0x42a4:
{
    const uint16_t a = r[TB];
    writeOperand(op1, a);
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 2ED (ROM line 2F1)
// Match: 100.001010?0.0101
// 0F Opcodes: 28, 2A
// -------------------------------------------------------------------------
// A -> tmpA                      ---  EC=COMMIT
// -------------------------------------------------------------------------
case 0x4285:
case 0x42a5:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[AX];
    r[TA] = a;
    commitOperand();
    break;
}

// Word: 2EE (ROM line 2F2)
// Match: 100.001010?0.0110
// 0F Opcodes: 28, 2A
// -------------------------------------------------------------------------
// tmpB -> A                      ---  --
// -------------------------------------------------------------------------
case 0x4286:
case 0x42a6:
{
    const uint16_t a = r[TB];
    r[AX] = a;
    break;
}

// Word: 2EF (ROM line 2F3)
// Match: 100.001010?0.0111
// 0F Opcodes: 28, 2A
// -------------------------------------------------------------------------
// AL:AH -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x4287:
case 0x42a7:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = a;
    break;
}

// Word: 2F0 (ROM line 2F4)
// Match: 100.001010?0.1000
// 0F Opcodes: 28, 2A
// -------------------------------------------------------------------------
// tmpA -> tmpBH                  --E  --
// -------------------------------------------------------------------------
case 0x4288:
case 0x42a8:
{
    const uint16_t a = r[TA];
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    endRequested = true;
    break;
}

// Word: 2F1 (ROM line 2F5)
// Match: 100.001010?0.1001
// 0F Opcodes: 28, 2A
// -------------------------------------------------------------------------
// tmpB -> A                      ---  --
// -------------------------------------------------------------------------
case 0x4289:
case 0x42a9:
{
    const uint16_t a = r[TB];
    r[AX] = a;
    break;
}

// Word: 2F4 (ROM line 2F8)
// Match: 100.00101010.0000
// 0F Opcodes: 2A
// -------------------------------------------------------------------------
// 8 -> LC                        ---  --
// -------------------------------------------------------------------------
case 0x42a0:
{
    const uint16_t a = 8;
    r[LC] = a;
    break;
}

// Word: 2F5 (ROM line 2F9)
// Match: 100.00101010.0001
// 0F Opcodes: 2A
// -------------------------------------------------------------------------
// OP1 -> tmpBL                   ---  --
// -------------------------------------------------------------------------
case 0x42a1:
{
    const uint16_t a = readOperand(op1);
    r[TB] = extendByte(a);
    break;
}

// Word: 2F6 (ROM line 2FA)
// Match: 100.00101010.0010
// 0F Opcodes: 2A
// -------------------------------------------------------------------------
// AL:AH -> tmpBH                 ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x42a2:
{
    const uint16_t a = swappedAccumulator();
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 2F7 (ROM line 2FB)
// Match: 100.00101010.0011
// 0F Opcodes: 2A
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU ROL12, tmpB, R
// -------------------------------------------------------------------------
case 0x42a3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<true, false>(Alu::Rol12, TB);
    break;
}

// Word: 314 (ROM line 318)
// Match: 100.0011?001.0000
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// OP1 -> tmpAL                   ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x4310:
case 0x4390:
{
    const uint16_t a = readOperand(op1);
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 315 (ROM line 319)
// Match: 100.0011?001.0001
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// tmpA -> LC      SIGMA -> NULL  ---  --
// -------------------------------------------------------------------------
case 0x4311:
case 0x4391:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    r[LC] = a;
    (void)b;
    break;
}

// Word: 316 (ROM line 31A)
// Match: 100.0011?001.0010
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// ZERO -> tmpC                   ---  JUMP JZ, 06
// -------------------------------------------------------------------------
case 0x4312:
case 0x4392:
{
    const uint16_t a = 0;
    r[TC] = a;
    if (aluZero()) {
        jumpLocal(6);
    }
    break;
}

// Word: 317 (ROM line 31B)
// Match: 100.0011?001.0011
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// DI -> DP                       ---  EC=MR, SR=ES
// -------------------------------------------------------------------------
case 0x4313:
case 0x4393:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestRead(Segment::ES);
    break;
}

// Word: 318 (ROM line 31C)
// Match: 100.00110001.0100
// 0F Opcodes: 31
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x4314:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 319 (ROM line 31D)
// Match: 100.00110001.0101
// 0F Opcodes: 31
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x4315:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 31A (ROM line 31E)
// Match: 100.00110001.0110
// 0F Opcodes: 31
// -------------------------------------------------------------------------
// tmpA -> OPR                    ---  --
// -------------------------------------------------------------------------
case 0x4316:
{
    const uint16_t a = r[TA];
    writeOpr(a);
    break;
}

// Word: 31B (ROM line 31F)
// Match: 100.00110001.0111
// 0F Opcodes: 31
// -------------------------------------------------------------------------
// OP2 -> tmpAL                   ---  ALU INC, tmpA
// -------------------------------------------------------------------------
case 0x4317:
{
    const uint16_t a = readOperand(op2);
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Inc, TA);
    break;
}

// Word: 31C (ROM line 320)
// Match: 100.0011?001.1000
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// OP1 -> tmpAL    SIGMA -> tmpB  ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x4318:
case 0x4398:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOperand(op1);
    const uint16_t b = sigma;
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 31D (ROM line 321)
// Match: 100.0011?001.1001
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// SIGMA -> tmpC                  ---  --
// -------------------------------------------------------------------------
case 0x4319:
case 0x4399:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TC] = a;
    break;
}

// Word: 31E (ROM line 322)
// Match: 100.0011?001.1010
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// tmpB -> LC                     ---  --
// -------------------------------------------------------------------------
case 0x431a:
case 0x439a:
{
    const uint16_t a = r[TB];
    r[LC] = a;
    break;
}

// Word: 31F (ROM line 323)
// Match: 100.0011?001.1011
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// 15 -> tmpB                     ---  ALU AND, tmpC
// -------------------------------------------------------------------------
case 0x431b:
case 0x439b:
{
    const uint16_t a = 15;
    r[TB] = a;
    setupAlu<false, false>(Alu::And, TC);
    break;
}

// Word: 320 (ROM line 324)
// Match: 100.0011?001.1100
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// OP1 -> tmpAL                   ---  --
// -------------------------------------------------------------------------
case 0x431c:
case 0x439c:
{
    const uint16_t a = readOperand(op1);
    r[TA] = uint8_t(a);
    break;
}

// Word: 321 (ROM line 325)
// Match: 100.0011?001.1101
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// SIGMA -> OP1                   ---  ALU SUB, tmpC
// -------------------------------------------------------------------------
case 0x431d:
case 0x439d:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    setupAlu<false, false>(Alu::Sub, TC);
    break;
}

// Word: 322 (ROM line 326)
// Match: 100.0011?001.1110
// 0F Opcodes: 31, 39
// -------------------------------------------------------------------------
// A -> tmpB       SIGMA -> NULL  -W-  CALL EXT (0E) -> 7700 [Line 324]
// -------------------------------------------------------------------------
case 0x431e:
case 0x439e:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[AX];
    const uint16_t b = sigma;
    r[TB] = a;
    (void)b;
    commitAluFlags();
    jumpFar(0x7700);
    break;
}

// Word: 2F8 (ROM line 2FC)
// Match: 100.00110011.0000
// 0F Opcodes: 33
// -------------------------------------------------------------------------
// 15 -> tmpC                     ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x4330:
{
    const uint16_t a = 15;
    r[TC] = a;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 2F9 (ROM line 2FD)
// Match: 100.00110011.0001
// 0F Opcodes: 33
// -------------------------------------------------------------------------
// OP2 -> tmpAL    SIGMA -> tmpB  ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x4331:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOperand(op2);
    const uint16_t b = sigma;
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 2FA (ROM line 2FE)
// Match: 100.00110011.0010
// 0F Opcodes: 33
// -------------------------------------------------------------------------
// SIGMA -> A                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x4332:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[AX] = a;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 2FC (ROM line 300)
// Match: 100.0011?011.0100
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// SI -> DP        SIGMA -> tmpB  ---  EC=MR
// -------------------------------------------------------------------------
case 0x4334:
case 0x43b4:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[SI];
    const uint16_t b = sigma;
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 2FD (ROM line 301)
// Match: 100.0011?011.0101
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// OP1 -> tmpAL                   ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x4335:
case 0x43b5:
{
    const uint16_t a = readOperand(op1);
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 2FE (ROM line 302)
// Match: 100.0011?011.0110
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// tmpC -> tmpB    SIGMA -> tmpA  ---  ALU AND, tmpA
// -------------------------------------------------------------------------
case 0x4336:
case 0x43b6:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TC];
    const uint16_t b = sigma;
    r[TB] = a;
    r[TA] = b;
    setupAlu<false, false>(Alu::And, TA);
    break;
}

// Word: 2FF (ROM line 303)
// Match: 100.0011?011.0111
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// SIGMA -> LC                    ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x4337:
case 0x43b7:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[LC] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 300 (ROM line 304)
// Match: 100.0011?011.1000
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// SI -> tmpB      SIGMA -> NULL  -W-  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x4338:
case 0x43b8:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[SI];
    const uint16_t b = sigma;
    r[TB] = a;
    (void)b;
    commitAluFlags();
    setupAlu<false, true>(Alu::Inc2, TB);
    break;
}

// Word: 301 (ROM line 305)
// Match: 100.0011?011.1001
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// OPR -> tmpC                    F--  JUMP JZ, 0B
// -------------------------------------------------------------------------
case 0x4339:
case 0x43b9:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TC] = a;
    if (aluZero()) {
        jumpLocal(11);
    }
    break;
}

// Word: 302 (ROM line 306)
// Match: 100.0011?011.1010
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
//                                ---  JUMP JNC, 0E
// -------------------------------------------------------------------------
case 0x433a:
case 0x43ba:
{
    if (!aluCarry()) {
        jumpLocal(14);
    }
    break;
}

// Word: 303 (ROM line 307)
// Match: 100.0011?011.1011
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// SIGMA -> SI     SIGMA -> IND   ---  JUMP JZ, 0E
// -------------------------------------------------------------------------
case 0x433b:
case 0x43bb:
{
    const bool branch = aluZero();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SI] = a;
    writeIndex(b);
    if (branch) {
        jumpLocal(14);
    }
    break;
}

// Word: 304 (ROM line 308)
// Match: 100.0011?011.1100
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// tmpC -> tmpA                   ---  EC=MR
// -------------------------------------------------------------------------
case 0x433c:
case 0x43bc:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TC];
    r[TA] = a;
    requestRead(Segment::Default);
    break;
}

// Word: 305 (ROM line 309)
// Match: 100.0011?011.1101
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// OPR -> tmpC                    F--  --
// -------------------------------------------------------------------------
case 0x433d:
case 0x43bd:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TC] = a;
    break;
}

// Word: 306 (ROM line 30A)
// Match: 100.0011?011.1110
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// LC -> tmpB                     ---  ALU INC, tmpB
// -------------------------------------------------------------------------
case 0x433e:
case 0x43be:
{
    const uint16_t a = r[LC];
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc, TB);
    break;
}

// Word: 307 (ROM line 30B)
// Match: 100.0011?011.1111
// 0F Opcodes: 33, 3B
// -------------------------------------------------------------------------
// SIGMA -> LC     SIGMA -> tmpB  ---  ALU ADJA, tmpB
// -------------------------------------------------------------------------
case 0x433f:
case 0x43bf:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[LC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::AdjustAscii, TB);
    break;
}

// Word: 308 (ROM line 30C)
// Match: 100.0011?100.0000
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x4340:
case 0x43c0:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 309 (ROM line 30D)
// Match: 100.0011?100.0001
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// tmpB -> OP1     SIGMA -> tmpB  ---  --
// -------------------------------------------------------------------------
case 0x4341:
case 0x43c1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TB];
    const uint16_t b = sigma;
    writeOperand(op1, a);
    r[TB] = b;
    break;
}

// Word: 30A (ROM line 30E)
// Match: 100.0011?100.0010
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// ZERO -> tmpC                   ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x4342:
case 0x43c2:
{
    const uint16_t a = 0;
    r[TC] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 30B (ROM line 30F)
// Match: 100.0011?100.0011
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x4343:
case 0x43c3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 30C (ROM line 310)
// Match: 100.0011?100.0100
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// A -> tmpB                      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x4344:
case 0x43c4:
{
    const uint16_t a = r[AX];
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 30D (ROM line 311)
// Match: 100.0011?100.0101
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// SIGMA -> LC                    ---  --
// -------------------------------------------------------------------------
case 0x4345:
case 0x43c5:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[LC] = a;
    break;
}

// Word: 30E (ROM line 312)
// Match: 100.0011?100.0110
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// ZERO -> tmpB                   ---  JUMP JZ, 08
// -------------------------------------------------------------------------
case 0x4346:
case 0x43c6:
{
    const uint16_t a = 0;
    r[TB] = a;
    if (aluZero()) {
        jumpLocal(8);
    }
    break;
}

// Word: 30F (ROM line 313)
// Match: 100.0011?100.0111
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x4347:
case 0x43c7:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 1FC (ROM line 200)
// Match: 100.0011?100.1000
// 0F Opcodes: 34, 3C
// -------------------------------------------------------------------------
// tmpA -> A                      --E  --
// -------------------------------------------------------------------------
case 0x4348:
case 0x43c8:
{
    const uint16_t a = r[TA];
    r[AX] = a;
    endRequested = true;
    break;
}

// Word: 340 (ROM line 344)
// Match: 100.00111001.0100
// 0F Opcodes: 39
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x4394:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 341 (ROM line 345)
// Match: 100.00111001.0101
// 0F Opcodes: 39
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x4395:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 342 (ROM line 346)
// Match: 100.00111001.0110
// 0F Opcodes: 39
// -------------------------------------------------------------------------
// tmpA -> OPR                    ---  --
// -------------------------------------------------------------------------
case 0x4396:
{
    const uint16_t a = r[TA];
    writeOpr(a);
    break;
}

// Word: 343 (ROM line 347)
// Match: 100.00111001.0111
// 0F Opcodes: 39
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  ALU INC, tmpA
// -------------------------------------------------------------------------
case 0x4397:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Inc, TA);
    break;
}

// Word: 310 (ROM line 314)
// Match: 100.00111011.0000
// 0F Opcodes: 3B
// -------------------------------------------------------------------------
// 15 -> tmpC                     ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x43b0:
{
    const uint16_t a = 15;
    r[TC] = a;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 311 (ROM line 315)
// Match: 100.00111011.0001
// 0F Opcodes: 3B
// -------------------------------------------------------------------------
// Q -> tmpAL      SIGMA -> tmpB  ---  --
// -------------------------------------------------------------------------
case 0x43b1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = sigma;
    r[TA] = uint8_t(a);
    r[TB] = b;
    break;
}

// Word: 312 (ROM line 316)
// Match: 100.00111011.0010
// 0F Opcodes: 3B
// -------------------------------------------------------------------------
//                                ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x43b2:
{
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 313 (ROM line 317)
// Match: 100.00111011.0011
// 0F Opcodes: 3B
// -------------------------------------------------------------------------
// SIGMA -> A                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x43b3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[AX] = a;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 344 (ROM line 348)
// Match: 100.11111111.0000
// 0F Opcodes: FF
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x4ff0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 345 (ROM line 349)
// Match: 100.11111111.0001
// 0F Opcodes: FF
// -------------------------------------------------------------------------
// 1 -> LC                        ---  CALL EM_INT (03) -> 7180 [Line 1E8]
// -------------------------------------------------------------------------
case 0x4ff1:
{
    const uint16_t a = 1;
    r[LC] = a;
    jumpFar(0x7180);
    break;
}

// Word: 3FC (ROM line 400)
// Match: 101.11101101.0000
// ED Opcodes: ED
// -------------------------------------------------------------------------
// Q -> tmpBL                     ---  --
// -------------------------------------------------------------------------
case 0x5ed0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TB] = extendByte(a);
    break;
}

// Word: 3FD (ROM line 401)
// Match: 101.11101101.0001
// ED Opcodes: ED
// -------------------------------------------------------------------------
// ZERO -> LC                     ---  CALL EM_INT (03) -> 7180 [Line 1E8]
// -------------------------------------------------------------------------
case 0x5ed1:
{
    const uint16_t a = 0;
    r[LC] = a;
    jumpFar(0x7180);
    break;
}

// Word: 3F8 (ROM line 3FC)
// Match: 101.11111101.0000
// ED Opcodes: FD
// -------------------------------------------------------------------------
// SP -> DP        SP -> tmpA     ---  IC=SUSP, EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x5fd0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[SP];
    const uint16_t b = r[SP];
    writeIndex(a);
    r[TA] = b;
    suspendPrefetch();
    requestRead(Segment::SS);
    break;
}

// Word: 3F9 (ROM line 3FD)
// Match: 101.11111101.0001
// ED Opcodes: FD
// -------------------------------------------------------------------------
//                                ---  IC={0}
// -------------------------------------------------------------------------
case 0x5fd1:
{
    leaveEmulation();
    break;
}

// Word: 3FA (ROM line 3FE)
// Match: 101.11111101.0010
// ED Opcodes: FD
// -------------------------------------------------------------------------
//                                ---  CALL IRET (01) -> 7080 [Line 1E0]
// -------------------------------------------------------------------------
case 0x5fd2:
{
    jumpFar(0x7080);
    break;
}

// Word: 348 (ROM line 34C)
// Match: 110.00000000.0000
// 8080 Opcodes: 00
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x6000:
{
    endRequested = true;
    break;
}

// Word: 354 (ROM line 358)
// Match: 110.00??0001.0000
// 8080 Opcodes: 01, 11, 21, 31
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x6010:
case 0x6110:
case 0x6210:
case 0x6310:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 355 (ROM line 359)
// Match: 110.00??0001.0001
// 8080 Opcodes: 01, 11, 21, 31
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6011:
case 0x6111:
case 0x6211:
case 0x6311:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 356 (ROM line 35A)
// Match: 110.00??0001.0010
// 8080 Opcodes: 01, 11, 21, 31
// -------------------------------------------------------------------------
// tmpA -> OP2                    --E  --
// -------------------------------------------------------------------------
case 0x6012:
case 0x6112:
case 0x6212:
case 0x6312:
{
    const uint16_t a = r[TA];
    writeOperand(op2, a);
    endRequested = true;
    break;
}

// Word: 36C (ROM line 370)
// Match: 110.000?0010.0000
// 8080 Opcodes: 02, 12
// -------------------------------------------------------------------------
// OP2 -> DP                      ---  --
// -------------------------------------------------------------------------
case 0x6020:
case 0x6120:
{
    const uint16_t a = readOperand(op2);
    writeIndex(a);
    break;
}

// Word: 36D (ROM line 371)
// Match: 110.000?0010.0001
// 8080 Opcodes: 02, 12
// -------------------------------------------------------------------------
// A -> OPR                       --E  EC=MW
// -------------------------------------------------------------------------
case 0x6021:
case 0x6121:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[AX];
    writeOpr(a);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 36E (ROM line 372)
// Match: 110.000?0010.0010
// 8080 Opcodes: 02, 12
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6022:
case 0x6122:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 388 (ROM line 38C)
// Match: 110.00??0011.0000
// 8080 Opcodes: 03, 13, 23, 33
// -------------------------------------------------------------------------
// OP2 -> tmpB                    --E  ALU INC, tmpB
// -------------------------------------------------------------------------
case 0x6030:
case 0x6130:
case 0x6230:
case 0x6330:
{
    const uint16_t a = readOperand(op2);
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc, TB);
    endRequested = true;
    break;
}

// Word: 389 (ROM line 38D)
// Match: 110.00??0011.0001
// 8080 Opcodes: 03, 13, 23, 33
// -------------------------------------------------------------------------
// SIGMA -> OP2                   ---  --
// -------------------------------------------------------------------------
case 0x6031:
case 0x6131:
case 0x6231:
case 0x6331:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op2, a);
    break;
}

// Word: 380 (ROM line 384)
// Match: 110.00???100.0000
// 8080 Opcodes: 04, 0C, 14, 1C, 24, 2C, 34, 3C
// -------------------------------------------------------------------------
// OP2 -> tmpB                    ---  ALU INC, tmpB
// -------------------------------------------------------------------------
case 0x6040:
case 0x60c0:
case 0x6140:
case 0x61c0:
case 0x6240:
case 0x62c0:
case 0x6340:
case 0x63c0:
{
    const uint16_t a = readOperand(op2);
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc, TB);
    break;
}

// Word: 381 (ROM line 385)
// Match: 110.00???100.0001
// 8080 Opcodes: 04, 0C, 14, 1C, 24, 2C, 34, 3C
// -------------------------------------------------------------------------
// B -> DP                        ---  --
// -------------------------------------------------------------------------
case 0x6041:
case 0x60c1:
case 0x6141:
case 0x61c1:
case 0x6241:
case 0x62c1:
case 0x6341:
case 0x63c1:
{
    const uint16_t a = r[BX];
    writeIndex(a);
    break;
}

// Word: 382 (ROM line 386)
// Match: 110.00???100.0010
// 8080 Opcodes: 04, 0C, 14, 1C, 24, 2C, 34, 3C
// -------------------------------------------------------------------------
// SIGMA -> OP2                   -WE  EC=COMMIT
// -------------------------------------------------------------------------
case 0x6042:
case 0x60c2:
case 0x6142:
case 0x61c2:
case 0x6242:
case 0x62c2:
case 0x6342:
case 0x63c2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op2, a);
    commitAluFlags();
    commitOperand();
    endRequested = true;
    break;
}

// Word: 383 (ROM line 387)
// Match: 110.00???100.0011
// 8080 Opcodes: 04, 0C, 14, 1C, 24, 2C, 34, 3C
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6043:
case 0x60c3:
case 0x6143:
case 0x61c3:
case 0x6243:
case 0x62c3:
case 0x6343:
case 0x63c3:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 384 (ROM line 388)
// Match: 110.00???101.0000
// 8080 Opcodes: 05, 0D, 15, 1D, 25, 2D, 35, 3D
// -------------------------------------------------------------------------
// OP2 -> tmpB                    ---  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x6050:
case 0x60d0:
case 0x6150:
case 0x61d0:
case 0x6250:
case 0x62d0:
case 0x6350:
case 0x63d0:
{
    const uint16_t a = readOperand(op2);
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec, TB);
    break;
}

// Word: 385 (ROM line 389)
// Match: 110.00???101.0001
// 8080 Opcodes: 05, 0D, 15, 1D, 25, 2D, 35, 3D
// -------------------------------------------------------------------------
// B -> DP                        ---  --
// -------------------------------------------------------------------------
case 0x6051:
case 0x60d1:
case 0x6151:
case 0x61d1:
case 0x6251:
case 0x62d1:
case 0x6351:
case 0x63d1:
{
    const uint16_t a = r[BX];
    writeIndex(a);
    break;
}

// Word: 386 (ROM line 38A)
// Match: 110.00???101.0010
// 8080 Opcodes: 05, 0D, 15, 1D, 25, 2D, 35, 3D
// -------------------------------------------------------------------------
// SIGMA -> OP2                   -WE  EC=COMMIT
// -------------------------------------------------------------------------
case 0x6052:
case 0x60d2:
case 0x6152:
case 0x61d2:
case 0x6252:
case 0x62d2:
case 0x6352:
case 0x63d2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op2, a);
    commitAluFlags();
    commitOperand();
    endRequested = true;
    break;
}

// Word: 387 (ROM line 38B)
// Match: 110.00???101.0011
// 8080 Opcodes: 05, 0D, 15, 1D, 25, 2D, 35, 3D
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6053:
case 0x60d3:
case 0x6153:
case 0x61d3:
case 0x6253:
case 0x62d3:
case 0x6353:
case 0x63d3:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 350 (ROM line 354)
// Match: 110.00???110.0000
// 8080 Opcodes: 06, 0E, 16, 1E, 26, 2E, 36, 3E
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x6060:
case 0x60e0:
case 0x6160:
case 0x61e0:
case 0x6260:
case 0x62e0:
case 0x6360:
case 0x63e0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 351 (ROM line 355)
// Match: 110.00???110.0001
// 8080 Opcodes: 06, 0E, 16, 1E, 26, 2E, 36, 3E
// -------------------------------------------------------------------------
// B -> DP                        ---  --
// -------------------------------------------------------------------------
case 0x6061:
case 0x60e1:
case 0x6161:
case 0x61e1:
case 0x6261:
case 0x62e1:
case 0x6361:
case 0x63e1:
{
    const uint16_t a = r[BX];
    writeIndex(a);
    break;
}

// Word: 352 (ROM line 356)
// Match: 110.00???110.0010
// 8080 Opcodes: 06, 0E, 16, 1E, 26, 2E, 36, 3E
// -------------------------------------------------------------------------
// tmpA -> OP2                    --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x6062:
case 0x60e2:
case 0x6162:
case 0x61e2:
case 0x6262:
case 0x62e2:
case 0x6362:
case 0x63e2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeOperand(op2, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 353 (ROM line 357)
// Match: 110.00???110.0011
// 8080 Opcodes: 06, 0E, 16, 1E, 26, 2E, 36, 3E
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6063:
case 0x60e3:
case 0x6163:
case 0x61e3:
case 0x6263:
case 0x62e3:
case 0x6363:
case 0x63e3:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 3A4 (ROM line 3A8)
// Match: 110.000??111.0000
// 8080 Opcodes: 07, 0F, 17, 1F
// -------------------------------------------------------------------------
// 1 -> LC                        ---  --
// -------------------------------------------------------------------------
case 0x6070:
case 0x60f0:
case 0x6170:
case 0x61f0:
{
    const uint16_t a = 1;
    r[LC] = a;
    break;
}

// Word: 3A5 (ROM line 3A9)
// Match: 110.000??111.0001
// 8080 Opcodes: 07, 0F, 17, 1F
// -------------------------------------------------------------------------
// A -> tmpB                      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x6071:
case 0x60f1:
case 0x6171:
case 0x61f1:
{
    const uint16_t a = r[AX];
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 3A6 (ROM line 3AA)
// Match: 110.000??111.0010
// 8080 Opcodes: 07, 0F, 17, 1F
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  -W-  ALU XI, tmpB, R
// -------------------------------------------------------------------------
case 0x6072:
case 0x60f2:
case 0x6172:
case 0x61f2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDecodedAlu<true, true>(TB);
    break;
}

// Word: 3A7 (ROM line 3AB)
// Match: 110.000??111.0011
// 8080 Opcodes: 07, 0F, 17, 1F
// -------------------------------------------------------------------------
// SIGMA -> AL                    --E  --
// -------------------------------------------------------------------------
case 0x6073:
case 0x60f3:
case 0x6173:
case 0x61f3:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(0, a);
    endRequested = true;
    break;
}

// Word: 398 (ROM line 39C)
// Match: 110.00??1001.0000
// 8080 Opcodes: 09, 19, 29, 39
// -------------------------------------------------------------------------
// OP2 -> tmpA     B -> tmpB      ---  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x6090:
case 0x6190:
case 0x6290:
case 0x6390:
{
    const uint16_t a = readOperand(op2);
    const uint16_t b = r[BX];
    r[TA] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 399 (ROM line 39D)
// Match: 110.00??1001.0001
// 8080 Opcodes: 09, 19, 29, 39
// -------------------------------------------------------------------------
// SIGMA -> B                     --E  --
// -------------------------------------------------------------------------
case 0x6091:
case 0x6191:
case 0x6291:
case 0x6391:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BX] = a;
    endRequested = true;
    break;
}

// Word: 368 (ROM line 36C)
// Match: 110.000?1010.0000
// 8080 Opcodes: 0A, 1A
// -------------------------------------------------------------------------
// OP2 -> DP                      ---  EC=MR
// -------------------------------------------------------------------------
case 0x60a0:
case 0x61a0:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readOperand(op2);
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 369 (ROM line 36D)
// Match: 110.000?1010.0001
// 8080 Opcodes: 0A, 1A
// -------------------------------------------------------------------------
// OPR -> AL                      F-E  --
// -------------------------------------------------------------------------
case 0x60a1:
case 0x61a1:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeByteReg(0, a);
    endRequested = true;
    break;
}

// Word: 38C (ROM line 390)
// Match: 110.00??1011.0000
// 8080 Opcodes: 0B, 1B, 2B, 3B
// -------------------------------------------------------------------------
// OP2 -> tmpB                    --E  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x60b0:
case 0x61b0:
case 0x62b0:
case 0x63b0:
{
    const uint16_t a = readOperand(op2);
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec, TB);
    endRequested = true;
    break;
}

// Word: 38D (ROM line 391)
// Match: 110.00??1011.0001
// 8080 Opcodes: 0B, 1B, 2B, 3B
// -------------------------------------------------------------------------
// SIGMA -> OP2                   ---  --
// -------------------------------------------------------------------------
case 0x60b1:
case 0x61b1:
case 0x62b1:
case 0x63b1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op2, a);
    break;
}

// Word: 364 (ROM line 368)
// Match: 110.00100010.0000
// 8080 Opcodes: 22
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x6220:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 365 (ROM line 369)
// Match: 110.00100010.0001
// 8080 Opcodes: 22
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6221:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 366 (ROM line 36A)
// Match: 110.00100010.0010
// 8080 Opcodes: 22
// -------------------------------------------------------------------------
// B -> OPR        SIGMA -> IND   --E  EC=MW
// -------------------------------------------------------------------------
case 0x6222:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[BX];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 367 (ROM line 36B)
// Match: 110.00100010.0011
// 8080 Opcodes: 22
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6223:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 39C (ROM line 3A0)
// Match: 110.00100111.0000
// 8080 Opcodes: 27
// -------------------------------------------------------------------------
// A -> tmpA                      ---  ALU ADJD, tmpA
// -------------------------------------------------------------------------
case 0x6270:
{
    const uint16_t a = r[AX];
    r[TA] = a;
    setupAlu<false, false>(Alu::AdjustDecimal, TA);
    break;
}

// Word: 39D (ROM line 3A1)
// Match: 110.00100111.0001
// 8080 Opcodes: 27
// -------------------------------------------------------------------------
// K -> tmpB                      --E  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x6271:
{
    const uint16_t a = readK();
    r[TB] = a;
    setupAlu<false, false>(Alu::Add, TA);
    endRequested = true;
    break;
}

// Word: 39E (ROM line 3A2)
// Match: 110.00100111.0010
// 8080 Opcodes: 27
// -------------------------------------------------------------------------
// SIGMA -> AL     SIGMA -> NULL  -W-  --
// -------------------------------------------------------------------------
case 0x6272:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeByteReg(0, a);
    (void)b;
    commitAluFlags();
    break;
}

// Word: 360 (ROM line 364)
// Match: 110.00101010.0000
// 8080 Opcodes: 2A
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x62a0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 361 (ROM line 365)
// Match: 110.00101010.0001
// 8080 Opcodes: 2A
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x62a1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 362 (ROM line 366)
// Match: 110.00101010.0010
// 8080 Opcodes: 2A
// -------------------------------------------------------------------------
// tmpA -> DP                     ---  EC=MR
// -------------------------------------------------------------------------
case 0x62a2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 363 (ROM line 367)
// Match: 110.00101010.0011
// 8080 Opcodes: 2A
// -------------------------------------------------------------------------
// OPR -> B                       F-E  --
// -------------------------------------------------------------------------
case 0x62a3:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[BX] = a;
    endRequested = true;
    break;
}

// Word: 3A0 (ROM line 3A4)
// Match: 110.00101111.0000
// 8080 Opcodes: 2F
// -------------------------------------------------------------------------
// A -> tmpA                      --E  ALU NOT, tmpA
// -------------------------------------------------------------------------
case 0x62f0:
{
    const uint16_t a = r[AX];
    r[TA] = a;
    setupAlu<false, false>(Alu::Not, TA);
    endRequested = true;
    break;
}

// Word: 3A1 (ROM line 3A5)
// Match: 110.00101111.0001
// 8080 Opcodes: 2F
// -------------------------------------------------------------------------
// SIGMA -> AL                    ---  --
// -------------------------------------------------------------------------
case 0x62f1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(0, a);
    break;
}

// Word: 35C (ROM line 360)
// Match: 110.00110010.0000
// 8080 Opcodes: 32
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x6320:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 35D (ROM line 361)
// Match: 110.00110010.0001
// 8080 Opcodes: 32
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6321:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 35E (ROM line 362)
// Match: 110.00110010.0010
// 8080 Opcodes: 32
// -------------------------------------------------------------------------
// A -> OPR        SIGMA -> IND   --E  EC=MW
// -------------------------------------------------------------------------
case 0x6322:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[AX];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 35F (ROM line 363)
// Match: 110.00110010.0011
// 8080 Opcodes: 32
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6323:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 358 (ROM line 35C)
// Match: 110.00111010.0000
// 8080 Opcodes: 3A
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x63a0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 359 (ROM line 35D)
// Match: 110.00111010.0001
// 8080 Opcodes: 3A
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x63a1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 35A (ROM line 35E)
// Match: 110.00111010.0010
// 8080 Opcodes: 3A
// -------------------------------------------------------------------------
// tmpA -> DP                     ---  EC=MR
// -------------------------------------------------------------------------
case 0x63a2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeIndex(a);
    requestRead(Segment::Default);
    break;
}

// Word: 35B (ROM line 35F)
// Match: 110.00111010.0011
// 8080 Opcodes: 3A
// -------------------------------------------------------------------------
// OPR -> AL                      F-E  --
// -------------------------------------------------------------------------
case 0x63a3:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeByteReg(0, a);
    endRequested = true;
    break;
}

// Word: 34C (ROM line 350)
// Match: 110.01??????.0000
// 8080 Opcodes: 40-75, 77-7F
// -------------------------------------------------------------------------
// OP1 -> tmpA                    ---  --
// -------------------------------------------------------------------------
case 0x6400:
case 0x6410:
case 0x6420:
case 0x6430:
case 0x6440:
case 0x6450:
case 0x6460:
case 0x6470:
case 0x6480:
case 0x6490:
case 0x64a0:
case 0x64b0:
case 0x64c0:
case 0x64d0:
case 0x64e0:
case 0x64f0:
case 0x6500:
case 0x6510:
case 0x6520:
case 0x6530:
case 0x6540:
case 0x6550:
case 0x6560:
case 0x6570:
case 0x6580:
case 0x6590:
case 0x65a0:
case 0x65b0:
case 0x65c0:
case 0x65d0:
case 0x65e0:
case 0x65f0:
case 0x6600:
case 0x6610:
case 0x6620:
case 0x6630:
case 0x6640:
case 0x6650:
case 0x6660:
case 0x6670:
case 0x6680:
case 0x6690:
case 0x66a0:
case 0x66b0:
case 0x66c0:
case 0x66d0:
case 0x66e0:
case 0x66f0:
case 0x6700:
case 0x6710:
case 0x6720:
case 0x6730:
case 0x6740:
case 0x6750:
case 0x6760:
case 0x6770:
case 0x6780:
case 0x6790:
case 0x67a0:
case 0x67b0:
case 0x67c0:
case 0x67d0:
case 0x67e0:
case 0x67f0:
{
    const uint16_t a = readOperand(op1);
    r[TA] = a;
    break;
}

// Word: 34D (ROM line 351)
// Match: 110.01??????.0001
// 8080 Opcodes: 40-75, 77-7F
// -------------------------------------------------------------------------
// B -> DP                        ---  --
// -------------------------------------------------------------------------
case 0x6401:
case 0x6411:
case 0x6421:
case 0x6431:
case 0x6441:
case 0x6451:
case 0x6461:
case 0x6471:
case 0x6481:
case 0x6491:
case 0x64a1:
case 0x64b1:
case 0x64c1:
case 0x64d1:
case 0x64e1:
case 0x64f1:
case 0x6501:
case 0x6511:
case 0x6521:
case 0x6531:
case 0x6541:
case 0x6551:
case 0x6561:
case 0x6571:
case 0x6581:
case 0x6591:
case 0x65a1:
case 0x65b1:
case 0x65c1:
case 0x65d1:
case 0x65e1:
case 0x65f1:
case 0x6601:
case 0x6611:
case 0x6621:
case 0x6631:
case 0x6641:
case 0x6651:
case 0x6661:
case 0x6671:
case 0x6681:
case 0x6691:
case 0x66a1:
case 0x66b1:
case 0x66c1:
case 0x66d1:
case 0x66e1:
case 0x66f1:
case 0x6701:
case 0x6711:
case 0x6721:
case 0x6731:
case 0x6741:
case 0x6751:
case 0x6761:
case 0x6771:
case 0x6781:
case 0x6791:
case 0x67a1:
case 0x67b1:
case 0x67c1:
case 0x67d1:
case 0x67e1:
case 0x67f1:
{
    const uint16_t a = r[BX];
    writeIndex(a);
    break;
}

// Word: 34E (ROM line 352)
// Match: 110.01??????.0010
// 8080 Opcodes: 40-75, 77-7F
// -------------------------------------------------------------------------
// tmpA -> OP2                    --E  EC=COMMIT
// -------------------------------------------------------------------------
case 0x6402:
case 0x6412:
case 0x6422:
case 0x6432:
case 0x6442:
case 0x6452:
case 0x6462:
case 0x6472:
case 0x6482:
case 0x6492:
case 0x64a2:
case 0x64b2:
case 0x64c2:
case 0x64d2:
case 0x64e2:
case 0x64f2:
case 0x6502:
case 0x6512:
case 0x6522:
case 0x6532:
case 0x6542:
case 0x6552:
case 0x6562:
case 0x6572:
case 0x6582:
case 0x6592:
case 0x65a2:
case 0x65b2:
case 0x65c2:
case 0x65d2:
case 0x65e2:
case 0x65f2:
case 0x6602:
case 0x6612:
case 0x6622:
case 0x6632:
case 0x6642:
case 0x6652:
case 0x6662:
case 0x6672:
case 0x6682:
case 0x6692:
case 0x66a2:
case 0x66b2:
case 0x66c2:
case 0x66d2:
case 0x66e2:
case 0x66f2:
case 0x6702:
case 0x6712:
case 0x6722:
case 0x6732:
case 0x6742:
case 0x6752:
case 0x6762:
case 0x6772:
case 0x6782:
case 0x6792:
case 0x67a2:
case 0x67b2:
case 0x67c2:
case 0x67d2:
case 0x67e2:
case 0x67f2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeOperand(op2, a);
    commitOperand();
    endRequested = true;
    break;
}

// Word: 34F (ROM line 353)
// Match: 110.01??????.0011
// 8080 Opcodes: 40-75, 77-7F
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6403:
case 0x6413:
case 0x6423:
case 0x6433:
case 0x6443:
case 0x6453:
case 0x6463:
case 0x6473:
case 0x6483:
case 0x6493:
case 0x64a3:
case 0x64b3:
case 0x64c3:
case 0x64d3:
case 0x64e3:
case 0x64f3:
case 0x6503:
case 0x6513:
case 0x6523:
case 0x6533:
case 0x6543:
case 0x6553:
case 0x6563:
case 0x6573:
case 0x6583:
case 0x6593:
case 0x65a3:
case 0x65b3:
case 0x65c3:
case 0x65d3:
case 0x65e3:
case 0x65f3:
case 0x6603:
case 0x6613:
case 0x6623:
case 0x6633:
case 0x6643:
case 0x6653:
case 0x6663:
case 0x6673:
case 0x6683:
case 0x6693:
case 0x66a3:
case 0x66b3:
case 0x66c3:
case 0x66d3:
case 0x66e3:
case 0x66f3:
case 0x6703:
case 0x6713:
case 0x6723:
case 0x6733:
case 0x6743:
case 0x6753:
case 0x6763:
case 0x6773:
case 0x6783:
case 0x6793:
case 0x67a3:
case 0x67b3:
case 0x67c3:
case 0x67d3:
case 0x67e3:
case 0x67f3:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 390 (ROM line 394)
// Match: 110.10??????.0000
// 8080 Opcodes: 80-BF
// -------------------------------------------------------------------------
// OP1 -> tmpA     A -> tmpB      ---  ALU XI, tmpA
// -------------------------------------------------------------------------
case 0x6800:
case 0x6810:
case 0x6820:
case 0x6830:
case 0x6840:
case 0x6850:
case 0x6860:
case 0x6870:
case 0x6880:
case 0x6890:
case 0x68a0:
case 0x68b0:
case 0x68c0:
case 0x68d0:
case 0x68e0:
case 0x68f0:
case 0x6900:
case 0x6910:
case 0x6920:
case 0x6930:
case 0x6940:
case 0x6950:
case 0x6960:
case 0x6970:
case 0x6980:
case 0x6990:
case 0x69a0:
case 0x69b0:
case 0x69c0:
case 0x69d0:
case 0x69e0:
case 0x69f0:
case 0x6a00:
case 0x6a10:
case 0x6a20:
case 0x6a30:
case 0x6a40:
case 0x6a50:
case 0x6a60:
case 0x6a70:
case 0x6a80:
case 0x6a90:
case 0x6aa0:
case 0x6ab0:
case 0x6ac0:
case 0x6ad0:
case 0x6ae0:
case 0x6af0:
case 0x6b00:
case 0x6b10:
case 0x6b20:
case 0x6b30:
case 0x6b40:
case 0x6b50:
case 0x6b60:
case 0x6b70:
case 0x6b80:
case 0x6b90:
case 0x6ba0:
case 0x6bb0:
case 0x6bc0:
case 0x6bd0:
case 0x6be0:
case 0x6bf0:
{
    const uint16_t a = readOperand(op1);
    const uint16_t b = r[AX];
    r[TA] = a;
    r[TB] = b;
    setupDecodedAlu<false, false>(TA);
    break;
}

// Word: 391 (ROM line 395)
// Match: 110.10??????.0001
// 8080 Opcodes: 80-BF
// -------------------------------------------------------------------------
// B -> DP                        --E  --
// -------------------------------------------------------------------------
case 0x6801:
case 0x6811:
case 0x6821:
case 0x6831:
case 0x6841:
case 0x6851:
case 0x6861:
case 0x6871:
case 0x6881:
case 0x6891:
case 0x68a1:
case 0x68b1:
case 0x68c1:
case 0x68d1:
case 0x68e1:
case 0x68f1:
case 0x6901:
case 0x6911:
case 0x6921:
case 0x6931:
case 0x6941:
case 0x6951:
case 0x6961:
case 0x6971:
case 0x6981:
case 0x6991:
case 0x69a1:
case 0x69b1:
case 0x69c1:
case 0x69d1:
case 0x69e1:
case 0x69f1:
case 0x6a01:
case 0x6a11:
case 0x6a21:
case 0x6a31:
case 0x6a41:
case 0x6a51:
case 0x6a61:
case 0x6a71:
case 0x6a81:
case 0x6a91:
case 0x6aa1:
case 0x6ab1:
case 0x6ac1:
case 0x6ad1:
case 0x6ae1:
case 0x6af1:
case 0x6b01:
case 0x6b11:
case 0x6b21:
case 0x6b31:
case 0x6b41:
case 0x6b51:
case 0x6b61:
case 0x6b71:
case 0x6b81:
case 0x6b91:
case 0x6ba1:
case 0x6bb1:
case 0x6bc1:
case 0x6bd1:
case 0x6be1:
case 0x6bf1:
{
    const uint16_t a = r[BX];
    writeIndex(a);
    endRequested = true;
    break;
}

// Word: 392 (ROM line 396)
// Match: 110.10??????.0010
// 8080 Opcodes: 80-BF
// -------------------------------------------------------------------------
// SIGMA -> AL                    -W-  --
// -------------------------------------------------------------------------
case 0x6802:
case 0x6812:
case 0x6822:
case 0x6832:
case 0x6842:
case 0x6852:
case 0x6862:
case 0x6872:
case 0x6882:
case 0x6892:
case 0x68a2:
case 0x68b2:
case 0x68c2:
case 0x68d2:
case 0x68e2:
case 0x68f2:
case 0x6902:
case 0x6912:
case 0x6922:
case 0x6932:
case 0x6942:
case 0x6952:
case 0x6962:
case 0x6972:
case 0x6982:
case 0x6992:
case 0x69a2:
case 0x69b2:
case 0x69c2:
case 0x69d2:
case 0x69e2:
case 0x69f2:
case 0x6a02:
case 0x6a12:
case 0x6a22:
case 0x6a32:
case 0x6a42:
case 0x6a52:
case 0x6a62:
case 0x6a72:
case 0x6a82:
case 0x6a92:
case 0x6aa2:
case 0x6ab2:
case 0x6ac2:
case 0x6ad2:
case 0x6ae2:
case 0x6af2:
case 0x6b02:
case 0x6b12:
case 0x6b22:
case 0x6b32:
case 0x6b42:
case 0x6b52:
case 0x6b62:
case 0x6b72:
case 0x6b82:
case 0x6b92:
case 0x6ba2:
case 0x6bb2:
case 0x6bc2:
case 0x6bd2:
case 0x6be2:
case 0x6bf2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(0, a);
    commitAluFlags();
    break;
}

// Word: 3CD (ROM line 3D1)
// Match: 110.11???000.0001
// 8080 Opcodes: C0, C8, D0, D8, E0, E8, F0, F8
// -------------------------------------------------------------------------
//                                ---  JUMP OPC, 04
// -------------------------------------------------------------------------
case 0x6c01:
case 0x6c81:
case 0x6d01:
case 0x6d81:
case 0x6e01:
case 0x6e81:
case 0x6f01:
case 0x6f81:
{
    if (opcodeCondition()) {
        jumpLocal(4);
    }
    break;
}

// Word: 3CE (ROM line 3D2)
// Match: 110.11???000.0010
// 8080 Opcodes: C0, C8, D0, D8, E0, E8, F0, F8
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x6c02:
case 0x6c82:
case 0x6d02:
case 0x6d82:
case 0x6e02:
case 0x6e82:
case 0x6f02:
case 0x6f82:
{
    endRequested = true;
    break;
}

// Word: 3D0 (ROM line 3D4)
// Match: 110.11???000.0100
// 8080 Opcodes: C0, C8, D0, D8, E0, E8, F0, F8
// -------------------------------------------------------------------------
// BP -> DP                       ---  IC=SUSP, EC=MR
// -------------------------------------------------------------------------
case 0x6c04:
case 0x6c84:
case 0x6d04:
case 0x6d84:
case 0x6e04:
case 0x6e84:
case 0x6f04:
case 0x6f84:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    writeIndex(a);
    suspendPrefetch();
    requestRead(Segment::Default);
    break;
}

// Word: 3D1 (ROM line 3D5)
// Match: 110.11???000.0101
// 8080 Opcodes: C0, C8, D0, D8, E0, E8, F0, F8
// -------------------------------------------------------------------------
// BP -> tmpA                     ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x6c05:
case 0x6c85:
case 0x6d05:
case 0x6d85:
case 0x6e05:
case 0x6e85:
case 0x6f05:
case 0x6f85:
{
    const uint16_t a = r[BP];
    r[TA] = a;
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 3D2 (ROM line 3D6)
// Match: 110.11???000.0110
// 8080 Opcodes: C0, C8, D0, D8, E0, E8, F0, F8
// -------------------------------------------------------------------------
// SIGMA -> BP                    ---  --
// -------------------------------------------------------------------------
case 0x6c06:
case 0x6c86:
case 0x6d06:
case 0x6d86:
case 0x6e06:
case 0x6e86:
case 0x6f06:
case 0x6f86:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BP] = a;
    break;
}

// Word: 3D3 (ROM line 3D7)
// Match: 110.11???000.0111
// 8080 Opcodes: C0, C8, D0, D8, E0, E8, F0, F8
// -------------------------------------------------------------------------
// OPR -> PC                      F-E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6c07:
case 0x6c87:
case 0x6d07:
case 0x6d87:
case 0x6e07:
case 0x6e87:
case 0x6f07:
case 0x6f87:
{
    if (!prefetchFlushReady(true)) { return; }
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[IP] = a;
    flushPrefetch(true, false, true);
    endRequested = true;
    break;
}

// Word: 3E0 (ROM line 3E4)
// Match: 110.110?0001.0000
// 8080 Opcodes: C1, D1
// -------------------------------------------------------------------------
// BP -> DP        BP -> tmpA     ---  EC=MR
// -------------------------------------------------------------------------
case 0x6c10:
case 0x6d10:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    const uint16_t b = r[BP];
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 3E1 (ROM line 3E5)
// Match: 110.110?0001.0001
// 8080 Opcodes: C1, D1
// -------------------------------------------------------------------------
//                                ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x6c11:
case 0x6d11:
{
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 3E2 (ROM line 3E6)
// Match: 110.110?0001.0010
// 8080 Opcodes: C1, D1
// -------------------------------------------------------------------------
// SIGMA -> BP                    ---  --
// -------------------------------------------------------------------------
case 0x6c12:
case 0x6d12:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BP] = a;
    break;
}

// Word: 3E3 (ROM line 3E7)
// Match: 110.110?0001.0011
// 8080 Opcodes: C1, D1
// -------------------------------------------------------------------------
// OPR -> OP2                     F-E  --
// -------------------------------------------------------------------------
case 0x6c13:
case 0x6d13:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op2, a);
    endRequested = true;
    break;
}

// Word: 3AC (ROM line 3B0)
// Match: 110.11???010.0000
// 8080 Opcodes: C2, CA, D2, DA, E2, EA, F2, FA
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x6c20:
case 0x6ca0:
case 0x6d20:
case 0x6da0:
case 0x6e20:
case 0x6ea0:
case 0x6f20:
case 0x6fa0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 3AD (ROM line 3B1)
// Match: 110.11???010.0001
// 8080 Opcodes: C2, CA, D2, DA, E2, EA, F2, FA
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6c21:
case 0x6ca1:
case 0x6d21:
case 0x6da1:
case 0x6e21:
case 0x6ea1:
case 0x6f21:
case 0x6fa1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 3AE (ROM line 3B2)
// Match: 110.11???010.0010
// 8080 Opcodes: C2, CA, D2, DA, E2, EA, F2, FA
// -------------------------------------------------------------------------
//                                ---  JUMP OPC, 05
// -------------------------------------------------------------------------
case 0x6c22:
case 0x6ca2:
case 0x6d22:
case 0x6da2:
case 0x6e22:
case 0x6ea2:
case 0x6f22:
case 0x6fa2:
{
    if (opcodeCondition()) {
        jumpLocal(5);
    }
    break;
}

// Word: 3AF (ROM line 3B3)
// Match: 110.11???010.0011
// 8080 Opcodes: C2, CA, D2, DA, E2, EA, F2, FA
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x6c23:
case 0x6ca3:
case 0x6d23:
case 0x6da3:
case 0x6e23:
case 0x6ea3:
case 0x6f23:
case 0x6fa3:
{
    endRequested = true;
    break;
}

// Word: 3B1 (ROM line 3B5)
// Match: 110.11???010.0101
// 8080 Opcodes: C2, CA, D2, DA, E2, EA, F2, FA
// -------------------------------------------------------------------------
// tmpA -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6c25:
case 0x6ca5:
case 0x6d25:
case 0x6da5:
case 0x6e25:
case 0x6ea5:
case 0x6f25:
case 0x6fa5:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TA];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 3A8 (ROM line 3AC)
// Match: 110.11000011.0000
// 8080 Opcodes: C3
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x6c30:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 3A9 (ROM line 3AD)
// Match: 110.11000011.0001
// 8080 Opcodes: C3
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6c31:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 3AB (ROM line 3AF)
// Match: 110.11000011.0011
// 8080 Opcodes: C3
// -------------------------------------------------------------------------
// tmpA -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6c33:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TA];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 3C0 (ROM line 3C4)
// Match: 110.11???100.0000
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
// Q -> tmpAL      BP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x6c40:
case 0x6cc0:
case 0x6d40:
case 0x6dc0:
case 0x6e40:
case 0x6ec0:
case 0x6f40:
case 0x6fc0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[BP];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 3C1 (ROM line 3C5)
// Match: 110.11???100.0001
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6c41:
case 0x6cc1:
case 0x6d41:
case 0x6dc1:
case 0x6e41:
case 0x6ec1:
case 0x6f41:
case 0x6fc1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 3C2 (ROM line 3C6)
// Match: 110.11???100.0010
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
//                                ---  JUMP OPC, 05
// -------------------------------------------------------------------------
case 0x6c42:
case 0x6cc2:
case 0x6d42:
case 0x6dc2:
case 0x6e42:
case 0x6ec2:
case 0x6f42:
case 0x6fc2:
{
    if (opcodeCondition()) {
        jumpLocal(5);
    }
    break;
}

// Word: 3C3 (ROM line 3C7)
// Match: 110.11???100.0011
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x6c43:
case 0x6cc3:
case 0x6d43:
case 0x6dc3:
case 0x6e43:
case 0x6ec3:
case 0x6f43:
case 0x6fc3:
{
    endRequested = true;
    break;
}

// Word: 3C5 (ROM line 3C9)
// Match: 110.11???100.0101
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
// SIGMA -> BP     SIGMA -> IND   ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x6c45:
case 0x6cc5:
case 0x6d45:
case 0x6dc5:
case 0x6e45:
case 0x6ec5:
case 0x6f45:
case 0x6fc5:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[BP] = a;
    writeIndex(b);
    suspendPrefetch();
    break;
}

// Word: 3C6 (ROM line 3CA)
// Match: 110.11???100.0110
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
// PC -> OPR                      ---  EC=MW
// -------------------------------------------------------------------------
case 0x6c46:
case 0x6cc6:
case 0x6d46:
case 0x6dc6:
case 0x6e46:
case 0x6ec6:
case 0x6f46:
case 0x6fc6:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readPc();
    writeOpr(a);
    requestWrite(Segment::Default);
    break;
}

// Word: 3C7 (ROM line 3CB)
// Match: 110.11???100.0111
// 8080 Opcodes: C4, CC, D4, DC, E4, EC, F4, FC
// -------------------------------------------------------------------------
// tmpA -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6c47:
case 0x6cc7:
case 0x6d47:
case 0x6dc7:
case 0x6e47:
case 0x6ec7:
case 0x6f47:
case 0x6fc7:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TA];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 3D4 (ROM line 3D8)
// Match: 110.110?0101.0000
// 8080 Opcodes: C5, D5
// -------------------------------------------------------------------------
// BP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x6c50:
case 0x6d50:
{
    const uint16_t a = r[BP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 3D5 (ROM line 3D9)
// Match: 110.110?0101.0001
// 8080 Opcodes: C5, D5
// -------------------------------------------------------------------------
// SIGMA -> BP     SIGMA -> IND   ---  --
// -------------------------------------------------------------------------
case 0x6c51:
case 0x6d51:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[BP] = a;
    writeIndex(b);
    break;
}

// Word: 3D6 (ROM line 3DA)
// Match: 110.110?0101.0010
// 8080 Opcodes: C5, D5
// -------------------------------------------------------------------------
// OP2 -> OPR                     --E  EC=MW
// -------------------------------------------------------------------------
case 0x6c52:
case 0x6d52:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readOperand(op2);
    writeOpr(a);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 3D7 (ROM line 3DB)
// Match: 110.110?0101.0011
// 8080 Opcodes: C5, D5
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6c53:
case 0x6d53:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 394 (ROM line 398)
// Match: 110.11???110.0000
// 8080 Opcodes: C6, CE, D6, DE, E6, EE, F6, FE
// -------------------------------------------------------------------------
// Q -> tmpAL      A -> tmpB      ---  ALU XI, tmpA
// -------------------------------------------------------------------------
case 0x6c60:
case 0x6ce0:
case 0x6d60:
case 0x6de0:
case 0x6e60:
case 0x6ee0:
case 0x6f60:
case 0x6fe0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[AX];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupDecodedAlu<false, false>(TA);
    break;
}

// Word: 395 (ROM line 399)
// Match: 110.11???110.0001
// 8080 Opcodes: C6, CE, D6, DE, E6, EE, F6, FE
// -------------------------------------------------------------------------
// SIGMA -> AL                    -WE  --
// -------------------------------------------------------------------------
case 0x6c61:
case 0x6ce1:
case 0x6d61:
case 0x6de1:
case 0x6e61:
case 0x6ee1:
case 0x6f61:
case 0x6fe1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeByteReg(0, a);
    commitAluFlags();
    endRequested = true;
    break;
}

// Word: 3B4 (ROM line 3B8)
// Match: 110.11???111.0000
// 8080 Opcodes: C7, CF, D7, DF, E7, EF, F7, FF
// -------------------------------------------------------------------------
// BP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x6c70:
case 0x6cf0:
case 0x6d70:
case 0x6df0:
case 0x6e70:
case 0x6ef0:
case 0x6f70:
case 0x6ff0:
{
    const uint16_t a = r[BP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 3B5 (ROM line 3B9)
// Match: 110.11???111.0001
// 8080 Opcodes: C7, CF, D7, DF, E7, EF, F7, FF
// -------------------------------------------------------------------------
// SIGMA -> BP     SIGMA -> IND   ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x6c71:
case 0x6cf1:
case 0x6d71:
case 0x6df1:
case 0x6e71:
case 0x6ef1:
case 0x6f71:
case 0x6ff1:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[BP] = a;
    writeIndex(b);
    suspendPrefetch();
    break;
}

// Word: 3B6 (ROM line 3BA)
// Match: 110.11???111.0010
// 8080 Opcodes: C7, CF, D7, DF, E7, EF, F7, FF
// -------------------------------------------------------------------------
// PC -> OPR                      ---  EC=MW
// -------------------------------------------------------------------------
case 0x6c72:
case 0x6cf2:
case 0x6d72:
case 0x6df2:
case 0x6e72:
case 0x6ef2:
case 0x6f72:
case 0x6ff2:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readPc();
    writeOpr(a);
    requestWrite(Segment::Default);
    break;
}

// Word: 3B7 (ROM line 3BB)
// Match: 110.11???111.0011
// 8080 Opcodes: C7, CF, D7, DF, E7, EF, F7, FF
// -------------------------------------------------------------------------
// OPC38 -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6c73:
case 0x6cf3:
case 0x6d73:
case 0x6df3:
case 0x6e73:
case 0x6ef3:
case 0x6f73:
case 0x6ff3:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = (opcode & 0x38);
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 3C8 (ROM line 3CC)
// Match: 110.11001001.0000
// 8080 Opcodes: C9
// -------------------------------------------------------------------------
// BP -> DP                       ---  IC=SUSP, EC=MR
// -------------------------------------------------------------------------
case 0x6c90:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    writeIndex(a);
    suspendPrefetch();
    requestRead(Segment::Default);
    break;
}

// Word: 3C9 (ROM line 3CD)
// Match: 110.11001001.0001
// 8080 Opcodes: C9
// -------------------------------------------------------------------------
// BP -> tmpA                     ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x6c91:
{
    const uint16_t a = r[BP];
    r[TA] = a;
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 3CA (ROM line 3CE)
// Match: 110.11001001.0010
// 8080 Opcodes: C9
// -------------------------------------------------------------------------
// SIGMA -> BP                    ---  --
// -------------------------------------------------------------------------
case 0x6c92:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BP] = a;
    break;
}

// Word: 3CB (ROM line 3CF)
// Match: 110.11001001.0011
// 8080 Opcodes: C9
// -------------------------------------------------------------------------
// OPR -> PC                      F-E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6c93:
{
    if (!prefetchFlushReady(true)) { return; }
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[IP] = a;
    flushPrefetch(true, false, true);
    endRequested = true;
    break;
}

// Word: 3B8 (ROM line 3BC)
// Match: 110.11001101.0000
// 8080 Opcodes: CD
// -------------------------------------------------------------------------
// Q -> tmpAL      BP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x6cd0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    const uint16_t b = r[BP];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 3B9 (ROM line 3BD)
// Match: 110.11001101.0001
// 8080 Opcodes: CD
// -------------------------------------------------------------------------
// Q -> tmpAH                     ---  --
// -------------------------------------------------------------------------
case 0x6cd1:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = (readPrefetchForMicrocode() << 8);
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    break;
}

// Word: 3BA (ROM line 3BE)
// Match: 110.11001101.0010
// 8080 Opcodes: CD
// -------------------------------------------------------------------------
// SIGMA -> BP     SIGMA -> IND   ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x6cd2:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[BP] = a;
    writeIndex(b);
    suspendPrefetch();
    break;
}

// Word: 3BB (ROM line 3BF)
// Match: 110.11001101.0011
// 8080 Opcodes: CD
// -------------------------------------------------------------------------
// PC -> OPR                      ---  EC=MW
// -------------------------------------------------------------------------
case 0x6cd3:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readPc();
    writeOpr(a);
    requestWrite(Segment::Default);
    break;
}

// Word: 3BC (ROM line 3C0)
// Match: 110.11001101.0100
// 8080 Opcodes: CD
// -------------------------------------------------------------------------
// tmpA -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6cd4:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TA];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 3F0 (ROM line 3F4)
// Match: 110.11010011.0000
// 8080 Opcodes: D3
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x6d30:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 3F1 (ROM line 3F5)
// Match: 110.11010011.0001
// 8080 Opcodes: D3
// -------------------------------------------------------------------------
// A -> OPR        SIGMA -> IND   --E  EC=MW, SR=None
// -------------------------------------------------------------------------
case 0x6d31:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[AX];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::Io);
    endRequested = true;
    break;
}

// Word: 3F2 (ROM line 3F6)
// Match: 110.11010011.0010
// 8080 Opcodes: D3
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6d32:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 3F3 (ROM line 3F7)
// Match: 110.11010011.0011
// 8080 Opcodes: D3
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6d33:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 3F4 (ROM line 3F8)
// Match: 110.11011011.0000
// 8080 Opcodes: DB
// -------------------------------------------------------------------------
// Q -> tmpAL                     ---  --
// -------------------------------------------------------------------------
case 0x6db0:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t a = readPrefetchForMicrocode();
    r[TA] = uint8_t(a);
    break;
}

// Word: 3F5 (ROM line 3F9)
// Match: 110.11011011.0001
// 8080 Opcodes: DB
// -------------------------------------------------------------------------
// tmpA -> DP                     ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x6db1:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 3F6 (ROM line 3FA)
// Match: 110.11011011.0010
// 8080 Opcodes: DB
// -------------------------------------------------------------------------
// OPR -> AL                      F-E  --
// -------------------------------------------------------------------------
case 0x6db2:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeByteReg(0, a);
    endRequested = true;
    break;
}

// Word: 3E4 (ROM line 3E8)
// Match: 110.11100001.0000
// 8080 Opcodes: E1
// -------------------------------------------------------------------------
// BP -> DP        BP -> tmpA     ---  EC=MR
// -------------------------------------------------------------------------
case 0x6e10:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    const uint16_t b = r[BP];
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 3E5 (ROM line 3E9)
// Match: 110.11100001.0001
// 8080 Opcodes: E1
// -------------------------------------------------------------------------
//                                ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x6e11:
{
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 3E6 (ROM line 3EA)
// Match: 110.11100001.0010
// 8080 Opcodes: E1
// -------------------------------------------------------------------------
// SIGMA -> BP                    ---  --
// -------------------------------------------------------------------------
case 0x6e12:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BP] = a;
    break;
}

// Word: 3E7 (ROM line 3EB)
// Match: 110.11100001.0011
// 8080 Opcodes: E1
// -------------------------------------------------------------------------
// OPR -> OP2                     F-E  --
// -------------------------------------------------------------------------
case 0x6e13:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeOperand(op2, a);
    endRequested = true;
    break;
}

// Word: 370 (ROM line 374)
// Match: 110.11100011.0000
// 8080 Opcodes: E3
// -------------------------------------------------------------------------
// BP -> DP        B -> tmpA      ---  EC=MR
// -------------------------------------------------------------------------
case 0x6e30:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    const uint16_t b = r[BX];
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 371 (ROM line 375)
// Match: 110.11100011.0001
// 8080 Opcodes: E3
// -------------------------------------------------------------------------
// OPR -> B        BP -> tmpB     F--  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x6e31:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    const uint16_t b = r[BP];
    r[BX] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 372 (ROM line 376)
// Match: 110.11100011.0010
// 8080 Opcodes: E3
// -------------------------------------------------------------------------
// tmpA -> OPR     SIGMA -> IND   --E  EC=MW
// -------------------------------------------------------------------------
case 0x6e32:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 373 (ROM line 377)
// Match: 110.11100011.0011
// 8080 Opcodes: E3
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6e33:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 3D8 (ROM line 3DC)
// Match: 110.11100101.0000
// 8080 Opcodes: E5
// -------------------------------------------------------------------------
// BP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x6e50:
{
    const uint16_t a = r[BP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 3D9 (ROM line 3DD)
// Match: 110.11100101.0001
// 8080 Opcodes: E5
// -------------------------------------------------------------------------
// SIGMA -> BP     SIGMA -> IND   ---  --
// -------------------------------------------------------------------------
case 0x6e51:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[BP] = a;
    writeIndex(b);
    break;
}

// Word: 3DA (ROM line 3DE)
// Match: 110.11100101.0010
// 8080 Opcodes: E5
// -------------------------------------------------------------------------
// OP2 -> OPR                     --E  EC=MW
// -------------------------------------------------------------------------
case 0x6e52:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = readOperand(op2);
    writeOpr(a);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 3DB (ROM line 3DF)
// Match: 110.11100101.0011
// 8080 Opcodes: E5
// -------------------------------------------------------------------------
// PC -> NULL                     ---  --
// -------------------------------------------------------------------------
case 0x6e53:
{
    const uint16_t a = readPc();
    (void)a;
    break;
}

// Word: 378 (ROM line 37C)
// Match: 110.11101001.0000
// 8080 Opcodes: E9
// -------------------------------------------------------------------------
// B -> PC                        --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x6e90:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[BX];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 374 (ROM line 378)
// Match: 110.11101011.0000
// 8080 Opcodes: EB
// -------------------------------------------------------------------------
// B -> tmpA                      ---  --
// -------------------------------------------------------------------------
case 0x6eb0:
{
    const uint16_t a = r[BX];
    r[TA] = a;
    break;
}

// Word: 375 (ROM line 379)
// Match: 110.11101011.0001
// 8080 Opcodes: EB
// -------------------------------------------------------------------------
// D -> B                         --E  --
// -------------------------------------------------------------------------
case 0x6eb1:
{
    const uint16_t a = r[DX];
    r[BX] = a;
    endRequested = true;
    break;
}

// Word: 376 (ROM line 37A)
// Match: 110.11101011.0010
// 8080 Opcodes: EB
// -------------------------------------------------------------------------
// tmpA -> D                      ---  --
// -------------------------------------------------------------------------
case 0x6eb2:
{
    const uint16_t a = r[TA];
    r[DX] = a;
    break;
}

// Word: 3E8 (ROM line 3EC)
// Match: 110.11110001.0000
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// BP -> DP        A -> tmpB      ---  EC=MR
// -------------------------------------------------------------------------
case 0x6f10:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[BP];
    const uint16_t b = r[AX];
    writeIndex(a);
    r[TB] = b;
    requestRead(Segment::Default);
    break;
}

// Word: 3E9 (ROM line 3ED)
// Match: 110.11110001.0001
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// OPR -> A                       F--  --
// -------------------------------------------------------------------------
case 0x6f11:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[AX] = a;
    break;
}

// Word: 3EA (ROM line 3EE)
// Match: 110.11110001.0010
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// AL:AH -> tmpA                  ---  --
// -------------------------------------------------------------------------
case 0x6f12:
{
    const uint16_t a = swappedAccumulator();
    r[TA] = a;
    break;
}

// Word: 3EB (ROM line 3EF)
// Match: 110.11110001.0011
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// tmpB -> tmpAH   A -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x6f13:
{
    const uint16_t a = r[TB];
    const uint16_t b = r[AX];
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 3EC (ROM line 3F0)
// Match: 110.11110001.0100
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// tmpA -> A       SIGMA -> tmpA  ---  --
// -------------------------------------------------------------------------
case 0x6f14:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    r[AX] = a;
    r[TA] = b;
    break;
}

// Word: 3ED (ROM line 3F1)
// Match: 110.11110001.0101
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// FLAGS -> tmpAH  BP -> tmpB     ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x6f15:
{
    const uint16_t a = r[FLAGS];
    const uint16_t b = r[BP];
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    r[TB] = b;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 3EE (ROM line 3F2)
// Match: 110.11110001.0110
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// tmpA -> FLAGS                  --E  --
// -------------------------------------------------------------------------
case 0x6f16:
{
    const uint16_t a = r[TA];
    writeFlags(a);
    endRequested = true;
    break;
}

// Word: 3EF (ROM line 3F3)
// Match: 110.11110001.0111
// 8080 Opcodes: F1
// -------------------------------------------------------------------------
// SIGMA -> BP                    ---  --
// -------------------------------------------------------------------------
case 0x6f17:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BP] = a;
    break;
}

// Word: 3DC (ROM line 3E0)
// Match: 110.11110101.0000
// 8080 Opcodes: F5
// -------------------------------------------------------------------------
// FLAGS -> tmpAL  BP -> tmpB     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x6f50:
{
    const uint16_t a = r[FLAGS];
    const uint16_t b = r[BP];
    r[TA] = uint8_t(a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 3DD (ROM line 3E1)
// Match: 110.11110101.0001
// 8080 Opcodes: F5
// -------------------------------------------------------------------------
// AL:AH -> tmpAH  SIGMA -> IND   ---  --
// -------------------------------------------------------------------------
case 0x6f51:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = swappedAccumulator();
    const uint16_t b = sigma;
    r[TA] = (r[TA] & 0xff) | (a & 0xff00);
    writeIndex(b);
    break;
}

// Word: 3DE (ROM line 3E2)
// Match: 110.11110101.0010
// 8080 Opcodes: F5
// -------------------------------------------------------------------------
// tmpA -> OPR                    --E  EC=MW
// -------------------------------------------------------------------------
case 0x6f52:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TA];
    writeOpr(a);
    requestWrite(Segment::Default);
    endRequested = true;
    break;
}

// Word: 3DF (ROM line 3E3)
// Match: 110.11110101.0011
// 8080 Opcodes: F5
// -------------------------------------------------------------------------
// SIGMA -> BP                    ---  --
// -------------------------------------------------------------------------
case 0x6f53:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[BP] = a;
    break;
}

// Word: 37C (ROM line 380)
// Match: 110.11111001.0000
// 8080 Opcodes: F9
// -------------------------------------------------------------------------
// B -> BP                        --E  --
// -------------------------------------------------------------------------
case 0x6f90:
{
    const uint16_t a = r[BX];
    r[BP] = a;
    endRequested = true;
    break;
}

// Word: 1D8 (ROM line 1D8)
// Match: 111.00000000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// 1 -> tmpBL                     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x7000:
{
    const uint16_t a = 1;
    r[TB] = extendByte(a);
    suspendPrefetch();
    break;
}

// Word: 1D9 (ROM line 1D9)
// Match: 111.00000000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x7001:
{
    jumpFar(0x7100);
    break;
}

// Word: 1DA (ROM line 1DA)
// Match: 111.00000000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// 2 -> tmpBL                     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x7002:
{
    const uint16_t a = 2;
    r[TB] = extendByte(a);
    suspendPrefetch();
    break;
}

// Word: 1DB (ROM line 1DB)
// Match: 111.00000000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x7003:
{
    jumpFar(0x7100);
    break;
}

// Word: V30 1DC (ROM line 1E0); V20 1DC (ROM line 1DC)
// Match: 111.00000010.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// V30: ZERO -> DP                     ---  IC=SUSP, EC=INTA, SR=None
// V20: A -> tmpC                      ---  IC=SUSP, EC=INTA, SR=None
// -------------------------------------------------------------------------
case 0x7020:
{
    if (model() == Model::V20) {
        if (!requestSlotReady()) { return; }
        const uint16_t a = r[AX];
        r[TC] = a;
        suspendPrefetch();
        requestInterruptAcknowledge();
    } else {
        if (!requestSlotReady()) { return; }
        const uint16_t a = 0;
        writeIndex(a);
        suspendPrefetch();
        requestInterruptAcknowledge();
    }
    break;
}

// Word: V30 1DD (ROM line 1E1); V20 1DD (ROM line 1DD)
// Match: 111.00000010.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// V30: OPR -> tmpB                    F--  --
// V20: OPR -> A                       F--  --
// -------------------------------------------------------------------------
case 0x7021:
{
    if (model() == Model::V20) {
        if (!operandAccessReady()) { return; }
        latchOprFromRead();
        const uint16_t a = readOpr();
        r[AX] = a;
    } else {
        if (!operandAccessReady()) { return; }
        latchOprFromRead();
        const uint16_t a = readOpr();
        r[TB] = a;
    }
    break;
}

// Word: V30 1DE (ROM line 1E2); V20 1DE (ROM line 1DE)
// Match: 111.00000010.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// V30: ZERO -> DP                     ---  EC=INTA, SR=None
// V20: AL:AH -> tmpBL                 ---  --
// -------------------------------------------------------------------------
case 0x7022:
{
    if (model() == Model::V20) {
        const uint16_t a = swappedAccumulator();
        r[TB] = extendByte(a);
    } else {
        if (!requestSlotReady()) { return; }
        const uint16_t a = 0;
        writeIndex(a);
        requestInterruptAcknowledge();
    }
    break;
}

// Word: V30 1DF (ROM line 1E3); V20 1DF (ROM line 1DF)
// Match: 111.00000010.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// V30: OPR -> tmpB                    F--  CALL INT (02) -> 7100 [Line 1E8]
// V20: tmpC -> A                      ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x7023:
{
    if (model() == Model::V20) {
        const uint16_t a = r[TC];
        r[AX] = a;
        jumpFar(0x7100);
    } else {
        if (!operandAccessReady()) { return; }
        latchOprFromRead();
        const uint16_t a = readOpr();
        r[TB] = a;
        jumpFar(0x7100);
    }
    break;
}

// Word: 1D0 (ROM line 1D0)
// Match: 111.00000011.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> DS      ZERO -> tmpB   ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x7030:
{
    const uint16_t a = 0;
    const uint16_t b = 0;
    writeSegment(DS, a);
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 1D1 (ROM line 1D1)
// Match: 111.00000011.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> FLAGS                  ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x7031:
{
    const uint16_t a = 0;
    writeFlags(a);
    suspendPrefetch();
    break;
}

// Word: 1D2 (ROM line 1D2)
// Match: 111.00000011.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// K -> CS                        ---  --
// -------------------------------------------------------------------------
case 0x7032:
{
    const uint16_t a = readK();
    writeSegment(CS, a);
    break;
}

// Word: 1D3 (ROM line 1D3)
// Match: 111.00000011.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> PC                     ---  IC=FLUSH
// -------------------------------------------------------------------------
case 0x7033:
{
    if (!prefetchFlushReady(false)) { return; }
    const uint16_t a = 0;
    r[IP] = a;
    flushPrefetch(false, false, false);
    break;
}

// Word: 1D4 (ROM line 1D4)
// Match: 111.00000011.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> ES                     --E  IC=MFS
// -------------------------------------------------------------------------
case 0x7034:
{
    const uint16_t a = 0;
    writeSegment(ES, a);
    r[FLAGS] |= MF;
    endRequested = true;
    break;
}

// Word: 1D5 (ROM line 1D5)
// Match: 111.00000011.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> SS                     ---  --
// -------------------------------------------------------------------------
case 0x7035:
{
    const uint16_t a = 0;
    writeSegment(SS, a);
    break;
}

// Word: 1E0 (ROM line 1E4)
// Match: 111.00001000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  ALU INC2, tmpA
// -------------------------------------------------------------------------
case 0x7080:
{
    setupAlu<false, false>(Alu::Inc2, TA);
    break;
}

// Word: 1E1 (ROM line 1E5)
// Match: 111.00001000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> DP     SIGMA -> tmpA  ---  IC=SUSP, EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7081:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeIndex(a);
    r[TA] = b;
    suspendPrefetch();
    requestRead(Segment::SS);
    break;
}

// Word: 1E2 (ROM line 1E6)
// Match: 111.00001000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> PC                      F--  --
// -------------------------------------------------------------------------
case 0x7082:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[IP] = a;
    break;
}

// Word: 1E3 (ROM line 1E7)
// Match: 111.00001000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> DP     SIGMA -> tmpA  ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7083:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    writeIndex(a);
    r[TA] = b;
    requestRead(Segment::SS);
    break;
}

// Word: 1E4 (ROM line 1E8)
// Match: 111.00001000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> CS                      F--  IC=FLUSH
// -------------------------------------------------------------------------
case 0x7084:
{
    if (!prefetchFlushReady(true)) { return; }
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeSegment(CS, a, true);
    flushPrefetch(true, false, false);
    break;
}

// Word: 1E5 (ROM line 1E9)
// Match: 111.00001000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x7085:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 1E6 (ROM line 1EA)
// Match: 111.00001000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> FLAGS                   F-E  --
// -------------------------------------------------------------------------
case 0x7086:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeFlags(a);
    endRequested = true;
    break;
}

// Word: 1E8 (ROM line 1EC)
// Match: 111.0001?000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> tmpBH                  ---  ALU ADD, tmpB
// -------------------------------------------------------------------------
case 0x7100:
case 0x7180:
{
    const uint16_t a = 0;
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    setupAlu<false, false>(Alu::Add, TB);
    break;
}

// Word: 1E9 (ROM line 1ED)
// Match: 111.0001?000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  IC=SUSP, EC=INTV, SR=None
// -------------------------------------------------------------------------
case 0x7101:
case 0x7181:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    suspendPrefetch();
    selectInterruptVector();
    break;
}

// Word: 1EA (ROM line 1EE)
// Match: 111.0001?000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x7102:
case 0x7182:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 1EB (ROM line 1EF)
// Match: 111.0001?000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU INC2, tmpB
// -------------------------------------------------------------------------
case 0x7103:
case 0x7183:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<false, false>(Alu::Inc2, TB);
    break;
}

// Word: 1EC (ROM line 1F0)
// Match: 111.0001?000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MR, SR=None
// -------------------------------------------------------------------------
case 0x7104:
case 0x7184:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestRead(Segment::Io);
    break;
}

// Word: 1ED (ROM line 1F1)
// Match: 111.0001?000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpC                    F--  --
// -------------------------------------------------------------------------
case 0x7105:
case 0x7185:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TC] = a;
    break;
}

// Word: 1EE (ROM line 1F2)
// Match: 111.0001?000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x7106:
case 0x7186:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 1EF (ROM line 1F3)
// Match: 111.0001?000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpA                    F--  --
// -------------------------------------------------------------------------
case 0x7107:
case 0x7187:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TA] = a;
    break;
}

// Word: 1F0 (ROM line 1F4)
// Match: 111.00010000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// FLAGS -> OPR                   F--  --
// -------------------------------------------------------------------------
case 0x7108:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[FLAGS];
    writeOpr(a);
    break;
}

// Word: 1F1 (ROM line 1F5)
// Match: 111.00010000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  IC=CLR_IF_TF?, EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7109:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    r[FLAGS] &= ~(TF | IF);
    requestWrite(Segment::SS);
    break;
}

// Word: 1F2 (ROM line 1F6)
// Match: 111.00010000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// CS -> OPR       SIGMA -> IND   F--  IC=MFS
// -------------------------------------------------------------------------
case 0x710a:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[CS];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    r[FLAGS] |= MF;
    break;
}

// Word: 1F5 (ROM line 1F9)
// Match: 111.0001?000.1101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> CS      SIGMA -> tmpB  ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x710d:
case 0x718d:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    writeSegment(CS, a);
    r[TB] = b;
    requestWrite(Segment::SS);
    break;
}

// Word: 1F6 (ROM line 1FA)
// Match: 111.0001?000.1110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// PC -> OPR       SIGMA -> IND   F--  --
// -------------------------------------------------------------------------
case 0x710e:
case 0x718e:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readPc();
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    break;
}

// Word: 1F7 (ROM line 1FB)
// Match: 111.0001?000.1111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> PC                     ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x710f:
case 0x718f:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TC];
    r[IP] = a;
    requestWrite(Segment::SS);
    break;
}

// Word: 1F8 (ROM line 1FC)
// Match: 111.0001?001.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x7110:
case 0x7190:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 090 (ROM line 090)
// Match: 111.00011000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// FLAGS -> OPR                   F--  --
// -------------------------------------------------------------------------
case 0x7188:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[FLAGS];
    writeOpr(a);
    break;
}

// Word: 091 (ROM line 091)
// Match: 111.00011000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  IC=MFS, EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7189:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    r[FLAGS] |= MF;
    requestWrite(Segment::SS);
    break;
}

// Word: 092 (ROM line 092)
// Match: 111.00011000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// CS -> OPR       SIGMA -> IND   F--  JUMP JLCNZ, 0C
// -------------------------------------------------------------------------
case 0x718a:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[CS];
    const uint16_t b = sigma;
    writeOpr(a);
    writeIndex(b);
    if (decrementLoopCounter()) {
        jumpLocal(12);
    }
    break;
}

// Word: 093 (ROM line 093)
// Match: 111.00011000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  IC=SETEM
// -------------------------------------------------------------------------
case 0x718b:
{
    enterEmulation();
    break;
}

// Word: 200 (ROM line 204)
// Match: 111.00100000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> tmpB                   ---  ALU ADD, tmpB
// -------------------------------------------------------------------------
case 0x7200:
{
    const uint16_t a = r[TA];
    r[TB] = a;
    setupAlu<false, false>(Alu::Add, TB);
    break;
}

// Word: 201 (ROM line 205)
// Match: 111.00100000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> NULL   ZERO -> tmpB   -W-  ALU ADC, tmpC
// -------------------------------------------------------------------------
case 0x7201:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = 0;
    (void)a;
    r[TB] = b;
    commitAluFlags();
    setupAlu<false, true>(Alu::Adc, TC);
    break;
}

// Word: 202 (ROM line 206)
// Match: 111.00100000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  CALL MUL2 (05) -> 7280 [Line 204]
// -------------------------------------------------------------------------
case 0x7202:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    jumpFar(0x7280);
    break;
}

// Word: 204 (ROM line 208)
// Match: 111.00101000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  IC=CCOF
// -------------------------------------------------------------------------
case 0x7280:
{
    r[FLAGS] &= ~(CF | OF);
    break;
}

// Word: 205 (ROM line 209)
// Match: 111.00101000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JZ, 03
// -------------------------------------------------------------------------
case 0x7281:
{
    if (aluZero()) {
        jumpLocal(3);
    }
    break;
}

// Word: 206 (ROM line 20A)
// Match: 111.00101000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  IC=SCOF
// -------------------------------------------------------------------------
case 0x7282:
{
    r[FLAGS] |= (CF | OF);
    break;
}

// Word: 207 (ROM line 20B)
// Match: 111.00101000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x7283:
{
    endRequested = true;
    break;
}

// Word: 208 (ROM line 20C)
// Match: 111.0011?000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> tmpB    SIGMA -> tmpA  ---  IC=SIGN
// -------------------------------------------------------------------------
case 0x7300:
case 0x7380:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    r[TB] = a;
    r[TA] = b;
    captureArithmeticSign();
    break;
}

// Word: 20A (ROM line 20E)
// Match: 111.0011?000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpC   ZERO -> tmpB   ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x7302:
case 0x7382:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = 0;
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 20B (ROM line 20F)
// Match: 111.0011?000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// 8 -> LC                        ---  JUMP JNWO, 05
// -------------------------------------------------------------------------
case 0x7303:
case 0x7383:
{
    const uint16_t a = 8;
    r[LC] = a;
    if (!wordSize) {
        jumpLocal(5);
    }
    break;
}

// Word: 20C (ROM line 210)
// Match: 111.0011?000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// 16 -> LC                       ---  --
// -------------------------------------------------------------------------
case 0x7304:
case 0x7384:
{
    const uint16_t a = 16;
    r[LC] = a;
    break;
}

// Word: 20D (ROM line 211)
// Match: 111.0011?000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x7305:
case 0x7385:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 20E (ROM line 212)
// Match: 111.0011?000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> tmpC                   ---  JUMP JPOS/NZ4S, 0C
// -------------------------------------------------------------------------
case 0x7306:
case 0x7386:
{
    const uint16_t a = r[TB];
    r[TC] = a;
    if (nonnegativeResult()) {
        jumpLocal(12);
    }
    break;
}

// Word: 20F (ROM line 213)
// Match: 111.0011?000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  ALU NEG, tmpA
// -------------------------------------------------------------------------
case 0x7307:
case 0x7387:
{
    setupAlu<false, false>(Alu::Neg, TA);
    break;
}

// Word: 210 (ROM line 214)
// Match: 111.0011?000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  -W-  ALU NEG, tmpB
// -------------------------------------------------------------------------
case 0x7308:
case 0x7388:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    commitAluFlags();
    setupAlu<false, true>(Alu::Neg, TB);
    break;
}

// Word: 211 (ROM line 215)
// Match: 111.0011?000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JNC, 0B
// -------------------------------------------------------------------------
case 0x7309:
case 0x7389:
{
    if (!aluCarry()) {
        jumpLocal(11);
    }
    break;
}

// Word: 212 (ROM line 216)
// Match: 111.0011?000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  ALU NOT, tmpB
// -------------------------------------------------------------------------
case 0x730a:
case 0x738a:
{
    setupAlu<false, false>(Alu::Not, TB);
    break;
}

// Word: 213 (ROM line 217)
// Match: 111.0011?000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpC   SIGMA -> tmpB  ---  --
// -------------------------------------------------------------------------
case 0x730b:
case 0x738b:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TC] = a;
    r[TB] = b;
    break;
}

// Word: 0B0 (ROM line 0B0)
// Match: 111.00110000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> tmpC                   ---  JUMP JNW, 0F
// -------------------------------------------------------------------------
case 0x730c:
{
    const uint16_t a = r[TB];
    r[TC] = a;
    if (shortImmediate()) {
        jumpLocal(15);
    }
    break;
}

// Word: 0B1 (ROM line 0B1)
// Match: 111.00110000.1101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> D                      ---  --
// -------------------------------------------------------------------------
case 0x730d:
{
    const uint16_t a = r[TB];
    r[DX] = a;
    break;
}

// Word: 0B2 (ROM line 0B2)
// Match: 111.00110000.1110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> A                      ---  CALL MUL (04) -> 7200 [Line 200]
// -------------------------------------------------------------------------
case 0x730e:
{
    const uint16_t a = r[TA];
    r[AX] = a;
    jumpFar(0x7200);
    break;
}

// Word: 0B3 (ROM line 0B3)
// Match: 111.00110000.1111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> AH                     ---  --
// -------------------------------------------------------------------------
case 0x730f:
{
    const uint16_t a = r[TB];
    writeByteReg(4, a);
    break;
}

// Word: 214 (ROM line 218)
// Match: 111.00110001.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> AL                     ---  CALL MUL (04) -> 7200 [Line 200]
// -------------------------------------------------------------------------
case 0x7310:
{
    const uint16_t a = r[TA];
    writeByteReg(0, a);
    jumpFar(0x7200);
    break;
}

// Word: 218 (ROM line 21C)
// Match: 111.00111000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> OP2                    ---  CALL MUL (04) -> 7200 [Line 200]
// -------------------------------------------------------------------------
case 0x738c:
{
    const uint16_t a = r[TA];
    writeOperand(op2, a);
    jumpFar(0x7200);
    break;
}

// Word: 21C (ROM line 220)
// Match: 111.01000000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// C -> tmpB                      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x7400:
{
    const uint16_t a = r[CX];
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 21D (ROM line 221)
// Match: 111.01000000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// PC -> tmpB      SIGMA -> NULL  ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x7401:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readPc();
    const uint16_t b = sigma;
    r[TB] = a;
    (void)b;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 21E (ROM line 222)
// Match: 111.01000000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JZ, 04
// -------------------------------------------------------------------------
case 0x7402:
{
    if (aluZero()) {
        jumpLocal(4);
    }
    break;
}

// Word: 21F (ROM line 223)
// Match: 111.01000000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP INT, 05
// -------------------------------------------------------------------------
case 0x7403:
{
    const bool interrupt_pending = interruptPending();
    if (interrupt_pending) {
        jumpLocal(5);
    }
    break;
}

// Word: 220 (ROM line 224)
// Match: 111.01000000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x7404:
{
    endRequested = true;
    break;
}

// Word: 221 (ROM line 225)
// Match: 111.01000000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// PFXCNT -> tmpA                 ---  --
// -------------------------------------------------------------------------
case 0x7405:
{
    const uint16_t a = prefixCount;
    r[TA] = a;
    break;
}

// Word: 222 (ROM line 226)
// Match: 111.01000000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x7406:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec, TB);
    break;
}

// Word: 223 (ROM line 227)
// Match: 111.01000000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> PC                    --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x7407:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[IP] = a;
    flushPrefetch(false, true, true);
    endRequested = true;
    break;
}

// Word: 224 (ROM line 228)
// Match: 111.01001000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JZ, 03
// -------------------------------------------------------------------------
case 0x7480:
{
    if (aluZero()) {
        jumpLocal(3);
    }
    break;
}

// Word: 225 (ROM line 229)
// Match: 111.01001000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  -W-  ALU XI, tmpB, R
// -------------------------------------------------------------------------
case 0x7481:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDecodedAlu<true, true>(TB);
    break;
}

// Word: 226 (ROM line 22A)
// Match: 111.01001000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> OP1                   ---  EC=COMMIT
// -------------------------------------------------------------------------
case 0x7482:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    commitOperand();
    break;
}

// Word: 227 (ROM line 22B)
// Match: 111.01001000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                --E  --
// -------------------------------------------------------------------------
case 0x7483:
{
    endRequested = true;
    break;
}

// Word: 260 (ROM line 264)
// Match: 111.01010000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP     Q -> tmpB      ---  --
// -------------------------------------------------------------------------
case 0x7500:
{
    if (microcodePrefetchBytes() < 1) {
        waitForQueue(1);
        return;
    }

    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = readPrefetchForMicrocode();
    r[SP] = a;
    r[TB] = b;
    break;
}

// Word: 261 (ROM line 265)
// Match: 111.01010000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> tmpBH                  ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x7501:
{
    const uint16_t a = 0;
    r[TB] = (r[TB] & 0xff) | (a & 0xff00);
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 262 (ROM line 266)
// Match: 111.01010000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x7502:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    setupAlu<false, false>(Alu::Dec, TB);
    break;
}

// Word: 263 (ROM line 267)
// Match: 111.01010000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SP -> tmpC                     ---  JUMP JZ, 0E
// -------------------------------------------------------------------------
case 0x7503:
{
    const uint16_t a = r[SP];
    r[TC] = a;
    if (aluZero()) {
        jumpLocal(14);
    }
    break;
}

// Word: 264 (ROM line 268)
// Match: 111.01010000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> NULL                  ---  ALU DEC, tmpB
// -------------------------------------------------------------------------
case 0x7504:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    setupAlu<false, false>(Alu::Dec, TB);
    break;
}

// Word: 265 (ROM line 269)
// Match: 111.01010000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> LC                    ---  JUMP JZ, 0B
// -------------------------------------------------------------------------
case 0x7505:
{
    const bool branch = aluZero();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[LC] = a;
    if (branch) {
        jumpLocal(11);
    }
    break;
}

// Word: 266 (ROM line 26A)
// Match: 111.01010000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// BP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x7506:
{
    const uint16_t a = r[BP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 267 (ROM line 26B)
// Match: 111.01010000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> BP     SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7507:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[BP] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 268 (ROM line 26C)
// Match: 111.01010000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  --
// -------------------------------------------------------------------------
case 0x7508:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    break;
}

// Word: 269 (ROM line 26D)
// Match: 111.01010000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP     SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7509:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SP] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 26A (ROM line 26E)
// Match: 111.01010000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JLCNZ, 06
// -------------------------------------------------------------------------
case 0x750a:
{
    if (decrementLoopCounter()) {
        jumpLocal(6);
    }
    break;
}

// Word: 26B (ROM line 26F)
// Match: 111.01010000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SP -> tmpB                     ---  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x750b:
{
    const uint16_t a = r[SP];
    r[TB] = a;
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 26C (ROM line 270)
// Match: 111.01010000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP     SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x750c:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SP] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 26D (ROM line 271)
// Match: 111.01010000.1101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> OPR                    F--  --
// -------------------------------------------------------------------------
case 0x750d:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[TC];
    writeOpr(a);
    break;
}

// Word: 26E (ROM line 272)
// Match: 111.01010000.1110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> BP      SP -> tmpB     --E  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x750e:
{
    const uint16_t a = r[TC];
    const uint16_t b = r[SP];
    r[BP] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Sub, TA);
    endRequested = true;
    break;
}

// Word: 26F (ROM line 273)
// Match: 111.01010000.1111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x750f:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 238 (ROM line 23C)
// Match: 111.01011000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7580:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 239 (ROM line 23D)
// Match: 111.01011000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// D -> OPR                       F--  --
// -------------------------------------------------------------------------
case 0x7581:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[DX];
    writeOpr(a);
    break;
}

// Word: 23A (ROM line 23E)
// Match: 111.01011000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7582:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 23B (ROM line 23F)
// Match: 111.01011000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// B -> OPR                       F--  --
// -------------------------------------------------------------------------
case 0x7583:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[BX];
    writeOpr(a);
    break;
}

// Word: 23C (ROM line 240)
// Match: 111.01011000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7584:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 23D (ROM line 241)
// Match: 111.01011000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SP -> OPR                      F--  --
// -------------------------------------------------------------------------
case 0x7585:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[SP];
    writeOpr(a);
    break;
}

// Word: 23E (ROM line 242)
// Match: 111.01011000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7586:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 23F (ROM line 243)
// Match: 111.01011000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// BP -> OPR                      F--  --
// -------------------------------------------------------------------------
case 0x7587:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[BP];
    writeOpr(a);
    break;
}

// Word: 240 (ROM line 244)
// Match: 111.01011000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7588:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 241 (ROM line 245)
// Match: 111.01011000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SI -> OPR                      F--  --
// -------------------------------------------------------------------------
case 0x7589:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[SI];
    writeOpr(a);
    break;
}

// Word: 242 (ROM line 246)
// Match: 111.01011000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x758a:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 243 (ROM line 247)
// Match: 111.01011000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// DI -> OPR                      F--  --
// -------------------------------------------------------------------------
case 0x758b:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[DI];
    writeOpr(a);
    break;
}

// Word: 244 (ROM line 248)
// Match: 111.01011000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP     SIGMA -> IND   --E  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x758c:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[SP] = a;
    writeIndex(b);
    requestWrite(Segment::SS);
    endRequested = true;
    break;
}

// Word: 24C (ROM line 250)
// Match: 111.01100000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7600:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 24D (ROM line 251)
// Match: 111.01100000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x7601:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    break;
}

// Word: 24E (ROM line 252)
// Match: 111.01100000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> SI                      F--  --
// -------------------------------------------------------------------------
case 0x7602:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[SI] = a;
    break;
}

// Word: 24F (ROM line 253)
// Match: 111.01100000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7603:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 250 (ROM line 254)
// Match: 111.01100000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> BP                      F--  --
// -------------------------------------------------------------------------
case 0x7604:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[BP] = a;
    break;
}

// Word: 251 (ROM line 255)
// Match: 111.01100000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7605:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 252 (ROM line 256)
// Match: 111.01100000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> B                       F--  --
// -------------------------------------------------------------------------
case 0x7606:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[BX] = a;
    break;
}

// Word: 253 (ROM line 257)
// Match: 111.01100000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7607:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 254 (ROM line 258)
// Match: 111.01100000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> D                       F--  --
// -------------------------------------------------------------------------
case 0x7608:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[DX] = a;
    break;
}

// Word: 255 (ROM line 259)
// Match: 111.01100000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB   SIGMA -> IND   ---  EC=MR, SR=SS
// -------------------------------------------------------------------------
case 0x7609:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    r[TB] = a;
    writeIndex(b);
    requestRead(Segment::SS);
    break;
}

// Word: 256 (ROM line 25A)
// Match: 111.01100000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> C                       F--  --
// -------------------------------------------------------------------------
case 0x760a:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[CX] = a;
    break;
}

// Word: 257 (ROM line 25B)
// Match: 111.01100000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x760b:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 258 (ROM line 25C)
// Match: 111.01100000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> A                       F-E  --
// -------------------------------------------------------------------------
case 0x760c:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[AX] = a;
    endRequested = true;
    break;
}

// Word: 228 (ROM line 22C)
// Match: 111.01101000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> tmpC    SP -> tmpB     ---  IC=SUSP
// -------------------------------------------------------------------------
case 0x7680:
{
    const uint16_t a = r[TB];
    const uint16_t b = r[SP];
    r[TC] = a;
    r[TB] = b;
    suspendPrefetch();
    break;
}

// Word: 229 (ROM line 22D)
// Match: 111.01101000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// CS -> OPR                      F--  ALU DEC2, tmpB
// -------------------------------------------------------------------------
case 0x7681:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = r[CS];
    writeOpr(a);
    setupAlu<false, false>(Alu::Dec2, TB);
    break;
}

// Word: 22A (ROM line 22E)
// Match: 111.01101000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> DP                    ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7682:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeIndex(a);
    requestWrite(Segment::SS);
    break;
}

// Word: 22B (ROM line 22F)
// Match: 111.01101000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// PC -> OPR       SIGMA -> tmpB  F--  --
// -------------------------------------------------------------------------
case 0x7683:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readPc();
    const uint16_t b = sigma;
    writeOpr(a);
    r[TB] = b;
    break;
}

// Word: 22C (ROM line 230)
// Match: 111.01101000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> CS      SIGMA -> IND   ---  EC=MW, SR=SS
// -------------------------------------------------------------------------
case 0x7684:
{
    if (!requestSlotReady()) { return; }
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TC];
    const uint16_t b = sigma;
    writeSegment(CS, a);
    writeIndex(b);
    requestWrite(Segment::SS);
    break;
}

// Word: 22D (ROM line 231)
// Match: 111.01101000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x7685:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TA];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 22E (ROM line 232)
// Match: 111.01101000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x7686:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 324 (ROM line 328)
// Match: 111.01110000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// DI -> DP                       ---  JUMP JNC, 0E
// -------------------------------------------------------------------------
case 0x7700:
{
    const uint16_t a = r[DI];
    writeIndex(a);
    if (!aluCarry()) {
        jumpLocal(14);
    }
    break;
}

// Word: 325 (ROM line 329)
// Match: 111.01110000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// 16 -> tmpB                     ---  ALU SUB, tmpA
// -------------------------------------------------------------------------
case 0x7701:
{
    const uint16_t a = 16;
    r[TB] = a;
    setupAlu<false, false>(Alu::Sub, TA);
    break;
}

// Word: 326 (ROM line 32A)
// Match: 111.01110000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> LC                    ---  --
// -------------------------------------------------------------------------
case 0x7702:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[LC] = a;
    break;
}

// Word: 327 (ROM line 32B)
// Match: 111.01110000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpA                    ---  --
// -------------------------------------------------------------------------
case 0x7703:
{
    const uint16_t a = readOpr();
    r[TA] = a;
    break;
}

// Word: 328 (ROM line 32C)
// Match: 111.01110000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> tmpC    A -> tmpB      ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x7704:
{
    const uint16_t a = 0;
    const uint16_t b = r[AX];
    r[TC] = a;
    r[TB] = b;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 329 (ROM line 32D)
// Match: 111.01110000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x7705:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 32A (ROM line 32E)
// Match: 111.01110000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// DI -> tmpC                     ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x7706:
{
    const uint16_t a = r[DI];
    r[TC] = a;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 32B (ROM line 32F)
// Match: 111.01110000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// DI -> DP                       ---  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x7707:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestWrite(Segment::ES);
    break;
}

// Word: 32C (ROM line 330)
// Match: 111.01110000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> OPR                    ---  --
// -------------------------------------------------------------------------
case 0x7708:
{
    const uint16_t a = r[TA];
    writeOpr(a);
    break;
}

// Word: 32D (ROM line 331)
// Match: 111.01110000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OP1 -> tmpAL                   ---  ALU INC2, tmpC
// -------------------------------------------------------------------------
case 0x7709:
{
    const uint16_t a = readOperand(op1);
    r[TA] = uint8_t(a);
    setupAlu<false, false>(Alu::Inc2, TC);
    break;
}

// Word: 32E (ROM line 332)
// Match: 111.01110000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> DI                    ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x770a:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[DI] = a;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 32F (ROM line 333)
// Match: 111.01110000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> LC      SIGMA -> NULL  ---  --
// -------------------------------------------------------------------------
case 0x770b:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[TA];
    const uint16_t b = sigma;
    r[LC] = a;
    (void)b;
    break;
}

// Word: 330 (ROM line 334)
// Match: 111.01110000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> tmpC                   ---  JUMP JNZ, 0E
// -------------------------------------------------------------------------
case 0x770c:
{
    const uint16_t a = 0;
    r[TC] = a;
    if (!aluZero()) {
        jumpLocal(14);
    }
    break;
}

// Word: 331 (ROM line 335)
// Match: 111.01110000.1101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> OP1                   --E  --
// -------------------------------------------------------------------------
case 0x770d:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    writeOperand(op1, a);
    endRequested = true;
    break;
}

// Word: 333 (ROM line 337)
// Match: 111.01110000.1111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// DI -> DP                       ---  EC=MR, SR=ES
// -------------------------------------------------------------------------
case 0x770f:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[DI];
    writeIndex(a);
    requestRead(Segment::ES);
    break;
}

// Word: 334 (ROM line 338)
// Match: 111.01110001.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpA                    ---  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x7710:
{
    const uint16_t a = readOpr();
    r[TA] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 335 (ROM line 339)
// Match: 111.01110001.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU MUL, tmpC, R
// -------------------------------------------------------------------------
case 0x7711:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupMul<true, false>(TC);
    break;
}

// Word: 336 (ROM line 33A)
// Match: 111.01110001.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> tmpC                   ---  --
// -------------------------------------------------------------------------
case 0x7712:
{
    const uint16_t a = r[TA];
    r[TC] = a;
    break;
}

// Word: 337 (ROM line 33B)
// Match: 111.01110001.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OP1 -> tmpAL                   ---  --
// -------------------------------------------------------------------------
case 0x7713:
{
    const uint16_t a = readOperand(op1);
    r[TA] = uint8_t(a);
    break;
}

// Word: 338 (ROM line 33C)
// Match: 111.01110001.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> LC                     ---  --
// -------------------------------------------------------------------------
case 0x7714:
{
    const uint16_t a = r[TA];
    r[LC] = a;
    break;
}

// Word: 339 (ROM line 33D)
// Match: 111.01110001.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpB                    F--  ALU PASS, tmpB
// -------------------------------------------------------------------------
case 0x7715:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TB] = a;
    setupAlu<false, false>(Alu::Pass, TB);
    break;
}

// Word: 33A (ROM line 33E)
// Match: 111.01110001.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU SHR, tmpB, R
// -------------------------------------------------------------------------
case 0x7716:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupAlu<true, false>(Alu::Shr, TB);
    break;
}

// Word: 33B (ROM line 33F)
// Match: 111.01110001.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> LC                     ---  ALU PASS, tmpC
// -------------------------------------------------------------------------
case 0x7717:
{
    const uint16_t a = r[TA];
    r[LC] = a;
    setupAlu<false, false>(Alu::Pass, TC);
    break;
}

// Word: 33C (ROM line 340)
// Match: 111.01110001.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// DI -> DP        SIGMA -> tmpA  ---  --
// -------------------------------------------------------------------------
case 0x7718:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = r[DI];
    const uint16_t b = sigma;
    writeIndex(a);
    r[TA] = b;
    break;
}

// Word: 33D (ROM line 341)
// Match: 111.01110001.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> tmpC                   ---  --
// -------------------------------------------------------------------------
case 0x7719:
{
    const uint16_t a = 0;
    r[TC] = a;
    break;
}

// Word: 33E (ROM line 342)
// Match: 111.01110001.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU DIV, tmpC, R
// -------------------------------------------------------------------------
case 0x771a:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDiv<true, false>(TC);
    break;
}

// Word: 33F (ROM line 343)
// Match: 111.01110001.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> OPR                    --E  EC=MW, SR=ES
// -------------------------------------------------------------------------
case 0x771b:
{
    if (!requestSlotReady()) { return; }
    const uint16_t a = r[TB];
    writeOpr(a);
    requestWrite(Segment::ES);
    endRequested = true;
    break;
}

// Word: 1A0 (ROM line 1A0)
// Match: 111.01111000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// A -> tmpA                      ---  ALU NEG, tmpA
// -------------------------------------------------------------------------
case 0x7780:
{
    const uint16_t a = r[AX];
    r[TA] = a;
    setupAlu<false, false>(Alu::Neg, TA);
    break;
}

// Word: 1A1 (ROM line 1A1)
// Match: 111.01111000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> OPR                    ---  JUMP JNS, 06
// -------------------------------------------------------------------------
case 0x7781:
{
    const uint16_t a = r[TB];
    writeOpr(a);
    if ((r[TB] & (wordSize ? 0x8000 : 0x80)) == 0) {
        jumpLocal(6);
    }
    break;
}

// Word: 1A2 (ROM line 1A2)
// Match: 111.01111000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  -W-  ALU NEG, tmpB
// -------------------------------------------------------------------------
case 0x7782:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    commitAluFlags();
    setupAlu<false, true>(Alu::Neg, TB);
    break;
}

// Word: 1A3 (ROM line 1A3)
// Match: 111.01111000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JNC, 05
// -------------------------------------------------------------------------
case 0x7783:
{
    if (!aluCarry()) {
        jumpLocal(5);
    }
    break;
}

// Word: 1A4 (ROM line 1A4)
// Match: 111.01111000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  ALU NOT, tmpB
// -------------------------------------------------------------------------
case 0x7784:
{
    setupAlu<false, false>(Alu::Not, TB);
    break;
}

// Word: 1A5 (ROM line 1A5)
// Match: 111.01111000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  --
// -------------------------------------------------------------------------
case 0x7785:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    break;
}

// Word: 1A6 (ROM line 1A6)
// Match: 111.01111000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  ALU SUB, tmpC
// -------------------------------------------------------------------------
case 0x7786:
{
    setupAlu<false, false>(Alu::Sub, TC);
    break;
}

// Word: 1A7 (ROM line 1A7)
// Match: 111.01111000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> NULL                  -W-  CALL IDIV2 (12) -> 7900 [Line 1A8]
// -------------------------------------------------------------------------
case 0x7787:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    (void)a;
    commitAluFlags();
    jumpFar(0x7900);
    break;
}

// Word: 230 (ROM line 234)
// Match: 111.10000000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpC                    F--  ALU ADD, tmpA
// -------------------------------------------------------------------------
case 0x7800:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    r[TC] = a;
    setupAlu<false, false>(Alu::Add, TA);
    break;
}

// Word: 231 (ROM line 235)
// Match: 111.10000000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> SP                    ---  --
// -------------------------------------------------------------------------
case 0x7801:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[SP] = a;
    break;
}

// Word: 232 (ROM line 236)
// Match: 111.10000000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> CS                      F--  --
// -------------------------------------------------------------------------
case 0x7802:
{
    if (!operandAccessReady()) { return; }
    latchOprFromRead();
    const uint16_t a = readOpr();
    writeSegment(CS, a, true);
    break;
}

// Word: 233 (ROM line 237)
// Match: 111.10000000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> PC                     --E  IC=FLUSH
// -------------------------------------------------------------------------
case 0x7803:
{
    if (!prefetchFlushReady(true)) { return; }
    const uint16_t a = r[TC];
    r[IP] = a;
    flushPrefetch(false, false, true);
    endRequested = true;
    break;
}

// Word: 1A8 (ROM line 1A8)
// Match: 111.10010000.0000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JC, 02
// -------------------------------------------------------------------------
case 0x7900:
{
    if ((r[FLAGS] & CF) != 0) {
        jumpLocal(2);
    }
    break;
}

// Word: 1A9 (ROM line 1A9)
// Match: 111.10010000.0001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// ZERO -> tmpBL                  ---  CALL INT (02) -> 7100 [Line 1E8]
// -------------------------------------------------------------------------
case 0x7901:
{
    const uint16_t a = 0;
    r[TB] = extendByte(a);
    jumpFar(0x7100);
    break;
}

// Word: 1AA (ROM line 1AA)
// Match: 111.10010000.0010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpB                  ---  ALU DIV, tmpC, R
// -------------------------------------------------------------------------
case 0x7902:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TB] = a;
    setupDiv<true, false>(TC);
    break;
}

// Word: 1AB (ROM line 1AB)
// Match: 111.10010000.0011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> NULL   SIGMA -> tmpB  ---  ALU DIV, tmpC
// -------------------------------------------------------------------------
case 0x7903:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    const uint16_t b = sigma;
    (void)a;
    r[TB] = b;
    setupDiv<false, false>(TC);
    break;
}

// Word: 1AC (ROM line 1AC)
// Match: 111.10010000.0100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpB -> tmpC                   ---  ALU PASS, tmpA
// -------------------------------------------------------------------------
case 0x7904:
{
    const uint16_t a = r[TB];
    r[TC] = a;
    setupAlu<false, false>(Alu::Pass, TA);
    break;
}

// Word: 1AD (ROM line 1AD)
// Match: 111.10010000.0101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// OPR -> tmpB     SIGMA -> NULL  -W-  ALU NEG, tmpA
// -------------------------------------------------------------------------
case 0x7905:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = readOpr();
    const uint16_t b = sigma;
    r[TB] = a;
    (void)b;
    commitAluFlags();
    setupAlu<false, true>(Alu::Neg, TA);
    break;
}

// Word: 1AE (ROM line 1AE)
// Match: 111.10010000.0110
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JL, 01
// -------------------------------------------------------------------------
case 0x7906:
{
    if (aluLess()) {
        jumpLocal(1);
    }
    break;
}

// Word: 1AF (ROM line 1AF)
// Match: 111.10010000.0111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JPOS/NZ4S, 09
// -------------------------------------------------------------------------
case 0x7907:
{
    if (nonnegativeResult()) {
        jumpLocal(9);
    }
    break;
}

// Word: 1B0 (ROM line 1B0)
// Match: 111.10010000.1000
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpA                  ---  --
// -------------------------------------------------------------------------
case 0x7908:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TA] = a;
    break;
}

// Word: 1B1 (ROM line 1B1)
// Match: 111.10010000.1001
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  ALU NEG, tmpC
// -------------------------------------------------------------------------
case 0x7909:
{
    setupAlu<false, false>(Alu::Neg, TC);
    break;
}

// Word: 1B2 (ROM line 1B2)
// Match: 111.10010000.1010
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
//                                ---  JUMP JNS, 0C
// -------------------------------------------------------------------------
case 0x790a:
{
    if ((r[TB] & (wordSize ? 0x8000 : 0x80)) == 0) {
        jumpLocal(12);
    }
    break;
}

// Word: 1B3 (ROM line 1B3)
// Match: 111.10010000.1011
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// SIGMA -> tmpC                  ---  --
// -------------------------------------------------------------------------
case 0x790b:
{
    const uint16_t sigma = evaluateAlu();
    const uint16_t a = sigma;
    r[TC] = a;
    break;
}

// Word: 1B4 (ROM line 1B4)
// Match: 111.10010000.1100
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpA -> A                      ---  JUMP JNW, 0F
// -------------------------------------------------------------------------
case 0x790c:
{
    const uint16_t a = r[TA];
    r[AX] = a;
    if (shortImmediate()) {
        jumpLocal(15);
    }
    break;
}

// Word: 1B5 (ROM line 1B5)
// Match: 111.10010000.1101
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> D                      --E  --
// -------------------------------------------------------------------------
case 0x790d:
{
    const uint16_t a = r[TC];
    r[DX] = a;
    endRequested = true;
    break;
}

// Word: 1B7 (ROM line 1B7)
// Match: 111.10010000.1111
// Opcodes: none (helper or hardware entry)
// -------------------------------------------------------------------------
// tmpC -> AH                     --E  --
// -------------------------------------------------------------------------
case 0x790f:
{
    const uint16_t a = r[TC];
    writeByteReg(4, a);
    endRequested = true;
    break;
}


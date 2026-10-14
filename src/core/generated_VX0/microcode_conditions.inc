// OPC predicates resolved from the condition decoder PLA.
bool opcodeCondition() const {
    const uint16_t flags = r[FLAGS];
    const unsigned condition = (flags & MF) != 0
        ? (opcode & 15) : 16 + ((opcode >> 3) & 7);

    switch (condition) {
    case 0: return ((flags & OF) == OF);
    case 1: return ((flags & OF) == 0);
    case 2: return ((flags & CF) == CF);
    case 3: return ((flags & CF) == 0);
    case 4: return ((flags & ZF) == ZF);
    case 5: return ((flags & ZF) == 0);
    case 6: return ((flags & CF) == CF) || ((flags & ZF) == ZF);
    case 7: return ((flags & (CF | ZF)) == 0);
    case 8: return ((flags & SF) == SF);
    case 9: return ((flags & SF) == 0);
    case 10: return ((flags & PF) == PF);
    case 11: return ((flags & PF) == 0);
    case 12: return ((flags & (SF | OF)) == SF) || ((flags & (SF | OF)) == OF);
    case 13: return ((flags & (SF | OF)) == 0) || ((flags & (SF | OF)) == (SF | OF));
    case 14: return ((flags & (SF | OF)) == SF) || ((flags & (SF | OF)) == OF) || ((flags & ZF) == ZF);
    case 15: return ((flags & (ZF | SF | OF)) == 0) || ((flags & (ZF | SF | OF)) == (SF | OF));
    case 16: return ((flags & ZF) == 0);
    case 17: return ((flags & ZF) == ZF);
    case 18: return ((flags & CF) == 0);
    case 19: return ((flags & CF) == CF);
    case 20: return ((flags & PF) == 0);
    case 21: return ((flags & PF) == PF);
    case 22: return ((flags & SF) == 0);
    case 23: return ((flags & SF) == SF);
    default: return false;
    }
}


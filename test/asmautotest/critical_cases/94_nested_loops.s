.text
.globl loop1
.type loop1, @function
# Function: loop1
loop1:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -64
loop1_label_entry:
# Store to memory
    st.w $a0, $sp, 44
# Store to memory
    st.w $a1, $sp, 40
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 36
    # Unconditional branch
    b loop1_1
loop1_label_ret:
    addi.d $sp, $sp, 48
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
loop1_1:
    ld.w $a0, $sp, 36
    ld.w $a1, $sp, 44
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, loop1_4
    b loop1_3
loop1_2:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 32
    # Unconditional branch
    b loop1_5
loop1_3:
    # Unconditional branch
    b loop1_label_ret
loop1_4:
    ld.w $a0, $sp, 36
    ld.w $a1, $sp, 40
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, loop1_2
    b loop1_3
loop1_5:
    ld.w $a0, $sp, 32
    li.w $t2, 2
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop1_6
    b loop1_7
loop1_6:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 28
    # Unconditional branch
    b loop1_8
loop1_7:
    ld.w $a0, $sp, 36
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 36
    # Unconditional branch
    b loop1_1
loop1_8:
    ld.w $a0, $sp, 28
    li.w $t2, 3
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop1_9
    b loop1_10
loop1_9:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 24
    # Unconditional branch
    b loop1_11
loop1_10:
    ld.w $a0, $sp, 32
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 32
    # Unconditional branch
    b loop1_5
loop1_11:
    ld.w $a0, $sp, 24
    li.w $t2, 4
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop1_12
    b loop1_13
loop1_12:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 20
    # Unconditional branch
    b loop1_14
loop1_13:
    ld.w $a0, $sp, 28
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 28
    # Unconditional branch
    b loop1_8
loop1_14:
    ld.w $a0, $sp, 20
    li.w $t2, 5
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop1_15
    b loop1_16
loop1_15:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 16
    # Unconditional branch
    b loop1_17
loop1_16:
    ld.w $a0, $sp, 24
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 24
    # Unconditional branch
    b loop1_11
loop1_17:
    ld.w $a0, $sp, 16
    li.w $t2, 6
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop1_18
    b loop1_19
loop1_18:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 12
    # Unconditional branch
    b loop1_20
loop1_19:
    ld.w $a0, $sp, 20
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 20
    # Unconditional branch
    b loop1_14
loop1_20:
    ld.w $a0, $sp, 12
    li.w $t2, 2
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop1_21
    b loop1_22
loop1_21:
    ld.w $a0, $sp, 36
    ld.w $a1, $sp, 32
    ld.w $a2, $sp, 28
    ld.w $a3, $sp, 24
    ld.w $a4, $sp, 20
    ld.w $a5, $sp, 16
    ld.w $a6, $sp, 12
    la.global $t1, arr1
    or $a7, $t1, $zero
    # Element size: 57600 bytes
    # offset: 0
    # Element size: 5760 bytes
    # indexReg: $a0
    li.d $t3, 5760
    mul.d $t3, $a0, $t3
    add.d $a7, $a7, $t3
    # Element size: 2880 bytes
    # indexReg: $a1
    li.d $t3, 2880
    mul.d $t3, $a1, $t3
    add.d $a7, $a7, $t3
    # Element size: 960 bytes
    # indexReg: $a2
    li.d $t3, 960
    mul.d $t3, $a2, $t3
    add.d $a7, $a7, $t3
    # Element size: 240 bytes
    # indexReg: $a3
    li.d $t3, 240
    mul.d $t3, $a3, $t3
    add.d $a7, $a7, $t3
    # Element size: 48 bytes
    # indexReg: $a4
    li.d $t3, 48
    mul.d $t3, $a4, $t3
    add.d $a7, $a7, $t3
    # Element size: 8 bytes
    # indexReg: $a5
    slli.d $t3, $a5, 3
    add.d $a7, $a7, $t3
    # Element size: 4 bytes
    # indexReg: $a6
    slli.d $t3, $a6, 2
    add.d $a7, $a7, $t3
    ld.w $a0, $sp, 36
    ld.w $a1, $sp, 32
    add.w $a2, $a0, $a1
    ld.w $a0, $sp, 28
    add.w $a1, $a2, $a0
    ld.w $a0, $sp, 24
    add.w $a2, $a1, $a0
    ld.w $a0, $sp, 20
    add.w $a1, $a2, $a0
    ld.w $a0, $sp, 16
    add.w $a2, $a1, $a0
    ld.w $a0, $sp, 12
    add.w $a1, $a2, $a0
    ld.w $a0, $sp, 44
    add.w $a2, $a1, $a0
    ld.w $a0, $sp, 40
    add.w $a1, $a2, $a0
# Store to memory
    st.w $a1, $a7, 0
    ld.w $a0, $sp, 12
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 12
    # Unconditional branch
    b loop1_20
loop1_22:
    ld.w $a0, $sp, 16
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 16
    # Unconditional branch
    b loop1_17
.globl loop2
.type loop2, @function
# Function: loop2
loop2:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -48
loop2_label_entry:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 28
    # Unconditional branch
    b loop2_23
loop2_label_ret:
    addi.d $sp, $sp, 32
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
loop2_23:
    ld.w $a0, $sp, 28
    li.w $t2, 10
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_24
    b loop2_25
loop2_24:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 24
    # Unconditional branch
    b loop2_26
loop2_25:
    # Unconditional branch
    b loop2_label_ret
loop2_26:
    ld.w $a0, $sp, 24
    li.w $t2, 2
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_27
    b loop2_28
loop2_27:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 20
    # Unconditional branch
    b loop2_29
loop2_28:
    ld.w $a0, $sp, 28
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 28
    # Unconditional branch
    b loop2_23
loop2_29:
    ld.w $a0, $sp, 20
    li.w $t2, 3
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_30
    b loop2_31
loop2_30:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 16
    # Unconditional branch
    b loop2_32
loop2_31:
    ld.w $a0, $sp, 24
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 24
    # Unconditional branch
    b loop2_26
loop2_32:
    ld.w $a0, $sp, 16
    li.w $t2, 2
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_33
    b loop2_34
loop2_33:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 12
    # Unconditional branch
    b loop2_35
loop2_34:
    ld.w $a0, $sp, 20
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 20
    # Unconditional branch
    b loop2_29
loop2_35:
    ld.w $a0, $sp, 12
    li.w $t2, 4
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_36
    b loop2_37
loop2_36:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 8
    # Unconditional branch
    b loop2_38
loop2_37:
    ld.w $a0, $sp, 16
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 16
    # Unconditional branch
    b loop2_32
loop2_38:
    ld.w $a0, $sp, 8
    li.w $t2, 8
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_39
    b loop2_40
loop2_39:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 4
    # Unconditional branch
    b loop2_41
loop2_40:
    ld.w $a0, $sp, 12
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 12
    # Unconditional branch
    b loop2_35
loop2_41:
    ld.w $a0, $sp, 4
    li.w $t2, 7
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop2_42
    b loop2_43
loop2_42:
    ld.w $a0, $sp, 28
    ld.w $a1, $sp, 24
    ld.w $a2, $sp, 20
    ld.w $a3, $sp, 16
    ld.w $a4, $sp, 12
    ld.w $a5, $sp, 8
    ld.w $a6, $sp, 4
    la.global $t1, arr2
    or $a7, $t1, $zero
    # Element size: 107520 bytes
    # offset: 0
    # Element size: 10752 bytes
    # indexReg: $a0
    li.d $t3, 10752
    mul.d $t3, $a0, $t3
    add.d $a7, $a7, $t3
    # Element size: 5376 bytes
    # indexReg: $a1
    li.d $t3, 5376
    mul.d $t3, $a1, $t3
    add.d $a7, $a7, $t3
    # Element size: 1792 bytes
    # indexReg: $a2
    li.d $t3, 1792
    mul.d $t3, $a2, $t3
    add.d $a7, $a7, $t3
    # Element size: 896 bytes
    # indexReg: $a3
    li.d $t3, 896
    mul.d $t3, $a3, $t3
    add.d $a7, $a7, $t3
    # Element size: 224 bytes
    # indexReg: $a4
    li.d $t3, 224
    mul.d $t3, $a4, $t3
    add.d $a7, $a7, $t3
    # Element size: 28 bytes
    # indexReg: $a5
    li.d $t3, 28
    mul.d $t3, $a5, $t3
    add.d $a7, $a7, $t3
    # Element size: 4 bytes
    # indexReg: $a6
    slli.d $t3, $a6, 2
    add.d $a7, $a7, $t3
    ld.w $a0, $sp, 28
    ld.w $a1, $sp, 24
    add.w $a2, $a0, $a1
    ld.w $a0, $sp, 16
    add.w $a1, $a2, $a0
    ld.w $a0, $sp, 4
    add.w $a2, $a1, $a0
# Store to memory
    st.w $a2, $a7, 0
    ld.w $a0, $sp, 4
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 4
    # Unconditional branch
    b loop2_41
loop2_43:
    ld.w $a0, $sp, 8
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 8
    # Unconditional branch
    b loop2_38
.globl loop3
.type loop3, @function
# Function: loop3
loop3:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -288
loop3_label_entry:
# Store to memory
    st.w $a0, $sp, 84
# Store to memory
    st.w $a1, $sp, 80
# Store to memory
    st.w $a2, $sp, 76
# Store to memory
    st.w $a3, $sp, 72
# Store to memory
    st.w $a4, $sp, 68
# Store to memory
    st.w $a5, $sp, 64
# Store to memory
    st.w $a6, $sp, 60
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 24
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 52
    # Call to function: putint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 1
    bl putint
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Call to function: putch
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 10
    bl putch
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Unconditional branch
    b loop3_44
loop3_label_ret:
    ld.w $a0, $sp, 56
    or $a0, $a0, $zero
    addi.d $sp, $sp, 272
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
loop3_44:
    ld.w $a0, $sp, 52
    li.w $t2, 10
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_45
    b loop3_46
loop3_45:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 48
    # Unconditional branch
    b loop3_47
loop3_46:
    ld.w $a0, $sp, 24
# Store to memory
    st.w $a0, $sp, 56
    # Unconditional branch
    b loop3_label_ret
loop3_47:
    ld.w $a0, $sp, 48
    li.w $t2, 100
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_48
    b loop3_49
loop3_48:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 44
    # Unconditional branch
    b loop3_50
loop3_49:
    ld.w $a0, $sp, 52
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 52
    ld.w $a0, $sp, 52
    ld.w $a1, $sp, 84
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_77
    b loop3_78
loop3_50:
    ld.w $a0, $sp, 44
    li.w $t2, 1000
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_51
    b loop3_52
loop3_51:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 40
    # Unconditional branch
    b loop3_53
loop3_52:
    ld.w $a0, $sp, 48
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 48
    ld.w $a0, $sp, 48
    ld.w $a1, $sp, 80
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_75
    b loop3_76
loop3_53:
    ld.w $a0, $sp, 40
    li.w $t2, 10000
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_54
    b loop3_55
loop3_54:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 36
    # Unconditional branch
    b loop3_56
loop3_55:
    ld.w $a0, $sp, 44
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 44
    ld.w $a0, $sp, 44
    ld.w $a1, $sp, 76
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_73
    b loop3_74
loop3_56:
    ld.w $a0, $sp, 36
    li.w $t2, 100000
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_57
    b loop3_58
loop3_57:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 32
    # Unconditional branch
    b loop3_59
loop3_58:
    ld.w $a0, $sp, 40
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 40
    ld.w $a0, $sp, 40
    ld.w $a1, $sp, 72
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_71
    b loop3_72
loop3_59:
    ld.w $a0, $sp, 32
    li.w $t2, 1000000
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_60
    b loop3_61
loop3_60:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 28
    # Unconditional branch
    b loop3_62
loop3_61:
    ld.w $a0, $sp, 36
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 36
    ld.w $a0, $sp, 36
    ld.w $a1, $sp, 68
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_69
    b loop3_70
loop3_62:
    ld.w $a0, $sp, 28
    li.w $t2, 10000000
    # Integer comparison: lt
    slt $a1, $a0, $t2
    # Conditional branch
    bnez $a1, loop3_63
    b loop3_64
loop3_63:
    ld.w $a0, $sp, 24
    li.w $t1, 817
    mod.w $a1, $a0, $t1
    ld.w $a0, $sp, 52
    ld.w $a2, $sp, 48
    ld.w $a3, $sp, 44
    ld.w $a4, $sp, 40
    ld.w $a5, $sp, 36
    ld.w $a6, $sp, 32
    ld.w $a7, $sp, 28
    # Result not mapped to register, using temporary $t0
    la.global $t1, arr1
    or $t0, $t1, $zero
    # Element size: 57600 bytes
    # offset: 0
    # Element size: 5760 bytes
    # indexReg: $a0
    li.d $t3, 5760
    mul.d $t3, $a0, $t3
    add.d $t0, $t0, $t3
    # Element size: 2880 bytes
    # indexReg: $a2
    li.d $t3, 2880
    mul.d $t3, $a2, $t3
    add.d $t0, $t0, $t3
    # Element size: 960 bytes
    # indexReg: $a3
    li.d $t3, 960
    mul.d $t3, $a3, $t3
    add.d $t0, $t0, $t3
    # Element size: 240 bytes
    # indexReg: $a4
    li.d $t3, 240
    mul.d $t3, $a4, $t3
    add.d $t0, $t0, $t3
    # Element size: 48 bytes
    # indexReg: $a5
    li.d $t3, 48
    mul.d $t3, $a5, $t3
    add.d $t0, $t0, $t3
    # Element size: 8 bytes
    # indexReg: $a6
    slli.d $t3, $a6, 3
    add.d $t0, $t0, $t3
    # Element size: 4 bytes
    # indexReg: $a7
    slli.d $t3, $a7, 2
    add.d $t0, $t0, $t3
    st.d $t0, $sp, 16
    ld.d $t0, $sp, 16 #读取arr1地址，改为ld.d
    
    ld.w $a0, $t0, 0
    add.w $a2, $a1, $a0
    ld.w $a0, $sp, 52
    ld.w $a1, $sp, 48
    ld.w $a3, $sp, 44
    ld.w $a4, $sp, 40
    ld.w $a5, $sp, 36
    ld.w $a6, $sp, 32
    ld.w $a7, $sp, 28
    # Result not mapped to register, using temporary $t0
    la.global $t1, arr2
    or $t0, $t1, $zero
    # Element size: 107520 bytes
    # offset: 0
    # Element size: 10752 bytes
    # indexReg: $a0
    li.d $t3, 10752
    mul.d $t3, $a0, $t3
    add.d $t0, $t0, $t3
    # Element size: 5376 bytes
    # indexReg: $a1
    li.d $t3, 5376
    mul.d $t3, $a1, $t3
    add.d $t0, $t0, $t3
    # Element size: 1792 bytes
    # indexReg: $a3
    li.d $t3, 1792
    mul.d $t3, $a3, $t3
    add.d $t0, $t0, $t3
    # Element size: 896 bytes
    # indexReg: $a4
    li.d $t3, 896
    mul.d $t3, $a4, $t3
    add.d $t0, $t0, $t3
    # Element size: 224 bytes
    # indexReg: $a5
    li.d $t3, 224
    mul.d $t3, $a5, $t3
    add.d $t0, $t0, $t3
    # Element size: 28 bytes
    # indexReg: $a6
    li.d $t3, 28
    mul.d $t3, $a6, $t3
    add.d $t0, $t0, $t3
    # Element size: 4 bytes
    # indexReg: $a7
    slli.d $t3, $a7, 2
    add.d $t0, $t0, $t3
    st.d $t0, $sp, 8
    ld.d $t0, $sp, 8 #读取arr2地址，改为ld.d
    ld.w $a0, $t0, 0
    add.w $a1, $a2, $a0
# Store to memory
    st.w $a1, $sp, 24
    ld.w $a0, $sp, 28
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 28
    ld.w $a0, $sp, 28
    ld.w $a1, $sp, 60
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_65
    b loop3_66
loop3_64:
    ld.w $a0, $sp, 32
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 32
    ld.w $a0, $sp, 32
    ld.w $a1, $sp, 64
    # Integer comparison: ge
    slt $a2, $a0, $a1
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, loop3_67
    b loop3_68
loop3_65:
    # Unconditional branch
    b loop3_64
loop3_66:
    # Unconditional branch
    b loop3_62
loop3_67:
    # Unconditional branch
    b loop3_61
loop3_68:
    # Unconditional branch
    b loop3_59
loop3_69:
    # Unconditional branch
    b loop3_58
loop3_70:
    # Unconditional branch
    b loop3_56
loop3_71:
    # Unconditional branch
    b loop3_55
loop3_72:
    # Unconditional branch
    b loop3_53
loop3_73:
    # Unconditional branch
    b loop3_52
loop3_74:
    # Unconditional branch
    b loop3_50
loop3_75:
    # Unconditional branch
    b loop3_49
loop3_76:
    # Unconditional branch
    b loop3_47
loop3_77:
    # Unconditional branch
    b loop3_46
loop3_78:
    # Unconditional branch
    b loop3_44
.globl main
.type main, @function
# Function: main
main:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -240
main_label_entry:
    # Call to function: putint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 3
    bl putint
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Call to function: putch
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 10
    bl putch
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Call to function: putint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 3
    bl putint
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Call to function: putch
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 10
    bl putch
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 32
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 28
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 24
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 20
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 16
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 12
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 8
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 4
    # Call to function: getint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    bl getint
    # Handle return value
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
# Store to memory
    st.w $a0, $sp, 0
    # Call to function: putint
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 2
    bl putint
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    # Call to function: putch
    # Save caller-saved registers (if needed)
    addi.d  $sp, $sp, 0
    # Load argument $a0
    li.w $a0, 10
    bl putch
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.w $a0, $sp, 24
    ld.w $a1, $sp, 20
    ld.w $a2, $sp, 16
    ld.w $a3, $sp, 12
    ld.w $a4, $sp, 8
    ld.w $a5, $sp, 4
    ld.w $a6, $sp, 0
    # Call to function: loop3
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 216
    st.d $a1, $sp, 208
    st.d $a2, $sp, 200
    st.d $a3, $sp, 192
    st.d $a4, $sp, 184
    st.d $a5, $sp, 176
    st.d $a6, $sp, 168
    addi.d  $sp, $sp, 0
    # Load argument $a0
    ld.d $a0, $sp, 216
    # Load argument $a1
    ld.d $a1, $sp, 208
    # Load argument $a2
    ld.d $a2, $sp, 200
    # Load argument $a3
    ld.d $a3, $sp, 192
    # Load argument $a4
    ld.d $a4, $sp, 184
    # Load argument $a5
    ld.d $a5, $sp, 176
    # Load argument $a6
    ld.d $a6, $sp, 168
    bl loop3
    # Handle return value
    or $a7, $a0, $zero
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 216
    ld.d $a1, $sp, 208
    ld.d $a2, $sp, 200
    ld.d $a3, $sp, 192
    ld.d $a4, $sp, 184
    ld.d $a5, $sp, 176
    ld.d $a6, $sp, 168
# Store to memory
    st.w $a7, $sp, 36
    # Unconditional branch
    b main_label_ret
main_label_ret:
    ld.w $a0, $sp, 36
    or $a0, $a0, $zero
    addi.d $sp, $sp, 224
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
.data
.globl arr1
.p2align 2
arr1:
.zero 57600
.globl arr2
.p2align 2
arr2:
.zero 107520
.bss

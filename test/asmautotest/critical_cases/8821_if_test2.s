.text
.globl main
.type main, @function
# Function: main
main:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $fp, $sp, -16
    addi.d $sp, $sp, -16
    # Function entry basic block
    addi.d $sp, $sp, -16
label_label_entry:
# Store to memory
    li.w $t1, 5
    st.w $t1, $fp, 8
# Store to memory
    li.w $t1, 10
    st.w $t1, $fp, 12
    ld.w $a3, $fp, 8
    li.w $t2, 6
    # Integer comparison: eq
    xor $t3, $a3, $t2
    sltui $a4, $t3, 1
    # Conditional branch
    bnez $a4, label_1
    b label_4
label_label_ret:
    ld.w $a3, $fp, 4
    or $a0, $a3, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
label_1:
    ld.w $a3, $fp, 8
# Store to memory
    st.w $a3, $fp, 4
    # Unconditional branch
    b label_label_ret
label_2:
    ld.w $a3, $fp, 12
    li.w $t2, 10
    # Integer comparison: eq
    xor $t3, $a3, $t2
    sltui $a4, $t3, 1
    # Conditional branch
    bnez $a4, label_8
    b label_6
label_3:
    ld.w $a3, $fp, 8
# Store to memory
    st.w $a3, $fp, 4
    # Unconditional branch
    b label_label_ret
label_4:
    ld.w $a0, $fp, 12
    li.w $t2, 11
    # Integer comparison: eq
    xor $t3, $a0, $t2
    sltui $a3, $t3, 1
    # Conditional branch
    bnez $a3, label_1
    b label_2
label_5:
# Store to memory
    li.w $t1, 25
    st.w $t1, $fp, 8
    # Unconditional branch
    b label_7
label_6:
    ld.w $a0, $fp, 12
    li.w $t2, 10
    # Integer comparison: eq
    xor $t3, $a0, $t2
    sltui $a2, $t3, 1
    # Conditional branch
    bnez $a2, label_12
    b label_10
label_7:
    # Unconditional branch
    b label_3
label_8:
    ld.w $a0, $fp, 8
    li.w $t2, 1
    # Integer comparison: eq
    xor $t3, $a0, $t2
    sltui $a2, $t3, 1
    # Conditional branch
    bnez $a2, label_5
    b label_6
label_9:
    ld.w $a0, $fp, 8
    addi.w $a2, $a0, 15
# Store to memory
    st.w $a2, $fp, 8
    # Unconditional branch
    b label_11
label_10:
    ld.w $a0, $fp, 8
    li.w $t0, 0
    sub.w $a2, $t0, $a0
# Store to memory
    st.w $a2, $fp, 8
    # Unconditional branch
    b label_11
label_11:
    # Unconditional branch
    b label_7
label_12:
    ld.w $a0, $fp, 8
    li.w $a1, -5
    # Integer comparison: eq
    xor $t3, $a0, $a1
    sltui $a2, $t3, 1
    # Conditional branch
    bnez $a2, label_9
    b label_10
.data
.bss

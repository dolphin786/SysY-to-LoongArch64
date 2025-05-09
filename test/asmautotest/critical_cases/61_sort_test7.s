.text
.globl merge_sort
.type merge_sort, @function
# Function: merge_sort
merge_sort:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -272
merge_sort_label_entry:
# Store to memory
    st.w $a0, $sp, 28
# Store to memory
    st.w $a1, $sp, 24
    ld.w $a0, $sp, 28
    addi.w $a1, $a0, 1
    ld.w $a0, $sp, 24
    # Integer comparison: ge
    slt $a2, $a1, $a0
    xori $a2, $a2, 1
    # Conditional branch
    bnez $a2, merge_sort_1
    b merge_sort_2
merge_sort_label_ret:
    addi.d $sp, $sp, 256
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
merge_sort_1:
    # Unconditional branch
    b merge_sort_label_ret
merge_sort_2:
    ld.w $a0, $sp, 28
    ld.w $a1, $sp, 24
    add.w $a2, $a0, $a1
    li.w $t1, 2
    div.w $a0, $a2, $t1
# Store to memory
    st.w $a0, $sp, 20
    ld.w $a0, $sp, 28
    ld.w $a1, $sp, 20
    # Call to function: merge_sort
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 248
    st.d $a1, $sp, 240
    addi.d  $sp, $sp, 0
    bl merge_sort
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 248
    ld.d $a1, $sp, 240
    ld.w $a0, $sp, 20
    ld.w $a1, $sp, 24
    # Call to function: merge_sort
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 248
    st.d $a1, $sp, 240
    addi.d  $sp, $sp, 0
    bl merge_sort
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 248
    ld.d $a1, $sp, 240
    ld.w $a0, $sp, 28
# Store to memory
    st.w $a0, $sp, 16
    ld.w $a0, $sp, 20
# Store to memory
    st.w $a0, $sp, 12
    ld.w $a0, $sp, 28
# Store to memory
    st.w $a0, $sp, 8
    # Unconditional branch
    b merge_sort_3
merge_sort_3:
    ld.w $a0, $sp, 16
    ld.w $a1, $sp, 20
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, merge_sort_6
    b merge_sort_5
merge_sort_4:
    ld.w $a0, $sp, 16
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $a1, 0
    ld.w $a1, $sp, 12
    la.global $t1, buf
    or $a2, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a1, 2
    add.d $a2, $a2, $t3
    ld.w $a1, $a2, 0
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, merge_sort_7
    b merge_sort_8
merge_sort_5:
    # Unconditional branch
    b merge_sort_10
merge_sort_6:
    ld.w $a0, $sp, 12
    ld.w $a1, $sp, 24
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, merge_sort_4
    b merge_sort_5
merge_sort_7:
    ld.w $a0, $sp, 8
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    addi.d $a1, $a1, 4
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $sp, 16
    la.global $t1, buf
    or $a2, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
# Store to memory
    st.w $a0, $a1, 0
    ld.w $a0, $sp, 16
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 16
    # Unconditional branch
    b merge_sort_9
merge_sort_8:
    ld.w $a0, $sp, 8
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    addi.d $a1, $a1, 4
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $sp, 12
    la.global $t1, buf
    or $a2, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
# Store to memory
    st.w $a0, $a1, 0
    ld.w $a0, $sp, 12
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 12
    # Unconditional branch
    b merge_sort_9
merge_sort_9:
    ld.w $a0, $sp, 8
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 8
    # Unconditional branch
    b merge_sort_3
merge_sort_10:
    ld.w $a0, $sp, 16
    ld.w $a1, $sp, 20
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, merge_sort_11
    b merge_sort_12
merge_sort_11:
    ld.w $a0, $sp, 8
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    addi.d $a1, $a1, 4
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $sp, 16
    la.global $t1, buf
    or $a2, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
# Store to memory
    st.w $a0, $a1, 0
    ld.w $a0, $sp, 16
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 16
    ld.w $a0, $sp, 8
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 8
    # Unconditional branch
    b merge_sort_10
merge_sort_12:
    # Unconditional branch
    b merge_sort_13
merge_sort_13:
    ld.w $a0, $sp, 12
    ld.w $a1, $sp, 24
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, merge_sort_14
    b merge_sort_15
merge_sort_14:
    ld.w $a0, $sp, 8
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    addi.d $a1, $a1, 4
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $sp, 12
    la.global $t1, buf
    or $a2, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
# Store to memory
    st.w $a0, $a1, 0
    ld.w $a0, $sp, 12
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 12
    ld.w $a0, $sp, 8
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 8
    # Unconditional branch
    b merge_sort_13
merge_sort_15:
    # Unconditional branch
    b merge_sort_16
merge_sort_16:
    ld.w $a0, $sp, 28
    ld.w $a1, $sp, 24
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, merge_sort_17
    b merge_sort_18
merge_sort_17:
    ld.w $a0, $sp, 28
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $sp, 28
    la.global $t1, buf
    or $a2, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    addi.d $a2, $a2, 4
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
# Store to memory
    st.w $a0, $a1, 0
    ld.w $a0, $sp, 28
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 28
    # Unconditional branch
    b merge_sort_16
merge_sort_18:
    # Unconditional branch
    b merge_sort_label_ret
.globl main
.type main, @function
# Function: main
main:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -256
main_label_entry:
    la.global $t1, buf
    or $a0, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    or $a1, $a0, $zero
    # Element size: 4 bytes
    # Call to function: getarray
    # Save caller-saved registers (if needed)
    st.d $a1, $sp, 224
    addi.d  $sp, $sp, 0
    or $a0, $a1, $zero
    bl getarray
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a1, $sp, 224
# Store to memory
    st.w $a0, $sp, 8
    ld.w $a0, $sp, 8
    # Call to function: merge_sort
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 232
    addi.d  $sp, $sp, 0
    li.w $a0, 0
    or $a1, $a0, $zero
    bl merge_sort
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 232
    ld.w $a0, $sp, 8
    la.global $t1, buf
    or $a1, $t1, $zero
    # Element size: 400 bytes
    # Element size: 4 bytes
    or $a2, $a1, $zero
    # Element size: 4 bytes
    # Call to function: putarray
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 232
    st.d $a2, $sp, 216
    addi.d  $sp, $sp, 0
    or $a1, $a2, $zero
    bl putarray
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 232
    ld.d $a2, $sp, 216
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 12
    # Unconditional branch
    b main_label_ret
main_label_ret:
    ld.w $a0, $sp, 12
    or $a0, $a0, $zero
    addi.d $sp, $sp, 240
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
.data
.globl buf
.p2align 2
buf:
.zero 80000
.bss

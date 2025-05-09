.text
.globl bubblesort
.type bubblesort, @function
# Function: bubblesort
bubblesort:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $fp, $sp, -16
    addi.d $sp, $sp, -480
bubblesort_label_entry:
# Store to memory
    st.w $a0, $fp, -4
# Store to memory
    li.w $t1, 0
    st.w $t1, $fp, -12
    # Unconditional branch
    b bubblesort_1
bubblesort_label_ret:
    ld.w $a0, $fp, -8
    or $a0, $a0, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
bubblesort_1:
    ld.w $a0, $fp, -12
    la.global $t0, n
    ld.w $a1, $t0, 0
    addi.w $a2, $a1, -1
    # Integer comparison: lt
    slt $a1, $a0, $a2
    # Conditional branch
    bnez $a1, bubblesort_2
    b bubblesort_3
bubblesort_2:
# Store to memory
    li.w $t1, 0
    st.w $t1, $fp, -16
    # Unconditional branch
    b bubblesort_4
bubblesort_3:
# Store to memory
    li.w $t1, 0
    st.w $t1, $fp, -8
    # Unconditional branch
    b bubblesort_label_ret
bubblesort_4:
    ld.w $a0, $fp, -16
    la.global $t0, n
    ld.w $a1, $t0, 0
    ld.w $a2, $fp, -12
    sub.w $a3, $a1, $a2
    addi.w $a1, $a3, -1
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, bubblesort_5
    b bubblesort_6
bubblesort_5:
    ld.w $a0, $fp, -16
    ld.w $a1, $fp, -4
    or $a2, $a1, $zero
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
    ld.w $a1, $fp, -16
    addi.w $a2, $a1, 1
    ld.w $a1, $fp, -4
    or $a3, $a1, $zero
    # Element size: 4 bytes
    slli.d $t3, $a2, 2
    add.d $a3, $a3, $t3
    ld.w $a1, $a3, 0
    # Integer comparison: gt
    slt $a2, $a1, $a0
    # Conditional branch
    bnez $a2, bubblesort_7
    b bubblesort_8
bubblesort_6:
    ld.w $a0, $fp, -12
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $fp, -12
    # Unconditional branch
    b bubblesort_1
bubblesort_7:
    ld.w $a0, $fp, -16
    addi.w $a1, $a0, 1
    ld.w $a0, $fp, -4
    or $a2, $a0, $zero
    # Element size: 4 bytes
    slli.d $t3, $a1, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $a2, 0
# Store to memory
    st.w $a0, $fp, -20
    ld.w $a0, $fp, -16
    addi.w $a1, $a0, 1
    ld.w $a0, $fp, -4
    or $a2, $a0, $zero
    # Element size: 4 bytes
    slli.d $t3, $a1, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $fp, -16
    ld.w $a1, $fp, -4
    or $a3, $a1, $zero
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a3, $a3, $t3
    ld.w $a0, $a3, 0
# Store to memory
    st.w $a0, $a2, 0
    ld.w $a0, $fp, -16
    ld.w $a1, $fp, -4
    or $a2, $a1, $zero
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a2, $a2, $t3
    ld.w $a0, $fp, -20
# Store to memory
    st.w $a0, $a2, 0
    # Unconditional branch
    b bubblesort_8
bubblesort_8:
    ld.w $a0, $fp, -16
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $fp, -16
    # Unconditional branch
    b bubblesort_4
.globl main
.type main, @function
# Function: main
main:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $fp, $sp, -16
    addi.d $sp, $sp, -304
main_label_entry:
# Store to variable: n
    # Store to global variable
    la.global $t0, n
    li.w $t1, 10
    st.w $t1, $t0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
# Store to memory
    li.w $t1, 4
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 4
# Store to memory
    li.w $t1, 3
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 8
# Store to memory
    li.w $t1, 9
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 12
# Store to memory
    li.w $t1, 2
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 16
# Store to memory
    li.w $t1, 0
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 20
# Store to memory
    li.w $t1, 1
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 24
# Store to memory
    li.w $t1, 6
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 28
# Store to memory
    li.w $t1, 5
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 32
# Store to memory
    li.w $t1, 7
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 36
# Store to memory
    li.w $t1, 8
    st.w $t1, $a0, 0
    addi.d $t1, $fp, -268
    or $a0, $t1, $zero
    # Element size: 4 bytes
    # Call to function: bubblesort
    # Save caller-saved registers (if needed)
    st.d $a0, $fp, -8
    addi.d  $sp, $sp, 0
    bl bubblesort
    or $a1, $a0, $zero
    # Restore caller-saved registers (if needed)
    ld.d $a0, $fp, -8
# Store to memory
    st.w $a1, $fp, -272
    # Unconditional branch
    b main_9
main_label_ret:
    ld.w $a0, $fp, -228
    or $a0, $a0, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
main_9:
    ld.w $a0, $fp, -272
    la.global $t0, n
    ld.w $a1, $t0, 0
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, main_10
    b main_11
main_10:
    ld.w $a0, $fp, -272
    addi.d $t1, $fp, -268
    or $a1, $t1, $zero
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $a1, 0
# Store to memory
    st.w $a0, $fp, -276
    ld.w $a0, $fp, -276
    # Call to function: putint
    # Save caller-saved registers (if needed)
    st.d $a0, $fp, -8
    addi.d  $sp, $sp, 0
    bl putint
    # Restore caller-saved registers (if needed)
    ld.d $a0, $fp, -8
# Store to memory
    li.w $t1, 10
    st.w $t1, $fp, -276
    ld.w $a0, $fp, -276
    # Call to function: putch
    # Save caller-saved registers (if needed)
    st.d $a0, $fp, -8
    addi.d  $sp, $sp, 0
    bl putch
    # Restore caller-saved registers (if needed)
    ld.d $a0, $fp, -8
    ld.w $a0, $fp, -272
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $fp, -272
    # Unconditional branch
    b main_9
main_11:
# Store to memory
    li.w $t1, 0
    st.w $t1, $fp, -228
    # Unconditional branch
    b main_label_ret
.data
.globl n
.p2align 2
n:
.word 0
.bss

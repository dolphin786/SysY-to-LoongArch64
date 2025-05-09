.text
.globl bubblesort
.type bubblesort, @function
# Function: bubblesort
bubblesort:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -32
bubblesort_label_entry:
# Store to memory
    st.w $a0, $sp, 12
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 4
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 0
    ld.w $a0, $sp, 0
# Store to memory
    st.w $a0, $sp, 8
    # Unconditional branch
    b bubblesort_label_ret
bubblesort_label_ret:
    ld.w $a0, $sp, 8
    or $a0, $a0, $zero
    addi.d $sp, $sp, 16
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
.globl main
.type main, @function
# Function: main
main:
    st.d $ra, $sp, -8
    st.d $fp, $sp, -16
    addi.d $sp, $sp, -304
main_label_entry:
# Store to variable: n
    # Store to global variable
    la.global $t0, n
    li.w $t1, 10
    st.w $t1, $t0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
# Store to memory
    li.w $t1, 4
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 4
# Store to memory
    li.w $t1, 3
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 8
# Store to memory
    li.w $t1, 9
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 12
# Store to memory
    li.w $t1, 2
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 16
# Store to memory
    li.w $t1, 0
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 20
# Store to memory
    li.w $t1, 1
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 24
# Store to memory
    li.w $t1, 6
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 28
# Store to memory
    li.w $t1, 5
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 32
# Store to memory
    li.w $t1, 7
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    addi.d $a0, $a0, 36
# Store to memory
    li.w $t1, 8
    st.w $t1, $a0, 0
    addi.d $t1, $sp, 20
    or $a0, $t1, $zero
    # Element size: 4 bytes
    # Call to function: bubblesort
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 280
    addi.d  $sp, $sp, 0
    bl bubblesort
    or $a1, $a0, $zero
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 280
# Store to memory
    st.w $a1, $sp, 16
    # Unconditional branch
    b main_1
main_label_ret:
    ld.w $a0, $sp, 60
    or $a0, $a0, $zero
    addi.d $sp, $sp, 288
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
main_1:
    ld.w $a0, $sp, 16
    la.global $t0, n
    ld.w $a1, $t0, 0
    # Integer comparison: lt
    slt $a2, $a0, $a1
    # Conditional branch
    bnez $a2, main_2
    b main_3
main_2:
    ld.w $a0, $sp, 16
    addi.d $t1, $sp, 20
    or $a1, $t1, $zero
    # Element size: 4 bytes
    slli.d $t3, $a0, 2
    add.d $a1, $a1, $t3
    ld.w $a0, $a1, 0
# Store to memory
    st.w $a0, $sp, 12
    ld.w $a0, $sp, 12
    # Call to function: putint
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 280
    addi.d  $sp, $sp, 0
    bl putint
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 280
# Store to memory
    li.w $t1, 10
    st.w $t1, $sp, 12
    ld.w $a0, $sp, 12
    # Call to function: putch
    # Save caller-saved registers (if needed)
    st.d $a0, $sp, 280
    addi.d  $sp, $sp, 0
    bl putch
    addi.d $sp, $sp, 0
    # Restore caller-saved registers (if needed)
    ld.d $a0, $sp, 280
    ld.w $a0, $sp, 16
    addi.w $a1, $a0, 1
# Store to memory
    st.w $a1, $sp, 16
    # Unconditional branch
    b main_1
main_3:
# Store to memory
    li.w $t1, 0
    st.w $t1, $sp, 60
    # Unconditional branch
    b main_label_ret
.data
.globl n
.p2align 2
n:
.word 0
.bss

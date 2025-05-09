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

    //ld.w $a1, $fp, 4
    //or $a0, $a1, $zero
    //addi.d $sp, $fp, 0
    //ld.d $ra, $sp, 8
    //ld.d $fp, $sp, 0
    //addi.d $sp, $sp, 16
    //jr $ra


    li.w $t1, 5

    //ld.w $a1, $fp, 4
    //or $a0, $a1, $zero
    //addi.d $sp, $fp, 0
    //ld.d $ra, $sp, 8
    //ld.d $fp, $sp, 0
    //addi.d $sp, $sp, 16
    //jr $ra

    st.w $t1, $fp, 8

    ld.w $a1, $fp, 4
    or $a0, $a1, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra

# Store to memory
    li.w $t1, 10
    st.w $t1, $fp, 12

    ld.w $a1, $fp, 4
    or $a0, $a1, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra



    ld.w $a2, $fp, 8
    li.w $t0, 0
    sub.w $a3, $t0, $a2
# Store to memory
    st.w $a3, $fp, 8
    ld.w $a2, $fp, 8
# Store to memory
    st.w $a2, $fp, 4
    # Unconditional branch
    b label_label_ret
label_label_ret:
    ld.w $a1, $fp, 4
    or $a0, $a1, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
.data
.bss

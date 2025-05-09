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
    addi.d $sp, $sp, -72
label_label_entry:
    or $a2, $a1, $zero
    # Element size: 8 bytes
    # Element size: 4 bytes
# Store to memory
    li.w $t1, 1
    st.w $t1, $a2, 0 # %v3: $a2
    or $a3, $a2, $zero
    # Element size: 4 bytes
    addi.d $a3, $a3, 4
# Store to memory
    li.w $t1, 2
    st.w $t1, $a3, 0 # %v4: $a3
    or $a3, $a2, $zero
    # Element size: 4 bytes
    addi.d $a3, $a3, 8
# Store to memory
    li.w $t1, 3
    st.w $t1, $a3, 0 # %v5: $a3
    or $a4, $a3, $zero
    # Element size: 4 bytes
    addi.d $a4, $a4, 4
# Store to memory
    li.w $t1, 4
    st.w $t1, $a4, 0 # %v6: $a4
    or $a3, $a2, $zero
    # Element size: 4 bytes
    addi.d $a3, $a3, 16
# Store to memory
    li.w $t1, 5
    st.w $t1, $a3, 0 # %v7: $a3
    or $a4, $a3, $zero
    # Element size: 4 bytes
    addi.d $a4, $a4, 4
# Store to memory
    li.w $t1, 6
    st.w $t1, $a4, 0 # %v8: $a4
    or $a3, $a2, $zero
    # Element size: 4 bytes
    addi.d $a3, $a3, 24
# Store to memory
    li.w $t1, 7
    st.w $t1, $a3, 0 # %v9: $a3
    or $a2, $a3, $zero
    # Element size: 4 bytes
    addi.d $a2, $a2, 4
# Store to memory
    li.w $t1, 8
    st.w $t1, $a2, 0 # %v10: $a2
    or $a3, $a2, $zero
    # Element size: 8 bytes
    # Element size: 4 bytes
# Store to memory
    li.w $t1, 0
    st.w $t1, $a3, 0
    or $a2, $a3, $zero
    # Element size: 4 bytes
    addi.d $a2, $a2, 4
    or $a4, $a1, $zero
    # Element size: 8 bytes
    addi.d $a4, $a4, 16
    # Element size: 4 bytes
    addi.d $a4, $a4, 4
    ld.w $a5, $a4, 0
# Store to memory
    st.w $a5, $a2, 0
    or $a2, $a3, $zero
    # Element size: 4 bytes
    addi.d $a2, $a2, 8
# Store to memory
    li.w $t1, 3
    st.w $t1, $a2, 0
    or $a4, $a2, $zero
    # Element size: 4 bytes
    addi.d $a4, $a4, 4
# Store to memory
    li.w $t1, 4
    st.w $t1, $a4, 0
    or $a2, $a3, $zero
    # Element size: 4 bytes
    addi.d $a2, $a2, 16
# Store to memory
    li.w $t1, 5
    st.w $t1, $a2, 0
    or $a4, $a2, $zero
    # Element size: 4 bytes
    addi.d $a4, $a4, 4
# Store to memory
    li.w $t1, 6
    st.w $t1, $a4, 0
    or $a2, $a3, $zero
    # Element size: 4 bytes
    addi.d $a2, $a2, 24
# Store to memory
    li.w $t1, 7
    st.w $t1, $a2, 0
    or $a3, $a2, $zero
    # Element size: 4 bytes
    addi.d $a3, $a3, 4
# Store to memory
    li.w $t1, 8
    st.w $t1, $a3, 0
    or $a2, $a1, $zero
    # Element size: 8 bytes
    addi.d $a2, $a2, 24
    # Element size: 4 bytes
    addi.d $a2, $a2, 4
    ld.w $a1, $a2, 0
# Store to memory
    st.w $a1, $fp, -4
    # Unconditional branch
    b label_label_ret
label_label_ret:
    ld.w $a1, $fp, -4
    or $a0, $a1, $zero
    addi.d $sp, $fp, 0
    ld.d $ra, $sp, 8
    ld.d $fp, $sp, 0
    addi.d $sp, $sp, 16
    jr $ra
.data
.bss

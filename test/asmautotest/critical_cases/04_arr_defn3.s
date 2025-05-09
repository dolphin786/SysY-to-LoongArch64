	.text
	.file	"04_arr_defn3.ll"
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi.d	$sp, $sp, -176
	.cfi_def_cfa_offset 176
	ori	$a0, $zero, 1
	lu32i.d	$a0, 2
	st.d	$a0, $sp, 104
	st.d	$a0, $sp, 72
	st.d	$a0, $sp, 40
	move	$a0, $zero
	st.d	$a0, $sp, 0                     # 8-byte Folded Spill
	st.d	$a0, $sp, 56
	st.d	$a0, $sp, 48
	ori	$a3, $zero, 5
	st.w	$a3, $sp, 56
	lu32i.d	$a3, 6
	ori	$a2, $zero, 3
	st.w	$a2, $sp, 48
	lu32i.d	$a2, 4
	st.d	$a0, $sp, 160
	st.d	$a0, $sp, 152
	st.d	$a0, $sp, 144
	st.d	$a0, $sp, 136
	st.d	$a2, $sp, 112
	st.d	$a3, $sp, 120
	ori	$a4, $zero, 7
	lu32i.d	$a4, 8
	st.d	$a4, $sp, 128
	st.d	$a4, $sp, 96
	st.d	$a3, $sp, 88
	st.d	$a2, $sp, 80
	st.d	$a4, $sp, 64
	st.d	$a0, $sp, 32
	st.d	$a0, $sp, 24
	st.d	$a0, $sp, 16
	st.d	$a0, $sp, 8
	ld.w	$a0, $sp, 60
	st.w	$a0, $sp, 8
	ld.w	$a1, $sp, 92
	st.d	$a4, $sp, 32
	st.d	$a3, $sp, 24
	st.d	$a2, $sp, 16
	st.w	$a1, $sp, 12
	add.d	$a0, $a0, $a1
	ld.w	$a1, $sp, 152
	add.d	$a0, $a0, $a1
	addi.d	$a0, $a0, 8
	st.w	$a0, $sp, 172
	b	.LBB0_1
.LBB0_1:                                # %label_ret
	ld.w	$a0, $sp, 172
	addi.d	$sp, $sp, 176
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
	.addrsig

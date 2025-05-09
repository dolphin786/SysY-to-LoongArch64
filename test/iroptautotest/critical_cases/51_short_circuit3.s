	.text
	.file	"51_short_circuit3.ll"
	.globl	set_a                           # -- Begin function set_a
	.p2align	2
	.type	set_a,@function
set_a:                                  # @set_a
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi.d	$sp, $sp, -16
	.cfi_def_cfa_offset 16
	pcalau12i	$a1, %got_pc_hi20(a)
	ld.d	$a1, $a1, %got_pc_lo12(a)
	st.w	$a0, $a1, 0
	st.w	$a0, $sp, 12
	st.w	$a0, $sp, 8
	b	.LBB0_1
.LBB0_1:                                # %label_ret
	ld.w	$a0, $sp, 8
	addi.d	$sp, $sp, 16
	ret
.Lfunc_end0:
	.size	set_a, .Lfunc_end0-set_a
	.cfi_endproc
                                        # -- End function
	.globl	set_b                           # -- Begin function set_b
	.p2align	2
	.type	set_b,@function
set_b:                                  # @set_b
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi.d	$sp, $sp, -16
	.cfi_def_cfa_offset 16
	pcalau12i	$a1, %got_pc_hi20(b)
	ld.d	$a1, $a1, %got_pc_lo12(b)
	st.w	$a0, $a1, 0
	st.w	$a0, $sp, 12
	st.w	$a0, $sp, 8
	b	.LBB1_1
.LBB1_1:                                # %label_ret
	ld.w	$a0, $sp, 8
	addi.d	$sp, $sp, 16
	ret
.Lfunc_end1:
	.size	set_b, .Lfunc_end1-set_b
	.cfi_endproc
                                        # -- End function
	.globl	set_d                           # -- Begin function set_d
	.p2align	2
	.type	set_d,@function
set_d:                                  # @set_d
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi.d	$sp, $sp, -16
	.cfi_def_cfa_offset 16
	pcalau12i	$a1, %got_pc_hi20(d)
	ld.d	$a1, $a1, %got_pc_lo12(d)
	st.w	$a0, $a1, 0
	st.w	$a0, $sp, 12
	st.w	$a0, $sp, 8
	b	.LBB2_1
.LBB2_1:                                # %label_ret
	ld.w	$a0, $sp, 8
	addi.d	$sp, $sp, 16
	ret
.Lfunc_end2:
	.size	set_d, .Lfunc_end2-set_d
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %label_entry
	addi.d	$sp, $sp, -96
	.cfi_def_cfa_offset 96
	st.d	$ra, $sp, 88                    # 8-byte Folded Spill
	st.d	$fp, $sp, 80                    # 8-byte Folded Spill
	.cfi_offset 1, -8
	.cfi_offset 22, -16
	addi.d	$fp, $sp, 96
	.cfi_def_cfa 22, 0
	pcalau12i	$a0, %got_pc_hi20(b)
	ld.d	$a1, $a0, %got_pc_lo12(b)
	ori	$a0, $zero, 3
	st.w	$a0, $a1, 0
	pcalau12i	$a0, %got_pc_hi20(a)
	ld.d	$a1, $a0, %got_pc_lo12(a)
	ori	$a0, $zero, 2
	st.w	$a0, $a1, 0
	move	$a0, $zero
	bl	%plt(set_a)
	bstrpick.d	$a0, $a0, 31, 0
	bnez	$a0, .LBB3_4
	b	.LBB3_3
.LBB3_1:                                # %label_ret
	ld.w	$a0, $fp, -20
	addi.d	$sp, $fp, -96
	ld.d	$fp, $sp, 80                    # 8-byte Folded Reload
	ld.d	$ra, $sp, 88                    # 8-byte Folded Reload
	addi.d	$sp, $sp, 96
	ret
.LBB3_2:                                # %label_4
	b	.LBB3_3
.LBB3_3:                                # %label_5
	pcalau12i	$a0, %got_pc_hi20(a)
	ld.d	$a0, $a0, %got_pc_lo12(a)
	st.d	$a0, $fp, -32                   # 8-byte Folded Spill
	ld.w	$a0, $a0, 0
	bl	%plt(putint)
	ori	$a0, $zero, 32
	st.d	$a0, $fp, -48                   # 8-byte Folded Spill
	bl	%plt(putch)
	pcalau12i	$a0, %got_pc_hi20(b)
	ld.d	$a0, $a0, %got_pc_lo12(b)
	st.d	$a0, $fp, -40                   # 8-byte Folded Spill
	ld.w	$a0, $a0, 0
	bl	%plt(putint)
	ld.d	$a0, $fp, -48                   # 8-byte Folded Reload
	bl	%plt(putch)
	ld.d	$a2, $fp, -40                   # 8-byte Folded Reload
	ld.d	$a1, $fp, -32                   # 8-byte Folded Reload
	ori	$a0, $zero, 3
	st.w	$a0, $a2, 0
	ori	$a0, $zero, 2
	st.w	$a0, $a1, 0
	move	$a0, $zero
	bl	%plt(set_a)
	bstrpick.d	$a0, $a0, 31, 0
	bnez	$a0, .LBB3_7
	b	.LBB3_6
.LBB3_4:                                # %label_10
	ori	$a0, $zero, 1
	bl	%plt(set_b)
	bstrpick.d	$a0, $a0, 31, 0
	bnez	$a0, .LBB3_2
	b	.LBB3_3
.LBB3_5:                                # %label_13
	b	.LBB3_6
.LBB3_6:                                # %label_14
	pcalau12i	$a0, %got_pc_hi20(a)
	ld.d	$a0, $a0, %got_pc_lo12(a)
	ld.w	$a0, $a0, 0
	bl	%plt(putint)
	ori	$a0, $zero, 32
	bl	%plt(putch)
	pcalau12i	$a0, %got_pc_hi20(b)
	ld.d	$a0, $a0, %got_pc_lo12(b)
	ld.w	$a0, $a0, 0
	bl	%plt(putint)
	ori	$a0, $zero, 10
	bl	%plt(putch)
	pcalau12i	$a0, %got_pc_hi20(d)
	ld.d	$a1, $a0, %got_pc_lo12(d)
	ori	$a0, $zero, 2
	st.w	$a0, $a1, 0
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_10
	b	.LBB3_9
.LBB3_7:                                # %label_17
	ori	$a0, $zero, 1
	bl	%plt(set_b)
	bstrpick.d	$a0, $a0, 31, 0
	bnez	$a0, .LBB3_5
	b	.LBB3_6
.LBB3_8:                                # %label_20
	b	.LBB3_9
.LBB3_9:                                # %label_21
	pcalau12i	$a0, %got_pc_hi20(d)
	ld.d	$a0, $a0, %got_pc_lo12(d)
	ld.w	$a0, $a0, 0
	bl	%plt(putint)
	ori	$a0, $zero, 32
	bl	%plt(putch)
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_11
	b	.LBB3_13
.LBB3_10:                               # %label_23
	ori	$a0, $zero, 3
	bl	%plt(set_d)
	bstrpick.d	$a0, $a0, 31, 0
	bnez	$a0, .LBB3_8
	b	.LBB3_9
.LBB3_11:                               # %label_26
	b	.LBB3_12
.LBB3_12:                               # %label_27
	pcalau12i	$a0, %got_pc_hi20(d)
	ld.d	$a0, $a0, %got_pc_lo12(d)
	ld.w	$a0, $a0, 0
	bl	%plt(putint)
	ori	$a0, $zero, 10
	bl	%plt(putch)
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_14
	b	.LBB3_15
.LBB3_13:                               # %label_29
	ori	$a0, $zero, 4
	bl	%plt(set_d)
	bstrpick.d	$a0, $a0, 31, 0
	bnez	$a0, .LBB3_11
	b	.LBB3_12
.LBB3_14:                               # %label_32
	ori	$a0, $zero, 65
	bl	%plt(putch)
	b	.LBB3_15
.LBB3_15:                               # %label_33
	move	$a0, $zero
	bnez	$a0, .LBB3_17
	b	.LBB3_16
.LBB3_16:                               # %label_34
	ori	$a0, $zero, 66
	bl	%plt(putch)
	b	.LBB3_17
.LBB3_17:                               # %label_35
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_19
	b	.LBB3_18
.LBB3_18:                               # %label_36
	ori	$a0, $zero, 67
	bl	%plt(putch)
	b	.LBB3_19
.LBB3_19:                               # %label_37
	move	$a0, $zero
	bnez	$a0, .LBB3_21
	b	.LBB3_20
.LBB3_20:                               # %label_38
	ori	$a0, $zero, 68
	bl	%plt(putch)
	b	.LBB3_21
.LBB3_21:                               # %label_39
	move	$a0, $zero
	bnez	$a0, .LBB3_23
	b	.LBB3_22
.LBB3_22:                               # %label_40
	ori	$a0, $zero, 69
	bl	%plt(putch)
	b	.LBB3_23
.LBB3_23:                               # %label_41
	move	$a0, $zero
	bnez	$a0, .LBB3_25
	b	.LBB3_24
.LBB3_24:                               # %label_42
	ori	$a0, $zero, 70
	bl	%plt(putch)
	b	.LBB3_25
.LBB3_25:                               # %label_43
	ori	$a0, $zero, 10
	bl	%plt(putch)
	move	$a1, $sp
	addi.d	$a0, $a1, -16
	st.d	$a0, $fp, -88                   # 8-byte Folded Spill
	move	$sp, $a0
	move	$a0, $zero
	st.w	$a0, $a1, -16
	move	$a1, $sp
	addi.d	$a0, $a1, -16
	st.d	$a0, $fp, -80                   # 8-byte Folded Spill
	move	$sp, $a0
	ori	$a0, $zero, 1
	st.w	$a0, $a1, -16
	move	$a1, $sp
	addi.d	$a0, $a1, -16
	st.d	$a0, $fp, -72                   # 8-byte Folded Spill
	move	$sp, $a0
	ori	$a0, $zero, 2
	st.w	$a0, $a1, -16
	move	$a1, $sp
	addi.d	$a0, $a1, -16
	st.d	$a0, $fp, -64                   # 8-byte Folded Spill
	move	$sp, $a0
	ori	$a0, $zero, 3
	st.w	$a0, $a1, -16
	move	$a1, $sp
	addi.d	$a0, $a1, -16
	st.d	$a0, $fp, -56                   # 8-byte Folded Spill
	move	$sp, $a0
	ori	$a0, $zero, 4
	st.w	$a0, $a1, -16
	b	.LBB3_26
.LBB3_26:                               # %label_49
                                        # =>This Inner Loop Header: Depth=1
	ld.d	$a0, $fp, -88                   # 8-byte Folded Reload
	ld.wu	$a0, $a0, 0
	bnez	$a0, .LBB3_29
	b	.LBB3_28
.LBB3_27:                               # %label_52
                                        #   in Loop: Header=BB3_26 Depth=1
	ori	$a0, $zero, 32
	bl	%plt(putch)
	b	.LBB3_26
.LBB3_28:                               # %label_53
	ld.d	$a0, $fp, -88                   # 8-byte Folded Reload
	ld.wu	$a0, $a0, 0
	bnez	$a0, .LBB3_30
	b	.LBB3_32
.LBB3_29:                               # %label_56
                                        #   in Loop: Header=BB3_26 Depth=1
	ld.d	$a0, $fp, -80                   # 8-byte Folded Reload
	ld.wu	$a0, $a0, 0
	bnez	$a0, .LBB3_27
	b	.LBB3_28
.LBB3_30:                               # %label_59
	ori	$a0, $zero, 67
	bl	%plt(putch)
	b	.LBB3_31
.LBB3_31:                               # %label_60
	ld.d	$a0, $fp, -88                   # 8-byte Folded Reload
	ld.d	$a1, $fp, -80                   # 8-byte Folded Reload
	ld.w	$a1, $a1, 0
	ld.w	$a0, $a0, 0
	bge	$a0, $a1, .LBB3_33
	b	.LBB3_35
.LBB3_32:                               # %label_64
	ld.d	$a0, $fp, -80                   # 8-byte Folded Reload
	ld.wu	$a0, $a0, 0
	bnez	$a0, .LBB3_30
	b	.LBB3_31
.LBB3_33:                               # %label_67
	ori	$a0, $zero, 72
	bl	%plt(putch)
	b	.LBB3_34
.LBB3_34:                               # %label_68
	ld.d	$a0, $fp, -72                   # 8-byte Folded Reload
	ld.d	$a1, $fp, -80                   # 8-byte Folded Reload
	ld.w	$a1, $a1, 0
	ld.w	$a0, $a0, 0
	bge	$a0, $a1, .LBB3_38
	b	.LBB3_37
.LBB3_35:                               # %label_72
	ld.d	$a0, $fp, -88                   # 8-byte Folded Reload
	ld.d	$a1, $fp, -80                   # 8-byte Folded Reload
	ld.w	$a1, $a1, 0
	ld.w	$a0, $a0, 0
	bge	$a0, $a1, .LBB3_33
	b	.LBB3_34
.LBB3_36:                               # %label_76
	ori	$a0, $zero, 73
	bl	%plt(putch)
	b	.LBB3_37
.LBB3_37:                               # %label_77
	ld.d	$a1, $fp, -80                   # 8-byte Folded Reload
	ld.d	$a0, $fp, -88                   # 8-byte Folded Reload
	ld.wu	$a0, $a0, 0
	ld.wu	$a1, $a1, 0
	sltui	$a1, $a1, 1
	beq	$a0, $a1, .LBB3_42
	b	.LBB3_41
.LBB3_38:                               # %label_83
	ld.d	$a0, $fp, -56                   # 8-byte Folded Reload
	ld.d	$a1, $fp, -64                   # 8-byte Folded Reload
	ld.wu	$a1, $a1, 0
	ld.wu	$a0, $a0, 0
	bne	$a0, $a1, .LBB3_36
	b	.LBB3_37
.LBB3_39:                               # %label_87
	ori	$a0, $zero, 74
	bl	%plt(putch)
	b	.LBB3_40
.LBB3_40:                               # %label_88
	ld.d	$a1, $fp, -80                   # 8-byte Folded Reload
	ld.d	$a0, $fp, -88                   # 8-byte Folded Reload
	ld.wu	$a0, $a0, 0
	ld.wu	$a1, $a1, 0
	sltui	$a1, $a1, 1
	beq	$a0, $a1, .LBB3_43
	b	.LBB3_45
.LBB3_41:                               # %label_94
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_39
	b	.LBB3_40
.LBB3_42:                               # %label_98
	move	$a0, $zero
	bnez	$a0, .LBB3_39
	b	.LBB3_41
.LBB3_43:                               # %label_102
	ori	$a0, $zero, 75
	bl	%plt(putch)
	b	.LBB3_44
.LBB3_44:                               # %label_103
	ori	$a0, $zero, 10
	bl	%plt(putch)
	move	$a0, $zero
	st.w	$a0, $fp, -20
	b	.LBB3_1
.LBB3_45:                               # %label_104
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_44
	b	.LBB3_46
.LBB3_46:                               # %label_108
	ori	$a0, $zero, 1
	bnez	$a0, .LBB3_43
	b	.LBB3_44
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.type	a,@object                       # @a
	.bss
	.globl	a
	.p2align	2, 0x0
a:
	.word	0                               # 0x0
	.size	a, 4

	.type	b,@object                       # @b
	.globl	b
	.p2align	2, 0x0
b:
	.word	0                               # 0x0
	.size	b, 4

	.type	d,@object                       # @d
	.globl	d
	.p2align	2, 0x0
d:
	.word	0                               # 0x0
	.size	d, 4

	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym putint
	.addrsig_sym putch
	.addrsig_sym set_a
	.addrsig_sym set_b
	.addrsig_sym set_d
	.addrsig_sym a
	.addrsig_sym b
	.addrsig_sym d

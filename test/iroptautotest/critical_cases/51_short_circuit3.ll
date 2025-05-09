@a = global i32 0
@b = global i32 0
@d = global i32 0
declare i32 @getint()
declare float @getfloat()
declare i32 @getch()
declare i32 @getarray(i32*)
declare i32 @getfarray(float*)
declare void @putint(i32)
declare void @putfloat(float)
declare void @putch(i32)
declare void @putarray(i32, i32*)
declare void @putfarray(i32, float*)
declare void @_sysy_starttime(i32)
declare void @_sysy_stoptime(i32)
declare void @__aeabi_memcpy4(i32*, i32*, i32)
declare void @__aeabi_memclr4(i32*, i32)
declare void @__aeabi_memset4(i32*, i32, i32)
declare void @llvm.memset.p0.i32(i32*, i8, i32, i1)
define i32 @set_a(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = alloca i32
  %v3 = load i32, i32* %v1
  store i32 %v3, i32* @a
  %v4 = load i32, i32* @a
  store i32 %v4, i32* %v2
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v5 = load i32, i32* %v2
  ret i32 %v5
}
define i32 @set_b(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = alloca i32
  %v3 = load i32, i32* %v1
  store i32 %v3, i32* @b
  %v4 = load i32, i32* @b
  store i32 %v4, i32* %v2
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v5 = load i32, i32* %v2
  ret i32 %v5
}
define i32 @set_d(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = alloca i32
  %v3 = load i32, i32* %v1
  store i32 %v3, i32* @d
  %v4 = load i32, i32* @d
  store i32 %v4, i32* %v2
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v5 = load i32, i32* %v2
  ret i32 %v5
}
define i32 @main() {
label_entry:
  %v0 = alloca i32
  store i32 2, i32* @a
  store i32 3, i32* @b
  %v1 = call i32 @set_a(i32 0)
  %v2 = icmp ne i32 %v1, 0
  br i1 %v2, label %label_10, label %label_5
label_ret:                                                ; preds = %label_103
  %v3 = load i32, i32* %v0
  ret i32 %v3
label_4:                                                ; preds = %label_10
  br label %label_5
label_5:                                                ; preds = %label_entry, %label_10, %label_4
  %v6 = load i32, i32* @a
  call void @putint(i32 %v6)
  call void @putch(i32 32)
  %v7 = load i32, i32* @b
  call void @putint(i32 %v7)
  call void @putch(i32 32)
  store i32 2, i32* @a
  store i32 3, i32* @b
  %v8 = call i32 @set_a(i32 0)
  %v9 = icmp ne i32 %v8, 0
  br i1 %v9, label %label_17, label %label_14
label_10:                                                ; preds = %label_entry
  %v11 = call i32 @set_b(i32 1)
  %v12 = icmp ne i32 %v11, 0
  br i1 %v12, label %label_4, label %label_5
label_13:                                                ; preds = %label_17
  br label %label_14
label_14:                                                ; preds = %label_5, %label_17, %label_13
  %v15 = load i32, i32* @a
  call void @putint(i32 %v15)
  call void @putch(i32 32)
  %v16 = load i32, i32* @b
  call void @putint(i32 %v16)
  call void @putch(i32 10)
  store i32 2, i32* @d
  br i1 1, label %label_23, label %label_21
  ; br label %label_23
  ; br label %label_23
label_17:                                                ; preds = %label_5
  %v18 = call i32 @set_b(i32 1)
  %v19 = icmp ne i32 %v18, 0
  br i1 %v19, label %label_13, label %label_14
label_20:                                                ; preds = %label_23
  br label %label_21
label_21:                                                ; preds = %label_14, %label_23, %label_20
  %v22 = load i32, i32* @d
  call void @putint(i32 %v22)
  call void @putch(i32 32)
  br i1 1, label %label_26, label %label_29
  ; br label %label_26
  ; br label %label_26
label_23:                                                ; preds = %label_14%label_14%label_14
  %v24 = call i32 @set_d(i32 3)
  %v25 = icmp ne i32 %v24, 0
  br i1 %v25, label %label_20, label %label_21
label_26:                                                ; preds = %label_21, %label_29%label_21%label_21
  br label %label_27
label_27:                                                ; preds = %label_29, %label_26
  %v28 = load i32, i32* @d
  call void @putint(i32 %v28)
  call void @putch(i32 10)
  br i1 1, label %label_32, label %label_33
  ; br label %label_32
  ; br label %label_32
label_29:                                                ; preds = %label_21
  %v30 = call i32 @set_d(i32 4)
  %v31 = icmp ne i32 %v30, 0
  br i1 %v31, label %label_26, label %label_27
label_32:                                                ; preds = %label_27%label_27%label_27
  call void @putch(i32 65)
  br label %label_33
label_33:                                                ; preds = %label_27, %label_32
  br i1 1, label %label_34, label %label_35
  ; br label %label_34
  ; br label %label_34
label_34:                                                ; preds = %label_33%label_33%label_33
  call void @putch(i32 66)
  br label %label_35
label_35:                                                ; preds = %label_33, %label_34
  br i1 0, label %label_36, label %label_37
  ; br label %label_37
  ; br label %label_37
label_36:                                                ; preds = %label_35
  call void @putch(i32 67)
  br label %label_37
label_37:                                                ; preds = %label_35, %label_36%label_35%label_35
  br i1 1, label %label_38, label %label_39
  ; br label %label_38
  ; br label %label_38
label_38:                                                ; preds = %label_37%label_37%label_37
  call void @putch(i32 68)
  br label %label_39
label_39:                                                ; preds = %label_37, %label_38
  br i1 1, label %label_40, label %label_41
  ; br label %label_40
  ; br label %label_40
label_40:                                                ; preds = %label_39%label_39%label_39
  call void @putch(i32 69)
  br label %label_41
label_41:                                                ; preds = %label_39, %label_40
  br i1 1, label %label_42, label %label_43
  ; br label %label_42
  ; br label %label_42
label_42:                                                ; preds = %label_41%label_41%label_41
  call void @putch(i32 70)
  br label %label_43
label_43:                                                ; preds = %label_41, %label_42
  call void @putch(i32 10)
  %v44 = alloca i32
  store i32 0, i32* %v44
  %v45 = alloca i32
  store i32 1, i32* %v45
  %v46 = alloca i32
  store i32 2, i32* %v46
  %v47 = alloca i32
  store i32 3, i32* %v47
  %v48 = alloca i32
  store i32 4, i32* %v48
  br label %label_49
label_49:                                                ; preds = %label_43, %label_52
  %v50 = load i32, i32* %v44
  %v51 = icmp ne i32 %v50, 0
  br i1 %v51, label %label_56, label %label_53
label_52:                                                ; preds = %label_56
  call void @putch(i32 32)
  br label %label_49
label_53:                                                ; preds = %label_49, %label_56
  %v54 = load i32, i32* %v44
  %v55 = icmp ne i32 %v54, 0
  br i1 %v55, label %label_59, label %label_64
label_56:                                                ; preds = %label_49
  %v57 = load i32, i32* %v45
  %v58 = icmp ne i32 %v57, 0
  br i1 %v58, label %label_52, label %label_53
label_59:                                                ; preds = %label_53, %label_64
  call void @putch(i32 67)
  br label %label_60
label_60:                                                ; preds = %label_64, %label_59
  %v61 = load i32, i32* %v44
  %v62 = load i32, i32* %v45
  %v63 = icmp sge i32 %v61, %v62
  br i1 %v63, label %label_67, label %label_72
label_64:                                                ; preds = %label_53
  %v65 = load i32, i32* %v45
  %v66 = icmp ne i32 %v65, 0
  br i1 %v66, label %label_59, label %label_60
label_67:                                                ; preds = %label_60, %label_72
  call void @putch(i32 72)
  br label %label_68
label_68:                                                ; preds = %label_72, %label_67
  %v69 = load i32, i32* %v46
  %v70 = load i32, i32* %v45
  %v71 = icmp sge i32 %v69, %v70
  br i1 %v71, label %label_83, label %label_77
label_72:                                                ; preds = %label_60
  %v73 = load i32, i32* %v45
  %v74 = load i32, i32* %v44
  %v75 = icmp sle i32 %v73, %v74
  br i1 %v75, label %label_67, label %label_68
label_76:                                                ; preds = %label_83
  call void @putch(i32 73)
  br label %label_77
label_77:                                                ; preds = %label_68, %label_83, %label_76
  %v78 = load i32, i32* %v44
  %v79 = load i32, i32* %v45
  %v80 = icmp eq i32 %v79, 0
  %v81 = zext i1 %v80 to i32
  %v82 = icmp eq i32 %v78, %v81
  br i1 %v82, label %label_98, label %label_94
label_83:                                                ; preds = %label_68
  %v84 = load i32, i32* %v48
  %v85 = load i32, i32* %v47
  %v86 = icmp ne i32 %v84, %v85
  br i1 %v86, label %label_76, label %label_77
label_87:                                                ; preds = %label_98, %label_94
  call void @putch(i32 74)
  br label %label_88
label_88:                                                ; preds = %label_94, %label_87
  %v89 = load i32, i32* %v44
  %v90 = load i32, i32* %v45
  %v91 = icmp eq i32 %v90, 0
  %v92 = zext i1 %v91 to i32
  %v93 = icmp eq i32 %v89, %v92
  br i1 %v93, label %label_102, label %label_104
label_94:                                                ; preds = %label_77, %label_98
  %v95 = load i32, i32* %v48
  %v96 = load i32, i32* %v48
  %v97 = icmp sge i32 %v95, %v96
  br i1 %v97, label %label_87, label %label_88
label_98:                                                ; preds = %label_77
  %v99 = load i32, i32* %v47
  %v100 = load i32, i32* %v47
  %v101 = icmp slt i32 %v99, %v100
  br i1 %v101, label %label_87, label %label_94
label_102:                                                ; preds = %label_88, %label_108
  call void @putch(i32 75)
  br label %label_103
label_103:                                                ; preds = %label_104, %label_108, %label_102
  call void @putch(i32 10)
  store i32 0, i32* %v0
  br label %label_ret
label_104:                                                ; preds = %label_88
  %v105 = load i32, i32* %v47
  %v106 = load i32, i32* %v47
  %v107 = icmp slt i32 %v105, %v106
  br i1 %v107, label %label_108, label %label_103
label_108:                                                ; preds = %label_104
  %v109 = load i32, i32* %v48
  %v110 = load i32, i32* %v48
  %v111 = icmp sge i32 %v109, %v110
  br i1 %v111, label %label_102, label %label_103
}

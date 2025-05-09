@arr1 = global [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]] zeroinitializer
@arr2 = global [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]] zeroinitializer
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
define void @loop1(i32 %arg_0, i32 %arg_1) {
label_entry:
  %v2 = alloca i32
  store i32 %arg_0, i32* %v2
  %v3 = alloca i32
  store i32 %arg_1, i32* %v3
  %v4 = alloca i32
  %v5 = alloca i32
  %v6 = alloca i32
  %v7 = alloca i32
  %v8 = alloca i32
  %v9 = alloca i32
  %v10 = alloca i32
  store i32 0, i32* %v4
  br label %label_11
label_ret:                                                ; preds = %label_16
  ret void
label_11:                                                ; preds = %label_entry, %label_25
  %v12 = load i32, i32* %v4
  %v13 = load i32, i32* %v2
  %v14 = icmp slt i32 %v12, %v13
  br i1 %v14, label %label_17, label %label_16
label_15:                                                ; preds = %label_17
  store i32 0, i32* %v5
  br label %label_21
label_16:                                                ; preds = %label_11, %label_17
  br label %label_ret
label_17:                                                ; preds = %label_11
  %v18 = load i32, i32* %v4
  %v19 = load i32, i32* %v3
  %v20 = icmp slt i32 %v18, %v19
  br i1 %v20, label %label_15, label %label_16
label_21:                                                ; preds = %label_15, %label_32
  %v22 = load i32, i32* %v5
  %v23 = icmp slt i32 %v22, 2
  br i1 %v23, label %label_24, label %label_25
label_24:                                                ; preds = %label_21
  store i32 0, i32* %v6
  br label %label_28
label_25:                                                ; preds = %label_21
  %v26 = load i32, i32* %v4
  %v27 = add i32 %v26, 1
  store i32 %v27, i32* %v4
  br label %label_11
label_28:                                                ; preds = %label_24, %label_39
  %v29 = load i32, i32* %v6
  %v30 = icmp slt i32 %v29, 3
  br i1 %v30, label %label_31, label %label_32
label_31:                                                ; preds = %label_28
  store i32 0, i32* %v7
  br label %label_35
label_32:                                                ; preds = %label_28
  %v33 = load i32, i32* %v5
  %v34 = add i32 %v33, 1
  store i32 %v34, i32* %v5
  br label %label_21
label_35:                                                ; preds = %label_31, %label_46
  %v36 = load i32, i32* %v7
  %v37 = icmp slt i32 %v36, 4
  br i1 %v37, label %label_38, label %label_39
label_38:                                                ; preds = %label_35
  store i32 0, i32* %v8
  br label %label_42
label_39:                                                ; preds = %label_35
  %v40 = load i32, i32* %v6
  %v41 = add i32 %v40, 1
  store i32 %v41, i32* %v6
  br label %label_28
label_42:                                                ; preds = %label_38, %label_53
  %v43 = load i32, i32* %v8
  %v44 = icmp slt i32 %v43, 5
  br i1 %v44, label %label_45, label %label_46
label_45:                                                ; preds = %label_42
  store i32 0, i32* %v9
  br label %label_49
label_46:                                                ; preds = %label_42
  %v47 = load i32, i32* %v7
  %v48 = add i32 %v47, 1
  store i32 %v48, i32* %v7
  br label %label_35
label_49:                                                ; preds = %label_45, %label_87
  %v50 = load i32, i32* %v9
  %v51 = icmp slt i32 %v50, 6
  br i1 %v51, label %label_52, label %label_53
label_52:                                                ; preds = %label_49
  store i32 0, i32* %v10
  br label %label_56
label_53:                                                ; preds = %label_49
  %v54 = load i32, i32* %v8
  %v55 = add i32 %v54, 1
  store i32 %v55, i32* %v8
  br label %label_42
label_56:                                                ; preds = %label_52, %label_59
  %v57 = load i32, i32* %v10
  %v58 = icmp slt i32 %v57, 2
  br i1 %v58, label %label_59, label %label_87
label_59:                                                ; preds = %label_56
  %v60 = load i32, i32* %v4
  %v61 = load i32, i32* %v5
  %v62 = load i32, i32* %v6
  %v63 = load i32, i32* %v7
  %v64 = load i32, i32* %v8
  %v65 = load i32, i32* %v9
  %v66 = load i32, i32* %v10
  %v67 = getelementptr [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]], [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]]* @arr1, i32 0, i32 %v60, i32 %v61, i32 %v62, i32 %v63, i32 %v64, i32 %v65, i32 %v66
  %v68 = load i32, i32* %v4
  %v69 = load i32, i32* %v5
  %v70 = add i32 %v68, %v69
  %v71 = load i32, i32* %v6
  %v72 = add i32 %v70, %v71
  %v73 = load i32, i32* %v7
  %v74 = add i32 %v72, %v73
  %v75 = load i32, i32* %v8
  %v76 = add i32 %v74, %v75
  %v77 = load i32, i32* %v9
  %v78 = add i32 %v76, %v77
  %v79 = load i32, i32* %v10
  %v80 = add i32 %v78, %v79
  %v81 = load i32, i32* %v2
  %v82 = add i32 %v80, %v81
  %v83 = load i32, i32* %v3
  %v84 = add i32 %v82, %v83
  store i32 %v84, i32* %v67
  %v85 = load i32, i32* %v10
  %v86 = add i32 %v85, 1
  store i32 %v86, i32* %v10
  br label %label_56
label_87:                                                ; preds = %label_56
  %v88 = load i32, i32* %v9
  %v89 = add i32 %v88, 1
  store i32 %v89, i32* %v9
  br label %label_49
}
define void @loop2() {
label_entry:
  %v0 = alloca i32
  %v1 = alloca i32
  %v2 = alloca i32
  %v3 = alloca i32
  %v4 = alloca i32
  %v5 = alloca i32
  %v6 = alloca i32
  store i32 0, i32* %v0
  br label %label_7
label_ret:                                                ; preds = %label_11
  ret void
label_7:                                                ; preds = %label_entry, %label_16
  %v8 = load i32, i32* %v0
  %v9 = icmp slt i32 %v8, 10
  br i1 %v9, label %label_10, label %label_11
label_10:                                                ; preds = %label_7
  store i32 0, i32* %v1
  br label %label_12
label_11:                                                ; preds = %label_7
  br label %label_ret
label_12:                                                ; preds = %label_10, %label_23
  %v13 = load i32, i32* %v1
  %v14 = icmp slt i32 %v13, 2
  br i1 %v14, label %label_15, label %label_16
label_15:                                                ; preds = %label_12
  store i32 0, i32* %v2
  br label %label_19
label_16:                                                ; preds = %label_12
  %v17 = load i32, i32* %v0
  %v18 = add i32 %v17, 1
  store i32 %v18, i32* %v0
  br label %label_7
label_19:                                                ; preds = %label_15, %label_30
  %v20 = load i32, i32* %v2
  %v21 = icmp slt i32 %v20, 3
  br i1 %v21, label %label_22, label %label_23
label_22:                                                ; preds = %label_19
  store i32 0, i32* %v3
  br label %label_26
label_23:                                                ; preds = %label_19
  %v24 = load i32, i32* %v1
  %v25 = add i32 %v24, 1
  store i32 %v25, i32* %v1
  br label %label_12
label_26:                                                ; preds = %label_22, %label_37
  %v27 = load i32, i32* %v3
  %v28 = icmp slt i32 %v27, 2
  br i1 %v28, label %label_29, label %label_30
label_29:                                                ; preds = %label_26
  store i32 0, i32* %v4
  br label %label_33
label_30:                                                ; preds = %label_26
  %v31 = load i32, i32* %v2
  %v32 = add i32 %v31, 1
  store i32 %v32, i32* %v2
  br label %label_19
label_33:                                                ; preds = %label_29, %label_44
  %v34 = load i32, i32* %v4
  %v35 = icmp slt i32 %v34, 4
  br i1 %v35, label %label_36, label %label_37
label_36:                                                ; preds = %label_33
  store i32 0, i32* %v5
  br label %label_40
label_37:                                                ; preds = %label_33
  %v38 = load i32, i32* %v3
  %v39 = add i32 %v38, 1
  store i32 %v39, i32* %v3
  br label %label_26
label_40:                                                ; preds = %label_36, %label_68
  %v41 = load i32, i32* %v5
  %v42 = icmp slt i32 %v41, 8
  br i1 %v42, label %label_43, label %label_44
label_43:                                                ; preds = %label_40
  store i32 0, i32* %v6
  br label %label_47
label_44:                                                ; preds = %label_40
  %v45 = load i32, i32* %v4
  %v46 = add i32 %v45, 1
  store i32 %v46, i32* %v4
  br label %label_33
label_47:                                                ; preds = %label_43, %label_50
  %v48 = load i32, i32* %v6
  %v49 = icmp slt i32 %v48, 7
  br i1 %v49, label %label_50, label %label_68
label_50:                                                ; preds = %label_47
  %v51 = load i32, i32* %v0
  %v52 = load i32, i32* %v1
  %v53 = load i32, i32* %v2
  %v54 = load i32, i32* %v3
  %v55 = load i32, i32* %v4
  %v56 = load i32, i32* %v5
  %v57 = load i32, i32* %v6
  %v58 = getelementptr [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]], [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]]* @arr2, i32 0, i32 %v51, i32 %v52, i32 %v53, i32 %v54, i32 %v55, i32 %v56, i32 %v57
  %v59 = load i32, i32* %v0
  %v60 = load i32, i32* %v1
  %v61 = add i32 %v59, %v60
  %v62 = load i32, i32* %v3
  %v63 = add i32 %v61, %v62
  %v64 = load i32, i32* %v6
  %v65 = add i32 %v63, %v64
  store i32 %v65, i32* %v58
  %v66 = load i32, i32* %v6
  %v67 = add i32 %v66, 1
  store i32 %v67, i32* %v6
  br label %label_47
label_68:                                                ; preds = %label_47
  %v69 = load i32, i32* %v5
  %v70 = add i32 %v69, 1
  store i32 %v70, i32* %v5
  br label %label_40
}
define i32 @loop3(i32 %arg_0, i32 %arg_1, i32 %arg_2, i32 %arg_3, i32 %arg_4, i32 %arg_5, i32 %arg_6) {
label_entry:
  %v7 = alloca i32
  store i32 %arg_0, i32* %v7
  %v8 = alloca i32
  store i32 %arg_1, i32* %v8
  %v9 = alloca i32
  store i32 %arg_2, i32* %v9
  %v10 = alloca i32
  store i32 %arg_3, i32* %v10
  %v11 = alloca i32
  store i32 %arg_4, i32* %v11
  %v12 = alloca i32
  store i32 %arg_5, i32* %v12
  %v13 = alloca i32
  store i32 %arg_6, i32* %v13
  %v14 = alloca i32
  %v15 = alloca i32
  %v16 = alloca i32
  %v17 = alloca i32
  %v18 = alloca i32
  %v19 = alloca i32
  %v20 = alloca i32
  %v21 = alloca i32
  %v22 = alloca i32
  store i32 0, i32* %v22
  store i32 0, i32* %v15
  br label %label_24
label_ret:                                                ; preds = %label_28
  %v23 = load i32, i32* %v14
  ret i32 %v23
label_24:                                                ; preds = %label_entry, %label_130
  %v25 = load i32, i32* %v15
  %v26 = icmp slt i32 %v25, 10
  br i1 %v26, label %label_27, label %label_28
label_27:                                                ; preds = %label_24
  store i32 0, i32* %v16
  br label %label_30
label_28:                                                ; preds = %label_24, %label_129
  %v29 = load i32, i32* %v22
  store i32 %v29, i32* %v14
  br label %label_ret
label_30:                                                ; preds = %label_27, %label_128
  %v31 = load i32, i32* %v16
  %v32 = icmp slt i32 %v31, 100
  br i1 %v32, label %label_33, label %label_34
label_33:                                                ; preds = %label_30
  store i32 0, i32* %v17
  br label %label_40
label_34:                                                ; preds = %label_30, %label_127
  %v35 = load i32, i32* %v15
  %v36 = add i32 %v35, 1
  store i32 %v36, i32* %v15
  %v37 = load i32, i32* %v15
  %v38 = load i32, i32* %v7
  %v39 = icmp sge i32 %v37, %v38
  br i1 %v39, label %label_129, label %label_130
label_40:                                                ; preds = %label_33, %label_126
  %v41 = load i32, i32* %v17
  %v42 = icmp slt i32 %v41, 1000
  br i1 %v42, label %label_43, label %label_44
label_43:                                                ; preds = %label_40
  store i32 0, i32* %v18
  br label %label_50
label_44:                                                ; preds = %label_40, %label_125
  %v45 = load i32, i32* %v16
  %v46 = add i32 %v45, 1
  store i32 %v46, i32* %v16
  %v47 = load i32, i32* %v16
  %v48 = load i32, i32* %v8
  %v49 = icmp sge i32 %v47, %v48
  br i1 %v49, label %label_127, label %label_128
label_50:                                                ; preds = %label_43, %label_124
  %v51 = load i32, i32* %v18
  %v52 = icmp slt i32 %v51, 10000
  br i1 %v52, label %label_53, label %label_54
label_53:                                                ; preds = %label_50
  store i32 0, i32* %v19
  br label %label_60
label_54:                                                ; preds = %label_50, %label_123
  %v55 = load i32, i32* %v17
  %v56 = add i32 %v55, 1
  store i32 %v56, i32* %v17
  %v57 = load i32, i32* %v17
  %v58 = load i32, i32* %v9
  %v59 = icmp sge i32 %v57, %v58
  br i1 %v59, label %label_125, label %label_126
label_60:                                                ; preds = %label_53, %label_122
  %v61 = load i32, i32* %v19
  %v62 = icmp slt i32 %v61, 100000
  br i1 %v62, label %label_63, label %label_64
label_63:                                                ; preds = %label_60
  store i32 0, i32* %v20
  br label %label_70
label_64:                                                ; preds = %label_60, %label_121
  %v65 = load i32, i32* %v18
  %v66 = add i32 %v65, 1
  store i32 %v66, i32* %v18
  %v67 = load i32, i32* %v18
  %v68 = load i32, i32* %v10
  %v69 = icmp sge i32 %v67, %v68
  br i1 %v69, label %label_123, label %label_124
label_70:                                                ; preds = %label_63, %label_120
  %v71 = load i32, i32* %v20
  %v72 = icmp slt i32 %v71, 1000000
  br i1 %v72, label %label_73, label %label_74
label_73:                                                ; preds = %label_70
  store i32 0, i32* %v21
  br label %label_80
label_74:                                                ; preds = %label_70, %label_119
  %v75 = load i32, i32* %v19
  %v76 = add i32 %v75, 1
  store i32 %v76, i32* %v19
  %v77 = load i32, i32* %v19
  %v78 = load i32, i32* %v11
  %v79 = icmp sge i32 %v77, %v78
  br i1 %v79, label %label_121, label %label_122
label_80:                                                ; preds = %label_73, %label_118
  %v81 = load i32, i32* %v21
  %v82 = icmp slt i32 %v81, 10000000
  br i1 %v82, label %label_83, label %label_111
label_83:                                                ; preds = %label_80
  %v84 = load i32, i32* %v22
  %v85 = srem i32 %v84, 817
  %v86 = load i32, i32* %v15
  %v87 = load i32, i32* %v16
  %v88 = load i32, i32* %v17
  %v89 = load i32, i32* %v18
  %v90 = load i32, i32* %v19
  %v91 = load i32, i32* %v20
  %v92 = load i32, i32* %v21
  %v93 = getelementptr [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]], [10 x [2 x [3 x [4 x [5 x [6 x [2 x i32]]]]]]]* @arr1, i32 0, i32 %v86, i32 %v87, i32 %v88, i32 %v89, i32 %v90, i32 %v91, i32 %v92
  %v94 = load i32, i32* %v93
  %v95 = add i32 %v85, %v94
  %v96 = load i32, i32* %v15
  %v97 = load i32, i32* %v16
  %v98 = load i32, i32* %v17
  %v99 = load i32, i32* %v18
  %v100 = load i32, i32* %v19
  %v101 = load i32, i32* %v20
  %v102 = load i32, i32* %v21
  %v103 = getelementptr [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]], [10 x [2 x [3 x [2 x [4 x [8 x [7 x i32]]]]]]]* @arr2, i32 0, i32 %v96, i32 %v97, i32 %v98, i32 %v99, i32 %v100, i32 %v101, i32 %v102
  %v104 = load i32, i32* %v103
  %v105 = add i32 %v95, %v104
  store i32 %v105, i32* %v22
  %v106 = load i32, i32* %v21
  %v107 = add i32 %v106, 1
  store i32 %v107, i32* %v21
  %v108 = load i32, i32* %v21
  %v109 = load i32, i32* %v13
  %v110 = icmp sge i32 %v108, %v109
  br i1 %v110, label %label_117, label %label_118
label_111:                                                ; preds = %label_80, %label_117
  %v112 = load i32, i32* %v20
  %v113 = add i32 %v112, 1
  store i32 %v113, i32* %v20
  %v114 = load i32, i32* %v20
  %v115 = load i32, i32* %v12
  %v116 = icmp sge i32 %v114, %v115
  br i1 %v116, label %label_119, label %label_120
label_117:                                                ; preds = %label_83
  br label %label_111
label_118:                                                ; preds = %label_83
  br label %label_80
label_119:                                                ; preds = %label_111
  br label %label_74
label_120:                                                ; preds = %label_111
  br label %label_70
label_121:                                                ; preds = %label_74
  br label %label_64
label_122:                                                ; preds = %label_74
  br label %label_60
label_123:                                                ; preds = %label_64
  br label %label_54
label_124:                                                ; preds = %label_64
  br label %label_50
label_125:                                                ; preds = %label_54
  br label %label_44
label_126:                                                ; preds = %label_54
  br label %label_40
label_127:                                                ; preds = %label_44
  br label %label_34
label_128:                                                ; preds = %label_44
  br label %label_30
label_129:                                                ; preds = %label_34
  br label %label_28
label_130:                                                ; preds = %label_34
  br label %label_24
}
define i32 @main() {
label_entry:
  %v0 = alloca i32
  %v1 = call i32 @getint()
  %v2 = alloca i32
  store i32 %v1, i32* %v2
  %v3 = call i32 @getint()
  %v4 = alloca i32
  store i32 %v3, i32* %v4
  %v5 = call i32 @getint()
  %v6 = alloca i32
  store i32 %v5, i32* %v6
  %v7 = call i32 @getint()
  %v8 = alloca i32
  store i32 %v7, i32* %v8
  %v9 = call i32 @getint()
  %v10 = alloca i32
  store i32 %v9, i32* %v10
  %v11 = call i32 @getint()
  %v12 = alloca i32
  store i32 %v11, i32* %v12
  %v13 = call i32 @getint()
  %v14 = alloca i32
  store i32 %v13, i32* %v14
  %v15 = call i32 @getint()
  %v16 = alloca i32
  store i32 %v15, i32* %v16
  %v17 = call i32 @getint()
  %v18 = alloca i32
  store i32 %v17, i32* %v18
  %v19 = load i32, i32* %v2
  %v20 = load i32, i32* %v4
  call void @loop1(i32 %v19, i32 %v20)
  call void @loop2()
  %v21 = load i32, i32* %v6
  %v22 = load i32, i32* %v8
  %v23 = load i32, i32* %v10
  %v24 = load i32, i32* %v12
  %v25 = load i32, i32* %v14
  %v26 = load i32, i32* %v16
  %v27 = load i32, i32* %v18
  %v28 = call i32 @loop3(i32 %v21, i32 %v22, i32 %v23, i32 %v24, i32 %v25, i32 %v26, i32 %v27)
  store i32 %v28, i32* %v0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v29 = load i32, i32* %v0
  ret i32 %v29
}

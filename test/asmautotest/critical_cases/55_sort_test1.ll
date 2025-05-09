@n = global i32 0
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
define i32 @bubblesort(i32* %arg_0) {
label_entry:
  %v1 = alloca i32*
  store i32* %arg_0, i32** %v1
  %v2 = alloca i32
  %v3 = alloca i32
  %v4 = alloca i32
  %v5 = alloca i32
  store i32 0, i32* %v3
  br label %label_7
label_ret:                                                ; preds = %label_13
  %v6 = load i32, i32* %v2
  ret i32 %v6
label_7:                                                ; preds = %label_entry, %label_32
  %v8 = load i32, i32* %v3
  %v9 = load i32, i32* @n
  %v10 = sub i32 %v9, 1
  %v11 = icmp slt i32 %v8, %v10
  br i1 %v11, label %label_12, label %label_13
label_12:                                                ; preds = %label_7
  store i32 0, i32* %v4
  br label %label_14
label_13:                                                ; preds = %label_7
  store i32 0, i32* %v2
  br label %label_ret
label_14:                                                ; preds = %label_12, %label_53
  %v15 = load i32, i32* %v4
  %v16 = load i32, i32* @n
  %v17 = load i32, i32* %v3
  %v18 = sub i32 %v16, %v17
  %v19 = sub i32 %v18, 1
  %v20 = icmp slt i32 %v15, %v19
  br i1 %v20, label %label_21, label %label_32
label_21:                                                ; preds = %label_14
  %v22 = load i32, i32* %v4
  %v23 = load i32*, i32** %v1
  %v24 = getelementptr i32, i32* %v23, i32 %v22
  %v25 = load i32, i32* %v24
  %v26 = load i32, i32* %v4
  %v27 = add i32 %v26, 1
  %v28 = load i32*, i32** %v1
  %v29 = getelementptr i32, i32* %v28, i32 %v27
  %v30 = load i32, i32* %v29
  %v31 = icmp sgt i32 %v25, %v30
  br i1 %v31, label %label_35, label %label_53
label_32:                                                ; preds = %label_14
  %v33 = load i32, i32* %v3
  %v34 = add i32 %v33, 1
  store i32 %v34, i32* %v3
  br label %label_7
label_35:                                                ; preds = %label_21
  %v36 = load i32, i32* %v4
  %v37 = add i32 %v36, 1
  %v38 = load i32*, i32** %v1
  %v39 = getelementptr i32, i32* %v38, i32 %v37
  %v40 = load i32, i32* %v39
  store i32 %v40, i32* %v5
  %v41 = load i32, i32* %v4
  %v42 = add i32 %v41, 1
  %v43 = load i32*, i32** %v1
  %v44 = getelementptr i32, i32* %v43, i32 %v42
  %v45 = load i32, i32* %v4
  %v46 = load i32*, i32** %v1
  %v47 = getelementptr i32, i32* %v46, i32 %v45
  %v48 = load i32, i32* %v47
  store i32 %v48, i32* %v44
  %v49 = load i32, i32* %v4
  %v50 = load i32*, i32** %v1
  %v51 = getelementptr i32, i32* %v50, i32 %v49
  %v52 = load i32, i32* %v5
  store i32 %v52, i32* %v51
  br label %label_53
label_53:                                                ; preds = %label_21, %label_35
  %v54 = load i32, i32* %v4
  %v55 = add i32 %v54, 1
  store i32 %v55, i32* %v4
  br label %label_14
}
define i32 @main() {
label_entry:
  %v0 = alloca i32
  store i32 10, i32* @n
  %v1 = alloca [10 x i32]
  %v2 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 0
  store i32 4, i32* %v2
  %v3 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 1
  store i32 3, i32* %v3
  %v4 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 2
  store i32 9, i32* %v4
  %v5 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 3
  store i32 2, i32* %v5
  %v6 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 4
  store i32 0, i32* %v6
  %v7 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 5
  store i32 1, i32* %v7
  %v8 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 6
  store i32 6, i32* %v8
  %v9 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 7
  store i32 5, i32* %v9
  %v10 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 8
  store i32 7, i32* %v10
  %v11 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 9
  store i32 8, i32* %v11
  %v12 = alloca i32
  %v13 = alloca i32
  %v14 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 0
  %v15 = call i32 @bubblesort(i32* %v14)
  store i32 %v15, i32* %v12
  br label %label_17
label_ret:                                                ; preds = %label_29
  %v16 = load i32, i32* %v0
  ret i32 %v16
label_17:                                                ; preds = %label_entry, %label_21
  %v18 = load i32, i32* %v12
  %v19 = load i32, i32* @n
  %v20 = icmp slt i32 %v18, %v19
  br i1 %v20, label %label_21, label %label_29
label_21:                                                ; preds = %label_17
  %v22 = load i32, i32* %v12
  %v23 = getelementptr [10 x i32], [10 x i32]* %v1, i32 0, i32 %v22
  %v24 = load i32, i32* %v23
  store i32 %v24, i32* %v13
  %v25 = load i32, i32* %v13
  call void @putint(i32 %v25)
  store i32 10, i32* %v13
  %v26 = load i32, i32* %v13
  call void @putch(i32 %v26)
  %v27 = load i32, i32* %v12
  %v28 = add i32 %v27, 1
  store i32 %v28, i32* %v12
  br label %label_17
label_29:                                                ; preds = %label_17
  store i32 0, i32* %v0
  br label %label_ret
}

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
define i32 @main() {
label_entry:
  %v0 = alloca i32
  %v1 = alloca [4 x [2 x i32]]
  %v2 = bitcast [4 x [2 x i32]]* %v1 to i32*
  call void @llvm.memset.p0.i32(i32* %v2, i8 0, i32 32, i1 false)
  %v3 = alloca [4 x [2 x i32]]
  %v4 = bitcast [4 x [2 x i32]]* %v3 to i32*
  call void @llvm.memset.p0.i32(i32* %v4, i8 0, i32 32, i1 false)
  %v5 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v3, i32 0, i32 0, i32 0
  store i32 1, i32* %v5
  %v6 = getelementptr i32, i32* %v5, i32 1
  store i32 2, i32* %v6
  %v7 = getelementptr i32, i32* %v5, i32 2
  store i32 3, i32* %v7
  %v8 = getelementptr i32, i32* %v5, i32 3
  store i32 4, i32* %v8
  %v9 = getelementptr i32, i32* %v5, i32 4
  store i32 5, i32* %v9
  %v10 = getelementptr i32, i32* %v5, i32 5
  store i32 6, i32* %v10
  %v11 = getelementptr i32, i32* %v5, i32 6
  store i32 7, i32* %v11
  %v12 = getelementptr i32, i32* %v5, i32 7
  store i32 8, i32* %v12
  %v13 = alloca [4 x [2 x i32]]
  %v14 = bitcast [4 x [2 x i32]]* %v13 to i32*
  call void @llvm.memset.p0.i32(i32* %v14, i8 0, i32 32, i1 false)
  %v15 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v13, i32 0, i32 0, i32 0
  store i32 1, i32* %v15
  %v16 = getelementptr i32, i32* %v15, i32 1
  store i32 2, i32* %v16
  %v17 = getelementptr i32, i32* %v15, i32 2
  store i32 3, i32* %v17
  %v18 = getelementptr i32, i32* %v17, i32 1
  store i32 4, i32* %v18
  %v19 = getelementptr i32, i32* %v15, i32 4
  store i32 5, i32* %v19
  %v20 = getelementptr i32, i32* %v19, i32 1
  store i32 6, i32* %v20
  %v21 = getelementptr i32, i32* %v15, i32 6
  store i32 7, i32* %v21
  %v22 = getelementptr i32, i32* %v21, i32 1
  store i32 8, i32* %v22
  %v23 = alloca [4 x [2 x i32]]
  %v24 = bitcast [4 x [2 x i32]]* %v23 to i32*
  call void @llvm.memset.p0.i32(i32* %v24, i8 0, i32 32, i1 false)
  %v25 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v23, i32 0, i32 0, i32 0
  store i32 1, i32* %v25
  %v26 = getelementptr i32, i32* %v25, i32 1
  store i32 2, i32* %v26
  %v27 = getelementptr i32, i32* %v25, i32 2
  store i32 3, i32* %v27
  %v28 = getelementptr i32, i32* %v25, i32 4
  store i32 5, i32* %v28
  %v29 = getelementptr i32, i32* %v25, i32 6
  store i32 7, i32* %v29
  %v30 = getelementptr i32, i32* %v25, i32 7
  store i32 8, i32* %v30
  %v31 = alloca [4 x [2 x i32]]
  %v32 = bitcast [4 x [2 x i32]]* %v31 to i32*
  call void @llvm.memset.p0.i32(i32* %v32, i8 0, i32 32, i1 false)
  %v33 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v31, i32 0, i32 0, i32 0
  %v34 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v23, i32 0, i32 2, i32 1
  %v35 = load i32, i32* %v34
  store i32 %v35, i32* %v33
  %v36 = getelementptr i32, i32* %v33, i32 1
  %v37 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v13, i32 0, i32 2, i32 1
  %v38 = load i32, i32* %v37
  store i32 %v38, i32* %v36
  %v39 = getelementptr i32, i32* %v33, i32 2
  store i32 3, i32* %v39
  %v40 = getelementptr i32, i32* %v39, i32 1
  store i32 4, i32* %v40
  %v41 = getelementptr i32, i32* %v33, i32 4
  store i32 5, i32* %v41
  %v42 = getelementptr i32, i32* %v41, i32 1
  store i32 6, i32* %v42
  %v43 = getelementptr i32, i32* %v33, i32 6
  store i32 7, i32* %v43
  %v44 = getelementptr i32, i32* %v43, i32 1
  store i32 8, i32* %v44
  %v45 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v31, i32 0, i32 3, i32 1
  %v46 = load i32, i32* %v45
  %v47 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v31, i32 0, i32 0, i32 0
  %v48 = load i32, i32* %v47
  %v49 = add i32 %v46, %v48
  %v50 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v31, i32 0, i32 0, i32 1
  %v51 = load i32, i32* %v50
  %v52 = add i32 %v49, %v51
  %v53 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v1, i32 0, i32 2, i32 0
  %v54 = load i32, i32* %v53
  %v55 = add i32 %v52, %v54
  store i32 %v55, i32* %v0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v56 = load i32, i32* %v0
  ret i32 %v56
}

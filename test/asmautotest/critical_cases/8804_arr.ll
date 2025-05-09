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
  %v3 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v1, i32 0, i32 0, i32 0
  store i32 1, i32* %v3
  %v4 = getelementptr i32, i32* %v3, i32 1
  store i32 2, i32* %v4
  %v5 = getelementptr i32, i32* %v3, i32 2
  store i32 3, i32* %v5
  %v6 = getelementptr i32, i32* %v5, i32 1
  store i32 4, i32* %v6
  %v7 = getelementptr i32, i32* %v3, i32 4
  store i32 5, i32* %v7
  %v8 = getelementptr i32, i32* %v7, i32 1
  store i32 6, i32* %v8
  %v9 = getelementptr i32, i32* %v3, i32 6
  store i32 7, i32* %v9
  %v10 = getelementptr i32, i32* %v9, i32 1
  store i32 8, i32* %v10
  %v11 = alloca [4 x [2 x i32]]
  %v12 = bitcast [4 x [2 x i32]]* %v11 to i32*
  call void @llvm.memset.p0.i32(i32* %v12, i8 0, i32 32, i1 false)
  %v13 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v11, i32 0, i32 0, i32 0
  store i32 0, i32* %v13
  %v14 = getelementptr i32, i32* %v13, i32 1
  %v15 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v1, i32 0, i32 2, i32 1
  %v16 = load i32, i32* %v15
  store i32 %v16, i32* %v14
  %v17 = getelementptr i32, i32* %v13, i32 2
  store i32 3, i32* %v17
  %v18 = getelementptr i32, i32* %v17, i32 1
  store i32 4, i32* %v18
  %v19 = getelementptr i32, i32* %v13, i32 4
  store i32 5, i32* %v19
  %v20 = getelementptr i32, i32* %v19, i32 1
  store i32 6, i32* %v20
  %v21 = getelementptr i32, i32* %v13, i32 6
  store i32 7, i32* %v21
  %v22 = getelementptr i32, i32* %v21, i32 1
  store i32 8, i32* %v22
  %v23 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v1, i32 0, i32 3, i32 1
  %v24 = load i32, i32* %v23
  store i32 %v24, i32* %v0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v25 = load i32, i32* %v0
  ret i32 %v25
}

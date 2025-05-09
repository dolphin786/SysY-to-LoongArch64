@ints = global [10000 x i32] zeroinitializer
@intt = global i32 0
@chas = global [10000 x i32] zeroinitializer
@chat = global i32 0
@i = global i32 0
@ii = global i32 1
@c = global i32 0
@get = global [10000 x i32] zeroinitializer
@get2 = global [10000 x i32] zeroinitializer
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
define i32 @isdigit(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = alloca i32
  %v3 = load i32, i32* %v1
  %v4 = icmp sge i32 %v3, 48
  br i1 %v4, label %label_8, label %label_7
label_ret:                                                ; preds = %label_6, %label_7
  %v5 = load i32, i32* %v2
  ret i32 %v5
label_6:                                                ; preds = %label_8
  store i32 1, i32* %v2
  br label %label_ret
label_7:                                                ; preds = %label_entry, %label_8
  store i32 0, i32* %v2
  br label %label_ret
label_8:                                                ; preds = %label_entry
  %v9 = load i32, i32* %v1
  %v10 = icmp sle i32 %v9, 57
  br i1 %v10, label %label_6, label %label_7
}
define i32 @power(i32 %arg_0, i32 %arg_1) {
label_entry:
  %v2 = alloca i32
  store i32 %arg_0, i32* %v2
  %v3 = alloca i32
  store i32 %arg_1, i32* %v3
  %v4 = alloca i32
  %v5 = alloca i32
  store i32 1, i32* %v5
  br label %label_7
label_ret:                                                ; preds = %label_16
  %v6 = load i32, i32* %v4
  ret i32 %v6
label_7:                                                ; preds = %label_entry, %label_10
  %v8 = load i32, i32* %v3
  %v9 = icmp ne i32 %v8, 0
  br i1 %v9, label %label_10, label %label_16
label_10:                                                ; preds = %label_7
  %v11 = load i32, i32* %v5
  %v12 = load i32, i32* %v2
  %v13 = mul i32 %v11, %v12
  store i32 %v13, i32* %v5
  %v14 = load i32, i32* %v3
  %v15 = sub i32 %v14, 1
  store i32 %v15, i32* %v3
  br label %label_7
label_16:                                                ; preds = %label_7
  %v17 = load i32, i32* %v5
  store i32 %v17, i32* %v4
  br label %label_ret
}
define i32 @getstr(i32* %arg_0) {
label_entry:
  %v1 = alloca i32*
  store i32* %arg_0, i32** %v1
  %v2 = alloca i32
  %v3 = call i32 @getch()
  %v4 = alloca i32
  store i32 %v3, i32* %v4
  %v5 = alloca i32
  store i32 0, i32* %v5
  br label %label_7
label_ret:                                                ; preds = %label_18
  %v6 = load i32, i32* %v2
  ret i32 %v6
label_7:                                                ; preds = %label_entry, %label_10
  %v8 = load i32, i32* %v4
  %v9 = icmp ne i32 %v8, 13
  br i1 %v9, label %label_20, label %label_18
label_10:                                                ; preds = %label_20
  %v11 = load i32, i32* %v5
  %v12 = load i32*, i32** %v1
  %v13 = getelementptr i32, i32* %v12, i32 %v11
  %v14 = load i32, i32* %v4
  store i32 %v14, i32* %v13
  %v15 = load i32, i32* %v5
  %v16 = add i32 %v15, 1
  store i32 %v16, i32* %v5
  %v17 = call i32 @getch()
  store i32 %v17, i32* %v4
  br label %label_7
label_18:                                                ; preds = %label_7, %label_20
  %v19 = load i32, i32* %v5
  store i32 %v19, i32* %v2
  br label %label_ret
label_20:                                                ; preds = %label_7
  %v21 = load i32, i32* %v4
  %v22 = icmp ne i32 %v21, 10
  br i1 %v22, label %label_10, label %label_18
}
define void @intpush(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = load i32, i32* @intt
  %v3 = add i32 %v2, 1
  store i32 %v3, i32* @intt
  %v4 = load i32, i32* @intt
  %v5 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 %v4
  %v6 = load i32, i32* %v1
  store i32 %v6, i32* %v5
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret void
}
define void @chapush(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = load i32, i32* @chat
  %v3 = add i32 %v2, 1
  store i32 %v3, i32* @chat
  %v4 = load i32, i32* @chat
  %v5 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v4
  %v6 = load i32, i32* %v1
  store i32 %v6, i32* %v5
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret void
}
define i32 @intpop() {
label_entry:
  %v0 = alloca i32
  %v1 = load i32, i32* @intt
  %v2 = sub i32 %v1, 1
  store i32 %v2, i32* @intt
  %v3 = load i32, i32* @intt
  %v4 = add i32 %v3, 1
  %v5 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 %v4
  %v6 = load i32, i32* %v5
  store i32 %v6, i32* %v0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v7 = load i32, i32* %v0
  ret i32 %v7
}
define i32 @chapop() {
label_entry:
  %v0 = alloca i32
  %v1 = load i32, i32* @chat
  %v2 = sub i32 %v1, 1
  store i32 %v2, i32* @chat
  %v3 = load i32, i32* @chat
  %v4 = add i32 %v3, 1
  %v5 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v4
  %v6 = load i32, i32* %v5
  store i32 %v6, i32* %v0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %v7 = load i32, i32* %v0
  ret i32 %v7
}
define void @intadd(i32 %arg_0) {
label_entry:
  %v1 = alloca i32
  store i32 %arg_0, i32* %v1
  %v2 = load i32, i32* @intt
  %v3 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 %v2
  %v4 = load i32, i32* @intt
  %v5 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 %v4
  %v6 = load i32, i32* %v5
  %v7 = mul i32 %v6, 10
  store i32 %v7, i32* %v3
  %v8 = load i32, i32* @intt
  %v9 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 %v8
  %v10 = load i32, i32* @intt
  %v11 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 %v10
  %v12 = load i32, i32* %v11
  %v13 = load i32, i32* %v1
  %v14 = add i32 %v12, %v13
  store i32 %v14, i32* %v9
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret void
}
define i32 @find() {
label_entry:
  %v0 = alloca i32
  %v1 = call i32 @chapop()
  store i32 %v1, i32* @c
  %v2 = load i32, i32* @ii
  %v3 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v2
  store i32 32, i32* %v3
  %v4 = load i32, i32* @ii
  %v5 = add i32 %v4, 1
  %v6 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v5
  %v7 = load i32, i32* @c
  store i32 %v7, i32* %v6
  %v8 = load i32, i32* @ii
  %v9 = add i32 %v8, 2
  store i32 %v9, i32* @ii
  %v10 = load i32, i32* @chat
  %v11 = icmp eq i32 %v10, 0
  br i1 %v11, label %label_13, label %label_14
label_ret:                                                ; preds = %label_13, %label_14
  %v12 = load i32, i32* %v0
  ret i32 %v12
label_13:                                                ; preds = %label_entry
  store i32 0, i32* %v0
  br label %label_ret
label_14:                                                ; preds = %label_entry
  store i32 1, i32* %v0
  br label %label_ret
}
define i32 @main() {
label_entry:
  %v0 = alloca i32
  store i32 0, i32* @intt
  store i32 0, i32* @chat
  %v1 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 0
  %v2 = call i32 @getstr(i32* %v1)
  %v3 = alloca i32
  %v4 = alloca i32
  %v5 = alloca i32
  %v6 = alloca i32
  %v7 = alloca i32
  store i32 %v2, i32* %v3
  br label %label_9
label_ret:                                                ; preds = %label_275
  %v8 = load i32, i32* %v0
  ret i32 %v8
label_9:                                                ; preds = %label_entry, %label_33
  %v10 = load i32, i32* @i
  %v11 = load i32, i32* %v3
  %v12 = icmp slt i32 %v10, %v11
  br i1 %v12, label %label_13, label %label_19
label_13:                                                ; preds = %label_9
  %v14 = load i32, i32* @i
  %v15 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v14
  %v16 = load i32, i32* %v15
  %v17 = call i32 @isdigit(i32 %v16)
  %v18 = icmp eq i32 %v17, 1
  br i1 %v18, label %label_20, label %label_28
label_19:                                                ; preds = %label_9
  br label %label_249
label_20:                                                ; preds = %label_13
  %v21 = load i32, i32* @ii
  %v22 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v21
  %v23 = load i32, i32* @i
  %v24 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v23
  %v25 = load i32, i32* %v24
  store i32 %v25, i32* %v22
  %v26 = load i32, i32* @ii
  %v27 = add i32 %v26, 1
  store i32 %v27, i32* @ii
  br label %label_33
label_28:                                                ; preds = %label_13
  %v29 = load i32, i32* @i
  %v30 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v29
  %v31 = load i32, i32* %v30
  %v32 = icmp eq i32 %v31, 40
  br i1 %v32, label %label_36, label %label_37
label_33:                                                ; preds = %label_20, %label_218
  %v34 = load i32, i32* @i
  %v35 = add i32 %v34, 1
  store i32 %v35, i32* @i
  br label %label_9
label_36:                                                ; preds = %label_28
  call void @chapush(i32 40)
  br label %label_37
label_37:                                                ; preds = %label_28, %label_36
  %v38 = load i32, i32* @i
  %v39 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v38
  %v40 = load i32, i32* %v39
  %v41 = icmp eq i32 %v40, 94
  br i1 %v41, label %label_42, label %label_43
label_42:                                                ; preds = %label_37
  call void @chapush(i32 94)
  br label %label_43
label_43:                                                ; preds = %label_37, %label_42
  %v44 = load i32, i32* @i
  %v45 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v44
  %v46 = load i32, i32* %v45
  %v47 = icmp eq i32 %v46, 41
  br i1 %v47, label %label_48, label %label_50
label_48:                                                ; preds = %label_43
  %v49 = call i32 @chapop()
  store i32 %v49, i32* @c
  br label %label_55
label_50:                                                ; preds = %label_43, %label_68
  %v51 = load i32, i32* @i
  %v52 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v51
  %v53 = load i32, i32* %v52
  %v54 = icmp eq i32 %v53, 43
  br i1 %v54, label %label_69, label %label_70
label_55:                                                ; preds = %label_48, %label_58
  %v56 = load i32, i32* @c
  %v57 = icmp ne i32 %v56, 40
  br i1 %v57, label %label_58, label %label_68
label_58:                                                ; preds = %label_55
  %v59 = load i32, i32* @ii
  %v60 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v59
  store i32 32, i32* %v60
  %v61 = load i32, i32* @ii
  %v62 = add i32 %v61, 1
  %v63 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v62
  %v64 = load i32, i32* @c
  store i32 %v64, i32* %v63
  %v65 = load i32, i32* @ii
  %v66 = add i32 %v65, 2
  store i32 %v66, i32* @ii
  %v67 = call i32 @chapop()
  store i32 %v67, i32* @c
  br label %label_55
label_68:                                                ; preds = %label_55
  br label %label_50
label_69:                                                ; preds = %label_50
  br label %label_75
label_70:                                                ; preds = %label_50, %label_83
  %v71 = load i32, i32* @i
  %v72 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v71
  %v73 = load i32, i32* %v72
  %v74 = icmp eq i32 %v73, 45
  br i1 %v74, label %label_111, label %label_112
label_75:                                                ; preds = %label_69, %label_110
  %v76 = load i32, i32* @chat
  %v77 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v76
  %v78 = load i32, i32* %v77
  %v79 = icmp eq i32 %v78, 43
  br i1 %v79, label %label_80, label %label_84
label_80:                                                ; preds = %label_75, %label_84, %label_89, %label_94, %label_99, %label_104
  %v81 = call i32 @find()
  %v82 = icmp eq i32 %v81, 0
  br i1 %v82, label %label_109, label %label_110
label_83:                                                ; preds = %label_104, %label_109
  call void @chapush(i32 43)
  br label %label_70
label_84:                                                ; preds = %label_75
  %v85 = load i32, i32* @chat
  %v86 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v85
  %v87 = load i32, i32* %v86
  %v88 = icmp eq i32 %v87, 45
  br i1 %v88, label %label_80, label %label_89
label_89:                                                ; preds = %label_84
  %v90 = load i32, i32* @chat
  %v91 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v90
  %v92 = load i32, i32* %v91
  %v93 = icmp eq i32 %v92, 42
  br i1 %v93, label %label_80, label %label_94
label_94:                                                ; preds = %label_89
  %v95 = load i32, i32* @chat
  %v96 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v95
  %v97 = load i32, i32* %v96
  %v98 = icmp eq i32 %v97, 47
  br i1 %v98, label %label_80, label %label_99
label_99:                                                ; preds = %label_94
  %v100 = load i32, i32* @chat
  %v101 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v100
  %v102 = load i32, i32* %v101
  %v103 = icmp eq i32 %v102, 37
  br i1 %v103, label %label_80, label %label_104
label_104:                                                ; preds = %label_99
  %v105 = load i32, i32* @chat
  %v106 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v105
  %v107 = load i32, i32* %v106
  %v108 = icmp eq i32 %v107, 94
  br i1 %v108, label %label_80, label %label_83
label_109:                                                ; preds = %label_80
  br label %label_83
label_110:                                                ; preds = %label_80
  br label %label_75
label_111:                                                ; preds = %label_70
  br label %label_117
label_112:                                                ; preds = %label_70, %label_125
  %v113 = load i32, i32* @i
  %v114 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v113
  %v115 = load i32, i32* %v114
  %v116 = icmp eq i32 %v115, 42
  br i1 %v116, label %label_153, label %label_154
label_117:                                                ; preds = %label_111, %label_152
  %v118 = load i32, i32* @chat
  %v119 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v118
  %v120 = load i32, i32* %v119
  %v121 = icmp eq i32 %v120, 43
  br i1 %v121, label %label_122, label %label_126
label_122:                                                ; preds = %label_117, %label_126, %label_131, %label_136, %label_141, %label_146
  %v123 = call i32 @find()
  %v124 = icmp eq i32 %v123, 0
  br i1 %v124, label %label_151, label %label_152
label_125:                                                ; preds = %label_146, %label_151
  call void @chapush(i32 45)
  br label %label_112
label_126:                                                ; preds = %label_117
  %v127 = load i32, i32* @chat
  %v128 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v127
  %v129 = load i32, i32* %v128
  %v130 = icmp eq i32 %v129, 45
  br i1 %v130, label %label_122, label %label_131
label_131:                                                ; preds = %label_126
  %v132 = load i32, i32* @chat
  %v133 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v132
  %v134 = load i32, i32* %v133
  %v135 = icmp eq i32 %v134, 42
  br i1 %v135, label %label_122, label %label_136
label_136:                                                ; preds = %label_131
  %v137 = load i32, i32* @chat
  %v138 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v137
  %v139 = load i32, i32* %v138
  %v140 = icmp eq i32 %v139, 47
  br i1 %v140, label %label_122, label %label_141
label_141:                                                ; preds = %label_136
  %v142 = load i32, i32* @chat
  %v143 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v142
  %v144 = load i32, i32* %v143
  %v145 = icmp eq i32 %v144, 37
  br i1 %v145, label %label_122, label %label_146
label_146:                                                ; preds = %label_141
  %v147 = load i32, i32* @chat
  %v148 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v147
  %v149 = load i32, i32* %v148
  %v150 = icmp eq i32 %v149, 94
  br i1 %v150, label %label_122, label %label_125
label_151:                                                ; preds = %label_122
  br label %label_125
label_152:                                                ; preds = %label_122
  br label %label_117
label_153:                                                ; preds = %label_112
  br label %label_159
label_154:                                                ; preds = %label_112, %label_167
  %v155 = load i32, i32* @i
  %v156 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v155
  %v157 = load i32, i32* %v156
  %v158 = icmp eq i32 %v157, 47
  br i1 %v158, label %label_185, label %label_186
label_159:                                                ; preds = %label_153, %label_184
  %v160 = load i32, i32* @chat
  %v161 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v160
  %v162 = load i32, i32* %v161
  %v163 = icmp eq i32 %v162, 42
  br i1 %v163, label %label_164, label %label_168
label_164:                                                ; preds = %label_159, %label_168, %label_173, %label_178
  %v165 = call i32 @find()
  %v166 = icmp eq i32 %v165, 0
  br i1 %v166, label %label_183, label %label_184
label_167:                                                ; preds = %label_178, %label_183
  call void @chapush(i32 42)
  br label %label_154
label_168:                                                ; preds = %label_159
  %v169 = load i32, i32* @chat
  %v170 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v169
  %v171 = load i32, i32* %v170
  %v172 = icmp eq i32 %v171, 47
  br i1 %v172, label %label_164, label %label_173
label_173:                                                ; preds = %label_168
  %v174 = load i32, i32* @chat
  %v175 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v174
  %v176 = load i32, i32* %v175
  %v177 = icmp eq i32 %v176, 37
  br i1 %v177, label %label_164, label %label_178
label_178:                                                ; preds = %label_173
  %v179 = load i32, i32* @chat
  %v180 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v179
  %v181 = load i32, i32* %v180
  %v182 = icmp eq i32 %v181, 94
  br i1 %v182, label %label_164, label %label_167
label_183:                                                ; preds = %label_164
  br label %label_167
label_184:                                                ; preds = %label_164
  br label %label_159
label_185:                                                ; preds = %label_154
  br label %label_191
label_186:                                                ; preds = %label_154, %label_199
  %v187 = load i32, i32* @i
  %v188 = getelementptr [10000 x i32], [10000 x i32]* @get, i32 0, i32 %v187
  %v189 = load i32, i32* %v188
  %v190 = icmp eq i32 %v189, 37
  br i1 %v190, label %label_217, label %label_218
label_191:                                                ; preds = %label_185, %label_216
  %v192 = load i32, i32* @chat
  %v193 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v192
  %v194 = load i32, i32* %v193
  %v195 = icmp eq i32 %v194, 42
  br i1 %v195, label %label_196, label %label_200
label_196:                                                ; preds = %label_191, %label_200, %label_205, %label_210
  %v197 = call i32 @find()
  %v198 = icmp eq i32 %v197, 0
  br i1 %v198, label %label_215, label %label_216
label_199:                                                ; preds = %label_210, %label_215
  call void @chapush(i32 47)
  br label %label_186
label_200:                                                ; preds = %label_191
  %v201 = load i32, i32* @chat
  %v202 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v201
  %v203 = load i32, i32* %v202
  %v204 = icmp eq i32 %v203, 47
  br i1 %v204, label %label_196, label %label_205
label_205:                                                ; preds = %label_200
  %v206 = load i32, i32* @chat
  %v207 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v206
  %v208 = load i32, i32* %v207
  %v209 = icmp eq i32 %v208, 37
  br i1 %v209, label %label_196, label %label_210
label_210:                                                ; preds = %label_205
  %v211 = load i32, i32* @chat
  %v212 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v211
  %v213 = load i32, i32* %v212
  %v214 = icmp eq i32 %v213, 94
  br i1 %v214, label %label_196, label %label_199
label_215:                                                ; preds = %label_196
  br label %label_199
label_216:                                                ; preds = %label_196
  br label %label_191
label_217:                                                ; preds = %label_186
  br label %label_223
label_218:                                                ; preds = %label_186, %label_231
  %v219 = load i32, i32* @ii
  %v220 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v219
  store i32 32, i32* %v220
  %v221 = load i32, i32* @ii
  %v222 = add i32 %v221, 1
  store i32 %v222, i32* @ii
  br label %label_33
label_223:                                                ; preds = %label_217, %label_248
  %v224 = load i32, i32* @chat
  %v225 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v224
  %v226 = load i32, i32* %v225
  %v227 = icmp eq i32 %v226, 42
  br i1 %v227, label %label_228, label %label_232
label_228:                                                ; preds = %label_223, %label_232, %label_237, %label_242
  %v229 = call i32 @find()
  %v230 = icmp eq i32 %v229, 0
  br i1 %v230, label %label_247, label %label_248
label_231:                                                ; preds = %label_242, %label_247
  call void @chapush(i32 37)
  br label %label_218
label_232:                                                ; preds = %label_223
  %v233 = load i32, i32* @chat
  %v234 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v233
  %v235 = load i32, i32* %v234
  %v236 = icmp eq i32 %v235, 47
  br i1 %v236, label %label_228, label %label_237
label_237:                                                ; preds = %label_232
  %v238 = load i32, i32* @chat
  %v239 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v238
  %v240 = load i32, i32* %v239
  %v241 = icmp eq i32 %v240, 37
  br i1 %v241, label %label_228, label %label_242
label_242:                                                ; preds = %label_237
  %v243 = load i32, i32* @chat
  %v244 = getelementptr [10000 x i32], [10000 x i32]* @chas, i32 0, i32 %v243
  %v245 = load i32, i32* %v244
  %v246 = icmp eq i32 %v245, 94
  br i1 %v246, label %label_228, label %label_231
label_247:                                                ; preds = %label_228
  br label %label_231
label_248:                                                ; preds = %label_228
  br label %label_223
label_249:                                                ; preds = %label_19, %label_252
  %v250 = load i32, i32* @chat
  %v251 = icmp sgt i32 %v250, 0
  br i1 %v251, label %label_252, label %label_262
label_252:                                                ; preds = %label_249
  %v253 = call i32 @chapop()
  store i32 %v253, i32* %v4
  %v254 = load i32, i32* @ii
  %v255 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v254
  store i32 32, i32* %v255
  %v256 = load i32, i32* @ii
  %v257 = add i32 %v256, 1
  %v258 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v257
  %v259 = load i32, i32* %v4
  store i32 %v259, i32* %v258
  %v260 = load i32, i32* @ii
  %v261 = add i32 %v260, 2
  store i32 %v261, i32* @ii
  br label %label_249
label_262:                                                ; preds = %label_249
  %v263 = load i32, i32* @ii
  %v264 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v263
  store i32 64, i32* %v264
  store i32 1, i32* @i
  br label %label_265
label_265:                                                ; preds = %label_262, %label_290
  %v266 = load i32, i32* @i
  %v267 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v266
  %v268 = load i32, i32* %v267
  %v269 = icmp ne i32 %v268, 64
  br i1 %v269, label %label_270, label %label_275
label_270:                                                ; preds = %label_265
  %v271 = load i32, i32* @i
  %v272 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v271
  %v273 = load i32, i32* %v272
  %v274 = icmp eq i32 %v273, 43
  br i1 %v274, label %label_278, label %label_293
label_275:                                                ; preds = %label_265
  %v276 = getelementptr [10000 x i32], [10000 x i32]* @ints, i32 0, i32 1
  %v277 = load i32, i32* %v276
  call void @putint(i32 %v277)
  store i32 0, i32* %v0
  br label %label_ret
label_278:                                                ; preds = %label_270, %label_293, %label_298, %label_303, %label_308, %label_313
  %v279 = call i32 @intpop()
  store i32 %v279, i32* %v5
  %v280 = call i32 @intpop()
  store i32 %v280, i32* %v6
  %v281 = load i32, i32* @i
  %v282 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v281
  %v283 = load i32, i32* %v282
  %v284 = icmp eq i32 %v283, 43
  br i1 %v284, label %label_318, label %label_322
label_285:                                                ; preds = %label_313
  %v286 = load i32, i32* @i
  %v287 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v286
  %v288 = load i32, i32* %v287
  %v289 = icmp ne i32 %v288, 32
  br i1 %v289, label %label_369, label %label_374
label_290:                                                ; preds = %label_367, %label_374
  %v291 = load i32, i32* @i
  %v292 = add i32 %v291, 1
  store i32 %v292, i32* @i
  br label %label_265
label_293:                                                ; preds = %label_270
  %v294 = load i32, i32* @i
  %v295 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v294
  %v296 = load i32, i32* %v295
  %v297 = icmp eq i32 %v296, 45
  br i1 %v297, label %label_278, label %label_298
label_298:                                                ; preds = %label_293
  %v299 = load i32, i32* @i
  %v300 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v299
  %v301 = load i32, i32* %v300
  %v302 = icmp eq i32 %v301, 42
  br i1 %v302, label %label_278, label %label_303
label_303:                                                ; preds = %label_298
  %v304 = load i32, i32* @i
  %v305 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v304
  %v306 = load i32, i32* %v305
  %v307 = icmp eq i32 %v306, 47
  br i1 %v307, label %label_278, label %label_308
label_308:                                                ; preds = %label_303
  %v309 = load i32, i32* @i
  %v310 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v309
  %v311 = load i32, i32* %v310
  %v312 = icmp eq i32 %v311, 37
  br i1 %v312, label %label_278, label %label_313
label_313:                                                ; preds = %label_308
  %v314 = load i32, i32* @i
  %v315 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v314
  %v316 = load i32, i32* %v315
  %v317 = icmp eq i32 %v316, 94
  br i1 %v317, label %label_278, label %label_285
label_318:                                                ; preds = %label_278
  %v319 = load i32, i32* %v5
  %v320 = load i32, i32* %v6
  %v321 = add i32 %v319, %v320
  store i32 %v321, i32* %v7
  br label %label_322
label_322:                                                ; preds = %label_278, %label_318
  %v323 = load i32, i32* @i
  %v324 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v323
  %v325 = load i32, i32* %v324
  %v326 = icmp eq i32 %v325, 45
  br i1 %v326, label %label_327, label %label_331
label_327:                                                ; preds = %label_322
  %v328 = load i32, i32* %v6
  %v329 = load i32, i32* %v5
  %v330 = sub i32 %v328, %v329
  store i32 %v330, i32* %v7
  br label %label_331
label_331:                                                ; preds = %label_322, %label_327
  %v332 = load i32, i32* @i
  %v333 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v332
  %v334 = load i32, i32* %v333
  %v335 = icmp eq i32 %v334, 42
  br i1 %v335, label %label_336, label %label_340
label_336:                                                ; preds = %label_331
  %v337 = load i32, i32* %v5
  %v338 = load i32, i32* %v6
  %v339 = mul i32 %v337, %v338
  store i32 %v339, i32* %v7
  br label %label_340
label_340:                                                ; preds = %label_331, %label_336
  %v341 = load i32, i32* @i
  %v342 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v341
  %v343 = load i32, i32* %v342
  %v344 = icmp eq i32 %v343, 47
  br i1 %v344, label %label_345, label %label_349
label_345:                                                ; preds = %label_340
  %v346 = load i32, i32* %v6
  %v347 = load i32, i32* %v5
  %v348 = sdiv i32 %v346, %v347
  store i32 %v348, i32* %v7
  br label %label_349
label_349:                                                ; preds = %label_340, %label_345
  %v350 = load i32, i32* @i
  %v351 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v350
  %v352 = load i32, i32* %v351
  %v353 = icmp eq i32 %v352, 37
  br i1 %v353, label %label_354, label %label_358
label_354:                                                ; preds = %label_349
  %v355 = load i32, i32* %v6
  %v356 = load i32, i32* %v5
  %v357 = srem i32 %v355, %v356
  store i32 %v357, i32* %v7
  br label %label_358
label_358:                                                ; preds = %label_349, %label_354
  %v359 = load i32, i32* @i
  %v360 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v359
  %v361 = load i32, i32* %v360
  %v362 = icmp eq i32 %v361, 94
  br i1 %v362, label %label_363, label %label_367
label_363:                                                ; preds = %label_358
  %v364 = load i32, i32* %v6
  %v365 = load i32, i32* %v5
  %v366 = call i32 @power(i32 %v364, i32 %v365)
  store i32 %v366, i32* %v7
  br label %label_367
label_367:                                                ; preds = %label_358, %label_363
  %v368 = load i32, i32* %v7
  call void @intpush(i32 %v368)
  br label %label_290
label_369:                                                ; preds = %label_285
  %v370 = load i32, i32* @i
  %v371 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v370
  %v372 = load i32, i32* %v371
  %v373 = sub i32 %v372, 48
  call void @intpush(i32 %v373)
  store i32 1, i32* @ii
  br label %label_375
label_374:                                                ; preds = %label_285, %label_391
  br label %label_290
label_375:                                                ; preds = %label_369, %label_382
  %v376 = load i32, i32* @i
  %v377 = load i32, i32* @ii
  %v378 = add i32 %v376, %v377
  %v379 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v378
  %v380 = load i32, i32* %v379
  %v381 = icmp ne i32 %v380, 32
  br i1 %v381, label %label_382, label %label_391
label_382:                                                ; preds = %label_375
  %v383 = load i32, i32* @i
  %v384 = load i32, i32* @ii
  %v385 = add i32 %v383, %v384
  %v386 = getelementptr [10000 x i32], [10000 x i32]* @get2, i32 0, i32 %v385
  %v387 = load i32, i32* %v386
  %v388 = sub i32 %v387, 48
  call void @intadd(i32 %v388)
  %v389 = load i32, i32* @ii
  %v390 = add i32 %v389, 1
  store i32 %v390, i32* @ii
  br label %label_375
label_391:                                                ; preds = %label_375
  %v392 = load i32, i32* @i
  %v393 = load i32, i32* @ii
  %v394 = add i32 %v392, %v393
  %v395 = sub i32 %v394, 1
  store i32 %v395, i32* @i
  br label %label_374
}

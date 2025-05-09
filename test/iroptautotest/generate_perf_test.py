#!/usr/bin/python3
import random
import string
import re
import copy
import math

def generate_var_name():
    """生成随机变量名"""
    return 'var_' + ''.join(random.choice(string.ascii_lowercase) for _ in range(5))

def generate_const():
    """生成随机整数常量"""
    return random.randint(-100, 100)

def generate_float_const():
    """生成随机浮点常量"""
    # 生成-100.0到100.0之间的随机浮点数，保留4位小数
    return round(random.uniform(-100.0, 100.0), 4)

def is_safe_expression(expr):
    """检查表达式是否包含连续的++或--"""
    return not re.search(r'\+\+|--', expr)

def make_safe_expression(expr):
    """修复表达式中的连续++或--"""
    # 用空格分隔连续的++或--
    expr = re.sub(r'\+\+', '+ +', expr)
    expr = re.sub(r'--', '- -', expr)
    return expr

def is_literal_constant(expr):
    """检查表达式是否为字面常量"""
    # 简单判断：如果是数字或带负号的数字则为常量
    return re.match(r'^-?\d+(\.\d+)?$', str(expr).strip())

def generate_global_var_decl(global_scope=None, use_float=False):
    """生成全局变量声明"""
    if global_scope is None:
        global_scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    var = generate_var_name()
    if use_float:
        value = generate_float_const()
    else:
        value = generate_const()
  
    if random.random() < 0.3:
        # 全局常量
        global_scope["const_vars"].append(var)
        if use_float:
            global_scope["float_vars"].append(var)
            return f"const float {var} = {value};"
        else:
            global_scope["vars"].append(var)
            return f"const int {var} = {value};"
    else:
        # 全局变量
        if use_float:
            global_scope["float_vars"].append(var)
            if random.random() < 0.5:
                return f"float {var} = {value};"
            else:
                return f"float {var};"
        else:
            global_scope["vars"].append(var)
            if random.random() < 0.5:
                return f"int {var} = {value};"
            else:
                return f"int {var};"

# def generate_global_array_decl(global_scope=None, use_float=True, size=None):
#     """生成全局数组声明"""
#     if global_scope is None:
#         global_scope = {"vars": [], "float_vars": [], "const_vars": []}
    
#     if size is None:
#         size = random.randint(10, 50)
    
#     var = generate_var_name()
#     if use_float:
#         global_scope["float_vars"].append(var)
#         type_name = "float"
#         elements = [str(generate_float_const()) for _ in range(min(size, 10))]  # 只初始化部分元素以节省空间
#     else:
#         global_scope["vars"].append(var)
#         type_name = "int"
#         elements = [str(generate_const()) for _ in range(min(size, 10))]
    
#     init_list = ", ".join(elements)
    
#     # 如果size大于初始化元素数量，则使用不完全初始化
#     if size > len(elements):
#         return f"{type_name} {var}[{size}] = {{{init_list}}};"
#     else:
#         return f"{type_name} {var}[{size}] = {{{init_list}}};"

def generate_const_decl(scope=None, use_float=False):
    """生成常量声明"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    var = generate_var_name()
    if use_float:
        value = generate_float_const()
        scope["float_vars"].append(var)
        scope["const_vars"].append(var)  # 添加到常量变量列表
        return f"const float {var} = {value};"
    else:
        value = generate_const()
        scope["vars"].append(var)
        scope["const_vars"].append(var)  # 添加到常量变量列表
        return f"const int {var} = {value};"
    
def generate_unary_exp(depth=0, scope=None, use_float=False):
    """生成一元表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 基础表达式或一元操作
    if depth >= 3 or random.random() < 0.7:
        # 基础表达式
        if random.random() < 0.8:
            # 变量或常量
            if use_float:
                if scope["float_vars"] and random.random() < 0.7:
                    return random.choice(scope["float_vars"])
                else:
                    return str(generate_float_const())
            else:
                if scope["vars"] and random.random() < 0.7:
                    return random.choice(scope["vars"])
                else:
                    return str(generate_const())
        else:
            # 括号表达式
            return f"({generate_add_exp(depth, scope, use_float)})"
    else:
        # 一元操作
        op = random.choice(['+', '-'])
        expr = generate_unary_exp(depth + 1, scope, use_float)
        result = f"{op}{expr}"
      
        # 检查并修复可能的连续运算符
        if not is_safe_expression(result):
            if expr.startswith('+') or expr.startswith('-'):
                result = f"{op} {expr}"
            else:
                result = make_safe_expression(result)
      
        return result

def generate_non_zero_expr(depth=0, scope=None, use_float=False):
    """生成一个保证非零的表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 生成保证非零的表达式的策略:
    # 1. 使用非零常量
    # 2. 使用绝对值表达式：a * a + 1 (永远>=1)
    # 3. 使用计算结果一定为奇数的表达式：2 * expr + 1 (永远是奇数，不为0)
  
    strategy = random.randint(1, 3)
  
    if strategy == 1:
        # 使用非零常量
        if use_float:
            non_zero = random.uniform(0.1, 10.0)
            return str(round(non_zero, 4))
        else:
            non_zero = random.randint(1, 10)
            return str(non_zero)
    elif strategy == 2 or use_float:
        # 使用平方加一表达式：变量平方加1永远大于0，浮点数和整数都适用，use_float为true时，一定触发，避免浮点数使用策略3
        if use_float and scope["float_vars"]:
            var = random.choice(scope["float_vars"])
            return f"({var} * {var} + 1.0)"
        elif scope["vars"]:
            var = random.choice(scope["vars"])
            if use_float:
                return f"({var} * {var} + 1.0)"
            else:
                return f"({var} * {var} + 1)"
        else:
            # 如果没有变量，使用常量
            if use_float:
                return str(round(random.uniform(0.1, 10.0), 4))
            else:
                return str(random.randint(1, 10))
    else:
        # 使用奇数表达式：2*expr+1永远是奇数，不为0，浮点数不适用
        expr = generate_unary_exp(depth, scope, use_float)

        return f"(2 * {expr} + 1)"
        # if use_float:
        #     return f"(2.0 * {expr} + 1.0)"
        # else:
        #     return f"(2 * {expr} + 1)"

def generate_mul_exp(depth=0, scope=None, use_float=False):
    """生成乘除模表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 基础表达式
    # if use_float and random.random() < 0.2:
    #     # 有一定几率使用数学函数
    #     result = generate_math_function(depth, scope)
    # else:

    # 一元表达式
    result = generate_unary_exp(depth, scope, use_float)
  
    # 随机添加乘除模操作
    ops_count = random.randint(0, 3 if depth < 2 else 1)  # 增加运算量
    for _ in range(ops_count):
        if use_float:
            op = random.choice(['*', '/'])  # 浮点不支持模运算
        else:
            op = random.choice(['*', '/', '%'])
      
        # 如果是除法或取模，确保右操作数不为0
        if op in ['/', '%']:
            # 使用专门的函数生成非零表达式
            # 对于%运算符，确保两侧都是整数表达式
            if op == '%':
                right = generate_non_zero_expr(depth + 1, scope, False)  # 强制使用整数

                # 确保右操作数是整数
                temp_right = right
                right = f"(int)({temp_right})"
                # 确保左操作数也是整数
                # if use_float:
                    # 如果当前是浮点模式，需要将结果转换为整型表达式
                    # 先保存当前结果

                # 将左操作数强制转换成整数    
                temp_result = result
                # 添加类型转换，确保是整数
                result = f"(int)({temp_result})"
                temp_result = f"{result} {op} {right}"
                # else:
                    # temp_result = f"{result} {op} {right}"
            else:
                right = generate_non_zero_expr(depth + 1, scope, use_float)
                temp_result = f"{result} {op} {right}"
        else:
            # 乘法不需要特殊处理
            right = generate_unary_exp(depth + 1, scope, use_float)
            temp_result = f"{result} {op} {right}"
      
        if is_safe_expression(temp_result):
            result = temp_result
        else:
            result = make_safe_expression(temp_result)
  
    return result

def generate_add_exp(depth=0, scope=None, use_float=False):
    """生成加减表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 乘除模表达式
    result = generate_mul_exp(depth, scope, use_float)
  
    # 随机添加加减操作
    ops_count = random.randint(0, 3 if depth < 2 else 1)  # 增加运算量
    for _ in range(ops_count):
        op = random.choice(['+', '-'])
        right = generate_mul_exp(depth + 1, scope, use_float)
      
        # 检查并确保不会生成++或--
        temp_result = f"{result} {op} {right}"
        if is_safe_expression(temp_result):
            result = temp_result
        else:
            # 如果右操作数以op开头，添加括号避免连续运算符
            if right.lstrip().startswith(op):
                result = f"{result} {op} ({right})"
            else:
                result = make_safe_expression(temp_result)
  
    return result

def generate_rel_exp(depth=0, scope=None, use_float=False):
    """生成关系表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 加减表达式
    result = generate_add_exp(depth, scope, use_float)
  
    # 随机添加关系运算符
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        op = random.choice(['<', '>', '<=', '>='])
        right = generate_add_exp(depth + 1, scope, use_float)
        result = f"{result} {op} {right}"
  
    return result

def generate_eq_exp(depth=0, scope=None, use_float=False):
    """生成相等性表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 关系表达式
    result = generate_rel_exp(depth, scope, use_float)
  
    # 随机添加相等性运算符
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        op = random.choice(['==', '!='])
        right = generate_rel_exp(depth + 1, scope, use_float)
        result = f"{result} {op} {right}"
  
    return result

def generate_land_exp(depth=0, scope=None, use_float=False):
    """生成逻辑与表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 相等性表达式
    result = generate_eq_exp(depth, scope, use_float)
  
    # 随机添加逻辑与
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        right = generate_eq_exp(depth + 1, scope, use_float)
        result = f"{result} && {right}"
  
    return result

def generate_lor_exp(depth=0, scope=None, use_float=False):
    """生成逻辑或表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 逻辑与表达式
    result = generate_land_exp(depth, scope, use_float)
  
    # 随机添加逻辑或
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        right = generate_land_exp(depth + 1, scope, use_float)
        result = f"{result} || {right}"
  
    return result

def generate_cond(scope=None, use_float=False):
    """生成条件表达式"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 直接使用逻辑或表达式作为条件
    return generate_lor_exp(0, scope, use_float)

def generate_var_decl(scope=None, use_float=False):
    """生成变量声明"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    var = generate_var_name()
  
    # 一定带初始化的变量声明，避免局部变量未初始化导致无法进行有效的测试
    expr = generate_add_exp(0, scope, use_float)
    if use_float:
        scope["float_vars"].append(var)
        return f"float {var} = {expr};"
    else:
        scope["vars"].append(var)
        return f"int {var} = {expr};"

# def generate_float_array_decl(scope=None, size=None):
#     """生成浮点数组声明"""
#     if scope is None:
#         scope = {"vars": [], "float_vars": [], "const_vars": []}
    
#     if size is None:
#         size = random.randint(5, 20)
    
#     var = generate_var_name()
#     scope["float_vars"].append(var)
    
#     # 生成带初始化的数组
#     elements = [str(generate_float_const()) for _ in range(size)]
#     init_list = ", ".join(elements)
    
#     return f"float {var}[{size}] = {{{init_list}}};"

def generate_stmt(depth=0, scope=None, needs_return_value=False, use_float=False):
    """生成随机语句，如果needs_return_value为True，则生成带返回值的return语句"""
    if scope is None:
        scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 在深度过大时返回简单语句
    if depth >= 3:
        vars_list = scope["float_vars"] if use_float else scope["vars"]
        if vars_list:
            # 如果需要返回语句且深度较大，直接生成返回语句
            if needs_return_value:
                expr = generate_add_exp(0, scope, use_float)
                return f"return {expr};"
          
            # 否则生成赋值语句
            non_const_vars = [v for v in vars_list if v not in scope["const_vars"]]
            if non_const_vars:
                var = random.choice(non_const_vars)
                expr = generate_add_exp(0, scope, use_float)
                return f"{var} = {expr};"
            else:
                return ";"
        elif needs_return_value:
            # 如果需要返回值但没有变量，返回常量
            if use_float:
                return f"return {generate_float_const()};"
            else:
                return f"return {generate_const()};"
        return ";"
  
    # 如果需要带返回值的return语句，增加return的权重
    if needs_return_value:
        types = ['assign', 'if', 'while', 'block', 'return', 'return']  # 增加return权重
    else:
        types = ['assign', 'if', 'while', 'block', 'return']
  
    stmt_type = random.choice(types)
  
    if stmt_type == 'assign':
        # 变量赋值
        vars_list = scope["float_vars"] if use_float else scope["vars"]
        if vars_list:
            # 挑选非常量变量进行赋值
            non_const_vars = [v for v in vars_list if v not in scope["const_vars"]]
            if non_const_vars:
                var = random.choice(non_const_vars)
                expr = generate_add_exp(0, scope, use_float)
                return f"{var} = {expr};"
            else:
                # 如果没有非常量变量，创建一个新变量
                var = generate_var_name()
                expr = generate_add_exp(0, scope, use_float)
                if use_float:
                    scope["float_vars"].append(var)
                    return f"float {var} = {expr};"
                else:
                    scope["vars"].append(var)
                    return f"int {var} = {expr};"
        else:
            var = generate_var_name()
            expr = generate_add_exp(0, scope, use_float)
            if use_float:
                scope["float_vars"].append(var)
                return f"float {var} = {expr};"
            else:
                scope["vars"].append(var)
                return f"int {var} = {expr};"
  
    elif stmt_type == 'if':
        # if语句
        cond = generate_cond(scope, use_float)
      
        # 创建then分支的作用域（继承当前作用域的变量）
        then_scope = copy.deepcopy(scope)
        then_stmt = generate_stmt(depth + 1, then_scope, needs_return_value, use_float)
      
        if random.random() < 0.5:
            # 带else - 创建else分支的作用域
            else_scope = copy.deepcopy(scope)
            else_stmt = generate_stmt(depth + 1, else_scope, needs_return_value, use_float)
            return f"if ({cond}) {{\n    {then_stmt}\n}} else {{\n    {else_stmt}\n}}"
        else:
            # 不带else
            return f"if ({cond}) {{\n    {then_stmt}\n}}"
  
    elif stmt_type == 'while':
        # while循环 - 循环体使用独立作用域
        var = generate_var_name()
        if use_float:
            scope["float_vars"].append(var) 
            scope["vars"].append(var)  # 同时添加到整数变量列表，便于条件判断
            init_val = "0.0"
        else:
            scope["vars"].append(var)
            init_val = "0"
            
        cond = generate_cond(scope, False)  # 条件使用整数更安全
        loop_scope = copy.deepcopy(scope)
        body = generate_stmt(depth + 1, loop_scope, False, use_float)
        
        # 添加一个break条件，防止死循环
        if use_float:
            limit_check = f"{var} = {var} + 0.1; if({var} > 100.0) break;"
        else:
            limit_check = f"{var} = {var} + 1; if({var} > 1000) break;"
        
        var_type = "float" if use_float else "int"
        return f"{var_type} {var} = {init_val};\n while ({cond}) {{\n    {body}\n    {limit_check}\n}}"
  
    elif stmt_type == 'block':
        # 语句块 - 使用独立作用域
        block_scope = copy.deepcopy(scope)
        stmts = []
      
        # 在块中声明一些新变量
        if random.random() < 0.5:
            var_count = random.randint(1, 2)
            for _ in range(var_count):
                if random.random() < 0.3:
                    stmts.append(generate_const_decl(block_scope, use_float))
                else:
                    stmts.append(generate_var_decl(block_scope, use_float))
      
        # 添加其他语句
        stmt_count = random.randint(1, 3)
        for i in range(stmt_count):
            # 块的最后一条语句可能需要返回值
            if i == stmt_count - 1 and needs_return_value and random.random() < 0.5:
                stmts.append(generate_stmt(depth + 1, block_scope, True, use_float))
            else:
                stmts.append(generate_stmt(depth + 1, block_scope, False, use_float))
      
        # 如果需要返回值且块中没有返回语句，添加一个
        if needs_return_value and not any("return " in stmt for stmt in stmts):
            expr = generate_add_exp(0, block_scope, use_float)
            stmts.append(f"return {expr};")
      
        return "{\n    " + "\n    ".join(stmts) + "\n}"
  
    elif stmt_type == 'return':
        # 返回语句
        if needs_return_value:
            # 需要返回值，确保有表达式
            expr = generate_add_exp(0, scope, use_float)
            return f"return {expr};"
        else:
            return ";"
    
    # elif stmt_type == 'perf_block':
    #     # 性能测试代码块 - 包含大量计算
    #     iterations = random.randint(1000, 5000)  # 迭代次数，增加计算量
    #     perf_code = generate_performance_code(scope, iterations, use_float)
    #     if needs_return_value:
    #         vars_list = scope["float_vars"] if use_float else scope["vars"]
    #         if vars_list:
    #             result_var = random.choice(vars_list)
    #             return f"{{\n    {perf_code}\n    return {result_var};\n}}"
    #         else:
    #             return f"{{\n    {perf_code}\n    return {generate_float_const() if use_float else generate_const()};\n}}"
    #     else:
    #         return f"{{\n    {perf_code}\n}}"


def generate_function(has_return=True, use_float=True):
    """生成随机函数"""
    func_name = 'func_' + ''.join(random.choice(string.ascii_lowercase) for _ in range(3))
  
    # 函数返回类型
    if has_return:
        func_type = "float" if use_float else "int"
    else:
        func_type = "void"
  
    # 函数作用域
    func_scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 函数体
    body_parts = []
  
    # 添加一些局部变量声明
    decl_count = random.randint(2, 5)  # 增加变量数量
    for _ in range(decl_count):
        if random.random() < 0.3:
            body_parts.append(generate_const_decl(func_scope, use_float))
        else:
            body_parts.append(generate_var_decl(func_scope, use_float))
            
    # 可能添加数组声明
    # if random.random() < 0.5:
    #     body_parts.append(generate_float_array_decl(func_scope))
    
    #  # 根据需要添加性能测试代码
    # if random.random() < 0.7:  # 增加性能测试的概率
    #     if random.random() < 0.5:
    #         # 矩阵运算
    #         matrix_size = random.randint(10, 20)
    #         body_parts.append(generate_matrix_ops(func_scope, matrix_size))
    #     else:
    #         # 迭代算法
    #         iterations = random.randint(100, 500)
    #         body_parts.append(generate_iterative_algorithm(func_scope, iterations))
  
    # 添加一些普通语句
    stmt_count = random.randint(3, 8)
    for _ in range(stmt_count):
        # 针对有返回值的函数，最后一条语句可能需要是返回语句
        if _ == stmt_count - 1 and has_return:
            body_parts.append(generate_stmt(0, func_scope, True, use_float))
        else:
            body_parts.append(generate_stmt(0, func_scope, False, use_float))
  
    # 确保末尾一定有return，防止ub
    if has_return:
        if use_float:
            expr = generate_add_exp(0, func_scope, True) if func_scope["float_vars"] else str(generate_float_const())
        else:
            expr = generate_add_exp(0, func_scope, False) if func_scope["vars"] else str(generate_const())
        body_parts.append(f"return {expr};")
    else:
        body_parts.append("return;")
  
    func_body = "\n    ".join(body_parts)
  
    return f"{func_type} {func_name}() {{\n    {func_body}\n}}"

# def check_modulo_operations(program):
#     """检查并修复所有模运算，确保操作数都是整数类型"""
#     lines = program.split('\n')
#     fixed_lines = []
    
#     for line in lines:
#         # 查找包含模运算的行
#         if '%' in line:
#             # 检查模运算的左右操作数
#             tokens = re.split(r'(\s*%\s*)', line)
#             for i in range(1, len(tokens), 2):
#                 if i+1 < len(tokens):
#                     # 左操作数是模运算符之前的部分
#                     left_expr = tokens[i-1].strip()
#                     # 右操作数是模运算符之后的部分
#                     right_expr = tokens[i+1].strip()
                    
#                     # 如果左操作数看起来可能是浮点数（含小数点或浮点常量后缀）
#                     if re.search(r'(\d+\.\d+|\.\d+|\d+\.|[fF])', left_expr):
#                         # 替换为类型转换
#                         tokens[i-1] = f"(int)({left_expr})"
                    
#                     # 如果右操作数看起来可能是浮点数
#                     if re.search(r'(\d+\.\d+|\.\d+|\d+\.|[fF])', right_expr):
#                         # 确保右操作数不是浮点数，如果是则转换为整数
#                         end_pos = 0
#                         for j, char in enumerate(right_expr):
#                             if char in '+-*/;,(){}[]':
#                                 end_pos = j
#                                 break
#                         if end_pos > 0:
#                             # 只转换模运算符右侧的直接操作数
#                             tokens[i+1] = f"(int)({right_expr[:end_pos]}){right_expr[end_pos:]}"
#                         else:
#                             tokens[i+1] = f"(int)({right_expr})"
            
#             # 重新组合行
#             fixed_line = ''.join(tokens)
#             fixed_lines.append(fixed_line)
#         else:
#             fixed_lines.append(line)
    
#     return '\n'.join(fixed_lines)


def generate_float_perf_program(num_funcs=3, include_globals=True):
    """生成包含浮点运算的性能测试程序"""
    program_parts = []
    
    # 添加必要的头文件
    # program_parts.append("#include <math.h>")
    # program_parts.append("#include <stdio.h>")
    # program_parts.append("#include <stdlib.h>")
    # program_parts.append("#include <time.h>")
    
    # 全局作用域
    global_scope = {"vars": [], "float_vars": [], "const_vars": []}
  
    # 添加全局变量声明
    if include_globals:
        global_count = random.randint(4, 10)  # 增加全局变量数量
        for _ in range(global_count):
            # 增加浮点变量的比例
            use_float = random.random() < 0.7
            program_parts.append(generate_global_var_decl(global_scope, use_float))
        
        # 添加全局数组
        # array_count = random.randint(1, 3)
        # for _ in range(array_count):
        #     use_float = random.random() < 0.7
        #     program_parts.append(generate_global_array_decl(global_scope, use_float))
  
    # 生成函数
    funcs = []
    for i in range(num_funcs):
        # 增加浮点函数的比例
        use_float = random.random() < 0.8
        has_return = True if i == num_funcs - 1 else random.random() < 0.7
        func = generate_function(has_return, use_float)
        funcs.append(func)
        program_parts.append(func)
  
    # 主函数
    main_body_parts = []
  
    # 主函数作用域（包含全局变量）
    main_scope = copy.deepcopy(global_scope)
    
    # # 添加计时代码
    # main_body_parts.append("clock_t start, end;")
    # main_body_parts.append("double cpu_time_used;")
    # main_body_parts.append("start = clock();")
  
    # 添加局部变量
    decl_count = random.randint(2, 5)
    for _ in range(decl_count):
        # 增加浮点变量
        use_float = random.random() < 0.7
        if random.random() < 0.3:
            main_body_parts.append(generate_const_decl(main_scope, use_float))
        else:
            main_body_parts.append(generate_var_decl(main_scope, use_float))
    
    # 添加数组
    # if random.random() < 0.7:
    #     main_body_parts.append(generate_float_array_decl(main_scope, random.randint(10, 50)))
  
    # 添加函数调用和其他语句
    for i in range(random.randint(5, 10)):  # 增加语句数量
        if i < len(funcs) and random.random() < 0.8:  # 增加函数调用的概率
            func_name = funcs[i].split()[1].split('(')[0]
            return_type = funcs[i].split()[0]
            
            if return_type != "void":
                var_type = return_type
                var = generate_var_name()
                
                if var_type == "float":
                    main_scope["float_vars"].append(var)
                else:
                    main_scope["vars"].append(var)
                    
                stmt = f"{var_type} {var} = {func_name}();"
            else:
                stmt = f"{func_name}();"
                
            main_body_parts.append(stmt)
        else:
            # 为主函数添加一些性能密集型代码
            # if random.random() < 0.6:
                # use_float = random.random() < 0.8
                # if random.random() < 0.5:
                #     matrix_size = random.randint(5, 15)
                #     main_body_parts.append(generate_matrix_ops(main_scope, matrix_size))
                # else:
                #     iterations = random.randint(50, 300)
                #     main_body_parts.append(generate_iterative_algorithm(main_scope, iterations))
            # else:
            # 随机stmt
            main_body_parts.append(generate_stmt(0, main_scope, False, random.random() < 0.8))
    
    # # 添加结束计时代码
    # main_body_parts.append("end = clock();")
    # main_body_parts.append("cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;")
    # main_body_parts.append("printf(\"执行时间: %f 秒\\n\", cpu_time_used);")
  
    # 确保主函数有返回语句
    result_expr = "0"
    if main_scope["float_vars"]:
        var = random.choice(main_scope["float_vars"])
        result_expr = f"(int)({var} * 100.0)"
    elif main_scope["vars"]:
        var = random.choice(main_scope["vars"])
        result_expr = var
        
    main_body_parts.append(f"return {result_expr};")
  
    main_body = "\n    ".join(main_body_parts)
    program_parts.append(f"int main() {{\n    {main_body}\n}}")
  
    # 最后验证整个程序，确保没有连续的++或--
    program = "\n\n".join(program_parts)
    # program = check_modulo_operations(program)  # 检查并修复模运算
    if not is_safe_expression(program):
        program = make_safe_expression(program)
  
    return program

def verify_no_increment_decrement(program):
    """验证程序中不包含++或--运算符"""
    if re.search(r'\+\+|--', program):
        print("警告：程序中包含++或--，进行修复...")
        program = make_safe_expression(program)
    return program

def check_and_fix_assignments(program):
    """检查并修复字面常量在赋值表达式左侧的情况"""
    lines = program.split('\n')
    fixed_lines = []
  
    for line in lines:
        # 检查赋值语句
        match = re.search(r'^\s*(\S+)\s*=\s*(.+);', line)
        if match:
            left = match.group(1).strip()
            right = match.group(2).strip()
          
            # 如果左侧是数字常量，修改为变量
            if is_literal_constant(left):
                # 替换为一个临时变量名
                temp_var = f"temp_{abs(hash(left)) % 1000}"
                fixed_line = line.replace(f"{left} =", f"/* 修复: 字面常量在左侧 */ int {temp_var} =")
                fixed_lines.append(fixed_line)
            else:
                fixed_lines.append(line)
        else:
            fixed_lines.append(line)
  
    return '\n'.join(fixed_lines)

def ensure_returns_have_values(program):
    """确保所有非void函数的return语句都有返回值"""
    lines = program.split('\n')
  
    # 找出所有函数定义
    functions = []
    current_func = {"name": None, "type": None, "start": -1, "end": -1, "is_void": False}
    in_function = False
    brace_level = 0
  
    for i, line in enumerate(lines):
        # 查找函数定义
        if not in_function:
            match = re.match(r'\s*(int|float|void)\s+(\w+)\s*\(\s*\)\s*{', line)
            if match:
                current_func["type"] = match.group(1)
                current_func["name"] = match.group(2)
                current_func["start"] = i
                current_func["is_void"] = (match.group(1) == "void")
                in_function = True
                brace_level = 1
        else:
            # 统计大括号，跟踪函数体范围
            brace_level += line.count('{') - line.count('}')
            if brace_level == 0:
                current_func["end"] = i
                functions.append(current_func.copy())
                current_func = {"name": None, "type": None, "start": -1, "end": -1, "is_void": False}
                in_function = False
  
    # 检查每个非void函数是否有带值的return语句
    for func in functions:
        if not func["is_void"]:
            func_body = lines[func["start"]:func["end"]+1]
            has_value_return = False
          
            for line in func_body:
                if re.search(r'\breturn\s+[^;]+;', line):
                    has_value_return = True
                    break
          
            # 如果没有带值的return，添加一个
            if not has_value_return:
                # 在函数结束前添加return语句
                return_value = "0" if func["type"] == "int" else "0.0"
                lines[func["end"]] = f"    return {return_value};\n{lines[func['end']]}"
  
    return '\n'.join(lines)


def main():
    # 生成浮点运算性能测试用例
    print("生成浮点运算性能测试用例...")
    
    # 生成随机测试用例
    program = generate_float_perf_program(num_funcs=5)  # 增加函数数量
    program = verify_no_increment_decrement(program)
    program = check_and_fix_assignments(program)
    program = ensure_returns_have_values(program)
    
    with open('sysy_float_perf_test.c', 'w') as f:
        f.write("// 自动生成的浮点运算性能测试用例\n")
        f.write("// 包含大量浮点运算，适用于性能测试\n")
        f.write("// 确保无++或--运算符，避免GCC解释为自增/自减\n")
        f.write("// 确保赋值表达式左侧无字面常量\n")
        f.write("// 确保所有非void函数都有带返回值的return语句\n")
        f.write("// 确保模运算(%)操作数都是整数\n\n")
        f.write(program)
    
    print("浮点运算性能测试用例已生成为sysy_float_perf_test.c")
    
    # # 生成矩阵乘法测试用例
    # matrix_program = generate_matrix_multiplication_test()
    # with open('matrix_multiplication_test.c', 'w') as f:
    #     f.write("// 矩阵乘法性能测试用例\n")
    #     f.write(matrix_program)
    
    # print("矩阵乘法性能测试用例已生成为matrix_multiplication_test.c")
    
    # # 生成迭代计算测试用例
    # iterative_program = generate_iterative_computation_test()
    # with open('iterative_computation_test.c', 'w') as f:
    #     f.write("// 迭代计算性能测试用例\n")
    #     f.write(iterative_program)
    
    # print("迭代计算性能测试用例已生成为iterative_computation_test.c")

if __name__ == "__main__":
    main()
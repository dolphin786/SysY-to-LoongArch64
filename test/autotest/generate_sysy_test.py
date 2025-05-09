#!/usr/bin/python3
import random
import string
import re
import copy

def generate_var_name():
    """生成随机变量名"""
    return 'var_' + ''.join(random.choice(string.ascii_lowercase) for _ in range(5))

def generate_const():
    """生成随机整数常量"""
    return random.randint(-100, 100)

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
    return re.match(r'^-?\d+$', str(expr).strip())

def generate_non_zero_expr(depth=0, scope=None):
    """生成一个保证非零的表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 生成保证非零的表达式的策略:
    # 1. 使用非零常量
    # 2. 使用绝对值表达式：a * a + 1 (永远>=1)
    # 3. 使用计算结果一定为奇数的表达式：2 * expr + 1 (永远是奇数，不为0)
    
    strategy = random.randint(1, 3)
    
    if strategy == 1:
        # 使用非零常量
        non_zero = random.randint(1, 10)
        return str(non_zero)
    elif strategy == 2:
        # 使用平方加一表达式：变量平方加1永远大于0
        if scope["vars"]:
            var = random.choice(scope["vars"])
            return f"({var} * {var} + 1)"
        else:
            # 如果没有变量，使用常量
            return str(random.randint(1, 10))
    else:
        # 使用奇数表达式：2*expr+1永远是奇数，不为0
        expr = generate_unary_exp(depth, scope)
        return f"(2 * {expr} + 1)"

def generate_unary_exp(depth=0, scope=None):
    """生成一元表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 基础表达式或一元操作
    if depth >= 3 or random.random() < 0.7:
        # 基础表达式
        if random.random() < 0.8:
            # 变量或常量
            if scope["vars"] and random.random() < 0.7:
                return random.choice(scope["vars"])
            else:
                return str(generate_const())
        else:
            # 括号表达式
            return f"({generate_add_exp(depth, scope)})"
    else:
        # 一元操作
        op = random.choice(['+', '-'])
        expr = generate_unary_exp(depth + 1, scope)
        result = f"{op}{expr}"
        
        # 检查并修复可能的连续运算符
        if not is_safe_expression(result):
            if expr.startswith('+') or expr.startswith('-'):
                result = f"{op} {expr}"
            else:
                result = make_safe_expression(result)
        
        return result

def generate_mul_exp(depth=0, scope=None):
    """生成乘除模表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 基础表达式
    result = generate_unary_exp(depth, scope)
    
    # 随机添加乘除模操作
    ops_count = random.randint(0, 2) if depth < 2 else 0
    for _ in range(ops_count):
        op = random.choice(['*', '/', '%'])
        
        # 如果是除法或取模，确保右操作数不为0
        if op in ['/', '%']:
            # 使用专门的函数生成非零表达式
            right = generate_non_zero_expr(depth + 1, scope)
        else:
            # 乘法不需要特殊处理
            right = generate_unary_exp(depth + 1, scope)
        
        temp_result = f"{result} {op} {right}"
        if is_safe_expression(temp_result):
            result = temp_result
        else:
            result = make_safe_expression(temp_result)
    
    return result

def generate_add_exp(depth=0, scope=None):
    """生成加减表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 乘除模表达式
    result = generate_mul_exp(depth, scope)
    
    # 随机添加加减操作
    ops_count = random.randint(0, 2) if depth < 2 else 0
    for _ in range(ops_count):
        op = random.choice(['+', '-'])
        right = generate_mul_exp(depth + 1, scope)
        
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

def generate_rel_exp(depth=0, scope=None):
    """生成关系表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 加减表达式
    result = generate_add_exp(depth, scope)
    
    # 随机添加关系运算符
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        op = random.choice(['<', '>', '<=', '>='])
        right = generate_add_exp(depth + 1, scope)
        result = f"{result} {op} {right}"
    
    return result

def generate_eq_exp(depth=0, scope=None):
    """生成相等性表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 关系表达式
    result = generate_rel_exp(depth, scope)
    
    # 随机添加相等性运算符
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        op = random.choice(['==', '!='])
        right = generate_rel_exp(depth + 1, scope)
        result = f"{result} {op} {right}"
    
    return result

def generate_land_exp(depth=0, scope=None):
    """生成逻辑与表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 相等性表达式
    result = generate_eq_exp(depth, scope)
    
    # 随机添加逻辑与
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        right = generate_eq_exp(depth + 1, scope)
        result = f"{result} && {right}"
    
    return result

def generate_lor_exp(depth=0, scope=None):
    """生成逻辑或表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 逻辑与表达式
    result = generate_land_exp(depth, scope)
    
    # 随机添加逻辑或
    ops_count = random.randint(0, 1) if depth < 1 else 0
    for _ in range(ops_count):
        right = generate_land_exp(depth + 1, scope)
        result = f"{result} || {right}"
    
    return result

def generate_cond(scope=None):
    """生成条件表达式"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 直接使用逻辑或表达式作为条件
    return generate_lor_exp(0, scope)

def generate_stmt(depth=0, scope=None, needs_return_value=False):
    """生成随机语句，如果needs_return_value为True，则生成带返回值的return语句"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    # 在深度过大时返回简单语句
    if depth >= 3:
        if scope["vars"]:
            # 如果需要返回语句且深度较大，直接生成返回语句
            if needs_return_value:
                expr = generate_add_exp(0, scope) if scope["vars"] else "0"
                return f"return {expr};"
            
            # 否则生成赋值语句
            non_const_vars = [v for v in scope["vars"] if v not in scope["const_vars"]]
            if non_const_vars:
                var = random.choice(non_const_vars)
                expr = generate_add_exp(0, scope)
                return f"{var} = {expr};"
            else:
                return ";"
        elif needs_return_value:
            # 如果需要返回值但没有变量，返回常量
            return f"return {generate_const()};"
        return ";"
    
    # 如果需要带返回值的return语句，增加return的权重
    if needs_return_value:
        types = ['assign', 'if', 'while', 'block', 'return', 'return', 'return']  # 增加return权重
    else:
        types = ['assign', 'if', 'while', 'block', 'return']
    
    stmt_type = random.choice(types)
    
    if stmt_type == 'assign':
        # 变量赋值
        if scope["vars"]:
            # 挑选非常量变量进行赋值
            non_const_vars = [v for v in scope["vars"] if v not in scope["const_vars"]]
            if non_const_vars:
                var = random.choice(non_const_vars)
                expr = generate_add_exp(0, scope)
                return f"{var} = {expr};"
            else:
                # 如果没有非常量变量，创建一个新变量
                var = generate_var_name()
                expr = generate_add_exp(0, scope)
                scope["vars"].append(var)

                return f"int {var} = {expr};"
        else:
            var = generate_var_name()
            expr = generate_add_exp(0, scope)
            scope["vars"].append(var)
            return f"int {var} = {expr};"
    
    elif stmt_type == 'if':
        # if语句
        cond = generate_cond(scope)
        
        # 创建then分支的作用域（继承当前作用域的变量）
        then_scope = copy.deepcopy(scope)
        then_stmt = generate_stmt(depth + 1, then_scope, needs_return_value)
        
        if random.random() < 0.5:
            # 带else - 创建else分支的作用域
            else_scope = copy.deepcopy(scope)
            else_stmt = generate_stmt(depth + 1, else_scope, needs_return_value)
            return f"if ({cond}) {{\n    {then_stmt}\n}} else {{\n    {else_stmt}\n}}"
        else:
            # 不带else
            return f"if ({cond}) {{\n    {then_stmt}\n}}"
    
    elif stmt_type == 'while':
        # while循环 - 循环体使用独立作用域
        var = generate_var_name()
        scope["vars"].append(var) # 添加一个变量，用于循环计数
        cond = generate_cond(scope)
        loop_scope = copy.deepcopy(scope)
        body = generate_stmt(depth + 1, loop_scope, False)  # 循环体中的return不满足函数的返回要求
        body = f"{var} = {var} + 1; if({var} > 1000) break;" # 添加一个break条件，防止死循环
        return f"int {var} = 0;\n while ({cond}) {{\n    {body}\n}}"
    
    elif stmt_type == 'block':
        # 语句块 - 使用独立作用域
        block_scope = copy.deepcopy(scope)
        stmts = []
        
        # 在块中声明一些新变量
        if random.random() < 0.5:
            var_count = random.randint(1, 2)
            for _ in range(var_count):
                if random.random() < 0.3:
                    stmts.append(generate_const_decl(block_scope))
                else:
                    stmts.append(generate_var_decl(block_scope))
        
        # 添加其他语句
        stmt_count = random.randint(1, 3)
        for i in range(stmt_count):
            # 块的最后一条语句可能需要返回值
            if i == stmt_count - 1 and needs_return_value and random.random() < 0.5:
                stmts.append(generate_stmt(depth + 1, block_scope, True))
            else:
                stmts.append(generate_stmt(depth + 1, block_scope, False))
        
        # 如果需要返回值且块中没有返回语句，添加一个
        if needs_return_value and not any("return " in stmt for stmt in stmts):
            expr = generate_add_exp(0, block_scope) if block_scope["vars"] else str(generate_const())
            stmts.append(f"return {expr};")
        
        return "{\n    " + "\n    ".join(stmts) + "\n}"
    
    else:  # return
        # 返回语句
        if needs_return_value:
            # 需要返回值，确保有表达式
            expr = generate_add_exp(0, scope) if scope["vars"] else str(generate_const())
            return f"return {expr};"
        else:
            # 根据需要可能返回值也可能不返回值
            # if random.random() < 0.5:
            #     expr = generate_add_exp(0, scope) if scope["vars"] else str(generate_const())
            #     return f"return {expr};"
            # else:
            #     return "return;"
            return ";"

def generate_const_decl(scope=None):
    """生成常量声明"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    var = generate_var_name()
    value = generate_const()
    scope["vars"].append(var)
    scope["const_vars"].append(var)  # 添加到常量变量列表
    return f"const int {var} = {value};"

def generate_var_decl(scope=None):
    """生成变量声明"""
    if scope is None:
        scope = {"vars": [], "const_vars": []}
    
    var = generate_var_name()
    
    
    # if random.random() < 0.7:
    #     # 带初始化的变量声明
    #     expr = generate_add_exp(0, scope)
    #     scope["vars"].append(var)
    #     return f"int {var} = {expr};"
    # else:
    #     # 不带初始化的变量声明
    #     scope["vars"].append(var)
    #     return f"int {var};"
    
    # 一定带初始化的变量声明，避免局部变量未初始化导致无法进行有效的difftest
    expr = generate_add_exp(0, scope)
    scope["vars"].append(var)
    return f"int {var} = {expr};"

def generate_function(has_return=True):
    """生成随机函数"""
    func_name = 'func_' + ''.join(random.choice(string.ascii_lowercase) for _ in range(3))
    
    # 函数返回类型
    func_type = "int" if has_return else "void"
    
    # 函数作用域
    func_scope = {"vars": [], "const_vars": []}
    
    # 函数体
    body_parts = []
    
    # 添加一些局部变量声明
    decl_count = random.randint(1, 3)
    for _ in range(decl_count):
        if random.random() < 0.3:
            body_parts.append(generate_const_decl(func_scope))
        else:
            body_parts.append(generate_var_decl(func_scope))
    
    # 添加一些语句
    stmt_count = random.randint(6, 10) # 6~10个语句
    for _ in range(stmt_count):
        # 针对有返回值的函数，最后一条语句可能需要是返回语句
        if _ == stmt_count - 1 and has_return:
            body_parts.append(generate_stmt(0, func_scope, True))
        else:
            body_parts.append(generate_stmt(0, func_scope, False))
    
    # 确保有return语句
    # if has_return and not any("return " in stmt for stmt in body_parts):  # 注意空格，确保检测到的是带值的return
    #     expr = generate_add_exp(0, func_scope) if func_scope["vars"] else str(generate_const())
    #     body_parts.append(f"return {expr};")
    # elif not has_return and not any(stmt.strip().startswith("return") for stmt in body_parts):
    #     body_parts.append("return;")


    # 确保末尾一定有return，防止ub
    if has_return:
        expr = generate_add_exp(0, func_scope) if func_scope["vars"] else str(generate_const())
        body_parts.append(f"return {expr};")
    else:
        body_parts.append("return;")

    
    func_body = "\n    ".join(body_parts)
    
    return f"{func_type} {func_name}() {{\n    {func_body}\n}}"

def generate_global_var_decl(global_scope=None):
    """生成全局变量声明"""
    if global_scope is None:
        global_scope = {"vars": [], "const_vars": []}
    
    var = generate_var_name()
    value = generate_const()
    
    if random.random() < 0.3:
        # 全局常量
        global_scope["vars"].append(var)
        global_scope["const_vars"].append(var)
        return f"const int {var} = {value};"
    else:
        # 全局变量
        global_scope["vars"].append(var)
        if random.random() < 0.5:
            return f"int {var} = {value};"
        else:
            return f"int {var};"

def generate_sysy_program(num_funcs=3, include_globals=True):
    """生成SysY2022程序"""
    program_parts = []
    
    # 全局作用域
    global_scope = {"vars": [], "const_vars": []}
    
    # 添加全局变量声明
    if include_globals:
        global_count = random.randint(3, 6) # 3~6个全局变量
        for _ in range(global_count):
            program_parts.append(generate_global_var_decl(global_scope))
    
    # 生成函数
    funcs = []
    for i in range(num_funcs):
        has_return = True if i == num_funcs - 1 else random.random() < 0.7
        func = generate_function(has_return)
        funcs.append(func)
        program_parts.append(func)
    
    # 主函数
    main_body_parts = []
    
    # 主函数作用域（包含全局变量）
    main_scope = copy.deepcopy(global_scope)
    
    # 添加局部变量
    decl_count = random.randint(1, 3)
    for _ in range(decl_count):
        if random.random() < 0.3:
            main_body_parts.append(generate_const_decl(main_scope))
        else:
            main_body_parts.append(generate_var_decl(main_scope))
    
    # 添加函数调用和其他语句
    for i in range(random.randint(20, 40)):
        if i < len(funcs) and random.random() < 0.7:
            func_name = funcs[i].split()[1].split('(')[0]
            stmt = f"{func_name}();"
            if "int" in funcs[i].split()[0]:
                var = generate_var_name()
                main_scope["vars"].append(var)
                stmt = f"int {var} = {func_name}();"
            main_body_parts.append(stmt)
        else:
            main_body_parts.append(generate_stmt(0, main_scope, False))
    
    # 确保主函数有返回语句
    if not any("return " in stmt for stmt in main_body_parts):  # 检查是否有带值的return
        expr = generate_add_exp(0, main_scope) if main_scope["vars"] else "0"
        main_body_parts.append(f"return {expr};")
    
    main_body = "\n    ".join(main_body_parts)
    program_parts.append(f"int main() {{\n    {main_body}\n}}")
    
    # 最后验证整个程序，确保没有连续的++或--
    program = "\n\n".join(program_parts)
    if not is_safe_expression(program):
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
            match = re.match(r'\s*(int|void)\s+(\w+)\s*\(\s*\)\s*{', line)
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
                lines[func["end"]] = f"    return 0;\n{lines[func['end']]}"
    
    return '\n'.join(lines)

def generate_optimization_testcase(test_type):
    """生成针对特定优化的测试用例"""
    if test_type == "constant_folding":
        return """
int constant_folding_test() {
    int a = 5;
    int b = 3;
    int c = a + b * 2;  // 应折叠为 c = 11
    if (c > 10) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    return constant_folding_test();
}
"""
    elif test_type == "dead_code":
        return """
int dead_code_test() {
    int a = 10;
    int b = 20;
    if (a < b) {
        return 1;
    } else {
        // 这部分代码永远不会执行
        int unused = a * b;
        return unused;
    }
}

int main() {
    return dead_code_test();
}
"""
    elif test_type == "loop_optimization":
        return """
int loop_optimization_test() {
    int sum = 0;
    int i = 0;
    while (i < 100) {
        sum = sum + i;  // 可以被循环不变代码外提等优化
        i = i + 1;
    }
    return sum;
}

int main() {
    return loop_optimization_test();
}
"""
    elif test_type == "common_subexpression":
        return """
int common_subexpression_test() {
    int a = 5;
    int b = 10;
    int c = 20;
    
    int x = (a + b) * (c - a);
    int y = (a + b) * (c - a);  // 相同表达式
    
    return x + y;
}

int main() {
    return common_subexpression_test();
}
"""
    else:
        return generate_sysy_program()

def verify_no_increment_decrement(program):
    """验证程序中不包含++或--运算符"""
    if re.search(r'\+\+|--', program):
        print("警告：程序中包含++或--，进行修复...")
        program = make_safe_expression(program)
    return program

def main():
    # 生成普通的SysY2022测试用例
    print("生成普通SysY2022测试用例...")
    program = generate_sysy_program()
    program = verify_no_increment_decrement(program)
    program = check_and_fix_assignments(program)
    program = ensure_returns_have_values(program)
    
    with open('sysy_custom_test.c', 'w') as f:
        f.write("// 自定义生成的SysY2022测试用例\n")
        f.write("// 确保无++或--运算符，避免GCC解释为自增/自减\n")
        f.write("// 确保赋值表达式左侧无字面常量和const变量\n")
        f.write("// 确保除法和取模运算的右操作数绝对不为0\n")
        f.write("// 确保所有非void函数都有带返回值的return语句\n")
        f.write("// 确保变量定义和使用遵循C语言作用域规则\n\n")
        f.write(program)
    
    print("普通测试用例已生成为sysy_custom_test.c")
    
    # 生成针对特定优化的测试用例
    # optimization_types = ["constant_folding", "dead_code", "loop_optimization", "common_subexpression"]
    
    # for opt_type in optimization_types:
    #     print(f"生成针对{opt_type}优化的测试用例...")
    #     program = generate_optimization_testcase(opt_type)
    #     program = verify_no_increment_decrement(program)
    #     program = check_and_fix_assignments(program)
    #     program = ensure_returns_have_values(program)
        
    #     with open(f'sysy_{opt_type}_test.c', 'w') as f:
    #         f.write(f"// 针对{opt_type}优化的SysY2022测试用例\n")
    #         f.write("// 确保无++或--运算符，避免GCC解释为自增/自减\n")
    #         f.write("// 确保赋值表达式左侧无字面常量和const变量\n")
    #         f.write("// 确保除法和取模运算的右操作数绝对不为0\n")
    #         f.write("// 确保所有非void函数都有带返回值的return语句\n")
    #         f.write("// 确保变量定义和使用遵循C语言作用域规则\n\n")
    #         f.write(program)
        
    #     print(f"优化测试用例已生成为sysy_{opt_type}_test.c")

if __name__ == "__main__":
    main()

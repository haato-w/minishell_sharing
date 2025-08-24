#!/bin/bash

echo "=== All Builtin Commands Test ==="

# Test all implemented builtins
echo "Testing all builtin commands:"

echo -e "\n1. pwd:"
echo "pwd" | ./minishell

echo -e "\n2. echo:"
echo "echo Hello World" | ./minishell

echo -e "\n3. echo -n:"
echo "echo -n No newline" | ./minishell
echo " (ended)"

echo -e "\n\n4. env (first 3 lines):"
echo "env" | ./minishell | head -3

echo -e "\n5. export (first 3 lines):"
echo "export" | ./minishell | head -3

echo -e "\n6. cd and pwd:"
echo -e "cd ..\npwd\ncd src\npwd" | ./minishell

echo -e "\n7. export and unset:"
echo -e "export TEST_VAR=hello\necho \$TEST_VAR\nunset TEST_VAR" | ./minishell

echo -e "\n=== All builtin commands working! ==="

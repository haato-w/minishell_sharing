RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat << EOF | cc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat << EOF | cc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
  for (int i = 0; argv[i]; i++)
    printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cat << EOF | cc -xc -o exit42 -
#include <stdio.h>
int main() { return 42; }
EOF

print_desc() {
  echo -e $YELLOW"$1"$RESET
}

cleanup() {
  rm -f cmp out a.out print_args exit42 infinite_loop
}

assert() {
  COMMAND="$1"
  shift
  printf '%-30s:' "[$COMMAND]"
  # exit status
  echo -n -e "$COMMAND" | bash >cmp 2>&-
  expected=$?
  for arg in "$@"
  do
    mv "$arg" "$arg"".cmp"
  done
  echo -n -e "$COMMAND" | ./minishell >out 2>&-
  actual=$?
  for arg in "$@"
  do
    mv "$arg" "$arg"".out"
  done

  diff cmp out >/dev/null && echo -e -n " diff $OK" || echo -e -n "  diff $NG"

  if [ "$actual" = "$expected" ]; then
    echo -e -n " status $OK"
  else
    echo -e -n " status $NG, expected $expected but got $actual"
  fi
  for arg in "$@"
  do
    echo -n " [$arg]"
    diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
    rm -f "$arg"".cmp" "$arg"".out"
  done
  echo
}

# Empty line (EOF)
assert ''

# Absolute path commands without args
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

# Tokenize
## unquoted word
assert 'ls /'
assert 'echo hello  world '
assert 'nosuchfile\n\n'

## single quote
assert "./printf_args 'hello  world'  '42Tokyo'"
assert "echo  'hello  world'  '42Tokyo'"
assert "echo  '\"hello  world\"'  '42Tokyo'"

## double quote
assert './printf_args "hello  world"  "42Tokyo"'
assert 'echo  "hello  world"  "42Tokyo"'
assert "echo  \"'hello  world'\"  \"42Tokyo\""

## combination
assert "echo hello' world'"
assert "echo hello' world '\" 42Tokyo \""

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirected output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >> pwd.txt' 'pwd.txt'

## Here Document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
export EOF="eof"
assert 'cat <<$EOF \neof\n$EPF\nEOF'
assert 'cat <<"$EOF" \neof\n$EPF\nEOF'

# Pipe
assert 'cat Makefile | grep minishell'
assert 'cat | cat |ls\n\n'

# Expand
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER $PATH $TERM"'

# Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

# Signal handling
echo "int main() {while (1) ; }" | cc -xc -o infinite_loop -

## Signal to shell processes
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) & 
assert './infinite_loop' 2> /dev/null # Redirect stderr to supress signal terminated message

# Builtin
## exit
assert 'exit'
assert 'exit 42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'

## export
assert 'export | grep nosuch | sort'
assert 'export nosuch\n export | grep nosuch | sort'
assert 'export nosuch=fuga\n export | grep nosuch | sort'
assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
assert 'export [invalid]'
assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'

## unset
export hoge fuga=fuga
assert 'unset'
assert 'unset hoge'
assert 'unset fuga'
assert 'unset nosuch'
assert 'unset [invalid]'
assert 'unset hoge fuga'
assert 'unset hoge nosuch fuga'
assert 'unset fuga \n export | echo $fuga'
assert 'unset [invalid] fuga \n echo $fuga'

cleanup

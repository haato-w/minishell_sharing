assert() {
  printf '%-30s:' "\"$1\""

  echo -n -e "$1" | bash >cmp 2>&-
  expected=$?

  echo -n -e "$1" | ./minishell >out 2>&-
  actual=$?

  diff cmp out >/dev/null && echo -n ' . diff OK' || echo -n '  diff NG'

  if [ "$actual" = "$expected" ]; then
    echo -n ' . status OK'
  else
    echo -n "  status NG, expected $expected but got $actual"
  fi
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

rm cmp out

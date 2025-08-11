# To do
- [x] Implementing fundamental code
- [x] Implementing our original tests
- [x] Implementing buildin commands
  - [x] exit
  - [x] export
  - [x] unset
  - [x] env
  - [x] cd
  - [x] echo
  - [x] pwd
- [x] Replacing standard libs to our implementations
- [ ] Applying tests made by other people
- [x] Applying norm

### バグ修正
  - [x] Ctrl cを押した時に入力欄がクリーンにならない
  - [ ] `< Makefile | cat`の時にfd消し忘れ
  - [x] `| cat`のときのエラー文がおかしい
  - [x] PATHがない時はCurrent dirだけにある実行ファイルを探すべき
  - [x] catの入力待ち中でctrl+cするとで変な出力が出る
  - [x] SIGQUITの出力を直す
  - [x] ctrl+cを連続で入力すると出力が崩れる
  - [ ] 入力途中で ctrl+cすると表示崩れる？
  - [x] minishell exit 1 2 でexit できちゃってる。
  - [x] exit のエラー表示がおかしい
  - [x] ^C の表示 されていない、終了ステータスが０のまま
  - [x] 今いるディレクトリが他のbashから消された時に`cd ..`で戻れない
  - [x] cd の存在しないディレクトリのエラーメッセージがおかしい
  - [ ] cd問題　同じ原因の問題が２つ
    - [ ] cd . や cd .. などの相対パス
    - [ ] PWD を unset した後、cd による PWD更新が上手くいっていない。
  - [ ] カレントディレクトリが消えた時(他のターミナルからディレクトリを消す)
  - [ ] 環境変数'~'は未対応
  - [ ] ディレクトリに入ってからその権限をなくすと抜けれなくなる？

- [ ] 全体的にfd closeでwarning出る
  - 外部関数を実行するときに出る
- [ ] Still reachableが出る
  - readlineに由来するのであれば良い
  - 多分mapのfreeをしていない
- [ ] 演算子があってコマンドがないと変なバグになる
  - ft_strchrで出ている
  - < main.c
  - ls | < main.c | cat　（これは要相談）
	でバグる
- [x] OLDPWDが元のshellから引き継がれていない
- [x] SHLVLへの対応
- [x] cdのエラーメッセージもおかしい
- [ ] echo -na
  - だったら-naとだす　n以外の文字があったらオプションじゃなくなる
- [ ] long max以上の数字でexitするとerrorを出すべき

ディレクトリ消されても戻れるようにする or エラーをしっかり出す
	今はstatのエラーが出ている
	本家はOLDPWD、PWDとは別に今いるディレクトリを持っている
		対応しないのであればdefenceできるようにする

ファイルがない時の出力は"No such file or directory"に統一すべき？

_=ってなんだろう
_=が２つない？

atoi使ってしまってない？

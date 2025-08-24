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
- [x] `< Makefile | cat`の時にfd消し忘れ
- [x] Still reachableが出る
  - readlineに由来するのであれば良い
- [x] 演算子があってコマンドがないと変なバグになる
  - ft_strchrで出ている
  - < main.c
  - ls | < main.c | cat　（これは要相談）
	でバグる
- [x] `| cat`のときのエラー文がおかしい
- [x] PATHがない時はCurrent dirだけにある実行ファイルを探すべき
- [x] catの入力待ち中でctrl+cするとで変な出力が出る
- [x] SIGQUITの出力を直す
- [x] ctrl+cを連続で入力すると出力が崩れる
- [x] 入力途中で ctrl+cすると表示崩れる
- [x] minishell exit 1 2 でexit できちゃってる。
- [x] exit のエラー表示がおかしい
- [x] ^C の表示 されていない、終了ステータスが０のまま
- [x] 今いるディレクトリが他のbashから消された時に`cd ..`で戻れない
- [x] cd の存在しないディレクトリのエラーメッセージがおかしい
- [ ] cd問題　同じ原因の問題が２つ
	- [x] cd . や cd .. などの相対パス
	- [ ] PWD を unset した後、cd による PWD更新が上手くいっていない。
- [x] カレントディレクトリが消えた時(他のターミナルからディレクトリを消す)
- [x] 全体的にfd closeでwarning出る
  - 外部関数を実行するときに出る
- [x] OLDPWDが元のshellから引き継がれていない
- [x] SHLVLへの対応
- [x] cdのエラーメッセージもおかしい
- [x] echo -na
  - だったら-naとだす　n以外の文字があったらオプションじゃなくなる
- [ ] long max以上の数字でexitするとerrorを出すべき
- [x] make時にreadlineのwarning出る
- [x] atoi使ってしまってない？
- [x] LibftのMakefileでCFLAGSが使われていないのでは？
- [x] Makefileの中で＊を使っちゃっている
- [ ] グローバルの構造体を使わない
- [ ] SIGQUITのstatusが130で正しいのかどうか
- [ ] SIGQUITのエラーメッセージのCore dumpedはおかしい
- [ ] ft_strtolの実装をしたほうがいい （現状strcmpを使ってしまっているので、echo 0000000.....を入れると本家と挙動が違ってしまう）
- [ ] envのprintfで出力している文言（/bin..)は、envの挙動を理解していない。 （レビュー項目にはないが、ナラさんが気になった部分。無理して本家とそろえるならやらない方がいい、言われていないことなので。本家は環境変数を使用している。しかし、環境変数の中身を変えること自体求められていない）
      - _=の挙動がおかしい
- [ ] minishell$ export A="s p a c e" minishell$ echo $A s

### これらはいらないかも
- [ ] 環境変数'~'は未対応(cd ~に対応させる)
- [ ] ディレクトリに入ってからその権限をなくすと抜けれなくなってしまう

	- ディレクトリ消されても戻れるようにする or エラーをしっかり出す
 		- 今はstatのエラーが出ている
		- 本家はOLDPWD、PWDとは別に今いるディレクトリを持っている
		- 対応しないのであればdefenceできるようにする

ファイルがない時の出力は"No such file or directory"に統一すべき？

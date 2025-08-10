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
  - [ ] `| cat`のときのエラー文がおかしい
  - [x] PATHがない時はCurrent dirだけにある実行ファイルを探すべき
  - [x] catの入力待ち中でctrl+cするとで変な出力が出る
  - [x] SIGQUITの出力を直す
  - [x] ctrl+cを連続で入力すると出力が崩れる
  - [ ] 入力途中で ctrl+cすると表示崩れる？
  - [ ] 今いるディレクトリが他のbashから消された時にcd ..で戻れない
  - [ ] minishell exit 1 2 でexit できちゃってる。
  - [ ] exit のエラー表示がおかしい
  - [x] ^C の表示 されていない、終了ステータスが０のまま
  - [ ] cd の存在しないディレクトリのエラーメッセージ
  - [ ] cd問題　同じ原因の問題が２つ
    - [ ] cd . や cd .. などの相対パス
    - [ ] PWD を unset した後、cd による PWD更新が上手くいっていない。
  - [ ] カレントディレクトリが消えた時(他のターミナルからディレクトリを消す)
  - [ ] 環境変数'~'は未対応
  - [ ] ディレクトリに入ってからその権限をなくすと抜けれなくなる？

ファイルがない時の出力は"No such file or directory"に統一すべき？

= VagrantでRe:VIEWサーバを作るよ

== Re:VIEWサーバを構築・起動してみる

□コマンドプロンプトで以下のコマンドを実行します。

//emlist{
cd C:\Users\naveffy\projects\review-sample-book\vagrant-review-precise64-master
vagrant up
//}


□sahara プラグインを試す(スナップショット機能)
※サーバを壊したり、元に戻したりできるよ。
//emlist{
vagrant plugin install sahara
vagrant sandbox on
vagrant sandbox status
vagrant sandbox rollback ← 元に戻す
vagrant sandbox commit ← 恒久的に反映
vagrant sandbox off
//}

□以下の共有フォルダにソースを置いて作業します。

//emlist{
C:\Users\naveffy\projects\review-sample-book
//}


□TeraTermで「192.168.33.10」へログイン。

 * ログオンID：vagrant
 * Passwd：vagrant


□PDFを作ってみる。

//emlist{
cd /home/vagrant/review-project
git clone git@github.com:naveffy/review.git
cd review
rake clean
rake pdf
//}

□Re:VIEWで雛形を生成してみる。
//emlist{
review-init test
//}

== jenkinsサーバを構築・起動してみる


□jenkinsインストール(古いバージョン)
//emlist{
sudo apt-get install jenkins
sudo apt-get remove jenkins ← アンインストール
//}

□jenkinsインストール(最新バージョン)
//emlist{
wget -q -O - http://pkg.jenkins-ci.org/debian/jenkins-ci.org.key | sudo apt-key add -
sudo sh -c 'echo deb http://pkg.jenkins-ci.org/debian binary/ > /etc/apt/sources.list.d/jenkins.list'
sudo aptitude update
sudo aptitude install jenkins
sudo service jenkins start
//}

□Webブラウザで「http://192.168.33.10:8080」を開いてみる。

== jenkinsサーバからgithubへアクセスしてみる


□githubのアクセス権を確認する。
//emlist{
# sudo -u jenkins ssh -T git@github.com
Permission denied (publickey). ← 「jenkins」ユーザ、アクセスデナイド。
//}

□SSH鍵を準備する。

//emlist{
$ sudo su jenkins
$ ls /var/lib/jenkins/.ssh/
$ ssh-keygen
$ ls
id_rsa  id_rsa.pub  known_hosts
$ cat id_rsa.pub ← 鍵の部分をコピーする。
//}

□Webブラウザで「https://github.com/」へログインする。

 * ログオンID：naveffy
 * Passwd：giko1234

□Webブラウザで「https://github.com/settings/ssh」を開く。
□[New SSH Key]押下する。
□以下の値を入力する。

 * title：jenkin
 * key：ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDFdZp4t7MGCQcrmkhLY1TykuusvLzoKfpzGu1yYvb0Tf2A3U9yEFLpPTXBGRYgzgJ5CPSrETMczh8KVmOf/p3is6m7sEc8ewHTkS34qAiYbW7P4s3Mr6pgVhzyJIyKq0sve/COgdVeq+aEiOezZTwMQ8vCGKM+99Nr15NZ7af7syu/DXpGOURbqerbRnwQK9QLZSSwoapKdS/4+PWHAi6/JbobzYvHYnDLeGALcaWgUAR8Lp4Re0uOQOk41VSRcZ4NpIlFxJAO6TjA/OJ3sfs2NYJPiJvQdPUOXX0b5c2T3Qlbd2cD2gA8y2t4ct6FQsppKoj5wO5KXEZz2iiEWnTd jenkins@precise64

□[Add SSH key]を押下する。

□SSH接続を確かめてみる。
//emlist{
$ ssh -T git@github.com
Hi naveffy! You've successfully authenticated, but GitHub does not provide shell access.
//}

□Webブラウザで「http://192.168.33.10:8080」を開いてみる。
□「Jenkinsの管理」->「プラグインの管理」->「利用可能」を押下する。
□以下のプラグインをインストールする。

 * Git Plugin
 * GitHub Plugin
 * GitHub API Plugin
 * Git Client Plugin
 * Run Condition Plugin
 * Run Condition Extras Plugin
 * Build Keeper Plugin
 * Conditional BuildStep Plugin
 * Flexible Publish Plugin
 * Parameterized Trigger plugin

□[新しいジョブ]を押下する。
□以下の内容でジョブを作成する。

 * ジョブ名：auto-build
 * [フリースタイル・プロジェクトのビルド]
 * プロジェクト名：auto-build
 * [ソースコード管理]-[Git]
 * Repository URL：git@github.com:naveffy/review.git
 * SSHユーザー名と秘密鍵、ユーザー名：naveffy、秘密鍵：Jenkinsマスター上の~/.sshから、説明：naveffy
 * Branch Specifier：*/master
 * [ビルド実行]
 * [ワークスペース]内に

□[ビルド]-[シェルの実行]を押下、以下の処理を記入する。
//emlist{
PATH=PATH=/sbin:/usr/sbin:/bin:/usr/bin:/home/vagrant/review/bin/
rake clean
rake pdf
//}

□[ビルド後の処理の追加]-[成果物を保存]を押下、以下のファイル名を設定してみる。

 * 保存するファイル：book.pdf









Pascalは1970年、スイスのチューリッヒ工科大学教授であったニクラス・ヴイルト（Niklaus Wirth）によって開発された。教育用として系統的な言語構造をもつこと、高度に抽象化された問題をできるだけ自然な形で明瞭に記述できることを目標にしたという。ALGOLの流れを汲み、厳密な構造化仕様を持っているが簡潔で使いやすく、実用性も高い。ヴイルト自身がPascalコンパイラをPascalで記述している。

//image[Niklaus_Wirth][Pascalの開発者、ニクラス・ヴイルト][scale=0.2]

1970年というとまだパソコンは登場しておらず、当時はミニコンや大型コンピュータで使われていたことになる。70年代中期に8ビットパソコンの普及が始まると、Pascalは本格的な開発言語として注目を集めた。まず、1978年にUCSD（カリフォルニア大学サンディエゴ校）のケネス・ボウルズ（Kenneth Bowles）が教育用にUCSD Pascalを開発した。UCSD Pascalはエディタ、デバッガ、ファイル管理機能などを備えた統合開発環境であった。さらにボウルズはUCSD Pascalを使ってUCSD p-SystemというOSまで開発した。

=== 一世を風靡したTurbo Pascal

だが、Pascalを有名にしたのはボーランド社Turbo Pascalの功績だろう。フィリップ・カーン（Philippe Kahn）が1982年に設立したボーランド社は、CP/Mで動く統合開発環境Turbo Pascalをリリースした。カーンは学生時代、ヴィルトのPascal講義を受けたと言われている。

===[column] コンパイラコンパイラ
 
ここにコラムの内容を書きます。ここにコラムの内容を書きます。
ここにコラムの内容を書きます。
 
ここにコラムの内容を書きます。
 
===[/column]


現在のReVIEW処理系はRuby@<fn>{ruby}で記述されています。

//footnote[ruby][まつもとゆきひろさんが開発されているスクリプト言語]

//quote{
「おい地獄さ行ぐんだで！」
　二人はデッキの手すりに寄りかかって、蝸牛が背のびをしたように延びて、海を抱え込んでいる函館の街を見ていた。
（小林多喜二『蟹工船』）
//}

 * 水星
 * 金星
 * 地球
 * 火星

 1. 水星
 2. 金星
 4. 地球
 4. 火星

//table[envvars][重要な環境変数]{
名前	意味
-------------------------------------------------------------
PATH	コマンドの存在するディレクトリ
TERM	使っている端末の種類。linux・kterm・vt100など
LANG	ユーザのデフォルトロケール。日本語ならja_JP.eucJPやja_JP.utf8
LOGNAME	ユーザのログイン名
TEMP	一時ファイルを置くディレクトリ。/tmpなど
PAGER	manなどで起動するテキスト閲覧プログラム。lessなど
EDITOR	デフォルトエディタ。viやemacsなど
MANPATH	manのソースを置いているディレクトリ
DISPLAY	X Window Systemのデフォルトディスプレイ
//}

: Alpha
  DEC の作っていた RISC CPU。
  浮動小数点数演算が速い。
: POWER
  IBM とモトローラが共同製作した RISC CPU。
  派生として POWER PC がある。
: SPARC
  Sun が作っている RISC CPU。
  CPU 数を増やすのが得意。

//list[list][リストのサンプル]{
int main(int argc, char **argv) {
  puts("OK");
  return 0;
}
//}

//emlist{
printf("hello");
//}

//listnum[listnum][番号付きリストのサンプル]{
int main(int argc, char **argv) {
  puts("OK");
  return 0;
}
//}

//emlistnum{
 puts "hello world!"
//}



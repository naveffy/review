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

□[ビルド実行]を実行してみる。

□[最新成功ビルドの成果物]のbook.pdfをクリックしてみる。

== 電子書籍(PDF)を作ってみる。

□「vagrant」アカウント用に鍵をコピーしてみる。
//emlist{
cd /home/vagrant/.ssh
sudo cp /var/lib/jenkins/.ssh/id_rsa ./
sudo chown vagrant id_rsa
cd /home/vagrant/review-project
git clone git@github.com:naveffy/review.git
git commit -m "add new file"
git status
git push origin master
//}

□id_rsaを共有フォルダにコピーする。
□「C:\Program Files\TortoiseGit\bin\puttygen.exe」を起動。
□id_rsaをppk形式に変換する。
□TortoiseGitを使う。
□フォルダで右クリック、[TortoiseGit]-[設定]を開く。
□[Git]-[リモート]-[origin]を選択、以下の値を入力。

 * リモート：origin
 * URL：origin：git@github.com:naveffy/review.git
 * 鍵：C:\home\watanabe\20160308_Vagrant\id_rsa.ppk

□「sample-document.re」を編集してみる。
□フォルダで右クリック、[Gitコミット->master]を選択する。
□メッセージ欄に適当な文字列を入れ、[OK]を押下する。
□[プッシュ(リモートへの反映)]を押下、[OK]を押下する。







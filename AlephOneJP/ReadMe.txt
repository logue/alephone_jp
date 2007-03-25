これは何？

AlephOne-SDLで日本語を表示できるようにしたソース差分（と変更されたソース）

利用方法
RenderOther/	->	ソースツリーのRenderOtherへコピー（同名ファイルは上書き）
XML/		->	同じくExpatフォルダへ
Expat/		-> 	同じくExpatフォルダへ
Fonts/		->	バイナリと同じディレクトリにコピー

OSX 10.4+Marathon Infinity 日本語版で検証済み
Windows2000+M1A1 Jでも動作を確認

今できること：
Soft描画/OpenGLでの日本語表示
Shift-JIS/(EUC-JP?/UTF-8?)でのMML

バグ：
たまにごみが表示される（プレイに支障はない？）
最初の起動でファイルの読み込みに失敗する(prefで変更すればOK)
一部の音楽が再生されない？（条件不明、AIFFは可）
メモリーリークのために２度目以降にテクスチャーが一部表示されない（修正された？）

Special Thanks
SDL_Kanji
ShinonomeFont
Expat_JP

Windows用のバイナリを添付しておきます。（リリース版はビルド環境不要のはずだが未検証のためわからない）

不都合はookawa_mi@hotmail.comまで
一応昔のバージョンを作った人とは無関係です。
ライセンスはオリジナルと同じでお願いします。
ベースはたぶん2006/12ごろのcvsバージョン

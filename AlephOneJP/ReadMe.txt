これは何？

AlephOne-SDLで日本語を表示できるようにしたソース差分（と変更されたソース）

利用方法
RenderOther/	->	ソースツリーのRenderOtherへコピー（同名ファイルは上書き）
XML/		->	同じくExpatフォルダへ
Expat/		-> 	同じくExpatフォルダへ
Fonts/		->	バイナリと同じディレクトリにコピー

OSX 10.4+Marathon Infinity 日本語版で検証済み

今できること：
Soft描画/OpenGLでの日本語表示
Shift-JIS/(EUC-JP?/UTF-8?)でのMML

バグ：
一部文字が切れる

Special Thanks
SDL_Kanji
ShinonomeFont
Expat_JP

不都合はookawa_mi@hotmail.comまで
一応昔のバージョンを作った人とは無関係です。Winの開発環境はないのでバイナリの配布はできません。
ライセンスはオリジナルと同じでお願いします。
ベースはたぶん2006/12ごろのcvsバージョン

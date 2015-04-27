#!/usr/bin/fontforge -script

# 新しいフォント名
family = "AlephJPSunsMono"


Open("mplus-1mn-bold.ttf")

# IPAゴシックの高さをDejaVu Sans Monoに揃える
ScaleToEm(2048)

# 別ファイルとして保存
Generate("AlephJPSansMono-Bold.ttf")

Close()


Open("AlephSansMono-Bold.ttf")

# DejaVu Sans Monoの横幅を縮小する処理
SelectWorthOutputting()
Scale(75,100)
SetWidth(1024)
SelectNone()

# 高さを揃えたIPAゴシックをマージ
MergeFonts("AlephJPSansMono-Bold.ttf")

#フォント名等を指定して保存
SetFontNames(family, family, family, "Bold")
Generate(family + ".ttf")

Close()
#!/usr/bin/fontforge -script

# �V�����t�H���g��
family = "AlephJPSunsMono"


Open("mplus-1mn-bold.ttf")

# IPA�S�V�b�N�̍�����DejaVu Sans Mono�ɑ�����
ScaleToEm(2048)

# �ʃt�@�C���Ƃ��ĕۑ�
Generate("AlephJPSansMono-Bold.ttf")

Close()


Open("AlephSansMono-Bold.ttf")

# DejaVu Sans Mono�̉������k�����鏈��
SelectWorthOutputting()
Scale(75,100)
SetWidth(1024)
SelectNone()

# �����𑵂���IPA�S�V�b�N���}�[�W
MergeFonts("AlephJPSansMono-Bold.ttf")

#�t�H���g�������w�肵�ĕۑ�
SetFontNames(family, family, family, "Bold")
Generate(family + ".ttf")

Close()
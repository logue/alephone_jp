#include "HPLStringModifier.h"

/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
std::vector<std::string> hpl::string::Split( std::string src, const char* key){
	//���ʗp
	std::vector<std::string> vList;

	int index = 0;
	//�p�ӂ��ꂽ������src�̒������������ׂ�B
	//�܂��A1�T���邲�Ƃ�index�Ɍ������ʂ��o��̂ŁA�������ʂ����������ꍇ�ɏI������B
	while( index < static_cast<int>(src.size()) && index != static_cast<int>(std::string::npos)){
		//�O�Ɍ��������ꏊ���o���Ă���
		int oldindex = index;
		//�w�蕶����őO���猟������
		index = (int)src.find( key,index);
		if( index != (int)std::string::npos){
			//��������
			//���O�Ɍ��������ꏊ����index�܂�((index-oldindex)��)���擾
			std::string str = src.substr( oldindex, index-oldindex);
			//���ʂɒǉ��B
			vList.push_back(str);
			//�����ʒu���L��
			index += (int)strlen(key);//key.size();
		}else{
			//������Ȃ�����
			//�����̏ꏊ����Ō�܂ł��Ō�̗v�f�Ƃ��Ēǉ��B����while�Ń��[�v���甲����
			std::string str = src.substr(oldindex);
			vList.push_back(str);
		}
	}
	return vList;
}

/*
    ������̐擪�Ɏw�萔�̕�����t��
    @param src �Ώ�
    @param power �ő啶����
    @param appender �t�����镶����
*/
std::string hpl::string::appendFrontString(std::string &src,
                                           int power,
                                           std::string& appender)
{
    std::string result = src;
    //���łɃI�[�o�[���Ă���ꍇ�����������R�s�[��Ԃ�
    if((int)(src.size()) > power){
        return result;
    }
    //�����񒷂��I�[�o�[����܂�
    while((int)(result.size()) <= power){
        result = appender + result;
    }
    //�I�[�o�[������J�b�g
    if((int)(result.size()) > power){
        result = result.substr(result.size() - power);
    }
    return result;
}

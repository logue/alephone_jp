/**
    ���[�U�[���m�邱�Ƃ̖����E�m��ׂ��łȂ��ݒ�t�@�C���ł�
    <en>user should not change these settings

*/

#ifndef _MAP_EDITOR_ONE_INNER_SETTING_
#define _MAP_EDITOR_ONE_INNER_SETTING_

//#include <vector>
#include <string>
#include <map>

namespace mapeditorone{
    namespace TagType{
        enum{
            //zooms
            ZOOM_DIVISION_STEP,
            ZOOM_DIV_STEP_THRESHOLD,
            ZOOM_DIVISION_STEP_DETAIL,
            ZOOM_DIVISION_MAX,
            ZOOM_DIVISION_MIN,
            ZOOM_DIVISION_DEFAULT,
            WORLD_OFFSET_X,
            WORLD_OFFSET_Y,
            POINT_DISTANCE_THRESHOLD,
            OBJECT_DISTANCE_THRESHOLD,
            LINE_DISTANCE_THRESHOLD,
            MaxTagTypes
        };
    };

    class MapEditorOneInnerSetting{
    private:
/*        //���f�[�^
        std::vector<std::string> rawData;
*/
        /**�^�O���̂̃��X�g�B�ʂ̃t�@�C������ǂݍ���*/
        std::map<int, std::string> tagMap;
        
        /**�^�O�ɑΉ�����f�[�^*/
        std::map<int, std::string> datas;
    public:
        MapEditorOneInnerSetting(const char* tagNameFilePath, const char* dataFilePath);
        ~MapEditorOneInnerSetting();
    public:
        std::string getString(int type);
        int getInt(int type);
        double getDouble(int type);
    };

};

#endif

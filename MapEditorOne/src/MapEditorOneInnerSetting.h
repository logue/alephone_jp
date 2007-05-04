/**
    ユーザーが知ることの無い・知るべきでない設定ファイルです
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
/*        //元データ
        std::vector<std::string> rawData;
*/
        /**タグ名称のリスト。別のファイルから読み込む*/
        std::map<int, std::string> tagMap;
        
        /**タグに対応するデータ*/
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

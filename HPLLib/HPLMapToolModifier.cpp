#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"
#include "map.h"
#include "HPLStockManager.h"
//角度の最大
const double DEG_ROUND = 360.0;

//////////////////////////////////////////////////////
/////// add delete and modify
/**
	点情報を追加します
	@param ep 追加する点データ（値渡しなのでコピーされます）
	@return 追加された点のインデックス値
*/
int hpl::aleph::map::addEndpoint(endpoint_data ep)
{
	EndpointList.push_back(ep);
	dynamic_world->endpoint_count = (int16)EndpointList.size();
	int index = dynamic_world->endpoint_count - 1;
	return index;
}
int hpl::aleph::map::addLine(line_data line)
{
	LineList.push_back(line);
	dynamic_world->line_count = (int16)LineList.size();
	int index = dynamic_world->line_count - 1;
	return index;
}
int hpl::aleph::map::addSide(side_data side, bool isClockwise)
{
	SideList.push_back(side);
	dynamic_world->side_count = (int16)SideList.size();
	int index = dynamic_world->side_count - 1;
    //依存するものを修正する
    //・線
    //・ポリゴン
    //・Side
    //TODO 左右の確認が必要
    side_data* newSide = get_side_data(index);
    line_data* line = get_line_data(newSide->line_index);
#ifdef __WXDEBUG__
    wxASSERT(line);
#else
    if(!line){
        hpl::error::halt("line[%d] doesn't exist", newSide->line_index);
    }
#endif
    polygon_data* poly = get_polygon_data(newSide->polygon_index);
#ifdef __WXDEBUG__
    wxASSERT(poly);
#else
    if(!poly){
        hpl::error::halt("polygon[%d] doesn't exist", newSide->polygon_index);
    }
#endif
    if(isClockwise){
        line->clockwise_polygon_side_index = index;
    }else{
        line->counterclockwise_polygon_side_index = index;
    }

    //ポリゴン
    int lineIndexInPolygon = NONE;
    for(int i = 0; i < poly->vertex_count; i ++){
        if(poly->line_indexes[i] == newSide->line_index){
            lineIndexInPolygon = i;
            break;
        }
    }
#ifdef __WXDEBUG__
    wxASSERT(lineIndexInPolygon != NONE);
#else
    if(lineIndexInPolygon == NONE){
        hpl::error::halt("line[%d] doesn't exist in polygon[%d]'s line_index", newSide->line_index,
            newSide->polygon_index);
    }
#endif
    poly->side_indexes[lineIndexInPolygon] = index;


	return index;
}
int hpl::aleph::map::addPolygon(polygon_data polygon)
{
	PolygonList.push_back(polygon);
	dynamic_world->polygon_count = (int16)PolygonList.size();
	int index = dynamic_world->polygon_count - 1;

    polygon_data* poly = get_polygon_data(index);

    //以下の依存する項目を修正する
    //・点（adjacent）
    //・線（owner）
    //・Side
    //TODO
    for(int i = 0; i < poly->vertex_count; i ++){
        int next = i + 1;
        if(next >= poly->vertex_count){
            next = 0;
        }
        endpoint_data* ep1 = get_endpoint_data(poly->endpoint_indexes[i]);
        //関連ポリゴンの指定が無ければ指定
        if(ep1->supporting_polygon_index == NONE){
            ep1->supporting_polygon_index = index;
        }

        endpoint_data* ep2 = get_endpoint_data(poly->endpoint_indexes[next]);

        //線
        line_data* line = get_line_data(poly->line_indexes[i]);
        if(line->endpoint_indexes[0] == poly->endpoint_indexes[i]){
            //順向き→clockwise
            line->clockwise_polygon_owner = index;
            side_data* side = get_side_data(line->clockwise_polygon_side_index);
            if(side)
                side->polygon_index = index;
        }else if(line->endpoint_indexes[0] == poly->endpoint_indexes[next]){
            //逆向き→counterclockwise
            line->counterclockwise_polygon_owner = index;
            side_data* side = get_side_data(line->counterclockwise_polygon_side_index);
            if(side)
                side->polygon_index = index;
        }else{
#ifdef __WXDEBUG__
            wxASSERT(false);
#else
            hpl::error::halt("invalid polygon frame");
#endif
        }
    }
	return index;
}
int hpl::aleph::map::addMapSavedObject(map_object object)
{
	SavedObjectList.push_back(object);
	//TODO
	//プレースメント情報に付加

	//TODO どれを集計すれば良いのか？
//	dynamic_world->object_count ++;// SavedObjectList.size();
	dynamic_world->initial_objects_count = (int16)SavedObjectList.size();
	int index = dynamic_world->initial_objects_count - 1;

    map_object* obj = &SavedObjectList[index];

    //依存する項目を修正する
    //・ポリゴン
    polygon_data* poly = get_polygon_data(obj->polygon_index);
#ifdef __WXDEBUG__
    wxASSERT(poly);
#else
    if(!poly){
        hpl::error::halt("poly[%d] not found", obj->polygon_index);
    }
#endif
    if(poly->first_object == NONE){
        poly->first_object = index;
    }
	return index;
}
int hpl::aleph::map::addAnnotation(map_annotation annotation)
{
	MapAnnotationList.push_back(annotation);
/*	dynamic_world-> = MapAnnotationList.size();
	int index = dynamic_world->annotation_count - 1;*/
	int index = (int16)MapAnnotationList.size() - 1;
	return index;
}

/**
    マップアイテム（点・線・Side・ポリゴン・オブジェクト）
    を削除します
    手法としては、
    １：線の端点など、参照元が削除対象となっている場合、
        ・参照をNONEにする
        ・自分自身も削除対象とする
    ２：削除対象を削除していく
        ・削除番号の列を作る
        ・後ろ側から消していく

    @param 
*/
bool hpl::aleph::map::deleteMapItems(std::vector<bool>& delPoints, std::vector<bool>& delLines,
                                     std::vector<bool>& delSides,
    std::vector<bool>& delPolygons, std::vector<bool>& delObjects)
{
    if(delPoints.size() != EndpointList.size() ||
        delPoints.size() != dynamic_world->endpoint_count ||
        delLines.size() != LineList.size() ||
        delLines.size() != dynamic_world->line_count ||
        delSides.size() != SideList.size() ||
        delSides.size() != dynamic_world->side_count ||
        delPolygons.size() != PolygonList.size() ||
        delPolygons.size() != dynamic_world->polygon_count ||
        delObjects.size() != SavedObjectList.size())
    {
        hpl::error::halt("数があっていない");
        return false;
    }



    /////////////////
    //実際に削除する
    std::map<int, int> indexMapPoints;
    std::map<int, int> indexMapLines;
    std::map<int, int> indexMapSides;
    std::map<int, int> indexMapPolygons;
    std::map<int, int> indexMapObjects;
    //対応表を作る
    int counter = 0;
    for(int i = 0; i < (int)delPoints.size(); i ++){
        if(!delPoints[i]){   indexMapPoints[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delLines.size(); i ++){
        if(!delLines[i]){   indexMapLines[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delSides.size(); i ++){
        if(!delSides[i]){   indexMapSides[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delPolygons.size(); i ++){
        if(!delPolygons[i]){   indexMapPolygons[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delObjects.size(); i ++){
        if(!delObjects[i]){   indexMapObjects[i] = counter;   counter ++;}
    }

    //インデックスを付け直す
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(!delPoints[i]){
            endpoint_data* ep = get_endpoint_data(i);
            ep->supporting_polygon_index = indexMapPolygons[ep->supporting_polygon_index];
        }
    }
    for(int i = 0; i < (int)LineList.size(); i ++){
        if(!delLines[i]){
            line_data* line = get_line_data(i);
            assert(line);
            if(line->clockwise_polygon_owner != NONE){
                line->clockwise_polygon_owner = indexMapPolygons[line->clockwise_polygon_owner];
            }
            if(line->clockwise_polygon_side_index != NONE){
                line->clockwise_polygon_side_index = indexMapSides[line->clockwise_polygon_side_index];
            }
            if(line->counterclockwise_polygon_owner != NONE){
                line->counterclockwise_polygon_owner = indexMapPolygons[line->counterclockwise_polygon_owner];
            }
            if(line->counterclockwise_polygon_side_index != NONE){
                line->counterclockwise_polygon_side_index = indexMapSides[line->counterclockwise_polygon_side_index];
            }
            for(int j = 0; j < 2; j ++){
                line->endpoint_indexes[j] = indexMapPoints[line->endpoint_indexes[j]];
            }
        }
    }
    for(int i = 0; i < (int)SideList.size(); i ++){
        if(!delSides[i]){
            side_data* side = get_side_data(i);
            assert(side);
            side->line_index = indexMapLines[side->line_index];
            side->polygon_index = indexMapPolygons[side->polygon_index];
        }
    }
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(!delPolygons[i]){
            polygon_data* poly = get_polygon_data(i);
            assert(poly);
            int n = poly->vertex_count;
            for(int j = 0; j < n; j ++){
                if(poly->adjacent_polygon_indexes[j] != NONE){
                    poly->adjacent_polygon_indexes[j] =
                        indexMapPolygons[poly->adjacent_polygon_indexes[j]];
                }
                poly->line_indexes[j] = indexMapLines[poly->line_indexes[j]];
                poly->endpoint_indexes[j] = indexMapPoints[poly->endpoint_indexes[j]];
                poly->side_indexes[j] = indexMapSides[poly->side_indexes[j]];
            }
            if(poly->first_object != NONE){
                poly->first_object = indexMapObjects[poly->first_object];
            }
        }
    }
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(!delObjects[i]){
            map_object* obj = &SavedObjectList[i];
            obj->polygon_index = indexMapPolygons[obj->polygon_index];
        }
    }

    return true;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/// add
/**
    基本の線&点からつながる線のうち、サイズがもっとも小さくなるように
    点のリストを取得します。点の並びはポリゴン指定にそのまま使える物となっています。

    再帰的に呼び出します。
    @param pointIndexes これまでにつなげてきた点のリスト。この個数がMAXIMUM_VERTEX_PER_POLYGON
        を超えたら見つからなかったものとする
    @return ポリゴンが完結した場合真
*/
static bool getValidLines(int basePointIndex, int baseLineIndex,
                          std::vector<int> *pointIndexes,
                          hpl::aleph::HPLStockManager* smgr,
                          int rotRem, std::set<int>* doneList,
                          int zMin, int zMax,
                          world_point2d& wpoint)
{
    //最大の角度
    double maxDeg = 0;
    int maxLineIndex = NONE;

    line_data* baseLine = get_line_data(baseLineIndex);
    int startBasePointIndex = baseLine->endpoint_indexes[0];
    int endBasePointIndex =  baseLine->endpoint_indexes[1];
    if(startBasePointIndex == basePointIndex){
        //入れ替え
        hpl::math::exchange(&startBasePointIndex, &endBasePointIndex);
    }else if(endBasePointIndex == basePointIndex){
    }else{
        hpl::error::halt("invalid basePointIndex");
    }

    int lastPointIndex = NONE;
    //ベースポイントに繋がる線を取り出す
    std::vector<int> conLines = hpl::aleph::map::getLineIndexesIncludePoint(basePointIndex);
    for(int k = 0; k < (int)conLines.size(); k ++){
        int conLineIndex = conLines[k];
        if(doneList->find(conLines[k]) != doneList->end()){
            //既に見つけ出したものは省く
            continue;
        }
        //delLinesは省く
        if(smgr->delLines[conLineIndex]){
            continue;
        }
        //ベースの線と一緒の場合も除外する
        if(baseLineIndex == conLineIndex){
            continue;
        }

        line_data* line = get_line_data(conLineIndex);
        if(!line)hpl::error::halt("line is null");
        //高さチェック
        if(!hpl::aleph::map::isValidHeight(line->highest_adjacent_floor,
            line->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int ep0Index = line->endpoint_indexes[0];
        int ep1Index = line->endpoint_indexes[1];
        if(basePointIndex == ep0Index){
        }else if(basePointIndex == ep1Index){
            //入れ替え
            hpl::math::exchange(&ep0Index, &ep1Index);
        }else{
            assert(false);
        }

        endpoint_data* ep0 = get_endpoint_data(ep0Index);
        if(!ep0)hpl::error::halt("ep0 is null");
        endpoint_data* ep1 = get_endpoint_data(ep1Index);
        if(!ep1)hpl::error::halt("ep1 is null");

        double l0x = ep0->vertex.x;
        double l0y = ep0->vertex.y;
        double l1x = ep1->vertex.x;
        double l1y = ep1->vertex.y;
        //線から指定点に対する角度を求める（左右の確認）
        int rot = hpl::math::getPointRotationTypeFromLine(
            wpoint.x, wpoint.y, l0x, l0y, l1x, l1y);
        //最初の線と違う（逆向き）に指定点が来ている場合は正しくないものとする。
        if(rotRem != rot){
            continue;
        }

        //前の線の始点→共有点→最後の点で角度を求める
        //前の線の始点
        endpoint_data* prevStartEp = get_endpoint_data(startBasePointIndex);
        assert(prevStartEp);
        double deg = hpl::math::getTwoLinesDegree(prevStartEp->vertex.x,
            prevStartEp->vertex.y, l0x, l0y,
            l0x, l0y, l1x, l1y);
        //[0,360)に制限する
        deg = hpl::math::optimizeDegree(deg);
        if(deg > DEG_ROUND / 2.0){
            deg = DEG_ROUND - deg;
        }
        //角度が現在最大かどうか確認する
        if(deg > maxDeg){
            maxDeg = deg;
            //今までより大きい
            maxLineIndex = conLineIndex;
            //最後の点
            lastPointIndex = ep1Index;
        }
        //済み
        doneList->insert(conLineIndex);
    }

    if(maxLineIndex == NONE){
        //見つからなかった
        //よって戻っていく
        return false;
    }else{
        //見つかった
        //最後に追加する
        pointIndexes->push_back(lastPointIndex);

        //最後の点がpointIndexes[0]と同一（一周してきた）だったら
        //終わったとする
        if(lastPointIndex == pointIndexes->at(0)){
            //ポリゴンとして成立するセットを見つけ出せた
            return true;
        }else{
            //まだまだ
            if(pointIndexes->size() >= MAXIMUM_VERTICES_PER_POLYGON + 1){
                return false;
            }
            //もう最大数を超えている
            //次を探す
            baseLineIndex = maxLineIndex;
            basePointIndex = lastPointIndex;
            bool found = getValidLines(basePointIndex, baseLineIndex, pointIndexes,
                smgr, rotRem, doneList, zMin, zMax, wpoint);
            //結局見つかったかどうかは子供だけが知っている
            return found;
        }
    }
}

/**
    座標を取り囲むポリゴンのうち、ポリゴンとして成立しているものをさがします
    すでにポリゴンが存在している場合は無視します
    @param wpoint 探索基点。ここを囲むポリゴンを探す
    @return ポリゴンの実データ候補。これを元に生成すると良い。データはcreatePolygonで生成すべし
*/
std::vector<polygon_data> hpl::aleph::map::searchValidPolygon(world_point2d wpoint,
                                                              hpl::aleph::HPLStockManager* smgr,
                                                              int zMin, int zMax)
{
    std::vector<polygon_data> polyDatas;

    int max = (int)LineList.size();
    //線への垂線の距離順で整列する
    //全部の線への垂線を求める
    struct hpl::math::qsort::Pair<double>* pairs = new struct hpl::math::qsort::Pair<double>[max];
    for(int i = 0; i < max; i ++){
        line_data* line = get_line_data(i);
        assert(line);
        endpoint_data* epStart = get_endpoint_data(line->endpoint_indexes[0]);
        assert(epStart);
        endpoint_data* epEnd = get_endpoint_data(line->endpoint_indexes[1]);
        assert(epEnd);
        pairs[i].data = hpl::math::getPointDistanceFromLine(wpoint.x, wpoint.y, 
            epStart->vertex.x, epStart->vertex.y, epEnd->vertex.x, epEnd->vertex.y);
    }
    hpl::math::qsort::quickSort<double>(pairs, max);

    //既に調べたリスト(線のインデックス値を入れる)
    std::set<int> doneList;

    //近くにある線から見ていく
    for(int i = 0; i < max; i ++){
        //削除対象なら無視
        if(smgr->delLines[i]){
            continue;
        }
        //すでに調べた線なら無視
        if(doneList.find(i) != doneList.end()){
            continue;
        }
        int lineIndexBase = pairs[i].index;
        line_data* startLine = get_line_data(lineIndexBase);
        if(!startLine)hpl::error::halt("startLine is null");
        //高さチェック
        if(!hpl::aleph::map::isValidHeight(startLine->highest_adjacent_floor,
            startLine->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int startPointIndex = startLine->endpoint_indexes[0];
		endpoint_data* epStart = get_endpoint_data(startPointIndex);
        if(!epStart)hpl::error::halt("epStart is null");
        int endPointIndex = startLine->endpoint_indexes[1];
		endpoint_data* epEnd = get_endpoint_data(endPointIndex);
        if(!epEnd)hpl::error::halt("epEnd is null");

        //線の左右どちらの側に点があるかをチェックします
		int rotRem = hpl::math::getPointRotationTypeFromLine(
			wpoint.x, wpoint.y, epStart->vertex.x, epStart->vertex.y,
			epEnd->vertex.x, epEnd->vertex.y);
        if(rotRem == hpl::math::RotationType::Clockwise &&
            startLine->counterclockwise_polygon_owner != NONE)
        {
            //右周りで、かつ線の右側（指定点のある領域）
            //にポリゴンが既にある場合スキップ
            hpl::error::caution("already polygon exists");
            continue;
        }
        if(rotRem == hpl::math::RotationType::Counterclockwise &&
            startLine->clockwise_polygon_owner != NONE)
        {
            hpl::error::caution("already polygon exists");
            continue;
        }
        //これ以降はすでに指定点の部分にポリゴンがないと仮定する

        //基点
		int nowBasePointIndex = endPointIndex;
        int prevLineIndex = lineIndexBase;
		//TODO
        //startLine->endpoint_indexes[1]からつながる線を調べる
        std::vector<int> pointIndexes;
        //最初の二つを代入しておく
        pointIndexes.push_back(startPointIndex);
        pointIndexes.push_back(endPointIndex);

        bool found = getValidLines(nowBasePointIndex, prevLineIndex,
            &pointIndexes, smgr, rotRem, &doneList,
            zMin, zMax, wpoint);
        if(found){
            //発見！
            //点インデックス（値渡し用）
            int indexes[MAXIMUM_VERTICES_PER_POLYGON];

            //点データ集計
            for(int l = 0; l < (int)pointIndexes.size() - 1; l ++){
                //
                indexes[l] = pointIndexes[l];
            }
            int vertexCount = (int)pointIndexes.size() - 1;
            //ポリゴン作成
            polygon_data poly;
            hpl::aleph::map::createPolygon(indexes, vertexCount, &poly);
            
            polyDatas.push_back(poly);

            //TODO 複数見つけ出すのか？
            //高さ順？何のことかね？
            //感覚的に近い線を取ればいいんじゃね？
            break;
        }
        doneList.insert(i);
    }
    
    //解放
    delete pairs;
    return polyDatas;
}

/**
    世界座標からポリゴンデータを作ります
    TODO 整合性
    @param points 世界座標
    @param ep 生成された点データ
    @param ld 生成された線データ
    @param n n角形
*
polygon_data hpl::aleph::map::createPolygon(world_point2d points[],
                                            endpoint_data epd[], line_data ld[],
        int n)
{
    //点生成
    for(int i = 0; i < n; i ++){
        epd[i].flags = 0;
        epd[i].highest_adjacent_floor_height = 0;
        epd[i].lowest_adjacent_ceiling_height = WORLD_ONE;
        epd[i].vertex.x = points[i].x;
        epd[i].vertex.y = points[i].y;

        epd[i].supporting_polygon_index = 0;
    }

    //線
    for(int i = 0; i < n ; i ++){
        ld[i].endpoint_indexes[0] = i;
        ld[i].endpoint_indexes[1] = i + 1;
        if(i == n - 1){
            ld[i].endpoint_indexes[0] = i;
            ld[i].endpoint_indexes[1] = 0;
        }
        ld[i].flags = SOLID_LINE_BIT | ELEVATION_LINE_BIT;

        ld[i].highest_adjacent_floor = 0;
        ld[i].lowest_adjacent_ceiling = WORLD_ONE;
	    ld[i].clockwise_polygon_side_index = NONE;
        ld[i].counterclockwise_polygon_side_index = NONE;
    	
	    ld[i].clockwise_polygon_owner = 0;
        ld[i].counterclockwise_polygon_owner = NONE;

        ld[i].length = (world_distance)hpl::aleph::map::getPointsDistance(
            epd[ld[i].endpoint_indexes[0]].vertex, epd[ld[i].endpoint_indexes[1]].vertex);
    }

    //ポリゴン
    polygon_data pdata;
	pdata.type = _polygon_is_normal;
	pdata.flags = 0;
	pdata.permutation = 0;

	pdata.vertex_count = n;
    for(int i = 0; i < n; i ++){
        pdata.endpoint_indexes[i] = i; //* clockwise *
        pdata.line_indexes[i] = i;
        pdata.side_indexes[i] = NONE;
    }
	
	pdata.floor_texture = NONE;
    pdata.ceiling_texture = NONE;
	pdata.floor_height = 0;
    pdata.ceiling_height = WORLD_ONE;
	pdata.floor_lightsource_index = NONE;
    pdata.ceiling_lightsource_index = NONE;
	
//	pdata.area; 
	
	pdata.first_object = NONE;
	
//	pdata.first_exclusion_zone_index;
//	pdata.line_exclusion_zone_count;
//	pdata.point_exclusion_zone_count;

	pdata.floor_transfer_mode = 0;
	pdata.ceiling_transfer_mode = 0;
	
//	pdata.adjacent_polygon_indexes[MAXIMUM_VERTICES_PER_POLYGON];
	
	pdata.first_neighbor_index = NONE;
	pdata.neighbor_count = 0;
	
    //
//    pdata.center;
	
//	pdata.side_indexes[MAXIMUM_VERTICES_PER_POLYGON];
	
//	pdata.floor_origin;
//  pdata.ceiling_origin;
	
	pdata.media_index = NONE;
	pdata.media_lightsource_index = NONE;
	
	pdata.sound_source_indexes = NONE;
	
	pdata.ambient_sound_image_index = NONE;
	pdata.random_sound_image_index = NONE;
	
    return pdata;
}
*/
/**
    独立したポリゴンデータを追加します
*
void hpl::aleph::map::addNewPolygon(polygon_data& pdata, endpoint_data epd[],
                                    line_data ld[], int n)
{
    //点
    std::map<int,int> epIndexTable;
    std::string str;
    for(int i = 0; i < n; i ++){
        //点の追加
		int newIndex = hpl::aleph::map::addEndpoint(epd[i]);
        epIndexTable[i] = newIndex;

    }
//    const char *buf = str.c_str();

    //線の追加
    std::map<int,int> lIndexTable;
    for(int i = 0; i < n; i ++){
        //修正
        for(int j = 0; j < 2; j ++){
            ld[i].endpoint_indexes[j] = epIndexTable[ld[i].endpoint_indexes[j]];
        }

        
		int newIndex = hpl::aleph::map::addLine(ld[i]);
        lIndexTable[i] = newIndex;
    }
    
    //ポリゴン情報修正
    for(int i = 0; i < n; i ++){
        pdata.endpoint_indexes[i] = epIndexTable[pdata.endpoint_indexes[i]];
        pdata.line_indexes[i] = lIndexTable[pdata.line_indexes[i]];
        pdata.side_indexes[i] = NONE;
    }
	
	//ポリゴン追加
	int newPolygonIndex = hpl::aleph::map::addPolygon(pdata);
	//線情報修正
    for(int i = 0; i < n; i ++){
        int newIndex = epIndexTable[i];
        endpoint_data* ep = get_endpoint_data(newIndex);
        ep->supporting_polygon_index = newPolygonIndex;
    }
    for(int i = 0; i < n - 1; i ++){
        int newIndex = lIndexTable[i];
        line_data* l = &(LineList[newIndex]);
        l->clockwise_polygon_owner = newPolygonIndex;
		l->counterclockwise_polygon_owner = NONE;
    }
   
}
*/

void hpl::aleph::map::addNewPolygon(world_distance points[][2], int n)
{
    world_point2d pt[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        pt[i].x = points[i][0];
        pt[i].y = points[i][1];
    }
    hpl::aleph::map::addNewPolygon(pt, n);
}
void hpl::aleph::map::addNewPolygon(world_point2d points[], int n)
{
    //endpointの作成
    int epIndexes[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        //endpointの生成
        endpoint_data ep;
        hpl::aleph::map::createPoint(points[i], &ep);
        int epIndex = hpl::aleph::map::addEndpoint(ep);
        epIndexes[i] = epIndex;
    }

    //lineの作成
    //int lineIndexes[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        int next = i + 1;
        if(next >= n){
            next = 0;
        }
        line_data line;
        hpl::aleph::map::createLine(epIndexes[i], epIndexes[next], &line);
        int lineIndex = hpl::aleph::map::addLine(line);
        //lineIndexes[i] = lineIndex;
    }
    polygon_data poly;
    hpl::aleph::map::createPolygon(epIndexes, n, &poly);
    hpl::aleph::map::addPolygon(poly);
}

